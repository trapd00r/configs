/* dwerg based on Cleanice for GTK 2.0
   CleanIce Author: Bastien Nocera <hadess@hadess.net>
   ThinIce Authors:
    Tim Gerla <timg@means.net>
   	Tomas Ögren <stric@ing.umu.se>
   Clean Author: dengen40@yahoo.com
*/

#include "dwerg_theme.h"
#include "dwerg_style.h"
#include <math.h>
#include <string.h>

#undef DEBUG

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif				/* M_PI */
#ifndef M_PI_4
#define M_PI_4  0.78539816339744830962
#endif				/* M_PI_4 */

#define DETAIL(xx) ((detail) && (!strcmp(xx, detail)))

static void dwerg_style_init (DwergStyle * style);
static void dwerg_style_class_init (DwergStyleClass * klass);


/* internal functions */
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

static void draw_polygon (GtkStyle * style,
    GdkWindow * window,
    GtkStateType state_type,
    GtkShadowType shadow_type,
    GdkRectangle * area,
    GtkWidget * widget,
    const gchar * detail,
    GdkPoint * point, gint npoints, gint fill);
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
static void draw_diamond (GtkStyle * style,
    GdkWindow * window,
    GtkStateType state_type,
    GtkShadowType shadow_type,
    GdkRectangle * area,
    GtkWidget * widget,
    const gchar * detail,
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
static void draw_shadow_gap (GtkStyle * style,
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
static void draw_box_gap (GtkStyle * style,
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
static void draw_focus(GtkStyle *style,
    GdkWindow *window,
    GtkStateType state_type,
    GdkRectangle *area,
    GtkWidget *widget,
    const gchar *detail,
    gint x, gint y, gint width, gint height);
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
static void dwerg_tab (GtkStyle * style,
    GdkWindow * window,
    GtkStateType state_type,
    GtkShadowType shadow_type,
    GdkRectangle * area,
    GtkWidget * widget,
    const gchar * detail,
    gint x, gint y, gint width, gint height);
static void dwerg_dot(GdkWindow *window,
    GdkGC *gc1,
    GdkGC *gc2,
    gint x,
    gint y);
static GtkStyleClass *parent_class = NULL;

typedef enum {
  CHECK_AA,
  CHECK_BASE,
  CHECK_BLACK,
  CHECK_DARK,
  CHECK_LIGHT,
  CHECK_MID,
  CHECK_TEXT,
  RADIO_BASE,
  RADIO_BLACK,
  RADIO_DARK,
  RADIO_LIGHT,
  RADIO_MID,
  RADIO_TEXT
} Part;

#define PART_SIZE 13

static char check_aa_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x58,0x00,0xa0,
 0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char check_base_bits[] = {
 0x00,0x00,0x00,0x00,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,
 0x07,0xfc,0x07,0xfc,0x07,0xfc,0x07,0x00,0x00,0x00,0x00};
static char check_black_bits[] = {
 0x00,0x00,0xfe,0x0f,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,
 0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x00,0x00};
static char check_dark_bits[] = {
 0xff,0x1f,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
 0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};
static char check_light_bits[] = {
 0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
 0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0xfe,0x1f};
static char check_mid_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,
 0x08,0x00,0x08,0x00,0x08,0x00,0x08,0xfc,0x0f,0x00,0x00};
static char check_text_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x03,0x80,0x01,0x80,0x00,0xd8,
 0x00,0x60,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char radio_base_bits[] = {
 0x00,0x00,0x00,0x00,0xf0,0x01,0xf8,0x03,0xfc,0x07,0xfc,0x07,0xfc,0x07,0xfc,
 0x07,0xfc,0x07,0xf8,0x03,0xf0,0x01,0x00,0x00,0x00,0x00};
static char radio_black_bits[] = {
 0x00,0x00,0xf0,0x01,0x08,0x02,0x04,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,
 0x00,0x02,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static char radio_dark_bits[] = {
 0xf0,0x01,0x08,0x02,0x04,0x04,0x02,0x04,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
 0x00,0x01,0x00,0x02,0x00,0x0c,0x00,0x00,0x00,0x00,0x00};
static char radio_light_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
 0x10,0x00,0x10,0x00,0x08,0x00,0x04,0x08,0x02,0xf0,0x01};
static char radio_mid_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,
 0x08,0x00,0x08,0x00,0x04,0x00,0x02,0xf0,0x01,0x00,0x00};
static char radio_text_bits[] = {
 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0x00,0xf0,0x01,0xf0,0x01,0xf0,
 0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

static struct {
  char      *bits;
  GdkBitmap *bmap;
} parts[] = {
  { check_aa_bits, NULL },
  { check_base_bits, NULL },
  { check_black_bits, NULL },
  { check_dark_bits, NULL },
  { check_light_bits, NULL },
  { check_mid_bits, NULL },
  { check_text_bits, NULL },
  { radio_base_bits, NULL },
  { radio_black_bits, NULL },
  { radio_dark_bits, NULL },
  { radio_light_bits, NULL },
  { radio_mid_bits, NULL },
  { radio_text_bits, NULL }
};

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
draw_hline (GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail, gint x1, gint x2, gint y) {

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

    if (area)
        gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);

    gdk_draw_line (window, style->dark_gc[state_type], x1, y, x2, y);

    if (area)
        gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
}

static void
draw_vline (GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail, gint y1, gint y2, gint x)
{
	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

    if (area)
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);

    gdk_draw_line(window, style->dark_gc[state_type], x, y1, x, y2);

    if (area)
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
}

static void
draw_shadow (GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail, gint x, gint y, gint width, gint height)
{
	//GdkGC *gc1 = NULL;
	//GdkGC *gc2 = NULL;
	GdkGC *gc = NULL;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

    return;

	if ((width == -1) && (height == -1))
		gdk_window_get_size (window, &width, &height);
	else if (width == -1)
		gdk_window_get_size (window, &width, NULL);
	else if (height == -1)
		gdk_window_get_size (window, NULL, &height);

    gc = style->dark_gc[state_type];

    // we don't want shadows, because non-alphablended shadow
    // are evilll
    if (shadow_type != GTK_SHADOW_NONE)
    {	
        if (area)
            gdk_gc_set_clip_rectangle (gc, area);

        gdk_draw_line (window, gc, x, y, x + width, y);
        gdk_draw_line (window, gc, x, y, x, y + height);
        gdk_draw_line (window, gc, x, y + height, x + width, y + height);
        gdk_draw_line (window, gc, x + width, y, x + width, y + height);

        if (area)
            gdk_gc_set_clip_rectangle (gc, NULL);
    }
}

static void
draw_polygon (GtkStyle * style,
	      GdkWindow * window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle * area,
	      GtkWidget * widget,
	      const gchar * detail,
	      GdkPoint * points, gint npoints, gint fill)
{
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

	switch (shadow_type) {
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

	if (area) {
		gdk_gc_set_clip_rectangle (gc1, area);
		gdk_gc_set_clip_rectangle (gc2, area);
		gdk_gc_set_clip_rectangle (gc3, area);
		gdk_gc_set_clip_rectangle (gc4, area);
	}

	if (fill)
		gdk_draw_polygon (window, style->bg_gc[state_type], TRUE,
				  points, npoints);

	npoints--;

	for (i = 0; i < npoints; i++) {
		if ((points[i].x == points[i + 1].x) &&
		    (points[i].y == points[i + 1].y)) {
			angle = 0;
		} else {
			angle = atan2 (points[i + 1].y - points[i].y,
				       points[i + 1].x - points[i].x);
		}

		if ((angle > -pi_3_over_4) && (angle < pi_over_4)) {
			if (angle > -pi_over_4) {
				xadjust = 0;
				yadjust = 1;
			} else {
				xadjust = 1;
				yadjust = 0;
			}

			gdk_draw_line (window, gc1,
				       points[i].x - xadjust,
				       points[i].y - yadjust,
				       points[i + 1].x - xadjust,
				       points[i + 1].y - yadjust);
			gdk_draw_line (window, gc3, points[i].x,
				       points[i].y, points[i + 1].x,
				       points[i + 1].y);
		} else {
			if ((angle < -pi_3_over_4)
			    || (angle > pi_3_over_4)) {
				xadjust = 0;
				yadjust = 1;
			} else {
				xadjust = 1;
				yadjust = 0;
			}

			gdk_draw_line (window, gc4,
				       points[i].x + xadjust,
				       points[i].y + yadjust,
				       points[i + 1].x + xadjust,
				       points[i + 1].y + yadjust);
			gdk_draw_line (window, gc2, points[i].x,
				       points[i].y, points[i + 1].x,
				       points[i + 1].y);
		}
	}
	if (area) {
		gdk_gc_set_clip_rectangle (gc1, NULL);
		gdk_gc_set_clip_rectangle (gc2, NULL);
		gdk_gc_set_clip_rectangle (gc3, NULL);
		gdk_gc_set_clip_rectangle (gc4, NULL);
	}
}

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

static void
draw_arrow (GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
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
      if (state_type == GTK_STATE_INSENSITIVE)
	draw_black_arrow (window, style->white_gc, area, arrow_type,
			  ax + 1, ay + 1, aw, ah);
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
			ax, ay, aw, ah);
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
                          ax + 1, ay + 1, 3, 5);
      draw_black_arrow (window, style->fg_gc[state_type], area, arrow_type,
                        ax, ay, 3, 5);
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

static void
draw_diamond (GtkStyle * style,
	      GdkWindow * window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle * area,
	      GtkWidget * widget,
	      const gchar * detail, gint x, gint y, gint width,
	      gint height)
{
	gint half_width;
	gint half_height;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);
#ifdef DEBUG
	g_print ("%-17s %-15s\n", "draw_diamond", detail);
#endif

	if ((width == -1) && (height == -1))
		gdk_window_get_size (window, &width, &height);
	else if (width == -1)
		gdk_window_get_size (window, &width, NULL);
	else if (height == -1)
		gdk_window_get_size (window, NULL, &height);

	half_width = width / 2;
	half_height = height / 2;

	if (area) {
		gdk_gc_set_clip_rectangle (style->light_gc[state_type],
					   area);
		gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type],
					   area);
		gdk_gc_set_clip_rectangle (style->black_gc, area);
	}
	switch (shadow_type) {
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
			       x, y + half_height, x + half_width,
			       y + height);
		gdk_draw_line (window, style->light_gc[state_type],
			       x + half_width, y + height, x + width,
			       y + half_height);

		gdk_draw_line (window, style->dark_gc[state_type],
			       x + 2, y + half_height, x + half_width,
			       y + 2);
		gdk_draw_line (window, style->dark_gc[state_type],
			       x + half_width, y + 2, x + width - 2,
			       y + half_height);
		gdk_draw_line (window, style->dark_gc[state_type], x + 1,
			       y + half_height, x + half_width, y + 1);
		gdk_draw_line (window, style->dark_gc[state_type],
			       x + half_width, y + 1, x + width - 1,
			       y + half_height);
		gdk_draw_line (window, style->dark_gc[state_type], x,
			       y + half_height, x + half_width, y);
		gdk_draw_line (window, style->dark_gc[state_type],
			       x + half_width, y, x + width,
			       y + half_height);
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
			       x, y + half_height, x + half_width,
			       y + height);
		gdk_draw_line (window, style->dark_gc[state_type],
			       x + half_width, y + height, x + width,
			       y + half_height);

		gdk_draw_line (window, style->light_gc[state_type],
			       x + 2, y + half_height, x + half_width,
			       y + 2);
		gdk_draw_line (window, style->light_gc[state_type],
			       x + half_width, y + 2, x + width - 2,
			       y + half_height);
		gdk_draw_line (window, style->light_gc[state_type], x + 1,
			       y + half_height, x + half_width, y + 1);
		gdk_draw_line (window, style->light_gc[state_type],
			       x + half_width, y + 1, x + width - 1,
			       y + half_height);
		gdk_draw_line (window, style->light_gc[state_type], x,
			       y + half_height, x + half_width, y);
		gdk_draw_line (window, style->light_gc[state_type],
			       x + half_width, y, x + width,
			       y + half_height);
		break;
	default:
		break;
	}
	if (area) {
		gdk_gc_set_clip_rectangle (style->light_gc[state_type],
					   NULL);
		gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type],
					   NULL);
		gdk_gc_set_clip_rectangle (style->black_gc, NULL);
	}
}

static void
draw_box (GtkStyle * style,
	  GdkWindow * window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle * area,
	  GtkWidget * widget,
	  const gchar * detail, gint x, gint y, gint width, gint height)
{
    GdkGC *light_gc, *dark_gc, *bg_gc;
    GtkOrientation orientation;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
  
    if ((width == -1) && (height == -1))
        gdk_window_get_size (window, &width, &height);
    else if (width == -1)
        gdk_window_get_size (window, &width, NULL);
    else if (height == -1)
        gdk_window_get_size (window, NULL, &height);

    sanitize_size(window, &width, &height);

    light_gc = style->light_gc[state_type];
    dark_gc = style->dark_gc[state_type];
    bg_gc = style->bg_gc[state_type];

    orientation = GTK_ORIENTATION_HORIZONTAL;
    if (height > width)
        orientation = GTK_ORIENTATION_VERTICAL;

#ifdef DEBUG
    g_print ("%p %s %i %i state_type = %d (%d)\n", detail, detail,
        width, height, state_type, orientation);
#endif

    if (DETAIL ("trough")) {

        if (area) {
            gdk_gc_set_clip_rectangle(bg_gc, area);
            gdk_gc_set_clip_rectangle(light_gc, area);
            gdk_gc_set_clip_rectangle(dark_gc, area);
        }

        gdk_draw_rectangle(window, bg_gc, TRUE, x, y, width, height);

/*
        width -= 4; height -= 4; x += 2; y += 2;

        gdk_draw_rectangle(window, light_gc, TRUE, x, y, width, height);
       
        gdk_draw_line(window, dark_gc, x, y, x + width, y);
        gdk_draw_line(window, dark_gc, x, y, x, y + height);
        gdk_draw_line(window, dark_gc, x, y + height, x + width, y + height);
        gdk_draw_line(window, dark_gc, x + width, y, x + width, y + height);
*/
        if (area) {
            gdk_gc_set_clip_rectangle(bg_gc, NULL);
            gdk_gc_set_clip_rectangle(light_gc, NULL);
            gdk_gc_set_clip_rectangle(dark_gc, NULL);
        }

    } else if (DETAIL ("vscrollbar") || DETAIL("hscrollbar") || DETAIL("bar")) {

        if (area)
            gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);

        gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE, x, y, width, height);

        if (area)
            gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);

    } else if (DETAIL ("slider")) {

        if (area)
            gdk_gc_set_clip_rectangle (light_gc, area);

        gdk_draw_rectangle (window, light_gc, TRUE, x, y, width, height);

        if (area)
            gdk_gc_set_clip_rectangle (light_gc, NULL);

	} else if (DETAIL ("buttondefault")) {
		/* I don't want no background on default buttons..
		   Let's add that cute triangle (see below) instead... */
	} else if (DETAIL ("button")) {
        gint px, py;

        if (area) {
            gdk_gc_set_clip_rectangle(light_gc, area);
            gdk_gc_set_clip_rectangle(style->black_gc, area);
            gdk_gc_set_clip_rectangle(dark_gc, area);
        }

        /* update the coordinates */
        width -= 4; height -= 4; x += 2; y += 2;

        gdk_draw_rectangle(window, light_gc, TRUE, x, y, width, height);
       
        gdk_draw_line(window, dark_gc, x, y, x + width, y);
        gdk_draw_line(window, dark_gc, x, y, x, y + height);
        gdk_draw_line(window, dark_gc, x, y + height, x + width, y + height);
        gdk_draw_line(window, dark_gc, x + width, y, x + width, y + height);

	    /*  Paint some points here instead of in "buttondefault"
	        which is drawn _behind_ the current button */
        if (GTK_WIDGET_HAS_DEFAULT (widget)) {
            px = x + width - 1;
            py = y+1;
     
            for (;py < (y+height); py += 2) {
                gdk_draw_point(window, style->dark_gc[state_type], px, py);
            }
        }

        if (area) {
            gdk_gc_set_clip_rectangle(light_gc, NULL);
            gdk_gc_set_clip_rectangle(style->black_gc, NULL);
            gdk_gc_set_clip_rectangle(dark_gc, NULL);
        }

	} else if (DETAIL ("handlebox_bin")) {

        if (area)
            gdk_gc_set_clip_rectangle(dark_gc, area);

        gdk_draw_rectangle(window, dark_gc, TRUE, x, y, width, height);

        if (area)
            gdk_gc_set_clip_rectangle(dark_gc, NULL);

    } else if (DETAIL ("menubar") || DETAIL("menuitem")) {

        if (area)
            gdk_gc_set_clip_rectangle(bg_gc, area);

        gdk_draw_rectangle(window, bg_gc, TRUE, x, y, width, height);

        if (area) {
            gdk_gc_set_clip_rectangle(bg_gc, NULL);
        }

	} else if (DETAIL ("tab")) {
		dwerg_tab(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	} else {

        if (area) {
            gdk_gc_set_clip_rectangle(bg_gc, area);
            gdk_gc_set_clip_rectangle(dark_gc, area);
        }

        gdk_draw_rectangle(window, bg_gc, TRUE, x, y, width, height);
       
        // update the coordinates
        height -= 2; width--;
        gdk_draw_line(window, dark_gc, x, y, x + width, y);
        gdk_draw_line(window, dark_gc, x, y, x, y + height);
        gdk_draw_line(window, dark_gc, x, y + height, x + width, y + height);
        gdk_draw_line(window, dark_gc, x + width, y, x + width, y + height);

        if (area) {
            gdk_gc_set_clip_rectangle(bg_gc, NULL);
            gdk_gc_set_clip_rectangle(dark_gc, NULL);
        }
	}
}

static void draw_flat_box (GtkStyle * style,
		      GdkWindow * window,
		      GtkStateType state_type,
		      GtkShadowType shadow_type,
		      GdkRectangle * area,
		      GtkWidget * widget,
		      const gchar * detail,
		      gint x, gint y, gint width, gint height)
{
    GdkGC *dark_gc, *light_gc;

    g_return_if_fail (style != NULL);
    g_return_if_fail (window != NULL);
 
#ifdef DEBUG 
    g_print ("%p %s %i %i state_type = %d\n", detail, detail,
        width, height, state_type);
#endif

    /* we're only interested in putting a line around the text
       fields */
    if (DETAIL("entry_bg"))
    {
        if ((width == -1) && (height == -1))
            gdk_window_get_size (window, &width, &height);
        else if (width == -1)
            gdk_window_get_size (window, &width, NULL);
        else if (height == -1)
            gdk_window_get_size (window, NULL, &height);

        sanitize_size(window, &width, &height);

        dark_gc = style->dark_gc[state_type];
        light_gc = style->light_gc[state_type];

        if (area) {
            gdk_gc_set_clip_rectangle(light_gc, area);
            gdk_gc_set_clip_rectangle(dark_gc, area);
        }

        gdk_draw_rectangle(window, light_gc, TRUE, x, y, width, height);
       
        // update the coordinates
        width -= 1; height -= 1;
        gdk_draw_line(window, dark_gc, x, y, x + width, y);
        gdk_draw_line(window, dark_gc, x, y, x, y + height);
        gdk_draw_line(window, dark_gc, x, y + height, x + width, y + height);
        gdk_draw_line(window, dark_gc, x + width, y, x + width, y + height);

        if (area) {
            gdk_gc_set_clip_rectangle(light_gc, NULL);
            gdk_gc_set_clip_rectangle(dark_gc, NULL);
        }
    }
}

static void
draw_part (GdkDrawable  *drawable,
	   GdkGC        *gc,
	   GdkRectangle *area,
	   gint          x,
	   gint          y,
	   Part          part)
{
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  
  if (!parts[part].bmap)
      parts[part].bmap = gdk_bitmap_create_from_data (drawable,
						      parts[part].bits,
						      PART_SIZE, PART_SIZE);

  gdk_gc_set_ts_origin (gc, x, y);
  gdk_gc_set_stipple (gc, parts[part].bmap);
  gdk_gc_set_fill (gc, GDK_STIPPLED);

  gdk_draw_rectangle (drawable, gc, TRUE, x, y, PART_SIZE, PART_SIZE);

  gdk_gc_set_fill (gc, GDK_SOLID);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_check (GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail, gint x, gint y, gint width, gint height)
{
    x -= ((1 + PART_SIZE) - width) / 2;
    y -= ((1 + PART_SIZE) - width) / 2;

    if (strcmp (detail, "check") == 0) {	/* Menu item */
        if (shadow_type == GTK_SHADOW_IN) {
            draw_part(window, style->black_gc, area, x, y, CHECK_TEXT);
            draw_part(window, style->dark_gc[state_type], area, x, y, CHECK_AA);
        }
    } else {
        gtk_paint_box (style, window, GTK_STATE_NORMAL, 
            GTK_SHADOW_IN, area, widget, detail, x, y, width + 3, height + 3);
        gdk_draw_rectangle (window, style->light_gc[state_type], TRUE, 
            x + 1,  y + 1, width + 1, height);
        if (shadow_type == GTK_SHADOW_IN) {
            draw_part (window, style->text_gc[state_type], area, x, y, CHECK_TEXT);
            draw_part (window, style->dark_gc[state_type], area, x, y, CHECK_AA);
        }
    }
}

/* Thanks to Evan Lawrence */
static void
draw_option (GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail, gint x, gint y, gint width, gint height)
{
    x -= (1 + PART_SIZE - width) / 2;
    y -= (1 + PART_SIZE - height) / 2;

    if (strcmp (detail, "option") == 0) { /* Menu item */
        if (shadow_type == GTK_SHADOW_IN)
            draw_part (window, style->black_gc, area, x + 1, y + 1, RADIO_TEXT);
    } else {
        gdk_draw_arc(window, style->light_gc[state_type],
            TRUE, x, y, width, height, 0, 360 * 64);
        gdk_draw_arc(window, style->dark_gc[state_type], FALSE, 
            x, y, width, height, 45 * 64, 225 * 64);
        gdk_draw_arc(window, style->light_gc[state_type], FALSE, 
            x, y, width, height, 225 * 64, 180 * 64);
        if (shadow_type == GTK_SHADOW_IN)
            draw_part (window, style->text_gc[state_type], area, x - 1, y - 1, RADIO_TEXT);
    }
}

static void
draw_shadow_gap (GtkStyle * style,
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
		 GtkPositionType gap_side, gint gap_x, gint gap_width)
{
	GdkRectangle rect;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

	gtk_paint_shadow (style, window, state_type, shadow_type, area,
			  widget, detail, x, y, width, height);

	switch (gap_side) {
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

	gtk_style_apply_default_background (style, window,
					    widget
					    &&
					    !GTK_WIDGET_NO_WINDOW (widget),
					    state_type, area, rect.x,
					    rect.y, rect.width,
					    rect.height);
}

static void
draw_box_gap (GtkStyle * style,
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
	      GtkPositionType gap_side, gint gap_x, gint gap_width)
{
	GdkRectangle rect;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

	gtk_paint_box (style, window, state_type, shadow_type, area,
		       widget, detail, x, y, width, height);

	switch (gap_side) {
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

	gtk_style_apply_default_background (style, window,
					    widget
					    &&
					    !GTK_WIDGET_NO_WINDOW (widget),
					    state_type, area, rect.x,
					    rect.y, rect.width,
					    rect.height);
}

static void
draw_extension (GtkStyle * style,
		GdkWindow * window,
		GtkStateType state_type,
		GtkShadowType shadow_type,
		GdkRectangle * area,
		GtkWidget * widget,
		const gchar * detail,
		gint x,
		gint y, gint width, gint height, GtkPositionType gap_side)
{
	GdkRectangle rect;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

	gtk_paint_box (style, window, state_type, shadow_type, area,
		       widget, detail, x, y, width, height);

	switch (gap_side) {
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

	gtk_style_apply_default_background (style, window,
					    widget
					    &&
					    !GTK_WIDGET_NO_WINDOW (widget),
					    state_type, area, rect.x,
					    rect.y, rect.width,
					    rect.height);
}
static void
draw_focus(GtkStyle *style,
    GdkWindow *window,
    GtkStateType state_type,
    GdkRectangle *area,
    GtkWidget *widget,
    const gchar *detail,
    gint x, gint y, gint width, gint height)
{
    gint px, py;
             
    g_return_if_fail(style != NULL);
    g_return_if_fail(window != NULL);

    sanitize_size (window, &width, &height);

	if (DETAIL ("button")) {
        px = x + width;
        py = y+1;
 
        if (area)
            gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);

        for (;py < (y+height); py += 2) {
            gdk_draw_point(window, style->dark_gc[state_type], px, py);
        }

        if (area)
            gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
    }
    else
    {
        if (area) {
            gdk_gc_set_clip_rectangle(style->mid_gc[state_type], area);
            gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
        }

        height--;

        gdk_draw_line(window, style->dark_gc[state_type], x, y+height-1, x+width, y+height-1);
        gdk_draw_line(window, style->mid_gc[state_type], x, y+height-2, x+width, y+height-2);

        if (area) {
            gdk_gc_set_clip_rectangle(style->mid_gc[state_type], NULL);
            gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
        }
    }
}   

static void
dwerg_dot(GdkWindow *window,
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
draw_slider (GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation)
{

    if (area) {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], area);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], area);
    }

    gdk_draw_rectangle(window, style->light_gc[state_type], TRUE, x, y, width, height);
   
    // update the coordinates
    width -= 1; height -= 1;
    gdk_draw_line(window, style->dark_gc[state_type], x, y, x + width, y);
    gdk_draw_line(window, style->dark_gc[state_type], x, y, x, y + height);
    gdk_draw_line(window, style->dark_gc[state_type], x, y + height, x + width, y + height);
    gdk_draw_line(window, style->dark_gc[state_type], x + width, y, x + width, y + height);

    if (area) {
        gdk_gc_set_clip_rectangle(style->light_gc[state_type], NULL);
        gdk_gc_set_clip_rectangle(style->dark_gc[state_type], NULL);
    }
}

static void
draw_handle (GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail,
	     gint x,
	     gint y, gint width, gint height, GtkOrientation orientation)
{
  GdkGC              *light_gc, *dark_gc;
  GdkRectangle        dest;
  gint                modx, mody;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  sanitize_size(window, &width, &height);

  if (DETAIL("paned")) 
    {
      int i, w;
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
      start_i = w/2 - 16;
      end_i = w/2 + 16;

      gdk_gc_set_clip_rectangle(light_gc, &dest);
      gdk_gc_set_clip_rectangle(dark_gc, &dest);

      if (orientation == GTK_ORIENTATION_HORIZONTAL)
        {
          for (i=x + start_i; i <= x + end_i; i+=8)
            {
              dwerg_dot(window, light_gc, dark_gc, i, y + height / 2);
            }
        }
      else
        {
          for (i=y + start_i; i <= y + end_i; i+=8)
            {
              dwerg_dot(window, light_gc, dark_gc, x + width / 2, i);
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

  dwerg_dot(window, light_gc, dark_gc,
	       x + width / 2 - modx,
	       y + height / 2 - mody);
  dwerg_dot(window, light_gc, dark_gc,
	       x + width / 2,
	       y + height / 2);
  dwerg_dot(window, light_gc, dark_gc,
	       x + width / 2 + modx,
	       y + height / 2 + mody);

  gdk_gc_set_clip_rectangle(light_gc, NULL);
  gdk_gc_set_clip_rectangle(dark_gc, NULL);
}

static void
dwerg_tab (GtkStyle * style,
	      GdkWindow * window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle * area,
	      GtkWidget * widget,
	      const gchar * detail,
	      gint x, gint y, gint width, gint height)
{
	GtkNotebook *notebook;
	GdkGC *bg_gc, *light_gc, *dark_gc;
	int orientation;


	light_gc = style->light_gc[state_type];
    bg_gc    = style->bg_gc[state_type];
	dark_gc  = style->dark_gc[state_type];

    if (DETAIL ("optionmenutab")) {
        parent_class->draw_tab (style, window, state_type, shadow_type,
            area, widget, detail, x, y, width, height);
        return;
	}

	notebook = GTK_NOTEBOOK (widget);
	orientation = notebook->tab_pos;

	if (area) {
		gdk_gc_set_clip_rectangle (bg_gc, area);
		gdk_gc_set_clip_rectangle (dark_gc, area);
		gdk_gc_set_clip_rectangle (light_gc, area);
	}

    width -= 2;
	switch (orientation) {
        case GTK_POS_TOP:
            gdk_draw_rectangle (window, bg_gc, TRUE, x, y, width, height-1);
            gdk_draw_line (window, dark_gc, x, y+height, x, y);
            gdk_draw_line (window, dark_gc, x, y, x+width, y);
            gdk_draw_line (window, dark_gc, x+width, y, x+width, y+height);
            break;
        case GTK_POS_BOTTOM:
            y -= 2;
            gdk_draw_rectangle (window, bg_gc, TRUE, x, y+1, width, height-1);
            gdk_draw_line (window, dark_gc, x, y + height, x, y);
            gdk_draw_line (window, dark_gc, x, y + height, x + width, y + height);
            gdk_draw_line (window, dark_gc, x + width, y, x + width, y + height);
            break;
        case GTK_POS_LEFT:
            gdk_draw_rectangle (window, bg_gc, TRUE, x, y, width, height);
            gdk_draw_line (window, dark_gc, x, y + height, x, y);
            gdk_draw_line (window, dark_gc, x, y, x + width, y);
            gdk_draw_line (window, dark_gc, x , y + height, x + width, y + height);
            break;
        case GTK_POS_RIGHT:
            gdk_draw_rectangle (window, bg_gc, TRUE, x, y, width, height);
            gdk_draw_line (window, dark_gc, x, y, x + width, y);
            gdk_draw_line (window, dark_gc, x, y + height, x + width, y + height);
            gdk_draw_line (window, dark_gc, x + width, y, x + width, y + height);
            break;
	}

	if (area) {
		gdk_gc_set_clip_rectangle (bg_gc, NULL);
		gdk_gc_set_clip_rectangle (dark_gc, NULL);
		gdk_gc_set_clip_rectangle (light_gc, NULL);
	}
}

GType dwerg_type_style = 0;

void
dwerg_style_register_type (GTypeModule * module)
{
	static const GTypeInfo object_info = {
		sizeof (DwergStyleClass),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) dwerg_style_class_init,
		NULL,		/* class_finalize */
		NULL,		/* class_data */
		sizeof (DwergStyle),
		0,		/* n_preallocs */
		(GInstanceInitFunc) dwerg_style_init,
	};

	dwerg_type_style = g_type_module_register_type (module,
							   GTK_TYPE_STYLE,
							   "DwergStyle",
							   &object_info,
							   0);
}

static void
dwerg_style_init (DwergStyle * style)
{
}

static void
dwerg_style_class_init (DwergStyleClass * klass)
{
	GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	style_class->draw_hline = draw_hline;
	style_class->draw_vline = draw_vline;
	style_class->draw_shadow = draw_shadow;
	style_class->draw_polygon = draw_polygon;
	style_class->draw_arrow = draw_arrow;
	style_class->draw_diamond = draw_diamond;
	/*style_class->draw_string = draw_string; */
	style_class->draw_box = draw_box;
	style_class->draw_flat_box = draw_flat_box;
	style_class->draw_check = draw_check;
	style_class->draw_option = draw_option;
	style_class->draw_tab = dwerg_tab;
	style_class->draw_shadow_gap = draw_shadow_gap;
	style_class->draw_box_gap = draw_box_gap;
	style_class->draw_extension = draw_extension;
	style_class->draw_focus = draw_focus;
	style_class->draw_slider = draw_slider;
	style_class->draw_handle = draw_handle;
}
