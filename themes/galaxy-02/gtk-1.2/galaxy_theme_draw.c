/*  galaxy
 *  Copyright (C) 2003 Frederic Crozat - MandrakeSoft
 *                1999 Olivier Fourdan (fourdan@xfce.org) for XFCE code
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <math.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <string.h>

#include "galaxy.h"

#define DETAIL(s)   ((detail) && (!strcmp(s, detail)))


static GtkStyleClass *parent_class;

#define PART_SIZE 13
#define SCALE_SIZE 5

static const guchar check_cross_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0xb8, 0x03, 0xf0, 0x01,
    0xe0, 0x00, 0xf0, 0x01, 0xb8, 0x03, 0x18, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

static unsigned char radio_text_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,0xf0,0x01,0xf0,0x01,0xf0,
 0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

static const guchar menu_check_bits[] = {
  0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x07,0x84,0x07,0xcc,0x03,0xfc,0x01,0xfc,
  0x00,0x78,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


/* internal functions */
static void draw_hline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x1, gint x2, gint y);
static void draw_vline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint y1, gint y2, gint x);
static void draw_shadow(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height);

static void draw_polygon(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, GdkPoint * point, gint npoints, gint fill);
static void draw_diamond(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height);
static void draw_box(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height);
static void draw_check(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height);
static void draw_option(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height);
static void draw_shadow_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_box_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_extension(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side);
static void draw_slider(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);
static void draw_handle(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);


static gboolean 
sanitize_size (GdkWindow      *window,
	       gint           *width,
	       gint           *height)
{
  gboolean set_bg = FALSE;

  if ((*width == -1) && (*height == -1))
    {
      gdk_window_get_size (window, width, height);
    }
  else if (*width == -1)
    gdk_window_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_window_get_size (window, NULL, height);

  return set_bg;
}


typedef struct _GtkBorder      GtkBorder;
struct _GtkBorder
{
  gint left;
  gint right;
  gint top;
  gint bottom;
};

static GtkRequisition default_option_indicator_size = { 7, 13 };
static GtkBorder default_option_indicator_spacing = { 7, 5, 2, 2 };

static void
option_menu_get_props (GtkWidget      *widget,
		       GtkRequisition *indicator_size,
		       GtkBorder      *indicator_spacing)
{
  GtkRequisition *tmp_size = NULL;
  GtkBorder *tmp_spacing = NULL;
  
  if (tmp_size)
    {
      *indicator_size = *tmp_size;
      g_free (tmp_size);
    }
  else
    *indicator_size = default_option_indicator_size;

  if (tmp_spacing)
    {
      *indicator_spacing = *tmp_spacing;
      g_free (tmp_spacing);
    }
  else
    *indicator_spacing = default_option_indicator_spacing;
}

void
gdk_rgb_find_color (GdkColormap *colormap, GdkColor *color)
{
  color->pixel = gdk_rgb_xpixel_from_rgb (((color->red >> 8) << 16) |
					  ((color->green >> 8) << 8) |
					  (color->blue >> 8));
}


static void
draw_vgradient (GdkDrawable *drawable, GdkGC *gc, GdkColormap *colormap,
		int x, int y, int width, int height,
		GdkColor *top_color, GdkColor *bottom_color)
{
  int i;
  GdkColor col;
  int dr, dg, db;
  GdkGCValues old_values;

  col = *top_color;
  dr = (bottom_color->red - top_color->red) / height;
  dg = (bottom_color->green - top_color->green) / height;
  db = (bottom_color->blue - top_color->blue) / height;
  
  gdk_gc_get_values (gc, &old_values);
  
  for (i = 0; i < height; i++)
    {
      gdk_rgb_find_color (colormap,
			  &col);
      
      gdk_gc_set_foreground (gc, &col);
      gdk_draw_line (drawable, gc,
		     x, y + i,
		     x + width - 1, y + i);
					   
      col.red += dr;
      col.green += dg;
      col.blue += db;
    }

  gdk_gc_set_foreground (gc, &old_values.foreground);
}


static void
draw_hgradient (GdkDrawable *drawable, GdkGC *gc, GdkColormap *colormap,
		int x, int y, int width, int height,
		GdkColor *left_color, GdkColor *right_color)
{
  int i;
  GdkColor col;
  int dr, dg, db;
  GdkGCValues old_values;

  col = *left_color;
  dr = (right_color->red - left_color->red) / width;
  dg = (right_color->green - left_color->green) / width;
  db = (right_color->blue - left_color->blue) / width;
  
  gdk_gc_get_values (gc, &old_values);
  
  for (i = 0; i < width; i++)
    {
      gdk_rgb_find_color (colormap,
			  &col);
      
      gdk_gc_set_foreground (gc, &col);
      gdk_draw_line (drawable, gc,
		     x + i, y,
		     x + i, y + height - 1);
					   
      col.red += dr;
      col.green += dg;
      col.blue += db;
    }

  gdk_gc_set_foreground (gc, &old_values.foreground);
}

static void galaxy_draw_point (GalaxyData * galaxy_data, GdkWindow * window, gint x, gint y) {

    gdk_draw_point(window, galaxy_data->gray_gc[7],x+1,y);
    gdk_draw_point(window, galaxy_data->gray_gc[7],x+2,y);
    gdk_draw_point(window, galaxy_data->gray_gc[7],x,y+1);
    gdk_draw_point(window, galaxy_data->gray_gc[7],x+1,y+1);
    
    gdk_draw_point(window, galaxy_data->gray_gc[4],x+2,y+1);
    gdk_draw_point(window, galaxy_data->gray_gc[4],x+3,y+1);
    gdk_draw_point(window, galaxy_data->gray_gc[4],x+1,y+2);
    
    gdk_draw_point(window, galaxy_data->gray_gc[2],x,y+2);
    gdk_draw_point(window, galaxy_data->gray_gc[2],x+1,y+3);
    gdk_draw_point(window, galaxy_data->gray_gc[2],x+3,y+3);
    
    gdk_draw_point(window, galaxy_data->gray_gc[0],x+2,y+2);
    gdk_draw_point(window, galaxy_data->gray_gc[0],x+2,y+3); 
}

static void galaxy_draw_handlers(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, char *detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
    GalaxyData *galaxy_data = style->engine_data;

    int i;
    int delta;
    gint xthick, ythick;
    GdkRectangle dest;

    sanitize_size (window, &width, &height);

    xthick = style->klass->xthickness;
    ythick = style->klass->ythickness;

    if (detail && (!strcmp (detail, "paned") || !strcmp (detail+1, "paned"))) {
      /* we want to ignore the shadow border in paned widgets */
      xthick = 0;
      ythick = 0;
    }

    dest.x = x + xthick;
    dest.y = y + ythick;
    dest.width = width - (xthick * 2);
    dest.height = height - (ythick * 2);

    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[7], &dest);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[4], &dest);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], &dest);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[0], &dest);

    if(orientation == GTK_ORIENTATION_HORIZONTAL) {
        if(width > 30)
        {
            delta = x + (width/2) - 11;
            for(i = 0; i < 3; i++) {
	      galaxy_draw_point (galaxy_data, window, delta + 9*i,
				 y + MAX((height-4)/2,0));
            }
        }
	else {
	  galaxy_draw_point (galaxy_data, window,  x + (width-4)/2,
				 y + MAX((height-4)/2,0));
	}
    }
    else {
        if(height > 30) {
	  delta = y + (height / 2) - 11;
            for(i = 0; i < 3; i++) {
	      galaxy_draw_point (galaxy_data, window, x + MAX((width-4)/2,0), 
				 delta+9*i);
            }
        }
	else {
	  galaxy_draw_point (galaxy_data, window, x + MAX((width-4)/2,0), 
			      y + (height-4) / 2);
	}
    }
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[7], NULL);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[4], NULL);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], NULL);
    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[0], NULL);
}

static void draw_hline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x1, gint x2, gint y)
{
    GalaxyData *galaxy_data = style->engine_data;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], area);
        gdk_gc_set_clip_rectangle(style->white_gc, area);
    }

    gdk_draw_line(window, galaxy_data->gray_gc[2], x1, y, x2, y);
    gdk_draw_line(window, style->white_gc, x1, y + 1, x2, y+1);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle(style->white_gc, NULL);
    }
}

static void draw_vline(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint y1, gint y2, gint x)
{
    GalaxyData *galaxy_data = style->engine_data;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], area);
        gdk_gc_set_clip_rectangle(style->white_gc, area);
    }

    gdk_draw_line(window, galaxy_data->gray_gc[2], x, y1, x, y2);
    gdk_draw_line(window, style->white_gc, x+1, y1, x+1, y2);

    if(area)
    {
        gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle(style->white_gc, NULL);
    }
}

static void draw_shadow(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height)
{
  GalaxyData *galaxy_data = style->engine_data;
  GdkGC *gc1, *gc2;
  int xthick, ythick;
  gboolean is_combo_button;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    if (shadow_type == GTK_SHADOW_NONE) {
      return;
    }
    xthick = style->klass->xthickness;
    ythick = style->klass->ythickness;

    sanitize_size (window, &width, &height);

    if(area)
    { 
        gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[0], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[1], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[2], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[3], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[7], area);
    }

    if (is_combo_button = (DETAIL("button") && (GTK_IS_COMBO(widget->parent)))) {
      xthick = ythick = 1;
    }


    if (DETAIL ("buttondefault")) {
      x += 5;
      y += 5;
      width -= 9;
      height -= 9;
    }

    if ((DETAIL ("button") ||
	(DETAIL ("togglebutton")) ||
	(DETAIL ("buttondefault")) ||
	 (DETAIL ("optionmenu")))
	&& (galaxy_data->enable_gradient)
	&& (!is_combo_button)
	&& (xthick >= 3)
	&& (ythick >= 3)) /* Button, Combobox */
      {
	int color1;
	switch (shadow_type) {
	case GTK_SHADOW_IN:
	  color1 = 7;
	  break;
	case GTK_SHADOW_OUT:
	  color1 = 5;
	  break;
	default:
	  color1 = 0;
	}
	
	if (color1 != 0) {
	  gdk_draw_point (window, galaxy_data->gray_gc[color1],x+3,y+3);
	  gdk_draw_line (window, galaxy_data->gray_gc[color1], x+4,y+2,x+width-5,y+2);
	  gdk_draw_line (window,galaxy_data->gray_gc[color1], x+2,y+4,x+2,y+height-5);
	
	  gdk_draw_point (window, galaxy_data->gray_gc[5], x+width-4, y+3);
	  gdk_draw_line (window,galaxy_data->gray_gc[5], x+width-3,y+4,x+width-3,y+height-5);
	  gdk_draw_point (window, galaxy_data->gray_gc[5], x+width-4, y+height-4);
	  gdk_draw_line (window,galaxy_data->gray_gc[5], x+4,y+height-3,x+width-5,y+height-3);
	  gdk_draw_point (window, galaxy_data->gray_gc[5], x+3, y+height-4);	  

	}	
      }


    if ((shadow_type == GTK_SHADOW_ETCHED_IN) || 
	(shadow_type == GTK_SHADOW_ETCHED_OUT)) {
      if (shadow_type == GTK_SHADOW_ETCHED_IN) {
	gc1 = galaxy_data->gray_gc[5];
	gc2 = style->white_gc;
      }
      else { /*GTK_SHADOW_ETCHED_OUT */
	gc2 = galaxy_data->gray_gc[5];
	gc1 = style->white_gc;
      }
      gdk_draw_line (window, gc1, x,y,x+width-2,y);
      gdk_draw_line (window, gc1, x,y+1,x,y+height-2);
      gdk_draw_line (window, gc1, x+width-2,y+1,x+width-2,y+height-2);
      gdk_draw_line (window, gc1, x+1,y+height-2,x+width-3,y+height-2);
      
      gdk_draw_line (window, gc2, x+1,y+1,x+width-3,y+1);
      gdk_draw_line (window, gc2, x+width-1,y,x+width-1,y+height-1);
      gdk_draw_line (window, gc2, x,y+height-1,x+width-1,y+height-1);
      gdk_draw_line (window, gc2, x+1,y+2,x+1,y+height-3);
    }
    
    switch (shadow_type) {
        case GTK_SHADOW_IN:
	  if (is_combo_button) {	    
	     gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x+1,y+1,width-3,height-3);	     
	     gdk_draw_line (window, style->white_gc,x,y+2,x,y+height-2);
	     gdk_draw_point (window, galaxy_data->gray_gc[5],x,y+1);
	     gdk_draw_line (window, style->white_gc,x+width-1,y+1,x+width-1,y+height-1);
	     gdk_draw_line (window, galaxy_data->gray_gc[2],x,y,x+width-1,y);
	     gdk_draw_point (window, galaxy_data->gray_gc[0],x,y+height-2);
	     gdk_draw_line (window, style->white_gc,x+width-1,y,x+width-1,y+height-1);
	     gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	  } else
	  if (DETAIL ("button") ||
	      DETAIL ("togglebutton") || 
	      DETAIL ("buttondefault") ||
	      DETAIL ("optionmenu")) {
	    if ((xthick>=3) &&
		(ythick>=3) && (galaxy_data->enable_gradient) && !is_combo_button) {
	    /* white */
	    gdk_draw_line (window, style->white_gc, x+width-4,y+4,x+width-4,y+height-5);
	    gdk_draw_line (window, style->white_gc, x+4,y+height-4,x+width-5,y+height-4);
	    /* grey 3 */
	    gdk_draw_line (window, galaxy_data->gray_gc[3],x+4,y+1,x+width-6,y+1);
	    gdk_draw_point (window,galaxy_data->gray_gc[3],x+3,y+2);
	    gdk_draw_point (window,galaxy_data->gray_gc[3],x+2,y+3);
	    gdk_draw_line (window, galaxy_data->gray_gc[3],x+1,y+4,x+1,y+height-6);

	    /* grey 2 */

	    gdk_draw_point (window,galaxy_data->gray_gc[2],x+1,y+height-5);
	    gdk_draw_point (window,galaxy_data->gray_gc[2],x+width-5,y+1);
	    gdk_draw_point (window,galaxy_data->gray_gc[2],x+3,y+1);
	    gdk_draw_point (window,galaxy_data->gray_gc[2],x+2,y+2);
	    gdk_draw_point (window,galaxy_data->gray_gc[2],x+1,y+3);

	    }
	    else if ((xthick == 1) && (ythick == 1)) {
	      gdk_draw_rectangle (window, galaxy_data->gray_gc[7],FALSE,
				  x,y,width-1,height-1);	     
	      gdk_draw_line (window, style->white_gc, x+1, y+1, x+width-2,y+1);
	      gdk_draw_line (window, style->white_gc, x+1, y+2, x+1,y+height-2);
	    } else {
	      gdk_draw_line(window, galaxy_data->gray_gc[3], x + 1, y, x + width - 2, y);
	      gdk_draw_line(window, galaxy_data->gray_gc[3], x, y + 1, x, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_data->gray_gc[5], x + 1, y + height - 1, x + width - 2, y + height - 1);
	      gdk_draw_line(window, galaxy_data->gray_gc[5], x + width - 1, y + 1, x + width - 1, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y + 1, x + width - 2, y + 1);
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y + 1, x + 1, y + height - 2);
		
	      gdk_draw_line(window, style->white_gc, x + 2, y + height - 2, x + width - 2, y + height - 2);
	      gdk_draw_line(window, style->white_gc, x + width - 2, y + 2, x + width - 2, y + height - 2);
	      
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	    }
	  }
	  else if (DETAIL("trough") && !GTK_IS_RANGE(widget)) { /* progressbar */
	    gdk_draw_line (window, galaxy_data->gray_gc[5],x,y,x+width-1,y);
	    gdk_draw_line (window, galaxy_data->gray_gc[5],x,y+1,x,y+height-1);
	    gdk_draw_line (window, style->white_gc, x+width-1, y+1, x+width-1,y+height-1);
	    gdk_draw_line (window, style->white_gc, x+1,y+height-1,x+width-1, y+height-1);
	  }
	  else if (DETAIL ("spinbutton_up")) {	    
	     gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x,y+1,width-3,height-2);	     
	     gdk_draw_point (window, galaxy_data->gray_gc[5],x,y+1);
	     gdk_draw_point (window, style->white_gc,x+width-1,y);
	  } else if (DETAIL("spinbutton_down")) {
	    gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x,y,width-3,height-2);
	    gdk_draw_point (window, galaxy_data->gray_gc[0],x,y+height-2);
	  } else {
	      gdk_draw_line (window, galaxy_data->gray_gc[2], x,y,x+width-2,y);
	      gdk_draw_line (window, galaxy_data->gray_gc[2], x,y+1,x,y+height-2);

	      gdk_draw_line (window, style->white_gc, x+width-1,y,x+width-1,y+height-1);
	      gdk_draw_line (window, style->white_gc, x,y+height-1,x+width-1,y+height-1);
  
	      gdk_draw_line (window, galaxy_data->gray_gc[5], x+1,y+1,x+width-2,y+1);
	      gdk_draw_line (window, galaxy_data->gray_gc[5], x+1,y+2,x+1,y+height-2);

	      gdk_draw_line (window, galaxy_data->gray_gc[0], x+width-2,y+2,x+width-2,y+height-2);
	      gdk_draw_line (window, galaxy_data->gray_gc[0], x+2,y+height-2,x+width-3,y+height-2);    
	    }	  
	  break;
        case GTK_SHADOW_OUT:
	  if (is_combo_button) {
	     gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x+1,y+1,width-3,height-3);	     
	     gdk_draw_line (window, style->white_gc,x,y+2,x,y+height-2);
	     gdk_draw_point (window, galaxy_data->gray_gc[5],x,y+1);
	     gdk_draw_line (window, style->white_gc,x+width-1,y+1,x+width-1,y+height-1);
	     gdk_draw_line (window, galaxy_data->gray_gc[2],x,y,x+width-1,y);
	     gdk_draw_point (window, galaxy_data->gray_gc[0],x,y+height-2);
	     gdk_draw_line (window, style->white_gc,x+width-1,y,x+width-1,y+height-1);
	     gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	  } else
	  if (DETAIL ("button") || 
	      DETAIL ("togglebutton") || 
	      DETAIL ("togglebutton") || 
	      DETAIL ("optionmenu")) {
	    if ((xthick>=3) &&
		(ythick>=3) && galaxy_data->enable_gradient && !is_combo_button) {
	      if (state_type != GTK_STATE_INSENSITIVE) {
		/* white */	  		
		gdk_draw_line (window, style->white_gc, x+4,y+3,x+width-5,y+3);
		gdk_draw_line (window, style->white_gc, x+3,y+4,x+3,y+height-5);	  
	      /* grey 3 */

		gdk_draw_line (window, galaxy_data->gray_gc[3], x+width-2, y+5, x+width-2, y+height-5);
		gdk_draw_point (window, galaxy_data->gray_gc[3], x+width-3, y+height-4);
		gdk_draw_point (window, galaxy_data->gray_gc[3], x+width-4, y+height-3);
		gdk_draw_line (window, galaxy_data->gray_gc[3], x+5, y+height-2, x+width-5, y+height-2);
		
		/* grey 2 */
		gdk_draw_point(window,galaxy_data->gray_gc[2],x+4,y+height-2);
		gdk_draw_point(window,galaxy_data->gray_gc[2],x+width-4,y+height-2);
		gdk_draw_point(window,galaxy_data->gray_gc[2],x+width-3,y+height-3);
		gdk_draw_point(window,galaxy_data->gray_gc[2],x+width-2,y+height-4);
		gdk_draw_point(window,galaxy_data->gray_gc[2],x+width-2,y+4);
	      }
	      
	    } else if ((xthick == 1) && (ythick == 1)) {
	      gdk_draw_rectangle (window, galaxy_data->gray_gc[5],
				  FALSE,x,y,width-1,height-1);
	      gdk_draw_line (window, style->white_gc, x+1, y+1, x+width-2,y+1);
	      gdk_draw_line (window, style->white_gc, x+1, y+2, x+1,y+height-2);
	    } else  {
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y, x + width - 2, y);
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x, y + 1, x, y + height - 2);
	      
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y + height - 1, x + width - 2, y + height - 1);
	      gdk_draw_line(window, galaxy_data->gray_gc[7], x + width - 1, y + 1, x + width - 1, y + height - 2);
	      
	      gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	      gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);
	      
	      gdk_draw_line(window, galaxy_data->gray_gc[5], x + 1, y + height - 2, x + width - 2, y + height - 2);
	      gdk_draw_line(window, galaxy_data->gray_gc[5], x + width - 2, y + 1, x + width - 2, y + height - 2);
	      
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	      gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	    }
	  }
	  else if (DETAIL ("menu")) {
	    gdk_draw_line(window, galaxy_data->gray_gc[5], x, y, x + width - 1, y);
	    gdk_draw_line(window, galaxy_data->gray_gc[5], x, y, x, y + height - 1);

	    gdk_draw_line(window, galaxy_data->gray_gc[5], x + 1, y + height - 1, x + width - 1, y + height - 1);
	    gdk_draw_line(window, galaxy_data->gray_gc[5], x + width - 1, y + 1, x + width - 1, y + height - 1);

	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);

	    gdk_draw_line(window, galaxy_data->gray_gc[2], x + 1, y + height - 2, x + width - 2, y + height - 2);
	    gdk_draw_line(window, galaxy_data->gray_gc[2], x + width - 2, y + 1, x + width - 2, y + height - 2);
	  }
	  else if (DETAIL ("spinbutton_up")) {

	     gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x,y+1,width-2,height-2);	     
	     gdk_draw_line (window, style->white_gc,x+width-1,y+1,x+width-1,y+height-1);
	     gdk_draw_line (window, galaxy_data->gray_gc[2],x,y,x+width-1,y);
	  } else if (DETAIL("spinbutton_down")) {
	    gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
				x,y,width-2,height-2);
	    gdk_draw_line (window, style->white_gc,x+width-1,y,x+width-1,y+height-1);
	    gdk_draw_line (window, style->white_gc,x,y+height-1,x+width-1,y+height-1);
	  }
	  else {
	    gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y, x + width - 2, y);
	    gdk_draw_line(window, galaxy_data->gray_gc[7], x, y + 1, x, y + height - 2);
	    
	    gdk_draw_line(window, galaxy_data->gray_gc[7], x + 1, y + height - 1, x + width - 2, y + height - 1);
	    gdk_draw_line(window, galaxy_data->gray_gc[7], x + width - 1, y + 1, x + width - 1, y + height - 2);
	    
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + width - 3, y + 1);
	    gdk_draw_line(window, style->white_gc, x + 1, y + 1, x + 1, y + height - 3);
	    
	    gdk_draw_line(window, galaxy_data->gray_gc[5], x + 1, y + height - 2, x + width - 2, y + height - 2);
	    gdk_draw_line(window, galaxy_data->gray_gc[5], x + width - 2, y + 1, x + width - 2, y + height - 2);
	    
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1);
	    gdk_draw_point(window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1);
	  }
            break;
    default:
      break;
    }

    if (shadow_type == GTK_SHADOW_IN && 
	widget && (GTK_IS_SPIN_BUTTON (widget) || (GTK_IS_COMBO (widget->parent))) &&
	 DETAIL ("entry"))
    {
      GdkGC * gc1 = style->base_gc[GTK_WIDGET_STATE(widget)];

      if (area) {
	gdk_gc_set_clip_rectangle (style->bg_gc[GTK_WIDGET_STATE(widget)], area);
      }
      
      gdk_draw_line (window,
		     gc1,
		     x + width - 2, y + 2,
		     x + width - 2, y + height - 3);
      
      gdk_draw_point (window,
		      galaxy_data->gray_gc[5],
		      x + width - 1, y + 1);
      gdk_draw_point (window,
		      galaxy_data->gray_gc[2],
		      x + width - 1, y);
      

      gdk_draw_point (window,
		      galaxy_data->gray_gc[0],
			  x + width - 1, y + height-2);
      if (area) {
	gdk_gc_set_clip_rectangle (style->bg_gc[GTK_WIDGET_STATE(widget)], NULL);
      }

    }

    if(area)
    {
        gdk_gc_set_clip_rectangle (style->bg_gc[GTK_STATE_NORMAL], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[0], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[1], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[2], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[3], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[7], NULL);
    }
}

static void draw_polygon(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, GdkPoint * points, gint npoints, gint fill)
{
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif /* M_PI */
#ifndef M_PI_4
#define M_PI_4  0.78539816339744830962
#endif /* M_PI_4 */

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

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);
    g_return_if_fail(points != NULL);

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

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle(gc3, area);
        gdk_gc_set_clip_rectangle(gc4, area);
    }

    if(fill)
        gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);

    npoints--;

    for(i = 0; i < npoints; i++)
    {
        if((points[i].x == points[i + 1].x) && (points[i].y == points[i + 1].y))
        {
            angle = 0;
        }
        else
        {
            angle = atan2(points[i + 1].y - points[i].y, points[i + 1].x - points[i].x);
        }

        if((angle > -pi_3_over_4) && (angle < pi_over_4))
        {
            if(angle > -pi_over_4)
            {
                xadjust = 0;
                yadjust = 1;
            }
            else
            {
                xadjust = 1;
                yadjust = 0;
            }

            gdk_draw_line(window, gc1, points[i].x - xadjust, points[i].y - yadjust, points[i + 1].x - xadjust, points[i + 1].y - yadjust);
            gdk_draw_line(window, gc3, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        else
        {
            if((angle < -pi_3_over_4) || (angle > pi_3_over_4))
            {
                xadjust = 0;
                yadjust = 1;
            }
            else
            {
                xadjust = 1;
                yadjust = 0;
            }

            gdk_draw_line(window, gc4, points[i].x + xadjust, points[i].y + yadjust, points[i + 1].x + xadjust, points[i + 1].y + yadjust);
            gdk_draw_line(window, gc2, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
    }
    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle(gc3, NULL);
        gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

static void draw_diamond(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height)
{
    gint half_width;
    gint half_height;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    half_width = width / 2;
    half_height = height / 2;

    if(area)
    {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->black_gc, area);
    }
    switch (shadow_type)
    {
        case GTK_SHADOW_IN:
            gdk_draw_line(window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x, y + half_height, x + half_width, y + height);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + height, x + width, y + half_height);

            gdk_draw_line(window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x, y + half_height, x + half_width, y);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y, x + width, y + half_height);
            break;
        case GTK_SHADOW_OUT:
            gdk_draw_line(window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->dark_gc[state_type], x, y + half_height, x + half_width, y + height);
            gdk_draw_line(window, style->dark_gc[state_type], x + half_width, y + height, x + width, y + half_height);

            gdk_draw_line(window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
            gdk_draw_line(window, style->light_gc[state_type], x, y + half_height, x + half_width, y);
            gdk_draw_line(window, style->light_gc[state_type], x + half_width, y, x + width, y + half_height);
            break;
        default:
            break;
    }
    if(area)
    {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->black_gc, NULL);
    }
}

static void draw_box(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height)
{
  
  GalaxyData *galaxy_data = style->engine_data;
  int color1, color2, xthick, ythick;
  int delta = 0;

  xthick = style->klass->xthickness;
  ythick = style->klass->ythickness;
  

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);
    
    if (widget && 
	(DETAIL ("button")  ||
	 DETAIL ("togglebutton") ||
	 DETAIL ("spinbutton_up") || 
	 DETAIL ("spinbutton_down") ||
	 DETAIL("optionmenu"))) /* Button, Combobox */ {
      if (area) { 
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], area);
      }
      
      if (("button") && GTK_IS_COMBO(widget->parent)) {
	xthick = ythick = 1;
      }

      if ((width > 2*xthick) && (height > 2*ythick) && (height < 38) 
	  && (galaxy_data->enable_gradient)
	  ||  DETAIL ("spinbutton_up") || 
	     DETAIL ("spinbutton_down")) {
	  GdkColor top_color, bottom_color;

	  if (state_type == GTK_STATE_PRELIGHT) {
	    bottom_color = galaxy_data->gray[1];
	    top_color = style->white;
	  }
	  else if (state_type == GTK_STATE_ACTIVE) {
	      bottom_color = galaxy_data->gray[0];
	      top_color = galaxy_data->gray[2];
	    }
	  else if (state_type == GTK_STATE_INSENSITIVE) {
	    bottom_color = galaxy_data->gray[2];
	    top_color = galaxy_data->gray[1];
	    delta = 1;
	  }
	  else {
	    bottom_color = galaxy_data->gray[2];
	    top_color = galaxy_data->gray[0];
	    }	  
	  /* Make the top button overlap the first line of the bottom button */
	  if (DETAIL ("spinbutton_up")) {
	    xthick = ythick = 1;
	    height += 1;
	  } else if (DETAIL ("spinbutton_down")) {
	    xthick = ythick = 1;
	  }

	  draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			  x+xthick-delta, y+ythick-delta, 
			  width-2*xthick+2*delta, 
			  height-2*ythick+2*delta, 
			  &top_color, 
			  &bottom_color);
	}
      else {
	gtk_style_apply_default_background(style, window, 1, state_type, 
					   area, x+xthick, 
					   y+ythick, 
					   width-2*xthick, 
					   height-2*ythick);
      }
	  
	if (DETAIL ("optionmenu")) {
	  GtkRequisition indicator_size;
	  GtkBorder indicator_spacing;
	  gint vline_x;
	  
	  option_menu_get_props (widget, &indicator_size, &indicator_spacing);
	  sanitize_size (window, &width, &height);

	  vline_x = x + width - (indicator_size.width + indicator_spacing.left
				 + indicator_spacing.right 
				 + xthick+1);
	  
	  gdk_draw_line (window, style->white_gc,
			 vline_x, y+4,
			 vline_x, y+height-4);
	  gdk_draw_line (window, galaxy_data->gray_gc[5],
			 vline_x,y+4, 
			 vline_x,y+height-4);

	}

	if (area) {

	    gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	    gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], NULL);
	}
	
	draw_shadow(style, window, state_type, shadow_type, area, 
		    widget, detail, x, y, width, height);

      }
    else if (widget && 
	     DETAIL ("menubar") || 
	     DETAIL ("toolbar") || 
	     DETAIL ("dockitem_bin") ) {
      if(area) {
            gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
	    gdk_gc_set_clip_rectangle(style->white_gc, area);
	    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[5], area);
        }
       
        gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE, x+1, y+1, width-1, height-1);

	if (shadow_type == GTK_SHADOW_OUT) {
	  gdk_draw_line (window,style->white_gc,x,y,x+width-1,y);
	  gdk_draw_line (window,style->white_gc,x,y+1,x,y+height-1);
	  gdk_draw_line (window,galaxy_data->gray_gc[5],x+width-1,y+1,x+width-1,y+height-2);
	  gdk_draw_line (window,galaxy_data->gray_gc[5],x+1,y+height-1,x+width-1,y+height-1);	
	}
        if(area) {
            gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
	    gdk_gc_set_clip_rectangle(style->white_gc, NULL);
	    gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[5], NULL);
        }
    }
    else if (widget && DETAIL ("trough")) {
      GtkOrientation orientation =  GTK_ORIENTATION_HORIZONTAL;

      if GTK_IS_HSCALE (widget)
	{
	  if (area) {
	    gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	  }

	  gdk_draw_rectangle (window, style->bg_gc[GTK_STATE_NORMAL],TRUE,
			      x,y,width,height);
	  if (area) {
	    gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	  }
	  y += (height - SCALE_SIZE) / 2;
	  height = SCALE_SIZE;
	  orientation = GTK_ORIENTATION_HORIZONTAL;

	}
      
      if GTK_IS_VSCALE (widget)
	{
	  if (area) {
	    gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	  }
	  gdk_draw_rectangle (window, style->bg_gc[GTK_STATE_NORMAL],TRUE,
			      x,y,width,height);
	  if (area) {
	    gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_NORMAL], area);
	  }
	  x += (width - SCALE_SIZE) / 2;
	  width = SCALE_SIZE;
	  orientation = GTK_ORIENTATION_VERTICAL;
	}

      if GTK_IS_HSCROLLBAR (widget) {
	orientation = GTK_ORIENTATION_HORIZONTAL;
      }
      if GTK_IS_VSCROLLBAR (widget) {
	orientation = GTK_ORIENTATION_VERTICAL;
      }			     
      
      if GTK_IS_RANGE (widget) {
	if (area) {
	  gdk_gc_set_clip_rectangle(style->base_gc[state_type], area);
	  gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[5], area);
	}

	if (orientation == GTK_ORIENTATION_HORIZONTAL) {
	  draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			  x+1, y+1, width-2, height-2, 
			  &galaxy_data->gray[2], 
			  &galaxy_data->gray[0]);
	}
	else {
	  draw_hgradient (window, style->base_gc[state_type], style->colormap, 
			  x+1, y+1, width-2, height-2, 
			  &galaxy_data->gray[2], 
			  &galaxy_data->gray[0]);
	}
	gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
			    x,y,width-1,height-1);
	if (area) {
	  gdk_gc_set_clip_rectangle(style->base_gc[state_type], NULL);	
	  gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[5], NULL);
	}
      }
      else {
	if (area) {
	  gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], area);
	}
	gdk_draw_rectangle (window, galaxy_data->gray_gc[2],TRUE,
			    x+1,y+1,x+width-2,y+height-2);
	if (area) {
	  gdk_gc_set_clip_rectangle(galaxy_data->gray_gc[2], NULL);
	}
       draw_shadow(style, window, state_type, shadow_type, area, widget, 
		  detail, x, y, width, height);
      }

    } 
    else if (widget && DETAIL ("hscrollbar") || DETAIL ("vscrollbar") ) {
      /* draw steppers, buttons used for scrollbar */
	 GdkColor top_color, bottom_color;

	 if (area) {
	   gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	   gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], area);
	 }

	  if (state_type == GTK_STATE_PRELIGHT) {
	    bottom_color = galaxy_data->gray[1];
	    top_color = style->white;
	  }
	  else if (state_type == GTK_STATE_ACTIVE) {
	    bottom_color = galaxy_data->gray[0];
	    top_color = galaxy_data->gray[2];
	    }
	  else {
	    bottom_color = galaxy_data->gray[2];
	    top_color = galaxy_data->gray[0];
	  }
	 if (DETAIL ("hscrollbar")) {	 
	   draw_vgradient (window, style->base_gc[state_type], style->colormap, 
			   x+1, y+1, width-2, height-2, 
			   &top_color, 
			   &bottom_color);
	 }
	 else {
	   draw_hgradient (window, style->base_gc[state_type], style->colormap, 
			   x+1, y+1, width-2, height-2, 
			   &top_color, 
			   &bottom_color);
	 }

	 gdk_draw_rectangle (window, galaxy_data->gray_gc[5],FALSE,
			     x,y,width-1,height-1);

	 if (area) {
	   gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], NULL);
	   gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	 }
   
       }
    else if (widget && DETAIL ("bar")) { /* progressbar */
      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_data->blue_gc[2], area);
      }
      
      if ((height > 2 ) && (width > 2)) {
	draw_vgradient (window, style->base_gc[state_type], style->colormap,
		       x+1, y+1, width-2, height-2,
		       &style->white,
		       &galaxy_data->blue[2]);
      }
     
      gdk_draw_line (window, style->white_gc, x,y,x+width-1,y);
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-1);

      gdk_draw_line (window, galaxy_data->blue_gc[2], x+width-1,y+1, x+width-1,y+height-2);
      gdk_draw_line (window, galaxy_data->blue_gc[2], x+1,y+height-1,x+width-1,y+height-1);

      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->blue_gc[2], NULL);
      }
      draw_shadow(style, window, state_type, shadow_type, area, widget, 
		  detail, x, y, width, height);
    }  

    else if (widget && DETAIL ("menuitem")) {
      if (state_type == GTK_STATE_PRELIGHT) {
	if(area) {
	  gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	}
	draw_vgradient (window, style->base_gc[state_type], style->colormap,
			x+1, y+1, width-1, height-1,
			&galaxy_data->blue[2],
			&galaxy_data->blue[0]);
	
	if(area) {
	  gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	}
      }
    } 
    else if (DETAIL ("slider"))
    {
      char *slider_detail = detail;
      GtkOrientation orientation = GTK_ORIENTATION_VERTICAL;
      
      if (widget)
	{
	  if (GTK_IS_HSCALE (widget))
	    {
	      slider_detail = "hscale";
	      orientation = GTK_ORIENTATION_HORIZONTAL;
	    }
	  else if (GTK_IS_VSCALE (widget))
	    {
	      slider_detail = "vscale";
	      orientation = GTK_ORIENTATION_VERTICAL;
	    }
	  else if (GTK_IS_HSCROLLBAR (widget))
	    orientation = GTK_ORIENTATION_HORIZONTAL;
	}

 /* Make sure stepper and slider outlines "overlap" */
      if (widget && GTK_IS_RANGE (widget))
    {
      GtkAdjustment *adj = GTK_RANGE (widget)->adjustment;

      if (adj->value <= adj->lower)
	{
	  if (GTK_IS_VSCROLLBAR (widget))
	    {
	      height += 1;
	      y -= 1;
	    }
	  else if (GTK_IS_HSCROLLBAR (widget))
	    {
	      width += 1;
	      x -= 1;
	    }
	}
      if (adj->value >= adj->upper - adj->page_size)
	{
	  if (GTK_IS_VSCROLLBAR (widget))
	    {
	      height += 1;
	    }
	  else if (GTK_IS_HSCROLLBAR (widget))
	    {
	      width += 1;
	    }
	}
    }

      draw_slider (style, window, state_type, shadow_type,
		   area, widget, slider_detail, x, y, width, height, orientation);
    } else if (detail && *detail != 0 && (!strcmp("paned", detail) 
					  || !strcmp("paned", detail + 1)))
    {
      GtkOrientation orientation = GTK_ORIENTATION_HORIZONTAL;

      if (*detail == 'h')
	orientation = GTK_ORIENTATION_VERTICAL;
      
      draw_handle (style, window, state_type, shadow_type,
		   area, widget, detail,
		   x, y, width, height, orientation);
    }

    else { /* everything else */
       parent_class->draw_box (style, window, state_type, shadow_type, area,
			      widget, detail, x, y, width, height);
    }

  
}

static void draw_check(GtkStyle * style, GdkWindow * window, GtkStateType state, GtkShadowType shadow, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height)
{
  GalaxyData *galaxy_data = style->engine_data;
  GdkGCValues old_values;
  static GdkBitmap* button_bmap = NULL;
  static GdkBitmap* menu_bmap = NULL;
  GdkBitmap* bmap = NULL;

  if(area) {
    gdk_gc_set_clip_rectangle(style->base_gc[state], area);
    gdk_gc_set_clip_rectangle(galaxy_data->check_gc, area);
  }

  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;    
  
  
  if (!DETAIL ("check")) {
    gdk_draw_rectangle(window, style->base_gc[state], TRUE, 
		       x, y, PART_SIZE, PART_SIZE);
    
    draw_shadow (style, window, state,GTK_SHADOW_IN,area,widget,detail,
		 x,y,PART_SIZE,PART_SIZE);

    if (button_bmap == NULL) {
      button_bmap = gdk_bitmap_create_from_data(window, check_cross_bits,
						PART_SIZE, PART_SIZE);
    }

    bmap = button_bmap;
  }
  else {
     if (menu_bmap == NULL) {
      menu_bmap = gdk_bitmap_create_from_data(window, menu_check_bits,
					      PART_SIZE, PART_SIZE);
     }
     bmap = menu_bmap;
     y += 1;
  }
  
  if (shadow == GTK_SHADOW_IN) {
      
	gdk_gc_set_stipple(galaxy_data->check_gc, bmap);
	gdk_gc_set_ts_origin(galaxy_data->check_gc, x, y);
	gdk_gc_set_fill(galaxy_data->check_gc, GDK_STIPPLED);

	if ((DETAIL ("cellcheck") || DETAIL ("check")) && 
	    ((state == GTK_STATE_SELECTED) || (state == GTK_STATE_ACTIVE) 
	     || (state == GTK_STATE_PRELIGHT))) {
	  gdk_gc_get_values (galaxy_data->check_gc, &old_values);
	  gdk_gc_set_foreground (galaxy_data->check_gc, &style->white);
	}

	gdk_draw_rectangle(window, galaxy_data->check_gc, TRUE, x, y, 
			   PART_SIZE, PART_SIZE);

	if ((DETAIL ("cellcheck") || DETAIL ("check"))&& 
	    ((state == GTK_STATE_SELECTED) || (state == GTK_STATE_ACTIVE)
	     || (state == GTK_STATE_PRELIGHT))) {
	  gdk_gc_set_foreground (galaxy_data->check_gc, &old_values.foreground);
	  
	}
	gdk_gc_set_fill(galaxy_data->check_gc, GDK_SOLID);
      }

  if(area) {
    gdk_gc_set_clip_rectangle(style->base_gc[state], NULL);
    gdk_gc_set_clip_rectangle(galaxy_data->check_gc, NULL);
  }
}

static void 
draw_option (GtkStyle      *style,
	     GdkWindow     *window,
	     GtkStateType   state_type,
	     GtkShadowType  shadow_type,
	     GdkRectangle  *area,
	     GtkWidget     *widget,
	     gchar   *detail,
	     gint           x,
	     gint           y,
	     gint           width,
	     gint           height)
{
  GalaxyData *galaxy_data = style->engine_data;
  GdkPixmap *pixmap;
  GdkGCValues old_values;
  static GdkBitmap* bmap = NULL;

  if (DETAIL ("option")) /* Menu item */
    {
      if (shadow_type == GTK_SHADOW_IN) {
	if (bmap == NULL) {
	  bmap = gdk_bitmap_create_from_data(window, radio_text_bits,
					     PART_SIZE, PART_SIZE);
	}

	if(area) {
	gdk_gc_set_clip_rectangle(style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle(galaxy_data->check_gc, area);
      }

	x -= (1 + PART_SIZE - width) / 2;
	y -= (1 + PART_SIZE - height) / 2;
      
	gdk_gc_set_stipple(galaxy_data->check_gc, bmap);
	gdk_gc_set_ts_origin(galaxy_data->check_gc, x, y);
	gdk_gc_set_fill(galaxy_data->check_gc, GDK_STIPPLED);
	
	if ((state_type == GTK_STATE_SELECTED) || 
	    (state_type == GTK_STATE_ACTIVE) || 
	    (state_type == GTK_STATE_PRELIGHT)) {
	  gdk_gc_get_values (galaxy_data->check_gc, &old_values);
	  gdk_gc_set_foreground (galaxy_data->check_gc, &style->white);
	}

	gdk_draw_rectangle(window, galaxy_data->check_gc, TRUE, x, y, 
			   PART_SIZE, PART_SIZE);

	if ((state_type == GTK_STATE_SELECTED) || 
	    (state_type == GTK_STATE_ACTIVE) ||
	    (state_type == GTK_STATE_PRELIGHT)) {
	  gdk_gc_set_foreground (galaxy_data->check_gc, &old_values.foreground);
	  
	}
	gdk_gc_set_fill(galaxy_data->check_gc, GDK_SOLID);
      }

      if(area) {
	gdk_gc_set_clip_rectangle(style->base_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle(galaxy_data->check_gc, NULL);
      }

      return;
    }
    
  if (area) {
    gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
  }

  if (shadow_type == GTK_SHADOW_IN) 
    pixmap = galaxy_data->radio_pixmap_active[state_type];
  else if (shadow_type == GTK_SHADOW_ETCHED_IN) /* inconsistent */
    pixmap = galaxy_data->radio_pixmap_inconsistent[state_type];  
  else 
    pixmap = galaxy_data->radio_pixmap_nonactive[state_type];

  x += (width - RADIO_SIZE)/2;
  y += (height - RADIO_SIZE)/2;

  gdk_gc_set_clip_mask (style->base_gc[state_type],
			galaxy_data->radio_pixmap_mask);
  gdk_gc_set_clip_origin (style->base_gc[state_type], x, y);

  gdk_draw_pixmap (window, style->base_gc[state_type],
		   pixmap,
		   0, 0,
		   x, y,
		   RADIO_SIZE, RADIO_SIZE);

  gdk_gc_set_clip_origin (style->base_gc[state_type], 0, 0);
  gdk_gc_set_clip_mask (style->base_gc[state_type], NULL);

  if (area) {
    gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
  }
}


static void draw_shadow_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkRectangle rect;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    draw_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

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

    gtk_style_apply_default_background(style, window, 1, state_type, area, rect.x, rect.y, rect.width, rect.height);
}

static void draw_box_gap(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
    GdkGC *gc1 = NULL;
    GdkGC *gc2 = NULL;
    GdkGC *gc3 = NULL;
    GdkGC *gc4 = NULL;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    gtk_style_apply_default_background(style, window, widget && !GTK_WIDGET_NO_WINDOW(widget), state_type, area, x, y, width, height);

    sanitize_size(window, &width, &height);

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
            return;
        case GTK_SHADOW_IN:
            gc1 = style->bg_gc[state_type];
            gc2 = style->dark_gc[state_type];;
            gc3 = style->bg_gc[state_type];
            gc4 = style->light_gc[state_type];
            break;
        case GTK_SHADOW_ETCHED_IN:
            gc1 = style->dark_gc[state_type];
            gc2 = style->light_gc[state_type];
            gc3 = style->dark_gc[state_type];
            gc4 = style->light_gc[state_type];
            break;
        case GTK_SHADOW_OUT:
            gc1 = style->light_gc[state_type];
            gc2 = style->bg_gc[state_type];
            gc3 = style->bg_gc[state_type];
            gc4 = style->dark_gc[state_type];
            break;
        case GTK_SHADOW_ETCHED_OUT:
            gc1 = style->light_gc[state_type];
            gc2 = style->dark_gc[state_type];
            gc3 = style->light_gc[state_type];
            gc4 = style->dark_gc[state_type];
            break;
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle(gc3, area);
        gdk_gc_set_clip_rectangle(gc4, area);
    }

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
        case GTK_SHADOW_IN:
        case GTK_SHADOW_OUT:
        case GTK_SHADOW_ETCHED_IN:
        case GTK_SHADOW_ETCHED_OUT:
            switch (gap_side)
            {
                case GTK_POS_TOP:
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y, x + 1, y + height - 2);

                    gdk_draw_line(window, gc3, x + 1, y + height - 2, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc3, x + width - 2, y, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc1, x, y, x + gap_x - 1, y);
                        gdk_draw_line(window, gc2, x + 1, y + 1, x + gap_x - 1, y + 1);
                        gdk_draw_line(window, gc2, x + gap_x, y, x + gap_x, y);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc1, x + gap_x + gap_width, y, x + width - 2, y);
                        gdk_draw_line(window, gc2, x + gap_x + gap_width, y + 1, x + width - 2, y + 1);
                        gdk_draw_line(window, gc2, x + gap_x + gap_width - 1, y, x + gap_x + gap_width - 1, y);
                    }
                    break;
                case GTK_POS_BOTTOM:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + width - 2, y + 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + height - 1);

                    gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc4, x, y + height - 1, x + gap_x - 1, y + height - 1);
                        gdk_draw_line(window, gc3, x + 1, y + height - 2, x + gap_x - 1, y + height - 2);
                        gdk_draw_line(window, gc3, x + gap_x, y + height - 1, x + gap_x, y + height - 1);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc4, x + gap_x + gap_width, y + height - 1, x + width - 2, y + height - 1);
                        gdk_draw_line(window, gc3, x + gap_x + gap_width, y + height - 2, x + width - 2, y + height - 2);
                        gdk_draw_line(window, gc3, x + gap_x + gap_width - 1, y + height - 1, x + gap_x + gap_width - 1, y + height - 1);
                    }
                    break;
                case GTK_POS_LEFT:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc2, x, y + 1, x + width - 2, y + 1);

                    gdk_draw_line(window, gc3, x, y + height - 2, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc1, x, y, x, y + gap_x - 1);
                        gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + gap_x - 1);
                        gdk_draw_line(window, gc2, x, y + gap_x, x, y + gap_x);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc1, x, y + gap_x + gap_width, x, y + height - 2);
                        gdk_draw_line(window, gc2, x + 1, y + gap_x + gap_width, x + 1, y + height - 2);
                        gdk_draw_line(window, gc2, x, y + gap_x + gap_width - 1, x, y + gap_x + gap_width - 1);
                    }
                    break;
                case GTK_POS_RIGHT:
                    gdk_draw_line(window, gc1, x, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y, x, y + height - 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + width - 1, y + 1);
                    gdk_draw_line(window, gc2, x + 1, y + 1, x + 1, y + height - 2);

                    gdk_draw_line(window, gc3, x + 1, y + height - 2, x + width - 1, y + height - 2);
                    gdk_draw_line(window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
                    if(gap_x > 0)
                    {
                        gdk_draw_line(window, gc4, x + width - 1, y, x + width - 1, y + gap_x - 1);
                        gdk_draw_line(window, gc3, x + width - 2, y + 1, x + width - 2, y + gap_x - 1);
                        gdk_draw_line(window, gc3, x + width - 1, y + gap_x, x + width - 1, y + gap_x);
                    }
                    if((width - (gap_x + gap_width)) > 0)
                    {
                        gdk_draw_line(window, gc4, x + width - 1, y + gap_x + gap_width, x + width - 1, y + height - 2);
                        gdk_draw_line(window, gc3, x + width - 2, y + gap_x + gap_width, x + width - 2, y + height - 2);
                        gdk_draw_line(window, gc3, x + width - 1, y + gap_x + gap_width - 1, x + width - 1, y + gap_x + gap_width - 1);
                    }
                    break;
            }
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle(gc3, NULL);
        gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

static void draw_extension(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side)
{ 
  GalaxyData *galaxy_data = style->engine_data;

    GdkGC *gc1 = NULL;
    GdkGC *gc2 = NULL;
    GdkGC *background_gc = NULL;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					GTK_STATE_NORMAL, area, x, y, width, height);
    sanitize_size(window, &width, &height);

    switch (shadow_type) {

    case GTK_SHADOW_NONE:
      return;

    case GTK_SHADOW_IN:
    case GTK_SHADOW_ETCHED_IN:
      gc1 = galaxy_data->gray_gc[5];
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc2 = style->white_gc;
      } else {
	gc2 = galaxy_data->gray_gc[0];
      }
      break;

      gc1 = galaxy_data->gray_gc[5];
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc2 = style->white_gc;		
      } else {
	gc2 = galaxy_data->gray_gc[0];
      }
      break;

    case GTK_SHADOW_OUT:
    case GTK_SHADOW_ETCHED_OUT:
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc1 = style->white_gc;		
      } else {
	gc1 = galaxy_data->gray_gc[0];
      }
      gc2 = galaxy_data->gray_gc[5];
      break;
      if (state_type == GTK_STATE_NORMAL) { /* we draw current page */
	gc1 = style->white_gc;		
      } else {
	gc1 = galaxy_data->gray_gc[0];
      }
      gc2 = galaxy_data->gray_gc[5];
      break;
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, area);
        gdk_gc_set_clip_rectangle(gc2, area);
        gdk_gc_set_clip_rectangle( galaxy_data->gray_gc[2], area);
        gdk_gc_set_clip_rectangle( galaxy_data->gray_gc[1], area);
    }

    switch (shadow_type)
    {
        case GTK_SHADOW_NONE:
        case GTK_SHADOW_IN:
        case GTK_SHADOW_OUT:
        case GTK_SHADOW_ETCHED_IN:
        case GTK_SHADOW_ETCHED_OUT:
            switch (gap_side)
            {
                case GTK_POS_TOP:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->klass->xthickness, 
						      y, 
						      width - (2 * style->klass->xthickness), 
						      height - (style->klass->ythickness));
						      
                    gdk_draw_line(window, gc1, x, y, x, y + height - 3);
		    gdk_draw_point (window, gc1, x+1,y+height-2);
                    gdk_draw_line(window, gc2, x + 2, y + height - 1, x + width - 3, y + height - 1);
                    gdk_draw_line(window, gc2, x + width - 1, y, x + width - 1, y + height - 3);
		    gdk_draw_point (window, gc2, x+width-2,y+height-2);
		    

                    break;
                case GTK_POS_BOTTOM:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->klass->xthickness, 
						      y + style->klass->ythickness, 
						      width - (2 * style->klass->xthickness), 
						      height - (style->klass->ythickness));
						      
                    gdk_draw_line(window, gc1, x + 2, y, x + width - 3, y);
                    gdk_draw_point(window, gc1, x + 1, y+1);
                    gdk_draw_line(window, gc1, x, y + 2, x, y + height - 1);
		    gdk_draw_point (window, gc2, x + width-2, y+1);
                    gdk_draw_line (window, gc2, x + width - 1, y + 2, x + width - 1, y + height - 1);
		    
                    break;
                case GTK_POS_LEFT:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x, 
						      y + style->klass->ythickness, 
						      width - (style->klass->xthickness), 
						      height - (2 * style->klass->ythickness));
                    gdk_draw_line(window, gc1, x, y, x + width - 3, y);
		    gdk_draw_point (window, gc1, x+width-2,y+1);
                    gdk_draw_line(window, gc2, x, y + height - 1, x + width - 3, y + height - 1);
                    gdk_draw_line(window, gc2, x + width - 1, y + 2, x + width - 1, y + height - 3);
                    gdk_draw_point(window, gc2, x + width - 2, y + height - 2);
                    break;
                case GTK_POS_RIGHT:
		  gtk_style_apply_default_background (style, window,
						      widget && !GTK_WIDGET_NO_WINDOW (widget),
						      state_type, area,
						      x + style->klass->xthickness, 
						      y + style->klass->ythickness, 
						      width - (style->klass->xthickness), 
						      height - (2 * style->klass->ythickness));
                    gdk_draw_line(window, gc1, x + 2, y, x + width - 1, y);
                    gdk_draw_line(window, gc1, x, y + 2, x, y + height - 3);
                    gdk_draw_point(window, gc1, x+1, y +height-2);
		    gdk_draw_point(window, gc1, x+1, y+1);
                    gdk_draw_line(window, gc2, x + 2, y + height - 1, x + width - 1, y + height - 1);
                    break;
            }
    }

    if(area)
    {
        gdk_gc_set_clip_rectangle(gc1, NULL);
        gdk_gc_set_clip_rectangle(gc2, NULL);
        gdk_gc_set_clip_rectangle( galaxy_data->gray_gc[2], NULL);
        gdk_gc_set_clip_rectangle( galaxy_data->gray_gc[1], NULL);
    }
}

static void draw_slider(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  GalaxyData *galaxy_data = style->engine_data;
  GdkColor *top_color, *bottom_color;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    if (area) {
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[0],area);
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4],area);
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5],area);
      gdk_gc_set_clip_rectangle (style->white_gc,area);
      gdk_gc_set_clip_rectangle (style->base_gc[state_type],area);
    }

      if (state_type == GTK_STATE_PRELIGHT) {
	bottom_color = &galaxy_data->gray[1];
	top_color = &style->white;
      }
      else {
	bottom_color = &galaxy_data->gray[2];
	top_color = &galaxy_data->gray[0];
      }

    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
      draw_vgradient (window, style->base_gc[state_type], style->colormap, 
		      x+1, y+1, width-2, height-2, 
		      top_color, 
		      bottom_color);
    }
    else {
      draw_hgradient (window, style->base_gc[state_type], style->colormap, 
		      x+2, y+1, width-3, height-2, 
		      top_color, 
		      bottom_color);
    }

    if (DETAIL ("slider")) {
      if (orientation == GTK_ORIENTATION_HORIZONTAL) {
	gdk_draw_line (window, galaxy_data->gray_gc[5], x,y,x+width-1,y);
	gdk_draw_line (window, galaxy_data->gray_gc[5], x,y+height-1,x+width-1,y+height-1);
	height -= 2;
	y+=1;
	width += 1;
      }
      else {     
	gdk_draw_line (window, galaxy_data->gray_gc[5], x,y,x,y+height-1);
	gdk_draw_line (window, galaxy_data->gray_gc[5], x+width-1,y,x+width-1,y+height-1);
	width -= 1;
	x+=1;

      }
    
      gdk_draw_line (window, style->white_gc, x,y,x+width-2,y);
      
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-1);
      
      gdk_draw_line (window, galaxy_data->gray_gc[5], x+1,y+height-1,x+width-2,y+height-1);
      gdk_draw_line (window, galaxy_data->gray_gc[5], x+width-2,y+1,x+width-2,y+height-1);
    } 
    else  if (DETAIL ("hscale")  || DETAIL ("vscale")) {

      gdk_draw_line (window, galaxy_data->gray_gc[5],x+1,y,x+width-2,y);
      gdk_draw_line (window, galaxy_data->gray_gc[5],x,y+1,x,y+height-2);

      gdk_draw_line (window, galaxy_data->gray_gc[5],x+width-1,y+1,x+width-1,y+height-2);
      gdk_draw_line (window, galaxy_data->gray_gc[5],x+1,y+height-1,x+width-2,y+height-1);
      gdk_draw_line (window, style->white_gc,x+1,y+1,x+width-2,y+1);
      gdk_draw_line (window, style->white_gc,x+1,y+2,x+1,y+height-2);

      if (orientation == GTK_ORIENTATION_HORIZONTAL) {
	gtk_paint_vline (style, window, state_type, area, widget, detail, 
			 y + style->klass->ythickness+1, 
			 y + height - style->klass->ythickness - 1, x + width / 2);

      }
      else {
	gtk_paint_hline (style, window, state_type, area, widget, detail,
			 x + style->klass->xthickness+1, 
			 x + width - style->klass->xthickness - 1, y + height / 2);
      }
    }

    if (area) {
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[0],NULL);
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4],NULL);
      gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5],NULL);
      gdk_gc_set_clip_rectangle (style->white_gc,NULL);
      gdk_gc_set_clip_rectangle (style->base_gc[state_type],NULL);
    }

}

static void draw_handle(GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  GalaxyData *galaxy_data = style->engine_data;

    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size(window, &width, &height);

    if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], area);
	gdk_gc_set_clip_rectangle (style->white_gc, area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4], area);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], area);
      }    

    if (detail && (!strcmp (detail, "paned") || !strcmp (detail+1, "paned"))) {
      gtk_style_apply_default_background(style, window, 1, state_type, 
					 area, x, 
					 y, 
					 width, 
					 height);
    }
    else {
      if ((height > 2 ) && (width > 2)) {
	if (orientation == GTK_ORIENTATION_VERTICAL) {
	  draw_vgradient (window, style->base_gc[state_type], style->colormap,
			  x+1, y+1, width-2, height-2,
			  &galaxy_data->gray[0],
			  &galaxy_data->gray[2]);
	}
	else {
	  draw_hgradient (window, style->base_gc[state_type], style->colormap,
			  x+1, y+1, width-2, height-2,
			  &galaxy_data->gray[0],
			  &galaxy_data->gray[2]);
	}
      }
    

      gdk_draw_line (window, galaxy_data->gray_gc[5], x,y+height-1, 
		     x+width-2,y+height-1);
      gdk_draw_line (window, galaxy_data->gray_gc[5], x+width-1,y+1,
		     x+width-1,y+height-1);
      gdk_draw_line (window, galaxy_data->gray_gc[4], x+width-2,y+1, 
		     x+width-2,y+height-2);
      gdk_draw_line (window, galaxy_data->gray_gc[4], x,y+height-2,
		     x+width-3,y+height-2);
      gdk_draw_line (window, style->white_gc, x,y,x+width-2,y);
      gdk_draw_line (window, style->white_gc, x,y+1,x,y+height-2);
    }

      if(area) {
	gdk_gc_set_clip_rectangle (style->base_gc[state_type], NULL);
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[4], NULL);
	gdk_gc_set_clip_rectangle (galaxy_data->gray_gc[5], NULL);
      }
    
    galaxy_draw_handlers(style, window, state_type, area, widget, detail, x, y, width, height, orientation);
}

static void
draw_varrow (GdkWindow     *window,
	     GdkGC         *gc,
	     GdkRectangle  *area,
	     GtkArrowType   arrow_type,
	     gint           x,
	     gint           y,
	     gint           width,
	     gint           height)
{
  gint steps, extra;
  gint y_start, y_increment;
  gint i;

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  
  width = width + width % 2 - 1;	/* Force odd */
  
  steps = 1 + width / 2;

  extra = height - steps;

  if (arrow_type == GTK_ARROW_DOWN)
    {
      y_start = y;
      y_increment = 1;
    }
  else
    {
      y_start = y + height - 1;
      y_increment = -1;
    }

  for (i = 0; i < extra; i++)
    {
      gdk_draw_line (window, gc,
		     x,              y_start + i * y_increment,
		     x + width - 1,  y_start + i * y_increment);
    }
  for (; i < height; i++)
    {
      gdk_draw_line (window, gc,
		     x + (i - extra),              y_start + i * y_increment,
		     x + width - (i - extra) - 1,  y_start + i * y_increment);
    }
  

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_harrow (GdkWindow     *window,
	     GdkGC         *gc,
	     GdkRectangle  *area,
	     GtkArrowType   arrow_type,
	     gint           x,
	     gint           y,
	     gint           width,
	     gint           height)
{
  gint steps, extra;
  gint x_start, x_increment;
  gint i;

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  
  height = height + height % 2 - 1;	/* Force odd */
  
  steps = 1 + height / 2;

  extra = width - steps;

  if (arrow_type == GTK_ARROW_RIGHT)
    {
      x_start = x;
      x_increment = 1;
    }
  else
    {
      x_start = x + width - 1;
      x_increment = -1;
    }

  for (i = 0; i < extra; i++)
    {
      gdk_draw_line (window, gc,
		     x_start + i * x_increment, y,
		     x_start + i * x_increment, y + height - 1);
    }
  for (; i < width; i++)
    {
      gdk_draw_line (window, gc,
		     x_start + i * x_increment, y + (i - extra),
		     x_start + i * x_increment, y + height - (i - extra) - 1);
    }
  

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_arrow (GtkStyle      *style,
		       GdkWindow     *window,
		       GtkStateType   state,
		       GtkShadowType  shadow,
		       GdkRectangle  *area,
		       GtkWidget     *widget,
		       gchar         *detail,
		       GtkArrowType   arrow_type,
		       gboolean       fill,
		       gint           x,
		       gint           y,
		       gint           width,
		       gint           height) {

  GdkGC *gc;

  if (state == GTK_STATE_INSENSITIVE)
    gc = style->white_gc;
  else if (state == GTK_STATE_NORMAL) {
    gc = style->black_gc;
  }
  else  gc = style->fg_gc[state];

 if (DETAIL ("spinbutton")) {
      x += (width - 7) / 2;

      if (arrow_type == GTK_ARROW_UP)
	y += (height - 3) / 2;
      else
	y += (1 + height - 3) / 2;

      draw_varrow (window, gc, area, arrow_type,
		   x, y, 7, 3);
    }
  else if (DETAIL ("vscrollbar"))
    {
      x += (width - 7) / 2;
      y += (height - 5) / 2;

      draw_varrow (window, gc, area, arrow_type,
		   x, y, 7, 5);
      
    }
  else if (DETAIL ("hscrollbar"))
    {
      y += (height - 7) / 2;
      x += (width - 5) / 2;

      draw_harrow (window, gc, area, arrow_type,
		   x, y, 5, 7);
    }
  else
    {
      if (arrow_type == GTK_ARROW_UP || arrow_type == GTK_ARROW_DOWN)
	{
	  x += (width - 7) / 2;
	  y += (height - 5) / 2;
	  
	  draw_varrow (window, gc, area, arrow_type,
		       x, y, 7, 5);
	}
      else
	{
	  x += (width - 5) / 2;
	  y += (height - 7) / 2;
	  
	  draw_harrow (window, gc, area, arrow_type,
		       x, y, 5, 7);
	}
    }
}

static void galaxy_draw_arrow (GtkStyle      *style,
			GdkWindow     *window,
			GtkStateType   state,
			GtkShadowType  shadow,
			GdkRectangle  *area,
			GtkWidget     *widget,
			gchar         *detail,
			GtkArrowType   arrow_type,
			gboolean       fill,
			gint           x,
			gint           y,
			gint           width,
			gint           height) {

  GdkGC *gc;
  gboolean is_spinbutton ;

  is_spinbutton = DETAIL ("spinbutton");

  sanitize_size (window, &width, &height);

  if ((shadow != GTK_SHADOW_NONE) && !DETAIL("arrow") && !DETAIL("header")){
    char *box_detail = detail;
    int box_x = x, box_y = y, box_width = width, box_height = height;
      

   if (is_spinbutton) {
     box_x -= 1;
     box_width += 2*2;
     if (arrow_type == GTK_ARROW_UP)
       {
	 box_y -= 1;
	 box_height += 2;
       }
     else
       {
	 box_y -= 1;
	 box_height += 2;
       }
     box_detail = (arrow_type == GTK_ARROW_DOWN)?"spinbutton_down":"spinbutton_up";
     if (shadow == GTK_SHADOW_ETCHED_IN)
	{
	  shadow = GTK_SHADOW_OUT;
	  state = GTK_STATE_INSENSITIVE;
	}
	 else if (shadow == GTK_SHADOW_IN) {
	   shadow = GTK_SHADOW_OUT;
	   state = GTK_STATE_ACTIVE;
	 }
     
   }
     draw_box (style, window, state, shadow,
	       area, widget, box_detail, box_x, box_y, width, box_height);

     if (is_spinbutton)
       {
	  x += 1;
	  if (arrow_type == GTK_ARROW_UP)
	    y += 3;
	  else
	    y +=1;
	    
	  width -= 2*3;
	  height -= 2*2;
       }
 }
 

 draw_arrow (style,window, state,shadow, area, widget,detail,arrow_type,fill,
	     x, y, width, height);
}

static void
draw_tab (GtkStyle      *style,
	  GdkWindow     *window,
	  GtkStateType   state_type,
	  GtkShadowType  shadow_type,
	  GdkRectangle  *area,
	  GtkWidget     *widget,
	  gchar         *detail,
	  gint           x,
	  gint           y,
	  gint           width,
	  gint           height)
{
#define ARROW_SPACE 4

  GtkRequisition indicator_size;
  GtkBorder indicator_spacing;
  gint arrow_height;
  
  option_menu_get_props (widget, &indicator_size, &indicator_spacing);

  indicator_size.width += (indicator_size.width % 2) - 1;
  arrow_height = indicator_size.width / 2 + 1;

  x += (width - indicator_size.width) / 2+4;
  y += (height - (2*arrow_height + ARROW_SPACE )) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
      draw_varrow (window, style->white_gc, area,
		  GTK_ARROW_UP, x + 1, y + 1,
		  indicator_size.width, arrow_height);

      draw_varrow (window, style->white_gc, area,
		  GTK_ARROW_DOWN, x + 1, y + 1+arrow_height + ARROW_SPACE,
		  indicator_size.width, arrow_height);
    }

  draw_varrow (window, style->black_gc, area,
	      GTK_ARROW_UP, x, y,
	      indicator_size.width, arrow_height);

  
  draw_varrow (window, style->black_gc, area,
	      GTK_ARROW_DOWN, x, y+arrow_height + ARROW_SPACE,
	      indicator_size.width, arrow_height);
 
}

static void 
draw_focus (GtkStyle      *style,
	    GdkWindow     *window,
	    GdkRectangle  *area,
	    GtkWidget     *widget,
	    gchar         *detail,
	    gint           x,
	    gint           y,
	    gint           width,
	    gint           height)
{
  GdkPoint points[5];
  GdkGC    *gc;
  gboolean free_dash_list = FALSE;
  gint line_width = 1;
  gchar *dash_list = "\1\1";
  gint dash_len;

  gc = style->black_gc;

  sanitize_size (window, &width, &height);
  
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  gdk_gc_set_line_attributes (gc, line_width,
			      dash_list[0] ? GDK_LINE_ON_OFF_DASH : GDK_LINE_SOLID,
			      GDK_CAP_BUTT, GDK_JOIN_MITER);


  if (detail && !strcmp (detail, "add-mode"))
    {
      if (free_dash_list)
	g_free (dash_list);
      
      dash_list = "\4\4";
      free_dash_list = FALSE;
    }

  points[0].x = x + line_width / 2;
  points[0].y = y + line_width / 2;
  points[1].x = x + width - line_width + line_width / 2;
  points[1].y = y + line_width / 2;
  points[2].x = x + width - line_width + line_width / 2;
  points[2].y = y + height - line_width + line_width / 2;
  points[3].x = x + line_width / 2;
  points[3].y = y + height - line_width + line_width / 2;
  points[4] = points[0];

  if (!dash_list[0])
    {
      gdk_draw_lines (window, gc, points, 5);
    }
  else
    {
      /* We go through all the pain below because the X rasterization
       * rules don't really work right for dashed lines if you
       * want continuity in segments that go between top/right
       * and left/bottom. For instance, a top left corner
       * with a 1-1 dash is drawn as:
       *
       *  X X X 
       *  X
       *
       *  X
       *
       * This is because pixels on the top and left boundaries
       * of polygons are drawn, but not on the bottom and right.
       * So, if you have a line going up that turns the corner
       * and goes right, there is a one pixel shift in the pattern.
       *
       * So, to fix this, we drawn the top and right in one call,
       * then the left and bottom in another call, fixing up
       * the dash offset for the second call ourselves to get
       * continuity at the upper left.
       *
       * It's not perfect since we really should have a join at
       * the upper left and lower right instead of two intersecting
       * lines but that's only really apparent for no-dashes,
       * which (for this reason) are done as one polygon and
       * don't to through this code path.
       */
      
      dash_len = strlen (dash_list);
      
      if (dash_list[0])
	gdk_gc_set_dashes (gc, 0, dash_list, dash_len);
      
      gdk_draw_lines (window, gc, points, 3);
      
      /* We draw this line one farther over than it is "supposed" to
       * because of another rasterization problem ... if two 1 pixel
       * unjoined lines meet at the lower right, there will be a missing
       * pixel.
       */
      points[2].x += 1;
      
      if (dash_list[0])
	{
	  gint dash_pixels = 0;
	  gint i;
	  
	  /* Adjust the dash offset for the bottom and left so we
	   * match up at the upper left.
	   */
	  for (i = 0; i < dash_len; i++)
	    dash_pixels += dash_list[i];
      
	  if (dash_len % 2 == 1)
	    dash_pixels *= 2;
	  
	  gdk_gc_set_dashes (gc, dash_pixels - (width + height - 2 * line_width) % dash_pixels, dash_list, dash_len);
	}
      
      gdk_draw_lines (window, gc, points + 2, 3);
    }

  gdk_gc_set_line_attributes (gc, 0, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);

  if (free_dash_list)
    g_free (dash_list);
}

void galaxy_initialize_style(GtkStyleClass *klass,
			     GtkStyleClass *parent)
{
  parent_class = parent;

  *klass = *parent;

    klass->draw_hline = draw_hline;
    klass->draw_vline = draw_vline;
    klass->draw_shadow = draw_shadow;
    klass->draw_polygon = draw_polygon;
    klass->draw_diamond = draw_diamond;
    klass->draw_box = draw_box;
    klass->draw_check = draw_check;
    klass->draw_option = draw_option;
    klass->draw_shadow_gap = draw_shadow_gap;
    klass->draw_box_gap = draw_box_gap;
    klass->draw_extension = draw_extension;
    klass->draw_slider = draw_slider;
    klass->draw_handle = draw_handle;
    klass->draw_arrow = galaxy_draw_arrow;
    klass->draw_focus = draw_focus;
    klass->draw_tab = draw_tab;
}

