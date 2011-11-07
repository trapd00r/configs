#include <gmodule.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>

#include "industrial1.h"

#define INDUSTRIAL_GTK_VERSION 1

#define INDUSTRIAL_CONST

static gboolean
check_page (GtkWidget *widget, 
	    int x, int y,
	    int width, int height);
static int
option_menu_get_indicator_width (GtkWidget      *widget);

#define GET_SHADING_HASH(style) (((IndustrialData *)(style)->engine_data)->shading_hash)
#define GET_CONTRAST(style) (((IndustrialRcData *) (style)->rc_style->engine_data)->contrast)
#define GET_CONTRAST_CENTER(style) (((IndustrialRcData *) (style)->rc_style->engine_data)->contrast_center)
#define GET_ROUNDED_BUTTONS(style) (((IndustrialRcData *) (style)->rc_style->engine_data)->rounded_buttons)
#define GET_XTHICKNESS(style) ((style)->klass->xthickness)
#define GET_YTHICKNESS(style) ((style)->klass->ythickness)
#define GDK_IS_WINDOW(window) (gdk_window_get_type((window)) != GDK_WINDOW_PIXMAP)
#define GTK_IS_STYLE(style) (TRUE)
