#include "misc_functions.h"
#include "../smooth_rc_style.h"

/* Many of the following functions were shamelessly copied
 * from multiple engines : the gtk-2.0 metal engine,
 * the XFCE theme engine(GTK2 port), Xenophilia 0.8,
 * CoolIce engine(GTK2 port), ThinIce engine(GTK2 port),
 * Wonderland(aka BlueCurve(TM)) engine, and the LighthouseBlue
 * engine, with a few subsequent (mostly minor) modifications.
 */

void
alloc_color (GtkStyle * style, GdkColor * color)
{
  GdkColormap *cmap = style->colormap;
  gint depth = style->depth;
  
  if (!(cmap)) {
    cmap = gdk_colormap_get_system();
    depth = gdk_colormap_get_visual(cmap)->depth;
  }
  
  gdk_colormap_alloc_color (cmap, color, FALSE, TRUE);
}

GdkGC *
new_color_gc (GtkStyle * style, GdkColor * color)
{
  GdkGCValues gc_values;
  GdkColormap *cmap = style->colormap;
  gint depth = style->depth;
  
  if (!(cmap)) {
    cmap = gdk_colormap_get_system();
    depth = gdk_colormap_get_visual(cmap)->depth;
  }
  
  gdk_colormap_alloc_color (cmap, color, FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (depth, cmap,
		     &gc_values, GDK_GC_FOREGROUND);
}

GdkGC *
shaded_color (GtkStyle * style, GtkStateType state_type, gdouble shade_value)
{
  GdkColor color;
  
  shade (&style->bg[state_type], &color, shade_value);

  return new_color_gc (style, &color);

}

void
lighttone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  if ((THEME_DATA(style)) && (THEME_DATA(style)->colors.has_light[state]))
    {
      color->red = THEME_DATA(style)->colors.light[state].red;
      color->green = THEME_DATA(style)->colors.light[state].green;
      color->blue = THEME_DATA(style)->colors.light[state].blue;
    }
  else 
    {
      shade (&style->bg[state], color, LIGHTNESS_MULT);

      THEME_DATA(style)->colors.light[state].red = color->red;
      THEME_DATA(style)->colors.light[state].green = color->green;
      THEME_DATA(style)->colors.light[state].blue = color->blue;
      
      THEME_DATA(style)->colors.has_light[state] = TRUE;
    }  
}

void
darktone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  if ((THEME_DATA(style)) && (THEME_DATA(style)->colors.has_dark[state]))
    {
      color->red = THEME_DATA(style)->colors.dark[state].red;
      color->green = THEME_DATA(style)->colors.dark[state].green;
      color->blue = THEME_DATA(style)->colors.dark[state].blue;
    }
  else 
    {
      shade(&style->bg[state], color, DARKNESS_MULT);

      THEME_DATA(style)->colors.dark[state].red = color->red;
      THEME_DATA(style)->colors.dark[state].green = color->green;
      THEME_DATA(style)->colors.dark[state].blue = color->blue;
      
      THEME_DATA(style)->colors.has_dark[state] = TRUE;
    }  
}

void
midtone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  if ((THEME_DATA(style)) && (THEME_DATA(style)->colors.has_mid[state]))
    {
      color->red = THEME_DATA(style)->colors.mid[state].red;
      color->green = THEME_DATA(style)->colors.mid[state].green;
      color->blue = THEME_DATA(style)->colors.mid[state].blue;
    }
  else 
    {
      GdkColor dark_color, light_color;
  
      lighttone_color(&light_color, style, state);
      darktone_color(&dark_color, style, state);

      color->red = (light_color.red + dark_color.red) / 2;
      color->green = (light_color.green + dark_color.green) / 2;
      color->blue = (light_color.blue + dark_color.blue) / 2;

      THEME_DATA(style)->colors.mid[state].red = color->red;
      THEME_DATA(style)->colors.mid[state].green = color->green;
      THEME_DATA(style)->colors.mid[state].blue = color->blue;
      
      THEME_DATA(style)->colors.has_mid[state] = TRUE;
    }  
}

void
middarktone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  if ((THEME_DATA(style)) && (THEME_DATA(style)->colors.has_middark[state]))
    {
      color->red = THEME_DATA(style)->colors.middark[state].red;
      color->green = THEME_DATA(style)->colors.middark[state].green;
      color->blue = THEME_DATA(style)->colors.middark[state].blue;
    }
  else 
    {
      GdkColor dark_color;
  
      darktone_color(&dark_color, style, state);

      color->red = (style->bg[state].red + dark_color.red) / 2;
      color->green = (style->bg[state].green + dark_color.green) / 2;
      color->blue = (style->bg[state].blue + dark_color.blue) / 2;

      THEME_DATA(style)->colors.middark[state].red = color->red;
      THEME_DATA(style)->colors.middark[state].green = color->green;
      THEME_DATA(style)->colors.middark[state].blue = color->blue;
      
      THEME_DATA(style)->colors.has_middark[state] = TRUE;
    }  
}

void
midlighttone_color(GdkColor * color, GtkStyle * style, GtkStateType state)
{
  if ((THEME_DATA(style)) && (THEME_DATA(style)->colors.has_midlight[state]))
    {
      color->red = THEME_DATA(style)->colors.midlight[state].red;
      color->green = THEME_DATA(style)->colors.midlight[state].green;
      color->blue = THEME_DATA(style)->colors.midlight[state].blue;
    }
  else 
    {
      GdkColor light_color;
  
      lighttone_color(&light_color, style, state);

      color->red = (style->bg[state].red + light_color.red) / 2;
      color->green = (style->bg[state].green + light_color.green) / 2;
      color->blue = (style->bg[state].blue + light_color.blue) / 2;

      THEME_DATA(style)->colors.midlight[state].red = color->red;
      THEME_DATA(style)->colors.midlight[state].green = color->green;
      THEME_DATA(style)->colors.midlight[state].blue = color->blue;
      
      THEME_DATA(style)->colors.has_midlight[state] = TRUE;
    }  
}

GdkGC *
lighttone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * light_gc=style->light_gc[state];
  GdkColor color;

  lighttone_color(&color, style, state);

  light_gc = new_color_gc(style, &color);
  return light_gc;
}

GdkGC *
darktone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * dark_gc=style->dark_gc[state];
  GdkColor color;

  darktone_color(&color, style, state);

  dark_gc = new_color_gc(style, &color);
  return dark_gc;
}

GdkGC *
midtone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * mid_gc=style->mid_gc[state];
  GdkColor color;

  midtone_color(&color, style, state);

  mid_gc = new_color_gc(style, &color);
  return mid_gc;
}

GdkGC *
middarktone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * middark_gc=style->mid_gc[state];
  GdkColor color;

  middarktone_color(&color, style, state);

  middark_gc = new_color_gc(style, &color);
  return middark_gc;
}

GdkGC *
midlighttone_gc(GtkStyle * style, GtkStateType state)
{
  GdkGC * midlight_gc=style->mid_gc[state];
  GdkColor color;

  midlighttone_color(&color, style, state);

  midlight_gc = new_color_gc(style, &color);
  return midlight_gc;
}

GdkBitmap *
arc_clip_mask(gint width,
	      gint height)
{
  GdkBitmap *result;
  GdkGC *gc;
  GdkColor color;

  result = (GdkBitmap *)gdk_pixmap_new(NULL, width, height, 1);
  gc = gdk_gc_new(result);
	
  color.pixel = 0;
  gdk_gc_set_foreground(gc, &color);

  gdk_draw_rectangle(result, gc, TRUE, 0, 0, width, height);
  gdk_draw_rectangle(result, gc, FALSE, 0, 0, width, height);

  color.pixel = 1;
  gdk_gc_set_foreground(gc, &color);

  gdk_draw_arc(result, gc, TRUE, 0, 0, width, height, 0, 360*64);
  gdk_draw_arc(result, gc, FALSE, 0, 0, width, height, 0, 360*64);

  gdk_gc_destroy(gc);

  return result;
}

/* The following is based on a similar routine found in most 
 * GTK2 engines, I have no idea which one came up with it first...
 */
gboolean
sanitize_parameters(GtkStyle * style,
  	            GdkWindow * window,
	            gint * width,
	            gint * height)
{
  if (!style) return FALSE;
  if (!window) return FALSE;

  if ((width) && (height)) {
    if ((*width == -1) && (*height == -1))
      gdk_window_get_size(window, width, height);
    else if (*width == -1)
      gdk_window_get_size(window, width, NULL);
    else if (*height == -1)
      gdk_window_get_size(window, NULL, height);  
  }
  return TRUE;  
}

GtkWidget *
get_notebook_page(GtkWidget * widget)
{
  g_return_val_if_fail(GTK_IS_WIDGET(widget), NULL);

  while (widget && widget->parent && !gtk_type_is_a(GTK_WIDGET_TYPE(widget->parent), GTK_TYPE_NOTEBOOK))
    widget = widget->parent;

  if (!(widget && widget->parent && gtk_type_is_a(GTK_WIDGET_TYPE(widget->parent), GTK_TYPE_NOTEBOOK)))
    return NULL;
      

  return widget;
}

GtkWidget *
get_tab_label(GtkWidget *page, GtkWidget * widget)
{
  GtkWidget * real_widget = widget;
  g_return_val_if_fail(GTK_IS_WIDGET(widget), NULL);

  widget = gtk_notebook_get_menu_label(GTK_NOTEBOOK(page->parent), page);
  if (!(widget)) 
     widget = gtk_notebook_get_tab_label(GTK_NOTEBOOK(page->parent), page);
     
  return widget;
}

gboolean 
widget_is_tab_label(GtkWidget *page, GtkWidget * widget)
{
  GtkWidget * real_widget = widget;
  g_return_val_if_fail(GTK_IS_WIDGET(widget), FALSE);

  widget = gtk_notebook_get_menu_label(GTK_NOTEBOOK(page->parent), page);
  if (!(widget)) 
     widget = gtk_notebook_get_tab_label(GTK_NOTEBOOK(page->parent), page);
     
  if ((real_widget) && (widget) && (real_widget != widget) && (!(gtk_widget_is_ancestor(real_widget, widget))))
    return FALSE;

  return TRUE;
}

gboolean 
tab_label_is_current_page(GtkWidget *page, GtkWidget * widget)
{
  gint current_num = 0;
  GtkWidget *current_page = NULL; 
  GtkWidget *current_label = NULL;

  current_num = gtk_notebook_get_current_page(GTK_NOTEBOOK(page->parent));
  if (current_num ==-1)
    return FALSE;

  current_page = gtk_notebook_get_nth_page(GTK_NOTEBOOK(page->parent), current_num); 

  if (!(current_page))
    return FALSE;

  current_label = gtk_notebook_get_tab_label(GTK_NOTEBOOK(page->parent), current_page);

  if ((current_label == NULL) || (current_label != widget) && (!gtk_widget_is_ancestor(widget, current_label)))
    return FALSE;

  return TRUE;
}

/* From GTK-Engines Metal 2.0:
 * 
 * This function makes up for some brokeness in gtkrange.c
 * where we never get the full arrow of the stepper button
 * and the type of button in a single drawing function.
 *
 * It doesn't work correctly when the scrollbar is squished
 * to the point we don't have room for full-sized steppers.
 */
void
reverse_engineer_stepper_box (GtkWidget    *range,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height)
{
#if GTK2
  gint slider_width = 15, stepper_size = 15;
  gint box_width;
  gint box_height;
  
  if (range)
    {
      gtk_widget_style_get (range,
			    "slider_width", &slider_width,
			    "stepper_size", &stepper_size,
			    NULL);
    }
	
  if (arrow_type == GTK_ARROW_UP || arrow_type == GTK_ARROW_DOWN)
    {
      box_width = slider_width;
      box_height = stepper_size;
    }
  else
    {
      box_width = stepper_size;
      box_height = slider_width;
    }

  *x = (*x - (box_width - *width) / 2) + 2;
  *y = (*y - (box_height - *height) / 2) + 2;
  *width = box_width - 3;
  *height = box_height - 3;
#endif

#if GTK1
  *x += 2;
  *y += 2;
  *width -= 4;
  *height -= 4;
#endif
}

/* This function is based on reverse_engineer_stepper_box
 * (and gtk2 sources) except it is for getting spin button 
 * size instead. It is not always right, and only returns 
 * a (hopefully more accurate) arrow box, not the entire
 * button box, as the button box is passed correctly
 * to paint_box and so only paint_arrow needs this.
 */
void
reverse_engineer_spin_button (GtkWidget    *widget,
			      GtkArrowType  arrow_type,
			      gint         *x,
			      gint         *y,
			      gint         *width,
			      gint         *height)
{
#ifdef GTK2
  gint size = pango_font_description_get_size (widget->style->font_desc);
  gint realheight, realwidth;

  realwidth = MIN(PANGO_PIXELS (size), 30);

  realwidth -= realwidth % 2; /* force even */
  
  realwidth -= 2 * xthickness(widget->style);
  
  realheight = ((widget->requisition.height) - 2 * ythickness(widget->style)) / 2;
      
  realheight -= 1;
  realwidth += 1;
  *x += ((*width - realwidth) / 2);
  *y += ((*height - realheight) / 2) + (arrow_type==GTK_ARROW_DOWN?1:-1);
  *width = realwidth;
  *height = realheight;
#endif
}

/* This function is a home-grown (probably flawed) function 
 * inspired by the metal, ThinIce, & Wonderland GTK2 engines
 */
void
reverse_engineer_arrow_box (GtkWidget    *widget,
                            const gchar * detail,
			    GtkArrowType  arrow_type,
			    gint         *x,
			    gint         *y,
			    gint         *width,
			    gint         *height)
{
  if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar"))
    {
      reverse_engineer_stepper_box (widget, arrow_type,
				    x, y, width, height);
 
    } else if (DETAIL("spinbutton")) {
      reverse_engineer_spin_button (widget, arrow_type,
				    x, y, width, height);
   }
  #if GTK2
  else if (DETAIL("menuitem"))
    {
      *width += 2;
      *height += 2;
      *x -= 1;
    }
  else if (DETAIL("arrow")) {
      *width += 2;
      *height += 2;
      *x -= 1;
      *y -= 1;
  }  
  #endif  
  #if GTK1
  else if (DETAIL("menuitem"))
    {
      *width += 2;
      *height += 2;
      *x -= 1;
      *y += 0;
    }
  else if (DETAIL("arrow")) {
      *y += 1;
  }  
  #endif  
}

/* This function is based on a portion of Xenophilia's xeno_draw_extension */
gboolean
rounded_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8])
{
  gint x2 = x + width, y2 = y + height;
  switch (position) {
    case GTK_POS_BOTTOM:
      y2 += ((fill)?1:0) + ((selected)?0:-1);
      points[0].x = x2-1;	points[0].y = y2;
      points[1].x = x2-1;	points[1].y = y+5;
      points[2].x = x2-3;	points[2].y = y+2;
      points[3].x = x2-6;	points[3].y = y;
      points[4].x = x+5;	points[4].y = y;
      points[5].x = x+2;	points[5].y = y+2;
      points[6].x = x;		points[6].y = y+5;
      points[7].x = x;		points[7].y = y2;
      break;
	
    case GTK_POS_RIGHT:
      x2 += ((fill)?1:0) + ((selected)?0:-1);
      points[0].y = y;		points[0].x = x2;
      points[1].y = y;		points[1].x = x+5;
      points[2].y = y+2;	points[2].x = x+2;
      points[3].y = y+5;	points[3].x = x;
      points[4].y = y2-6;	points[4].x = x;
      points[5].y = y2-3;	points[5].x = x+2;
      points[6].y = y2-1;	points[6].x = x+5;
      points[7].y = y2-1;	points[7].x = x2;
      break;
			
    case GTK_POS_TOP:
      y -= ((fill)?1:0) + ((selected)?1:0);
      y2 += ((selected)?-1:0) - 1;
      points[0].x = x;		points[0].y = y;
      points[1].x = x;		points[1].y = y2-5;
      points[2].x = x+2;	points[2].y = y2-2;
      points[3].x = x+5;	points[3].y = y2;
      points[4].x = x2-6;	points[4].y = y2;
      points[5].x = x2-3;	points[5].y = y2-2;
      points[6].x = x2-1;	points[6].y = y2-5;
      points[7].x = x2-1;	points[7].y = y;
      break;
    
    case GTK_POS_LEFT:
      x -= ((fill)?1:0) + ((selected)?1:0);
      x2 += ((selected)?-1:0) - 1;
      points[0].y = y2-1;	points[0].x = x;
      points[1].y = y2-1;	points[1].x = x2-5;
      points[2].y = y2-3;	points[2].x = x2-2;
      points[3].y = y2-6;	points[3].x = x2;
      points[4].y = y+5;	points[4].x = x2;
      points[5].y = y+2;	points[5].x = x2-2;
      points[6].y = y;		points[6].x = x2-5;
      points[7].y = y;		points[7].x = x;
      break;

    default :
      return FALSE;     
  }  
  return TRUE;     
}

/* This function is based on a portion of Xenophilia's xeno_draw_extension */
gboolean
square_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8])
{
  gint x2 = x + width, y2 = y + height;

  switch (position) {
    case GTK_POS_BOTTOM:
      y2 += ((fill)?1:0) + ((selected)?0:-1);
      points[0].x = x2-1;	points[0].y = y2;
      points[1].x = x2-1;	points[1].y = y+1;
      points[2].x = x2-1;	points[2].y = y;
      points[3].x = x2-2;	points[3].y = y;
      points[4].x = x+1;	points[4].y = y;
      points[5].x = x;		points[5].y = y;
      points[6].x = x;		points[6].y = y+1;
      points[7].x = x;		points[7].y = y2;
      break;
	
    case GTK_POS_RIGHT:
      x2 += ((fill)?1:0) + ((selected)?0:-1);
      points[0].y = y;		points[0].x = x2;
      points[1].y = y;		points[1].x = x+1;
      points[2].y = y;		points[2].x = x;
      points[3].y = y+1;	points[3].x = x;
      points[4].y = y2-2;	points[4].x = x;
      points[5].y = y2-1;	points[5].x = x;
      points[6].y = y2-1;	points[6].x = x+1;
      points[7].y = y2-1;	points[7].x = x2;
      break;
			
    case GTK_POS_TOP:
      y -= ((fill)?1:0) + ((selected)?1:0);
      y2 += ((selected)?-1:0) - 1;
      points[0].x = x;		points[0].y = y;
      points[1].x = x;		points[1].y = y2-1;
      points[2].x = x;		points[2].y = y2;
      points[3].x = x+1;	points[3].y = y2;
      points[4].x = x2-2;	points[4].y = y2;
      points[5].x = x2-1;	points[5].y = y2;
      points[6].x = x2-1;	points[6].y = y2-1;
      points[7].x = x2-1;	points[7].y = y;
      break;
    
    case GTK_POS_LEFT:
      x -= ((fill)?1:0) + ((selected)?1:0);
      x2 += ((selected)?-1:0) - 1;
      points[0].y = y2-1;	points[0].x = x;
      points[1].y = y2-1;	points[1].x = x2-1;
      points[2].y = y2-1;	points[2].x = x2;
      points[3].y = y2-2;	points[3].x = x2;
      points[4].y = y+1;	points[4].x = x2;
      points[5].y = y;		points[5].x = x2;
      points[6].y = y;		points[6].x = x2-1;
      points[7].y = y;		points[7].x = x;
      break;
         
    default :
      return FALSE;     
  }  
  return TRUE;     
}

/* This function is based on a portion of Xenophilia's xeno_draw_extension */
gboolean
triangle_extension_points(gint x,
                         gint y, 
			 gint width, 
			 gint height,
			 gboolean selected,
			 gboolean fill,
			 GtkPositionType position,
			 GdkPoint points[8])
{
  gint x2 = x + width, y2 = y + height;
  gint i = 0;

  switch (position) {
    case GTK_POS_BOTTOM:
      i = (height - 5 + 2) / 3;

      if (!(i > 0)) return square_extension_points(x, y, width, height, selected, fill, position, points);

      y2 = y + i*3 + 5 + ((fill)?1:0) + ((selected)?0:-1);
         
      points[0].x = x2-1;	points[0].y = y2;
      points[1].x = x2-i-1;	points[1].y = y+4;
      points[2].x = x2-i-3;	points[2].y = y+2;
      points[3].x = x2-i-6;	points[3].y = y;
      points[4].x = x+i+5;	points[4].y = y;
      points[5].x = x+i+2;	points[5].y = y+2;
      points[6].x = x+i;		points[6].y = y+4;
      points[7].x = x;		points[7].y = y2;
      break;
	
    case GTK_POS_RIGHT:
      i = (width- 5 + 2) / 3;
      if (!(i > 0)) return square_extension_points(x, y, width, height, selected, fill, position, points);

      x2 = x + i*3 + 5 + ((fill)?1:0) + ((selected)?0:-1);
      points[0].y = y;		points[0].x = x2;
      points[1].y = y+i;	points[1].x = x+4;
      points[2].y = y+i+2;	points[2].x = x+2;
      points[3].y = y+i+5;	points[3].x = x;
      points[4].y = y2-i-6;	points[4].x = x;
      points[5].y = y2-i-3;	points[5].x = x+2;
      points[6].y = y2-i-1;	points[6].x = x+4;
      points[7].y = y2-1;	points[7].x = x2;
      break;

    case GTK_POS_TOP:
      i = (height - 5 + 2) / 3;
      if (!(i > 0)) return square_extension_points(x, y, width, height, selected, fill, position, points);

      y -= (i*3 + 5 - height) + ((fill)?1:0) + ((selected)?1:0);
      y2 += ((selected)?-1:0) - 1;
      points[0].x = x;		points[0].y = y;
      points[1].x = x+i;		points[1].y = y2-4;
      points[2].x = x+i+2;	points[2].y = y2-2;
      points[3].x = x+i+5;	points[3].y = y2;
      points[4].x = x2-i-6;	points[4].y = y2;
      points[5].x = x2-i-3;	points[5].y = y2-2;
      points[6].x = x2-i-1;	points[6].y = y2-4;
      points[7].x = x2-1;	points[7].y = y;
      break;
             
    case GTK_POS_LEFT:
      i = (width- 5 + 2) / 3;
      if (!(i > 0)) return square_extension_points(x, y, width, height, selected, fill, position, points);

      x -= (i*3 + 5 - width) + ((fill)?1:0) + ((selected)?1:0);
      x2 += ((selected)?-1:0) - 1;
      points[0].y = y2-1;	points[0].x = x;
      points[1].y = y2-i-1;	points[1].x = x2-4;
      points[2].y = y2-i-3;	points[2].x = x2-2;
      points[3].y = y2-i-6;	points[3].x = x2;
      points[4].y = y+i+5;	points[4].x = x2;
      points[5].y = y+i+2;	points[5].x = x2-2;
      points[6].y = y+i;	points[6].x = x2-4;
      points[7].y = y;		points[7].x = x;
      break;

    default :
      return square_extension_points(x, y, width, height, selected, fill, position, points);
  }  
  return TRUE;     
}
		
void
rounded_box_points(gint x,
                   gint y, 
  	           gint width, 
		   gint height,
		   GdkPoint points[13],
		   gboolean large)
{
  gint x2 = x + width - 1, y2 = y + height - 1;

  if (large) {
  	points[0].x = x+5;	points[0].y = y2;
  	points[1].x = x+2;	points[1].y = y2-2;
  	points[2].x = x;	points[2].y = y2-5;
  	points[3].x = x;	points[3].y = y+5;
  	points[4].x = x+2;	points[4].y = y+2;
  	points[5].x = x+5;	points[5].y = y;
  	points[6].x = x2-5;	points[6].y = y;
  	points[7].x = x2-2;	points[7].y = y+2;
  	points[8].x = x2;	points[8].y = y+5;
  	points[9].x = x2;	points[9].y = y2-5;
  	points[10].x = x2-2;	points[10].y = y2-2;
  	points[11].x = x2-5;	points[11].y = y2;
  	points[12].x = x+5;	points[12].y = y2;
   } else {
  	points[0].x = x+2;	points[0].y = y2;
  	points[1].x = x+1;	points[1].y = y2-1;
  	points[2].x = x;	points[2].y = y2-2;
  	points[3].x = x;	points[3].y = y+2;
  	points[4].x = x+1;	points[4].y = y+1;
  	points[5].x = x+2;	points[5].y = y;
  	points[6].x = x2-2;	points[6].y = y;
  	points[7].x = x2-1;	points[7].y = y+1;
  	points[8].x = x2;		points[8].y = y+2;
  	points[9].x = x2;		points[9].y = y2-2;
  	points[10].x = x2-1;	points[10].y = y2-1;
  	points[11].x = x2-2;	points[11].y = y2;
  	points[12].x = x+2;	points[12].y = y2;
   }
}

/* This function is based on a portion of EnGradient's draw_box */
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
		      gint height)
{
  GdkPoint points1[3]; /* dark */
  GdkPoint points2[3]; /* light */
  
  points1[0].x = x+2;  points1[0].y = y+2;
  points1[1].x = x+10; points1[1].y = y+2;
  points1[2].x = x+2;  points1[2].y = y+10;
  points2[0].x = x+3;  points2[0].y = y+3;
  points2[1].x = x+10; points2[1].y = y+3;
  points2[2].x = x+3;  points2[2].y = y+10;

   if (area) {
     gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
     gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
     gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
   } 
	
   /* Paint a triangle here instead of in "buttondefault"
      which is drawn _behind_ the current button */
   if (GTK_WIDGET_HAS_DEFAULT (widget)) {
     gdk_draw_polygon(window, style->dark_gc[state_type], FALSE, points1, 3);
     gdk_draw_polygon(window, style->light_gc[state_type], FALSE, points2, 3);
     gdk_draw_polygon(window, style->bg_gc[GTK_STATE_SELECTED], TRUE, points2, 3);
   }

   if (area) {
     gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
     gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
     gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
   } 
}

/* This function is a homegrown function based upon the draw_shadow 
 * & draw_shadow_gap routines of XFCE, lighthouseblue, EnGradient, 
 * & Xenophilia.
 */
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
	       gboolean topleft_overlap)
{
  if (area)
    {
      gdk_gc_set_clip_rectangle(tl_gc, area);
      gdk_gc_set_clip_rectangle(br_gc, area);
    }

  switch (gap_side) {
    case GTK_POS_TOP:
      if (topleft_overlap) {
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      } 

      gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
    
      if (gap_size <= 0)
        gdk_draw_line(window, tl_gc, x, y, x + width-1, y);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, tl_gc, x, y, x + gap_pos, y);
        if ((width - (gap_pos + gap_size)) > 0)
	  gdk_draw_line (window, tl_gc,  x + gap_pos + gap_size - 1, y, x + width - 1, y);
      }

      if (!topleft_overlap) {
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      } 
      break;
    case GTK_POS_BOTTOM:
      if (!topleft_overlap) {
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
        gdk_draw_line(window, tl_gc, x, y, x + width-1, y);
      } 

      if (gap_size <= 0)
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, br_gc, x, y + height-1, x + gap_pos, y + height-1);
        if ((width - (gap_pos + gap_size)) > 0)
          gdk_draw_line(window, br_gc, x + gap_pos + gap_size - 1, y + height-1, x + width - 1, y + height-1);
      }
      gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);

      if (topleft_overlap) {
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
        gdk_draw_line(window, tl_gc, x, y, x + width-1, y);
      } 
      break;
    case GTK_POS_LEFT:
      if (topleft_overlap) {
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      } 

       gdk_draw_line(window, tl_gc, x, y, x + width -1, y);
    
      if (gap_size <= 0)
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, tl_gc, x, y, x, y + gap_pos);
          
        if ((height - (gap_pos + gap_size)) > 0)
	  gdk_draw_line (window, tl_gc,  x, y + gap_pos + gap_size - 1, x, y + height - 1);
      }

      if (!topleft_overlap) {
        gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      } 
      break;
    case GTK_POS_RIGHT:
      if (!topleft_overlap) {
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
        gdk_draw_line(window, tl_gc, x, y, x + width-1, y);
      } 

      gdk_draw_line(window, br_gc, x, y + height-1, x + width-1, y + height-1);
      if (gap_size <= 0)
        gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + height-1);
      else {
        if (gap_pos > 0)
          gdk_draw_line(window, br_gc, x + width-1, y, x + width-1, y + gap_pos);
          
       if ((height - (gap_pos + gap_size)) > 0)
          gdk_draw_line(window, br_gc, x + width-1, y + gap_pos + gap_size -1, x + width-1, y + height-1);
      }

      if (topleft_overlap) {
        gdk_draw_line(window, tl_gc, x, y, x, y + height-1);
        gdk_draw_line(window, tl_gc, x, y, x + width-1, y);
      } 
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

/* This function is a simple homegrown function wrapper around
 * do_draw_shadow_with_gap.
 */
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
		       gint gap_size)
{
  gint i;
  for (i=0;i<thickness;i++) {
    gint gap_thick = thickness - i - 1;
    do_draw_shadow_with_gap(window, area, tl_gc, br_gc, x+i, y+i, width-i*2, height-i*2, gap_side, gap_pos+gap_thick, gap_size-gap_thick, FALSE);
  }  
}

void
do_draw_option_shadow(GdkWindow * window,
	       GdkRectangle * area,
               GdkGC * tl_gc,
               GdkGC * br_gc,
	       gint x,
	       gint y,
	       gint width,
	       gint height)
{
  if (area)
    {
      gdk_gc_set_clip_rectangle(tl_gc, area);
      gdk_gc_set_clip_rectangle(br_gc, area);
    }

  gdk_draw_arc(window, tl_gc, FALSE, x, y, width, height, 45 * 64, 225 * 64);
  gdk_draw_arc(window, br_gc, FALSE, x, y, width, height, 225 * 64, 180 * 64);

  if (area)
    {
      gdk_gc_set_clip_rectangle(tl_gc, NULL);
      gdk_gc_set_clip_rectangle(br_gc, NULL);
    }
}

void
do_draw_option_bevel(GdkWindow * window,
                       GdkRectangle * area,
		       GdkGC * tl_gc,
		       GdkGC * br_gc,
		       gint x,
		       gint y,
		       gint width,
		       gint height,
		       gint thickness)
{
  gint i;
  for (i=0;i<thickness;i++) {
    gint gap_thick = thickness - i - 1;
    do_draw_option_shadow(window, area, tl_gc, br_gc, x+i, y+i, width-i*2, height-i*2);
  }  
}

void
draw_check_mark(GdkWindow * window,
                GdkGC * gc,
		GdkRectangle * area,
		gint x,
		gint y,
		gint width,
		gint height,
		gint check_style)
{
   switch (check_style) {
      case FAST_CHECK : /* most common style */
        gdk_draw_line(window, gc, x, y+height-1, x, y+(height/2)-1);
        gdk_draw_line(window, gc, x+1, y+height-1, x+1, y+(height/2)-1);
        gdk_draw_line(window, gc, x+1, y+height-1, x+width, y - 1);
        gdk_draw_line(window, gc, x, y+height-1, x+width, y);
	break;
      case SLOPPY_CHECK : /* default theme style, not done so just fall through*/
      case CLEAN_CHECK :/* classic redmond style */
	x+=1;
	y+=1; 
	width-=2;
        height-=2; 

        /* short diagonal */
	gdk_draw_line(window, gc, x+0, y+height-5, x+0, y+height-2);/* Left Line */
        gdk_draw_line(window, gc, x+1, y+height-4, x+1, y+height-1);/* Right Line */

        /* Long Diagonal */
        gdk_draw_line(window, gc, x+2, y+height-3, x+width-1, y+0);/* Top Line */
        gdk_draw_line(window, gc, x+2, y+height-2, x+width-1, y+1);/* Center Line */
        gdk_draw_line(window, gc, x+2, y+height-1, x+width-1, y+2);/* Bottom Line */
	break;
      case X_CHECK : /* common(default?) style in kde themes */
        {
	  GdkGC * line_gc = NULL;
          if (width>=16) 
	  {
  	    GdkGCValues gc_vals;
	    gint off_1, off_2, off_3;
            gint line_width = ceil(((width + 1)/5));
	
	    if (!(line_width % 2)) line_width -= 1;
	    gdk_gc_get_values(gc, &gc_vals);
	    gc_vals.line_width = line_width;
	    gc_vals.cap_style = GDK_CAP_ROUND;

	    off_2 = gc_vals.line_width;
	    off_1 = off_2 - 1;
	    off_3 = off_2 + 1;

              line_gc = gdk_gc_new_with_values(window, &gc_vals,   GDK_GC_FOREGROUND | GDK_GC_BACKGROUND | GDK_GC_FUNCTION |
              GDK_GC_CLIP_MASK | GDK_GC_CLIP_X_ORIGIN | GDK_GC_CLIP_Y_ORIGIN | GDK_GC_LINE_WIDTH | GDK_GC_LINE_STYLE |
	      GDK_GC_CAP_STYLE);

  	    /* Backward Diagonal */
            gdk_draw_line(window, line_gc, x+off_1, y+off_1, x+width-off_2, y+height-off_2);/* Center Line */

            /* Forward Diagonal */
            gdk_draw_line(window, line_gc, x+off_1, y+height - off_2, x+width-off_2, y+off_1);/* Center Line */

  	    gdk_gc_unref(line_gc);
	  } else {
	    /* Backward Diagonal */
            if (width>=7) 
	      gdk_draw_line(window, gc, x+2, y+1, x+width-2, y+height-3);/* Top Line */
            gdk_draw_line(window, gc, x+1, y+1, x+width-2, y+height-2);/* Center Line */
            if (width>=7) 
              gdk_draw_line(window, gc, x+1, y+2, x+width-3, y+height-2);/* Bottom Line */

            /* Forward Diagonal */
            if (width>=7) 
              gdk_draw_line(window, gc, x+1, y+height-3, x+width-3, y+1);/* Top Line */
            gdk_draw_line(window, gc, x+1, y+height - 2, x+width-2, y+1);/* Center Line */
            if (width>=7) 
              gdk_draw_line(window, gc, x+2, y+height - 2, x+width-2, y+2);/* Bottom Line */
          }	  
	}
	break;	
      case BLOCK_CHECK : /* square check style, like mist */
        gdk_draw_rectangle(window, gc, TRUE, x+1, y+1, width-2, height-2); 
	break;	
      case CIRCLE_CHECK : /* round check style, like mist, but with circles */
        gdk_draw_arc(window, gc, TRUE, x + width / 4, y + height / 4, width / 2 + 1, height / 2 + 1, 0, 360*64); 
        gdk_draw_arc(window, gc, FALSE, x + width / 4, y + height / 4, width / 2 + 1, height / 2 + 1, 0, 360*64); 
	break;	
      case DIAMOND_CHECK : /* diamond check style, like mist, but with diamonds */
	{
	  GdkPoint * points = g_new(GdkPoint, 5);
          
	  x+=1;
	  y+=1; 
	  width-=2;
	  height-=2; 
	  
	  points[0].x = x + width/2;
	  points[0].y = y;

	  points[1].x = x + width;
	  points[1].y = y + height/2;

	  points[2].x = x + width/2;
	  points[2].y = y + height;
	  
	  points[3].x = x;
	  points[3].y = y + height/2;

	  points[4].x = x + width/2;
	  points[4].y = y;
	  
	  gdk_draw_polygon(window, gc, TRUE, points, 5);
	  gdk_draw_polygon(window, gc, FALSE, points, 5);
	  
	  g_free(points);
	}
	break;	
      case XPM_CHECK : /* custom check in xpm format */
	break;	
      case NO_CHECK :
      default :
        return;
   }   
}

gboolean 
TranslateCheckStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("none"))
    *retval = NO_CHECK;
  else if (is_enum("fast"))
    *retval = FAST_CHECK;
  else if (is_enum("sloppy"))
    *retval = SLOPPY_CHECK;
  else if (is_enum("clean"))
    *retval = CLEAN_CHECK;
  else if (is_enum("criss_cross") || is_enum("criss-cross") || is_enum("crisscross") || is_enum("x"))
    *retval = X_CHECK;
  else if (is_enum("block") || is_enum("square") || is_enum("box"))
    *retval = BLOCK_CHECK;
  else if (is_enum("circle") || is_enum("round"))
    *retval = CIRCLE_CHECK;
  else if (is_enum("diamond"))
    *retval = DIAMOND_CHECK;
  else if (is_enum("xpm"))
    *retval = XPM_CHECK;
  else
    return FALSE; 

  return TRUE;
}

gboolean 
TranslateEdgeStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("none"))
    *retval = NO_EDGE;
  else if (is_enum("line") || is_enum("normal") || is_enum("default") || is_enum("standard"))
    *retval = LINE_EDGE;
  else if (is_enum("gradient"))
    *retval = GRADIENT_EDGE;
  else if (is_enum("xpm"))
    *retval = XPM_EDGE;
  else
    return FALSE; 

  return TRUE;
}
