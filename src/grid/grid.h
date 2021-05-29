#include "../include/raylib.h"
#include "stdlib.h"
#include "list"
#include "vector"

const int pixSize = 31;

typedef struct {
    bool activated;
    int posX;
    int posY;
} Pixel;

using namespace std;

typedef vector<vector<Pixel>> PixelArray;

typedef struct {
    int x;
    int y;
} PositionOffset;

class Grid {
    private:
        //outer list is row, inner is colum
        PixelArray pixels;
    public:
        Grid(int screenWidth, int screenHeight);
        void DrawGrid();
        void UpdateGrid();
        void GameOfLife();
        void ResetGrid();
        void ExportGrid(int slot);
        void LoadGrid(int slot);
};