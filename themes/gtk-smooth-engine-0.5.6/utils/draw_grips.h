#ifndef DRAW_GRIPS_H
#define DRAW_GRIPS_H

#include "misc_functions.h"
	
#define NO_GRIP				1
#define BARS_IN_GRIP			2
#define BARS_OUT_GRIP			3
#define LINES_IN_GRIP			4
#define LINES_OUT_GRIP			5
#define FIXEDLINES_IN_GRIP		6
#define FIXEDLINES_OUT_GRIP		7
#define SLASHES_GRIP			8
#define MAC_BUDS_IN_GRIP		9
#define MAC_BUDS_OUT_GRIP		10
#define NS_BUDS_IN_GRIP			11
#define NS_BUDS_OUT_GRIP		12
#define DOTS_IN_GRIP			13
#define DOTS_OUT_GRIP			14
#define SMALLDOTS_IN_GRIP		15
#define SMALLDOTS_OUT_GRIP		16
#define XPM_GRIP			17

void 
do_draw_buds(GdkWindow * window,
             GdkRectangle * area,
             GdkGC * light_gc,
   	     GdkGC * dark_gc,
   	     GdkGC * mid_gc,
	     gint x,
	     gint y,
             gint width,
	     gint height,
	     GtkOrientation orientation,
	     gboolean ns);

void 
do_draw_lines(GdkWindow * window,
             GdkRectangle * area,
             GdkGC * light_gc,
   	     GdkGC * dark_gc,
   	     GdkGC * mid_gc,
	     gint x,
	     gint y,
             gint width,
	     gint height,	     
	     GtkOrientation orientation,
	     gboolean invert);

void
do_draw_fixed_midlines(GdkWindow * window, 
                    GdkRectangle * area, 
		    GdkGC * light_gc,
   	            GdkGC * dark_gc,
		    gint x, 
		    gint y, 
		    gint width, 
		    gint height, 
		    GtkOrientation orientation,
		    gint count,
		    gint spacing,
		    gboolean invert,
		    gboolean diagonal,
		    gboolean bar);

void
do_draw_fixed_dots(GdkWindow * window, 
                    GdkRectangle * area, 
		    GdkGC * light_gc,
   	            GdkGC * dark_gc,
   	            GdkGC * mid_gc,
		    gint x, 
		    gint y, 
		    gint width, 
		    gint height, 
		    GtkOrientation orientation,
		    gint count,
		    gint spacing,
		    gboolean small);

gboolean TranslateGripStyleName (gchar * str, gint *retval);

#endif /* DRAW_GRIPS_H */
