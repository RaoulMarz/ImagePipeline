/* 
 * File:   quickdrawvariety.h
 * Author: raoul
 *
 */

#ifndef _QUICKDRAW_VARIETY_H
#define	_QUICKDRAW_VARIETY_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include "dimension.h"
#include "graphicstypes.h"
#include "fwdstringlist.h"

using namespace userinterface;

class quickdrawvariety : public Gtk::DrawingArea {
public:
    quickdrawvariety();
    virtual ~quickdrawvariety();
    bool pauseTimer(bool pause = true);
    
    void initialise();
    void switchdrawtext(int scale = -1);
    void textjustification(Gtk::Justification txtJustification);
    void setDrawSelection(DRAWING_AREA_SELECTION drawAreaType);
private:
    long drawcounter;
    double simpleclock_radius;
    double simpleclock_line_width;
    int appwidth = 600;
    int appheight = 400;
    int charWidth;
    int charHeight;
    int columns = 80;
    int rows = 26;
    int textWinWidth, textWinHeight;
    dimension<int> defaultTextBoxSize;
    DRAWING_AREA_SELECTION drawingareaType;
    fwdstringlist* workDrawTextItems = nullptr;
    Gtk::Justification text_draw_justification;
    sigc::slot<bool> mydrawTimer_slot;
    sigc::connection* signalconnectionTimer;
    Glib::RefPtr<Gdk::Pixbuf> jumpbox_image;
    
    void setTextGridDimension(dimension<int> txtgridsize);
    void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void draw_text(const Cairo::RefPtr<Cairo::Context>& cr, int rectangle_width, int rectangle_height);
    void drawLoadingBars(const Cairo::RefPtr<Cairo::Context>& crtx, int counter, int width, int height, bool clearArea);
    bool drawSimpleClock(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    bool displayTextGrid(fwdstringlist* textlines, const Cairo::RefPtr<Cairo::Context>& cr, int width, int height, int top = -1, int left = -1);
    bool draw_simpletext(const Cairo::RefPtr<Cairo::Context>& cr, int coordX, int coordY, int fontsize, string myText);
    bool draw_picturetest(const Cairo::RefPtr<Cairo::Context>& cr, double scalefactor = -1.000);
    bool drawVarietyTest(const Cairo::RefPtr<Cairo::Context>& cr);
    bool drawShapesTest(const Cairo::RefPtr<Cairo::Context>& cr);
    bool drawMiscImagesTest(const Cairo::RefPtr<Cairo::Context>& cr);
    bool drawImageListTest(const Cairo::RefPtr<Cairo::Context>& cr);
    bool drawTextBoxTest(const Cairo::RefPtr<Cairo::Context>& cr);
protected:
    int m_timer_number;
    
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_timeout(int timer_number);
};

#endif	/* _QUICKDRAW_VARIETY_H */

