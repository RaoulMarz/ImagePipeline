/* 
 * File:   quickdrawvariety.cpp
 * Author: raoul
 * 
 */

#include "quickdrawvariety.h"
#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <gtk-3.0/gdk/gdk.h>
#include <gtkmm.h>

quickdrawvariety::quickdrawvariety() : simpleclock_radius(0.42), simpleclock_line_width(0.05), m_timer_number(0) {
    drawcounter = 0L;
    mydrawTimer_slot = sigc::bind(sigc::mem_fun(*this,
              &quickdrawvariety::on_timeout), m_timer_number);
    // This is where we connect the slot to the Glib::signal_timeout()
    signalconnectionTimer = new sigc::connection(Glib::signal_timeout().connect(mydrawTimer_slot, 100));
}

void quickdrawvariety::initialise() {
    Pango::FontDescription font;

    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_NORMAL);
    font.set_size(14);

    // http://developer.gnome.org/pangomm/unstable/classPango_1_1Layout.html
    Glib::RefPtr<Pango::Layout> layout = create_pango_layout("A");

    layout->set_font_description(font);

    //get the text dimensions (it updates the variables -- by reference)
    layout->get_pixel_size(charWidth, charHeight);

    textWinWidth = charWidth * columns;
    textWinHeight = charHeight * rows;
    
    jumpbox_image = Gdk::Pixbuf::create_from_file("gtk.png");
}

void quickdrawvariety::switchdrawtext(int scale) {
    bool switchLargeText = false;
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    if (((textWinWidth / width) <= 0.90) && (switchLargeText)) {
        switchLargeText = false;
        int charWidth1, charHeight1;
        int charWidth2, charHeight2;
        int charWidth3, charHeight3;
        Pango::FontDescription font;

        font.set_family("Monospace");
        font.set_weight(Pango::WEIGHT_NORMAL);
        font.set_size(14);

        Glib::RefPtr<Pango::Layout> layoutInit = create_pango_layout("A");
        
        font.set_size(16);
        layoutInit->set_font_description(font);
        layoutInit->get_pixel_size(charWidth1, charHeight1);

        font.set_size(17);
        layoutInit->set_font_description(font);
        layoutInit->get_pixel_size(charWidth2, charHeight2);

        font.set_size(18);
        layoutInit->set_font_description(font);
        layoutInit->get_pixel_size(charWidth3, charHeight3);

        textWinWidth = charWidth3 * columns;
        textWinHeight = charHeight3 * rows;
        if ((textWinWidth < width) && (textWinHeight < height)) {
            charWidth = charWidth3;
            charHeight = charHeight3;
        } else {
            textWinWidth = charWidth2 * columns;
            textWinHeight = charHeight2 * rows;
            if ((textWinWidth < width) && (textWinHeight < height)) {
                charWidth = charWidth2;
                charHeight = charHeight2;
            } else
                charWidth = charWidth1;
                charHeight = charHeight1;
        }
    }
}

void quickdrawvariety::textjustification(Gtk::Justification txtJustification) {
    text_draw_justification = txtJustification;
}

void quickdrawvariety::setDrawSelection(DRAWING_AREA_SELECTION drawAreaType) {
    drawingareaType = drawAreaType;
}

bool quickdrawvariety::pauseTimer(bool pause) {
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

bool quickdrawvariety::on_timeout(int timer_number) {
    // force our program to redraw the drawing area.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

void quickdrawvariety::setTextGridDimension(dimension<int> txtgridsize) {
    textWinHeight = txtgridsize.getHeight();
    textWinWidth = txtgridsize.getWidth();
}

void quickdrawvariety::drawLoadingBars(const Cairo::RefPtr<Cairo::Context>& crtx, int counter, int width, int height, bool clearArea) {
    int numbars = 4;
    int runbars = ((counter / 2) % numbars) + 1;
    int barwidth = 40;
    int barspacing = 10;
    int midx = width / 2;
    int midy = height / 2;
    GdkRGBA colBack1, colBack2;
    if (clearArea) {
        GdkRGBA colBackConsole;
        gdk_rgba_parse(&colBackConsole, "black");
        crtx->set_source_rgb(colBackConsole.red, colBackConsole.green, colBackConsole.blue);
        crtx->rectangle(0, 0, width, height);
        crtx->fill();
    }
    
    crtx->set_line_width(2);
    gdk_rgba_parse(&colBack1, "green");
    gdk_rgba_parse(&colBack2, "#209d20");
    crtx->set_source_rgb(colBack1.red, colBack1.green, colBack1.blue);
    for (int ib = 0; ib < runbars; ib++) {
        if ((ib % 2) == 0)
            crtx->set_source_rgb(colBack1.red, colBack1.green, colBack1.blue);
        else
            crtx->set_source_rgb(colBack2.red, colBack2.green, colBack2.blue);
        crtx->rectangle((midx - ((numbars / 2) * barwidth)) + ((barwidth + barspacing) * ib), midy - 15, 40, 30);
        crtx->fill();
    }
}

bool quickdrawvariety::drawSimpleClock(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    cr->scale(width, height);
    cr->translate(0.5, 0.5);
    cr->set_line_width(simpleclock_line_width);

    cr->save();
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9); // green
    cr->paint();
    cr->restore();
    cr->arc(0, 0, simpleclock_radius, 0, 2 * M_PI);
    cr->save();
    cr->set_source_rgba(1.0, 1.0, 1.0, 0.8);
    cr->fill_preserve();
    cr->restore();
    cr->stroke_preserve();
    cr->clip();

    //clock ticks
    for (int i = 0; i < 12; i++) {
        double inset = 0.05;

        cr->save();
        cr->set_line_cap(Cairo::LINE_CAP_ROUND);

        if (i % 3 != 0) {
            inset *= 0.8;
            cr->set_line_width(0.03);
        }

        cr->move_to(
                (simpleclock_radius - inset) * cos(i * M_PI / 6),
                (simpleclock_radius - inset) * sin(i * M_PI / 6));
        cr->line_to(
                simpleclock_radius * cos(i * M_PI / 6),
                simpleclock_radius * sin(i * M_PI / 6));
        cr->stroke();
        cr->restore(); /* stack-pen-size */
    }

    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime(&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds = timeinfo->tm_sec * M_PI / 30;

    cr->save();
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);

    // draw the seconds hand
    cr->save();
    cr->set_line_width(simpleclock_line_width / 3);
    cr->set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
    cr->move_to(0, 0);
    cr->line_to(sin(seconds) * (simpleclock_radius * 0.9),
            -cos(seconds) * (simpleclock_radius * 0.9));
    cr->stroke();
    cr->restore();

    // draw the minutes hand
    cr->set_source_rgba(0.117, 0.337, 0.612, 0.9); // blue
    cr->move_to(0, 0);
    cr->line_to(sin(minutes + seconds / 60) * (simpleclock_radius * 0.8),
            -cos(minutes + seconds / 60) * (simpleclock_radius * 0.8));
    cr->stroke();

    // draw the hours hand
    cr->set_source_rgba(0.337, 0.612, 0.117, 0.9); // green
    cr->move_to(0, 0);
    cr->line_to(sin(hours + minutes / 12.0) * (simpleclock_radius * 0.5),
            -cos(hours + minutes / 12.0) * (simpleclock_radius * 0.5));
    cr->stroke();
    cr->restore();

    // draw a little dot in the middle
    cr->arc(0, 0, simpleclock_line_width / 3.0, 0, 2 * M_PI);
    cr->fill();

    return true;
}

void quickdrawvariety::draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr,
                            int width, int height)
{
  cr->rectangle(0, 0, width, height);
  cr->fill();
  coordinate<int> textAnchorCoord = coordinate<int>(width / 4 - 10, height / 3);
  Glib::RefPtr<Pango::Layout> layout = create_pango_layout("Rectangle here ^");
  cr->move_to(textAnchorCoord.getX(), textAnchorCoord.getY());
  layout->show_in_cairo_context(cr);  
}

void quickdrawvariety::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
        int rectangle_width, int rectangle_height) {
    
    //Loop through the text items in workDrawTextItems
    if (workDrawTextItems == nullptr)
        return;
    coordinate<int> textAnchorCoord;
    Glib::RefPtr<Pango::Layout> layout = create_pango_layout("Hi there!");
    // Position the text in the middle
    if (text_draw_justification == Gtk::Justification::JUSTIFY_CENTER) {
        textAnchorCoord = coordinate<int>(charWidth, charHeight);
    }
    if (text_draw_justification == Gtk::Justification::JUSTIFY_LEFT) {
        textAnchorCoord = coordinate<int>(charWidth, charHeight);
    }
    if (text_draw_justification == Gtk::Justification::JUSTIFY_RIGHT) {
        int adjustCharCount = 0;
        textAnchorCoord = coordinate<int>(charWidth* adjustCharCount, charHeight);
    }
    cr->move_to(textAnchorCoord.getX(), textAnchorCoord.getY());

    layout->show_in_cairo_context(cr);
}

bool quickdrawvariety::displayTextGrid(fwdstringlist* textlines, const Cairo::RefPtr<Cairo::Context>& cr, int width, int height, int top, int left) {
    if (textlines == nullptr)
        return false;
    cr->scale(width, height);
    int rectangle_width;// = defaultTextBoxSize.
    int rectangle_height;
    
    // draw the background rectangle in which to place text "frame"
    cr->set_source_rgb(1.0, 1.0, 1.0);
    draw_rectangle(cr, rectangle_width, rectangle_height);
    
    cr->set_source_rgb(0.0, 0.0, 0.0);
    draw_text(cr, rectangle_width, rectangle_height);
    
    return true;
}

bool quickdrawvariety::draw_simpletext(const Cairo::RefPtr<Cairo::Context>& cr, int coordX, int coordY, int fontsize, string myText) {
  cr->move_to(coordX, coordY);
  cr->set_source_rgb(0.8, 0.2, 0.2);
  auto font =
  Cairo::ToyFontFace::create("Bitstream Charter",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_BOLD);
  cr->set_font_face(font);
  cr->set_font_size(fontsize);
  cr->show_text(myText);
  return true;
}

bool quickdrawvariety::draw_picturetest(const Cairo::RefPtr<Cairo::Context>& cr, double scalefactor) {
    // Get drawing area size
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// Scale the image to the area
        if (scalefactor > 0.001) {
            cr->scale(scalefactor, scalefactor);
        } else
            cr->scale((double)width/jumpbox_image->get_width(),(double)height/jumpbox_image->get_height());

	cr->save();
	// Place the image at 0,0
	Gdk::Cairo::set_source_pixbuf(cr, jumpbox_image, 0,0);
	// Update the area where the image is located
	cr->rectangle(0, 0, jumpbox_image->get_width(), jumpbox_image->get_height());
	// Fill the area with the image
	cr->fill();
	cr->restore();


	cr->save();
	cr->set_source_rgba(0.,0.,1.,1.);   // blue
	cr->set_line_width(10);
	cr->arc(jumpbox_image->get_width()/2.,jumpbox_image->get_height()/2,width/3,0,2*M_PI);
	cr->stroke();
	cr->restore();

	return true;
}

bool quickdrawvariety::drawVarietyTest(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;
    
    if (drawcounter <= 30L) {
        cr->set_line_width(10.0);
        GdkRGBA colBackConsole;
        gdk_rgba_parse(&colBackConsole, "black");
        cr->set_source_rgb(colBackConsole.red, colBackConsole.green, colBackConsole.blue);
        cr->rectangle(0, 0, width, height);
        cr->fill();
        if (drawcounter >= 15L) {
            gdk_rgba_parse(&colBackConsole, "green");
            cr->set_source_rgb(colBackConsole.red, colBackConsole.green, colBackConsole.blue);
            cr->rectangle(20, 20, width - 40, height - 40);
            cr->fill();
            if (drawcounter >= 20L) {
                gdk_rgba_parse(&colBackConsole, "blue");
                cr->set_source_rgb(colBackConsole.red, colBackConsole.green, colBackConsole.blue);
                cr->rectangle(50, 50, width - 100, height - 100);
                cr->fill();
            }
            draw_simpletext(cr, 40, 300, 48, "Loading Application ...");
        }
    } else {
        if (drawcounter >= 240) {
            drawSimpleClock(cr, width, height);
        }
        if ( (drawcounter >= 100L) && (drawcounter <= 150L) ) {
            drawLoadingBars(cr, drawcounter, width, height, true);
            return true;
        }
        if ( (drawcounter >= 150L) && (drawcounter <= 240L) ) {
            draw_picturetest(cr);
        }
    }
    return true;
}

bool quickdrawvariety::drawShapesTest(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    // coordinates for the center of the window
    //int xc = width / 2;
    //int yc = height / 2;
    
    int topLine = 2 * (drawcounter % 100);
    
    cr->save();
    cr->translate(20, 80 + topLine);
    cr->arc(128.0, 128.0, 76.8, 0, 2 * M_PI);
    cr->clip();

    cr->begin_new_path();
    cr->rectangle(0, 0, 256, 256);
    cr->fill();
    cr->set_source_rgb(0, 1, 0);
    cr->move_to(0, 0);
    cr->line_to(256, 256);
    cr->move_to(256, 0);
    cr->line_to(0, 256);
    cr->set_line_width(10.0);
    cr->close_path();
    cr->stroke();
    cr->restore();
    
    // Another shape
    cr->translate(140 + (drawcounter % 150) * 3, 40 + (drawcounter % 150) * 2.5);
    cr->move_to(128.0, 25.6);
    cr->line_to(230.4, 230.4);
    cr->rel_line_to(-102.4, 0.0);
    cr->curve_to(51.2, 230.4, 51.2, 128.0, 128.0, 128.0);
    cr->close_path();

    cr->move_to(64.0, 25.6);
    cr->rel_line_to(51.2, 51.2);
    cr->rel_line_to(-51.2, 51.2);
    cr->rel_line_to(-51.2, -51.2);
    cr->close_path();

    cr->set_line_width(10.0);
    cr->set_source_rgb(0, 0, 1);
    cr->fill_preserve();
    cr->set_source_rgb(0, 0, 0);    
    cr->stroke();
    return true;
}

bool quickdrawvariety::drawMiscImagesTest(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    return true;
}

bool quickdrawvariety::drawImageListTest(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    return true;
}

bool quickdrawvariety::drawTextBoxTest(const Cairo::RefPtr<Cairo::Context>& cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    
    return true;
}

bool quickdrawvariety::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    drawcounter++;

    switch (drawingareaType) {
        case DRAWING_AREA_SELECTION::DRAWING_AREA_SHAPES : {
            drawShapesTest(cr);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_VARIETY : {
            drawVarietyTest(cr);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGEMISC : {
            drawMiscImagesTest(cr);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGELIST : {
            drawImageListTest(cr);
            break;
        }
        case DRAWING_AREA_SELECTION::DRAWING_AREA_TEXTBOX : {
            drawTextBoxTest(cr);
            break;
        }
    }
    
    return true;
}

quickdrawvariety::~quickdrawvariety() {
}

