/* 
 * File:   imagescrollpanel.cpp
 * Author: raoul
 * 
 * Created on April 15, 2017, 10:49 PM
 */
#include "imagelist.h"
#include "dimension.h"
#include "imagescrollpanel.h"

using namespace std;

namespace userinterface {
    
imagescrollpanel::imagescrollpanel(cairo_t *cr) {
    imagebackstore = std::make_unique<imagelist>();
}

imagescrollpanel::imagescrollpanel(const imagescrollpanel& orig) {
    imagebackstore = std::make_unique<imagelist>();
}

imagescrollpanel::imagescrollpanel(cairo_t *cr, int maxitems) {
    maxsize = maxitems;
}

imagescrollpanel::imagescrollpanel(cairo_t *cr, int maxitems, imagelist* imageitems) {
    maxsize = maxitems;
}

imagescrollpanel::~imagescrollpanel() {
}

/* Returns a vector with all the images that are visible in the current view */
optional<std::vector<string>> imagescrollpanel::getVisibleInViewArea() {
    optional<std::vector<string>> res = optional<std::vector<string>> {};
    std::vector<string> resultVisibleImages;
    res = optional<std::vector<string>> { resultVisibleImages };
    return res;
}

void imagescrollpanel::render() {
        
}

void imagescrollpanel::setdimensions(dimension<int> panelarea) {
    panelareaDimension = panelarea;
}

void imagescrollpanel::setpadding(padding itempadding) {
    
}

void imagescrollpanel::setscrollbaroptions(bool showscroll, BOX_ANCHOR_DIRECTION boxanchor, int width) {
    
}

}
