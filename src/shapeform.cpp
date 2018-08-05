/* 
 * File:   shapeform.cpp
 * Author: raoul
 * 
 * Created on February 24, 2018, 9:56 PM
 */

#include "shapeform.h"
#include <sstream>

namespace userinterface {

shapeform::shapeform() {
}

shapeform::shapeform(const shapeform& orig) {
}

shapeform::~shapeform() {
}

string shapeform::print() {
    std::ostringstream ss;
    ss << x;
    ss << y;
    ss << extentDimension.print();
    return ss.str();
}

}

