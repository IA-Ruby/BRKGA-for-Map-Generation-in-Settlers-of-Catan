#ifndef MAPCATAN_H
#define MAPCATAN_H

#include <iostream>
#include <vector>

using namespace std;

class MapCatan
{
    private:
        struct Tile{
            int number;
            string type;
            struct Tile* right;
            struct Tile* left;
            struct Tile* topRight;
            struct Tile* topLeft;
            struct Tile* botRight; 
            struct Tile* botLeft;
            Tile()
            {
                number = 0;
                type = "";
                right = NULL;
                left = NULL;
                topRight = NULL;
                topLeft = NULL;
                botRight = NULL;
                botLeft = NULL;
            }
        };
        Tile* root = new Tile();
        int verify(Tile* tile);
    public:
        MapCatan();
        void setValues(vector<int> numbers, vector<string> types);
        int getResult();
        void printTypes();
        void printNumbers();
};

#endif