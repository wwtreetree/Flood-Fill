/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"
using namespace std;

/**
 * STRIPE is given as an example
*/
animation filler::fillStripeDFS(PNG &img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq) {
    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, scp, tolerance, frameFreq);
}

animation filler::fillStripeBFS(PNG &img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq) {
    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, scp, tolerance, frameFreq);
}

/**
 * @todo your turn!
 */
// x, y is starting point
animation filler::fillBorderDFS(PNG &img, int x, int y,
                                HSLAPixel borderColor, double tolerance, int frameFreq) {
    HSLAPixel p = *(img.getPixel(x, y));
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, p);
    return fill<Stack>(img, x, y, bcp, tolerance, frameFreq);

}

animation filler::fillBorderBFS(PNG &img, int x, int y,
                                HSLAPixel borderColor, double tolerance, int frameFreq) {
    HSLAPixel p = *(img.getPixel(x, y));
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, p);
    return fill<Queue>(img, x, y, bcp, tolerance, frameFreq);
}

/* Given implementation of a DFS conwa fill. */
animation filler::fillConwayDFS(PNG &img, int x, int y, double tolerance, int frameFreq) {
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Stack>(img, x, y, ccp, tolerance, frameFreq);
}

/* Given implementation of a BFS conwa fill. */
animation filler::fillConwayBFS(PNG &img, int x, int y, double tolerance, int frameFreq) {
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Queue>(img, x, y, ccp, tolerance, frameFreq);
}


animation filler::fillGridDFS(PNG &img, int x, int y, HSLAPixel fillColor,
                              int spacing, double tolerance, int frameFreq) {
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Stack>(img, x, y, gcp, tolerance, frameFreq);
}

animation filler::fillGridBFS(PNG &img, int x, int y, HSLAPixel fillColor,
                              int spacing, double tolerance, int frameFreq) {
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Queue>(img, x, y, gcp, tolerance, frameFreq);
}


template<template<class T> class OrderingStructure>
animation filler::fill(PNG &img, int x, int y, colorPicker &fillColor,
                       double tolerance, int frameFreq) {
    /**
     * @todo Your code here! 
     * NOTE: this'll be a long one!
     */

    animation g;
    //g.addFrame(img);
    int timesAdded = 0;
    int width = img.width();
    int height = img.height();
    bool visited[width][height];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            visited[i][j] = false;
        }
    }


//    To begin the algorithm, you simply place the
//    * given point in the ordering structure, marking it processed
//    * (the way you mark it is a design decision you'll make yourself).
//                                                   * We have a choice to either change the color, if appropriate, when we
//    * add the point to the OS, or when we take it off. In our test cases,
//    * we have assumed that you will change the color when a point is REMOVED
//    * from the structure.
    HSLAPixel ctrPixel = *(img.getPixel(x,y));
    OrderingStructure<std::pair<int, int>> os;
    os.add(std::pair<int, int>(x, y));
    visited[x][y] = true;

//    * Until the structure is empty, you do the following:
//    *
//            * 1.     Remove a point from the ordering structure, and then...
//    *
//            *        1.    add its unprocessed neighbors whose color values are
//    *              within (or equal to) tolerance distance from the center,
//    *              to the ordering structure, marking each as processed.
//    *        2.    use the colorPicker to set the new color of the point.
//     *        3.    if it is an appropriate frame, send the current PNG to the
//    *              animation (as described below).
//    *        4.    if it is an appropriate frame, send the current PNG to the
//    *              animation (as described below).
//    *

    while (!os.isEmpty()) {
        std::pair<int,int> removeOne = os.remove();
        //HSLAPixel removeOnePixel = *(img.getPixel(removeOne.first,removeOne.second));
        //>>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
        if (removeOne.second+1 < img.height()) {  //not equal
            HSLAPixel south = *(img.getPixel(removeOne.first, removeOne.second+1));
            if (visited[removeOne.first][removeOne.second+ 1] == false && south.dist(ctrPixel) <= tolerance) {
                os.add(pair<int,int>(removeOne.first,removeOne.second+1));
                visited[removeOne.first][removeOne.second+1] =true;
            }
        }

        if (removeOne.first+1 < img.width()) {  //not equal
            HSLAPixel east = *(img.getPixel(removeOne.first+1, removeOne.second));
            if (visited[removeOne.first+1][removeOne.second] == false && east.dist(ctrPixel) <= tolerance) {
                os.add(pair<int,int>(removeOne.first+1,removeOne.second));
                visited[removeOne.first+1][removeOne.second] =true;
            }
        }

        if (removeOne.second-1 >= 0) {  //not equal
            HSLAPixel north = *(img.getPixel(removeOne.first, removeOne.second-1));
            if (visited[removeOne.first][removeOne.second-1] == false && north.dist(ctrPixel) <= tolerance) {
                os.add(pair<int,int>(removeOne.first,removeOne.second-1));
                visited[removeOne.first][removeOne.second-1] =true;
            }
        }
        if (removeOne.first-1 >= 0) {  //not equal
            HSLAPixel west = *(img.getPixel(removeOne.first-1, removeOne.second));
            if (visited[removeOne.first-1][removeOne.second] == false && west.dist(ctrPixel) <= tolerance) {
                os.add(pair<int,int>(removeOne.first-1,removeOne.second));
                visited[removeOne.first-1][removeOne.second] =true;
            }
        }
        *(img.getPixel(removeOne.first,removeOne.second))=fillColor(removeOne.first,removeOne.second);

        timesAdded++;
        if (timesAdded==frameFreq) {
            g.addFrame(img);
            timesAdded=0;
        }
    }

    if (timesAdded != 0) {
        g.addFrame(img);
    }
    return g;
}

/** FOR ABOVE fill
 * @todo You need to implement this function!
 *
 * This is the basic description of a flood-fill algorithm: Every fill
 * algorithm requires an ordering structure, which is passed to this
 * function via its template parameter. For a breadth-first-search
 * fill, that structure is a QUEUE, for a depth-first-search, that
 * structure is a STACK.
 * To begin the algorithm, you simply place the
 * given point in the ordering structure, marking it processed
 * (the way you mark it is a design decision you'll make yourself).
 * We have a choice to either change the color, if appropriate, when we
 * add the point to the OS, or when we take it off. In our test cases,
 * we have assumed that you will change the color when a point is REMOVED
 * from the structure.
 *
 * Until the structure is empty, you do the following:
 *
 * 1.     Remove a point from the ordering structure, and then...
 *
 *        1.    add its unprocessed neighbors whose color values are
 *              within (or equal to) tolerance distance from the center,
 *              to the ordering structure, marking each as processed.
 *        2.    use the colorPicker to set the new color of the point.
 *        3.    if it is an appropriate frame, send the current PNG to the
 *              animation (as described below).
 *        4.    if it is an appropriate frame, send the current PNG to the
 *              animation (as described below).
 *
 * 2.     When implementing your breadth-first-search and
 *        depth-first-search fills, you will need to explore neighboring
 *        pixels in some order.
 *
 *        For this assignment, each pixel p has 4 neighbors, consisting of
 *        the 4 pixels who share an edge or corner with p. (We leave it to
 *        you to describe those 4 pixel locations, relative to the location
 *        of p.)
 *
 *        While the order in which you examine neighbors does not matter
 *        for a proper fill, you must use the same order as we do for
 *        your animations to come out like ours!
 *
 *        The order you should put
 *        neighboring pixels **ONTO** the ordering structure (queue or stack)
 *        is as follows:
 *          >>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
 *
 *        If you do them in a different order, your fill may
 *        still work correctly, but your animations will be different
 *        from the grading scripts!
 *
 *        IMPORTANT NOTE: *UP*
 *        here means towards the top of the image, so since an image has
 *        smaller y coordinates at the top, this is in the *negative y*
 *        direction. Similarly, *DOWN* means in the *positive y*
 *        direction.
 *
 * 3.     For every k pixels filled, **starting at the kth pixel**, you
 *        must add a frame to the animation, where k = frameFreq.
 *
 *        For example, if frameFreq is 4, then after the 4th pixel has
 *        been filled you should add a frame to the animation, then again
 *        after the 8th pixel, etc.  You must only add frames for the
 *        number of pixels that have been filled, not the number that
 *        have been checked. So if frameFreq is set to 1, a pixel should
 *        be filled every frame.
 * 4.     Finally, as you leave the function, send one last frame to the
 *        animation. This frame will be the final result of the fill, and
 *        it will be the one we test against.
 */