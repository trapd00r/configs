/* ThinIce theme for gtk, based on raster's Motif theme and the Metal theme.
Authors: Tim Gerla <timg@rrv.net>
Tomas Ögren <stric@ing.umu.se>
 */ 
/* #define DEBUG 1 */

#include <math.h>
#include <string.h>
#include <gtk/gtknotebook.h>

#include "thinice_style.h"
#include "thinice_rc_style.h"

#define DETAIL(xx) ((detail) && (!strcmp(xx, detail)))
#ifndef max
#define max(x,y) ((x)>=(y)?(x):(y))
#endif
#ifndef min
#define min(x,y) ((x)<=(y)?(x):(y))
#endif

static void thinice_style_init       (ThiniceStyle      *style);
static void thinice_style_class_init (ThiniceStyleClass *klass);

static void
thinice_slash_two(GdkWindow *window,
                  GdkGC *gc1,
                  GdkGC *gc2,
                  gint x,
                  gint y,
                  gint width,
                  gint height);

static void
thinice_slash_one(GdkWindow *window,
                  GdkGC *gc1,
                  GdkGC *gc2,
                  gint x,
                  gint y,
                  gint width,
                  gint height);

static void
thinice_dot(GdkWindow *window,
            GdkGC *gc1,
            GdkGC *gc2,
            gint x,
            gint y);


static void
thinice_tab(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            gint width,
            gint height);

#if 0
static void
draw_harrow (GdkWindow     *window,
             GdkGC         *gc,
             GtkShadowType  shadow_type,
             GdkRectangle  *area,
             GtkArrowType   arrow_type,
             gint           x,
             gint           y,
             gint           width,
             gint           height);
static void
draw_varrow (GdkWindow     *window,
             GdkGC         *gc,
             GtkShadowType  shadow_type,
             GdkRectangle  *area,
             GtkArrowType   arrow_type,
             gint           x,
             gint           y,
             gint           width,
             gint           height);
#endif

static GtkStyleClass *parent_class = NULL;

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
static void
sanitize_size (GdkWindow *window,
	       gint      *width,
	       gint      *height)
{
  if ((*width == -1) && (*height == -1))
    gdk_window_get_size (window, width, height);
  else if (*width == -1)
    gdk_window_get_size (window, width, NULL);
  else if (*height == -1)
    gdk_window_get_size (window, NULL, height);
}

static void
draw_hline(GtkStyle * style,
           GdkWindow * window,
           GtkStateType state_type,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           gint x1,
           gint x2,
           gint y)
{
  gint                thickness_light;
  gint                thickness_dark;
  gint                i;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  thickness_light = style->ythickness / 2;
  thickness_dark = style->ythickness - thickness_light;

  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
    }
  for (i = 0; i < thickness_dark; i++)
    {
      gdk_draw_line(window, style->light_gc[state_type], x2 - i - 1, y + i, x2, y + i);
      gdk_draw_line(window, style->dark_gc[state_type], x1, y + i, x2 - i - 1, y + i);
    }

  y += thickness_dark;
  for (i = 0; i < thickness_light; i++)
    {
      gdk_draw_line(window, style->dark_gc[state_type], x1, y + i, x1 + thickness_light - i - 1, y + i);
      gdk_draw_line(window, style->light_gc[state_type], x1 + thickness_light - i - 1, y + i, x2, y + i);
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
    }
}

static void
draw_vline(GtkStyle * style,
           GdkWindow * window,
           GtkStateType state_type,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           gint y1,
           gint y2,
           gint x)
{
  gint                thickness_light;
  gint                thickness_dark;
  gint                i;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  thickness_light = style->xthickness / 2;
  thickness_dark = style->xthickness - thickness_light;

  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
    }
  for (i = 0; i < thickness_dark; i++)
    {
      gdk_draw_line(window, style->light_gc[state_type], x + i, y2 - i - 1, x + i, y2);
      gdk_draw_line(window, style->dark_gc[state_type], x + i, y1, x + i, y2 - i - 1);
    }

  x += thickness_dark;
  for (i = 0; i < thickness_light; i++)
    {
      gdk_draw_line(window, style->dark_gc[state_type], x + i, y1, x + i, y1 + thickness_light - i);
      gdk_draw_line(window, style->light_gc[state_type], x + i, y1 + thickness_light - i, x + i, y2);
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
    }
}

static void
draw_shadow(GtkStyle     *style,
	    GdkWindow    *window,
	    GtkStateType  state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle *area,
	    GtkWidget    *widget,
	    const gchar  *detail,
	    gint          x,
	    gint          y,
	    gint          width,
	    gint          height)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size(window, &width, &height);

  if (DETAIL("entry") || DETAIL("text")) {
      gint entry_width;
      gint entry_height;
      gdk_window_get_size (window, &entry_width, &entry_height);
      if (entry_width != width || entry_height != height)
        return;
  }

  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      return;
    case GTK_SHADOW_IN:
      if (((x == 1) || (y == 1)) && (DETAIL("entry") || DETAIL("text")))
        {
          gc1 = gc2 = style->base_gc[state_type];
          break;
        }
    case GTK_SHADOW_ETCHED_IN:
      gc1 = style->light_gc[state_type];
      gc2 = style->dark_gc[state_type];
      break;
    case GTK_SHADOW_OUT:
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      break;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      if ((shadow_type == GTK_SHADOW_IN) ||
          (shadow_type == GTK_SHADOW_OUT))
        {
          gdk_gc_set_clip_rectangle(style->black_gc, area);
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        }
    }
  switch (shadow_type)
    {
    case GTK_SHADOW_NONE:
      break;

    case GTK_SHADOW_ETCHED_IN:
      gdk_draw_rectangle(window, gc1, FALSE, x+1, y+1, width-2, height-2);
      gdk_draw_rectangle(window, gc2, FALSE, x, y, width-2, height-2);

      break;
    case GTK_SHADOW_IN:
      gdk_draw_line(window, gc2,
                    x, y, x + width-1, y);
      gdk_draw_line(window, gc2,
                    x, y, x, y + height-1);

      gdk_draw_line(window, gc1,
                    x, y + height-1, x + width-1, y + height-1);
      gdk_draw_line(window, gc1,
                    x + width-1, y, x + width-1, y + height-1);
      break;

    case GTK_SHADOW_ETCHED_OUT:
      gdk_draw_rectangle(window, gc1, FALSE, x+1, y+1, width-2, height-2);
      gdk_draw_rectangle(window, gc2, FALSE, x, y, width-2, height-2);

      break;
    case GTK_SHADOW_OUT:
      gdk_draw_line(window, gc2,
                    x, y, x + width-1, y);
      gdk_draw_line(window, gc2,
                    x, y, x, y + height-1);

      gdk_draw_line(window, gc1,
                    x, y + height-1, x + width-1, y + height-1);
      gdk_draw_line(window, gc1,
                    x + width-1, y, x + width-1, y + height-1);

      break;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      if ((shadow_type == GTK_SHADOW_IN) ||
          (shadow_type == GTK_SHADOW_OUT))
        {
          gdk_gc_set_clip_rectangle(style->black_gc, NULL);
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        }
    }
}

static void
draw_polygon(GtkStyle * style,
             GdkWindow * window,
             GtkStateType state_type,
             GtkShadowType shadow_type,
             GdkRectangle * area,
             GtkWidget * widget,
             const gchar *detail,
             GdkPoint * points,
             gint npoints,
             gint fill)
{
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif /* M_PI */
#ifndef M_PI_4
#define M_PI_4  0.78539816339744830962
#endif /* M_PI_4 */

  static const gdouble pi_over_4 = M_PI_4;
  static const gdouble pi_3_over_4 = M_PI_4 * 3;

  GdkGC              *gc1;
  GdkGC              *gc2;
  GdkGC              *gc3;
  GdkGC              *gc4;
  gdouble             angle;
  gint                xadjust;
  gint                yadjust;
  gint                i;

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

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      gdk_gc_set_clip_rectangle(gc3, area);
      gdk_gc_set_clip_rectangle(gc4, area);
    }

  if (fill)
    gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);

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
          angle = atan2(points[i + 1].y - points[i].y,
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

          gdk_draw_line(window, gc1,
                        points[i].x - xadjust, points[i].y - yadjust,
                        points[i + 1].x - xadjust, points[i + 1].y - yadjust);
          gdk_draw_line(window, gc3,
                        points[i].x, points[i].y,
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

          gdk_draw_line(window, gc4,
                        points[i].x + xadjust, points[i].y + yadjust,
                        points[i + 1].x + xadjust, points[i + 1].y + yadjust);
          gdk_draw_line(window, gc2,
                        points[i].x, points[i].y,
                        points[i + 1].x, points[i + 1].y);
        }
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      gdk_gc_set_clip_rectangle(gc3, NULL);
      gdk_gc_set_clip_rectangle(gc4, NULL);
    }
}

#if 0
void
draw_shadearrow(GtkStyle * style,
                GdkWindow * window,
                GtkStateType state_type,
                GtkShadowType shadow_type,
                GdkRectangle * area,
                GtkWidget * widget,
                const gchar *detail,
                GtkArrowType arrow_type,
                gint fill,
                gint x, gint y,
                gint width, gint height)
{
  int           awidth, aheight;
  GdkGC        *gc1, *gc2, *gc3, *gc4;

  aheight = height + height % 2 - 1;
  awidth = width + width % 2 - 1;


  gc1 = style->dark_gc[state_type];
  gc2 = style->light_gc[state_type];
  if (arrow_type == GTK_ARROW_UP || arrow_type == GTK_ARROW_DOWN)
    {
      if (state_type  == GTK_STATE_INSENSITIVE ||
          shadow_type == GTK_SHADOW_ETCHED_IN ||
          shadow_type == GTK_SHADOW_ETCHED_OUT)
        {
          gc1 = style->bg_gc[GTK_STATE_ACTIVE];
        }
      else
        {
          draw_varrow (window, gc2, shadow_type, area, arrow_type,
                       x+1, y, awidth, aheight);
          draw_varrow (window, gc2, shadow_type, area, arrow_type,
                       x, y+1, awidth, aheight);
        }
      draw_varrow (window, gc1, shadow_type, area, arrow_type,
                   x, y, awidth, aheight);
    }
  else
    {

      if (state_type  == GTK_STATE_INSENSITIVE ||
          shadow_type == GTK_SHADOW_ETCHED_IN ||
          shadow_type == GTK_SHADOW_ETCHED_OUT)
        {
          gc1 = style->bg_gc[GTK_STATE_ACTIVE];
        }
      else
        {
          draw_harrow (window, gc2, shadow_type, area, arrow_type,
                       x+1, y, awidth, aheight);
          draw_harrow (window, gc2, shadow_type, area, arrow_type,
                       x, y+1, awidth, aheight);
        }
      draw_harrow (window, gc1, shadow_type, area, arrow_type,
                   x, y, awidth, aheight);
    }

}
#endif

static void
draw_black_arrow (GdkWindow     *window,
	    GdkGC         *gc,
	    GdkRectangle  *area,
	    GtkArrowType   arrow_type,
	    gint           x,
	    gint           y,
	    gint           width,
	    gint           height)
{
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

#if 0
static void
draw_arrow(GtkStyle * style,
           GdkWindow * window,
           GtkStateType state,
           GtkShadowType shadow,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           GtkArrowType arrow_type,
           gint fill, gint x, gint y, gint width, gint height)
{
  gint original_width, original_x;
  
  sanitize_size (window, &width, &height);

  original_width = width;
  original_x = x;

  calculate_arrow_geometry (arrow_type, &x, &y, &width, &height);
  
  if (detail && strcmp (detail, "menuitem") == 0)
    x = original_x + original_width - width;

  if (state == GTK_STATE_INSENSITIVE)
    draw_black_arrow (window, style->white_gc, area, arrow_type,
		x + 1, y + 1, width, height);
  draw_black_arrow (window, style->fg_gc[state], area, arrow_type,
	      x, y, width, height);
}
#endif
static void
draw_arrow(GtkStyle * style,
           GdkWindow * window,
           GtkStateType state_type,
           GtkShadowType shadow_type,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           GtkArrowType arrow_type,
           gint fill, gint x, gint y, gint width, gint height)
{
  GdkGC              *gc1;
  GdkGC              *gc2;
  GdkGC              *gc3;
  GdkGC              *gc4;
  gint                half_width;
  gint                half_height;
  gint                ax, ay, aw, ah;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

#ifdef DEBUG
  printf("arrow! state_type=%d shadow_type=%d, fill=%d, x,y=%d,%d width,height=%d,%d\n",
         state_type, shadow_type, fill, x, y, width, height);
  printf("\\-- detail=%s, arrow_type=%d\n", detail?detail:"<null>", arrow_type);
#endif
  /*
     detail=scrollbar,
     arrow_type=0  -> ^
     arrow_type=1  -> V
     arrow_type=2  -> <
     arrow_type=3  -> >
   */


  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
      gc1 = style->bg_gc[state_type];
      gc2 = style->dark_gc[state_type];
      gc3 = style->light_gc[state_type];
      gc4 = style->black_gc;
      break;
    case GTK_SHADOW_OUT:
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = style->black_gc;
      gc4 = style->bg_gc[state_type];
      break;
    case GTK_SHADOW_ETCHED_IN:
      gc2 = style->light_gc[state_type];
      gc1 = style->dark_gc[state_type];
      gc3 = NULL;
      gc4 = NULL;
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = NULL;
      gc4 = NULL;
      break;
    default:
      return;
    }

  sanitize_size(window, &width, &height);
  ax = x;
  ay = y;
  aw = width;
  ah = height;
  calculate_arrow_geometry (arrow_type, &ax, &ay, &aw, &ah);

  half_width = width / 2;
  half_height = height / 2;

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      if ((gc3) && (gc4))
        {
          gdk_gc_set_clip_rectangle(gc3, area);
          gdk_gc_set_clip_rectangle(gc4, area);
        }
    }

  if (DETAIL("vscrollbar") || DETAIL("hscrollbar"))
    {
#ifdef DEBUG
      printf("Scrollbar of type (%s)!\n", detail);
#endif
#ifdef DEBUG
      printf("type = %p\n", thinice_type_rc_style);
      printf("style->rc_style = %p\n", style->rc_style);
      printf("theme_data = %p\n", THINICE_RC_STYLE (style->rc_style));

      printf("mojj1=%d\n", THINICE_RC_STYLE (style->rc_style)->scrollbar_type);
      printf("mojj2=%d\n", THINICE_RC_STYLE (style->rc_style)->scrollbar_marks);
      printf("mojj3=%d\n", THINICE_RC_STYLE (style->rc_style)->scroll_button_marks);
      printf("mojj4=%d\n", THINICE_RC_STYLE (style->rc_style)->handlebox_marks);

      printf("mojj5=%d\n", THINICE_RC_STYLE (style->rc_style)->mark_type1);
      printf("mojj6=%d\n", THINICE_RC_STYLE (style->rc_style)->mark_type2);
      printf("rcstyle=%d\n", THINICE_RC_STYLE (style->rc_style)->mark_type2);
      printf("rcstyle2=%d\n", ((struct _ThiniceRcStyle*)(style->rc_style))->mark_type2);
#endif
      switch (THINICE_RC_STYLE (style->rc_style)->mark_type2)
        {
        case MARKS_NOTHING:
          break;
        case MARKS_INVSLASH:
          thinice_slash_one(window, gc2, gc1, x, y, width, height);
          break;
        case MARKS_DOT:
          thinice_dot(window, gc2, gc1, x + half_width, y + half_height);
          break;
        case MARKS_INVDOT:
          thinice_dot(window, gc1, gc2, x + half_width, y + half_height);
          break;
        case MARKS_ARROW:
          if (state_type == GTK_STATE_INSENSITIVE)
            draw_black_arrow (window, style->white_gc, area, arrow_type,
                              ax + 1, ay + 1, aw, ah);
          draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
                  ax, ay, aw, ah);
          break;
        case MARKS_SLASH:
        default:
          thinice_slash_one(window, gc1, gc2, x, y, width - 1, height - 1);
          break;
        }
    }
  else if DETAIL("spinbutton")
    {
      if (state_type == GTK_STATE_INSENSITIVE)
        draw_black_arrow (window, style->white_gc, area, arrow_type,
                          ax + 1, ay + 1, aw, ah);
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
                        ax, ay, aw, ah);
    }
  else if (DETAIL("menuitem"))
    {
      ax = x + width - aw;

      if (state_type == GTK_STATE_INSENSITIVE)
        draw_black_arrow (window, style->white_gc, area, arrow_type,
                          ax + 1, ay + 1, aw, ah);
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
                        ax, ay, aw, ah);
    }
  else
    {
      if (state_type == GTK_STATE_INSENSITIVE)
        draw_black_arrow (window, style->white_gc, area, arrow_type,
                          ax + 1, ay + 1, aw, ah);
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
                        ax, ay, aw, ah);
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      if (gc3)
        {
          gdk_gc_set_clip_rectangle(gc3, NULL);
          gdk_gc_set_clip_rectangle(gc4, NULL);
        }
    }
}


#if 0
static void
draw_harrow (GdkWindow     *window,
             GdkGC         *gc,
             GtkShadowType  shadow_type,
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

  height = height + height % 2 - 1;     /* Force odd */

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
draw_varrow (GdkWindow     *window,
             GdkGC         *gc,
             GtkShadowType  shadow_type,
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

  width = width + width % 2 - 1;        /* Force odd */

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
#endif

static void
draw_diamond(GtkStyle * style,
             GdkWindow * window,
             GtkStateType state_type,
             GtkShadowType shadow_type,
             GdkRectangle * area,
             GtkWidget * widget,
             const gchar *detail,
             gint x,
             gint y,
             gint width,
             gint height)
{
  gint                half_width;
  gint                half_height;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size(window, &width, &height);

  half_width = width / 2;
  half_height = height / 2;

  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->black_gc, area);
    }
  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
      gdk_draw_line(window, style->light_gc[state_type],
                    x + 2, y + half_height,
                    x + half_width, y + height - 2);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y + height - 2,
                    x + width - 2, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + 1, y + half_height,
                    x + half_width, y + height - 1);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y + height - 1,
                    x + width - 1, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
                    x, y + half_height,
                    x + half_width, y + height);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y + height,
                    x + width, y + half_height);

      gdk_draw_line(window, style->dark_gc[state_type],
                    x + 2, y + half_height,
                    x + half_width, y + 2);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y + 2,
                    x + width - 2, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + 1, y + half_height,
                    x + half_width, y + 1);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y + 1,
                    x + width - 1, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x, y + half_height,
                    x + half_width, y);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y,
                    x + width, y + half_height);
      break;
    case GTK_SHADOW_OUT:
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + 2, y + half_height,
                    x + half_width, y + height - 2);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y + height - 2,
                    x + width - 2, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + 1, y + half_height,
                    x + half_width, y + height - 1);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y + height - 1,
                    x + width - 1, y + half_height);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x, y + half_height,
                    x + half_width, y + height);
      gdk_draw_line(window, style->dark_gc[state_type],
                    x + half_width, y + height,
                    x + width, y + half_height);

      gdk_draw_line(window, style->light_gc[state_type],
                    x + 2, y + half_height,
                    x + half_width, y + 2);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y + 2,
                    x + width - 2, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + 1, y + half_height,
                    x + half_width, y + 1);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y + 1,
                    x + width - 1, y + half_height);
      gdk_draw_line(window, style->light_gc[state_type],
                    x, y + half_height,
                    x + half_width, y);
      gdk_draw_line(window, style->light_gc[state_type],
                    x + half_width, y,
                    x + width, y + half_height);
      break;
    default:
      break;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->black_gc, NULL);
    }
}

#if 0
static void
draw_string(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            const gchar * string)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if (area)
    {
      if (state_type == GTK_STATE_INSENSITIVE)
        {
          gdk_gc_set_clip_rectangle(style->base_gc[state_type], area);
        }
      gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
    }
  if (state_type == GTK_STATE_INSENSITIVE)
    {
      gdk_draw_string(window, gtk_style_get_font(style), style->base_gc[state_type], x + 1, y + 1, string);
    }
  gdk_draw_string(window, gtk_style_get_font(style), style->fg_gc[state_type], x, y, string);
  if (area)
    {
      if (state_type == GTK_STATE_INSENSITIVE)
        {
          gdk_gc_set_clip_rectangle(style->base_gc[state_type], NULL);
        }
      gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
    }
}
#endif

static void
draw_box(GtkStyle * style,
         GdkWindow * window,
         GtkStateType state_type,
         GtkShadowType shadow_type,
         GdkRectangle * area,
         GtkWidget * widget,
         const gchar *detail,
         gint x,
         gint y,
         gint width,
         gint height)
{
  GdkGC *light_gc, *dark_gc;
  GtkOrientation      orientation;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size(window, &width, &height);

  light_gc = style->light_gc[state_type];
  dark_gc = style->dark_gc[state_type];

  orientation = GTK_ORIENTATION_HORIZONTAL;
  if (height > width)
    orientation = GTK_ORIENTATION_VERTICAL;

#ifdef DEBUG
  printf("%p %s %i %i state_type = %d (%d)\n", detail, detail, width, height, state_type, orientation);
#endif

  if (DETAIL("optionmenutab"))
    {
#ifdef DEBUG
  printf("%p %s %ix%i @ +%i+%i state_type = %d (%d)\n", detail, detail, width, height, x, y, state_type, orientation);
#endif
      if (area)
        {
          GdkPoint            points[4];
          guint size, ydiff, xdiff;

          size = min(width, height);
          gdk_gc_set_clip_rectangle(light_gc, area);
          gdk_gc_set_clip_rectangle(dark_gc, area);

#if 0
          /* DEBUG */
          points[0].x = x ;
          points[0].y = y ;
          points[1].x = x + width;
          points[1].y = y ;
          points[2].x = x + width;
          points[2].y = y + height;
          points[3].x = x ;
          points[3].y = y + height;

          gdk_draw_polygon(window, light_gc, FALSE, points, 4);
          /* DEBUG */
#endif

          if (size % 2)
            size++;

          ydiff = max(0, (height - size) / 2);
          xdiff = max(0, (width - size) / 2);
          points[0].x = x + size + xdiff;
          points[0].y = y + ydiff;
          points[1].x = x + xdiff;
          points[1].y = y + ydiff;
          points[2].x = x + size / 2 + xdiff;
          points[2].y = y + size + ydiff;
          gdk_draw_polygon(window, light_gc, FALSE, points, 3);
          points[0].x--;
          points[1].x--;
          points[2].x--;
          gdk_draw_polygon(window, dark_gc, FALSE, points, 3);

          gdk_gc_set_clip_rectangle(light_gc, NULL);
          gdk_gc_set_clip_rectangle(dark_gc, NULL);
        }
    }
  else if (DETAIL("trough"))
    {
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        }
#ifdef DEBUG
      printf("trough\n");
#endif
      gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                         x, y, width, height);
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        }
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                       detail, x, y, width, height);
    }
  else if (DETAIL("slider"))
    {
    }
  else if (DETAIL("buttondefault"))
    {
      /* I don't want no background on default buttons..
         Let's add that cute triangle (see below) instead... */
    }
  else if (DETAIL("button"))
    {
      GdkPoint points1[3]; /* dark */
      GdkPoint points2[3]; /* light */
      points1[0].x = x+2;  points1[0].y = y+2;
      points1[1].x = x+10; points1[1].y = y+2;
      points1[2].x = x+2;  points1[2].y = y+10;
      points2[0].x = x+3;  points2[0].y = y+3;
      points2[1].x = x+10; points2[1].y = y+3;
      points2[2].x = x+3;  points2[2].y = y+10;

      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        }
      if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP (window))
        {
          gdk_draw_rectangle(window, style->bg_gc[state_type],
                             TRUE, x + 1, y + 1, width - 2, height - 2);
        }
      else
        {
          gtk_style_apply_default_background(style, window,
                                             widget && !GTK_WIDGET_NO_WINDOW(widget),
                                             state_type, area,
                                             x, y, width, height);
        }
      /* Paint a triangle here instead of in "buttondefault"
         which is drawn _behind_ the current button */
      if (GTK_WIDGET_HAS_DEFAULT (widget))
        {
          gdk_draw_polygon(window, dark_gc,
                           FALSE, points1, 3);
          gdk_draw_polygon(window, light_gc,
                           FALSE, points2, 3);
          gdk_draw_polygon(window, style->bg_gc[GTK_STATE_SELECTED],
                           TRUE, points2, 3);
        }
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        }
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                       detail, x, y, width, height);
    }
  else if (DETAIL("bar"))
    {
      if ((height > 1) && (width > 1))
        {
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_SELECTED], area);
            }
          gdk_draw_rectangle(window, style->bg_gc[GTK_STATE_SELECTED],
                             TRUE, x + 1, y + 1, width - 2, height - 2);
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_SELECTED], NULL);
            }
        }
    }
  else if (DETAIL("handlebox_bin"))
    {
      if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP(window))
        {
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
            }
          gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                             x, y, width, height);
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
            }
        }
      else
        {
          gtk_style_apply_default_background(style, window,
                                             widget && !GTK_WIDGET_NO_WINDOW(widget),
                                             state_type, area,
                                             x, y, width, height);
        }
      /*
         gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
         detail, x, y, width, height);
       */
    }
  else if (DETAIL("menubar"))
    {
      if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP(window))
        {
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
            }
          gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                             x, y, width, height);
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
            }
        }
      else
        {
          gtk_style_apply_default_background(style, window,
                                             widget && !GTK_WIDGET_NO_WINDOW(widget),
                                             state_type, area,
                                             x, y, width, height);
        }
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                       detail, x, y, width, height);
      /*
         }
         else if (DETAIL("notebook"))
         {
         thinice_notebook(style, window, state_type, shadow_type, area, widget,
         detail, x, y, width, height);
       */
    }
  else if (DETAIL("tab"))
    {
      thinice_tab(style, window, state_type, shadow_type, area, widget,
                  detail, x, y, width, height);
    }
  else
    {
#ifdef DEBUG
      printf("Unknown: [%d,%d] @ [%d,%d] - detail=(%s) shadow_type=%d state_type=%d\n",
             height,width, x, y, detail, shadow_type, state_type);
#endif
      if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP(window))
        {
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
            }
          gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                             x, y, width, height);
          if (area)
            {
              gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
            }
        }
      else
        {
          gtk_style_apply_default_background(style, window,
                                             widget && !GTK_WIDGET_NO_WINDOW(widget),
                                             state_type, area,
                                             x, y, width, height);
        }
      gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                       detail, x, y, width, height);
    }
}



#if 0
static void
draw_flat_box(GtkStyle * style,
              GdkWindow * window,
              GtkStateType state_type,
              GtkShadowType shadow_type,
              GdkRectangle * area,
              GtkWidget * widget,
              const gchar *detail,
              gint x,
              gint y,
              gint width,
              gint height)
{
  GdkGC              *gc1;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size(window, &width, &height);

  gc1 = style->bg_gc[state_type];

  if (DETAIL("text") && (state_type == GTK_STATE_SELECTED))
    gc1 = style->bg_gc[state_type];
  else if (DETAIL("viewportbin"))
    gc1 = style->bg_gc[state_type];
  else if (DETAIL("entry_bg"))
    gc1 = style->base_gc[state_type];

  if ((!style->bg_pixmap[state_type]) || (gc1 != style->bg_gc[state_type]) ||
      GDK_IS_PIXMAP(window))
    {
      if (area)
        gdk_gc_set_clip_rectangle(gc1, area);

      gdk_draw_rectangle(window, gc1, TRUE,
                         x, y, width, height);
      if (DETAIL("tooltip"))
        gdk_draw_rectangle(window, style->black_gc, FALSE,
                           x, y, width - 1, height - 1);
      if (area)
        gdk_gc_set_clip_rectangle(gc1, NULL);
    }
  else
    gtk_style_apply_default_background(style, window,
                                       widget && !GTK_WIDGET_NO_WINDOW(widget),
                                       state_type, area, x, y, width, height);
}
#endif /* 0 */

static void
draw_check(GtkStyle * style,
           GdkWindow * window,
           GtkStateType state_type,
           GtkShadowType shadow_type,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           gint x,
           gint y,
           gint width,
           gint height)
{

  GdkGC              *gc1 = NULL;

  if (shadow_type == GTK_SHADOW_IN)
    {
    gc1 = style->bg_gc[GTK_STATE_ACTIVE];
  }

  if (area && gc1) 
    {
      gdk_gc_set_clip_rectangle(gc1, area);
    }

  if (state_type == GTK_STATE_INSENSITIVE)
    {
      gdk_draw_rectangle(window, style->dark_gc[state_type], FALSE,
                         x, y, width, height);
    }
  else
    {
      gtk_paint_box(style, window, state_type, shadow_type, area, widget,
                    detail, x, y, width, height);
      if (gc1)
        {
          gdk_draw_rectangle(window, gc1, TRUE, x+1, y+1, width-2, height-2);
        }
    }

  if (area && gc1)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
    }
}


/* Thanks to Evan Lawrence */
static void
draw_option(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            gint width,
            gint height)
{
  GdkGC              *gc1;
  GdkGC              *gc2;
  GdkGC              *gc3;

  if (shadow_type == GTK_SHADOW_IN ||
      shadow_type == GTK_SHADOW_ETCHED_IN)
    {
      gc1 = style->dark_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = style->bg_gc[GTK_STATE_ACTIVE];
    }
  else
    {
      gc1 = style->light_gc[state_type]; 
      gc2 = style->dark_gc[state_type];
      gc3 = style->bg_gc[state_type];
    }

  if (area)                           
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      gdk_gc_set_clip_rectangle(gc3, area);
    }

  switch (shadow_type)
    {
    case GTK_SHADOW_ETCHED_IN:
      gdk_draw_arc(window, gc2, FALSE, x+1, y+1, width, height, 0, 360 * 64);
      gdk_draw_arc(window, gc1, FALSE, x, y, width, height, 0, 360 * 64);
      break;
    case GTK_SHADOW_ETCHED_OUT:
      gdk_draw_arc(window, gc1, FALSE, x-1, y-1, width, height, 0, 360 * 64);
      gdk_draw_arc(window, gc2, FALSE, x, y, width, height, 0, 360 * 64);
      break;
    default:
      gdk_draw_arc(window, gc3, TRUE, x, y, width, height, 0, 360 * 64);
      gdk_draw_arc(window, gc1, FALSE, x, y, width, height, 45 * 64, 225 * 64);
      gdk_draw_arc(window, gc2, FALSE, x, y, width, height, 225 * 64, 180 * 64);
      break;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      gdk_gc_set_clip_rectangle(gc3, NULL);
    }
}


static void
draw_tab(GtkStyle * style,
         GdkWindow * window,
         GtkStateType state_type,
         GtkShadowType shadow_type,
         GdkRectangle * area,
         GtkWidget * widget,
         const gchar *detail,
         gint x,
         gint y,
         gint width,
         gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

#ifdef DEBUG
  printf("draw_tab(%d,%d,%d,%d) (detail = '%s')\n", x, y, width, height, detail?detail:"<null>");
#endif
  gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail,
                x, y, width, height);
}

static void
draw_shadow_gap(GtkStyle * style,
                GdkWindow * window,
                GtkStateType state_type,
                GtkShadowType shadow_type,
                GdkRectangle * area,
                GtkWidget * widget,
                const gchar *detail,
                gint x,
                gint y,
                gint width,
                gint height,
                GtkPositionType gap_side,
                gint gap_x,
                gint gap_width)
{
  GdkRectangle        rect;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail,
                   x, y, width, height);

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

  gtk_style_apply_default_background(style, window,
                                     widget && !GTK_WIDGET_NO_WINDOW(widget),
                                     state_type, area,
                                     rect.x, rect.y, rect.width, rect.height);
}

static void
draw_box_gap(GtkStyle * style,
             GdkWindow * window,
             GtkStateType state_type,
             GtkShadowType shadow_type,
             GdkRectangle * area,
             GtkWidget * widget,
             const gchar *detail,
             gint x,
             gint y,
             gint width,
             gint height,
             GtkPositionType gap_side,
             gint gap_x,
             gint gap_width)
{
  GdkRectangle        rect;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail,
                x, y, width, height);

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

  gtk_style_apply_default_background(style, window,
                                     widget && !GTK_WIDGET_NO_WINDOW(widget),
                                     state_type, area, rect.x, rect.y, rect.width, rect.height);
}

static void
draw_extension(GtkStyle * style,
               GdkWindow * window,
               GtkStateType state_type,
               GtkShadowType shadow_type,
               GdkRectangle * area,
               GtkWidget * widget,
               const gchar *detail,
               gint x,
               gint y,
               gint width,
               gint height,
               GtkPositionType gap_side)
{
  GdkRectangle        rect;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail,
                x, y, width, height);

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

  gtk_style_apply_default_background(style, window,
                                     widget && !GTK_WIDGET_NO_WINDOW(widget),
                                     state_type, area, rect.x, rect.y, rect.width, rect.height);
}

#if 0
static void
draw_focus(GtkStyle * style,
           GdkWindow * window,
           GdkRectangle * area,
           GtkWidget * widget,
           const gchar *detail,
           gint x,
           gint y,
           gint width,
           gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if ((width == -1) && (height == -1))
    {
      gdk_window_get_size(window, &width, &height);
      width--;
      height--;
    }
  else if (width == -1)
    {
      gdk_window_get_size(window, &width, NULL);
      width--;
    }
  else if (height == -1)
    {
      gdk_window_get_size(window, NULL, &height);
      height--;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->black_gc, area);
    }
  gdk_draw_rectangle(window,
                     style->black_gc, FALSE,
                     x, y, width, height);
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->black_gc, NULL);
    }
}
#endif /* 0 */

static void
draw_slider(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            gint width,
            gint height,
            GtkOrientation orientation)
{
  GdkPoint pointsh[7];
  GdkRegion *clipreg;
  GdkRectangle rec;
  int i, rect = FALSE, midlines = MARKS_SLASH;
  int modx, mody;


  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

#ifdef DEBUG
  printf("draw_slider(%s, %d, %d, %d)\n", detail, x, y, orientation);
#endif

#ifdef DEBUG
      printf("Slider... x,y=%d,%d width = %d, height = %d (%d)\n",x,y,width,height, state_type);
#endif
      midlines = THINICE_RC_STYLE (style->rc_style)->mark_type1;
#ifdef DEBUG
      printf("Midlines = %d\n", midlines);
#endif

      if (THINICE_RC_STYLE (style->rc_style)->scrollbar_type == SCROLL_RECT)
        {
          rect = TRUE;
        }

      /* too small, use rect & no midlines */
      if ((width <= SMALLEST_HANDLE) && (height <= SMALLEST_HANDLE))
        {
          midlines = MARKS_NOTHING;
          rect = TRUE;
        }

      if (rect)
        {
          pointsh[0].x = x;             pointsh[0].y = y;
          pointsh[1].x = x + width - 1; pointsh[1].y = y;
          pointsh[2].x = x + width - 1; pointsh[2].y = y + height - 1;
          pointsh[3].x = x;             pointsh[3].y = y + height - 1;
          pointsh[4].x = x;             pointsh[4].y = y;
          clipreg = gdk_region_polygon(pointsh, 5, GDK_WINDING_RULE);
          gdk_region_shrink(clipreg, -1, -1);
        } 
      else
        {
          int chopoff;

          if (orientation == GTK_ORIENTATION_HORIZONTAL) {
            chopoff = max(0, min(6, width-SMALLEST_HANDLE));
          } else {
            chopoff = max(0, min(6, height-SMALLEST_HANDLE));
          }

          pointsh[0].x = x;                  pointsh[0].y = y+height-1;
          pointsh[1].x = x;                  pointsh[1].y = y+chopoff;
          pointsh[2].x = x+chopoff;          pointsh[2].y = y;
          pointsh[3].x = x+width-1;          pointsh[3].y = y;
          pointsh[4].x = x+width-1;          pointsh[4].y = y+height-1-chopoff;
          pointsh[5].x = x+width-1-chopoff;  pointsh[5].y = y+height-1;
          pointsh[6].x = x;                  pointsh[6].y = y+height-1;
          clipreg = gdk_region_polygon(pointsh, 7, GDK_WINDING_RULE);
          gdk_region_shrink(clipreg, -1, -1);
        }

      gdk_gc_set_clip_region(style->bg_gc[state_type], clipreg);
      gdk_gc_set_clip_region(style->light_gc[state_type], clipreg);
      gdk_gc_set_clip_region(style->dark_gc[state_type], clipreg);

      if (!rect)
        {
          rec.x = x;
          rec.y = y;
          rec.width = width;
          rec.height = height;
          gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_ACTIVE], &rec);
        }

      if (rect)
        {
          /* Just a plain rectangle with shadow ... */
          if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP (window))
            {
              gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                                 x, y, width, height);
            }
          else
            {
              gtk_style_apply_default_background(style, window,
                                                 widget && !GTK_WIDGET_NO_WINDOW(widget),
                                                 state_type, area,
                                                 x, y, width, height);
            }
          gtk_paint_shadow(style, window, state_type, shadow_type, area,
                           widget, detail, x, y, width, height);
        }
      else
        {
          /* Fill the polygon */
          gdk_draw_polygon(window, style->bg_gc[state_type],
                           TRUE, pointsh, 6);
          /* Draw the light border */
          for (i=0;i<3;i++)
            {
              gdk_draw_line(window, style->light_gc[state_type],
                            pointsh[i].x,pointsh[i].y,
                            pointsh[i+1].x,pointsh[i+1].y);
            }
          /* Draw the dark border */
          for (i=3;i<6;i++)
            {
              gdk_draw_line(window, style->dark_gc[state_type],
                            pointsh[i].x,pointsh[i].y,
                            pointsh[i+1].x,pointsh[i+1].y);
            }

        }
      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        { modx = 4; mody = 0; }
      else
        { modx = 0; mody = 4; }
      switch (midlines)
        {
        case MARKS_NOTHING:
          break;
        case MARKS_INVSLASH: /* Inverse //:es */
          thinice_slash_two(window,
                            style->dark_gc[state_type],
                            style->light_gc[state_type],
                            x, y, width, height);
          break;
        case MARKS_DOT:
          thinice_dot(window,
                      style->light_gc[state_type],
                      style->dark_gc[state_type],
                      x + width / 2 - modx,
                      y + height / 2 - mody);
          thinice_dot(window,
                      style->light_gc[state_type],
                      style->dark_gc[state_type],
                      x + width / 2,
                      y + height / 2);
          thinice_dot(window,
                      style->light_gc[state_type],
                      style->dark_gc[state_type],
                      x + width / 2 + modx,
                      y + height / 2 + mody);
          break;
        case MARKS_INVDOT: /* Inverted */
          thinice_dot(window,
                      style->dark_gc[state_type],
                      style->light_gc[state_type],
                      x + width / 2 - modx,
                      y + height / 2 - mody);
          thinice_dot(window,
                      style->dark_gc[state_type],
                      style->light_gc[state_type],
                      x + width / 2,
                      y + height / 2);
          thinice_dot(window,
                      style->dark_gc[state_type],
                      style->light_gc[state_type],
                      x + width / 2 + modx,
                      y + height / 2 + mody);
          break;
	case MARKS_SLASH:
        default:
          thinice_slash_two(window,
                            style->light_gc[state_type],
                            style->dark_gc[state_type],
                            x, y, width, height);
          break;
        }
      /*
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
          gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
          gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
        }
      else
        {
       */
      gdk_gc_set_clip_region(style->bg_gc[state_type], NULL);
      gdk_gc_set_clip_region(style->light_gc[state_type], NULL);
      gdk_gc_set_clip_region(style->dark_gc[state_type], NULL);
      /*
        }
       */
      if (!rect)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[GTK_STATE_ACTIVE], NULL);
        }
}

static void
draw_handle(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            gint width,
            gint height,
            GtkOrientation orientation)
{
  GdkGC              *light_gc, *dark_gc;
  GdkRectangle        dest;
//  ThemeStyleData     *data = NULL;//style->engine_data;
  gint                modx, mody;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

#if DEBUG
  printf("draw_handle(state=%d, shadow=%d, detail=%s, [%d,%d]@[%d,%d]\n",
         state_type, shadow_type, detail?detail:"nul",width,height,x,y);
#endif
  sanitize_size(window, &width, &height);

  if (DETAIL("paned")) 
    {
      int i, w, h;
      int start_i, end_i;

      dest.x = x;
      dest.y = y;
      dest.width = width;
      dest.height = height;

      light_gc = style->light_gc[state_type];
      dark_gc = style->dark_gc[state_type];
      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        w = width;
      else
        w = height;
      switch (THINICE_RC_STYLE (style->rc_style)->paned_dots) {
      default:
      case PANED_DOTSFULL:
        start_i = 5;
        end_i = w - 5;
        break;
      case PANED_DOTSSOME:
        start_i = w/2 - 16;
        end_i = w/2 + 16;
        break;
      case PANED_DOTSNONE:
        start_i = w;
        end_i = 0;
        break;
      }
      gdk_gc_set_clip_rectangle(light_gc, &dest);
      gdk_gc_set_clip_rectangle(dark_gc, &dest);

      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        {
          for (i=x + start_i; i <= x + end_i; i+=8)
            {
              thinice_dot(window, light_gc, dark_gc, i, y + height / 2);
            }
        }
      else
        {
          for (i=y + start_i; i <= y + end_i; i+=8)
            {
              thinice_dot(window, light_gc, dark_gc, x + width / 2, i);
            }
        }
      gdk_gc_set_clip_rectangle(light_gc, NULL);
      gdk_gc_set_clip_rectangle(dark_gc, NULL);
      return;
    }
  gtk_paint_box(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
  gdk_draw_line(window, style->light_gc[state_type],
                x + width, y, x + width, y + height - 2);

  /* Draw something in the box if so wanted */
  if (THINICE_RC_STYLE (style->rc_style)->mark_type1 != MARKS_NOTHING)
    {
      light_gc = style->light_gc[state_type];
      dark_gc = style->dark_gc[state_type];

      orientation = GTK_ORIENTATION_HORIZONTAL;
      if (height > width)
        orientation = GTK_ORIENTATION_VERTICAL;

      dest.x = x + style->xthickness;
      dest.y = y + style->ythickness;
      dest.width = width - (style->xthickness * 2);
      dest.height = height - (style->ythickness * 2);

      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        { modx = 4; mody = 0; }
      else
        { modx = 0; mody = 4; }

      gdk_gc_set_clip_rectangle(light_gc, &dest);
      gdk_gc_set_clip_rectangle(dark_gc, &dest);

      switch (THINICE_RC_STYLE (style->rc_style)->mark_type1)
        {
        case MARKS_INVSLASH: /* Inverse //:es */
          thinice_slash_two(window, dark_gc, light_gc,
                            x, y, width, height);
          break;
        case MARKS_DOT: /* Dots */
          thinice_dot(window, light_gc, dark_gc,
                      x + width / 2 - modx,
                      y + height / 2 - mody);
          thinice_dot(window, light_gc, dark_gc,
                      x + width / 2,
                      y + height / 2);
          thinice_dot(window, light_gc, dark_gc,
                      x + width / 2 + modx,
                      y + height / 2 + mody);
          break;
        case MARKS_INVDOT: /* Inverted dots */
          thinice_dot(window, dark_gc, light_gc,
                      x + width / 2 - modx,
                      y + height / 2 - mody);
          thinice_dot(window, dark_gc, light_gc,
                      x + width / 2,
                      y + height / 2);
          thinice_dot(window, dark_gc, light_gc,
                      x + width / 2 + modx,
                      y + height / 2 + mody);
          break;
	case MARKS_SLASH:
        default:
          thinice_slash_two(window, light_gc, dark_gc,
                            x, y, width, height);
          break;
        }

      gdk_gc_set_clip_rectangle(light_gc, NULL);
      gdk_gc_set_clip_rectangle(dark_gc, NULL);
    }

}

static void
thinice_slash_two(GdkWindow *window,
                  GdkGC *gc1,
                  GdkGC *gc2,
                  gint x,
                  gint y,
                  gint width,
                  gint height)
{
  gint centerx, centery, thick;
  gint ax1=0,ax2=0,ay1=0,ay2=0;

  centerx = (width - 1)/2 + x;
  centery = (height - 1)/2 + y;
  if (width > height)
    {
      ax1 = -2; ax2 = 1;
    }
  else
    {
      ay1 = -2; ay2 = 1;
    }

  thick = ((width < height?width-1:height-1) >> 1) - 2;
  gdk_draw_line(window, gc2,
                centerx - thick + ax1, centery + thick + ay1,
                centerx + thick + ax1, centery - thick + ay1);
  gdk_draw_line(window, gc1,
                centerx - thick + ax1 + ax2, centery + thick + ay1 + ay2,
                centerx + thick + ax1 + ax2, centery - thick + ay1 + ay2);
  if (width > height)
    {
      ax1 = 2; /* ax2 = 1; */
    }
  else
    {
      ay1 = 2; /* ay2 = 1; */
    }
  gdk_draw_line(window, gc2,
                centerx - thick + ax1, centery + thick + ay1,
                centerx + thick + ax1, centery - thick + ay1);
  gdk_draw_line(window, gc1,
                centerx - thick + ax1 + ax2, centery + thick + ay1 + ay2,
                centerx + thick + ax1 + ax2, centery - thick + ay1 + ay2);
}


static void
thinice_slash_one(GdkWindow *window,
                  GdkGC *gc1,
                  GdkGC *gc2,
                  gint x,
                  gint y,
                  gint width,
                  gint height)
{
  gint centerx, centery, thick;

  centerx = width/2 + x;
  centery = height/2 + y;

  thick = ((width < height?width:height) >> 1);
  gdk_draw_line(window, gc2,
                centerx - thick, centery + thick,
                centerx + thick, centery - thick);
  gdk_draw_line(window, gc1,
                centerx - thick, centery + thick - 1,
                centerx + thick - 1, centery - thick);
}

static void
thinice_dot(GdkWindow *window,
            GdkGC *gc1,
            GdkGC *gc2,
            gint x,
            gint y)
{
  GdkPoint points[3];

  points[0].x = x-1; points[0].y = y;
  points[1].x = x-1; points[1].y = y-1;
  points[2].x = x;   points[2].y = y-1;

  gdk_draw_points(window, gc2, points, 3);

  points[0].x = x+1; points[0].y = y;
  points[1].x = x+1; points[1].y = y+1;
  points[2].x = x;   points[2].y = y+1;

  gdk_draw_points(window, gc1, points, 3);
}

static void
thinice_tab(GtkStyle * style,
            GdkWindow * window,
            GtkStateType state_type,
            GtkShadowType shadow_type,
            GdkRectangle * area,
            GtkWidget * widget,
            const gchar *detail,
            gint x,
            gint y,
            gint width,
            gint height)
{
  GtkNotebook *notebook;
  GdkGC *lightgc, *darkgc;
  int orientation;


  notebook = GTK_NOTEBOOK(widget);
  orientation = notebook->tab_pos;

  lightgc = style->light_gc[state_type];
  darkgc = style->dark_gc[state_type];

  if ((!style->bg_pixmap[state_type]) || GDK_IS_PIXMAP(window))
    {
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
        }
      gdk_draw_rectangle(window, style->bg_gc[state_type], TRUE,
                         x, y, width, height);
      if (area)
        {
          gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
        }
    }
  else
    {
      gtk_style_apply_default_background(style, window,
                                         widget && !GTK_WIDGET_NO_WINDOW(widget),
                                         state_type, area, x, y, width, height);
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
    }
  switch(orientation)
    {
    case GTK_POS_TOP:
      gdk_draw_line(window, lightgc,
                    x, y + height - 1, x, y);
      gdk_draw_line(window, lightgc,
                    x, y, x + width - 1, y);
      gdk_draw_line(window, darkgc,
                    x + width - 1, y, x + width - 1, y + height - 1);
      break;
    case GTK_POS_BOTTOM:
      gdk_draw_line(window, lightgc,
                    x, y, x, y + height - 1);
      gdk_draw_line(window, darkgc,
                    x, y + height - 1, x + width - 1, y + height - 1);
      gdk_draw_line(window, darkgc,
                    x + width - 1, y + height - 1, x + width - 1, y);
      break;
    case GTK_POS_LEFT:
      gdk_draw_line(window, lightgc,
                    x, y + height - 1, x, y);
      gdk_draw_line(window, lightgc,
                    x, y, x + width - 1, y);
      gdk_draw_line(window, darkgc,
                    x, y + height - 1, x + width - 1, y + height - 1);
      break;
    case GTK_POS_RIGHT:
      gdk_draw_line(window, lightgc,
                    x, y, x + width - 1, y);
      gdk_draw_line(window, darkgc,
                    x + width - 1, y, x + width - 1, y + height - 1);
      gdk_draw_line(window, darkgc,
                    x, y + height - 1, x + width - 1, y + height - 1);
      break;
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
    }
  /*gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
    detail, x, y, width, height);
   */
}

GType thinice_type_style = 0;

void
thinice_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (ThiniceStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) thinice_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (ThiniceStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) thinice_style_init,
  };
  
  thinice_type_style = g_type_module_register_type (module,
						    GTK_TYPE_STYLE,
						    "ThiniceStyle",
						    &object_info, 0);
}

static void
thinice_style_init (ThiniceStyle *style)
{
}

static void
thinice_style_class_init (ThiniceStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

#if 0
#endif
  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;
  style_class->draw_polygon = draw_polygon;
  style_class->draw_arrow = draw_arrow;
  style_class->draw_diamond = draw_diamond;
  /*style_class->draw_string = draw_string;*/
  style_class->draw_box = draw_box;
  /* style_class->draw_flat_box = draw_flat_box; */
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  /*style_class->draw_focus = draw_focus;*/
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;
}


/*
FIXME: file/font selector background OK
FIXME: radioknappar varierar storlek rätt bra.. OK
FIXME: scrollbars OK
FIXME: inconsistent-radioknappar OK
FIXME: paned-pluttarna OK
FIXME: spinbuttons, vid max OK

FIXME: Blå triangeln vid RTL, WONTFIX?
*/

