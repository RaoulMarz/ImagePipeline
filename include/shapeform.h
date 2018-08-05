/* 
 * File:   shapeform.h
 * Author: raoul
 *
 * Created on February 24, 2018, 9:56 PM
 */

#ifndef SHAPEFORM_H
#define SHAPEFORM_H

#include "dimension.h"

enum class SHAPE_BASICFORM : std::int8_t { SHAPE_BASICFORM_NONE = 0, SHAPE_BASICFORM_CIRCLE, SHAPE_BASICFORM__OVAL, SHAPE_BASICFORM_RECTANGLE, SHAPE_BASICFORM_TRIANGLE };

namespace userinterface {
    
class shapeform {
public:
    shapeform();
    shapeform(const shapeform& orig);
    virtual ~shapeform();
    
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void setX(int newx) { x = newx; }
    inline void setY(int newy) { y = newy; }
    string print();
private:
    SHAPE_BASICFORM objBasicShape;
    
    int x;
    int y;
    dimension<int> extentDimension;
};

}
#endif /* SHAPEFORM_H */

