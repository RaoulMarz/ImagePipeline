/* 
 * File:   shapegeometry.h
 * Author: raoul
 *
 * Created on February 18, 2018, 2:06 PM
 */

#ifndef SHAPEGEOMETRY_H
#define SHAPEGEOMETRY_H

#include <string>
#include <vector>
#include "coordinate.h"
#include "graphicstypes.h"

namespace userinterface {

class shapegeometry {
public:
    shapegeometry();
    shapegeometry(const shapegeometry& orig);
    virtual ~shapegeometry();
    
    void setshape(CAIRO_SHAPE_CATEGORY shapedesc);
    void setcutoutborder(std::vector<coordinate<double>> & plotpoints); //vector of coordinate specifying a polygon that will use as clip border (cut-out)
private:
    CAIRO_SHAPE_CATEGORY shapetype;
};

#endif /* SHAPEGEOMETRY_H */

}
