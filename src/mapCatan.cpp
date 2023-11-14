#include "../header/mapCatan.h"

MapCatan::MapCatan()
{
    Tile* aux = root;
    Tile* prevAux = root;
    
    int row = 1;
    int colum = 3;

    while(true)
    {   
        Tile* aux2 = aux;
        for(int k = 1; k < colum; k++)
        {
            Tile* newTile = new Tile();
            newTile->left = aux2;
            aux2->right = newTile;
            aux2 = newTile;

            if(row > 1)
            {
                if(row > 3)
                {
                    aux2->topLeft = prevAux;
                    prevAux->botRight = aux2;
                        
                    prevAux = prevAux->right;

                    aux2->topRight = prevAux;                
                    prevAux->botLeft = aux2;                   
                    
                }
                else
                {
                    aux2->topLeft = prevAux;
                    prevAux->botRight = aux2;
                    
                    if(prevAux->right != NULL)
                    {
                        prevAux = prevAux->right;

                        aux2->topRight = prevAux;
                        prevAux->botLeft = aux2;
                    }
                }
            }
        }
        
        row++;
        if(row <= 5)
        {
            Tile* newRowTile = new Tile();

            if(row > 3)
            {   
                newRowTile->topLeft = aux;
                aux->botRight = newRowTile;

                newRowTile->topRight = aux->right;
                aux->right->botLeft = newRowTile;
                
                prevAux = aux->right;
                colum--;
            }
            else
            {
                newRowTile->topRight = aux;
                aux->botLeft = newRowTile;
                
                prevAux = aux;
                colum++;
            }
            
            aux = newRowTile;
        }
        else break;
    }
}

void MapCatan::setValues(vector<int> numbers, vector<string> types)
{       
    Tile* aux = root;
    Tile* aux2 = root;

    for(int i = 0; i < numbers.size(); i++)
    {
        aux2->number = numbers[i];
        aux2->type = types[i];

        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            aux2 = aux;
        }
    }
}

int MapCatan::getResult()
{
    const int req1 = 1;
    const int req2 = 5;
    const int req3 = 1;

    int value = verifyProb() * req2;

    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        value += verifyAdjTile(aux2) * req1;
        value += verifyAdjNumber(aux2) * req3; 

        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            else break;
            aux2 = aux;
        }
    }

    return value;
}

//REQ1

int MapCatan::verifyAdjTile(Tile* tile)
{
    if(tile->right    != NULL  &&  tile->right->type    == tile->type) return 1;
    if(tile->left     != NULL  &&  tile->left->type     == tile->type) return 1;
    if(tile->topRight != NULL  &&  tile->topRight->type == tile->type) return 1;
    if(tile->topLeft  != NULL  &&  tile->topLeft->type  == tile->type) return 1;
    if(tile->botRight != NULL  &&  tile->botRight->type == tile->type) return 1;
    if(tile->botLeft  != NULL  &&  tile->botLeft->type  == tile->type) return 1;
    return 0;
}

// REQ2

int MapCatan::verifyProb()
{
    float probGrain = 0.0;
    float probLumber = 0.0;
    float probWool = 0.0;
    float probBrick = 0.0;
    float probOre = 0.0;

    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        float prob = calcProb(aux2->number);
        if(aux2->type == "G") probGrain += prob;
        if(aux2->type == "L") probLumber += prob;
        if(aux2->type == "W") probWool += prob;
        if(aux2->type == "B") probBrick += prob;
        if(aux2->type == "O") probOre += prob;

        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            else break;
            aux2 = aux;
        }
    }

    if((probGrain - probLumber < 1) && (probGrain - probLumber > -1) // Group 1
        && (probGrain - probWool < 1) && (probGrain - probWool > -1)
        && (probWool - probLumber < 1) && (probWool - probLumber > -1)

        && (probOre - probBrick) < 1 && (probOre - probBrick > -1)) // Group 2
            return 0;
    return 1;
        

}

float MapCatan::calcProb(int i){
    if(i == 2 || i == 12) return 1/36;  // ~2,8%
    if(i == 3 || i == 11) return 2/36;  // ~5,6%
    if(i == 4 || i == 10) return 3/36;  // ~8,3%
    if(i == 5 || i == 9)  return 4/36;  // ~11,1%
    if(i == 6 || i == 8)  return 5/36;  // ~13,9%
    return 0;
}

//REQ3

int MapCatan::verifyAdjNumber(Tile* tile)
{
    
    if(tile->number == 6 || tile->number == 8){
        if(tile->right != NULL    && (tile->right->number == 6    || tile->right->number == 8))    return 1;
        if(tile->left != NULL     && (tile->left->number == 6     || tile->left->number == 8))     return 1;
        if(tile->topRight != NULL && (tile->topRight->number == 6 || tile->topRight->number == 8)) return 1;
        if(tile->topLeft != NULL  && (tile->topLeft->number == 6  || tile->topLeft->number == 8))  return 1;
        if(tile->botRight != NULL && (tile->botRight->number == 6 || tile->botRight->number == 8)) return 1;
        if(tile->botLeft != NULL  && (tile->botLeft->number == 6  || tile->botLeft->number == 8))  return 1;
    }
    return 0;
}

void MapCatan::printTypes()
{
    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        cout << aux2->type << ' ';
            
        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            cout << '\n';
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            else break;
            aux2 = aux;
        }
    }
}

void MapCatan::printNumbers()
{
    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        cout << aux2->number << ' ';
            
        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            cout << '\n';
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            else break;
            aux2 = aux;
        }
    }
}

void MapCatan::printMap()
{
    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        cout << "[" << aux2->number << ";" << aux2->type << "]";

        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {
            cout << '\n';
            if(aux->botLeft != NULL)
            {
                aux = aux->botLeft;
            }
            else if(aux->botRight != NULL)
            {
                aux = aux->botRight;
            }
            else break;
            aux2 = aux;
        }
    }
}