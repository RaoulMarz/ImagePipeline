
/* 
 * File:   gtkmaintask.cpp
 * Author: raoul
 * 
 * Created on April 13, 2017, 10:25 PM
 */

#include "gtkmaintask.h"
#include "dimension.h"
#include "chillergtkwindow.h"

using namespace userinterface;

static int appwidth = 900;
static int appheight = 600;
static GtkWidget* drawing_area = nullptr;
static int ref_argc;
static char** ref_argv;
static GtkWidget *window;
static GdkPixbuf *appIcon = nullptr;
static DrawStructState *data;
static gulong drawHandlerID = 0;
static gint drawTimerHandle = 0;
static int loadCount = 0;
static gboolean drawActive = FALSE;
static gboolean loadingState = FALSE;

GdkPixbuf* gtkmaintask::create_pixbuf(const gchar * filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf) {
        //fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
    return pixbuf;
}

gboolean gtkmaintask::configure_event(GtkWidget *widget,
        GdkEventConfigure *event,
        DrawStructState * data) {
    PangoLayout *layoutInit = gtk_widget_create_pango_layout(widget, "A");
    /*
    PangoFontDescription* font_desc1 = pango_font_description_from_string(appFontDescription.c_str());
    pango_layout_set_font_description(layoutInit, font_desc1);
    pango_font_description_free(font_desc1);
    pango_layout_get_pixel_size(layoutInit, &charWidth, &charHeight);

    textWinWidth = charWidth * columns;
    textWinHeight = charHeight * rows;
    g_object_unref(layoutInit);

    if (!data->update_id) {
        data->update_id = g_timeout_add(timerdrawperiod, (GSourceFunc)update_buffer, data);
    }
     * */

    return FALSE;
}

gboolean gtkmaintask::draw_callback(GtkWidget *widget, cairo_t *cr) {
    if (cr == NULL)
        return FALSE;
    GtkStyleContext *context;
    gint width, height;

    context = gtk_widget_get_style_context(widget);
    width = gtk_widget_get_allocated_width(widget);
    height = gtk_widget_get_allocated_height(widget);
    
    //Draw grid or visual view of the images in the scrollable image panel    
    if (drawActive) {
        if (loadingState) {
            loadCount++;
            drawLoadingBars(cr, loadCount, width, height);
        } else {
            //cr = cairo_create(drawSurface);
            clearArea(cr, "black");
        }
    }
    return TRUE;
}

void gtkmaintask::close_window(void) {
    if (drawTimerHandle != 0)
        g_source_remove(drawTimerHandle);
    //SystemTime::microsleep(40000L);

    gtk_main_quit();
    window = nullptr;
}

void gtkmaintask::setParameterTitle(string title) {
    
}

void gtkmaintask::setParameterAppIcon(string iconFile) {
    
}

void gtkmaintask::drawPatternImage(cairo_t *crtx, string imagefile, dimension<int> dimextent) {
    cairo_surface_t *surface1 = cairo_image_surface_create_from_png(imagefile.c_str());
    cairo_pattern_t *pattern1 = cairo_pattern_create_for_surface(surface1);

    cairo_set_source(crtx, pattern1);
    cairo_pattern_set_extend(cairo_get_source(crtx), CAIRO_EXTEND_REPEAT);
    //cairo_rectangle(crtx, offX, offY, boxWidth, boxHeight);
    cairo_fill(crtx);
    cairo_pattern_destroy(pattern1);
    cairo_surface_destroy(surface1);
}

void gtkmaintask::clearArea(cairo_t *crtx, string backColour) {
    GdkRGBA colBack;
    gdk_rgba_parse(&colBack, backColour.c_str());
    //int offX = 0;
    //int offY = 0;

    cairo_set_line_width(crtx, 2);
    gdk_cairo_set_source_rgba(crtx, &colBack);
    //cairo_rectangle(crtx, offX, offY, areaWidth, areaHeight);
    cairo_fill(crtx);
}

void gtkmaintask::drawLoadingBars(cairo_t *crtx, int counter, int width, int height) {
    int numbars = 4;
    int runbars = ((counter / 2) % numbars) + 1;
    int barwidth = 40;
    int barspacing = 10;
    int midx = width / 2;
    int midy = height / 2;
    GdkRGBA colBack1, colBack2, colBackConsole;
    gdk_rgba_parse(&colBackConsole, "black");
    gdk_cairo_set_source_rgba(crtx, &colBackConsole);
    cairo_rectangle(crtx, 0, 0, width, height);
    cairo_fill(crtx);
    cairo_set_line_width(crtx, 2);
    gdk_rgba_parse(&colBack1, "green");
    gdk_rgba_parse(&colBack2, "#209d20");
    gdk_cairo_set_source_rgba(crtx, &colBack1);
    for (int ib = 0; ib < runbars; ib++) {
        if ( (ib % 2) == 0)
            gdk_cairo_set_source_rgba(crtx, &colBack1);
        else
            gdk_cairo_set_source_rgba(crtx, &colBack2);
        cairo_rectangle(crtx, (midx - ((numbars / 2) * barwidth)) + ((barwidth + barspacing) * ib), midy - 15, 40, 30);
        cairo_fill(crtx);
    }
}

void gtkmaintask::launchUI() {
    GtkWidget *vbox;
    PangoFontDescription *font_desc;

    //gtk_init(&ref_argc, &ref_argv);
    data = g_slice_new0(DrawStructState);
    //imageWorkSurface.data = NULL;
    drawActive = TRUE;
    loadingState = TRUE;

    appwidth = 900;
    appheight = 600;
    /*
    string appIconFile;// = appParameters.getParameter();
    appIcon = create_pixbuf((const gchar*)(appIconFile.c_str()));
    gtk_window_set_icon(GTK_WINDOW(window), appIcon);
    gtk_widget_realize(window);    

    gboolean keepAboveApplicationWindow = FALSE;
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, appwidth - 2, appheight - 2);
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);
    gulong drawHandlerID = g_signal_connect(gtk_widget_get_toplevel(drawing_area), "draw",
            G_CALLBACK(draw_callback), NULL);
    g_signal_connect(gtk_widget_get_toplevel(drawing_area), "configure_event",
            G_CALLBACK(configure_event), data);
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);
    data->area = drawing_area;
    data->buffer = NULL;
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_window_set_keep_above(GTK_WINDOW(window), keepAboveApplicationWindow);
    //g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(key_press_cb), window);
    
    //run_maintask(ref_argc, ref_argv);
    gtk_main();
     * */
    Gtk::Main kit(&ref_argc, &ref_argv);
    dimension<int> appWindowsExt = dimension<int>(0, 0, appwidth, appheight);
    
    chillergtkwindow* applicationMainWindow = new chillergtkwindow(appWindowsExt, "Chill Room");
    applicationMainWindow->loadImageConfiguration("imagesblur.list");
    //applicationMainWindow->setDrawingCanvas(DRAWING_AREA_SELECTION::DRAWING_AREA_SHAPES);
    applicationMainWindow->setDrawingCanvas(DRAWING_AREA_SELECTION::DRAWING_AREA_IMAGELIST);
    applicationMainWindow->switchToDrawingArea();
    Gtk::Main::run(*applicationMainWindow);
}

