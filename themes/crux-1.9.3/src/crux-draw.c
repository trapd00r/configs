#include "crux-draw.h"
#include "crux-style.h"
#include "crux-rc-style.h"
#include "crux-common.h"
#include "crux-pixmaps.h"
#include "crux-gradient.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEBUG 0

#define DETAIL(xx) ((detail) != 0 && strcmp (xx, detail) == 0)

/* Focus change hooks */
#define WINDOW_FOCUS_DATA_KEY "eazel-engine-focus-data"
static GQuark window_focus_data_key;

typedef struct focus_change_data_struct focus_change_data;
struct focus_change_data_struct {
    GtkWidget *widget;

    gboolean is_focused;
    gboolean connected;

    guint focus_in_signal_id;
    guint focus_out_signal_id;
    guint destroyed_signal_id;
};

static GSList *focus_data_list = NULL;

static focus_change_data *
get_focus_data (GtkWidget *widget, gboolean add)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel (widget);
    focus_change_data *data = gtk_object_get_data_by_id (GTK_OBJECT (toplevel),
							 window_focus_data_key);
    if (data == 0 && add)
    {
	data = g_new0 (focus_change_data, 1);
	data->widget = widget;
	gtk_object_set_data_by_id_full (GTK_OBJECT (toplevel),
					window_focus_data_key,
					data, g_free);
	focus_data_list = g_slist_prepend (focus_data_list, data);
    }

    return data;
}

static void
focus_change_helper (GtkWidget *widget, gpointer data)
{
    if (GTK_IS_CONTAINER (widget))
    {
	gtk_container_forall (GTK_CONTAINER (widget),
			      focus_change_helper, NULL);
    }
    else if (GTK_IS_RANGE (widget))
    {
	gtk_widget_queue_draw (widget);
    }
    else if (GTK_IS_PROGRESS (widget))
    {
	/* This is horrible. But the GtkProgress widget stores the
	   progress bar in a pixmap, then blits it on expose. But
	   it will refresh the pixmap when asked to resize.. */
	if (GTK_WIDGET_DRAWABLE (widget))
	    gtk_widget_queue_resize (widget);
    }
}

static void
window_focus_in_callback (GtkWidget *window, GdkEventFocus *event,
			  focus_change_data *data)
{
  printf ("focus in\n");
    data->is_focused = TRUE;
    gtk_container_forall (GTK_CONTAINER (window),
			  focus_change_helper, NULL);
}

static void
window_focus_out_callback (GtkWidget *window, GdkEventFocus *event,
			   focus_change_data *data)
{
  printf ("focus out\n");
    data->is_focused = FALSE;
    gtk_container_forall (GTK_CONTAINER (window),
			  focus_change_helper, NULL);
}

static void
window_destroyed_callback (GtkWidget *window, focus_change_data *data)
{
    focus_data_list = g_slist_remove (focus_data_list, data);
}

gboolean
eazel_engine_widget_in_focused_window_p (GtkWidget *widget)
{
  focus_change_data *data = get_focus_data (widget, FALSE);
  return TRUE;

  if (data) {
    printf ("there was data\n");
    printf ("data->is_focused: %d\n", data->is_focused);
  } else {
    printf ("there was no data\n");
  }
  return (data != 0) ? data->is_focused : FALSE;
}

static void
install_focus_hooks (GdkWindow *window)
{
    /* Evilness */
    GtkWidget *widget;
    gdk_window_get_user_data (window, (gpointer *) &widget);

    printf ("installing focus hooks\n");
    if (widget != NULL && GTK_IS_WINDOW (widget))
    {
	focus_change_data *data = get_focus_data (widget, TRUE);
	if (!data->connected)
	{
	    /* Connect to this window so we get focus-in/out events */
	    data->focus_in_signal_id
		= gtk_signal_connect (GTK_OBJECT (widget), "focus_in_event",
				      GTK_SIGNAL_FUNC(window_focus_in_callback), data);
	    data->focus_out_signal_id
		= gtk_signal_connect (GTK_OBJECT (widget), "focus_out_event",
				      GTK_SIGNAL_FUNC(window_focus_out_callback), data);
	    data->destroyed_signal_id
		= gtk_signal_connect (GTK_OBJECT (widget), "destroy",
				      GTK_SIGNAL_FUNC(window_destroyed_callback), data);

	    data->connected = TRUE;
	}
    }
}

void
uninstall_all_focus_hooks (void)
{
    GSList *ptr;
    for (ptr = focus_data_list; ptr != 0; ptr = ptr->next)
    {
	focus_change_data *data = ptr->data;
	if (data->connected)
	{
	    gtk_signal_disconnect (GTK_OBJECT (data->widget),
				   data->focus_in_signal_id);
	    gtk_signal_disconnect (GTK_OBJECT (data->widget),
			       data->focus_out_signal_id);
	    gtk_signal_disconnect (GTK_OBJECT (data->widget),
				   data->destroyed_signal_id);
	}
	gtk_object_remove_data_by_id (GTK_OBJECT (data->widget),
				      window_focus_data_key);
    }
    g_slist_free (focus_data_list);
    focus_data_list = NULL;
}


/* utility functions */

static inline void
debug (const char *fmt, ...)
{
    if (DEBUG)
    {
	va_list args;
	va_start (args, fmt);
	vfprintf (stderr, fmt, args);
	va_end (args);
    }
}

/* adapted from nautilus-gdk-extensions.c */
static void
interpolate_color (GdkColor *dest, gdouble ratio,
		   GdkColor *start, GdkColor *end)
{
	g_return_if_fail (ratio >= 0.0);
	g_return_if_fail (ratio <= 1.0);

	dest->red = start->red * (1.0 - ratio) + (end->red & 0xFF) * ratio;
	dest->green = start->green * (1.0 - ratio) + end->green * ratio;
	dest->blue = start->blue * (1.0 - ratio) + end->blue * ratio;
}

static void
paint_background_area (GtkStyle *style,
		       GdkWindow *window,
		       GtkStateType state_type,
		       GdkRectangle *area,
		       int x, int y, int width, int height)
{
    GdkGC *gc = style->bg_gc[GTK_STATE_NORMAL];

    if (area != 0)
	gdk_gc_set_clip_rectangle (gc, area);

    gdk_draw_rectangle (window, gc, TRUE, x, y, width, height);

    if (area != 0)
	gdk_gc_set_clip_rectangle (gc, 0);
}

static void
paint_stock_image (eazel_theme_data *theme_data,
		   eazel_engine_stock_image type,
		   gboolean scaled, gboolean setbg,
		   GtkStyle *style,
		   GdkWindow *window,
		   GtkStateType state_type,
		   GdkRectangle *area,
		   GtkWidget *widget,
		   gint x, gint y, gint width, gint height)
{
    GdkPixmap *pixmap, *mask;

    if (width == -1 || height == -1)
    {
	eazel_engine_stock_get_size (theme_data->stock, type,
				     width == -1 ? &width : 0,
				     height == -1 ? &height : 0);
    }

    if (scaled)
    {
	eazel_engine_stock_pixmap_and_mask_scaled (theme_data->stock, type,
						   width, height,
						   &pixmap, &mask);
    }
    else
	eazel_engine_stock_pixmap_and_mask (theme_data->stock, type,
					    &pixmap, &mask);

    /* FIXME GNOME2
       if (gdk_window_get_type (window) == GDK_WINDOW_PIXMAP)
	setbg = FALSE;
    */

    /* FIXME GNOME2 this is probably bad */
    setbg = FALSE;

    if (setbg)
    {
	gdk_draw_pixmap (window, style->fg_gc[state_type], pixmap,
			 0, 0, x, y, width, height);
	if (mask != 0)
	    gdk_window_shape_combine_mask (window, mask, 0, 0);
    }
    else
    {
	int xsrc = 0, ysrc = 0;

	/* Install the mask before clipping.. */
	if (mask != 0)
	{
	    gdk_gc_set_clip_mask (style->fg_gc[state_type], mask);
	    gdk_gc_set_clip_origin (style->fg_gc[state_type], x, y);
	}

	if (area != 0)
	{
	    /* clip by hand to leave gc's clipping for the possible mask */
	    GdkRectangle src = { x, y, width, height }, dest;

	    if (!gdk_rectangle_intersect (&src, area, &dest))
		return;

	    xsrc -= x - dest.x;
	    ysrc -= y - dest.y;
	    x = dest.x;
	    y = dest.y;
	    width = dest.width;
	    height = dest.height;

	}

	if (width > 0 && height > 0)
	{
	    gdk_draw_pixmap (window, style->fg_gc[state_type], pixmap,
			     xsrc, ysrc, x, y, width, height);
	} 

	if (mask != 0)
	{
	    gdk_gc_set_clip_mask (style->fg_gc[state_type], 0);
	    gdk_gc_set_clip_origin (style->fg_gc[state_type], 0, 0);
	}
   }
    
    eazel_engine_stock_free_pixmaps (theme_data->stock, type, pixmap, mask);
}

static void
paint_outline (GdkWindow *window, GdkGC *gc, gboolean rounded,
	       int x, int y, int width, int height)
{
    int corner = rounded ? 1 : 0;

    /* left and top outermost */
    gdk_draw_line (window, gc, x, y + corner,
		   x, y + height - (corner + 1));
    gdk_draw_line (window, gc, x + corner, y, x + width - (corner + 1), y);

    /* right and bottom outermost */
    gdk_draw_line (window, gc, x + width - 1, y + corner,
		   x + width - 1, y + height - (corner + 1));
    gdk_draw_line (window, gc, x + corner, y + height - 1,
		   x + width - (corner + 1), y + height - 1);
}

static void
paint_shadow (GdkWindow *window, GdkGC *a, GdkGC *b, GdkGC *c, GdkGC *d,
	      gboolean rounded, int x, int y, int width, int height)
{
    int corner = rounded ? 1 : 0;

    if (a != 0)
    {
	/* left and top outermost */
	gdk_draw_line (window, a, x, y + corner,
		       x, y + height - (corner + 1));
	gdk_draw_line (window, a, x + corner, y, x + width - (corner + 1), y);
    }

    if (d != 0)
    {
	/* right and bottom outermost */
	gdk_draw_line (window, d, x + width - 1, y + corner,
		       x + width - 1, y + height - (corner + 1));
	gdk_draw_line (window, d, x + corner, y + height - 1,
		       x + width - (corner + 1), y + height - 1);
    }

    if (b != 0)
    {
	/* left and top inner */
	gdk_draw_line (window, b, x + 1, y + 2, x + 1, y + height - 2);
	gdk_draw_line (window, b, x + 1, y + 1, x + width - 2, y + 1);
    }

    if (c != 0)
    {
	/* right and bottom outermost */
	gdk_draw_line (window, c, x + width - 2, y + 1,
		       x + width - 2, y + height - 2);
	gdk_draw_line (window, c, x + 1, y + height - 2,
		       x + width - 2, y + height - 2);
    }
}

static void
paint_entry_shadow (GdkWindow *window, GtkStyle *style,
		    GtkStateType state_type,
		    int x, int y, int width, int height)
{
    gdk_draw_rectangle (window, style->black_gc, FALSE,
			x + 1, y + 1, width - 3, height - 3);

    gdk_draw_line (window, style->dark_gc[state_type],
		   x, y, x + width - 1, y);
    gdk_draw_line (window, style->dark_gc[state_type],
		   x, y, x, y + height - 1);

    gdk_draw_line (window, style->white_gc,
		   x + 1, y + height - 1, x + width - 1, y + height - 1);
    gdk_draw_line (window, style->white_gc,
		   x + width - 1, y + 1, x + width - 1, y + height - 1);

    gdk_draw_line (window, style->mid_gc[state_type],
		   x + 2, y + 2, x + width - 3, y + 2);
    gdk_draw_line (window, style->mid_gc[state_type],
		   x + 2, y + 2, x + 2, y + height - 3);

    gdk_draw_line (window, style->white_gc,
		   x + 2, y + height - 3, x + width - 3, y + height - 3);
    gdk_draw_line (window, style->white_gc,
		   x + width - 3, y + 2, x + width - 3, y + height - 3);
}

static void
paint_menuitem_shadow (GdkWindow *window, GtkStyle *style,
		       int x, int y, int width, int height)
{
    gdk_draw_rectangle (window, style->black_gc, FALSE,
			x + 2, y + 1, width - 5, height - 3);

    gdk_draw_line (window, style->dark_gc[GTK_STATE_NORMAL],
		   x + 1, y, x + width - 3, y);
    gdk_draw_line (window, style->dark_gc[GTK_STATE_NORMAL],
		   x + 1, y, x + 1, y + height - 2);
    gdk_draw_line (window, style->white_gc,
		   x + 2, y + height - 1, x + width - 2, y + height - 1);
    gdk_draw_line (window, style->white_gc,
		   x + width - 2, y + 1, x + width - 2, y + height - 1);
}

static void
paint_default_highlight (eazel_theme_data *theme_data,
			 GdkColor *hi_color, GdkColor *bg_color,
			 GdkWindow *window, GdkGC *gc, int x, int y)
{
    GdkColormap *sys_lut = gdk_colormap_get_system ();
    GdkGCValues old_values;
    GdkColor spectrum[6];
    int i;

    gdk_gc_get_values (gc, &old_values);

    /* Calculate pixel colors */
    for (i = 0; i < 6; i++)
    {
	interpolate_color (spectrum + i, 1.0 / 7 * i, hi_color, bg_color);
    }

#define COLOR(i)							\
    gdk_colormap_alloc_color (sys_lut, spectrum + i, FALSE, TRUE);	\
    gdk_gc_set_foreground (gc, spectrum + i);

#define PIXEL(a,b) gdk_draw_point (window, gc, x + a, y + b)

    COLOR (0); PIXEL (2, 2);
    COLOR (1); PIXEL (3, 2); PIXEL (2, 3); PIXEL (4, 1); PIXEL (1, 4);
    COLOR (2); PIXEL (5, 1); PIXEL (1, 5);
    COLOR (3); PIXEL (6, 1); PIXEL (1, 6);
    COLOR (4); PIXEL (7, 1); PIXEL (1, 7); PIXEL (4, 2); PIXEL (2, 4);
    COLOR (5); PIXEL (8, 1); PIXEL (1, 8);

#undef PIXEL
#undef COLOR

    gdk_gc_set_foreground (gc, &old_values.foreground);
}

static void
paint_default (eazel_theme_data *theme_data,
	       GdkWindow *window, GdkGC *gc, GdkColor *bg,
	       gboolean rounded, gboolean rounded_inner, int thickness,
	       int x, int y, int width, int height)
{
    int corner = rounded ? ((thickness > 2) ? 3 : 1) : 0;
    int window_width, window_height;
    int i;

    gdk_window_get_size (window, &window_width, &window_height);

    /* If trying to draw a box that's too big for the dimensions of
       the window, iteratively reduce the thickness until a value
       is found that won't draw off the window edges */
    while (x < 0 || y < 0 || x + width >= window_width
	   || y + height >= window_height)
    {
	if (thickness <= 0 || width <= 0 || height <= 0)
	    return;

	thickness -= 1;
	x += 1;
	y += 1;
	width -= 2;
	height -= 2;
    }

    if (rounded)
    {
	/* XXX this doesn't work, the background of the window
	   XXX is white, not grey */
	gdk_window_clear_area (window, x, y, 1, 1);
	gdk_window_clear_area (window, x + width, y, 1, 1);
	gdk_window_clear_area (window, x, y + height, 1, 1);
	gdk_window_clear_area (window, x + width, y + height, 1, 1);
    }

    for (i = 0; i < thickness; i++)
    {
	int x_i = x + i;
	int y_i = y + i;
	int w_i = width - (i * 2);
	int h_i = height - (i * 2);

	int d_corner = (corner && i == 0) ? corner : 0;

	gdk_draw_line (window, gc, x_i + d_corner, y_i,
		       x_i + w_i - d_corner , y_i);
	gdk_draw_line (window, gc, x_i + w_i, y_i + d_corner,
		       x_i + w_i, y_i + h_i - d_corner);
	gdk_draw_line (window, gc, x_i + w_i - d_corner, y_i + h_i,
		       x_i + d_corner, y_i + h_i);
	gdk_draw_line (window, gc, x_i, y+i + h_i - d_corner,
		       x_i, y_i + d_corner);
    }

    if (rounded_inner)
    {
	gdk_draw_point (window, gc, x + thickness, y + thickness);
	gdk_draw_point (window, gc, x + thickness, y + height - thickness);
	gdk_draw_point (window, gc, x + width - thickness, y + thickness);
	gdk_draw_point (window, gc, x + width - thickness, y + height - thickness);
    }

    if (thickness >= 3 && rounded)
    {
	GdkColor white = { 0, 65535, 65535, 65535 };
	paint_default_highlight (theme_data, &white, bg, window, gc, x, y);
    }
}

static void
paint_default_box (eazel_theme_data *theme_data,
		   GdkWindow *window, GdkGC *gc,
		   gboolean rounded, gboolean rounded_inner, int thickness,
		   int x, int y, int width, int height)
{
    GdkColor black = { 0, 0, 0, 0 };
    paint_default (theme_data, window, gc, &black,
		   rounded, rounded_inner, thickness,
		   x, y, width, height);
}

static void
paint_focus_box (eazel_theme_data *theme_data, GdkWindow *window,
		 GdkGC *gc, gboolean rounded, gboolean rounded_inner,
		 int thickness, int x, int y, int width, int height)
{
    GdkColormap *sys_lut = gdk_colormap_get_system ();
    GdkGCValues old_values;
    GdkColor color;
    gdk_gc_get_values (gc, &old_values);

    color = theme_data->focus_color;
    gdk_colormap_alloc_color (sys_lut, &color, FALSE, TRUE);
    gdk_gc_set_foreground (gc, &color);

    paint_default (theme_data, window, gc, &color, rounded,
		   rounded_inner, thickness, x, y, width, height);

    gdk_gc_set_foreground (gc, &old_values.foreground);
}

static void
paint_insensitive_box (eazel_theme_data *theme_data,
		       GdkWindow *window, GdkGC *gc, gboolean rounded,
		       int x, int y, int width, int height)
{
    GdkColormap *sys_lut = gdk_colormap_get_system ();
    GdkGCValues old_values;
    GdkColor color;
    gdk_gc_get_values (gc, &old_values);

    color = theme_data->insensitive_colors[1];
    gdk_colormap_alloc_color (sys_lut, &color, FALSE, TRUE);
    gdk_gc_set_foreground (gc, &color);
    gdk_draw_rectangle (window, gc, TRUE, x, y, width, height);

    color = theme_data->insensitive_colors[0];
    gdk_colormap_alloc_color (sys_lut, &color, FALSE, TRUE);
    gdk_gc_set_foreground (gc, &color);
    paint_default (theme_data, window, gc, &color, rounded,
		   FALSE, 1, x, y, width - 1, height - 1);

    gdk_gc_set_foreground (gc, &old_values.foreground);
}

static void
paint_arrow (GdkWindow *window, GdkGC *gc, GtkArrowType arrow_type,
	     int x, int y, int width, int height)
{
    int half_width, half_height;
    int center_x, center_y;

    if ((width & 1) == 0)
	width = width - 1;
    if ((height & 1) == 0)
	height = height - 1;

    half_width = width / 2;
    half_height = height / 2;

    center_x = x + half_width;
    center_y = y + half_height;
  
    switch (arrow_type)
    {
	int i;
	static int offset[5] = { 0, -1, -2, -3, -4 };
	static int length[5] = { 0, 2, 4, 6, 8 };
	static const int size = 4;

    case GTK_ARROW_UP:
	for (i = 0; i < size; i++)
	{
	    gdk_draw_line (window, gc,
			   center_x + offset[i],
			   center_y - 2 + i,
			   center_x + offset[i] + length[i],
			   center_y - 2 + i);
	}
	break;

    case GTK_ARROW_DOWN:
	for (i = 0; i < size; i++)
	{
	    gdk_draw_line (window, gc,
			   center_x + offset[i],
			   center_y + 2 - i,
			   center_x + offset[i] + length[i],
			   center_y + 2 - i);
	}
	break;

    case GTK_ARROW_LEFT:
	for (i = 0; i < size; i++)
	{
	    gdk_draw_line (window, gc,
			   center_x - 2 + i,
			   center_y + offset[i],
			   center_x - 2 + i,
			   center_y + offset[i] + length[i]);
	}
	break;

    case GTK_ARROW_RIGHT:
	for (i = 0; i < size; i++)
	{
	    gdk_draw_line (window, gc,
			   center_x + 2 - i,
			   center_y + offset[i],
			   center_x + 2 - i,
			   center_y + offset[i] + length[i]);
	}
	break;
    }
}

static void
paint_tick (GdkWindow *window, GdkGC *gc, int x, int y)
{
#define PIXEL(a,b) gdk_draw_point (window, gc, x + a, y + b)

    PIXEL (4, -4);
    PIXEL (3, -3); PIXEL (4, -3); PIXEL (5, -3);
    PIXEL (-2, -2);
    PIXEL (2, -2); PIXEL (3, -2); PIXEL (4, -2);
    PIXEL (-3, -1); PIXEL (-2, -1); PIXEL (-1, -1);
    PIXEL (1, -1); PIXEL (2, -1); PIXEL (3, -1);
    PIXEL (-2, 0); PIXEL (-1, 0); PIXEL (0, 0); PIXEL (1, 0); PIXEL (2, 0);
    PIXEL (-1, 1); PIXEL (0, 1); PIXEL (1, 1);
    PIXEL (0, 2);

#undef PIXEL
}

static void
paint_bullet (GdkWindow *window, GdkGC *gc, int x, int y)
{
#define PIXEL(a, b) gdk_draw_point (window, gc, x + a, x + b)

    PIXEL (0, 0); PIXEL (0, -1); PIXEL (-1, 0); PIXEL (-1, -1);
    PIXEL (1, -1); PIXEL (2, -1); PIXEL (-1, 1); PIXEL (-1, 2);

    PIXEL (0, -2); PIXEL (1, -2);
    PIXEL (-2, 0); PIXEL (-2, 1);
    PIXEL (1, 0); PIXEL (2, 0); PIXEL (3, 0);
    PIXEL (0, 1); PIXEL (1, 1); PIXEL (2, 1); PIXEL (3, 1);
    PIXEL (0, 2); PIXEL (1, 2); PIXEL (2, 2);
    PIXEL (0, 3); PIXEL (1, 3);

    PIXEL (-1, -2); PIXEL (-2, -1); PIXEL (2, -2); PIXEL (3, -1);
    PIXEL (-2, 2); PIXEL (-1, 3); PIXEL (2, 3); PIXEL (3, 2);

#undef PIXEL
}


/* style functions */

void
draw_hline (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail,
	    gint x1, gint x2, gint y)
{
    gint thickness_light;
    gint thickness_dark;
    gint i;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_hline: detail=%s state=%d x1=%d x2=%d y=%d\n",
	    detail, state_type, x1, x2, y);

    thickness_light = style->ythickness / 2;
    thickness_dark = style->ythickness - thickness_light;

    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
    }
    for (i = 0; i < thickness_dark; i++)
    {
	gdk_draw_line (window, style->light_gc[state_type], x2 - i - 1,
		       y + i, x2, y + i);
	gdk_draw_line (window, style->dark_gc[state_type], x1, y + i,
		       x2 - i - 1, y + i);
    }

    y += thickness_dark;
    for (i = 0; i < thickness_light; i++)
    {
	gdk_draw_line (window, style->dark_gc[state_type], x1, y + i,
		       x1 + thickness_light - i - 1, y + i);
	gdk_draw_line (window, style->light_gc[state_type],
		       x1 + thickness_light - i - 1, y + i, x2, y + i);
    }
    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
    }
}

void
draw_vline (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget, const gchar *detail, gint y1, gint y2, gint x)
{
    gint thickness_light;
    gint thickness_dark;
    gint i;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_vline: detail=%s state=%d x=%d y1=%d y2=%d\n",
	    detail, state_type, x, y1, y2);

    thickness_light = style->xthickness / 2;
    thickness_dark = style->xthickness - thickness_light;

    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
    }
    for (i = 0; i < thickness_dark; i++)
    {
	gdk_draw_line (window, style->light_gc[state_type], x + i,
		       y2 - i - 1, x + i, y2);
	gdk_draw_line (window, style->dark_gc[state_type], x + i, y1, x + i,
		       y2 - i - 1);
    }

    x += thickness_dark;
    for (i = 0; i < thickness_light; i++)
    {
	gdk_draw_line (window, style->dark_gc[state_type], x + i, y1, x + i,
		       y1 + thickness_light - i);
	gdk_draw_line (window, style->light_gc[state_type], x + i,
		       y1 + thickness_light - i, x + i, y2);
    }
    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
    }
}

void
draw_shadow (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, gint width, gint height)
{
    GdkGC *gc1 = NULL;
    GdkGC *gc2 = NULL;
    GdkGC *gc3 = NULL;
    GdkGC *gc4 = NULL;
    GdkGC *gc_a, *gc_b, *gc_c, *gc_d;
    gint thickness_light;
    gint thickness_dark;
    gboolean rounded = FALSE, rounded_inner = FALSE;
    gboolean outline = TRUE;
    gint i;

    eazel_theme_data *theme_data;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    theme_data = CRUX_RC_STYLE(style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    outline = theme_data->outline_shadow;

    if (widget != 0 && !GTK_WIDGET_IS_SENSITIVE (widget))
	state_type = GTK_STATE_INSENSITIVE;

    debug ("draw_shadow: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
	return;
    case GTK_SHADOW_IN:
    case GTK_SHADOW_ETCHED_IN:
	if (theme_data->inverse_shadow)
	    goto out;
    in:
	gc1 = style->light_gc[state_type];
	gc2 = style->dark_gc[state_type];
	gc3 = style->mid_gc[state_type];
	gc4 = style->bg_gc[state_type];
	break;
    case GTK_SHADOW_OUT:
    case GTK_SHADOW_ETCHED_OUT:
	if (theme_data->inverse_shadow)
	    goto in;
    out:
	gc1 = style->dark_gc[state_type];
	gc2 = style->light_gc[state_type];
	gc3 = style->mid_gc[state_type];
	gc4 = style->bg_gc[state_type];
	break;
    }

    gc_a = gc2;
    gc_b = gc4;
    gc_c = 0;
    gc_d = gc1;

    if (DETAIL ("button") || DETAIL ("optionmenu"))
    {
	/* Clist title buttons have square edges */
	if (widget == 0 || !GTK_IS_CLIST (widget->parent))
	    rounded = rounded_inner = TRUE;
    }
    else if (DETAIL ("menuitem"))
    {
	paint_menuitem_shadow (window, style, x, y, width, height);
	return;
    }
    else if (DETAIL ("entry") || DETAIL ("text"))
    {
	if (widget == 0 || GTK_WIDGET_IS_SENSITIVE (widget))
	{
	    paint_entry_shadow (window, style, state_type,
				x, y, width, height);
	    return;
	}
    }
    else if (DETAIL ("spinbutton"))
    {
      gc_a = gc2;
      gc_b = NULL;
      outline = FALSE;

    }

    if (area)
    {
	gdk_gc_set_clip_rectangle (gc1, area);
	gdk_gc_set_clip_rectangle (gc2, area);
	gdk_gc_set_clip_rectangle (gc3, area);
	gdk_gc_set_clip_rectangle (gc4, area);
	if ((shadow_type == GTK_SHADOW_IN) || (shadow_type == GTK_SHADOW_OUT))
	{
	    gdk_gc_set_clip_rectangle (style->black_gc, area);
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	}
    }
    switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
	break;

    case GTK_SHADOW_IN:
    case GTK_SHADOW_OUT:
	if (state_type == GTK_STATE_INSENSITIVE)
	{
	    paint_insensitive_box (theme_data, window,
				   style->bg_gc[state_type],
				   rounded, x, y, width, height);
	}
	else if (outline)
	{
	    paint_outline (window, style->black_gc, rounded,
			   x, y, width, height);
	    if (!theme_data->no_shadow)
	    {
		paint_shadow (window, gc_a, gc_b, gc_c, gc_d, rounded,
			      x + 1, y + 1, width - 2, height - 2);
	    }
	}
	else
	{
	    if (!theme_data->no_shadow)
	    {
		paint_shadow (window, gc_a, gc_b, gc_c, gc_d, rounded,
			      x, y, width, height);
	    }
	}
	break;

    case GTK_SHADOW_ETCHED_IN:
    case GTK_SHADOW_ETCHED_OUT:
	thickness_light = 1;
	thickness_dark = 1;

	for (i = 0; i < thickness_dark; i++)
	{
	    gdk_draw_line (window, gc1,
			   x + i,
			   y + height - i - 1,
			   x + width - i - 1, y + height - i - 1);
	    gdk_draw_line (window, gc1,
			   x + width - i - 1,
			   y + i, x + width - i - 1, y + height - i - 1);

	    gdk_draw_line (window, gc2,
			   x + i, y + i, x + width - i - 2, y + i);
	    gdk_draw_line (window, gc2,
			   x + i, y + i, x + i, y + height - i - 2);
	}

	for (i = 0; i < thickness_light; i++)
	{
	    gdk_draw_line (window, gc1,
			   x + thickness_dark + i,
			   y + thickness_dark + i,
			   x + width - thickness_dark - i - 1,
			   y + thickness_dark + i);
	    gdk_draw_line (window, gc1,
			   x + thickness_dark + i,
			   y + thickness_dark + i,
			   x + thickness_dark + i,
			   y + height - thickness_dark - i - 1);

	    gdk_draw_line (window, gc2,
			   x + thickness_dark + i,
			   y + height - thickness_light - i - 1,
			   x + width - thickness_light - 1,
			   y + height - thickness_light - i - 1);
	    gdk_draw_line (window, gc2,
			   x + width - thickness_light - i - 1,
			   y + thickness_dark + i,
			   x + width - thickness_light - i - 1,
			   y + height - thickness_light - 1);
	}
	break;
    }
    if (area)
    {
	gdk_gc_set_clip_rectangle (gc1, NULL);
	gdk_gc_set_clip_rectangle (gc2, NULL);
	gdk_gc_set_clip_rectangle (gc3, NULL);
	gdk_gc_set_clip_rectangle (gc4, NULL);
	if ((shadow_type == GTK_SHADOW_IN) || (shadow_type == GTK_SHADOW_OUT))
	{
	    gdk_gc_set_clip_rectangle (style->black_gc, NULL);
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	}
    }
}

void
draw_box (GtkStyle *style,
	  GdkWindow *window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle *area,
	  GtkWidget *widget,
	  const gchar *detail, gint x, gint y, gint width, gint height)
{
    gboolean add_shadow = FALSE;
    eazel_theme_data *theme_data;
    gboolean set_bg = FALSE;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
    {
	gdk_window_get_size (window, &width, &height);
	
	/* FIXME GNOME2
	   if (gdk_window_get_type (window) != GDK_WINDOW_PIXMAP)
	   set_bg = TRUE;
	*/
    }
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    if (DETAIL ("spinbutton")) {
      if (y > (height / 3)) {
	/* this is a down arrow shadow */
	y += 2;
      }
    }

    if (widget != 0 && !GTK_WIDGET_IS_SENSITIVE (widget))
	state_type = GTK_STATE_INSENSITIVE;

    debug ("draw_box: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    if ((!style->bg_pixmap[state_type]) || /* this is totally wronG!!!! */ TRUE /* FIXME GNOME2 ||
					   (gdk_window_get_type (window) == GDK_WINDOW_PIXMAP)*/)
    {
	if (area)
	{
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], area);
	    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
	    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
	    gdk_gc_set_clip_rectangle (style->black_gc, area);
	}

	if (DETAIL ("trough"))
	{
	    if (GTK_IS_PROGRESS_BAR (widget))
	    {
		if (state_type != GTK_STATE_INSENSITIVE)
		{
		    paint_stock_image (theme_data,
				       EAZEL_ENGINE_PROGRESS_TROUGH,
				       TRUE, FALSE,
				       style, window, state_type, area,
				       widget, x, y, width, height);
		}
		else
		{
		    paint_insensitive_box (theme_data, window,
					   style->fg_gc[state_type],
					   FALSE, x, y, width, height);
		}
	    }
	    else if (GTK_IS_SCALE (widget))
	    {
		gboolean focused = GTK_WIDGET_HAS_FOCUS (widget);

		paint_background_area (style, window, state_type, area,
				       x, y, width, height);
		paint_stock_image (theme_data,
				   width > height
				   ? (focused
				      ? EAZEL_ENGINE_H_SLIDER_TROUGH_ACTIVE
				      : EAZEL_ENGINE_H_SLIDER_TROUGH)
				   : (focused
				      ? EAZEL_ENGINE_V_SLIDER_TROUGH_ACTIVE
				      : EAZEL_ENGINE_V_SLIDER_TROUGH),
				   TRUE, FALSE, style, window, state_type,
				   area, widget, x, y, width, height);
	    }
	    else
	    {
		paint_stock_image (theme_data,
				   width > height ? EAZEL_ENGINE_H_TROUGH
				   : EAZEL_ENGINE_V_TROUGH, TRUE, FALSE,
				   style, window, state_type, area,
				   widget, x, y, width, height);
	    }
	}
	else if (DETAIL ("vscrollbar"))
	{
	}
	else if (DETAIL ("hscrollbar"))
	{
	}
	else if (DETAIL ("bar"))
	{
	    if (state_type != GTK_STATE_INSENSITIVE)
	    {
		gboolean focused;
		focused = eazel_engine_widget_in_focused_window_p (widget);
		paint_stock_image (theme_data,
				   focused ? EAZEL_ENGINE_PROGRESS_BAR
				   : EAZEL_ENGINE_PROGRESS_BAR_INACTIVE,
				   TRUE, FALSE, style, window, state_type,
				   area, widget, x, y, width, height);
		if (x > style->xthickness)
		{
		    paint_stock_image (theme_data,
				       EAZEL_ENGINE_PROGRESS_BAR_LEFT,
				       TRUE, FALSE, style, window, state_type,
				       area, widget, x - 2, y, -1, height);
		}
		if (widget != 0
		    && x + width < widget->allocation.width - style->xthickness - 3)
		{
		    paint_stock_image (theme_data,
				       EAZEL_ENGINE_PROGRESS_BAR_RIGHT,
				       TRUE, FALSE, style, window,
				       state_type, area, widget,
				       x + width, y, -1, height);
		}
	    }
	    else
	    {
		paint_insensitive_box (theme_data, window,
				       style->fg_gc[state_type],
				       FALSE, x, y, width, height);
	    }
	}
	else if (DETAIL ("optionmenutab"))
	{
	    int real_width, real_height;
	    int y1, y2;
	    int center_y;
	    int x_offset = -3;

	    gdk_window_get_size (window, &real_width, &real_height);

	    y1 = /*style->ythickness +*/ y;
	    y2 = (y + height) /*- style->ythickness*/;

	    gdk_draw_line (window, style->dark_gc[state_type], 
			   x + x_offset, y1, x + x_offset, y2);
	    gdk_draw_line (window, style->light_gc[state_type],
			   x + 1 + x_offset, y1, x +1 + x_offset, y2);

	    center_y = height / 2 + y;

	    paint_arrow (window, style->fg_gc[state_type], GTK_ARROW_UP,
			 x + 4, center_y - 6, 7, 7);
	    paint_arrow (window, style->fg_gc[state_type], GTK_ARROW_DOWN,
			 x + 4, center_y - 1, 7, 7);
	}
	else if (DETAIL ("buttondefault"))
	{
	    /* Don't draw default markings. */
	}
	else
	{
	    GdkRectangle full;

	    eazel_engine_gradient *gradient = theme_data->gradients[state_type];
	    add_shadow = (shadow_type != GTK_SHADOW_NONE);

	    if (DETAIL ("button") && widget != 0
		&& GTK_WIDGET_HAS_FOCUS (widget)
		&& GTK_WIDGET_CAN_DEFAULT (widget))
	    {
		x -= 1;
		y -= 1;
		width += 2;
		height += 2;
	    }

	    full.x = x;
	    full.y = y;
	    full.width = width;
	    full.height = height;

	    if (DETAIL ("menuitem"))
	    {
		full.x++; full.y++;
		full.width -= 2; full.height -= 2;
	    }

	    if (gradient != NULL && gradient->direction != GRADIENT_NONE)
	    {
		if (!set_bg)
		{
		    eazel_engine_draw_gradient (window,
						style->bg_gc[state_type],
						&full, &full, gradient);
		}
		else
		{
		    GdkRectangle dest;

		    if (area != 0)
			gdk_rectangle_intersect (&full, area, &dest);
		    else
			dest = full;
		    eazel_engine_set_bg_gradient (window, gradient);
		    gdk_window_clear_area (window, dest.x, dest.y,
					   dest.width, dest.height);
		}
	    }
	    else
	    {
		if (!set_bg)
		{
		    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
					x, y, width, height);
		}
		else
		{
		    GdkRectangle dest;
		    if (area != 0)
			gdk_rectangle_intersect (&full, area, &dest);
		    else
			dest = full;
		    gdk_window_set_background (window, &style->bg[state_type]);
		    gdk_window_clear_area (window, dest.x, dest.y,
					   dest.width, dest.height);
		}
	    }

	    if (DETAIL ("button") && widget != 0
		&& GTK_WIDGET_HAS_DEFAULT (widget))
	    {
		void (*fun) (eazel_theme_data *, GdkWindow *, GdkGC *, gboolean, gboolean, int, int, int, int, int) = paint_default_box;

		if (GTK_WIDGET_HAS_FOCUS (widget))
		    fun = paint_focus_box;

		fun (theme_data, window, style->black_gc, TRUE, TRUE,
		     theme_data->default_thickness,
		     x - (theme_data->default_thickness),
		     y - (theme_data->default_thickness),
		     width + theme_data->default_thickness * 2 - 1,
		     height + theme_data->default_thickness * 2 - 1);
	    }
	}
	if (area)
	{
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->black_gc, NULL);
	}
    }
    else
    {
	gtk_style_apply_default_pixmap (style, window, state_type, area, x,
					y, width, height);
    }

    if (add_shadow)
    {
	gtk_paint_shadow (style, window, state_type, shadow_type, area, widget,
			  detail, x, y, width, height);
    }
}

void
draw_polygon (GtkStyle *style,
	      GdkWindow *window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle *area,
	      GtkWidget *widget,
	      const gchar *detail, GdkPoint *points, gint npoints, gint fill)
{
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif /*
        * M_PI 
        */
#ifndef M_PI_4
#define M_PI_4  0.78539816339744830962
#endif /*
        * M_PI_4 
        */

    static const gdouble pi_over_4 = M_PI_4;
    static const gdouble pi_3_over_4 = M_PI_4 * 3;

    GdkGC *gc1;
    GdkGC *gc2;
    GdkGC *gc3;
    GdkGC *gc4;
    gdouble angle;
    gint xadjust;
    gint yadjust;
    gint i;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
    g_return_if_fail (points != NULL);

    debug ("draw_polygon: detail=%s state=%d shadow=%d\n",
	    detail, state_type, shadow_type);

    switch (shadow_type)
    {
    case GTK_SHADOW_IN:
	gc1 = style->light_gc[state_type];
	gc2 = style->dark_gc[state_type];
	gc3 = style->light_gc[state_type];
	gc4 = style->dark_gc[state_type];
	break;
    case GTK_SHADOW_ETCHED_IN:
	gc1 = style->light_gc[state_type];
	gc2 = style->dark_gc[state_type];
	gc3 = style->dark_gc[state_type];
	gc4 = style->light_gc[state_type];
	break;
    case GTK_SHADOW_OUT:
	gc1 = style->dark_gc[state_type];
	gc2 = style->light_gc[state_type];
	gc3 = style->dark_gc[state_type];
	gc4 = style->light_gc[state_type];
	break;
    case GTK_SHADOW_ETCHED_OUT:
	gc1 = style->dark_gc[state_type];
	gc2 = style->light_gc[state_type];
	gc3 = style->light_gc[state_type];
	gc4 = style->dark_gc[state_type];
	break;
    default:
	return;
    }

    if (area)
    {
	gdk_gc_set_clip_rectangle (gc1, area);
	gdk_gc_set_clip_rectangle (gc2, area);
	gdk_gc_set_clip_rectangle (gc3, area);
	gdk_gc_set_clip_rectangle (gc4, area);
    }

    if (fill)
	gdk_draw_polygon (window, style->bg_gc[state_type], TRUE, points,
			  npoints);

    npoints--;

    for (i = 0; i < npoints; i++)
    {
	if ((points[i].x == points[i + 1].x) &&
	    (points[i].y == points[i + 1].y))
	{
	    angle = 0;
	}
	else
	{
	    angle = atan2 (points[i + 1].y - points[i].y,
			   points[i + 1].x - points[i].x);
	}

	if ((angle > -pi_3_over_4) && (angle < pi_over_4))
	{
	    if (angle > -pi_over_4)
	    {
		xadjust = 0;
		yadjust = 1;
	    }
	    else
	    {
		xadjust = 1;
		yadjust = 0;
	    }

	    gdk_draw_line (window, gc1,
			   points[i].x - xadjust, points[i].y - yadjust,
			   points[i + 1].x - xadjust,
			   points[i + 1].y - yadjust);
	    gdk_draw_line (window, gc3, points[i].x, points[i].y,
			   points[i + 1].x, points[i + 1].y);
	}
	else
	{
	    if ((angle < -pi_3_over_4) || (angle > pi_3_over_4))
	    {
		xadjust = 0;
		yadjust = 1;
	    }
	    else
	    {
		xadjust = 1;
		yadjust = 0;
	    }

	    gdk_draw_line (window, gc4,
			   points[i].x + xadjust, points[i].y + yadjust,
			   points[i + 1].x + xadjust,
			   points[i + 1].y + yadjust);
	    gdk_draw_line (window, gc2, points[i].x, points[i].y,
			   points[i + 1].x, points[i + 1].y);
	}
    }
    if (area)
    {
	gdk_gc_set_clip_rectangle (gc1, NULL);
	gdk_gc_set_clip_rectangle (gc2, NULL);
	gdk_gc_set_clip_rectangle (gc3, NULL);
	gdk_gc_set_clip_rectangle (gc4, NULL);
    }
}

void
draw_arrow (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail,
	    GtkArrowType arrow_type,
	    gint fill, gint x, gint y, gint width, gint height)
{
    eazel_theme_data *theme_data;

    /* FIXME GNOME2: bad hack added to make arrows draw large enough */
    width = width + 6;
    height = height + 6;
    x = x - 3;
    y = y - 3;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    debug ("draw_arrow: detail=%s state=%d shadow=%d arrow_type=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, arrow_type, x, y, width, height);

    if (DETAIL ("vscrollbar") || DETAIL ("hscrollbar"))
    {
	int type = 0;
	switch (arrow_type)
	{
	case GTK_ARROW_UP:
	    type = EAZEL_ENGINE_ARROW_UP;
	    break;

	case GTK_ARROW_DOWN:
	    type = EAZEL_ENGINE_ARROW_DOWN;
	    break;

	case GTK_ARROW_LEFT:
	    type = EAZEL_ENGINE_ARROW_LEFT;
	    break;

	case GTK_ARROW_RIGHT:
	    type = EAZEL_ENGINE_ARROW_RIGHT;
	    break;
	}

	type += (state_type == GTK_STATE_ACTIVE ? 2
		 : state_type == GTK_STATE_PRELIGHT ? 1 : 0);

	paint_stock_image (theme_data, type, TRUE, FALSE,
			   style, window, state_type,
			   area, widget, x, y, width, height);
    }
    else if (DETAIL ("spinbutton"))
    {
	int window_width, window_height;
	int tem_x, tem_y;

	if (widget != 0 && !GTK_WIDGET_IS_SENSITIVE (widget))
	    state_type = GTK_STATE_INSENSITIVE;

	gdk_window_get_size (window, &window_width, &window_height);

	if (state_type != GTK_STATE_INSENSITIVE)
	{
	    draw_box (style, window, state_type, shadow_type,
		      area, widget, detail,
		      x, y - (arrow_type == GTK_ARROW_DOWN),
		      width, height + 1);
	}

	/*
	  else if (arrow_type == GTK_ARROW_UP)
	  {
	  XXX A hack, assumes that up arrow is drawn before
	  XXX down arrow. (Currently it is)
	  
	  draw_shadow (style, window, GTK_STATE_NORMAL, GTK_SHADOW_OUT,
	  NULL, widget, "entry", x - 2, 0,
	  width + 4, window_height);
	  }
	*/

	tem_x = x + (width / 2);
	tem_y = y + (height / 2);
	if (arrow_type == GTK_ARROW_UP)
	{
	    int i;
	    tem_y--;
	    for (i = 0; i < 4; i++)
	    {
		gdk_draw_line (window, style->fg_gc[state_type],
			       tem_x - i, tem_y + i, 
			       tem_x + i, tem_y + i);
	    }
	}
	else
	{
	    int i;
	    tem_y -= 2;
	    for (i = 0; i < 4; i++)
	    {
		gdk_draw_line (window, style->fg_gc[state_type],
			       tem_x - i, tem_y + (4 - i),
			       tem_x + i, tem_y + (4 - i));
	    }
	}
	if (state_type != GTK_STATE_INSENSITIVE)
	{
	  draw_shadow (style, window, GTK_STATE_NORMAL, GTK_SHADOW_OUT,
		       NULL, widget, "entry", x - 2, 0,
		       width + 4, window_height);
	}
    }
    else
    {
	if (widget != 0 && !GTK_WIDGET_IS_SENSITIVE (widget))
	    state_type = GTK_STATE_INSENSITIVE;

	paint_arrow (window, style->fg_gc[state_type],
		     arrow_type, x, y, width, height);
    }
}

void
draw_diamond (GtkStyle *style,
	      GdkWindow *window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle *area,
	      GtkWidget *widget,
	      const gchar *detail, gint x, gint y, gint width, gint height)
{
    gint half_width;
    gint half_height;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_diamond: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    half_width = width / 2;
    half_height = height / 2;

    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->black_gc, area);
    }
    switch (shadow_type)
    {
    case GTK_SHADOW_IN:
	gdk_draw_line (window, style->light_gc[state_type],
		       x + 2, y + half_height,
		       x + half_width, y + height - 2);
	gdk_draw_line (window, style->light_gc[state_type],
		       x + half_width, y + height - 2,
		       x + width - 2, y + half_height);
	gdk_draw_line (window, style->light_gc[state_type],
		       x + 1, y + half_height,
		       x + half_width, y + height - 1);
	gdk_draw_line (window, style->light_gc[state_type],
		       x + half_width, y + height - 1,
		       x + width - 1, y + half_height);
	gdk_draw_line (window, style->light_gc[state_type],
		       x, y + half_height, x + half_width, y + height);
	gdk_draw_line (window, style->light_gc[state_type],
		       x + half_width, y + height,
		       x + width, y + half_height);

	gdk_draw_line (window, style->dark_gc[state_type],
		       x + 2, y + half_height, x + half_width, y + 2);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + half_width, y + 2, x + width - 2, y + half_height);
	gdk_draw_line (window, style->dark_gc[state_type], x + 1,
		       y + half_height, x + half_width, y + 1);
	gdk_draw_line (window, style->dark_gc[state_type], x + half_width,
		       y + 1, x + width - 1, y + half_height);
	gdk_draw_line (window, style->dark_gc[state_type], x,
		       y + half_height, x + half_width, y);
	gdk_draw_line (window, style->dark_gc[state_type], x + half_width,
		       y, x + width, y + half_height);
	break;
    case GTK_SHADOW_OUT:
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + 2, y + half_height,
		       x + half_width, y + height - 2);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + half_width, y + height - 2,
		       x + width - 2, y + half_height);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + 1, y + half_height,
		       x + half_width, y + height - 1);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + half_width, y + height - 1,
		       x + width - 1, y + half_height);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x, y + half_height, x + half_width, y + height);
	gdk_draw_line (window, style->dark_gc[state_type],
		       x + half_width, y + height,
		       x + width, y + half_height);

	gdk_draw_line (window, style->light_gc[state_type],
		       x + 2, y + half_height, x + half_width, y + 2);
	gdk_draw_line (window, style->light_gc[state_type],
		       x + half_width, y + 2, x + width - 2, y + half_height);
	gdk_draw_line (window, style->light_gc[state_type], x + 1,
		       y + half_height, x + half_width, y + 1);
	gdk_draw_line (window, style->light_gc[state_type], x + half_width,
		       y + 1, x + width - 1, y + half_height);
	gdk_draw_line (window, style->light_gc[state_type], x,
		       y + half_height, x + half_width, y);
	gdk_draw_line (window, style->light_gc[state_type], x + half_width,
		       y, x + width, y + half_height);
	break;
    default:
	break;
    }
    if (area)
    {
	gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->black_gc, NULL);
    }
}

void
draw_oval (GtkStyle *style,
	   GdkWindow *window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle *area,
	   GtkWidget *widget,
	   const gchar *detail, gint x, gint y, gint width, gint height)
{
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
}

void
draw_string (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, const gchar *string)
{
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_string: detail=%s state=%d x=%d y=%d\n",
	    detail, state_type, x, y);

    if (area)
    {
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (style->fg_gc[state_type], area);
    }

    /* FIXME GNOME2
    if (state_type == GTK_STATE_INSENSITIVE)
	gdk_draw_string (window, style->font, style->white_gc, x + 1, y + 1,
			 string);
    gdk_draw_string (window, style->font, style->fg_gc[state_type], x, y,
		     string);
    */
    if (area)
    {
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (style->fg_gc[state_type], NULL);
    }
}

void
draw_flat_box (GtkStyle *style,
	       GdkWindow *window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle *area,
	       GtkWidget *widget,
	       const gchar *detail, gint x, gint y, gint width, gint height)
{
    GdkGC *gc1;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    debug ("draw_flat_box: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    gc1 = style->bg_gc[state_type];

    if (DETAIL ("text") && (state_type == GTK_STATE_SELECTED))
	gc1 = style->bg_gc[GTK_STATE_SELECTED];
    else if (DETAIL ("viewportbin"))
	gc1 = style->bg_gc[GTK_STATE_NORMAL];
    else if (DETAIL ("entry_bg"))
	gc1 = style->white_gc;

    if ((!style->bg_pixmap[state_type])
	|| (gc1 != style->bg_gc[state_type])
	/* FIXME GNOME2 || (gdk_window_get_type (window) == GDK_WINDOW_PIXMAP)*/ )
    {
	if (area)
	{
	    gdk_gc_set_clip_rectangle (gc1, area);
	}
	gdk_draw_rectangle (window, gc1, TRUE, x, y, width, height);
	if ((detail) && (!strcmp ("tooltip", detail)))
	    gdk_draw_rectangle (window, style->black_gc, FALSE,
				x, y, width - 1, height - 1);
	if (area)
	{
	    gdk_gc_set_clip_rectangle (gc1, NULL);
	}
    }
    else
	gtk_style_apply_default_pixmap (style, window, state_type, area, x,
					y, width, height);
}

static void
paint_check (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, gint width, gint height,
	     eazel_engine_stock_image stock_base)
{
    eazel_engine_stock_image type;
    gboolean active = (shadow_type != GTK_SHADOW_OUT);
    gboolean has_focus = (widget != 0 && GTK_WIDGET_HAS_FOCUS (widget));
    gboolean menu_item = (widget != 0 && gtk_widget_get_ancestor (widget, GTK_TYPE_MENU_ITEM));

    eazel_theme_data *theme_data;

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    if (GTK_IS_TREE_VIEW (widget)) {
      has_focus = FALSE;
    }

    if (DETAIL ("checkbutton") || DETAIL ("radiobutton"))
    {
	/* correct for braindeath in gtk_real_check_button_draw_indicator */
	if (widget != 0 && GTK_IS_TOGGLE_BUTTON (widget))
	    active = GTK_TOGGLE_BUTTON (widget)->active;
	if (widget != 0)
	{
	    state_type = GTK_WIDGET_STATE (widget);
	    /* XXX the widget gives us no way to tell between
	       XXX checked, and checked-and-clicked states.. */
	    if (active && state_type == GTK_STATE_ACTIVE)
		state_type = GTK_STATE_NORMAL;
	}
    }

    if (!menu_item)
    {
	switch (state_type)
	{
	case GTK_STATE_INSENSITIVE:
	    type = (!active ? EAZEL_ENGINE_CHECK_DISABLED
		    : EAZEL_ENGINE_CHECK_ACTIVE_DISABLED);
	    break;

	case GTK_STATE_PRELIGHT:
	    type = (active
		    ? (has_focus ? EAZEL_ENGINE_CHECK_ACTIVE_HI_FOCUS
		       : EAZEL_ENGINE_CHECK_ACTIVE_HI)
		    : (has_focus ? EAZEL_ENGINE_CHECK_HI_FOCUS
		       : EAZEL_ENGINE_CHECK_HI));
	    break;

	case GTK_STATE_ACTIVE:
	    type = (active
		    ? (has_focus ? EAZEL_ENGINE_CHECK_ACTIVE_PRESSED_FOCUS
		       : EAZEL_ENGINE_CHECK_ACTIVE)
		    : (has_focus ? EAZEL_ENGINE_CHECK_PRESSED_FOCUS
		       : EAZEL_ENGINE_CHECK_PRESSED));
	    break;

	default:
	    type = (active
		    ? (has_focus ? EAZEL_ENGINE_CHECK_ACTIVE_FOCUS
		       : EAZEL_ENGINE_CHECK_ACTIVE)
		    : (has_focus ? EAZEL_ENGINE_CHECK_FOCUS
		       : EAZEL_ENGINE_CHECK));
	}

	paint_stock_image (theme_data, type + stock_base,
			   FALSE, FALSE, style, window,
			   state_type, area, widget,
			   x-3, y-3, width+6, height+6);
    }
    else
    {
	if (!active)
	    return;

	if (stock_base == EAZEL_ENGINE_CHECK)
	{
	    paint_tick (window, style->fg_gc[state_type],
			x + width / 2, y + width / 2);
	}
	else
	{
	    paint_bullet (window, style->fg_gc[state_type],
			  x + width / 2, y + width / 2);
	}
    }
}

void
draw_check (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, gint x, gint y, gint width, gint height)
{
    paint_check (style, window, state_type, shadow_type, area,
		 widget, detail, x, y, width, height, EAZEL_ENGINE_CHECK);
}

void
draw_option (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail, gint x, gint y, gint width, gint height)
{
    paint_check (style, window, state_type, shadow_type, area,
		 widget, detail, x, y, width, height, EAZEL_ENGINE_OPTION);
}

void
draw_cross (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, gint x, gint y, gint width, gint height)
{
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
}

void
draw_ramp (GtkStyle *style,
	   GdkWindow *window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle *area,
	   GtkWidget *widget,
	   const gchar *detail,
	   GtkArrowType arrow_type, gint x, gint y, gint width, gint height)
{
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
}

void
draw_tab (GtkStyle *style,
	  GdkWindow *window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle *area,
	  GtkWidget *widget,
	  const gchar *detail, gint x, gint y, gint width, gint height)
{
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    gtk_paint_box (style, window, state_type, shadow_type, area, widget,
		   detail, x, y, width, height);
}

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
		 GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkRectangle rect;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_shadow_gap: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    gtk_paint_shadow (style, window, state_type, shadow_type, area, widget,
		      detail, x, y, width, height);

    switch (gap_side)
    {
    case GTK_POS_TOP:
	rect.x = x + gap_x;
	rect.y = y;
	rect.width = gap_width;
	rect.height = 2;
	break;
    case GTK_POS_BOTTOM:
	rect.x = x + gap_x;
	rect.y = y + height - 2;
	rect.width = gap_width;
	rect.height = 2;
	break;
    case GTK_POS_LEFT:
	rect.x = x;
	rect.y = y + gap_x;
	rect.width = 2;
	rect.height = gap_width;
	break;
    case GTK_POS_RIGHT:
	rect.x = x + width - 2;
	rect.y = y + gap_x;
	rect.width = 2;
	rect.height = gap_width;
	break;
    }

    gtk_style_apply_default_pixmap (style, window, state_type, area,
				    rect.x, rect.y, rect.width, rect.height);
}

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
	      GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkRectangle rect;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_box_gap: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    gtk_paint_box (style, window, state_type, shadow_type, area, widget,
		   detail, x, y, width, height);

    /* XXX Eavel hack to prevent a hole being draw when the
       XXX active tab is on the far left */
    if (gap_x < 1)
    {
	gap_width -= (1 - gap_x);
	gap_x = 1;
    }

    switch (gap_side)
    {
    case GTK_POS_TOP:
	rect.x = x + gap_x;
	rect.y = y;
	rect.width = gap_width;
	rect.height = 2;
	break;
    case GTK_POS_BOTTOM:
	rect.x = x + gap_x;
	rect.y = y + height - 2;
	rect.width = gap_width;
	rect.height = 2;
	break;
    case GTK_POS_LEFT:
	rect.x = x;
	rect.y = y + gap_x;
	rect.width = 2;
	rect.height = gap_width;
	break;
    case GTK_POS_RIGHT:
	rect.x = x + width - 2;
	rect.y = y + gap_x;
	rect.width = 2;
	rect.height = gap_width;
	break;
    }

    gtk_style_apply_default_pixmap (style, window, state_type, area,
				    rect.x, rect.y, rect.width, rect.height);
}

void
draw_extension (GtkStyle *style,
		GdkWindow *window,
		GtkStateType state_type,
		GtkShadowType shadow_type,
		GdkRectangle *area,
		GtkWidget *widget,
		const gchar *detail,
		gint x,
		gint y, gint width, gint height, GtkPositionType gap_side)
{
    GdkRectangle rect;

    eazel_theme_data *theme_data;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    debug ("draw_extension: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);


    if (DETAIL ("tab"))
    {
	eazel_engine_stock_image type = 0;
	switch (gap_side)
	{
	case GTK_POS_TOP:
	    type = ((state_type != GTK_STATE_ACTIVE)
		    ? EAZEL_ENGINE_TAB_BOTTOM_ACTIVE
		    : (x < 10) ? EAZEL_ENGINE_TAB_BOTTOM_LEFT
		    : EAZEL_ENGINE_TAB_BOTTOM);
	    break;

	case GTK_POS_BOTTOM:
	    type = ((state_type != GTK_STATE_ACTIVE)
		    ? EAZEL_ENGINE_TAB_TOP_ACTIVE
		    : (x < 10) ? EAZEL_ENGINE_TAB_TOP_LEFT
		    : EAZEL_ENGINE_TAB_TOP);
	    break;

	default:			/* gcc drugging */
	}
	paint_background_area (style, window, state_type, area,
			       x, y, width, height);
	if (type != 0)
	{
	    paint_stock_image (theme_data, type, TRUE, FALSE, style, window,
			       state_type, area, widget, x, y, width, height);
	    return;
	}
    }

    gtk_paint_box (style, window, state_type, shadow_type, area, widget,
		   detail, x, y, width, height);

    switch (gap_side)
    {
    case GTK_POS_TOP:
	rect.x = x + style->xthickness;
	rect.y = y;
	rect.width = width - style->xthickness * 2;
	rect.height = style->ythickness;
	break;
    case GTK_POS_BOTTOM:
	rect.x = x + style->xthickness;
	rect.y = y + height - style->ythickness;
	rect.width = width - style->xthickness * 2;
	rect.height = style->ythickness;
	break;
    case GTK_POS_LEFT:
	rect.x = x;
	rect.y = y + style->ythickness;
	rect.width = style->xthickness;
	rect.height = height - style->ythickness * 2;
	break;
    case GTK_POS_RIGHT:
	rect.x = x + width - style->xthickness;
	rect.y = y + style->ythickness;
	rect.width = style->xthickness;
	rect.height = height - style->ythickness * 2;
	break;
    }

    gtk_style_apply_default_pixmap (style, window, state_type, area,
				    rect.x, rect.y, rect.width, rect.height);
}

void
draw_focus (GtkStyle *style,
	    GdkWindow *window,
	    GtkStateType state_type,
	    GdkRectangle *area,
	    GtkWidget *widget,
	    const gchar *detail, gint x, gint y, gint width, gint height)
{
    eazel_theme_data *theme_data;
    gboolean rounded = TRUE, rounded_inner = TRUE;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    debug ("draw_focus: detail=%s x=%d y=%d w=%d h=%d\n",
	    detail, x, y, width, height);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((DETAIL ("button") && widget != 0
	 && GTK_IS_BUTTON (widget) && GTK_WIDGET_HAS_DEFAULT (widget))
	|| DETAIL ("checkbutton") || DETAIL ("option") || DETAIL ("slider")
	|| (widget != 0 && GTK_IS_SCALE (widget))
	/* XXX reenable me */
	|| DETAIL ("tab"))
    {
	return;
    }

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    if (area)
	gdk_gc_set_clip_rectangle (style->black_gc, area);

    if (DETAIL ("button"))
    {
	x--; y--;
	width += 2; height += 2;
    }
    else if (DETAIL ("text") || DETAIL ("entry"))
    {
	rounded_inner = FALSE;
    }

    paint_focus_box (theme_data, window, style->black_gc,
		     rounded, rounded_inner, theme_data->focus_thickness,
		     x, y, width, height);

    if (area)
	gdk_gc_set_clip_rectangle (style->black_gc, NULL);
}

void
draw_slider (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation)
{
    eazel_theme_data *theme_data;
    gboolean focused;
    
    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    theme_data = CRUX_RC_STYLE (style->rc_style)->theme_data;
    g_assert (theme_data != NULL);

    debug ("draw_slider: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	    detail, state_type, shadow_type, x, y, width, height);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    if (area)
	gdk_gc_set_clip_rectangle (style->black_gc, area);

    focused = (widget != 0) && eazel_engine_widget_in_focused_window_p (widget);

    if (DETAIL ("slider")) {
	{
	    int thumb_x, thumb_y;
	    gboolean focused;

	    focused = eazel_engine_widget_in_focused_window_p (widget);

	    /* XXX could be a gradient? */
	    paint_stock_image (theme_data,
			       width > height
			       ? (state_type == GTK_STATE_PRELIGHT
				  ? EAZEL_ENGINE_H_SCROLLBAR_HI
				  : !focused
				  ? EAZEL_ENGINE_H_SCROLLBAR_INACTIVE
				  : EAZEL_ENGINE_H_SCROLLBAR)
			       : (state_type == GTK_STATE_PRELIGHT
				  ? EAZEL_ENGINE_V_SCROLLBAR_HI
				  : !focused
				  ? EAZEL_ENGINE_V_SCROLLBAR_INACTIVE
				  : EAZEL_ENGINE_V_SCROLLBAR),
			       TRUE, FALSE, style, window, state_type, area,
			       widget, x, y, width, height);
	    if (width > height)
	      {
	      /* XXX `4' is 1/2 width of thumb */
	      thumb_x = x + width / 2 - 4;
		thumb_y = y;
	    }
	    else
	      {
	      thumb_x = x;
		/* XXX `4' is 1/2 height of thumb */
		thumb_y = y + height / 2 - 4;
	    }
	    
	    paint_stock_image (theme_data,
			       width > height
			       ? (state_type == GTK_STATE_PRELIGHT
				  ? EAZEL_ENGINE_H_SCROLLBAR_THUMB_HI
				  : !focused
				  ? EAZEL_ENGINE_H_SCROLLBAR_THUMB_INACTIVE
				  : EAZEL_ENGINE_H_SCROLLBAR_THUMB)
			       : (state_type == GTK_STATE_PRELIGHT
				  ? EAZEL_ENGINE_V_SCROLLBAR_THUMB_HI
				  : !focused
				  ? EAZEL_ENGINE_V_SCROLLBAR_THUMB_INACTIVE
				  : EAZEL_ENGINE_V_SCROLLBAR_THUMB),
			       FALSE, FALSE, style, window, state_type, area,
			       widget, thumb_x, thumb_y, -1, -1);
	}
    } else {
      paint_stock_image (theme_data,
			 orientation == GTK_ORIENTATION_HORIZONTAL
			 ? (focused ? EAZEL_ENGINE_H_SLIDER_THUMB
			    : EAZEL_ENGINE_H_SLIDER_THUMB_INACTIVE)
			 : (focused ? EAZEL_ENGINE_V_SLIDER_THUMB
			    : EAZEL_ENGINE_V_SLIDER_THUMB_INACTIVE),
			 TRUE, TRUE, style, window, state_type,
			 area, widget, x, y, width, height);
    }
    if (area)
	gdk_gc_set_clip_rectangle (style->black_gc, NULL);

}

void
draw_handle (GtkStyle *style,
	     GdkWindow *window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle *area,
	     GtkWidget *widget,
	     const gchar *detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation)
{
    gint i, yy, xx;
    gint xthick, ythick;
    GdkGC *light_gc, *dark_gc;
    GdkRectangle dest;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);

    debug ("draw_handle: detail=%s state=%d shadow=%d x=%d y=%d w=%d h=%d\n",
	   detail, state_type, shadow_type, x, y, width, height);

    /* Protection against broken GTK+ widgets */
    g_return_if_fail (width < 32768);
    g_return_if_fail (height < 32768);
    g_return_if_fail (width >= -1);
    g_return_if_fail (height >= -1);

    if ((width == -1) && (height == -1))
	gdk_window_get_size (window, &width, &height);
    else if (width == -1)
	gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
	gdk_window_get_size (window, NULL, &height);

    if (DETAIL ("dockitem") && state_type == GTK_STATE_NORMAL)
	state_type = GTK_STATE_ACTIVE;

    gtk_paint_box (style, window, state_type, shadow_type, area, widget,
		   detail, x, y, width, height);

    light_gc = style->light_gc[state_type];
    dark_gc = style->dark_gc[state_type];

    xthick = style->xthickness;
    ythick = style->ythickness;

    dest.x = x + xthick;
    dest.y = y + ythick;
    dest.width = width - (xthick * 2);
    dest.height = height - (ythick * 2);

    gdk_gc_set_clip_rectangle (light_gc, &dest);
    gdk_gc_set_clip_rectangle (dark_gc, &dest);

    /* ORIENTATION parameters is unreliable */
    if (height > width)
    {
	yy = y + height / 2 - 5;
	for (i = 0; i < 10; i += 2)
	{
	    gdk_draw_line (window, dark_gc, xthick, yy + i,
			   x + width - xthick, yy + i);
	    gdk_draw_line (window, light_gc, xthick, yy + i + 1,
			   x + width - xthick, yy + i + 1);
	}
    }
    else
    {
	xx = x + width / 2 - 5;
	for (i = 0; i < 10; i += 2)
	{
	    gdk_draw_line (window, dark_gc, xx + i, ythick,
			   xx + i, y + height - ythick);
	    gdk_draw_line (window, light_gc, xx + i + 1, ythick,
			   xx + i + 1, y + height - ythick);
	}
    }

    gdk_gc_set_clip_rectangle (light_gc, NULL);
    gdk_gc_set_clip_rectangle (dark_gc, NULL);
}
