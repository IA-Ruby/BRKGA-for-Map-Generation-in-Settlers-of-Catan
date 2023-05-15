#include "../header/mapTM.h"

MapTM::MapTM()
{
    Tile* aux = root;
    Tile* prevAux = root;
    
    int row = 1;
    int colum = 13;

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
                if(row%2 == 0)
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
        if(row <= 9)
        {
            Tile* newRowTile = new Tile();

            if(row%2 == 0)
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

void MapTM::setValues(vector<int> types)
{       
    Tile* aux = root;
    Tile* aux2 = root;

    for(int i = 0; i < types.size(); i++)
    {
        aux2->type = types[i];
        aux2->viwed = false;

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

int MapTM::getResult()
{
    int value = verifyRiver()*2;

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

    return value/2;
}

int MapTM::verify(Tile* tile)
{
    int count = 0;
    if(tile->type != 8)
    {
        if( tile->right    != NULL  &&  tile->right->type    == tile->type) count++;
        if( tile->left     != NULL  &&  tile->left->type     == tile->type) count++;
        if( tile->topRight != NULL  &&  tile->topRight->type == tile->type) count++;
        if( tile->topLeft  != NULL  &&  tile->topLeft->type  == tile->type) count++;
        if( tile->botRight != NULL  &&  tile->botRight->type == tile->type) count++;
        if( tile->botLeft  != NULL  &&  tile->botLeft->type  == tile->type) count++;
    }
    else
    {
        int adjRiver = 0;
        if( tile->right    != NULL && tile->right->type    == tile->type) adjRiver++;
        if( tile->left     != NULL && tile->left->type     == tile->type) adjRiver++;
        if( tile->topRight != NULL && tile->topRight->type == tile->type) adjRiver++;
        if( tile->topLeft  != NULL && tile->topLeft->type  == tile->type) adjRiver++;
        if( tile->botRight != NULL && tile->botRight->type == tile->type) adjRiver++;
        if( tile->botLeft  != NULL && tile->botLeft->type  == tile->type) adjRiver++;
        if( adjRiver == 0 || adjRiver > 3) count += 2;
    }
    return count;
}

int MapTM::verifyRiver()
{
    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        if(aux2->type == 8)
        {
            int count = 1;
            aux2->viwed = true;
                
            if( aux2->right != NULL && aux2->right->type == 8 && aux2->right->viwed == false)
                count += verifyRiverTile(aux2->right);

            if( aux2->left != NULL && aux2->left->type == 8 && aux2->left->viwed == false) 
                count += verifyRiverTile(aux2->left);
            
            if( aux2->topRight != NULL && aux2->topRight->type == 8 && aux2->topRight->viwed == false) 
                count += verifyRiverTile(aux2->topRight);

            if( aux2->topLeft != NULL && aux2->topLeft->type == 8 && aux2->topLeft->viwed == false) 
                count += verifyRiverTile(aux2->topLeft);

            if( aux2->botRight != NULL && aux2->botRight->type == 8 && aux2->botRight->viwed == false) 
                count += verifyRiverTile(aux2->botRight);

            if( aux2->botLeft != NULL && aux2->botLeft->type == 8 && aux2->botLeft->viwed == false) 
                count += verifyRiverTile(aux2->botLeft);
            
            if(count == 36) return 0;
            return 20; 
        }

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
}

int MapTM::verifyRiverTile(Tile* tile)
{
    tile->viwed = true;
    int aux = 1;

    if( tile->right != NULL && tile->right->type == 8 && tile->right->viwed == false)
        aux += verifyRiverTile(tile->right);

    if( tile->left != NULL && tile->left->type == 8 && tile->left->viwed == false) 
        aux += verifyRiverTile(tile->left);
    
    if( tile->topRight != NULL && tile->topRight->type == 8 && tile->topRight->viwed == false) 
        aux += verifyRiverTile(tile->topRight);

    if( tile->topLeft != NULL && tile->topLeft->type == 8 && tile->topLeft->viwed == false) 
        aux += verifyRiverTile(tile->topLeft);

    if( tile->botRight != NULL && tile->botRight->type == 8 && tile->botRight->viwed == false) 
        aux += verifyRiverTile(tile->botRight);

    if( tile->botLeft != NULL && tile->botLeft->type == 8 && tile->botLeft->viwed == false) 
        aux += verifyRiverTile(tile->botLeft);

    return aux;
}