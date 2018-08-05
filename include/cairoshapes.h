/* 
 * File:   cairoshapes.h
 * Author: raoul
 *
 * Created on February 18, 2018, 12:07 PM
 */

#ifndef CAIROSHAPES_H
#define CAIROSHAPES_H

#include "graphicstypes.h"
#include "shapegeometry.h"

namespace userinterface {

class cairoshapes {
public:
    cairoshapes();
    cairoshapes(const cairoshapes& orig);
    virtual ~cairoshapes();
private:
    void drawshape(CAIRO_SHAPE_CATEGORY shapedesc, shapegeometry thisgeometry);
    void setcolourscheme(std::string schemedescription);
    
    std::string colourscehemetext;
};

#endif /* CAIROSHAPES_H */
}

