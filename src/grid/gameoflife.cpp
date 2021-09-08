#include "grid.h"
#include "stdio.h"
#define pop_front(v) if(!v.empty())v.erase(v.begin());

int getNebiourCount(int x, int y, PixelArray pixels) {
    int count = 0;

    vector<PositionOffset> directions = {
        //cardinal directions
        { -1, 0 },
        { 1, 0 },
        { 0, -1 },
        { 0, 1 },

        //subcardinal directions
        { -1, -1 },
        { 1, -1 },
        { -1, 1 },
        { 1, 1 }
    };

    //loop thru all directions to check
    for (int i=0; i < directions.size(); i++) {
        //check if direction is out of bounds
        if (y + directions[i].y >= 0 && y + directions[i].y <= pixels.size()-1 
            && x + directions[i].x >= 0 && x + directions[i].x <= pixels[0].size()-1) 
        {   
            //if not out of bounds check neibour
            if ( pixels[y + directions[i].y][x + directions[i].x].activated ) {
                //if neibour is actrivated then count 
                count++;

            }
        }
    }
    
    return count;
}

void Grid::AddUndoState() {
    auto& prevStates = Grid::previousStates;

    auto size = Grid::previousStates.size();

    if (size >= Grid::maxUndoFrames) pop_front(previousStates);

    previousStates.push_back(Grid::pixels);
}

void Grid::Undo() {
    if (Grid::previousStates.size() > 0) {
        Grid::pixels = Grid::previousStates.back();
        Grid::previousStates.pop_back();
    }
}

void Grid::GameOfLife() {
    Grid::AddUndoState();
    //create snapshot of pixels
    PixelArray temp = Grid::pixels;

    for (int h=0; h < Grid::pixels.size(); h++) {
        for (int w=0; w < Grid::pixels[h].size(); w++) {

            //get neibour count
            auto count = getNebiourCount(w, h, Grid::pixels);
                

            //if less than 2 neibours then die
            if (count < 2) {
                temp[h][w].activated = false;
            } 
                
            //overpopulation
            if (count > 3) {
                temp[h][w].activated = false;
            }

            //if enough surrounding neibours then aciivate
            if (!Grid::pixels[h][w].activated && count > 2 && count <= 3) {
                temp[h][w].activated = true;
            }

        }
    }

    //apply snapshot
    Grid::pixels = temp;
}