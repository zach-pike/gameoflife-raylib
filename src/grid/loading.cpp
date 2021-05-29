#include "grid.h"
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "fstream"
#include "rapidjson/document.h"

using namespace std;

void Grid::ExportGrid(int slot) {
    string filepath = "saves/" + to_string(slot) + ".json";

    FILE* fp = fopen(filepath.c_str(), "w");
    printf("exporting slot %d\n", slot);

    //start main json string
    string text = "[\n";

    //loop thru rows
    for (int h=0; h < Grid::pixels.size(); h++) {
        
        //start row string
        string row = "\n\t[\n";

        //loop thru colums
        for(int w=0; w < Grid::pixels[h].size(); w++) {
            
            //add one or zero depending on if the pixel is on or off
            if (w == Grid::pixels[h].size()-1) {
                row.append( Grid::pixels[h][w].activated ? "\t\t1\n" : "\t\t0\n" );
            } else {
                row.append( Grid::pixels[h][w].activated ? "\t\t1,\n" : "\t\t0,\n" );
            }
            
        }

        //add comma after array
        if (h == Grid::pixels.size()-1) {
            row.append("\t]");
        } else {
            row.append("\t],");
        }
        
        //append row to text
        text.append(row);
    }

    //add ending bracket
    text.append("\n]");

    fputs(text.c_str(), fp);

    fclose(fp);
}

void Grid::LoadGrid(int slot) {

    printf("loading slot %d\n", slot);

    string filepath = "saves/" + to_string(slot) + ".json";

    //load file
    ifstream importfile(filepath.c_str());

    //return if file don't exist
    if (!importfile.is_open()) return;

    //load file contents to string
    string json((istreambuf_iterator<char>(importfile)), istreambuf_iterator<char>());

    //start using rapidjson
    using namespace rapidjson;

    //make a document
    Document d;

    //parse the loaded string
    d.Parse(json.c_str());

    //close the file as we no longer need it
    importfile.close();

    //iterate thru height
    for (int h=0; h < d.Size(); h++) {
        string rowName = to_string(h);

        //iterate thru rows
        for (int w=0; w < d[h].Size(); w++ ) {

            if (h < Grid::pixels.size() && w < Grid::pixels[h].size()) Grid::pixels[h][w].activated = d[h][w].GetInt() == 1 ? true : false;

        }
    }
}