#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include <gtk/gtk.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "draw_fill.h"
#include "draw_grips.h"
#include "draw_arrows.h"

#include <math.h>
#include <string.h>

#define DETAIL(xx) ((detail) && (!strcmp(xx, detail)))
#define FUZZY_COMPARE(i, j, fudge) ((i>j)?(i - j <= fudge):(j - i <= fudge))

#if GTK_CHECK_VERSION(2, 0, 0)
#define GTK2		1
#else
#define GTK1		1 
#endif

#define IS_HANDLE_BOX_ITEM(object) ((widget) && (widget->parent) && GTK_IS_HANDLE_BOX(gtk_widget_get_parent (widget)))

#ifdef GTK2
#define xthickness(style) (((GtkStyle *)style)->xthickness)
#define ythickness(style) (((GtkStyle *)style)->ythickness)

#define gdk_window_get_size(window, width, height) (gdk_drawable_get_size (window, width, height))
#define gdk_pixbuf_unref(pixbuf) (g_object_unref(pixbuf))
#define gdk_pixmap_unref(pixmap) (g_object_unref(pixmap))
#define gdk_bitmap_unref(pixmap) (g_object_unref(pixmap))
#define gdk_pixbuf_ref(pixbuf) (g_object_ref(pixbuf))
#define gdk_pixmap_ref(pixmap) (g_object_ref(pixmap))
#define gdk_gc_destroy(gc) (g_object_unref(gc))

#define gtk_type_is_a(object, type) (g_type_is_a(object, type))

typedef const gchar		detail_char;

static GtkStyleClass *parent_class = NULL;

#define IS_BONOBO_DOCK_ITEM(object) ((widget) && (widget->parent) && (GTK_IS_HANDLE_BOX(gtk_widget_get_parent (widget)) || (g_type_name(G_OBJECT_TYPE(widget->parent))) && (!strcmp("BonoboDockItem", g_type_name(G_OBJECT_TYPE(widget->parent))))))

#endif

#ifdef GTK1
#define gtk_range_get_value(range) gtk_range_get_adjustment(range)->value
#define gtk_range_get_inverted(range) FALSE

#define gtk_widget_get_parent(widget) (((widget) && (widget->parent))?widget->parent:NULL)

#define xthickness(style) (((GtkStyle *)style)->klass->xthickness)
#define ythickness(style) (((GtkStyle *)style)->klass->ythickness)
#define g_ascii_strncasecmp(str1, str2, len) (g_strncasecmp(str1, str2, len))

typedef gchar			detail_char;

extern GtkStyleClass smooth_default_class;

#define IS_BONOBO_DOCK_ITEM(object) (IS_HANDLE_BOX_ITEM(object))

#endif

#define NO_CHECK	1
#define FAST_CHECK	2
#define SLOPPY_CHECK	3
#define CLEAN_CHECK	4
#define X_CHECK		5
#define BLOCK_CHECK	6
#define CIRCLE_CHECK	7
#define DIAMOND_CHECK   8
#define XPM_CHECK	9

#define NO_OPTION	1
#define CIRCLE_OPTION	2
#define DIAMOND_OPTION	3
#define SQUARE_OPTION	4
#define XPM_OPTION	5

#define NO_EDGE		1
#define LINE_EDGE	2
#define GRADIENT_EDGE	3
#define XPM_EDGE	4

#define LIGHTNESS_MULT  1.2//1.1
#define DARKNESS_MULT   0.666667 //0.5

void
alloc_color (GtkStyle * style, GdkColor * color);

GdkGC * 
new_color_gc (GtkStyle * style, GdkColor * color);

GdkGC *
shaded_color (GtkStyle * style, GtkStateType state_type, gdouble shade_value);

void
lighttone_color(GdkColor * color, GtkStyle * style, GtkStateType state);

void
darktone_color(GdkColor * color, GtkStyle * style, GtkStateType state);

void
midtone_color(GdkColor * color, GtkStyle * style, GtkStateType state);

GdkGC *
lighttone_gc(GtkStyle * style, GtkStateType state);

GdkGC *
darktone_gc(GtkStyle * style, GtkStateType state);

GdkGC *
midtone_gc(GtkStyle * style, GtkStateType state);

GdkGC *
middarktone_gc(GtkStyle * style, GtkStateType state);

GdkGC *
midlighttone_gc(GtkStyle * style, GtkStateType state);

GdkBitmap *
arc_clip_mask(gint width,
	      gint height);

gboolean
sanitize_parameters(GtkStyle * style,
  	            GdkWindow * window,
	            gint * width,
	            gint * height);

GtkWidget *
get_notebook_page(GtkWidget * widget);

GtkWidget *
get_tab_label(GtkWidget *page, GtkWidget * widget);

gboolean 
widget_is_tab_label(GtkWidget *page, GtkWidget * widget);

gboolean 
tab_label_is_current_page(GtkWidget *page, GtkWidget * widget);
		    
void
reverse_engineer_stepper_box (GtkWidget    *range,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height);

void
reverse_engineer_spin_button (GtkWidget    *widget,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height);

void
reverse_engineer_arrow_box (GtkWidget    *widget,
                            const gchar * detail,
			    GtkArrowType  arrow_type,
			    gint         *x,
			    gint         *y,
			    gint         *width,
			    gint         *height);
			    
gboolean
rounded_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8]);

gboolean
square_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8]);

gboolean
triangle_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8]);

void
rounded_box_points(gint x,
                   gint y, 
  	           gint width, 
		   gint height,
		   GdkPoint points[13],
		   gboolean large);

void
draw_default_triangle(GtkStyle * style,
	              GdkWindow * window,
	              GtkStateType state_type,
	              GtkShadowType shadow_type,
	              GdkRectangle * area,
	              GtkWidget * widget,
	              const gchar * detail,
		      gint x,
		      gint y,
		      gint width,
		      gint height);	

void
do_draw_shadow_with_gap(GdkWindow * window,
                        GdkRectangle * area,
			GdkGC * tl_gc,
			GdkGC * br_gc,
			gint x,
			gint y,
			gint width,
			gint height,
			GtkPositionType gap_side, 
			gint gap_pos,
			gint gap_size,
			gboolean topleft_overlap);

void
do_draw_bevel_with_gap(GdkWindow * window,
                       GdkRectangle * area,
		       GdkGC * tl_gc,
		       GdkGC * br_gc,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       gint thickness,
		       GtkPositionType gap_side, 
		       gint gap_pos,
		       gint gap_size);

void
do_draw_option_shadow(GdkWindow * window,
	       GdkRectangle * area,
               GdkGC * tl_gc,
               GdkGC * br_gc,
	       gint x,
	       gint y,
	       gint width,
	       gint height);
	       
void
do_draw_option_bevel(GdkWindow * window,
                       GdkRectangle * area,
		       GdkGC * tl_gc,
		       GdkGC * br_gc,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       gint thickness);

void
draw_check_mark(GdkWindow * window,
                GdkGC * gc,
		GdkRectangle * area,
		gint x,
		gint y,
		gint width,
		gint height,
		gint check_style);

gboolean 
TranslateCheckStyleName (gchar * str, gint *retval);

gboolean 
TranslateEdgeStyleName (gchar * str, gint *retval);

#endif /* MISC_FUNCTIONS_H */
