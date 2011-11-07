/* CleanIce engine for GTK+ 2.x
   Based on ThinIce and Clean GTK+ engines

   Author: Rodney Dawes <dobey@free.fr>
   ThinIce Author: Tomas Ögren <stric@ing.umu.se>
   Clean Author: dengen40@yahoo.com
*/

#include "cleanice.h"

#define DETAIL(xx) ((detail) && (!strcmp(xx, detail)))

static void cleanice_style_init (CleanIceStyle * style);
static void cleanice_style_class_init (CleanIceStyleClass * klass);

static void draw_hline (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail, gint x1, gint x2, gint y);
static void draw_vline (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail, gint y1, gint y2, gint x);
static void draw_shadow (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height);

static void draw_arrow (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail,
			GtkArrowType arrow_type,
			gint fill,
			gint x, gint y, gint width, gint height);

static void draw_box (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x, gint y, gint width, gint height);

static void draw_flat_box (GtkStyle * style,
		           GdkWindow * window,
		           GtkStateType state_type,
		           GtkShadowType shadow_type,
		           GdkRectangle * area,
		           GtkWidget * widget,
		           const gchar * detail,
		           gint x, gint y, gint width, gint height);

static void draw_check (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height);
static void draw_option (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height);

static void draw_gap (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x,
		      gint y,
		      gint width,
		      gint height,
		      GtkPositionType gap_side,
		      gint gap_x, gint gap_width);
static void draw_extension (GtkStyle * style,
			    GdkWindow * window,
			    GtkStateType state_type,
			    GtkShadowType shadow_type,
			    GdkRectangle * area,
			    GtkWidget * widget,
			    const gchar * detail,
			    gint x,
			    gint y,
			    gint width,
			    gint height, GtkPositionType gap_side);

static void draw_slider (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x,
			 gint y,
			 gint width,
			 gint height, GtkOrientation orientation);
static void draw_handle (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x,
			 gint y,
			 gint width,
			 gint height, GtkOrientation orientation);
static void draw_resize_grip (GtkStyle * style, GdkWindow * window,
			      GtkStateType state_type, GdkRectangle * area,
			      GtkWidget * widget, const gchar * detail,
			      GdkWindowEdge edge, gint x, gint y,
			      gint width, gint height);
static void draw_layout (GtkStyle * style, GdkWindow * window,
			 GtkStateType state_type, gboolean use_text,
			 GdkRectangle * area, GtkWidget * widget,
			 const gchar * detail, gint x, gint y,
			 PangoLayout * layout);
			 
static void cleanice_dot(GdkWindow *window,
			 GdkGC *gc1,
			 GdkGC *gc2,
			 gint x,
			 gint y);
static GtkStyleClass *parent_class = NULL;

static void calculate_arrow_geometry (GtkArrowType  arrow_type,
				      gint         *x,
				      gint         *y,
				      gint         *width,
				      gint         *height) {
  gint w = *width;
  gint h = *height;
  
  switch (arrow_type) {
  case GTK_ARROW_UP:
  case GTK_ARROW_DOWN:
    w += (w % 2) - 1;
    h = (w / 2 + 1);
      
    if (h > *height) {
      h = *height;
      w = 2 * h - 1;
    }
      
    if (arrow_type == GTK_ARROW_DOWN)
      {
	if (*height % 2 == 1 || h % 2 == 0)
	  *height += 1;
      }
    else
      {
	if (*height % 2 == 0 || h % 2 == 0)
	  *height -= 1;
      }
    break;

  case GTK_ARROW_RIGHT:
  case GTK_ARROW_LEFT:
    h += (h % 2) - 1;
    w = (h / 2 + 1);
      
    if (w > *width)
      {
	w = *width;
	h = 2 * w - 1;
      }
      
    if (arrow_type == GTK_ARROW_RIGHT)
      {
	if (*width % 2 == 1 || w % 2 == 0)
	  *width += 1;
      }
    else
      {
	if (*width % 2 == 0 || w % 2 == 0)
	  *width -= 1;
      }
    break;
      
  default:
    /* should not be reached */
    break;
  }

  *x += (*width - w) / 2;
  *y += (*height - h) / 2;
  *height = h;
  *width = w;
}

static void sanitize_size (GdkDrawable * window, gint * width, gint * height) {
  if ((*width == -1) && (*height == -1))
    gdk_drawable_get_size (window, width, height);
  else if (*width == -1)
    gdk_drawable_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_drawable_get_size (window, NULL, height);
}

static void real_draw_line (GtkStyle * style, GdkWindow * window,
			    GtkOrientation orientation,
			    GdkRectangle * area, GtkShadowType shadow_type,
			    GtkStateType state_type, const gchar * detail,
			    gint y1, gint y2, gint x1, gint x2) {
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type],
			       area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type],
			       area);
  }

  if (orientation == GTK_ORIENTATION_VERTICAL) {
    if (shadow_type == GTK_SHADOW_OUT) {
      gdk_draw_line (window, style->light_gc[state_type],
		     x1 + 1, y1, x1 + 1, y2);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1, y1, x1, y2);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1, y1, x1, y2 - 1);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1 + 1, y1 + 1, x1 + 1, y2);
    } else {
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1 + 1, y1, x1 + 1, y2);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1, y1, x1, y2);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1, y1, x1, y2 - 1);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1 + 1, y1 + 1, x1 + 1, y2);
    }
  } else {
    if (shadow_type == GTK_SHADOW_OUT) {
      gdk_draw_line (window, style->light_gc[state_type],
		     x1, y1 + 1, x2, y1 + 1);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1, y1, x2, y1);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1, y1, x2 - 1, y1);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1 + 1, y1 + 1, x2, y1 + 1);
    } else {
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1, y1 + 1, x2, y1 + 1);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1, y1, x2, y1);
      gdk_draw_line (window, style->dark_gc[state_type],
		     x1, y1, x2 - 1, y1);
      gdk_draw_line (window, style->light_gc[state_type],
		     x1 + 1, y1 + 1, x2, y1 + 1);
    }
  }

  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type],
			       NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type],
			       NULL);
  }
}

static void draw_hline (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail, gint x1, gint x2, gint y) {

  if (DETAIL ("handlebox") || DETAIL ("dockitem")) {
    real_draw_line (style, window, GTK_ORIENTATION_HORIZONTAL,
		    area, GTK_SHADOW_OUT,
		    state_type, detail, y, 0, x1, x2);
  } else {
    real_draw_line (style, window, GTK_ORIENTATION_HORIZONTAL,
		    area, GTK_SHADOW_IN,
		    state_type, detail, y, 0, x1, x2);
  }
}

static void draw_vline (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail, gint y1, gint y2, gint x) {

  if (DETAIL ("handlebox") || DETAIL ("dockitem")) {
    real_draw_line (style, window, GTK_ORIENTATION_VERTICAL,
		    area, GTK_SHADOW_OUT,
		    state_type, detail, y1, y2, x, 0);
  } else {
    real_draw_line (style, window, GTK_ORIENTATION_VERTICAL,
		    area, GTK_SHADOW_IN,
		    state_type, detail, y1, y2, x, 0);
  }
}

static void do_draw_shadow_with_gap (GdkWindow * window, GdkRectangle * area,
				     GdkGC * tl_gc, GdkGC * br_gc,
				     const gchar * detail,
				     gint x, gint y, gint width, gint height,
				     GtkPositionType gap_side, gint gap_pos,
				     gint gap_size) {
  if (area) {
    gdk_gc_set_clip_rectangle(tl_gc, area);
    gdk_gc_set_clip_rectangle(br_gc, area);
  }

  switch (gap_side) {
    case GTK_POS_TOP:
      gdk_draw_line(window, br_gc, x, y + height - 1,
		    x + width - 1, y + height - 1);
      gdk_draw_line(window, br_gc, x + width - 1, y,
		    x + width - 1, y + height - 1);

      gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
    
      if (gap_size <= 0)
	gdk_draw_line(window, tl_gc, x, y, x + width - 1, y);
      else {
	if (gap_pos > 0)
	  gdk_draw_line(window, tl_gc, x, y, x + gap_pos, y);
	if ((width - (gap_pos + gap_size)) > 0)
	  gdk_draw_line (window, tl_gc,  x + gap_pos + gap_size - 1, y,
			 x + width - 1, y);
      }

      break;
    case GTK_POS_BOTTOM:
      if (gap_size <= 0)
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, br_gc, x, y + height-1, x + gap_pos - 1, y + height-1);
        if ((width - (gap_pos + gap_size)) > 0)
          gdk_draw_line(window, br_gc, x + gap_pos + gap_size - 1, y + height-1, x + width - 1, y + height-1);
      }
      gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);

      gdk_draw_line(window, tl_gc, x, y, x, y + height - 1);
      gdk_draw_line(window, tl_gc, x, y, x + width - 1, y);

      break;
    case GTK_POS_LEFT:
      gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
      gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);

      if (gap_size <= 0)
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, tl_gc, x, y, x, y + gap_pos - 1);
       if ((height - (gap_pos + gap_size)) > 0)
          gdk_draw_line(window, tl_gc, x, y + gap_pos + gap_size - 1, x, y + height-1);
      }
      gdk_draw_line(window, tl_gc, x, y, x + width-1, y);

      break;
    case GTK_POS_RIGHT:
      gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
      if (gap_size <= 0)
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + gap_pos - 1);
       if ((height - (gap_pos + gap_size)) > 0)
          gdk_draw_line(window, br_gc, x + width-1, y + gap_pos + gap_size - 1, x + width-1, y + height-1);
      }
      gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
      gdk_draw_line(window, tl_gc, x, y, x + width-1, y);

      break;
    default :
      break;
  }
  if (area)
    {
      gdk_gc_set_clip_rectangle(tl_gc, NULL);
      gdk_gc_set_clip_rectangle(br_gc, NULL);
    }
}

static void draw_shadow_with_gap (GtkStyle * style,
			          GdkWindow * window,
				  GtkStateType state_type,
				  GtkShadowType shadow_type,
 				  GdkRectangle * area,
				  GtkWidget * widget,
				  const gchar * detail,
				  gint x, gint y, gint width, 
				  gint height,
				  GtkPositionType gap_side,
				  gint gap_pos, gint gap_size) {
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  sanitize_size (GDK_DRAWABLE (window), &width, &height); 
  
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
  }

  if (DETAIL ("menuitem")) {
    gdk_draw_rectangle (window, style->dark_gc[state_type],
			FALSE, x, y, width - 1, height - 1);
  } else {
    switch (shadow_type) {
    case GTK_SHADOW_NONE:
      break;
    case GTK_SHADOW_IN:
      do_draw_shadow_with_gap (window, area,
			       style->dark_gc[state_type],
			       style->light_gc[state_type],
			       detail, x, y, width, height,
			       gap_side, gap_pos, gap_size);
      break;
    case GTK_SHADOW_ETCHED_IN:
      do_draw_shadow_with_gap (window, area,
			       style->light_gc[GTK_STATE_NORMAL],
			       style->light_gc[GTK_STATE_NORMAL],
			       detail, x + 1, y + 1, width - 2, height - 2,
			       gap_side, gap_pos, gap_size);
      do_draw_shadow_with_gap (window, area,
			       style->dark_gc[state_type],
			       style->dark_gc[state_type],
			       detail, x, y, width - 2, height - 2,
			       gap_side, gap_pos, gap_size);
      break;
    case GTK_SHADOW_OUT:
      do_draw_shadow_with_gap (window, area,
			       style->light_gc[state_type],
			       style->dark_gc[state_type],
			       detail, x, y, width, height,
			       gap_side, gap_pos, gap_size);
      break;
    case GTK_SHADOW_ETCHED_OUT:
      do_draw_shadow_with_gap (window, area,
			       style->dark_gc[GTK_STATE_NORMAL],
			       style->dark_gc[GTK_STATE_NORMAL],
			       detail, x + 1, y + 1, width - 2, height - 2,
			       gap_side, gap_pos, gap_size);
      do_draw_shadow_with_gap (window, area,
			       style->light_gc[state_type],
			       style->light_gc[state_type],
			       detail, x, y, width - 2, height - 2,
			       gap_side, gap_pos, gap_size);
      break;
    }
  }
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
  }
}

static void draw_shadow (GtkStyle * style, GdkWindow * window,
			 GtkStateType state_type, GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget, const gchar * detail,
			 gint x, gint y, gint width, gint height) {
  draw_shadow_with_gap (style, window, state_type, shadow_type,
			area, widget, detail,
			x, y, width,  height,
			GTK_POS_TOP, 0, 0);
}

static void draw_black_arrow (GdkWindow     *window,
			      GdkGC         *gc,
			      GdkRectangle  *area,
			      GtkArrowType   arrow_type,
			      gint           x,
			      gint           y,
			      gint           width,
			      gint           height) {
  gint i, j;
  
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  
  if (arrow_type == GTK_ARROW_DOWN)
    {
      for (i = 0, j = 0; i < height; i++, j++)
	gdk_draw_line (window, gc, x + j, y + i, x + width - j - 1, y + i);
    }
  else if (arrow_type == GTK_ARROW_UP)
    {
      for (i = height - 1, j = 0; i >= 0; i--, j++)
	gdk_draw_line (window, gc, x + j, y + i, x + width - j - 1, y + i);
    }
  else if (arrow_type == GTK_ARROW_LEFT)
    {
      for (i = width - 1, j = 0; i >= 0; i--, j++)
	gdk_draw_line (window, gc, x + i, y + j, x + i, y + height - j - 1);
    }
  else if (arrow_type == GTK_ARROW_RIGHT)
    {
      for (i = 0, j = 0; i < width; i++, j++)
	gdk_draw_line (window, gc, x + i, y + j, x + i, y + height - j - 1);
    }

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void draw_arrow (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail,
			GtkArrowType arrow_type,
			gint fill, gint x, gint y, gint width, gint height) {
  gint ax, ay, aw, ah;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size (GDK_DRAWABLE (window), &width, &height);
  ax = x;
  ay = y;
  aw = width;
  ah = height;
  calculate_arrow_geometry (arrow_type, &ax, &ay, &aw, &ah);

  if (DETAIL ("vscrollbar")) {
    draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
		      ax, ay, aw + 2, ah + 1);
  } else if (DETAIL ("hscrollbar")) {
    draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
		      ax, ay, aw + 1, ah + 2);
  } else if (DETAIL ("spinbutton")) {
    if (arrow_type == GTK_ARROW_UP) {
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
			ax, ay - 1, aw + 2, ah + 1);
    } else {
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
			ax, ay + 1, aw + 2, ah + 1);
    }
  } else if (DETAIL ("menuitem")) {
    aw = width/2 + (width % 2);
    ah = height - !(height % 2);
    ax = x + (width - aw) / 2;
    ay = y + (height - ah) / 2;
     
    if (aw < 3) aw = 3;
    if (ah < 5) ah = 5;

    draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
		      ax, ay, aw, ah);
  } else {
    draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
		      ax, ay, aw, ah);
  }
}

static void real_draw_box (GtkStyle * style,
			   GdkWindow * window,
			   GtkStateType state_type,
			   GtkShadowType shadow_type,
			   GdkRectangle * area,
			   GtkWidget * widget,
			   const gchar * detail,
			   gint x,
			   gint y,
			   gint width,
			   gint height, 
			   gboolean draw_shadow) {

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);
  
  sanitize_size (GDK_DRAWABLE (window), &width, &height);
  
  if (area) {
    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
  }

  gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		      x, y, width, height);
  if (area) {
    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
  }

  if (draw_shadow) {
    gtk_paint_shadow (style, window, state_type, 
		      shadow_type, area, widget, 
		      detail, x, y, width, height);
  }
}

static void draw_box (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x, gint y, gint width, gint height) {

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);
  
  sanitize_size (GDK_DRAWABLE (window), &width, &height);

  if (DETAIL ("optionmenu")) {
    real_draw_box (style, window, state_type,
		   shadow_type, area, widget,
		   detail, x, y, width, height, TRUE);

    draw_vline (style, window, state_type,
		area, widget, detail,
		y + style->ythickness + 1,
		y + height - style->ythickness - 2,
		x + width - 19 - style->xthickness);
  } else if (DETAIL ("trough")) {
    if (GTK_IS_SCALE (widget)) {
      if (width > height) {
	draw_hline (style, window, state_type, area, widget, detail,
		    x, x + width, y + (height / 2) - 1);
      } else {
	draw_vline (style, window, state_type, area, widget, detail,
		    y, y + height, x + (width / 2) - 1);
      }
      return;
    }
    real_draw_box (style, window, state_type,
		   shadow_type, area, widget,
		   detail, x, y, width, height, TRUE);
  } else if (DETAIL ("buttondefault")) {
    /* I don't want no background on default buttons..
       Let's add that cute triangle (see below) instead... */
  } else if (DETAIL ("button")) {
    GdkPoint points1[3]; /* dark */
    GdkPoint points2[3]; /* light */
    points1[0].x = x+2;  points1[0].y = y+2;
    points1[1].x = x+10; points1[1].y = y+2;
    points1[2].x = x+2;  points1[2].y = y+10;
    points2[0].x = x+3;  points2[0].y = y+3;
    points2[1].x = x+10; points2[1].y = y+3;
    points2[2].x = x+3;  points2[2].y = y+10;

    if (GTK_IS_COMBO (widget->parent)) {
      if (state_type == GTK_STATE_ACTIVE) {
	real_draw_box (style, window, state_type, GTK_SHADOW_IN,
		       area, widget, detail, x, y, width, height, TRUE);
      } else {
	real_draw_box (style, window, state_type, shadow_type,
		       area, widget, detail, x, y, width, height, TRUE);
      }
    } else {
      real_draw_box (style, window, state_type, shadow_type,
		     area, widget, detail, x, y, width, height, TRUE);
    }

    /* Paint a triangle here instead of in "buttondefault"
       which is drawn _behind_ the current button */
    if (GTK_WIDGET_HAS_DEFAULT (widget)) {
      gdk_draw_polygon(window, style->dark_gc[state_type],
		       FALSE, points1, 3);
      gdk_draw_polygon(window, style->light_gc[state_type],
		       FALSE, points2, 3);
      if (state_type != GTK_STATE_PRELIGHT) {
	gdk_draw_polygon(window, style->bg_gc[GTK_STATE_PRELIGHT],
			 TRUE, points2, 3);
      } else {
	gdk_draw_polygon(window, style->fg_gc[GTK_STATE_PRELIGHT],
			 TRUE, points2, 3);
      }
    }
  } else if (DETAIL ("bar")) {
    real_draw_box (style, window, GTK_STATE_SELECTED, GTK_SHADOW_OUT,
		   area, widget, detail, x, y, width, height, TRUE);
  } else if (DETAIL ("spinbutton_up") || DETAIL ("spinbutton_down")) {
    if (state_type == GTK_STATE_PRELIGHT || state_type == GTK_STATE_ACTIVE) {
      real_draw_box (style, window, state_type, shadow_type,
		     area, widget, detail, x, y, width, height, TRUE);
    } else {
      real_draw_box (style, window, GTK_STATE_NORMAL, shadow_type,
		     area, widget, detail, x, y, width, height, FALSE);
    }
  } else {
    real_draw_box (style, window, state_type, shadow_type,
		  area, widget, detail, x, y, width, height, TRUE);
  }
}

static void draw_flat_box (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x, gint y, gint width, gint height) {
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);
  
  sanitize_size (GDK_DRAWABLE (window), &width, &height);

  if (DETAIL ("checkbutton") && state_type == GTK_STATE_PRELIGHT) {
    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[GTK_STATE_NORMAL], area);
    }

    gdk_draw_rectangle (window, style->bg_gc[GTK_STATE_NORMAL], TRUE,
			x, y, width, height);

    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[GTK_STATE_NORMAL], NULL);
    }
  } else {
    parent_class->draw_flat_box (style, window, state_type, shadow_type,
				 area, widget, detail, x, y, width, height);
  }  

}

static void draw_check_item (GdkWindow * window, GdkGC * gc,
			     GdkRectangle * area,
			     gint x, gint y, gint width, gint height) {
  gdk_draw_line(window, gc, x + 1, y + height - 6, x + 1, y + height - 3);
  gdk_draw_line(window, gc, x + 2, y + height - 5, x + 2, y + height - 2);
  
  gdk_draw_line(window, gc, x + 3, y + height - 4, x + width - 2, y + 1);
  gdk_draw_line(window, gc, x + 3, y + height - 3, x + width - 2, y + 2);
  gdk_draw_line(window, gc, x + 3, y + height - 2, x + width - 2, y + 3);
}

static void draw_check (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			const gchar * detail,
			gint x, gint y, gint width, gint height)  {
  if (DETAIL ("check")) {	/* Menu item */
    if (shadow_type == GTK_SHADOW_IN) {
      draw_check_item (window, style->fg_gc[state_type], area,
		       x, y, width + 1, height + 1);
    }
  } else {
    gtk_paint_box (style, window, GTK_STATE_NORMAL, 
		   GTK_SHADOW_IN, area, widget, 
		   detail, x, y - 2, width + 3, height + 3);
    gdk_draw_rectangle (window, style->base_gc[state_type], TRUE, 
			x + 1,  y - 1, width + 1, height + 1);
    if (shadow_type == GTK_SHADOW_IN) {
      draw_check_item (window, style->text_gc[state_type], area,
		       x + 2, y, width, height);
    }
  }
}

static void draw_option (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height) {

  if (DETAIL ("option")) { /* Menu item */
    if (shadow_type == GTK_SHADOW_IN) {
      gdk_draw_arc (window, style->fg_gc[state_type], TRUE,
		    x + 2, y + 2, width / 2, height / 2, 0, 360 * 64);
      gdk_draw_arc (window, style->fg_gc[state_type], FALSE,
		    x + 2, y + 2, width / 2, height / 2, 0, 360 * 64);
    }
  } else {
    gdk_draw_arc (window, style->base_gc[state_type],
		  TRUE, x, y, width, height, 0, 360 * 64);
    gdk_draw_arc (window, style->mid_gc[GTK_STATE_NORMAL], FALSE, 
		  x, y, width, height, 45 * 64, 225 * 64);
    gdk_draw_arc (window, style->light_gc[GTK_STATE_NORMAL], FALSE, 
		  x, y, width, height, 225 * 64, 180 * 64);
    if (shadow_type == GTK_SHADOW_IN) {
      gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		    x + width / 4,
		    y + height / 4,
		    width / 2 + 1, height / 2 + 1,
		    0, 360 * 64); 
      gdk_draw_arc (window, style->mid_gc[state_type], FALSE,
		    x + width / 4,
		    y + height / 4,
		    width / 2 + 1, height / 2 + 1,
		    0, 360 * 64); 
    }
  }
}

static void draw_gap (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x, gint y, gint width, gint height,
		      GtkPositionType gap_side,
		      gint gap_x, gint gap_width) {
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  sanitize_size (GDK_DRAWABLE (window), &width, &height);
  
  real_draw_box(style, window, state_type, shadow_type, area, 
                widget, detail, x, y, width, height, FALSE);
  
  draw_shadow_with_gap (style, window, state_type, shadow_type,
			area, widget, detail,
			x, y, width, height,
			gap_side, gap_x, gap_width);
}

static void draw_extension (GtkStyle * style,
			    GdkWindow * window,
			    GtkStateType state_type,
			    GtkShadowType shadow_type,
			    GdkRectangle * area,
			    GtkWidget * widget,
			    const gchar * detail,
			    gint x, gint y, gint width, gint height,
			    GtkPositionType gap_side)  {

  draw_gap (style, window, state_type, shadow_type, area, widget, 
  	    detail, x, y, width, height, gap_side, 1, width);

}

static void cleanice_dot(GdkWindow *window,
			 GdkGC *gc1, GdkGC *gc2,
			 gint x, gint y) {
  GdkPoint points[3];

  points[0].x = x-1; points[0].y = y;
  points[1].x = x-1; points[1].y = y-1;
  points[2].x = x;   points[2].y = y-1;

  gdk_draw_points (window, gc2, points, 3);

  points[0].x = x+1; points[0].y = y;
  points[1].x = x+1; points[1].y = y+1;
  points[2].x = x;   points[2].y = y+1;

  gdk_draw_points (window, gc1, points, 3);
}

static void draw_slider (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height,
			 GtkOrientation orientation) {
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  sanitize_size (GDK_DRAWABLE (window), &width, &height); 

  real_draw_box(style, window, state_type,
		shadow_type, area, widget,
	        detail, x, y, width, height, 
		TRUE);

  if (area) {
    gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
  }

  cleanice_dot(window, style->light_gc[state_type],
	       style->dark_gc[state_type],
	       x + width / 2, y + height / 2);
  if (area) {
    gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
  }
}

static void draw_handle (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GtkShadowType shadow_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 const gchar * detail,
			 gint x, gint y, gint width, gint height,
			 GtkOrientation orientation) {
  GdkRectangle        dest;

  g_return_if_fail(style != NULL);

  g_return_if_fail(window != NULL);

  sanitize_size (GDK_DRAWABLE (window), &width, &height);

  dest.x = x + style->xthickness;
  dest.y = y + style->ythickness;
  dest.width = width - (style->xthickness * 2);
  dest.height = height - (style->ythickness * 2);

  if (width > height) {
    orientation = GTK_ORIENTATION_HORIZONTAL;
  } else {
    orientation = GTK_ORIENTATION_VERTICAL;
  }

  gdk_gc_set_clip_rectangle (style->light_gc[state_type], &dest);
  gdk_gc_set_clip_rectangle (style->dark_gc[state_type], &dest);

  if (DETAIL("paned")) {
    if (orientation == GTK_ORIENTATION_VERTICAL) {
      gtk_paint_box(style, window, state_type, shadow_type, area, widget,
		    detail, x, y, width, height);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 - 8);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 - 4);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 + 4);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 + 8);
    } else {
      gtk_paint_box(style, window, state_type, shadow_type, area, widget,
		    detail, x, y, width, height);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 - 8,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 - 4,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 + 4,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 + 8,
		   y + height / 2);
    }
  } else {
    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
      gtk_paint_box(style, window, state_type, GTK_SHADOW_OUT, area, widget,
		    detail, x, y, width, height);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 - 4,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2 + 4,
		   y + height / 2);
    } else {
      gtk_paint_box(style, window, state_type, GTK_SHADOW_OUT, area, widget,
		    detail, x, y, width, height);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 - 4);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2);
      cleanice_dot(window,
		   style->light_gc[state_type],
		   style->dark_gc[state_type],
		   x + width / 2,
		   y + height / 2 + 4);
    }
  }

  gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
  gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
}

static void draw_resize_grip (GtkStyle * style, GdkWindow * window,
			      GtkStateType state_type, GdkRectangle * area,
			      GtkWidget * widget, const gchar * detail,
			      GdkWindowEdge edge, gint x, gint y,
			      gint width, gint height) {
  GdkPoint points2[3]; /* light */

  if (GTK_IS_STATUSBAR (widget))
    gtk_statusbar_set_has_resize_grip (GTK_STATUSBAR (widget), FALSE);
  return;

  points2[0].x = x + width; points2[0].y = y - 1;
  points2[1].x = x + width; points2[1].y = y + height;
  points2[2].x = x + (width - height) - 1;  points2[2].y = y + height;

  gtk_paint_box(style, window, state_type, GTK_SHADOW_OUT, area, widget,
		detail, x + (width - height) - 2, y - 2,
		height + 6, height + 6);
  gdk_draw_polygon(window, style->dark_gc[state_type], TRUE, points2, 3);
}

static void draw_layout (GtkStyle * style, GdkWindow * window,
			 GtkStateType state_type, gboolean use_text,
			 GdkRectangle * area, GtkWidget * widget,
			 const gchar * detail, gint x, gint y,
			 PangoLayout * layout) {
  if ((widget && widget->parent) &&
      (strstr (g_type_name (GTK_WIDGET_TYPE (widget->parent)),
	       "CheckButton") ||
       strstr (g_type_name (GTK_WIDGET_TYPE (widget->parent)),
	       "RadioButton")) &&
      state_type == GTK_STATE_PRELIGHT) {
    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }
    gdk_draw_layout (window, style->bg_gc[state_type], x, y, layout);
    if (area) {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
  } else {
    parent_class->draw_layout (style, window, state_type, use_text,
			       area, widget, detail, x, y, layout);
  }
}

GType cleanice_type_style = 0;

void cleanice_style_register_type (GTypeModule * module) {
  static const GTypeInfo object_info = {
    sizeof (CleanIceStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) cleanice_style_class_init,
    NULL,		/* class_finalize */
    NULL,		/* class_data */
    sizeof (CleanIceStyle),
    0,		/* n_preallocs */
    (GInstanceInitFunc) cleanice_style_init,
  };

  cleanice_type_style = g_type_module_register_type (module,
						     GTK_TYPE_STYLE,
						     "CleanIceStyle",
						     &object_info, 0);
}

static void cleanice_style_init (CleanIceStyle * style) {
}

static void cleanice_style_class_init (CleanIceStyleClass * klass) {
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;
  style_class->draw_arrow = draw_arrow;
  style_class->draw_box = draw_box;
  style_class->draw_flat_box = draw_flat_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_shadow_gap = draw_gap;
  style_class->draw_box_gap = draw_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;
  style_class->draw_resize_grip = draw_resize_grip;
  style_class->draw_layout = draw_layout;
}	
