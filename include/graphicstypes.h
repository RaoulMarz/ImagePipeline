/* 
 * File:   graphicstypes.h
 * Author: raoul
 *
 * Created on February 18, 2018, 2:25 PM
 */

#ifndef GRAPHICSTYPES_H
#define GRAPHICSTYPES_H

#include <cstdint>

namespace userinterface {
    enum class CAIRO_SHAPE_CATEGORY : std::int8_t { CAIRO_SHAPE_NONE = 0, CAIRO_SHAPE_CIRCLE, CAIRO_SHAPE_OVAL, CAIRO_SHAPE_RECTANGLE };
    enum class PADDING_DIRECTION : std::int8_t { PADDING_NONE = 0, PADDING_LEFT };
    enum class DRAWING_AREA_SELECTION : std::int8_t { DRAWING_AREA_SHAPES = 0, DRAWING_AREA_VARIETY, DRAWING_AREA_IMAGEMISC, DRAWING_AREA_IMAGELIST, DRAWING_AREA_TEXTBOX};
    enum class BOX_ANCHOR_DIRECTION : std::int8_t { BOX_ANCHOR_NONE, BOX_ANCHOR_LEFT };
}

#endif /* GRAPHICSTYPES_H */

