#include "gridColorPicker.h"

gridColorPicker::gridColorPicker(HSLAPixel gridColor, int gridSpacing)
{
    color = gridColor;
    spacing = gridSpacing;
}

HSLAPixel gridColorPicker::operator()(int x, int y)
{
    /**
     * @todo your code here!
     * HINT: manipulate y = mx + b
     */

    HSLAPixel ret;
    int a = y - x;
    int b = y + x;
    bool isGrid = a%spacing == 0 || b%spacing == 0;
    if(isGrid) {
        ret = color;
    } else {
        ret = HSLAPixel(0,0,1);
    }

    return ret;
}
