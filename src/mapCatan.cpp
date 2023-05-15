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
    int value = 0;

    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        value += verify(aux2);
            
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

int MapCatan::verify(Tile* tile)
{
    int count = 0;
    if(tile->right    != NULL  &&  tile->right->type    == tile->type) count++;
    if(tile->left     != NULL  &&  tile->left->type     == tile->type) count++;
    if(tile->topRight != NULL  &&  tile->topRight->type == tile->type) count++;
    if(tile->topLeft  != NULL  &&  tile->topLeft->type  == tile->type) count++;
    if(tile->botRight != NULL  &&  tile->botRight->type == tile->type) count++;
    if(tile->botLeft  != NULL  &&  tile->botLeft->type  == tile->type) count++;

    if(tile->number == 6 || tile->number == 8)
    {
        if(tile->right != NULL    && (tile->right->number == 6    || tile->right->number == 8))    count++;
        if(tile->left != NULL     && (tile->left->number == 6     || tile->left->number == 8))     count++;
        if(tile->topRight != NULL && (tile->topRight->number == 6 || tile->topRight->number == 8)) count++;
        if(tile->topLeft != NULL  && (tile->topLeft->number == 6  || tile->topLeft->number == 8))  count++;
        if(tile->botRight != NULL && (tile->botRight->number == 6 || tile->botRight->number == 8)) count++;
        if(tile->botLeft != NULL  && (tile->botLeft->number == 6  || tile->botLeft->number == 8))  count++;
    }    

    return count;
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