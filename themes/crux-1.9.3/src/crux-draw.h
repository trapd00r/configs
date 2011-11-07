#ifndef CRUX_DRAW_H
#define CRUX_DRAW_H

#include <gtk/gtk.h>

void
draw_hline (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail,
	    gint x1, gint x2, gint y);

void
draw_vline (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget, const gchar *detail, gint y1, gint y2, gint x);

void
draw_shadow (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_box (GtkStyle *style,
	  GdkWindow *window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle *area,
	  GtkWidget *widget,
	  const gchar *detail, gint x, gint y, gint width, gint height);
void
draw_polygon (GtkStyle *style,
	      GdkWindow *window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle *area,
	      GtkWidget *widget,
	      const gchar *detail, GdkPoint *points, gint npoints, gint fill);

void
draw_arrow (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail,
	    GtkArrowType arrow_type,
	    gint fill, gint x, gint y, gint width, gint height);

void
draw_diamond (GtkStyle *style,
	      GdkWindow *window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle *area,
	      GtkWidget *widget,
	      const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_oval (GtkStyle *style,
	   GdkWindow *window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle *area,
	   GtkWidget *widget,
	   const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_string (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, const gchar *string);
void
draw_flat_box (GtkStyle *style,
	       GdkWindow *window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle *area,
	       GtkWidget *widget,
	       const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_check (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, gint x, gint y, gint width, gint height);
void
draw_option (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_cross (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_ramp (GtkStyle *style,
	   GdkWindow *window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle *area,
	   GtkWidget *widget,
	   const gchar *detail,
	   GtkArrowType arrow_type, gint x, gint y, gint width, gint height);

void
draw_tab (GtkStyle *style,
	  GdkWindow *window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle *area,
	  GtkWidget *widget,
	  const gchar *detail, gint x, gint y, gint width, gint height);

void
draw_shadow_gap (GtkStyle *style,
		 GdkWindow *window,
		 GtkStateType state_type,
		 GtkShadowType shadow_type,
		 GdkRectangle *area,
		 GtkWidget *widget,
		 const gchar *detail,
		 gint x,
		 gint y,
		 gint width,
		 gint height,
		 GtkPositionType gap_side, gint gap_x, gint gap_width);

void
draw_box_gap (GtkStyle *style,
	      GdkWindow *window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle *area,
	      GtkWidget *widget,
	      const gchar *detail,
	      gint x,
	      gint y,
	      gint width,
	      gint height,
	      GtkPositionType gap_side, gint gap_x, gint gap_width);
void
draw_extension (GtkStyle *style,
		GdkWindow *window,
		GtkStateType state_type,
		GtkShadowType shadow_type,
		GdkRectangle *area,
		GtkWidget *widget,
		const gchar *detail,
		gint x,
		gint y, gint width, gint height, GtkPositionType gap_side);

void
draw_focus (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, 
	    gint x, 
	    gint y, 
	    gint width, 
	    gint height);
void
draw_slider (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation);

void
draw_handle (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation);


extern gboolean eazel_engine_widget_in_focused_window_p (GtkWidget *widget);
void uninstall_all_focus_hooks (void);

#endif
