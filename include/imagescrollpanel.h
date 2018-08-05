/* 
 * File:   imagescrollpanel.h
 * Author: raoul
 *
 * Created on April 15, 2017, 10:49 PM
 */

#ifndef IMAGESCROLLPANEL_H
#define IMAGESCROLLPANEL_H

#include <vector>
#include <string>
#include <pango/pango.h>
#include <cairo/cairo-ft.h>
#include "fwdstringlist.h"
#include "imagelist.h"
#include "dimension.h"
#include "padding.h"

using namespace std;

namespace userinterface {

class imagescrollpanel {
public:
    imagescrollpanel(cairo_t *cr);
    imagescrollpanel(const imagescrollpanel& orig);
    imagescrollpanel(cairo_t *cr, int maxitems);
    imagescrollpanel(cairo_t *cr, int maxitems, imagelist* imageitems);
    virtual ~imagescrollpanel();
    
    optional<std::vector<string>> getVisibleInViewArea();
    void render();
    void setdimensions(dimension<int> panelarea);
    void setpadding(padding itempadding);
    void setscrollbaroptions(bool showscroll, BOX_ANCHOR_DIRECTION boxanchor, int width);
    void setdiscretetruncate(bool discreteview); //Only shows image if it can be full displayed
private:
    std::unique_ptr<imagelist> imagebackstore;
    fwdstringlist visibleImages;
    int maxsize = -1;
    dimension<int> panelareaDimension;
    padding border_padding;
    bool scrollbar_visible = false;
    bool truncate_partialvisible = false; //Truncate (do not display) an image if it would not be fully displayed
};

#endif /* IMAGESCROLLPANEL_H */

}

