#include "raylib.h"
#include "stdlib.h"
#include "list"
#include "vector"

const int pixSize = 19;

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

typedef struct {
    int x;
    int y;
} Point;


class Grid {
    private:
        //outer list is row, inner is colum
        PixelArray pixels;

        int maxUndoFrames = 100;

        Point lastMousePos = {0, 0};

        vector<PixelArray> previousStates;

        void AddUndoState();
        void Undo();
    public:
        Grid(int screenWidth, int screenHeight);
        void DrawGrid();
        void UpdateGrid();
        void GameOfLife();
        void ResetGrid();
        void ExportGrid(int slot);
        void LoadGrid(int slot);
};