/* 
 * File:   imagecanvastester.cpp
 * Author: raoul
 * 
 * Created on February 19, 2018, 10:27 PM
 */

#include <boost/filesystem.hpp>
#include <stdio.h>
#include "imagecanvastester.h"
#include "fwdstringlist.h"
#include "fileutilities.h"

imagecanvastester::imagecanvastester() {
    renderImages = std::make_unique<std::vector <Cairo::RefPtr < Cairo::ImageSurface>>>();

    mydrawTimer_slot = sigc::bind(sigc::mem_fun(*this,
            &imagecanvastester::on_timeout), m_timer_number);
    // This is where we connect the slot to the Glib::signal_timeout()
    signalconnectionTimer = new sigc::connection(Glib::signal_timeout().connect(mydrawTimer_slot, 100));
}

imagecanvastester::imagecanvastester(fwdstringlist& imageslist, gint refreshmillis) {
    
}

imagecanvastester::imagecanvastester(const imagecanvastester& orig) {
}

imagecanvastester::~imagecanvastester() {
}

void imagecanvastester::initialise() {
    Pango::FontDescription font;

    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_NORMAL);
    font.set_size(14);

    Glib::RefPtr<Pango::Layout> layout = create_pango_layout("A");

    layout->set_font_description(font);

    //get the text dimensions (it updates the variables -- by reference)
    layout->get_pixel_size(charWidth, charHeight);

    textWinWidth = charWidth * columns;
    textWinHeight = charHeight * rows;
}

bool imagecanvastester::pauseTimer(bool pause) {
    if (pause) {
        if (signalconnectionTimer == NULL)
            return false;
        signalconnectionTimer->disconnect();
        delete signalconnectionTimer;
        signalconnectionTimer = NULL;
        return true;
    } else {
        if (signalconnectionTimer) {
            signalconnectionTimer = new sigc::connection(Glib::signal_timeout().connect(mydrawTimer_slot, 100));
            return true;
        } else
            return false;
    }
}

bool imagecanvastester::on_timeout(int timer_number) {
    // force our program to redraw the drawing area.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

bool imagecanvastester::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    drawcounter++;
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    // coordinates for the center of the window
    int xc = width / 2;
    int yc = height / 2;

    switch (myCanvasType) {
        case DRAWING_AREA_SELECTION::DRAWING_AREA_SHAPES:
        {

            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_VARIETY:
        {
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_TEXTBOX:
        {
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGEMISC:
        {
            dimension<int> myRectangleBorder = dimension<int>(10, 10, width - 20, height - 20);
            draw_roundedrectangle(cr, myRectangleBorder);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGELIST:
        {
            dimension<int> myRectangleBorder = dimension<int>(10, 10, 540, 400);
            draw_roundedrectangle(cr, myRectangleBorder);
            draw_imageslist(cr);
            //string myTestImage = "/home/raoul/Pictures/image1.png";
            //draw_singleImage(cr, myTestImage);
            break;
        }
    }
    return true;
}

bool imagecanvastester::draw_roundedrectangle(const Cairo::RefPtr<Cairo::Context>& cr, dimension<int> rectdim) {
    double x = rectdim.getTopLeft().getX();
    double y = rectdim.getTopLeft().getY();
    double width = rectdim.getWidth();
    double height = rectdim.getHeight();
    double  aspect = 1.0, /* aspect ratio */
            corner_radius = height / 10.0; /* and corner curvature radius */

    double radius = corner_radius / aspect;
    double degrees = M_PI / 180.0;

    cr->begin_new_sub_path();
    cr->arc(x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cr->arc(x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cr->arc(x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cr->arc(x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cr->close_path();

    cr->set_source_rgb(0.5, 0.5, 1);
    cr->fill_preserve();
    cr->set_source_rgba(0.5, 0, 0, 0.5);
    cr->set_line_width(10.0);
    cr->stroke();
    return true;
}

bool imagecanvastester::draw_singleImage(const Cairo::RefPtr<Cairo::Context>& cr, string imagefile) {
    Cairo::RefPtr<Cairo::ImageSurface> image = Cairo::ImageSurface::create_from_png(imagefile);
    int w = image->get_width();
    int h = image->get_height();

    cr->translate(128.0, 128.0);
    cr->rotate(45 * M_PI / 180);
    cr->scale(256.0 / w, 256.0 / h);
    cr->translate(-0.5 * w, -0.5 * h);

    cr->set_source(image, 0, 0);
    cr->paint();
    return true;
}

bool imagecanvastester::draw_imageslist(const Cairo::RefPtr<Cairo::Context>& cr) {
    if (imagesDisplay.count() > 0) {
        int imageIndex = 0;
        for (auto& imageName : imagesDisplay) {
            // draws an image if the file name is valid and renders it with the given attributes
            coordinate<double> imgToLeft = coordinate<double>(10, imageIndex * 200);
            drawImage(cr, imageName, imgToLeft);
            imageIndex++;
        }
    }
    return true;
}

bool imagecanvastester::draw_shapes(const Cairo::RefPtr<Cairo::Context>& cr, vector<shapeform>* shapesList) {
    if ( (shapesList != nullptr) && (shapesList->size() > 0) ) {
        auto print = [](shapeform& shapeX) { std::cout << " " << shapeX.print(); };
        std::for_each(shapesList->begin(), shapesList->end(), print);
    }
    return true;
}

void imagecanvastester::setimageslist(fwdstringlist& imageslist) {
    if (imageslist.count() > 0) {
        imagesDisplay = imageslist;
        for (auto& fileitem : imageslist) {
            if (fileutilities::fileexists(fileitem)) {
                if (flagImageBackend == IMAGE_BACKEND::IMAGE_BACKEND_CAIRO) {
                    Cairo::RefPtr<Cairo::ImageSurface> myImage = Cairo::ImageSurface::create_from_png(fileitem);
                    std::pair<std::string, Cairo::RefPtr<Cairo::ImageSurface>> newitem(fileitem, myImage);
                    mapImageToSurface.insert(newitem);
                } else {
                    Glib::RefPtr<Gdk::Pixbuf> pixBuffer = Gdk::Pixbuf::create_from_file(fileitem);                    
                    guint8* imagePixelData = pixBuffer->get_pixels();
                    //Cairo::ImageSurface::create
                    Cairo::RefPtr<Cairo::ImageSurface> myImage = Cairo::ImageSurface::create(imagePixelData, Cairo::Format::FORMAT_RGB24, pixBuffer->get_width(), pixBuffer->get_height(), 0);
                    std::pair<std::string, Cairo::RefPtr<Cairo::ImageSurface>> newitem(fileitem, myImage);
                    mapImageToSurface.insert(newitem);
                }
            }
        }
    }
}

void imagecanvastester::setrefreshperiod(gint refreshmillis) {
    refreshPeriod = refreshmillis;
}

bool imagecanvastester::image_exists(string filename) {
    if (filename.length() > 0) {
        struct stat statbuf;

        int iret = stat(filename.c_str(), &statbuf);
        return (iret >= 0);
    }
    return false;
}

bool imagecanvastester::isEmptyDimension(dimension<double> dimensionvalue) {
    return (dimensionvalue.getTopLeft() == coordinate<double>(0, 0));
}

bool imagecanvastester::isEmptyCoordinate(coordinate<double> coordinatevalue) {
    return (coordinatevalue == coordinate<double>(0, 0));
}

void imagecanvastester::setDrawSelection(DRAWING_AREA_SELECTION drawAreaType) {
    myCanvasType = drawAreaType;
}

optional<Cairo::RefPtr<Cairo::ImageSurface>> imagecanvastester::getMappedImageFile(string filename) {
    auto imageResult = optional<Cairo::RefPtr < Cairo::ImageSurface>> {};
    Cairo::RefPtr<Cairo::ImageSurface> surfaceObject;
    for (auto& mapitem : mapImageToSurface) {
        if (mapitem.first.compare(filename) == 0) {
            surfaceObject = mapitem.second;
            imageResult = optional<Cairo::RefPtr < Cairo::ImageSurface>> { surfaceObject };
            break;
        }
    }
    return imageResult;
}

void imagecanvastester::drawImage(const Cairo::RefPtr<Cairo::Context>& cr, string filename, coordinate<double> topleft, dimension<double> imagebox) {
    if (filename.length() > 0) {
        if (image_exists(filename)) {
            cr->save();
            //Cairo::RefPtr<Cairo::ImageSurface> myImage = Cairo::ImageSurface::create_from_png(filename);
            optional<Cairo::RefPtr < Cairo::ImageSurface>> myImageFound = getMappedImageFile(filename);
            if (myImageFound) {
                Cairo::RefPtr < Cairo::ImageSurface> myImage = myImageFound.get();
                cr->translate(topleft.getX(), topleft.getY());
                if (isEmptyDimension(imagebox))
                    cr->rectangle(0, 0, myImage->get_width(), myImage->get_height());
                else {
                    
                }
                cr->set_source(myImage, 0, 0);
                cr->paint();
                cr->restore();
            }
        }
    }
}

void imagecanvastester::drawImage(const Cairo::RefPtr<Cairo::Context>& cr, string filename, coordinate<double> topleft, coordinate<double> scale, dimension<double> boundingbox, dimension<double> imagebox) {
    if (filename.length() > 0) {
        if (image_exists(filename)) {
            cr->save();
            optional<Cairo::RefPtr < Cairo::ImageSurface>> myImageFound = getMappedImageFile(filename);
            if (myImageFound) {
                Cairo::RefPtr < Cairo::ImageSurface> myImage = myImageFound.get();
                cr->translate(topleft.getX(), topleft.getY());
                if (isEmptyCoordinate(scale) == false) {
                    cr->scale(scale.getX(), scale.getY());
                }
                if (isEmptyDimension(imagebox))
                    cr->rectangle(0, 0, myImage->get_width(), myImage->get_height());
                else {
                    
                }
                cr->set_source(myImage, 0, 0);
                cr->paint();
                cr->restore();
            }
        }
    }
}
