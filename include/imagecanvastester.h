/* 
 * File:   imagecanvastester.h
 * Author: raoul
 *
 * Created on February 19, 2018, 10:27 PM
 */

#ifndef IMAGECANVASTESTER_H
#define IMAGECANVASTESTER_H

#include <unordered_map>
#include <boost/optional.hpp>
#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include "dimension.h"
#include "shapeform.h"
#include "graphicstypes.h"
#include "fwdstringlist.h"

using namespace userinterface;

enum class IMAGE_BACKEND : std::int8_t { IMAGE_BACKEND_NONE = 0, IMAGE_BACKEND_CAIRO , IMAGE_BACKEND_GDK };

class imagecanvastester : public Gtk::DrawingArea {
public:
    imagecanvastester();
    imagecanvastester(fwdstringlist& imageslist, gint refreshmillis);
    imagecanvastester(const imagecanvastester& orig);
    virtual ~imagecanvastester();
    
    bool pauseTimer(bool pause = true);    
    void initialise();
    void setimageslist(fwdstringlist& imageslist);
    void setrefreshperiod(gint refreshmillis);
    void setDrawSelection(DRAWING_AREA_SELECTION drawAreaType);
private:
    long drawcounter;
    int appwidth = 600;
    int appheight = 400;
    int charWidth;
    int charHeight;
    int columns = 80;
    int rows = 26;
    int textWinWidth, textWinHeight;
    gint refreshPeriod;
    dimension<double> defaultTextBoxSize;
    fwdstringlist imagesDisplay;
    std::unordered_map <std::string, Cairo::RefPtr<Cairo::ImageSurface>> mapImageToSurface;
    DRAWING_AREA_SELECTION myCanvasType;
    IMAGE_BACKEND flagImageBackend; 

    std::unique_ptr<vector<Cairo::RefPtr<Cairo::ImageSurface>>> renderImages;
    Gtk::Justification text_draw_justification;
    sigc::slot<bool> mydrawTimer_slot;
    sigc::connection* signalconnectionTimer;
    
    void drawImage(const Cairo::RefPtr<Cairo::Context>& cr, string filename, coordinate<double> topleft, dimension<double> imagebox = dimension<double>(0,0,0,0));
    void drawImage(const Cairo::RefPtr<Cairo::Context>& cr, string filename, coordinate<double> topleft, coordinate<double> scale, dimension<double> boundingbox, dimension<double> imagebox = dimension<double>(0,0,0,0));
    bool draw_imageslist(const Cairo::RefPtr<Cairo::Context>& cr);
    bool draw_shapes(const Cairo::RefPtr<Cairo::Context>& cr, vector<shapeform>* shapesList);
    bool draw_roundedrectangle(const Cairo::RefPtr<Cairo::Context>& cr, dimension<int> rectdim);
    bool draw_singleImage(const Cairo::RefPtr<Cairo::Context>& cr, string imagefile);
    bool image_exists(string filename);
    bool isEmptyDimension(dimension<double> dimensionvalue);
    bool isEmptyCoordinate(coordinate<double> coordinatevalue);
    optional<Cairo::RefPtr<Cairo::ImageSurface>> getMappedImageFile(string filename);
protected:
    int m_timer_number;
    
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_timeout(int timer_number);
};

#endif /* IMAGECANVASTESTER_H */

