#include "grid.h"
#include "../include/raylib.h"

using namespace std;

Grid::Grid(int screenWidth, int screenHeight) {
    //loop thru rows
    for (int h=0; h < screenHeight; h++) {
        //make a list of Pixels
        vector<Pixel> tempixels;
        
        //loop thru width
        for (int w=0; w < screenWidth; w++) {

            //if it is time to make square then make one
            if (w % pixSize == 0 && h % pixSize == 0) {
                // add pixel to row
                tempixels.push_back((Pixel) {
                    false,
                    w,
                    h
                });
            }
        }

        //if boxes were added then append them to the main array
        if (tempixels.size() != 0) Grid::pixels.push_back(tempixels);
    }
}

void Grid::DrawGrid() {
    Color on = GetColor(0x404040);
    Color off = LIGHTGRAY;

    for ( int h=0; h < Grid::pixels.size(); h++ ) {
        for (int w=0; w < Grid::pixels[h].size(); w++) {
            if (Grid::pixels[h][w].activated) {
                DrawRectangle(Grid::pixels[h][w].posX, Grid::pixels[h][w].posY, pixSize-2, pixSize-2, off);
            } else {
                DrawRectangle(Grid::pixels[h][w].posX, Grid::pixels[h][w].posY, pixSize-2, pixSize-2, on);
            }
        }
    }
}

void Grid::UpdateGrid() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        //calculate width and height of box
        Vector2 mousepos = GetMousePosition();

        //calculate the postions
        int x = (int)mousepos.x / pixSize;
        int y = (int)mousepos.y / pixSize;

        //invert the color
        Grid::pixels[y][x].activated = !Grid::pixels[y][x].activated;
    }

    //actual game of life code
    if (IsKeyPressed(KEY_SPACE)) {
        Grid::GameOfLife();
    }
}

void Grid::ResetGrid() {
    for (int h=0; h < Grid::pixels.size(); h++) {
        for (int w=0; w < Grid::pixels[h].size(); w++) {
            Grid::pixels[h][w].activated = false;
        }
    }
}