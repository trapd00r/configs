/* #define DEBUG 1 */

#include <gtk/gtk.h>

#include "lighthouseblue_style.h"
#include "lighthouseblue_rc_style.h"

#include <string.h>


#define SCALE_SIZE 5

#define DETAIL(xx)   ((detail) && (!strcmp(xx, detail)))


static void lighthouseblue_style_init       (LighthouseBlueStyle      *style);
static void lighthouseblue_style_class_init (LighthouseBlueStyleClass *klass);

static GtkStyleClass *parent_class = NULL;


static void
rgb_to_hls (gdouble *r,
            gdouble *g,
            gdouble *b)
{
  gdouble min;
  gdouble max;
  gdouble red;
  gdouble green;
  gdouble blue;
  gdouble h, l, s;
  gdouble delta;
  
  red = *r;
  green = *g;
  blue = *b;
  
  if (red > green)
    {
      if (red > blue)
        max = red;
      else
        max = blue;
      
      if (green < blue)
        min = green;
      else
        min = blue;
    }
  else
    {
      if (green > blue)
        max = green;
      else
        max = blue;
      
      if (red < blue)
        min = red;
      else
        min = blue;
    }
  
  l = (max + min) / 2;
  s = 0;
  h = 0;
  
  if (max != min)
    {
      if (l <= 0.5)
        s = (max - min) / (max + min);
      else
        s = (max - min) / (2 - max - min);
      
      delta = max -min;
      if (red == max)
        h = (green - blue) / delta;
      else if (green == max)
        h = 2 + (blue - red) / delta;
      else if (blue == max)
        h = 4 + (red - green) / delta;
      
      h *= 60;
      if (h < 0.0)
        h += 360;
    }
  
  *r = h;
  *g = l;
  *b = s;
}

static void
hls_to_rgb (gdouble *h,
            gdouble *l,
            gdouble *s)
{
  gdouble hue;
  gdouble lightness;
  gdouble saturation;
  gdouble m1, m2;
  gdouble r, g, b;
  
  lightness = *l;
  saturation = *s;
  
  if (lightness <= 0.5)
    m2 = lightness * (1 + saturation);
  else
    m2 = lightness + saturation - lightness * saturation;
  m1 = 2 * lightness - m2;
  
  if (saturation == 0)
    {
      *h = lightness;
      *l = lightness;
      *s = lightness;
    }
  else
    {
      hue = *h + 120;
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        r = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        r = m2;
      else if (hue < 240)
        r = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        r = m1;
      
      hue = *h;
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        g = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        g = m2;
      else if (hue < 240)
        g = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        g = m1;
      
      hue = *h - 120;
      while (hue > 360)
        hue -= 360;
      while (hue < 0)
        hue += 360;
      
      if (hue < 60)
        b = m1 + (m2 - m1) * hue / 60;
      else if (hue < 180)
        b = m2;
      else if (hue < 240)
        b = m1 + (m2 - m1) * (240 - hue) / 60;
      else
        b = m1;
      
      *h = r;
      *l = g;
      *s = b;
    }
}

static void
shade (GdkColor * a, GdkColor * b, float k)
{
  gdouble red;
  gdouble green;
  gdouble blue;
  
  red = (gdouble) a->red / 65535.0;
  green = (gdouble) a->green / 65535.0;
  blue = (gdouble) a->blue / 65535.0;
  
  rgb_to_hls (&red, &green, &blue);
  
  green *= k;
  if (green > 1.0)
    green = 1.0;
  else if (green < 0.0)
    green = 0.0;
  
  blue *= k;
  if (blue > 1.0)
    blue = 1.0;
  else if (blue < 0.0)
    blue = 0.0;
  
  hls_to_rgb (&red, &green, &blue);
  
  b->red = red * 65535.0;
  b->green = green * 65535.0;
  b->blue = blue * 65535.0;
}



static void
calculate_arrow_geometry (GtkArrowType  arrow_type,
			  gint         *x,
			  gint         *y,
			  gint         *width,
			  gint         *height)
{
  gint w = *width;
  gint h = *height;
  
  switch (arrow_type)
    {
    case GTK_ARROW_UP:
    case GTK_ARROW_DOWN:
      w += (w % 2) - 1;
      h = (w / 2 + 1);
      
      if (h > *height)
	{
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

static gboolean sanitize_size (GdkWindow  *window,
			       gint       *width,
			       gint       *height)
{
  gboolean set_bg = FALSE;

  if ((*width == -1) && (*height == -1))
    {
      set_bg = GDK_IS_WINDOW (window);
      gdk_window_get_size (window, width, height);
    }
  else if (*width == -1)
    gdk_window_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_window_get_size (window, NULL, height);

  return set_bg;
}

static void theme_draw_rectangle (GdkDrawable      *drawable,
				  GdkGC            *gc,
				  gint              filled,
				  gint              x,
				  gint              y,
				  gint              width,
				  gint              height)
{
      gdk_draw_line (drawable, gc, x + 1, y, x + width - 1, y);
      gdk_draw_line (drawable, gc, x + 1, y + height, x + width - 1, y + height);
  
      gdk_draw_line (drawable, gc, x, y + 1, x, y + height - 1);
      gdk_draw_line (drawable, gc, x + width, y + 1, x + width, y + height - 1);
}

static void draw_hline (GtkStyle        *style,
			GdkWindow       *window,
			GtkStateType     state_type,
			GdkRectangle    *area,
			GtkWidget       *widget,
			const gchar     *detail,
			gint             x1,
			gint             x2,
			gint             y)
{
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  if (area)
    {
      gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2], area);
    }
  
  if (DETAIL ("label"))
    {
      if (state_type == GTK_STATE_INSENSITIVE)
        gdk_draw_line (window, style->white_gc, x1 + 1, y + 1, x2 + 1, y + 1);   
      gdk_draw_line (window, style->fg_gc[state_type], x1, y, x2, y);     
    }
  else
    {
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2],
		     x1, y, x2, y);
      if (DETAIL ("menuitem"))
	gdk_draw_line (window, style->white_gc,
		       x1, y+1, x2, y+1);
      
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2], NULL);
    }
}

static void draw_vline (GtkStyle        *style,
			GdkWindow       *window,
			GtkStateType     state_type,
			GdkRectangle    *area,
			GtkWidget       *widget,
			const gchar     *detail,
			gint             y1,
			gint             y2,
			gint             x)
{
  gint thickness_light;
  gint thickness_dark;
  
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  thickness_light = style->xthickness / 2;
  thickness_dark = style->xthickness - thickness_light;
  
  if (area)
    {
      gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2], area);
    }
  
  gdk_draw_line (window, style->dark_gc[state_type], x, y1, x, y2 - 1);
  
  if (area)
    {
      gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2], NULL);
    }
}

static void draw_shadow (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 GtkShadowType    shadow_type,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 gint             width,
			 gint             height)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *outer_gc = NULL;

  gint thickness_light;
  gint thickness_dark;
  gint i;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  if (DETAIL ("frame") && widget && widget->parent && GTK_IS_STATUSBAR (widget->parent))
    {
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x, y, width, height);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], area);
	}
      
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3],
		     x, y, x + width, y);
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0],
		     x, y + 1, x + width, y + 1);
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], NULL);
	}
      return;
    }

  
  sanitize_size (window, &width, &height);

  /* Make sure stepper and slider outlines "overlap" */
  if (DETAIL("slider") && widget && GTK_IS_RANGE (widget))
    {
      GtkAdjustment *adj = GTK_RANGE (widget)->adjustment;

      if (adj->value <= adj->lower &&
	  (GTK_RANGE (widget)->has_stepper_a ||
	   GTK_RANGE (widget)->has_stepper_b))
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
      if (adj->value >= adj->upper - adj->page_size &&
	  (GTK_RANGE (widget)->has_stepper_c ||
	   GTK_RANGE (widget)->has_stepper_d))
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
  
  if (detail &&
      ((strcmp (detail, "button") == 0) ||
       (strcmp (detail, "togglebutton") == 0) ||
       (strcmp (detail, "optionmenu") == 0) ||
       (strcmp (detail, "slider") == 0) ||
       (strcmp (detail, "vscrollbar") == 0) || 
       (strcmp (detail, "hscrollbar") == 0))) 
    outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];
  else
    outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
    
  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      return;
    case GTK_SHADOW_IN:
    case GTK_SHADOW_ETCHED_IN:
      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      break;
    case GTK_SHADOW_OUT:
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      gc2 = style->white_gc;
      break;
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
      if (shadow_type == GTK_SHADOW_IN || 
          shadow_type == GTK_SHADOW_OUT)
	{
	  gdk_gc_set_clip_rectangle (outer_gc, area);
	  gdk_gc_set_clip_rectangle (style->black_gc, area);
	}
    }
  
  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      break;
      
    case GTK_SHADOW_IN:
      if (widget && GTK_WIDGET_HAS_DEFAULT (widget) &&
	  detail && (strcmp (detail, "button") == 0))
	theme_draw_rectangle (window, style->black_gc, FALSE,
			      x, y, width - 1, height - 1);
      else if (DETAIL ("slider"))
	{
	  gdk_draw_rectangle (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], FALSE, x, y, width - 1, height - 1);
	  theme_draw_rectangle (window, outer_gc, FALSE, x, y, width - 1, height - 1);	  
	}
      else
	{
	  theme_draw_rectangle (window, outer_gc, FALSE, x, y, width - 1, height - 1);
	}

      if (detail &&
	  ((strcmp (detail, "button") == 0) ||
	   (strcmp (detail, "togglebutton") == 0) ||
	   (strcmp (detail, "handlebox") == 0) ||
	   (strcmp (detail, "optionmenu") == 0) ||
	   (strcmp (detail, "notebook") == 0) ||
	   (strcmp (detail, "menu") == 0) ||
	   (strcmp (detail, "slider") == 0) ||
	   (strcmp (detail, "spinbutton_up") == 0) ||
	   (strcmp (detail, "spinbutton_down") == 0) ||
	   (strcmp (detail, "vscrollbar") == 0) ||
	   (strcmp (detail, "hscrollbar") == 0) ||
	   (strcmp (detail, "stepper") == 0)))
	{
      
      /* Light around right and bottom edge */

      if (style->ythickness > 0)
        gdk_draw_line (window, gc1,
                       x + 1, y + height - 2, x + width - 2, y + height - 2);
      if (style->xthickness > 0)
        gdk_draw_line (window, gc1,
                       x + width - 2, y + 1, x + width - 2, y + height - 2);

      /* Dark around left and top */

      if (style->ythickness > 0)
        gdk_draw_line (window, gc2,
                       x + 1, y + 1, x + width - 3, y + 1);
      if (style->xthickness > 0)
        gdk_draw_line (window, gc2,
                       x + 1, y + 1, x + 1, y + height - 3);
	}
      break;
      
    case GTK_SHADOW_OUT:
      if (widget && GTK_WIDGET_HAS_DEFAULT (widget) &&
	  detail && (strcmp (detail, "button") == 0))
	theme_draw_rectangle (window, style->black_gc, FALSE,
			    x, y, width - 1, height - 1);
      else if (DETAIL ("slider"))
	{
	  gdk_draw_rectangle (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], FALSE, x, y, width - 1, height - 1);
	  theme_draw_rectangle (window, outer_gc, FALSE, x, y, width - 1, height - 1);	  
	}
      else
	theme_draw_rectangle (window, outer_gc, FALSE,
			    x, y, width - 1, height - 1);

      if (detail &&
	  ((strcmp (detail, "button") == 0) ||
	   (strcmp (detail, "togglebutton") == 0) ||
	   (strcmp (detail, "handlebox") == 0) ||
	   (strcmp (detail, "optionmenu") == 0) ||
	   (strcmp (detail, "notebook") == 0) ||
	   (strcmp (detail, "slider") == 0) ||
	   (strcmp (detail, "spinbutton_up") == 0) ||
	   (strcmp (detail, "spinbutton_down") == 0) ||
	   (strcmp (detail, "menu") == 0) ||
	   (strcmp (detail, "menuitem") == 0) ||
	   (strcmp (detail, "vscrollbar") == 0) ||
	   (strcmp (detail, "hscrollbar") == 0) ||
	   (strcmp (detail, "stepper") == 0)))
	{
	  /* Dark around right and bottom edge */
	  if (style->ythickness > 0)
	    gdk_draw_line (window, gc1,
			   x + 2, y + height - 2, x + width - 2, y + height - 2);
	  if (style->xthickness > 0)
	    gdk_draw_line (window, gc1,
			   x + width - 2, y + 2, x + width - 2, y + height - 2);
	  
	  /* Light around top and left */
	  
	  if (style->ythickness > 0)
	    gdk_draw_line (window, gc2,
			   x + 1, y + 1, x + width - 2, y + 1);
	  if (style->xthickness > 0)
	    gdk_draw_line (window, gc2,
			   x + 1, y + 1, x + 1, y + height - 2);
	}      
      break;
      
    case GTK_SHADOW_ETCHED_IN:
    case GTK_SHADOW_ETCHED_OUT:
      if (style->xthickness > 0)
        {
          if (style->xthickness > 1)
            {
              thickness_light = 1;
              thickness_dark = 1;
      
              for (i = 0; i < thickness_dark; i++)
                {
                  gdk_draw_line (window, gc1,
                                 x + width - i - 1,
                                 y + i,
                                 x + width - i - 1,
                                 y + height - i - 1);
                  gdk_draw_line (window, gc2,
                                 x + i,
                                 y + i,
                                 x + i,
                                 y + height - i - 2);
                }
      
              for (i = 0; i < thickness_light; i++)
                {
                  gdk_draw_line (window, gc1,
                                 x + thickness_dark + i,
                                 y + thickness_dark + i,
                                 x + thickness_dark + i,
                                 y + height - thickness_dark - i - 1);
                  gdk_draw_line (window, gc2,
                                 x + width - thickness_light - i - 1,
                                 y + thickness_dark + i,
                                 x + width - thickness_light - i - 1,
                                 y + height - thickness_light - 1);
                }
            }
          else
            {
              gdk_draw_line (window, 
                             style->dark_gc[state_type],
                             x, y, x, y + height);                         
              gdk_draw_line (window, 
                             style->dark_gc[state_type],
                             x + width, y, x + width, y + height);
            }
        }

      if (style->ythickness > 0)
        {
          if (style->ythickness > 1)
            {
              thickness_light = 1;
              thickness_dark = 1;
      
              for (i = 0; i < thickness_dark; i++)
                {
                  gdk_draw_line (window, gc1,
                                 x + i,
                                 y + height - i - 1,
                                 x + width - i - 1,
                                 y + height - i - 1);
          
                  gdk_draw_line (window, gc2,
                                 x + i,
                                 y + i,
                                 x + width - i - 2,
                                 y + i);
                }
      
              for (i = 0; i < thickness_light; i++)
                {
                  gdk_draw_line (window, gc1,
                                 x + thickness_dark + i,
                                 y + thickness_dark + i,
                                 x + width - thickness_dark - i - 1,
                                 y + thickness_dark + i);
          
                  gdk_draw_line (window, gc2,
                                 x + thickness_dark + i,
                                 y + height - thickness_light - i - 1,
                                 x + width - thickness_light - 1,
                                 y + height - thickness_light - i - 1);
                }
            }
          else
            {
              gdk_draw_line (window, 
                             style->dark_gc[state_type],
                             x, y, x + width, y);
              gdk_draw_line (window, 
                             style->dark_gc[state_type],
                             x, y + height, x + width, y + height);
            }
        }
      
      break;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
      if (shadow_type == GTK_SHADOW_IN || 
          shadow_type == GTK_SHADOW_OUT)
	{
	  gdk_gc_set_clip_rectangle (outer_gc, NULL);
	  gdk_gc_set_clip_rectangle (style->black_gc, NULL);
	}
    }
    

  if (shadow_type == GTK_SHADOW_IN &&
      widget && GTK_IS_SPIN_BUTTON (widget) &&
      detail && strcmp (detail, "entry") == 0)
    {
      gc1 = style->base_gc[GTK_WIDGET_STATE(widget)];
      
      if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_LTR)
	{
	  gdk_draw_line (window,
			 gc1,
			 x + width - 1, y + 1,
			 x + width - 1, y + height - 2);
	  gdk_draw_line (window,
			 gc1,
			 x + width - 2, y + 1,
			 x + width - 2, y + height - 2);
	  gdk_draw_point (window,
			  (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[1],
			  x + width - 1, y + 1);
	}
      else
	{
	  gdk_draw_line (window,
			 gc1,
			 x, y + 1,
			 x, y + height - 2);
	  gdk_draw_line (window,
			 gc1,
			 x + 1, y + 1,
			 x + 1, y + height - 2);
	  gdk_draw_point (window,
			  (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[1],
			  x, y + height - 1);
	}
    }

  if (shadow_type == GTK_SHADOW_IN &&
      widget && DETAIL ("entry"))
    {
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[1];
      if (area)
	gdk_gc_set_clip_rectangle (gc1, area);
      
      gdk_draw_line (window, 
		     gc1,
		     x + 1, y + 1, x + width - 2, y + 1);
      
      gdk_draw_line (window, 
		     gc1,
		     x + 1, y + 1, x + 1, y + height - 2);
      if (area)
	gdk_gc_set_clip_rectangle (gc1, NULL);
    }
}

static void draw_polygon (GtkStyle        *style,
			  GdkWindow       *window,
			  GtkStateType     state_type,
			  GtkShadowType    shadow_type,
			  GdkRectangle    *area,
			  GtkWidget       *widget,
			  const gchar     *detail,
			  GdkPoint        *points,
			  gint             npoints,
			  gboolean         fill)
{
  g_message ("DRAW POLYGON");
  parent_class->draw_polygon (style, window, state_type, shadow_type, area, widget, detail, points, npoints, fill);
}


static void draw_arrow (GtkStyle        *style,
			GdkWindow       *window,
			GtkStateType     state_type,
			GtkShadowType    shadow_type,
			GdkRectangle    *area,
			GtkWidget       *widget,
			const gchar     *detail,
			GtkArrowType     arrow_type,
			gboolean         fill,
			gint             x,
			gint             y,
			gint             width,
			gint             height)
{
  gint i, j;
  gint orig_width, orig_x;
  GdkGC *gc;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  if (DETAIL ("menuitem") && state_type == GTK_STATE_INSENSITIVE)
    {
      return;
    }

  sanitize_size (window, &width, &height);

  orig_width = width;
  orig_x = x;

  if (DETAIL ("menuitem"))
    {
      height += 2;
    }

  if (DETAIL ("spinbutton"))
    {
      height += 1;
    }
  
  calculate_arrow_geometry (arrow_type, &x, &y, &width, &height);

  if (DETAIL ("menuitem"))
    {
      x = orig_x + orig_width - width;
    }

  if (DETAIL ("spinbutton") && (arrow_type == GTK_ARROW_DOWN))
    {
      y += 1;
    }

  if (DETAIL ("vscrollbar") || DETAIL ("hscrollbar"))
    {
      x += 1;
      y += 1;
    }

  switch (state_type)
    {
    case GTK_STATE_INSENSITIVE:
      gc = style->white_gc;
      break;
    case GTK_STATE_NORMAL:
      gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[7];
      break;
    default:
      gc = style->fg_gc[state_type];
    }

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

static void draw_diamond (GtkStyle        *style,
			  GdkWindow       *window,
			  GtkStateType     state_type,
			  GtkShadowType    shadow_type,
			  GdkRectangle    *area,
			  GtkWidget       *widget,
			  const gchar     *detail,
			  gint             x,
			  gint             y,
			  gint             width,
			  gint             height)
{}

static void draw_string (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 const gchar     *string)
{}

static void draw_box (GtkStyle        *style,
		      GdkWindow       *window,
		      GtkStateType     state_type,
		      GtkShadowType    shadow_type,
		      GdkRectangle    *area,
		      GtkWidget       *widget,
		      const gchar     *detail,
		      gint             x,
		      gint             y,
		      gint             width,
		      gint             height)
{
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  sanitize_size (window, &width, &height);

  /*printf ("draw_box: %p %p %s %i %i %i %i\n", widget, window, detail, x, y, width, height);*/

  if (widget && DETAIL ("trough")) /* Scrollbars */
    {
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[4], area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], area);
	}

      if GTK_IS_HSCALE (widget)
	{
	  y += (height - SCALE_SIZE) / 2;
	  height = SCALE_SIZE;
	}
      
      if GTK_IS_VSCALE (widget)
	{
	  x += (width - SCALE_SIZE) / 2;
	  width = SCALE_SIZE;
	}
      
      gdk_draw_rectangle (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3],
			  TRUE, x, y, width, height);
      gdk_draw_rectangle (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
			  FALSE, x, y, width - 1, height - 1);

      if (GTK_IS_HSCALE (widget) || GTK_IS_VSCALE (widget))
	{
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[4],
			 x + 1, y + 1,
			 x + width - 2, y + 1);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[4],
			 x + 1, y + 1,
			 x + 1, y + height - 2);
	}

      
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[4], NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], NULL);
	}

    }
  else if (widget && (DETAIL ("menubar") || DETAIL ("toolbar") || DETAIL ("dockitem_bin"))
	   && shadow_type != GTK_SHADOW_NONE)
    {
      /* Toolbars and menus */
      /*gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x, y, width, height);*/
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x + 1, y + 1, width - 2, height - 2);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], area);
	}

      if (!DETAIL ("menubar")) /* Only toolbars have the top line */
	{
	gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0],
		       x, y, x + width, y);
	}
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3],
		     x, y + height - 1, x + width, y + height - 1);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], NULL);
	}
    }
  else if (widget && DETAIL ("bar") && GTK_IS_PROGRESS_BAR (widget))
    {
      GtkProgressBarOrientation orientation;
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->base_gc[GTK_STATE_SELECTED], area);
	}
      
      orientation = gtk_progress_bar_get_orientation (GTK_PROGRESS_BAR (widget));

      if (orientation == GTK_PROGRESS_LEFT_TO_RIGHT || GTK_PROGRESS_RIGHT_TO_LEFT)
	{
	  if (width > 2)
	    {
	      width -= 1;
	    }
	}
      else
	{
	  if (height > 2)
	    {
	      height -= 1;
	    }
	}

      gdk_draw_rectangle (window, style->base_gc[GTK_STATE_SELECTED], TRUE,
			  x, y, width - 1,  height);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->base_gc[GTK_STATE_SELECTED], NULL);
	}
    }
  else if (widget && DETAIL ("menuitem"))
    {
      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	}
      
      gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE, x + 1, y + 1, width - 2, height - 2);
      theme_draw_rectangle (window, style->bg_gc[state_type], FALSE, x, y, width - 1, height - 1);

      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	}
    }
  /*else if (widget && DETAIL ("optionmenu"))
    {
      GtkRequisition indicator_size;
      GtkBorder indicator_spacing;
      
      if (!style->bg_pixmap[state_type] || 
	  GDK_IS_PIXMAP (window))
	{
	  if (area)
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	  
	  gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
			      x, y, width, height);
	  if (area)
	    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	}
      else
	gtk_style_apply_default_background (style, window,
					    widget && !GTK_WIDGET_NO_WINDOW (widget),
					    state_type, area, x, y, width, height);


      gtk_paint_shadow (style, window, state_type, shadow_type, area, widget, detail,
			x, y, width, height);
      
      option_menu_get_props (widget, &indicator_size, &indicator_spacing);

      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->white_gc, area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], area);
	}
      
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3],
		     x + width - (indicator_size.width + indicator_spacing.left + indicator_spacing.right) - style->xthickness,
		     y + style->ythickness - 1,
		     x + width - (indicator_size.width + indicator_spacing.left + indicator_spacing.right) - style->xthickness,
		     y + height - style->ythickness);
	
      gdk_draw_line (window, style->white_gc,
		     x + width - (indicator_size.width + indicator_spacing.left + indicator_spacing.right) - style->xthickness + 1,
		     y + style->ythickness,
		     x + width - (indicator_size.width + indicator_spacing.left + indicator_spacing.right) - style->xthickness + 1,
		     y + height - style->ythickness - 1);
	
		     
      if (area)
	{
	  gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], NULL);
	}
	}*/
  else if (widget &&
	   (DETAIL ("hscale") || DETAIL ("vscale")))
    {
      GdkGC *outer_gc = NULL;
      GdkGC *gc1 = NULL;
      GdkGC *gc2 = NULL;

      
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x + 1, y + 1, width - 2, height - 2);


      outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];

      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];

      if (area)
	{
	  gdk_gc_set_clip_rectangle (outer_gc, area);
	  gdk_gc_set_clip_rectangle (gc1, area);
	  gdk_gc_set_clip_rectangle (gc2, area);
	}

      gdk_draw_line (window, outer_gc,
		     x + 2, y, x + width - 3, y);
      gdk_draw_point (window, gc2,
		      x + 1, y);
      gdk_draw_point (window, gc2,
		      x + width - 2, y);
      
      gdk_draw_point (window, gc2,
		      x, y + 1);
      gdk_draw_point (window, outer_gc,
		      x + 1, y + 1);
      gdk_draw_line (window, gc1,
		     x + 2, y + 1, x + width - 3, y + 1);
      gdk_draw_point (window, outer_gc,
		      x + width - 2, y + 1);
      gdk_draw_point (window, gc2,
		      x + width - 1, y + 1);
      
      gdk_draw_line (window, outer_gc,
		     x, y + 2, x, y + height - 3);
      gdk_draw_line (window, gc1,
		     x + 1, y + 2, x + 1, y + height - 3);
      
      gdk_draw_line (window, gc2,
		     x + width - 2, y + 2, x + width - 2, y + height - 3);
      gdk_draw_line (window, outer_gc,
		     x + width - 1, y + 2, x + width - 1, y + height - 3);
      
      gdk_draw_point (window, gc2,
		      x, y + height - 2);
      gdk_draw_point (window, outer_gc,
		      x + 1, y + height - 2);
      gdk_draw_line (window, gc2,
		     x + 2, y + height - 2, x + width - 2, y + height - 2);
      gdk_draw_point (window, outer_gc,
		      x + width - 2, y + height - 2);
      gdk_draw_point (window, gc2,
		      x + width - 1, y + height - 2);
      
      gdk_draw_point (window, gc2,
		      x + 1, y + height - 1);
      gdk_draw_line (window, outer_gc,
		     x + 2, y + height - 1, x + width - 3, y + height - 1);
      gdk_draw_point (window, gc2,
		      x + width - 2, y + height - 1);

      if (area)
	{
	  gdk_gc_set_clip_rectangle (outer_gc, NULL);
	  gdk_gc_set_clip_rectangle (gc1, NULL);
	  gdk_gc_set_clip_rectangle (gc2, NULL);
	}

    }
  else if (DETAIL ("spinbutton_up") || DETAIL ("spinbutton_down"))
    {
      /* Make the top button overlap the first line of the bottom button */
      if (strcmp (detail, "spinbutton_up") == 0)
	height += 1;
      
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x, y, width, height);
      gtk_paint_shadow (style, window, state_type, shadow_type, area, widget, detail,
			x, y, width, height);
    }
  else
    {
      parent_class->draw_box (style, window, state_type, shadow_type, area,
			      widget, detail, x, y, width, height);
  
      /*
      if (!style->bg_pixmap[state_type] || GDK_IS_PIXMAP (window))
	{
	  if (area)
	    {
	      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	    }
	  
	  gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
			      x, y, width, height);
	  if (area)
	    {
	      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	    }
	}
      else
	{
	  gtk_style_apply_default_background (style, window,
					      widget && !GTK_WIDGET_NO_WINDOW (widget),
					      state_type, area, x + 1, y + 1, width - 2, height - 2);
	}
      */
      /*gtk_paint_shadow (style, window, state_type, shadow_type, area, widget, detail,
	x, y, width, height);*/

    }
}

static void draw_flat_box (GtkStyle        *style,
			   GdkWindow       *window,
			   GtkStateType     state_type,
			   GtkShadowType    shadow_type,
			   GdkRectangle    *area,
			   GtkWidget       *widget,
			   const gchar     *detail,
			   gint             x,
			   gint             y,
			   gint             width,
			   gint             height)
{
  GdkGC *gc1;
  GdkGC *freeme = NULL;
  
  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  sanitize_size (window, &width, &height);

  /*printf ("draw_flat_box: %p %p %s %i %i %i %i\n", widget, window, detail, x, y, width, height);*/

  if (detail)
    {
      if (state_type == GTK_STATE_SELECTED)
        {
          if (!strcmp ("text", detail))
            gc1 = style->bg_gc[GTK_STATE_SELECTED];
          else if (!strncmp ("cell_even", detail, strlen ("cell_even")) ||
		   !strncmp ("cell_odd", detail, strlen ("cell_odd")))
            {
	      /* This has to be really broken; alex made me do it. -jrb */
	      if (GTK_WIDGET_HAS_FOCUS (widget))
		gc1 = style->base_gc[state_type];
	      else 
		gc1 = style->base_gc[GTK_STATE_ACTIVE];
            }
          else
            {
              gc1 = style->bg_gc[state_type];
            }
        }
      else
        {
          if (!strcmp ("viewportbin", detail))
	    {
	      gc1 = style->bg_gc[GTK_STATE_NORMAL];
	    }
          else if (!strcmp ("entry_bg", detail))
	    {
	      gc1 = style->base_gc[state_type];
	    }

          /* For trees: even rows are base color, odd rows are a shade of
           * the base color, the sort column is a shade of the original color
           * for that row.
           */

          /* FIXME when we have style properties, clean this up.
           */
          
          else if (!strcmp ("cell_even", detail) ||
                   !strcmp ("cell_odd", detail) ||
                   !strcmp ("cell_even_ruled", detail))
            {
	      gc1 = style->base_gc[state_type];
            }
          /*else if (!strcmp ("cell_even_sorted", detail) ||
                   !strcmp ("cell_odd_sorted", detail) ||
                   !strcmp ("cell_odd_ruled", detail) ||
                   !strcmp ("cell_even_ruled_sorted", detail))
            {
	      freeme = get_darkened_gc (window, &style->base[state_type], 1);
              gc1 = freeme;
            }
          else if (!strcmp ("cell_odd_ruled_sorted", detail))
            {
              freeme = get_darkened_gc (window, &style->base[state_type], 2);
              gc1 = freeme;
	      }*/
          else
	    {
	      gc1 = style->bg_gc[state_type];
	    }
        }
    }
  else
    {
      gc1 = style->bg_gc[state_type];
    }

  if (!style->bg_pixmap[state_type] || gc1 != style->bg_gc[state_type] ||
      GDK_IS_PIXMAP (window))
    {
      if (area)
	{
	  gdk_gc_set_clip_rectangle (gc1, area);
	}
      if (state_type == GTK_STATE_SELECTED)
	{
	  if (GTK_IS_TREE_VIEW (widget) && (LIGHTHOUSEBLUE_RC_STYLE (style->rc_style))->combine_treeview_select)
	    {
	      GList *columns = gtk_tree_view_get_columns(GTK_TREE_VIEW (widget));
	      guint length = g_list_length (columns);
	      g_list_free (columns);

	      if (length > 1 && length < 3)
		{
		  if (x > 0)
		    {
		      gdk_draw_rectangle (window, gc1, TRUE, x, y, width - 3, height);
		      theme_draw_rectangle (window, gc1, FALSE, x, y, width - 3, height - 1);
		    }
		  else
		    {
		      gdk_draw_rectangle (window, gc1, TRUE, x + 3, y, width - 3, height);
		      theme_draw_rectangle (window, gc1, FALSE, x + 2, y, width - 3, height - 1);
		    }
		}
	      else
		{
		  gdk_draw_rectangle (window, gc1, TRUE, x + 3, y, width - 6, height - 1);
		  theme_draw_rectangle (window, gc1, FALSE, x + 2, y, width - 5, height - 1);
		}
	    }
	  else
	    {
	      gdk_draw_rectangle (window, gc1, TRUE, x + 3, y, width - 6, height - 1);
	      theme_draw_rectangle (window, gc1, FALSE, x + 2, y, width - 5, height - 1);
	    }
	}
      else
	{
	  gdk_draw_rectangle (window, gc1, TRUE, x, y, width, height);
	}

      if (detail && !strcmp ("tooltip", detail))
	{
	  gdk_draw_rectangle (window, style->black_gc, FALSE,
			      x, y, width - 1, height - 1);
	}

      if (area)
	{
	  gdk_gc_set_clip_rectangle (gc1, NULL);
	}
    }
  else
    {
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x, y, width, height);
    }

  if (freeme)
    g_object_unref (G_OBJECT (freeme));
}

static void draw_check (GtkStyle        *style,
			GdkWindow       *window,
			GtkStateType     state_type,
			GtkShadowType    shadow_type,
			GdkRectangle    *area,
			GtkWidget       *widget,
			const gchar     *detail,
			gint             x,
			gint             y,
			gint             width,
			gint             height)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC* mark_gc = NULL;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  if (DETAIL ("check")) /* Menu item */
    {
      parent_class->draw_check (style, window, state_type, shadow_type, area, 
				widget, detail, x, y, width, height);
      return;
    }

  gc1 = style->base_gc[GTK_STATE_NORMAL];
  gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
  mark_gc = style->base_gc[GTK_STATE_SELECTED];

  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
      gdk_gc_set_clip_rectangle (mark_gc, area);
    }
  
  gdk_draw_rectangle (window, gc1, TRUE, x + 1, y + 1, 10, 10);
  theme_draw_rectangle (window, gc2, FALSE, x, y, 11, 11);

  if (shadow_type == GTK_SHADOW_IN)
    {
      gdk_draw_line (window, mark_gc, x + 3, y + 5, x + 3, y + 9);
      gdk_draw_line (window, mark_gc, x + 4, y + 5, x + 4, y + 9);

      gdk_draw_line (window, mark_gc, x + 5, y + 8, x + 9, y + 4);
      gdk_draw_line (window, mark_gc, x + 5, y + 7, x + 9, y + 3);
    }
  else if (shadow_type == GTK_SHADOW_ETCHED_IN) /* inconsistent */
    {
      gdk_draw_rectangle (window, mark_gc, TRUE, x + 3, y + 5, 6, 2);
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
      gdk_gc_set_clip_rectangle (mark_gc, NULL);
    }
}

static void draw_option (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 GtkShadowType    shadow_type,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 gint             width,
			 gint             height)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC* mark_gc = NULL;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  if (DETAIL ("option")) /* Menu item */
    {
      parent_class->draw_option (style, window, state_type, shadow_type, area,
				 widget, detail, x, y, width, height);
      return;
    }

  gc1 = style->base_gc[GTK_STATE_NORMAL];
  gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
  mark_gc = style->base_gc[GTK_STATE_SELECTED];

  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
      gdk_gc_set_clip_rectangle (mark_gc, area);
    }

  gdk_draw_arc(window, gc1, TRUE, x, y, width - 1, height - 1, 0, 360 * 64);
  gdk_draw_arc(window, gc2, FALSE, x, y, width - 1, height - 1, 0, 360 * 64);

  if (shadow_type == GTK_SHADOW_IN)
    {
      gdk_draw_arc(window, mark_gc, TRUE, x + 2, y + 2, width - 5, height - 5, 0, 360 * 64);
    }
  else if (shadow_type == GTK_SHADOW_ETCHED_IN) /* inconsistent */
    {
      gdk_draw_rectangle (window, mark_gc, TRUE, x + 3, y + 5, 6, 2);
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
      gdk_gc_set_clip_rectangle (mark_gc, NULL);
    }
}

static void draw_tab (GtkStyle        *style,
		      GdkWindow       *window,
		      GtkStateType     state_type,
		      GtkShadowType    shadow_type,
		      GdkRectangle    *area,
		      GtkWidget       *widget,
		      const gchar     *detail,
		      gint             x,
		      gint             y,
		      gint             width,
		      gint             height)
{}

static void draw_shadow_gap (GtkStyle        *style,
			     GdkWindow       *window,
			     GtkStateType     state_type,
			     GtkShadowType    shadow_type,
			     GdkRectangle    *area,
			     GtkWidget       *widget,
			     const gchar     *detail,
			     gint             x,
			     gint             y,
			     gint             width,
			     gint             height,
			     GtkPositionType  gap_side,
			     gint             gap_x,
			     gint             gap_width)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *gc3 = NULL;
  GdkGC *gc4 = NULL;
  GdkGC *outer_gc = NULL;
  
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  sanitize_size (window, &width, &height);
  
  outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];
  
  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      return;
    case GTK_SHADOW_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[1];
      gc3 = style->white_gc;
      gc4 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
      break;
    case GTK_SHADOW_ETCHED_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3];
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0];
      gc3 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3];
      gc4 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0];
      break;
    case GTK_SHADOW_OUT:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
      gc2 = style->white_gc;
      gc3 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[1];
      gc4 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0];
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3];
      gc3 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0];
      gc4 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3];
      break;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, area);
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
      gdk_gc_set_clip_rectangle (gc3, area);
      gdk_gc_set_clip_rectangle (gc4, area);
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
          gdk_draw_line (window, gc1,
                         x, y, x, y + height - 1);
          gdk_draw_line (window, gc2,
                         x + 1, y, x + 1, y + height - 2);
          
          gdk_draw_line (window, gc3,
                         x + 1, y + height - 2, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc3,
                         x + width - 2, y, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc4,
                         x, y + height - 1, x + width - 1, y + height - 1);
          gdk_draw_line (window, gc4,
                         x + width - 1, y, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, gc1,
                             x, y, x + gap_x - 1, y);
              gdk_draw_line (window, gc2,
                             x + 1, y + 1, x + gap_x - 1, y + 1);
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, gc1,
                             x + gap_x + gap_width, y, x + width - 2, y);
              gdk_draw_line (window, gc2,
                             x + gap_x + gap_width, y + 1, x + width - 3, y + 1);
            }
          break;
        case GTK_POS_BOTTOM:
          gdk_draw_line (window, gc1,
                         x, y, x + width - 1, y);
          gdk_draw_line (window, gc1,
                         x, y, x, y + height - 1);
          gdk_draw_line (window, gc2,
                         x + 1, y + 1, x + width - 2, y + 1);
          gdk_draw_line (window, gc2,
                         x + 1, y + 1, x + 1, y + height - 1);
          
          gdk_draw_line (window, gc3,
                         x + width - 2, y + 1, x + width - 2, y + height - 1);
          gdk_draw_line (window, gc4,
                         x + width - 1, y, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, gc4,
                             x, y + height - 1, x + gap_x - 1, y + height - 1);
              gdk_draw_line (window, gc3,
                             x + 1, y + height - 2, x + gap_x - 1, y + height - 2);
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, gc4,
                             x + gap_x + gap_width, y + height - 1, x + width - 2, y + height - 1);
              gdk_draw_line (window, gc3,
                             x + gap_x + gap_width, y + height - 2, x + width - 2, y + height - 2);
            }
          break;
        case GTK_POS_LEFT:
          gdk_draw_line (window, gc1,
                         x, y, x + width - 1, y);
          gdk_draw_line (window, gc2,
                         x, y + 1, x + width - 2, y + 1);
          
          gdk_draw_line (window, gc3,
                         x, y + height - 2, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc3,
                         x + width - 2, y + 1, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc4,
                         x, y + height - 1, x + width - 1, y + height - 1);
          gdk_draw_line (window, gc4,
                         x + width - 1, y, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, gc1,
                             x, y, x, y + gap_x - 1);
              gdk_draw_line (window, gc2,
                             x + 1, y + 1, x + 1, y + gap_x - 1);
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, gc1,
                             x, y + gap_x + gap_width, x, y + height - 2);
              gdk_draw_line (window, gc2,
                             x + 1, y + gap_x + gap_width, x + 1, y + height - 2);
            }
          break;
        case GTK_POS_RIGHT:
          gdk_draw_line (window, gc1,
                         x, y, x + width - 1, y);
          gdk_draw_line (window, gc1,
                         x, y, x, y + height - 1);
          gdk_draw_line (window, gc2,
                         x + 1, y + 1, x + width - 1, y + 1);
          gdk_draw_line (window, gc2,
                         x + 1, y + 1, x + 1, y + height - 2);
          
          gdk_draw_line (window, gc3,
                         x + 1, y + height - 2, x + width - 1, y + height - 2);
          gdk_draw_line (window, gc4,
                         x, y + height - 1, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, gc4,
                             x + width - 1, y, x + width - 1, y + gap_x - 1);
              gdk_draw_line (window, gc3,
                             x + width - 2, y + 1, x + width - 2, y + gap_x - 1);
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, gc4,
                             x + width - 1, y + gap_x + gap_width, x + width - 1, y + height - 2);
              gdk_draw_line (window, gc3,
                             x + width - 2, y + gap_x + gap_width, x + width - 2, y + height - 2);
            }
          break;
        }
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, NULL);
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
      gdk_gc_set_clip_rectangle (gc3, NULL);
      gdk_gc_set_clip_rectangle (gc4, NULL);
    }
}

static void draw_box_gap (GtkStyle        *style,
			  GdkWindow       *window,
			  GtkStateType     state_type,
			  GtkShadowType    shadow_type,
			  GdkRectangle    *area,
			  GtkWidget       *widget,
			  const gchar     *detail,
			  gint             x,
			  gint             y,
			  gint             width,
			  gint             height,
			  GtkPositionType  gap_side,
			  gint             gap_x,
			  gint             gap_width)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *outer_gc = NULL;
  
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  switch (gap_side)
    {
    case GTK_POS_LEFT:
    case GTK_POS_RIGHT:
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x, y + 1, width, height - 2);  
      break;
    case GTK_POS_TOP:
    case GTK_POS_BOTTOM:
      gtk_style_apply_default_background (style, window,
					  widget && !GTK_WIDGET_NO_WINDOW (widget),
					  state_type, area, x + 1, y, width - 2, height);
      break;
    }  
  
  sanitize_size (window, &width, &height);

  outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];

  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      return;
    case GTK_SHADOW_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      gc2 = style->white_gc;
      break;
    case GTK_SHADOW_ETCHED_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      gc2 = style->white_gc;
      break;
    case GTK_SHADOW_OUT:
      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      break;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, area);
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
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
          gdk_draw_line (window, outer_gc,
                         x, y, x, y + height - 2);

          gdk_draw_line (window, gc1,
                         x + 1, y, x + 1, y + height - 2);
          
          gdk_draw_line (window, gc2,
                         x + 1, y + height - 2, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc2,
                         x + width - 2, y, x + width - 2, y + height - 2);

          gdk_draw_line (window, outer_gc,
                         x + 1, y + height - 1, x + width - 2, y + height - 1);
          gdk_draw_line (window, outer_gc,
                         x + width - 1, y, x + width - 1, y + height - 2);
          if (gap_x > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x, y, x + gap_x - 1, y);
              gdk_draw_line (window, gc1,
                             x + 1, y + 1, x + gap_x - 1, y + 1);
              /*gdk_draw_line (window, gc1,
		x + gap_x + 1, y, x + gap_x + 1, y);*/
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x + gap_x + gap_width, y, x + width - 2, y);
              gdk_draw_line (window, gc1,
                             x + gap_x + gap_width, y + 1, x + width - 2, y + 1);
              /*gdk_draw_line (window, gc2,
		x + gap_x + gap_width - 2, y, x + gap_x + gap_width - 2, y + 1);*/
            }
	    break;
        case  GTK_POS_BOTTOM:
          gdk_draw_line (window, outer_gc,
                         x + 1, y, x + width - 2, y);
          gdk_draw_line (window, outer_gc,
                         x, y + 1, x, y + height - 1);
          gdk_draw_line (window, gc1,
                         x + 1, y + 1, x + width - 2, y + 1);
          gdk_draw_line (window, gc1,
                         x + 1, y + 1, x + 1, y + height - 1);
          
          gdk_draw_line (window, gc2,
                         x + width - 2, y + 1, x + width - 2, y + height - 1);
          gdk_draw_line (window, outer_gc,
                         x + width - 1, y + 1, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x, y + height - 1, x + gap_x - 1, y + height - 1);
              gdk_draw_line (window, gc2,
                             x + 1, y + height - 2, x + gap_x - 1, y + height - 2);
              /*gdk_draw_line (window, gc1,
		x + gap_x + 1, y + height - 2, x + gap_x + 1, y + height - 1);*/
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x + gap_x + gap_width, y + height - 1, x + width - 2, y + height - 1);
              gdk_draw_line (window, gc2,
                             x + gap_x + gap_width, y + height - 2, x + width - 2, y + height - 2);
              /*gdk_draw_line (window, gc2,
		x + gap_x + gap_width - 2, y + height - 2, x + gap_x + gap_width - 2, y + height - 1);*/
	    }
          break;
        case GTK_POS_LEFT:
          gdk_draw_line (window, outer_gc,
                         x, y, x + width - 2, y);
          gdk_draw_line (window, gc1,
                         x, y + 1, x + width - 2, y + 1);
          
          gdk_draw_line (window, gc2,
                         x, y + height - 2, x + width - 2, y + height - 2);
          gdk_draw_line (window, gc2,
                         x + width - 2, y + 1, x + width - 2, y + height - 2);
          gdk_draw_line (window, outer_gc,
                         x, y + height - 1, x + width - 2, y + height - 1);
          gdk_draw_line (window, outer_gc,
                         x + width - 1, y + 1, x + width - 1, y + height - 2);
          if (gap_x > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x, y, x, y + gap_x - 1);
              gdk_draw_line (window, gc1,
                             x + 1, y + 1, x + 1, y + gap_x - 1);
              /*gdk_draw_line (window, gc1,
		x, y + gap_x + 1, x + 1, y + gap_x + 1);*/
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x, y + gap_x + gap_width, x, y + height - 2);
              gdk_draw_line (window, gc1,
                             x + 1, y + gap_x + gap_width, x + 1, y + height - 2);
              /*gdk_draw_line (window, gc2,
		x, y + gap_x + gap_width - 2, x + 1, y + gap_x + gap_width - 2);*/
            }
          break;
        case GTK_POS_RIGHT:
          gdk_draw_line (window, outer_gc,
                         x + 1, y, x + width - 1, y);
          gdk_draw_line (window, outer_gc,
                         x, y + 1, x, y + height - 2);
          gdk_draw_line (window, gc1,
                         x + 1, y + 1, x + width - 1, y + 1);
          gdk_draw_line (window, gc1,
                         x + 1, y + 1, x + 1, y + height - 2);
          
          gdk_draw_line (window, gc2,
                         x + 1, y + height - 2, x + width - 1, y + height - 2);
          gdk_draw_line (window, outer_gc,
                         x + 1, y + height - 1, x + width - 1, y + height - 1);
          if (gap_x > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x + width - 1, y, x + width - 1, y + gap_x - 1);
              gdk_draw_line (window, gc2,
                             x + width - 2, y + 1, x + width - 2, y + gap_x - 1);
              /*gdk_draw_line (window, gc1,
		x + width - 2, y + gap_x + 1, x + width - 1, y + gap_x + 1);*/
            }
          if ((width - (gap_x + gap_width)) > 0)
            {
              gdk_draw_line (window, outer_gc,
                             x + width - 1, y + gap_x + gap_width, x + width - 1, y + height - 2);
              gdk_draw_line (window, gc2,
                             x + width - 2, y + gap_x + gap_width, x + width - 2, y + height - 2);
              /*gdk_draw_line (window, gc2,
		x + width - 2, y + gap_x + gap_width - 2, x + width - 1, y + gap_x + gap_width - 2);*/
            }
          break;
        }
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, NULL);
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
    }
}

static void draw_extension (GtkStyle        *style,
			    GdkWindow       *window,
			    GtkStateType     state_type,
			    GtkShadowType    shadow_type,
			    GdkRectangle    *area,
			    GtkWidget       *widget,
			    const gchar     *detail,
			    gint             x,
			    gint             y,
			    gint             width,
			    gint             height,
			    GtkPositionType  gap_side)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *outer_gc = NULL;
  gint d = 0;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  /*gtk_style_apply_default_background (style, window,
                                      widget && !GTK_WIDGET_NO_WINDOW (widget),
                                      GTK_STATE_NORMAL, area, x, y, width, height);*/
  
  sanitize_size (window, &width, &height);
  
  outer_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];

  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      return;
    case GTK_SHADOW_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      gc2 = style->white_gc;
      break;
    case GTK_SHADOW_ETCHED_IN:
      gc1 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      gc2 = style->white_gc;
      break;
    case GTK_SHADOW_OUT:
      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = style->white_gc;
      gc2 = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[2];
      break;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, area);
      gdk_gc_set_clip_rectangle (gc1, area);
      gdk_gc_set_clip_rectangle (gc2, area);
    }

  //Unselected tab should be drawn 2 pixels lower than selected tab
  if (state_type == GTK_STATE_ACTIVE)
    {
      d = 2;
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
                                              x + style->xthickness, 
                                              y, 
                                              width - (2 * style->xthickness), 
                                              height - (style->ythickness) - d);

          gdk_draw_line (window, outer_gc,
                         x, y, x, y + height - 2 - d);

          gdk_draw_line (window, gc1,
                         x + 1, y, x + 1, y + height - 2 - d);
          
          gdk_draw_line (window, gc2,
                         x + 2, y + height - 2 - d, x + width - 2, y + height - 2 - d);
          gdk_draw_line (window, gc2,
                         x + width - 2, y, x + width - 2, y + height - 2 - d);

          gdk_draw_line (window, outer_gc,
                         x + 1, y + height - 1 - d, x + width - 2, y + height - 1 - d);
          gdk_draw_line (window, outer_gc,
			 x + width - 1, y, x + width - 1, y + height - 2 - d);

	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x, y + height - 1 - d);
	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + height - 1 - d);

          break;
        case GTK_POS_BOTTOM:
          gtk_style_apply_default_background (style, window,
                                              widget && !GTK_WIDGET_NO_WINDOW (widget),
                                              state_type, area,
                                              x + style->xthickness, 
                                              y + d + style->ythickness, 
                                              width - (2 * style->xthickness), 
                                              height - (style->ythickness) - d);


          gdk_draw_line (window, outer_gc,
                         x + 1, y + d, x + width - 2, y + d);
          gdk_draw_line (window, outer_gc,
                         x, y + d + 1, x, y + height - 1);
          
	  gdk_draw_line (window, gc1,
                         x + 1, y + d + 1, x + width - 2, y + d + 1);
          gdk_draw_line (window, gc1,
                         x + 1, y + d + 1, x + 1, y + height - 1);
          
          gdk_draw_line (window, gc2,
                         x + width - 2, y + d + 1, x + width - 2, y + height - 1);
          
	  gdk_draw_line (window, outer_gc,
			 x + width - 1, y + d + 1, x + width - 1, y + height - 1);

	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x, y + d);
	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1, y + d);

          break;
        case GTK_POS_LEFT:

          gtk_style_apply_default_background (style, window,
                                              widget && !GTK_WIDGET_NO_WINDOW (widget),
                                              state_type, area,
                                              x, 
                                              y + style->ythickness, 
                                              width - (style->xthickness) - d, 
                                              height - (2 * style->ythickness));

          gdk_draw_line (window, outer_gc,
                         x, y, x + width - 2 - d, y);

          gdk_draw_line (window, gc1,
                         x, y + 1, x + width - 2 - d, y + 1);
          
          gdk_draw_line (window, gc2,
                         x, y + height - 2, x + width - 2 - d, y + height - 2);
          gdk_draw_line (window, gc2,
                         x + width - 2 - d, y + 2, x + width - 2 - d, y + height - 2);

          gdk_draw_line (window, outer_gc,
                         x, y + height - 1, x + width - 2 - d, y + height - 1);
          gdk_draw_line (window, outer_gc,
                         x + width - 1 - d, y + 1, x + width - 1 - d, y + height - 2);

	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1 - d, y);
	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + width - 1 - d, y + height - 1);

          break; 
        case GTK_POS_RIGHT:
          gtk_style_apply_default_background (style, window,
                                              widget && !GTK_WIDGET_NO_WINDOW (widget),
                                              state_type, area,
                                              x + style->xthickness + d, 
                                              y + style->ythickness, 
                                              width - (style->xthickness) - d, 
                                              height - (2 * style->ythickness));

          gdk_draw_line (window, outer_gc,
                         x + 1 + d, y, x + width - 1, y);
          gdk_draw_line (window, outer_gc,
                         x + d, y + 1, x + d, y + height - 2);

          gdk_draw_line (window, gc1,
                         x + 1 + d, y + 1, x + width - 1, y + 1);
          gdk_draw_line (window, gc1,
                         x + 1 + d, y + 1, x + 1 + d, y + height - 1);
          
          gdk_draw_line (window, gc2,
                         x + 1 + d, y + height - 2, x + width - 1, y + height - 2);

          gdk_draw_line (window, outer_gc,
                         x + 1 + d, y + height - 1, x + width - 1, y + height - 1);

	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + d, y);
	  gdk_draw_point (window, style->bg_gc[GTK_STATE_NORMAL], x + d, y + height - 1);

          break;
        }
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle (outer_gc, NULL);
      gdk_gc_set_clip_rectangle (gc1, NULL);
      gdk_gc_set_clip_rectangle (gc2, NULL);
    }
}

static void draw_focus (GtkStyle        *style,
			GdkWindow       *window,
			GtkStateType     state_type,
			GdkRectangle    *area,
			GtkWidget       *widget,
			const gchar     *detail,
			gint             x,
			gint             y,
			gint             width,
			gint             height)
{
  GdkPoint points[5];
  GdkGC    *gc;
  gboolean free_dash_list = FALSE;
  gint line_width = 1;
  gchar *dash_list = "\1\1";
  gint dash_len;

  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);

  /*printf ("draw_focus: %p %p %s %i %i %i %i\n", widget, window, detail, x, y, width, height);*/

  if (DETAIL ("treeview")) /* focus is represented with color only (see base color definitions) */
    {
      return;
    }

  gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];

  if (widget)
    {
      gtk_widget_style_get (widget,
			    "focus-line-width", &line_width,
			    "focus-line-pattern", (gchar *)&dash_list,
			    NULL);

      free_dash_list = TRUE;
  }

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

static void draw_slider (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 GtkShadowType    shadow_type,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 gint             width,
			 gint             height,
			 GtkOrientation   orientation)
{
  gint x1, y1;
  
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  sanitize_size (window, &width, &height);
  
  gtk_paint_box (style, window, state_type, shadow_type,
                 area, widget, detail, x, y, width, height);

  if (detail &&
      strcmp ("slider", detail) == 0)
    {
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], area);
	  gdk_gc_set_clip_rectangle (style->white_gc, area);
	}
      if (orientation == GTK_ORIENTATION_HORIZONTAL)
	{
	  x1 = x + width / 2 - 8;
	  y1 = y + (height - 6) / 2;
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5, y1,
			 x1, y1 + 5);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5, y1 + 1,
			 x1 + 1, y1 + 5);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5 + 5, y1,
			 x1 + 5, y1 + 5);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5 + 5, y1 + 2,
			 x1 + 5 + 1, y1 + 5);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5 + 5*2, y1,
			 x1 + 5*2, y1 + 5);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5 + 5*2, y1 + 1,
			 x1 + 5*2 + 1, y1 + 5);
	}
      else
	{
	  x1 = x + (width - 6) / 2;
	  y1 = y + height / 2 - 8;
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5, y1,
			 x1, y1 + 5);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5, y1 + 1,
			 x1 + 1, y1 + 5);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5, y1 + 5,
			 x1, y1 + 5 + 5);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5, y1 + 5 + 1,
			 x1 + 1, y1 + 5 + 5);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5, y1 + 5*2,
			 x1, y1 + 5 + 5*2);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5, y1 + 5*2 + 1,
			 x1 + 1, y1 + 5 + 5*2);
	}
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], NULL);
	  gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	}
    }
  if (detail &&
      (strcmp ("hscale", detail) == 0 ||
       strcmp ("vscale", detail) == 0))
    {
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], area);
	  gdk_gc_set_clip_rectangle (style->white_gc, area);
	}
      
      if (orientation == GTK_ORIENTATION_HORIZONTAL)
	{
	  x1 = x + width / 2 - 5;
	  y1 = y + (height - 7) / 2;
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 0, y1 + 4,
			 x1 + 3, y1 + 1);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 1, y1 + 4,
			 x1 + 3, y1 + 2);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 2, y1 + 6,
			 x1 + 8, y1 + 0);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 3, y1 + 6,
			 x1 + 8, y1 + 1);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 7,  y1 + 5,
			 x1 + 10, y1 + 2);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 8,  y1 + 5,
			 x1 + 10, y1 + 3);
	}
      else
	{
	  x1 = x + (width - 7) / 2;
	  y1 = y + height / 2 - 5;
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 4, y1 + 0,
			 x1 + 1, y1 + 3);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 4, y1 + 1,
			 x1 + 2, y1 + 3);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 6, y1 + 2,
			 x1 + 0, y1 + 8);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 6, y1 + 3,
			 x1 + 1, y1 + 8);
	  gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                         x1 + 5, y1 + 7,
			 x1 + 2, y1 + 10);
	  gdk_draw_line (window, style->white_gc,
                         x1 + 5, y1 + 8,
			 x1 + 3, y1 + 10);
	}
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5], NULL);
	  gdk_gc_set_clip_rectangle (style->white_gc, NULL);
	}
    }
}

static void draw_handle (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 GtkShadowType    shadow_type,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 gint             width,
			 gint             height,
			 GtkOrientation   orientation)
{
  gint xx, yy;
  gint xthick, ythick;
  GdkGC *light_gc, *dark_gc;
  GdkRectangle rect;
  GdkRectangle dest;
  gint intersect;
  gint h;
  int i;
  int n_lines;
  int offset;
  
  g_return_if_fail (LIGHTHOUSEBLUE_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  sanitize_size (window, &width, &height);
  
  gtk_style_apply_default_background (style, window,
				      widget && !GTK_WIDGET_NO_WINDOW (widget),
				      state_type, area, x, y, width, height);

  if (DETAIL ("dockitem") ||
      (widget && strcmp (g_type_name (G_TYPE_FROM_INSTANCE (widget)), "PanelAppletFrame") == 0))
    {
      /* Work around orientation bugs */
      if (orientation == GTK_ORIENTATION_VERTICAL)
	orientation = GTK_ORIENTATION_HORIZONTAL;
      else
	orientation = GTK_ORIENTATION_VERTICAL;
      
    }
  
  if (!strcmp (detail, "paned"))
    {
      /* we want to ignore the shadow border in paned widgets */
      xthick = 0;
      ythick = 0;
    }
  else
    {
      xthick = style->xthickness;
      ythick = style->ythickness;
    }

  if ( (DETAIL ("handlebox") && widget && GTK_IS_HANDLE_BOX (widget)) ||
       DETAIL ("dockitem"))
    {
      /* The line in the toolbar */

      light_gc = style->white_gc;
      dark_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3];
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle (light_gc, area);
	  gdk_gc_set_clip_rectangle (dark_gc, area);
	}
      
      gdk_draw_line (window, light_gc,
		     x + width - 1, y + ythick + 3,
		     x + width - 1, y + height - ythick - 3);
      gdk_draw_line (window, dark_gc,
		     x + width - 2, y + ythick + 3,
		     x + width - 2, y + height - ythick - 3);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle (light_gc, NULL);
	  gdk_gc_set_clip_rectangle (dark_gc, NULL);
	}

      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], area);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], area);
	}
      
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0],
		     x, y, x + width, y);
      gdk_draw_line (window, (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3],
		     x, y + height - 1, x + width, y + height - 1);
      
      if (area)
	{
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[0], NULL);
	  gdk_gc_set_clip_rectangle ((LIGHTHOUSEBLUE_STYLE (style))->shade_gc[3], NULL);
	}
    }
  /* Don't draw the box on the panel grippies */
  else if (!(widget && strcmp (g_type_name (G_TYPE_FROM_INSTANCE (widget)), "PanelAppletFrame") == 0)) 
    {
      draw_box (style,
		window,
		state_type,
		shadow_type,
		area,
		widget,
		detail,
		x, y,
		width, height);
    }


  if ( (DETAIL ("handlebox") && widget && GTK_IS_HANDLE_BOX (widget)) ||
       DETAIL ("dockitem"))
    {
      /* Toolbar grippies are slightly darker */
      light_gc = style->white_gc;
      dark_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[6];
    }
  else
    {
      light_gc = style->white_gc;
      dark_gc = (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5];
    }
  
  rect.x = x + xthick;
  rect.y = y + ythick;
  rect.width = width - (xthick * 2);
  rect.height = height - (ythick * 2);

  if (area)
      intersect = gdk_rectangle_intersect (area, &rect, &dest);
  else
    {
      intersect = TRUE;
      dest = rect;
    }

  if (!intersect)
    return;

  gdk_gc_set_clip_rectangle (light_gc, &dest);
  gdk_gc_set_clip_rectangle (dark_gc, &dest);


  n_lines = 5;

  if (orientation == GTK_ORIENTATION_VERTICAL)
    {
      h = width - 2 * xthick;
      h = MAX (3, h - 6);
      
      xx = x + (width - h) / 2;
      offset = (height - 2 * ythick - 4 * n_lines)/2;
      if (offset < 0)
	offset = 0;
      
      for (i = 0, yy = y + ythick + offset; yy <= (y + height - ythick - h) && i < n_lines; yy += h + 2, i++)
	{
	  gdk_draw_line (window, dark_gc,
			 xx, yy + h,
			 xx + h, yy);
	  gdk_draw_line (window, light_gc,
			 xx, yy + h + 1,
			 xx + h, yy + 1);
	}
    }
  else
    {
      h = height - 2 * ythick;
      h = MAX (3, h - 6);
      
      yy = y + (height - h) / 2;
      offset = (width - 2 * xthick - 4 * n_lines)/2;
      if (offset < 0)
	offset = 0;
      
      for (i = 0, xx = x + xthick + offset; xx <= (x + width - xthick - h) && i < n_lines; xx += h + 2, i++)
	{
	  gdk_draw_line (window, dark_gc,
			 xx, yy + h,
			 xx + h, yy);
	  gdk_draw_line (window, light_gc,
			 xx + 1, yy + h,
			 xx + h + 1, yy);
	}
    }
  
  gdk_gc_set_clip_rectangle (light_gc, NULL);
  gdk_gc_set_clip_rectangle (dark_gc, NULL);
}

static void draw_expander (GtkStyle        *style,
			   GdkWindow       *window,
			   GtkStateType     state_type,
			   GdkRectangle    *area,
			   GtkWidget       *widget,
			   const gchar     *detail,
			   gint             x,
			   gint             y,
			   GtkExpanderStyle expander_style)
{}

static void draw_layout (GtkStyle        *style,
			 GdkWindow       *window,
			 GtkStateType     state_type,
			 gboolean         use_text,
			 GdkRectangle    *area,
			 GtkWidget       *widget,
			 const gchar     *detail,
			 gint             x,
			 gint             y,
			 PangoLayout     *layout)
{
  g_message ("LAYOUT");
}

static void draw_resize_grip (GtkStyle       *style,
			      GdkWindow      *window,
			      GtkStateType    state_type,
			      GdkRectangle   *area,
			      GtkWidget      *widget,
			      const gchar    *detail,
			      GdkWindowEdge   edge,
			      gint            x,
			      gint            y,
			      gint            width,
			      gint            height)
{
  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }

  /* make it square, aligning to bottom right */
  if (width < height)
    {
      y += (height - width);
      height = width;
    }
  else if (height < width)
    {
      x += (width - height);
      width = height;
    }

  /* Clear background */
  gtk_style_apply_default_background (style, window, FALSE,
				      state_type, area,
				      x, y, width, height);   

  switch (edge)
    {
    case GDK_WINDOW_EDGE_SOUTH_EAST:
      {
        gint xi, yi;

        xi = x;
        yi = y;

        while (xi < (x + width - 3))
          {
            gdk_draw_line (window,
                           style->white_gc,
                           xi, y + height,
                           x + width, yi);                           

            ++xi;
            ++yi;
            
            gdk_draw_line (window,
                           (LIGHTHOUSEBLUE_STYLE (style))->shade_gc[5],
                           xi, y + height,
                           x + width, yi);                           
            
            xi += 3;
            yi += 3;
          }
      }
      break;
    default:
      g_assert_not_reached ();
      break;
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
}


static void lighthouseblue_style_init_from_rc (GtkStyle *style, GtkRcStyle *rc_style)
{
  LighthouseBlueStyle *lighthouseblue_style = LIGHTHOUSEBLUE_STYLE (style);
  double shades[] = {1.065, 0.963, 0.896, 0.90, 0.768, 0.665, 0.4, 0.205};
  gint i;

  parent_class->init_from_rc (style, rc_style);

  for (i = 0; i < 8; i++)
    {
      shade (&style->bg[GTK_STATE_NORMAL], &lighthouseblue_style->shade[i], (shades[i] - 0.7) * 1.0 + 0.7);
    }
}

static GdkGC *
realize_color (GtkStyle * style,
	       GdkColor * color)
{
  GdkGCValues gc_values;

  gdk_colormap_alloc_color (style->colormap, color,
			    FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (style->depth, style->colormap,
		     &gc_values, GDK_GC_FOREGROUND);
}

static void lighthouseblue_style_realize (GtkStyle *style)
{
  LighthouseBlueStyle *lighthouseblue_style = LIGHTHOUSEBLUE_STYLE (style);
  gint i;

  parent_class->realize (style);

  for (i = 0; i < 8; i++)
    {
      lighthouseblue_style->shade_gc[i] = realize_color (style, &lighthouseblue_style->shade[i]);
    }
}

static void lighthouseblue_style_unrealize (GtkStyle *style)
{
  LighthouseBlueStyle *lighthouseblue_style = LIGHTHOUSEBLUE_STYLE (style);
  gint i;

  for (i = 0; i < 8; i++)
    {
      gtk_gc_release (lighthouseblue_style->shade_gc[i]);
    }

  parent_class->unrealize (style);
}

static void
lighthouseblue_style_init (LighthouseBlueStyle *style)
{
}

static void
lighthouseblue_style_class_init (LighthouseBlueStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  style_class->realize = lighthouseblue_style_realize;
  style_class->unrealize = lighthouseblue_style_unrealize;
  style_class->init_from_rc = lighthouseblue_style_init_from_rc;
 
  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;

  //style_class->draw_polygon = draw_polygon;
  //style_class->draw_diamond = draw_diamond;

  style_class->draw_box = draw_box;
  style_class->draw_flat_box = draw_flat_box; 
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  //style_class->draw_tab = draw_tab; 
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;

  style_class->draw_arrow = draw_arrow;


  //style_class->draw_string = draw_string;

  style_class->draw_focus = draw_focus;

  //style_class->draw_expander = draw_expander; L
  //style_class->draw_layout = draw_layout;

  style_class->draw_resize_grip = draw_resize_grip;
}

GType lighthouseblue_type_style = 0;

void
lighthouseblue_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (LighthouseBlueStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) lighthouseblue_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (LighthouseBlueStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) lighthouseblue_style_init,
  };
  
  lighthouseblue_type_style = g_type_module_register_type (module,
							   GTK_TYPE_STYLE,
							   "LighthouseBlueStyle",
							   &object_info, 0);
}
