#include "borderColorPicker.h"


/**
     * Constructs a new borderColorPicker.
     *
     * @param fillColor Color for the border .
     * @param tolerance used to determine the border of the fill.
     * @param center the color used to determine whether or not a point is within
     *          the fill region.
     */
borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance, HSLAPixel center)
{   color = fillColor;
   im = img;
   tol = tolerance;
   ctr = center;
}

/**
    * Picks the color for pixel (x, y). If the x or y coordinate is
    * near the border of the fill, or the border of the image,
    * the fillColor will be returned.
    * Otherwise, the current color of (x,y) will be returned.
    *
    * @param x The x coordinate to pick a color for.
    * @param y The y coordinat to pick a color for.
    * @return The color chosen for (x, y).
    */
HSLAPixel borderColorPicker::operator()(int x, int y) {
    HSLAPixel pixel = *(im.getPixel(x, y));

    /* your code here */
//
//    if (x >= im.width() || y >= im.height())
//        return pixel;
//
//    if ((x >= im.width() - 3) || (x < 3) || (y >= im.height() - 3) || (y < 3))
//        return color;
//
//    for (unsigned int horz = (x - 3); horz <= (x + 3); horz++) {
//        for (unsigned int vert = (y - 3); vert <= (y + 3); vert++) {
//            HSLAPixel *p = im.getPixel(x, y);
//            unsigned int sqdist = ((horz - x) * (horz - x) + (vert - y) * (vert - y));
//            if (p->dist(ctr) > tol && sqdist <= 3 * 3) return color;
//        }
//    }
//    return pixel;



     for(int i = x-3; i<= x+3; i++) {
         for (int j = y-3; j<=y+3; j++) {
             int dx = i-x;
             int dy = y-j;
             if ((dx*dx)+(dy*dy)>9) {
                 continue;
             }
             if(i<0 || i>=im.width() || j<0 || j>= im.height()) {
                 return color;
             }
             if(im.getPixel(i,j)->dist(ctr) > tol) {
                 return color;
             }
         }
     }
     return *im.getPixel(x,y);
}









