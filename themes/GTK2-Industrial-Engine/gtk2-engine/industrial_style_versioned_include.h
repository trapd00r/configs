
#include <gtk/gtk.h>
#include "industrial_style.h"
#include "industrial_rc_style.h"
#include <math.h>
#include <string.h>

#include "bits.c"

#define INDUSTRIAL_GTK_VERSION 2

#define INDUSTRIAL_CONST const

static gboolean
check_page (GtkWidget *widget, 
	    int x, int y,
	    int width, int height);
static int option_menu_get_indicator_width (GtkWidget      *widget);

#define GET_SHADING_HASH(style) (INDUSTRIAL_STYLE((style))->shading_hash)
#define GET_CONTRAST(style) (INDUSTRIAL_STYLE((style))->contrast)
#define GET_CONTRAST_CENTER(style) (INDUSTRIAL_STYLE((style))->contrast_center)
#define GET_ROUNDED_BUTTONS(style) (INDUSTRIAL_STYLE((style))->rounded_buttons)
#define GET_XTHICKNESS(style) ((style)->xthickness)
#define GET_YTHICKNESS(style) ((style)->ythickness)
