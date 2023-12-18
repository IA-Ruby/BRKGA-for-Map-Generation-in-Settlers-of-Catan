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
    const int req1 = 1;
    const int req2 = 1;
    const int req3 = 100;
    const int req4 = 1;
    
    int value = verifyRiver() * req3;

    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        if(aux2->type == 8)
        {
            value += (verifyAdjRiver(aux2) * req2);
        } 
        else
        {
            value += (verifyAdj(aux2) * req1);
            value += (verifyTerraforming(aux2) * req4);
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

    return value;
}

// REQ1

int MapTM::verifyAdj(Tile* tile)
{
    if( tile->right    != NULL  &&  tile->right->type    == tile->type) return 1; 
    if( tile->left     != NULL  &&  tile->left->type     == tile->type) return 1;
    if( tile->topRight != NULL  &&  tile->topRight->type == tile->type) return 1;
    if( tile->topLeft  != NULL  &&  tile->topLeft->type  == tile->type) return 1;
    if( tile->botRight != NULL  &&  tile->botRight->type == tile->type) return 1;
    if( tile->botLeft  != NULL  &&  tile->botLeft->type  == tile->type) return 1;
    return 0;
}

// REQ2

int MapTM::verifyRiver()
{
    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        if(aux2->type == 8)
        {
            int count = verifyRiverTile(aux2);
            if(count == 36) return 0;
            return 1; 
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
    return 0;
}

int MapTM::verifyRiverTile(Tile* tile)
{
    tile->viwed = true;
    int count = 1;

    if( tile->right != NULL && tile->right->type == 8 && tile->right->viwed == false)
        count += verifyRiverTile(tile->right);

    if( tile->left != NULL && tile->left->type == 8 && tile->left->viwed == false) 
        count += verifyRiverTile(tile->left);
    
    if( tile->topRight != NULL && tile->topRight->type == 8 && tile->topRight->viwed == false) 
        count += verifyRiverTile(tile->topRight);

    if( tile->topLeft != NULL && tile->topLeft->type == 8 && tile->topLeft->viwed == false) 
        count += verifyRiverTile(tile->topLeft);

    if( tile->botRight != NULL && tile->botRight->type == 8 && tile->botRight->viwed == false) 
        count += verifyRiverTile(tile->botRight);

    if( tile->botLeft != NULL && tile->botLeft->type == 8 && tile->botLeft->viwed == false) 
        count += verifyRiverTile(tile->botLeft);

    return count;
}

// REQ3

int MapTM::verifyAdjRiver(Tile* tile)
{
    int adjRiver = 0;
    if( tile->right    != NULL && tile->right->type    == 8) adjRiver++;
    if( tile->left     != NULL && tile->left->type     == 8) adjRiver++;
    if( tile->topRight != NULL && tile->topRight->type == 8) adjRiver++;
    if( tile->topLeft  != NULL && tile->topLeft->type  == 8) adjRiver++;
    if( tile->botRight != NULL && tile->botRight->type == 8) adjRiver++;
    if( tile->botLeft  != NULL && tile->botLeft->type  == 8) adjRiver++;
    if( adjRiver == 0 || adjRiver > 3) return 1;
    return 0;
}

// REQ4

int MapTM::verifyTerraforming(Tile* tile)
{
    int type = tile->type;
    
    if(type == 8) printf("%d", type);
    switch(type){
        case 1: return verifyTerraformingTiles(tile, 2, 7);
        case 2 ... 6: return verifyTerraformingTiles(tile, type-1, type+1);
        case 7: return verifyTerraformingTiles(tile, 6, 1);
    }
    return 0;
}

int MapTM::verifyTerraformingTiles(Tile* tile, int a, int b)
{
    if( tile->right != NULL     && (tile->right->type    == a  ||  tile->right->type    == b)) return 0;
    if( tile->left != NULL      && (tile->left->type     == a  ||  tile->left->type     == b)) return 0;
    if( tile->topRight != NULL  && (tile->topRight->type == a  ||  tile->topRight->type == b)) return 0;
    if( tile->topLeft != NULL   && (tile->topLeft->type  == a  ||  tile->topLeft->type  == b)) return 0;
    if( tile->botRight != NULL  && (tile->botRight->type == a  ||  tile->botRight->type == b)) return 0;
    if( tile->botLeft != NULL   && (tile->botLeft->type  == a  ||  tile->botLeft->type  == b)) return 0;
    return 1;
}

void MapTM::printMap()
{
    int space = true;

    Tile* aux = root;
    Tile* aux2 = root;

    while(true)
    {
        if(aux2->type == 8)
        {
            cout << " * ";
        } 
        else
        {
            cout << "[" << aux2->type << "]";
        }

        if(aux2->right != NULL)
        { 
            aux2 = aux2->right;
        }
        else
        {   
            cout << "\n";
            if(space) cout << "  ";
            space = !space;

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

