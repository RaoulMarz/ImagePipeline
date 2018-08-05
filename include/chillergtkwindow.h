/* 
 * File:   chillergtkwindow.h
 * Author: raoul
 *
 * Created on August 29, 2015, 3:51 PM
 */

#ifndef BOIMGTKWINDOW_H
#define	BOIMGTKWINDOW_H

#include <gtkmm.h>
#include "dimension.h"
#include "graphicstypes.h"
#include "quickdrawvariety.h"
#include "imagecanvastester.h"

enum class DEMO_CANVAS_SELECTION : std::int8_t { DEMO_CANVAS_NONE = 0, DEMO_CANVAS_VARIETY, DEMO_CANVAS_IMAGES };

class chillergtkwindow : public Gtk::Window {
public:
    chillergtkwindow(userinterface::dimension<int> windowextent, string windowtitle);
    chillergtkwindow(Glib::RefPtr<Gtk::Builder> refBuilder, userinterface::dimension<int> windowextent, string windowtitle);
    virtual ~chillergtkwindow();
    void switchToDrawingArea();
    void switchToBuilderInterface();
    void setDrawingCanvas(DRAWING_AREA_SELECTION drawcanvastype);
    void loadImageConfiguration(string imagesConfig);
private:
    DRAWING_AREA_SELECTION myCanvasType;
    DEMO_CANVAS_SELECTION mySelectedCanvas = DEMO_CANVAS_SELECTION::DEMO_CANVAS_NONE;
    
    void switchToSelectedCanvas();
protected:
    Glib::RefPtr<Gtk::Builder> myBoimBuilder;
    Gtk::Box* myComponents_Box1 = NULL;
    Gtk::MenuBar* myComponents_Menubar1 = NULL;
    Gtk::Box m_VBox;
    Gtk::DrawingArea genericDrawingArea;
    Gtk::Stack stackDrawVariety;
    Gtk::Stack stackDrawImages;
    fwdstringlist loadCarouselImages;
    quickdrawvariety m_AppVarietyDrawingArea;
    imagecanvastester m_AppImageMiscCanvas;
};

#endif	/* BOIMGTKWINDOW_H */