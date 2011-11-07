/*  gxfce
 *  Copyright (C) 1999 Olivier Fourdan (fourdan@xfce.org)
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
#  include <config.h>
#endif

#include <math.h>
#include <gtk/gtk.h>
#include <string.h>

#include "xfce_style.h"
#include "xfce_rc_style.h"

/* 
  Port to GTK+-2.0 based on Thinice port by Tim Gerla <timg@rrv.net>
      Tomas Ögren <stric@ing.umu.se> and  Richard Hult <rhult@codefactory.se>
  Portions based on Raleigh theme by Owen Taylor
  Portions based on Notif theme
  Portions based on Notif2 theme
  Portions based on original GTK theme
 */

static void xfce_style_init       (XfceStyle      *style);
static void xfce_style_class_init (XfceStyleClass *klass);
static GtkStyleClass *parent_class = NULL;

extern GtkStyleClass xfce_default_class;

/* Taken from raleigh theme engine */
typedef enum
{
  CHECK_LIGHT,
  CHECK_DARK,
  CHECK_BASE,
  CHECK_TEXT,
  CHECK_CROSS,
  RADIO_LIGHT,
  RADIO_DARK,
  RADIO_BASE,
  RADIO_TEXT
}
Part;

#define PART_SIZE 13
#define OPTION_INDICATOR_WIDTH 7

static char check_light_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08,
  0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0xfc, 0x0f,
  0x00, 0x00, };
static char check_dark_bits[] = {
  0x00, 0x00, 0xfe, 0x0f, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
  0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
  0x00, 0x00, };
static char check_base_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07,
  0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0x00, 0x00,
  0x00, 0x00, };
static char check_text_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x0f, 0x80, 0x03, 0xc0, 0x01,
  0xe0, 0x00, 0x73, 0x00, 0x3f, 0x00, 0x3e, 0x00, 0x1c, 0x00, 0x18, 0x00,
  0x08, 0x00
};
static char check_cross_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0xb8, 0x03, 0xf0, 0x01,
  0xe0, 0x00, 0xf0, 0x01, 0xb8, 0x03, 0x18, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, };
static char radio_light_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x08,
  0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x04, 0x08, 0x02, 0xf0, 0x01,
  0x00, 0x00, };
static char radio_dark_bits[] = {
  0x00, 0x00, 0xf0, 0x01, 0x08, 0x02, 0x04, 0x00, 0x02, 0x00, 0x02, 0x00,
  0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, };
static char radio_base_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xf8, 0x03, 0xfc, 0x07, 0xfc, 0x07,
  0xfc, 0x07, 0xfc, 0x07, 0xfc, 0x07, 0xf8, 0x03, 0xf0, 0x01, 0x00, 0x00,
  0x00, 0x00, };
static char radio_text_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0xf0, 0x01,
  0xf0, 0x01, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00,
};

static struct
{
  char *bits;
  GdkBitmap *bmap;
}
parts[] =
{
  {check_light_bits, NULL},
  {check_dark_bits, NULL},
  {check_base_bits, NULL},
  {check_text_bits, NULL},
  {check_cross_bits, NULL},
  {radio_light_bits, NULL},
  {radio_dark_bits, NULL},
  {radio_base_bits, NULL},
  {radio_text_bits, NULL}
};

/* internal functions */
static void draw_hline (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x1, gint x2, gint y);
static void draw_vline (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint y1, gint y2, gint x);
static void draw_shadow (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);

static void draw_polygon (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GdkPoint * point, gint npoints, gint fill);
static void draw_arrow (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GtkArrowType arrow_type, gint fill, gint x, gint y, gint width, gint height);
static void draw_diamond (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_box (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_check (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_option (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_tab (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height);
static void draw_shadow_gap (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_box_gap (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width);
static void draw_extension (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side);
static void draw_slider (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);
static void draw_handle (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation);

static void
xfce_draw_handlers (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  gint xx, yy;
  gint xthick, ythick;
  GdkGC *light_gc, *dark_gc;
  GdkRectangle dest;

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

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

  if (orientation == GTK_ORIENTATION_HORIZONTAL)
  {
    if (width > 15 + xthick)
    {
      gint delta = x + xthick + (width / 2) - 7;
      yy = y + ythick;
      for (xx = 0; xx < 10; xx += 2)
      {
	gdk_draw_line (window, dark_gc, xx + delta, yy, xx + delta, yy + height - ythick);
	gdk_draw_line (window, light_gc, xx + delta + 1, yy, xx + delta + 1, yy + height - ythick);
      }
    }
  }
  else
  {
    if (height > 15 + ythick)
    {
      gint delta = y + ythick + height / 2 - 7;
      xx = x + xthick;
      for (yy = 0; yy < 10; yy += 2)
      {
	gdk_draw_line (window, dark_gc, xx, yy + delta, xx + width - xthick, yy + delta);
	gdk_draw_line (window, light_gc, xx, yy + delta + 1, xx + width - xthick, yy + delta + 1);
      }
    }
  }
  
  gdk_gc_set_clip_rectangle (light_gc, NULL);
  gdk_gc_set_clip_rectangle (dark_gc, NULL);
}

static void
draw_hline (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x1, gint x2, gint y)
{
  gint thickness_light;
  gint thickness_dark;
  gint i;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  thickness_light = style->ythickness / 2;
  thickness_dark = style->ythickness - thickness_light;

  if (area)
  {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
  }

  for (i = 0; i < thickness_dark; i++)
  {
    gdk_draw_line (window, style->dark_gc[state_type], x2 - i - 1, y + i, x2, y + i);
    gdk_draw_line (window, style->dark_gc[state_type], x1, y + i, x2 - i - 1, y + i);
  }

  y += thickness_dark;
  for (i = 0; i < thickness_light; i++)
  {
    gdk_draw_line (window, style->light_gc[state_type], x1, y + i, x1 + thickness_light - i - 1, y + i);
    gdk_draw_line (window, style->light_gc[state_type], x1 + thickness_light - i - 1, y + i, x2, y + i);
  }

  if (area)
  {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
  }
}

static void
draw_vline (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint y1, gint y2, gint x)
{
  gint thickness_light;
  gint thickness_dark;
  gint i;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  thickness_light = style->xthickness / 2;
  thickness_dark = style->xthickness - thickness_light;

  if (area)
  {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
  }
  for (i = 0; i < thickness_dark; i++)
  {
    gdk_draw_line (window, style->dark_gc[state_type], x + i, y2 - i - 1, x + i, y2);
    gdk_draw_line (window, style->dark_gc[state_type], x + i, y1, x + i, y2 - i - 1);
  }

  x += thickness_dark;
  for (i = 0; i < thickness_light; i++)
  {
    gdk_draw_line (window, style->light_gc[state_type], x + i, y1, x + i, y1 + thickness_light - i);
    gdk_draw_line (window, style->light_gc[state_type], x + i, y1 + thickness_light - i, x + i, y2);
  }
  if (area)
  {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
  }
}

static void
draw_shadow (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  GdkGC *gc1, *gc2, *gc3;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);
	
  gc1 = style->dark_gc[state_type];
  gc2 = style->light_gc[state_type];
  gc3 = style->black_gc;
	
  if(XFCE_RC_STYLE (style->rc_style)->smooth_edge)
  {
      gc1 = style->mid_gc[state_type];
      gc2 = style->light_gc[state_type];
      gc3 = style->dark_gc[state_type];
  }

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

  if (area)
  {
    gdk_gc_set_clip_rectangle (gc1, area);
    gdk_gc_set_clip_rectangle (gc2, area);
    gdk_gc_set_clip_rectangle (gc3, area);
    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
  }

  switch (shadow_type)
  {
  case GTK_SHADOW_NONE:
    break;
  case GTK_SHADOW_ETCHED_IN:
    gdk_draw_line (window, style->light_gc[state_type], x, y + height - 1, x + width - 1, y + height - 1);
    gdk_draw_line (window, style->light_gc[state_type], x + width - 1, y, x + width - 1, y + height - 1);

    gdk_draw_line (window, style->dark_gc[state_type], x, y, x + width - 2, y);
    gdk_draw_line (window, style->dark_gc[state_type], x, y, x, y + height - 2);

    gdk_draw_line (window, style->light_gc[state_type], x + 1, y + 1, x + width - 2, y + 1);
    gdk_draw_line (window, style->light_gc[state_type], x + 1, y + 1, x + 1, y + height - 2);

    gdk_draw_line (window, style->dark_gc[state_type], x + 1, y + height - 2, x + width - 2, y + height - 2);
    gdk_draw_line (window, style->dark_gc[state_type], x + width - 2, y + 1, x + width - 2, y + height - 2);
    break;
  case GTK_SHADOW_ETCHED_OUT:
    gdk_draw_line (window, style->dark_gc[state_type], x, y + height - 1, x + width - 1, y + height - 1);
    gdk_draw_line (window, style->dark_gc[state_type], x + width - 1, y, x + width - 1, y + height - 1);

    gdk_draw_line (window, style->light_gc[state_type], x, y, x + width - 2, y);
    gdk_draw_line (window, style->light_gc[state_type], x, y, x, y + height - 2);

    gdk_draw_line (window, style->dark_gc[state_type], x + 1, y + 1, x + width - 2, y + 1);
    gdk_draw_line (window, style->dark_gc[state_type], x + 1, y + 1, x + 1, y + height - 2);

    gdk_draw_line (window, style->light_gc[state_type], x + 1, y + height - 2, x + width - 2, y + height - 2);
    gdk_draw_line (window, style->light_gc[state_type], x + width - 2, y + 1, x + width - 2, y + height - 2);
    break;
  case GTK_SHADOW_IN:
    gdk_draw_line (window, gc1, x, y, x + width - 1, y);
    gdk_draw_line (window, gc1, x, y, x, y + height - 1);

    gdk_draw_line (window, gc2, x + 1, y + height - 1, x + width - 1, y + height - 1);
    gdk_draw_line (window, gc2, x + width - 1, y + 1, x + width - 1, y + height - 1);

    gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);
    gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + height - 2);

    gdk_draw_line (window, gc1, x + 2, y + height - 2, x + width - 2, y + height - 2);
    gdk_draw_line (window, gc1, x + width - 2, y + 2, x + width - 2, y + height - 2);
    break;
  case GTK_SHADOW_OUT:
    gdk_draw_line (window, gc1, x, y, x + width - 1, y);
    gdk_draw_line (window, gc1, x, y, x, y + height - 1);

    gdk_draw_line (window, gc3, x + 1, y + height - 1, x + width - 1, y + height - 1);
    gdk_draw_line (window, gc3, x + width - 1, y + 1, x + width - 1, y + height - 1);

    gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
    gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);

    gdk_draw_line (window, gc1, x + 2, y + height - 2, x + width - 2, y + height - 2);
    gdk_draw_line (window, gc1, x + width - 2, y + 2, x + width - 2, y + height - 2);
    break;
  }
  if (area)
  {
    gdk_gc_set_clip_rectangle (gc1, NULL);
    gdk_gc_set_clip_rectangle (gc2, NULL);
    gdk_gc_set_clip_rectangle (gc3, NULL);
    gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
  }
}

static void
draw_polygon (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GdkPoint * points, gint npoints, gint fill)
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

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);
  g_return_if_fail (points != NULL);

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
    gdk_draw_polygon (window, style->bg_gc[state_type], TRUE, points, npoints);

  npoints--;

  for (i = 0; i < npoints; i++)
  {
    if ((points[i].x == points[i + 1].x) && (points[i].y == points[i + 1].y))
    {
      angle = 0;
    }
    else
    {
      angle = atan2 (points[i + 1].y - points[i].y, points[i + 1].x - points[i].x);
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

      gdk_draw_line (window, gc1, points[i].x - xadjust, points[i].y - yadjust, points[i + 1].x - xadjust, points[i + 1].y - yadjust);
      gdk_draw_line (window, gc3, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
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

      gdk_draw_line (window, gc4, points[i].x + xadjust, points[i].y + yadjust, points[i + 1].x + xadjust, points[i + 1].y + yadjust);
      gdk_draw_line (window, gc2, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
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

static void
draw_diamond (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  gint half_width;
  gint half_height;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

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
    gdk_draw_line (window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
    gdk_draw_line (window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
    gdk_draw_line (window, style->light_gc[state_type], x, y + half_height, x + half_width, y + height);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y + height, x + width, y + half_height);

    gdk_draw_line (window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
    gdk_draw_line (window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
    gdk_draw_line (window, style->dark_gc[state_type], x, y + half_height, x + half_width, y);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y, x + width, y + half_height);
    break;
  case GTK_SHADOW_OUT:
    gdk_draw_line (window, style->dark_gc[state_type], x + 2, y + half_height, x + half_width, y + height - 2);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y + height - 2, x + width - 2, y + half_height);
    gdk_draw_line (window, style->dark_gc[state_type], x + 1, y + half_height, x + half_width, y + height - 1);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y + height - 1, x + width - 1, y + half_height);
    gdk_draw_line (window, style->dark_gc[state_type], x, y + half_height, x + half_width, y + height);
    gdk_draw_line (window, style->dark_gc[state_type], x + half_width, y + height, x + width, y + half_height);

    gdk_draw_line (window, style->light_gc[state_type], x + 2, y + half_height, x + half_width, y + 2);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y + 2, x + width - 2, y + half_height);
    gdk_draw_line (window, style->light_gc[state_type], x + 1, y + half_height, x + half_width, y + 1);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y + 1, x + width - 1, y + half_height);
    gdk_draw_line (window, style->light_gc[state_type], x, y + half_height, x + half_width, y);
    gdk_draw_line (window, style->light_gc[state_type], x + half_width, y, x + width, y + half_height);
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

static void
draw_box (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

  if (!style->bg_pixmap[state_type])
  {
    if (area)
    {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }
    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE, x, y, width, height);
    if (area)
    {
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
  }
  else
    gtk_style_apply_default_background (style, window, 1, state_type, area, x, y, width, height);

  if ((detail) && (!strcmp("spinbutton_up", detail)))
  {
    gtk_paint_shadow (style, window, state_type, GTK_SHADOW_ETCHED_IN, area, widget, detail, x, y, width, height);
  }
  else if ((detail) && (!strcmp("spinbutton_down", detail)))
  {
    gtk_paint_shadow (style, window, state_type, GTK_SHADOW_ETCHED_IN, area, widget, detail, x, y, width, height);
  }
  else 
    gtk_paint_shadow (style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

static void
draw_part (GdkDrawable * drawable, GdkGC * gc, GdkRectangle * area, gint x, gint y, Part part)
{
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  if (!parts[part].bmap)
    parts[part].bmap = gdk_bitmap_create_from_data (drawable, parts[part].bits, PART_SIZE, PART_SIZE);

  gdk_gc_set_ts_origin (gc, x, y);
  gdk_gc_set_stipple (gc, parts[part].bmap);
  gdk_gc_set_fill (gc, GDK_STIPPLED);

  gdk_draw_rectangle (drawable, gc, TRUE, x, y, PART_SIZE, PART_SIZE);

  gdk_gc_set_fill (gc, GDK_SOLID);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_check (GtkStyle * style, GdkWindow * window, GtkStateType state, GtkShadowType shadow, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;

  if (strcmp (detail, "check") == 0)	/* Menu item */
  {
    if (shadow == GTK_SHADOW_IN)
    {
      draw_part (window, style->text_gc[state], area, x, y, CHECK_TEXT);
    }
  }
  else
  {
    draw_part (window, style->base_gc[state],  area, x, y, CHECK_BASE);
    draw_part (window, style->light_gc[state], area, x, y, CHECK_LIGHT);
    draw_part (window, style->dark_gc[state],  area, x, y, CHECK_DARK);

    if (shadow == GTK_SHADOW_IN)
    {
      draw_part (window, style->text_gc[state], area, x, y, CHECK_CROSS);
    }
  }
}

static void
draw_option (GtkStyle * style, GdkWindow * window, GtkStateType state, GtkShadowType shadow, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  x -= (1 + PART_SIZE - width) / 2;
  y -= (1 + PART_SIZE - height) / 2;

  if (strcmp (detail, "option") == 0)	/* Menu item */
  {
    if (shadow == GTK_SHADOW_IN)
    {
      draw_part (window, style->text_gc[state], area, x, y, RADIO_TEXT);
    }
  }
  else
  {
    draw_part (window, style->base_gc[state],  area, x, y, RADIO_BASE);
    draw_part (window, style->light_gc[state], area, x, y, RADIO_LIGHT);
    draw_part (window, style->dark_gc[state],  area, x, y, RADIO_DARK);

    if (shadow == GTK_SHADOW_IN)
    {
      draw_part (window, style->text_gc[state], area, x, y, RADIO_TEXT);
    }
  }
}

static void
draw_varrow (GdkWindow * window, GdkGC * gc, GtkShadowType shadow_type, GdkRectangle * area, GtkArrowType arrow_type, gint x, gint y, gint width, gint height)
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
    gdk_draw_line (window, gc, x, y_start + i * y_increment, x + width - 1, y_start + i * y_increment);
  }
  for (; i < height; i++)
  {
    gdk_draw_line (window, gc, x + (i - extra), y_start + i * y_increment, x + width - (i - extra) - 1, y_start + i * y_increment);
  }


  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_harrow (GdkWindow * window, GdkGC * gc, GtkShadowType shadow_type, GdkRectangle * area, GtkArrowType arrow_type, gint x, gint y, gint width, gint height)
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
    gdk_draw_line (window, gc, x_start + i * x_increment, y, x_start + i * x_increment, y + height - 1);
  }
  for (; i < width; i++)
  {
    gdk_draw_line (window, gc, x_start + i * x_increment, y + (i - extra), x_start + i * x_increment, y + height - (i - extra) - 1);
  }


  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_arrow (GtkStyle * style, GdkWindow * window, GtkStateType state, GtkShadowType shadow, GdkRectangle * area, GtkWidget * widget, const gchar * detail, GtkArrowType arrow_type, gboolean fill, gint x, gint y, gint width, gint height)
{
  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

  if (detail && strcmp (detail, "spinbutton") == 0)
  {
    x += (width - 7) / 2;

    if (arrow_type == GTK_ARROW_UP)
      y += (height - 7) / 2;
    else
      y += (height - 5) / 2;

    draw_varrow (window, style->text_gc[state], shadow, area, arrow_type, x, y, 7, 5);
  }
  else if (detail && strcmp (detail, "vscrollbar") == 0)
  {
    x += (width - 7) / 2;
    y += (height - 5) / 2;

    draw_varrow (window, style->text_gc[state], shadow, area, arrow_type, x, y, 7, 5);

  }
  else if (detail && strcmp (detail, "hscrollbar") == 0)
  {
    y += (height - 7) / 2;
    x += (width - 5) / 2;

    draw_harrow (window, style->text_gc[state], shadow, area, arrow_type, x, y, 5, 7);
  }
  else
  {
    if (arrow_type == GTK_ARROW_UP || arrow_type == GTK_ARROW_DOWN)
    {
      x += (width - 7) / 2;
      y += (height - 5) / 2;

      draw_varrow (window, style->text_gc[state], shadow, area, arrow_type, x, y, 7, 5);
    }
    else
    {
      x += (width - 5) / 2;
      y += (height - 7) / 2;

      draw_harrow (window, style->text_gc[state], shadow, area, arrow_type, x, y, 5, 7);
    }
  }
}

static void
draw_tab (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height)
{
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  x += (width - OPTION_INDICATOR_WIDTH) / 2;
  y += (height - PART_SIZE) / 2 - 1;

  draw_varrow (window, style->text_gc[state_type], shadow_type, area, GTK_ARROW_UP, x, y, OPTION_INDICATOR_WIDTH, 5);
  draw_varrow (window, style->text_gc[state_type], shadow_type, area, GTK_ARROW_DOWN, x, y + OPTION_INDICATOR_WIDTH + 1, OPTION_INDICATOR_WIDTH, 5);
}

static void
draw_shadow_gap (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
  GdkRectangle rect;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  gtk_paint_shadow (style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

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

  gtk_style_apply_default_background (style, window, 1, state_type, area, rect.x, rect.y, rect.width, rect.height);
}

static void
draw_box_gap (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side, gint gap_x, gint gap_width)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *gc3 = NULL;
  GdkGC *gc4 = NULL;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), state_type, area, x, y, width, height);

  if (width == -1 && height == -1)
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

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

  if (area)
  {
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
      gdk_draw_line (window, gc1, x, y, x, y + height - 1);
      gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 2);

      gdk_draw_line (window, gc3, x + 1, y + height - 2, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc3, x + width - 2, y, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
      if (gap_x > 0)
      {
	gdk_draw_line (window, gc1, x, y, x + gap_x - 1, y);
	gdk_draw_line (window, gc2, x + 1, y + 1, x + gap_x - 1, y + 1);
	gdk_draw_line (window, gc2, x + gap_x, y, x + gap_x, y);
      }
      if ((width - (gap_x + gap_width)) > 0)
      {
	gdk_draw_line (window, gc1, x + gap_x + gap_width, y, x + width - 2, y);
	gdk_draw_line (window, gc2, x + gap_x + gap_width, y + 1, x + width - 2, y + 1);
	gdk_draw_line (window, gc2, x + gap_x + gap_width - 1, y, x + gap_x + gap_width - 1, y);
      }
      break;
    case GTK_POS_BOTTOM:
      gdk_draw_line (window, gc1, x, y, x + width - 1, y);
      gdk_draw_line (window, gc1, x, y, x, y + height - 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 1);

      gdk_draw_line (window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
      if (gap_x > 0)
      {
	gdk_draw_line (window, gc4, x, y + height - 1, x + gap_x - 1, y + height - 1);
	gdk_draw_line (window, gc3, x + 1, y + height - 2, x + gap_x - 1, y + height - 2);
	gdk_draw_line (window, gc3, x + gap_x, y + height - 1, x + gap_x, y + height - 1);
      }
      if ((width - (gap_x + gap_width)) > 0)
      {
	gdk_draw_line (window, gc4, x + gap_x + gap_width, y + height - 1, x + width - 2, y + height - 1);
	gdk_draw_line (window, gc3, x + gap_x + gap_width, y + height - 2, x + width - 2, y + height - 2);
	gdk_draw_line (window, gc3, x + gap_x + gap_width - 1, y + height - 1, x + gap_x + gap_width - 1, y + height - 1);
      }
      break;
    case GTK_POS_LEFT:
      gdk_draw_line (window, gc1, x, y, x + width - 1, y);
      gdk_draw_line (window, gc2, x, y + 1, x + width - 2, y + 1);

      gdk_draw_line (window, gc3, x, y + height - 2, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc3, x + width - 2, y + 1, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y, x + width - 1, y + height - 1);
      if (gap_x > 0)
      {
	gdk_draw_line (window, gc1, x, y, x, y + gap_x - 1);
	gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + gap_x - 1);
	gdk_draw_line (window, gc2, x, y + gap_x, x, y + gap_x);
      }
      if ((width - (gap_x + gap_width)) > 0)
      {
	gdk_draw_line (window, gc1, x, y + gap_x + gap_width, x, y + height - 2);
	gdk_draw_line (window, gc2, x + 1, y + gap_x + gap_width, x + 1, y + height - 2);
	gdk_draw_line (window, gc2, x, y + gap_x + gap_width - 1, x, y + gap_x + gap_width - 1);
      }
      break;
    case GTK_POS_RIGHT:
      gdk_draw_line (window, gc1, x, y, x + width - 1, y);
      gdk_draw_line (window, gc1, x, y, x, y + height - 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 1, y + 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);

      gdk_draw_line (window, gc3, x + 1, y + height - 2, x + width - 1, y + height - 2);
      gdk_draw_line (window, gc4, x, y + height - 1, x + width - 1, y + height - 1);
      if (gap_x > 0)
      {
	gdk_draw_line (window, gc4, x + width - 1, y, x + width - 1, y + gap_x - 1);
	gdk_draw_line (window, gc3, x + width - 2, y + 1, x + width - 2, y + gap_x - 1);
	gdk_draw_line (window, gc3, x + width - 1, y + gap_x, x + width - 1, y + gap_x);
      }
      if ((width - (gap_x + gap_width)) > 0)
      {
	gdk_draw_line (window, gc4, x + width - 1, y + gap_x + gap_width, x + width - 1, y + height - 2);
	gdk_draw_line (window, gc3, x + width - 2, y + gap_x + gap_width, x + width - 2, y + height - 2);
	gdk_draw_line (window, gc3, x + width - 1, y + gap_x + gap_width - 1, x + width - 1, y + gap_x + gap_width - 1);
      }
      break;
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

static void
draw_extension (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkPositionType gap_side)
{
  GdkGC *gc1 = NULL;
  GdkGC *gc2 = NULL;
  GdkGC *gc3 = NULL;
  GdkGC *gc4 = NULL;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), GTK_STATE_NORMAL, area, x, y, width, height);

  if (width == -1 && height == -1)
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

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

  if (area)
  {
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
      gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), state_type, area, x + 1, y, width - 2, height - 1);
      gdk_draw_line (window, gc1, x, y, x, y + height - 2);
      gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 2);

      gdk_draw_line (window, gc3, x + 2, y + height - 2, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc3, x + width - 2, y, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc4, x + 1, y + height - 1, x + width - 2, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y, x + width - 1, y + height - 2);
      break;
    case GTK_POS_BOTTOM:
      gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), state_type, area, x + style->xthickness, y + style->ythickness, width - (2 * style->xthickness), height - (style->ythickness));
      gdk_draw_line (window, gc1, x + 1, y, x + width - 2, y);
      gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 1);

      gdk_draw_line (window, gc3, x + width - 2, y + 2, x + width - 2, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y + 1, x + width - 1, y + height - 1);
      break;
    case GTK_POS_LEFT:
      gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), state_type, area, x, y + style->ythickness, width - (style->xthickness), height - (2 * style->ythickness));
      gdk_draw_line (window, gc1, x, y, x + width - 2, y);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);

      gdk_draw_line (window, gc3, x, y + height - 2, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc3, x + width - 2, y + 2, x + width - 2, y + height - 2);
      gdk_draw_line (window, gc4, x, y + height - 1, x + width - 2, y + height - 1);
      gdk_draw_line (window, gc4, x + width - 1, y + 1, x + width - 1, y + height - 2);
      break;
    case GTK_POS_RIGHT:
      gtk_style_apply_default_background (style, window, widget && !GTK_WIDGET_NO_WINDOW (widget), state_type, area, x + style->xthickness, y + style->ythickness, width - (style->xthickness), height - (2 * style->ythickness));
      gdk_draw_line (window, gc1, x + 1, y, x + width - 1, y);
      gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 1, y + 1);
      gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);

      gdk_draw_line (window, gc3, x + 2, y + height - 2, x + width - 1, y + height - 2);
      gdk_draw_line (window, gc4, x + 1, y + height - 1, x + width - 1, y + height - 1);
      break;
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

static void
draw_slider (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

  orientation = GTK_ORIENTATION_HORIZONTAL;
  if (height > width)
    orientation = GTK_ORIENTATION_VERTICAL;

  gtk_draw_box (style, window, state_type, shadow_type, x, y, width, height);
  xfce_draw_handlers (style, window, state_type, area, widget, x, y, width, height, orientation);
}

static void
draw_handle (GtkStyle * style, GdkWindow * window, GtkStateType state_type, GtkShadowType shadow_type, GdkRectangle * area, GtkWidget * widget, const gchar * detail, gint x, gint y, gint width, gint height, GtkOrientation orientation)
{
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if ((width == -1) && (height == -1))
    gdk_drawable_get_size (window, &width, &height);
  else if (width == -1)
    gdk_drawable_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_drawable_get_size (window, NULL, &height);

  orientation = GTK_ORIENTATION_HORIZONTAL;
  if (height > width)
    orientation = GTK_ORIENTATION_VERTICAL;

  gtk_draw_box (style, window, state_type, GTK_SHADOW_OUT, x, y, width, height);
  xfce_draw_handlers (style, window, state_type, area, widget, x, y, width, height, orientation);
}

GType xfce_type_style = 0;

void
xfce_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (XfceStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) xfce_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (XfceStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) xfce_style_init,
  };
  
  xfce_type_style = g_type_module_register_type (module,
						    GTK_TYPE_STYLE,
						    "XfceStyle",
						    &object_info, 0);
}

static void
xfce_style_init (XfceStyle *style)
{
}

static void
xfce_style_class_init (XfceStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;
  style_class->draw_polygon = draw_polygon;
  style_class->draw_arrow = draw_arrow;
  style_class->draw_diamond = draw_diamond;
  style_class->draw_box = draw_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;
}


