#include "conwayColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

conwayColorPicker::conwayColorPicker() : iter(0)
{
}
/**
 *  The function below returns either a black or a white HSLA pixels.
 *  The logic for determining whether a pixel is black or white is abstracted
 *  away in nextColor() which is given to you.
 * 
 *  However, nextColor() requires the number of WHITE pixels (representing dead cells)
 *  so your job here to figure out how to do an 8 point search around a pixel, eg
 *      NW  | North| NE
 *      West| (x,y)| East
 *      SW  | South| SE 
 *  All pixels around an initial (x,y) pixel
 * 
 *  HINT: in this filler, you will have to exploit and update the PNGmap field accordingly.
 *          it will also be useful if you look up the documentation for a C++ Map
 * 
 */
HSLAPixel conwayColorPicker::operator()(int x, int y)
{
    PNGmap::iterator stored;
    vector<PNGmap::iterator> neighbours;
    HSLAPixel deadCell = HSLAPixel(0, 0, 1, 1);
    unsigned int deadNeighbourCount = 0;

    for (int hor = x-1; hor <=x+1; hor++) {
        for (int vert = y-1; vert <=y+1; vert++) {
            if (hor == x && vert == y) continue;
            PNGmap::iterator one = prev.find(std::pair<int, int>(hor,vert));
            if (one == prev.end())  continue;

            else if (one->second == deadCell)
                deadNeighbourCount++;
        }
    }

    HSLAPixel ret = nextColor(deadNeighbourCount);
    std::pair<int, int> coord(x,y);
    std::pair<std::map<std::pair<int,int>,HSLAPixel>::iterator,bool> newret;
    newret=prev.insert(std::pair<std::pair<int, int>, HSLAPixel>(coord, ret));
    //update if check next time
    if (newret.second == false)   //already existed
        prev[coord] = ret;       //map use key to find value;

    return ret;
}


/**
 * GIVEN FUNCTION
 * 
 * for those interested, I did my best to mimic Conway's Game of Life in a colourpicker,
 * constrained to the 8 pixels and the propogating nature of a fill. See
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * 
 * John Horton Conway, am active mathematician in the fields of number theory, 
 * combinatorial game theory and coding theory, died recently of COVID 19 complications.
*/
HSLAPixel conwayColorPicker::nextColor(int deadNeighbourCount)
{
    // extra variables for readability
    HSLAPixel alive = HSLAPixel(0, 0, 0, 1); // black means alive, true to the game
    HSLAPixel dead = HSLAPixel(0, 0, 1, 1);  // white means alive, true to the game

    HSLAPixel ret = dead;

    if (deadNeighbourCount == 2) 
    {
        return alive;
    }

    if (deadNeighbourCount > 2)
    { // possibility of death by population if more than 3 neighbours
        if (iter % deadNeighbourCount == 0)
        { // chance to be alive decreases with deadNeighbourCount
            ret = alive;
        }
        else
        {
            ret = dead;
        }
    }
    iter++;
    return ret;
}