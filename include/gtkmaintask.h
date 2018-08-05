/* 
 * File:   gtkmaintask.h
 * Author: raoul
 *
 * Created on April 13, 2017, 10:25 PM
 */

#ifndef GTKMAINTASK_H
#define GTKMAINTASK_H

#include <gtk/gtk.h>
#include <pango/pango.h>
#include <cairo/cairo-ft.h>
#include <gtk-3.0/gdk/gdk.h>
#include <string>
#include "dimension.h"

using namespace std;
using namespace userinterface;

typedef struct _UIdrawstruct DrawStructState;

struct _UIdrawstruct {
    /* Buffer surface */
    cairo_surface_t *buffer;

    /* Widgets */
    GtkWidget *window; /* Main window */
    GtkWidget *area; /* Display area */

    /* Update timeout id */
    guint update_id;
};

class gtkmaintask {
public:
    static void launchUI();
    static gboolean configure_event(GtkWidget *widget,
        GdkEventConfigure *event,
        DrawStructState* data);
    static gboolean draw_callback(GtkWidget *widget, cairo_t *cr);
    static void close_window(void);
    static void setParameterTitle(string title);
    static void setParameterAppIcon(string iconFile);
    static void clearArea(cairo_t *crtx, string backColour);
    static void drawPatternImage(cairo_t *crtx, string imagefile, dimension<int> dimextent);
private:
    static GdkPixbuf *create_pixbuf(const gchar * filename);
    static void drawLoadingBars(cairo_t *crtx, int counter, int width, int height);
};


#endif /* GTKMAINTASK_H */

