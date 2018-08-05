/* 
 * File:   chillergtkwindow.cpp
 * Author: raoul
 * 
 * Created on August 29, 2015, 3:51 PM
 */

#include <vector>
#include "chillergtkwindow.h"
#include "fileutilities.h"

using namespace std;
using namespace userinterface;

chillergtkwindow::chillergtkwindow(dimension<int> windowextent, string windowtitle) : m_VBox(Gtk::ORIENTATION_VERTICAL) {
    set_size_request(windowextent.getWidth(), windowextent.getHeight());
    set_title(windowtitle);
    add(m_VBox);
    //m_Entry.set_max_length(50);
    //m_VBox.pack_start(m_Button_Close);
    //m_Button_Close.set_can_default();
    //m_Button_Close.grab_default();
    m_VBox.pack_start(stackDrawVariety);
    //m_VBox.pack_start(m_AppVarietyDrawingArea);
    m_AppVarietyDrawingArea.set_can_default();
    m_AppVarietyDrawingArea.grab_default();
    m_AppVarietyDrawingArea.initialise();
    //genericDrawingArea
    m_AppImageMiscCanvas.set_can_default();
    m_AppImageMiscCanvas.grab_default();
    m_AppImageMiscCanvas.setimageslist(loadCarouselImages);
    m_AppImageMiscCanvas.initialise();
    show_all_children();
}

chillergtkwindow::chillergtkwindow(Glib::RefPtr<Gtk::Builder> refBuilder, dimension<int> windowextent, string windowtitle) : m_VBox(Gtk::ORIENTATION_VERTICAL) {
    myBoimBuilder = refBuilder;
    set_size_request(windowextent.getWidth(), windowextent.getHeight());
    set_title(windowtitle);
    add(m_VBox);
    m_VBox.pack_start(stackDrawVariety);
    //m_VBox.pack_start(m_AppVarietyDrawingArea);
    m_AppVarietyDrawingArea.set_can_default();
    m_AppVarietyDrawingArea.grab_default();
    m_AppVarietyDrawingArea.initialise();
    m_AppImageMiscCanvas.set_can_default();
    m_AppImageMiscCanvas.grab_default();
    m_AppImageMiscCanvas.setimageslist(loadCarouselImages);
    m_AppImageMiscCanvas.initialise();
    show_all_children();
}

void chillergtkwindow::switchToSelectedCanvas() {
    switch (mySelectedCanvas) {
        case DEMO_CANVAS_SELECTION::DEMO_CANVAS_NONE: {
            break;
        }
        case DEMO_CANVAS_SELECTION::DEMO_CANVAS_IMAGES: {
            stackDrawVariety.add(m_AppImageMiscCanvas, "images");
            break;
        }
        case DEMO_CANVAS_SELECTION::DEMO_CANVAS_VARIETY: {
            stackDrawVariety.add(m_AppVarietyDrawingArea, "variety");
            break;
        }
    }
    show_all_children();
}

void chillergtkwindow::loadImageConfiguration(string imagesConfig) {
    //Load the images from the specified configuration file
    if (fileutilities::fileexists(imagesConfig)) {
        //Read the config file into a stream buffer
        string configText = fileutilities::readfilecontent(imagesConfig);
        if (configText.length() > 1) {
            loadCarouselImages.parsefromstring(configText, "\n");
        }
    }
}

void chillergtkwindow::switchToDrawingArea() {
    // Get list of all the children controls and if "box1", "menubar1", etc...
    // then remove these Builder controls
    std::vector<Widget*> appBoxChildren = m_VBox.get_children();
    for (Widget* childwidget : appBoxChildren) {
        string ctlname = childwidget->get_name();
        if (ctlname.compare("box1") == 0) {
            // Drop the parent or all the children as well? or decouple the control ??
        }
    }
    //Change the drawing area if it has changed
    switchToSelectedCanvas();
    /*
    m_VBox.pack_start(m_AppDrawingArea);
    m_AppDrawingArea.set_can_default();
    m_AppDrawingArea.grab_default();
    m_AppMiscCanvas.initialise();
    show_all_children();
     * */
}

void chillergtkwindow::switchToBuilderInterface() {
    m_AppVarietyDrawingArea.pauseTimer();
    // Remove m_AppDrawingArea from m_VBox
    if (myBoimBuilder) {
        //Load the application components from the Builder in the correct order
        //and keep the relationship(s) of parent and child controls
        //myBoimBuilder->get_widget("BoimWindow", pDialog);
        /*
        Gtk::Button* pButton = 0;
        refBuilder->get_widget("quit_button", pButton);
        if(pButton)
        {
            pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
        }
         * */
        myBoimBuilder->get_widget("box1", myComponents_Box1);
        myBoimBuilder->get_widget("menubar1", myComponents_Menubar1);
    }
}

void chillergtkwindow::setDrawingCanvas(DRAWING_AREA_SELECTION drawcanvastype) {
    myCanvasType = drawcanvastype;
    switch (drawcanvastype) {
        case DRAWING_AREA_SELECTION::DRAWING_AREA_SHAPES : {
            mySelectedCanvas = DEMO_CANVAS_SELECTION::DEMO_CANVAS_VARIETY;
            m_AppVarietyDrawingArea.setDrawSelection(DRAWING_AREA_SELECTION::DRAWING_AREA_SHAPES);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_VARIETY : {
            mySelectedCanvas = DEMO_CANVAS_SELECTION::DEMO_CANVAS_VARIETY;
            m_AppVarietyDrawingArea.setDrawSelection(DRAWING_AREA_SELECTION::DRAWING_AREA_VARIETY);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGEMISC : {
            mySelectedCanvas = DEMO_CANVAS_SELECTION::DEMO_CANVAS_IMAGES;
            m_AppImageMiscCanvas.setDrawSelection(DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGEMISC);
            //m_AppDrawingArea.setimages(loadCarouselImages);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGELIST : {
            mySelectedCanvas = DEMO_CANVAS_SELECTION::DEMO_CANVAS_IMAGES;
            m_AppImageMiscCanvas.setDrawSelection(DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGELIST);
            m_AppImageMiscCanvas.setimageslist(loadCarouselImages);
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_TEXTBOX : {
            break;
        }
    }
}

chillergtkwindow::~chillergtkwindow() {
    //Release (delete) any dynamically, non reference-counted variables
}

