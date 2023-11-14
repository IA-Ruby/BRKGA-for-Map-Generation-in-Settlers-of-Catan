#ifndef MAPTM_H
#define MAPTM_H

#include <iostream>
#include <vector>

using namespace std;

class MapTM
{
    private:
        struct Tile{
            int type;
            bool viwed;
            struct Tile* right;
            struct Tile* left;
            struct Tile* topRight;
            struct Tile* topLeft;
            struct Tile* botRight; 
            struct Tile* botLeft;
            Tile()
            {
                type = 0;
                viwed = false;
                right = NULL;
                left = NULL;
                topRight = NULL;
                topLeft = NULL;
                botRight = NULL;
                botLeft = NULL;
            }
        };
        Tile* root = new Tile();
        int verifyAdj(Tile* tile);
        int verifyRiver();
        int verifyRiverTile(Tile* tile);
        int verifyAdjRiver(Tile* tile);
        int verifyTerraforming(Tile* tile);
        int verifyTerraformingTiles(Tile* tile, int a, int b);

    public:
        MapTM();
        void setValues(vector<int> types);
        int getResult();
        void printMap();
};

#endif