/**************************************************************************
* GTK Industrial Theme
* Designed by Tigert and Jimmac
* Implemented by Christopher James Lahey
*
* Based on GTK Bluecurve Theme
* Designed by Garrett LeSage
* Implemented by Alexander Larsson
*
* Parts of the code based on Metal theme, Copyright:
* Randy Gordon, randy@integrand.com
* Owen Taylor <otaylor@redhat.com>
*
* License: GPL (Gnu Public License)
*
**************************************************************************/

#include "industrial_style_versioned_include.h"

#define DETAIL(xx)   ((detail) && (!strcmp((xx), detail)))
#if INDUSTRIAL_GTK_VERSION == 2
#define WIDGET_TYPE_NAME(xx) (widget && !strcmp (g_type_name (G_TYPE_FROM_INSTANCE (widget)), (xx)))
#else
#define WIDGET_TYPE_NAME(xx) (FALSE)
#endif
/* #define DEBUG 1 */

static GtkStyleClass *parent_class;

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
shade_doubles (double *red, double *green, double *blue, double *red_fg, double *green_fg, double *blue_fg, float k)
{
  rgb_to_hls (red, green, blue);
  rgb_to_hls (red_fg, green_fg, blue_fg);
  
  *green = (*green - *green_fg) * k + *green_fg;
  if (*green > 1.0)
    *green = 1.0;
  else if (*green < 0.0)
    *green = 0.0;

  /* Don't change saturation. */
#if 0
  *blue *= k;
  if (*blue > 1.0)
    *blue = 1.0;
  else if (*blue < 0.0)
    *blue = 0.0;
#endif
  
  hls_to_rgb (red, green, blue);
}

static void
shade_color (GdkColor * a, GdkColor *fg, GdkColor * b, float k)
{
  gdouble red;
  gdouble green;
  gdouble blue;

  gdouble red_fg;
  gdouble green_fg;
  gdouble blue_fg;
  
  red = (gdouble) a->red / 65535.0;
  green = (gdouble) a->green / 65535.0;
  blue = (gdouble) a->blue / 65535.0;

  red_fg = (gdouble) fg->red / 65535.0;
  green_fg = (gdouble) fg->green / 65535.0;
  blue_fg = (gdouble) fg->blue / 65535.0;

  shade_doubles (&red, &green, &blue, &red_fg, &green_fg, &blue_fg, k);
  
  b->red = red * 65535.0;
  b->green = green * 65535.0;
  b->blue = blue * 65535.0;
}

#define TOHEX(x) (CLAMP ((int) ((x) * 255.0), 0, 255))
#define FROMHEX(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : (tolower(x) - 'a' + 10))

static void
shade_hex (GdkColor * a, GdkColor *fg, char hex[6])
{
  gdouble red;
  gdouble green;
  gdouble blue;

  gdouble red_fg;
  gdouble green_fg;
  gdouble blue_fg;

  double k;
  
  k = FROMHEX (hex[0]) * 0x10 + FROMHEX(hex[1]);
  k /= 253.0;

  red = (gdouble) a->red / 65535.0;
  green = (gdouble) a->green / 65535.0;
  blue = (gdouble) a->blue / 65535.0;

  red_fg = (gdouble) fg->red / 65535.0;
  green_fg = (gdouble) fg->green / 65535.0;
  blue_fg = (gdouble) fg->blue / 65535.0;

  shade_doubles (&red, &green, &blue, &red_fg, &green_fg, &blue_fg, k);

  sprintf (hex, "%02x%02x%02x", TOHEX (red), TOHEX (green), TOHEX (blue));
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

#define SHADE_FG   0 
#define SHADE_DARK 1 
#define SHADE_0x9E 2 
#define SHADE_0xB3 3 
#define SHADE_0xBB 4 
#define SHADE_0xBE 5 
#define SHADE_0xC7 6 
#define SHADE_0xC8 7 
#define SHADE_0xCA 8 
#define SHADE_0xD1 9 
#define SHADE_0xD5 10
#define SHADE_0xD9 11
#define SHADE_0xDA 12
#define SHADE_0xE7 13
#define SHADE_0xEA 14
#define SHADE_0xEB 15
#define SHADE_0xEC 16
#define SHADE_0xF2 17
#define SHADE_0xF3 18
#define SHADE_0xF4 19
#define SHADE_0xF6 20
#define SHADE_0xF7 21
#define SHADE_0xF8 22	
#define SHADE_0xFA 23	
#define SHADE_0xFB 24	
#define SHADE_0xFC 25
#define SHADE_0xFD 26
#define SHADE_0xFF 27
#define SHADE_HALF 28
#define SHADE_NEG  29

#define SHADE_COUNT 30
static const double shades[SHADE_COUNT] = { 0.0   / 253.0,   /* 0  - SHADE_FG   */
					    100.0 / 253.0,   /* 1  - SHADE_DARK 0x64 */
					    158.0 / 253.0,   /* 2  - SHADE_0x9E */
					    179.0 / 253.0,   /* 3  - SHADE_0xB3 */
					    187.0 / 253.0,   /* 4  - SHADE_0xBB */
					    190.0 / 253.0,   /* 5  - SHADE_0xBE */
					    199.0 / 253.0,   /* 6  - SHADE_0xC7 */
					    200.0 / 253.0,   /* 7  - SHADE_0xC8 */
					    202.0 / 253.0,   /* 8  - SHADE_0xCA */
					    209.0 / 253.0,   /* 9  - SHADE_0xD1 */
					    213.0 / 253.0,   /* 10 - SHADE_0xD5 */
					    217.0 / 253.0,   /* 11 - SHADE_0xD9 */
					    218.0 / 253.0,   /* 12 - SHADE_0xDA */
					    231.0 / 253.0,   /* 13 - SHADE_0xE7 */
					    234.0 / 253.0,   /* 14 - SHADE_0xEA */
					    235.0 / 253.0,   /* 15 - SHADE_0xEB */
					    236.0 / 253.0,   /* 16 - SHADE_0xEC */
					    242.0 / 253.0,   /* 17 - SHADE_0xF2 */
					    243.0 / 253.0,   /* 18 - SHADE_0xF3 */
					    244.0 / 253.0,   /* 19 - SHADE_0xF4 */
					    246.0 / 253.0,   /* 20 - SHADE_0xF6 */
					    247.0 / 253.0,   /* 21 - SHADE_0xF7 */
					    248.0 / 253.0,   /* 22 - SHADE_0xF8 */
					    250.0 / 253.0,   /* 23 - SHADE_0xFA */
					    251.0 / 253.0,   /* 24 - SHADE_0xFB */
					    252.0 / 253.0,   /* 25 - SHADE_0xFC */
					    253.0 / 253.0,   /* 26 - SHADE_0xFD */
					    255.0 / 253.0,   /* 27 - SHADE_0xFF */
					    50.0  / 100.0,   /* 28 - SHADE_HALF */ 
					    52.0  / 83.0 }; /* 29 - SHADE_NEG 0x34 / 0x53 */
/* 135.0 /  83.0 26 - SHADE_NEG (0x53 + 0x34) / 0x53 */

#define MENUITEM_BORDER_SHADE SHADE_NEG

#define HANDLE_SHADE SHADE_0xD9
#define SLIDER_HANDLE_SHADE SHADE_0xD9
#define LINE_SHADE SHADE_0x9E
#define STANDARD_BORDER_SHADE SHADE_0x9E
#define STANDARD_BEVEL_TOP_SHADE SHADE_0xFF
#define STANDARD_BEVEL_BOTTOM_SHADE SHADE_0xF3
#define TROUGH_BORDER_SHADE SHADE_0xC7
#define TROUGH_BG_SHADE SHADE_0xD9

#define BUTTON_BORDER_SHADE SHADE_0x9E

#define MENUBAR_BORDER_SHADE SHADE_0xEA

#define BUTTON_DEPRESSED_SHADOW_SHADE_1 SHADE_0xDA
#define BUTTON_DEPRESSED_SHADOW_SHADE_2 SHADE_0xEC
#define BUTTON_DEPRESSED_SHADOW_SHADE_3 SHADE_0xF7

#define SHADE_BG SHADE_0xFD


#define PIXMAP_CHECK_ACTIVE 0
#define PIXMAP_CHECK_INACTIVE 1
#define PIXMAP_CHECK_MIXED 2
#define PIXMAP_MEDIUM_CHECK_ACTIVE 3
#define PIXMAP_MEDIUM_CHECK_INACTIVE 4
#define PIXMAP_MEDIUM_CHECK_MIXED 5
#define PIXMAP_SMALL_CHECK_ACTIVE 6
#define PIXMAP_SMALL_CHECK_INACTIVE 7
#define PIXMAP_SMALL_CHECK_MIXED 8
#define PIXMAP_RADIO_ACTIVE 9
#define PIXMAP_RADIO_INACTIVE 10
#define PIXMAP_RADIO_MIXED 11
#define PIXMAP_SMALL_RADIO_ACTIVE 12
#define PIXMAP_SMALL_RADIO_INACTIVE 13
#define PIXMAP_SMALL_RADIO_MIXED 14

#define PIXMAP_COUNT 15

#include "checkbox-on.xpm"
#include "checkbox-off.xpm"
#include "checkbox-mixed.xpm"
#include "table-checkbox-on.xpm"
#include "table-checkbox-off.xpm"
#include "table-checkbox-mixed.xpm"
#include "menu-checkbox-on.xpm"
#include "menu-checkbox-off.xpm"
#include "menu-checkbox-mixed.xpm"
#include "radio-on.xpm"
#include "radio-off.xpm"
#include "radio-mixed.xpm"
#include "menu-radio-on.xpm"
#include "menu-radio-off.xpm"
#include "menu-radio-mixed.xpm"

static char ** pixmaps[PIXMAP_COUNT] = { checkbox_on_xpm,
					 checkbox_off_xpm,
					 checkbox_mixed_xpm,
					 table_checkbox_on_xpm,
					 table_checkbox_off_xpm,
					 table_checkbox_mixed_xpm,
					 menu_checkbox_on_xpm,
					 menu_checkbox_off_xpm,
					 menu_checkbox_mixed_xpm,
					 radio_on_xpm,
					 radio_off_xpm,
					 radio_mixed_xpm,
					 menu_radio_on_xpm,
					 menu_radio_off_xpm,
					 menu_radio_mixed_xpm };

typedef struct {
  GdkColor bg_color;
  GdkColor fg_color;
  GdkColor colors[SHADE_COUNT];
  GdkGC *gcs[SHADE_COUNT];
  GdkPixmap *pixmaps[PIXMAP_COUNT];
  GdkBitmap *masks[PIXMAP_COUNT];
} Shading;

static guint
hash_colors (gconstpointer key)
{
  GdkColor **colors = (GdkColor **) key;
  return colors[0]->red ^ (colors[0]->green << 8) ^ (colors[0]->blue << 16) ^
    (colors[1]->red) << 12 ^ (colors[1]->green << 20) ^ (colors[1]->blue << 4);
}

static gboolean
equal_colors (gconstpointer key1, gconstpointer key2)
{
  GdkColor **colors1 = (GdkColor **) key1;
  GdkColor **colors2 = (GdkColor **) key2;

  return colors1[0]->red == colors2[0]->red &&
    colors1[0]->green == colors2[0]->green &&
    colors1[0]->blue == colors2[0]->blue &&
    colors1[1]->red == colors2[1]->red &&
    colors1[1]->green == colors2[1]->green &&
    colors1[1]->blue == colors2[1]->blue;
}

#if 0
static void
free_colors (gpointer data)
{
  GdkColor **colors = data;
  gdk_color_free (colors[0]);
  gdk_color_free (colors[1]);
  g_free (colors);
}

static void
free_shading (gpointer data)
{
  int i;
  Shading *shading = data;
  for (i = 0; i < SHADE_COUNT; i++) {
    if (shading->gcs[i])
      g_object_unref (shading->gcs[i]);
  }
  g_free (shading);
}
#endif

static Shading *
get_shading (GtkStyle *style, GdkColor *bg_color, GdkColor *fg_color)
{
  Shading *shading;
  GdkColor *colors[2] = {bg_color, fg_color};

  if (GET_SHADING_HASH (style) == NULL)
    GET_SHADING_HASH (style) = g_hash_table_new (hash_colors, equal_colors);

  shading = g_hash_table_lookup (GET_SHADING_HASH (style), colors);

  if (shading == NULL) {
    int i;
    GdkColor **colors = g_new (GdkColor *, 2);

    shading = g_new (Shading, 1);
    shading->bg_color = *bg_color;
    shading->fg_color = *fg_color;
    for (i = 0; i < SHADE_COUNT; i++) {
      shading->gcs[i] = NULL;
    }
    for (i = 0; i < PIXMAP_COUNT; i++) {
      shading->pixmaps[i] = NULL;
    }
    colors[0] = gdk_color_copy (bg_color);
    colors[1] = gdk_color_copy (fg_color);

    g_hash_table_insert (GET_SHADING_HASH (style), colors, shading);
  }

  return shading;
}

static void
ensure_shade (GtkStyle *style, Shading *shading, int shade)
{
  if (shading->gcs[shade] == NULL) {
    double contrast = GET_CONTRAST (style);
    double contrast_center = GET_CONTRAST_CENTER (style);
    if (shade == SHADE_HALF ||
	shade == SHADE_NEG) {
      shade_color (&shading->bg_color, &shading->fg_color, &shading->colors[shade], shades[shade]);
    } else {
      shade_color (&shading->bg_color, &shading->fg_color, &shading->colors[shade], CLAMP ((shades[shade]-contrast_center) * contrast + contrast_center, 0.0, 1.0));
    }
    shading->gcs[shade] = realize_color (style, &shading->colors[shade]);
  }
}

/* This isn't robust pixmap parsing code.  It'll crash at a moments
 * notice, but not with the 12 pixmaps provided. 
 **/

static void
ensure_pixmap (GtkStyle *style, GdkWindow *window, Shading *shading, int pixmap)
{
  if (shading->pixmaps[pixmap] == NULL) {
    char **first_line;
    char **xpm;
    char **xpm_copy;
    int colors;
    int height;
    int width;
    int i;

    xpm = pixmaps[pixmap];
    first_line = g_strsplit (xpm[0], " ", 0);

    width = atoi (first_line[0]);
    height = atoi (first_line[1]);
    colors = atoi (first_line[2]);

    g_strfreev (first_line);

    xpm_copy = g_new (char *, 1 + colors + height + 1);
    xpm_copy[0] = g_strdup (xpm[0]);

    for (i = 1; i < 1 + colors; i++) {
      char *color;

      xpm_copy[i] = g_strdup (xpm[i]);

      color = strstr (xpm_copy[i], " #");
      if (color) {
	color += 2;
	shade_hex (&shading->bg_color, &shading->fg_color, color);
      }
    }
    for (; i < 1 + colors + height; i++) {
      xpm_copy[i] = g_strdup (xpm[i]);
    }
    xpm_copy[i] = NULL;

    shading->pixmaps[pixmap] = gdk_pixmap_colormap_create_from_xpm_d (window, style->colormap, &shading->masks[pixmap], &style->bg[GTK_STATE_NORMAL], xpm_copy);

    g_strfreev (xpm_copy);
  }
}

static GdkPixmap *
get_pixmap (GtkStyle *style, GdkWindow *window, GdkColor *bg_color, GdkColor *fg_color, int pixmap)
{
  Shading *shading = get_shading (style, bg_color, fg_color);
  ensure_pixmap (style, window, shading, pixmap);
  return shading->pixmaps[pixmap];
}

static GdkBitmap *
get_mask (GtkStyle *style, GdkWindow *window, GdkColor *bg_color, GdkColor *fg_color, int pixmap)
{
  Shading *shading = get_shading (style, bg_color, fg_color);
  ensure_pixmap (style, window, shading, pixmap);
  return shading->masks[pixmap];
}

static GdkGC *
get_gc (GtkStyle *style, GdkColor *bg_color, GdkColor *fg_color, int shade)
{
  Shading *shading = get_shading (style, bg_color, fg_color);
  ensure_shade (style, shading, shade);
  return shading->gcs[shade];
}

static GdkColor *
get_color (GtkStyle *style, GdkColor *bg_color, GdkColor *fg_color, int shade)
{
  Shading *shading = get_shading (style, bg_color, fg_color);
  ensure_shade (style, shading, shade);
  return &shading->colors[shade];
}

static GdkGC *
get_gray_gc (GtkStyle *style, int shade)
{
  return get_gc (style, &style->bg[GTK_STATE_NORMAL], &style->fg[GTK_STATE_NORMAL], shade);
}

static GdkColor *
get_gray_color (GtkStyle *style, int shade)
{
  return get_color (style, &style->bg[GTK_STATE_NORMAL], &style->fg[GTK_STATE_NORMAL], shade);
}

static gboolean 
sanitize_size (GdkWindow      *window,
	       gint           *width,
	       gint           *height)
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
static void
kaleidoscope_point (GdkWindow *window,
		    GdkGC *gc,
		    GdkRectangle *area,
		    gint x, gint y,
		    gint width, gint height,
		    gint offset_x, gint offset_y)
{
  if (!gc)
    return;
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  /* No mirror */
  gdk_draw_point (window, gc, x + offset_x, y + offset_y);
  /* Mirror x */
  gdk_draw_point (window, gc, x + width - offset_x - 1, y + offset_y);
  /* Mirror y */
  gdk_draw_point (window, gc, x + offset_x, y + height - offset_y - 1);
  /* Mirror both */
  gdk_draw_point (window, gc, x + width - offset_x - 1, y + height - offset_y - 1);
  /* Mirror diagonal */
  if (offset_x != offset_y) {
    gdk_draw_point (window, gc, x + offset_y, y + offset_x);
    gdk_draw_point (window, gc, x + width - offset_y - 1, y + offset_x);
    gdk_draw_point (window, gc, x + offset_y, y + height - offset_x - 1);
    gdk_draw_point (window, gc, x + width - offset_y - 1, y + height - offset_x - 1);
  }
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
kaleidoscope_line (GdkWindow *window,
		    GdkGC *gc,
		    GdkRectangle *area,
		    gint x, gint y,
		    gint width, gint height,
		    gint edge_distance_offset, gint directional_offset)
{
  if (!gc)
    return;
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  /* Top line */
  gdk_draw_line (window, gc,
		 x + directional_offset,
		 y + edge_distance_offset,
		 x + width - directional_offset - 1,
		 y + edge_distance_offset);

  /* Bottom line */
  gdk_draw_line (window, gc,
		 x + directional_offset,
		 y + height - edge_distance_offset - 1,
		 x + width - directional_offset - 1,
		 y + height - edge_distance_offset - 1);

  /* Left line */
  gdk_draw_line (window, gc,
		 x + edge_distance_offset,
		 y + directional_offset,
		 x + edge_distance_offset,
		 y + height - directional_offset - 1);

  /* Right line */
  gdk_draw_line (window, gc,
		 x + width - edge_distance_offset - 1,
		 y + directional_offset,
		 x + width - edge_distance_offset - 1,
		 y + height - directional_offset - 1);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

typedef enum {
  ROTATION_CORNER_TL = 0,
  ROTATION_CORNER_TR = 1,
  ROTATION_CORNER_BR = 2,
  ROTATION_CORNER_BL = 3
} RotationCorner;

static void
rotate_point (GtkPositionType pos, 
	      gint x, gint y,
	      gint width, gint height,
	      RotationCorner corner, /* if GTK_POS_TOP */
	      gint offset_x, gint offset_y,
	      gint *x_result, gint *y_result)
{
  int x_value, y_value;
  gboolean invert = 0;

  if (!x_result && !y_result)
    return;

  if (corner == ROTATION_CORNER_TR ||
      corner == ROTATION_CORNER_BL) {
    /* Swap values */
    offset_x ^= offset_y;
    offset_y ^= offset_x;
    offset_x ^= offset_y;
  }

  switch (pos) {
  case GTK_POS_TOP:
    /* corner += 0; */
    break;
  case GTK_POS_RIGHT:
    corner += 1;
    break;
  case GTK_POS_BOTTOM:
    corner = 3 - corner;
    invert = 1;
    break;
  case GTK_POS_LEFT:
    corner = 4 - corner;
    invert = 1;
    break;
  }
  corner %= 4;

  if (invert) {
    offset_x ^= offset_y;
    offset_y ^= offset_x;
    offset_x ^= offset_y;
  }

  switch (corner) {
  case ROTATION_CORNER_TL:
    x_value = x + offset_x;
    y_value = y + offset_y;
    break;
  case ROTATION_CORNER_TR:
    x_value = x + width - offset_y - 1;
    y_value = y + offset_x;
    break;
  case ROTATION_CORNER_BR:
    x_value = x + width - offset_x - 1;
    y_value = y + height - offset_y - 1;
    break;
  case ROTATION_CORNER_BL:
    x_value = x + offset_y;
    y_value = y + height - offset_x - 1;
    break;
  }

  if (x_result)
    *x_result = x_value;
  if (y_result)
    *y_result = y_value;
}

static void
draw_rotated_point (GdkWindow *window,
		    GdkGC *gc,
		    GdkRectangle *area,
		    GtkPositionType pos, 
		    gint x, gint y,
		    gint width, gint height,
		    RotationCorner corner,
		    gint offset_x, gint offset_y)
{
  int x_result, y_result;
  rotate_point (pos, x, y, width, height, corner, offset_x, offset_y, &x_result, &y_result);
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  /* No mirror */
  gdk_draw_point (window, gc, x_result, y_result);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_rotated_line (GdkWindow *window,
		   GdkGC *gc,
		   GdkRectangle *area,
		   GtkPositionType pos, 
		   gint x, gint y,
		   gint width, gint height,
		   RotationCorner corner_1,
		   gint offset_x_1, gint offset_y_1,
		   RotationCorner corner_2,
		   gint offset_x_2, gint offset_y_2)
{
  int x_result_1, y_result_1, x_result_2, y_result_2;
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  rotate_point (pos, x, y, width, height, corner_1, offset_x_1, offset_y_1, &x_result_1, &y_result_1);
  rotate_point (pos, x, y, width, height, corner_2, offset_x_2, offset_y_2, &x_result_2, &y_result_2);
  /* No mirror */
  gdk_draw_line (window, gc, x_result_1, y_result_1, x_result_2, y_result_2);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_rounded_rect_one_pixel (GdkWindow *window,
			     GdkGC *bg_gc,
			     GdkGC *fg_gc,
			     GdkGC *corner_gc,
			     GdkRectangle *area,
			     gint x, gint y,
			     gint width, gint height)
{
  /*
    ... ...
    .+@ @+.
    .@. .@.

    .@. .@.
    .+@ @+.
    ... ...

    The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
    Set of . around the edge not part of width & height.
  */

  if (bg_gc) {
    if (area)
      gdk_gc_set_clip_rectangle (bg_gc, area);
    gdk_draw_rectangle (window, bg_gc, TRUE, x, y, width, height);
    if (area)
      gdk_gc_set_clip_rectangle (bg_gc, NULL);
  }

  /* Draw @s */
  kaleidoscope_line (window, fg_gc, area, x, y, width, height, 0, 1);

  /* Draw +s */
  kaleidoscope_point (window, corner_gc, area, x, y, width, height, 0, 0);
}

static void
draw_rounded_rect_two_pixel (GdkWindow *window,
			     GdkGC *bg_gc,
			     GdkGC *fg_gc,
			     GdkGC *corner_gc,
			     GdkRectangle *area,
			     gint x, gint y,
			     gint width, gint height)
{
  /*
    .... ....
    ..+@ @+..
    .+@. .@+.
    .@.. ..@.

    .@.. ..@.
    .+@. .@+.
    ..+@ @+..
    .... ....

    The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
    Set of . around the edge not part of width & height.
  */

  if (bg_gc) {
    if (area)
      gdk_gc_set_clip_rectangle (bg_gc, area);
    gdk_draw_rectangle (window, bg_gc, TRUE, x + 1, y + 1, width - 2, height - 2);
    if (area)
      gdk_gc_set_clip_rectangle (bg_gc, NULL);
  }

  /* Draw @s */
  if (area)
    gdk_gc_set_clip_rectangle (fg_gc, area);
  kaleidoscope_line (window, fg_gc, NULL, x, y, width, height, 0, 2);
  kaleidoscope_point (window, fg_gc, NULL, x, y, width, height, 1, 1);
  if (area)
    gdk_gc_set_clip_rectangle (fg_gc, NULL);

  /* Draw +s */
  kaleidoscope_point (window, corner_gc, area, x, y, width, height, 0, 1);
}

static void
draw_dot (GdkWindow *window,
	  GdkGC *gc,
	  GtkOrientation orientation,
	  int x_base,
	  int y_base,
	  int first_offset,
	  int second_offset)
{
  if (orientation == GTK_ORIENTATION_HORIZONTAL) {
    gdk_draw_point (window,
		    gc,
		    x_base + first_offset,
		    y_base + second_offset);
  } else {
    gdk_draw_point (window,
		    gc,
		    x_base + second_offset,
		    y_base + first_offset);
  }
}

static void
draw_grid (GdkWindow *window,
	   GdkGC *gc,
	   gint x, gint y,
	   gint width, gint height)
{
  int i, j, k;

  /*
    ...........
    .@...@...@.
    ...........
    ...+...+...
    ...........
    .@...@...@.
    ...........
    ...+...+...
    ...........
    .@...@...@.
    ...........

    Repeated pattern.

    + and @ are the same color.  They're just used in comments later.

    Set of . around the edge not part of width & height.
  */
  for (k = 0; k <= 2; k += 2) /* draw @ -> k = 0 ... draw + -> k = 2 */
    for (i = k; i < width; i += 4)
      for (j = k; j < height; j += 4)
	gdk_draw_point (window, gc, x + i, y + j);
}


/**************************************************************************/

static void
draw_hline (GtkStyle     *style,
	    GdkWindow    *window,
	    GtkStateType  state_type,
	    GdkRectangle  *area,
	    GtkWidget     *widget,
	    INDUSTRIAL_CONST gchar   *detail,
	    gint          x1,
	    gint          x2,
	    gint          y)
{
  GdkGC *gc;
  
#if DEBUG
  printf ("draw_hline: %p %p %s %i %i %i\n", widget, window, detail, x1, x2,
	  y);
#endif

  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  if (DETAIL("label")) {
    if (state_type == GTK_STATE_INSENSITIVE) {
      if (area)
	gdk_gc_set_clip_rectangle (style->white_gc, area);
      gdk_draw_line (window, style->white_gc, x1 + 1, y + 1, x2 + 1, y + 1);
      if (area)
	gdk_gc_set_clip_rectangle (style->white_gc, NULL);
    }
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_FG);
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    gdk_draw_line (window, gc, x1, y, x2, y);
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);
  } else {
    if (DETAIL ("menuitem"))
      y++;

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], LINE_SHADE);

    if (area)
      gdk_gc_set_clip_rectangle (gc, area);

    gdk_draw_line (window, gc,
		   x1, y, x2, y);

    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);
  }
}

/**************************************************************************/

static void 
draw_handle (GtkStyle      *style,
	     GdkWindow     *window,
	     GtkStateType   state_type,
	     GtkShadowType  shadow_type,
	     GdkRectangle  *area,
	     GtkWidget     *widget,
	     INDUSTRIAL_CONST gchar   *detail,
	     gint           x,
	     gint           y,
	     gint           width,
	     gint           height,
	     GtkOrientation orientation)
{
  GdkGC *gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], HANDLE_SHADE);
  int handle_width, handle_height, maxwidth, maxheight;

  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  sanitize_size (window, &width, &height);

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i  %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height, orientation);
#endif
  
  gtk_paint_box (style, window, state_type, shadow_type, area, widget, 
                 detail, x, y, width, height);

#define HANDLE_HANDLE_HEIGHT (4 * 4 + 1)
#define HANDLE_HANDLE_WIDTH (4 + 1)

  if (DETAIL ("paned")) {
#if 0
    x += 3;
    y += 3;
    width -= 5;
    height -= 5;
#endif
  } else {
    x += 2;
    y += 2;
    width -= 4;
    height -= 4;
  }

#if INDUSTRIAL_GTK_VERSION == 2
  if (DETAIL ("dockitem") ||
      WIDGET_TYPE_NAME ("PanelAppletFrame")) {
    if (orientation == GTK_ORIENTATION_HORIZONTAL)
      orientation = GTK_ORIENTATION_VERTICAL;
    else
      orientation = GTK_ORIENTATION_HORIZONTAL;
  }
#endif

  if (shadow_type == GTK_SHADOW_NONE) {
    maxwidth = width;
    maxheight = height;
  } else {
    maxwidth = width - 2;
    maxheight = height - 2;
  }

  if (orientation == GTK_ORIENTATION_HORIZONTAL)
    {
      handle_width = MIN (maxwidth, HANDLE_HANDLE_HEIGHT);
      handle_height = MIN (maxheight, HANDLE_HANDLE_WIDTH);
    }
  else
    {
      handle_width = MIN (maxwidth, HANDLE_HANDLE_WIDTH);
      handle_height = MIN (maxheight, HANDLE_HANDLE_HEIGHT);
    }

  if (handle_width <= 0 || handle_height <= 0)
    return;

  x += (width - handle_width) / 2;
  y += (height - handle_height) / 2;

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  draw_grid (window, gc, x, y, handle_width, handle_height);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

/**************************************************************************/

static void
draw_vline (GtkStyle     *style,
	    GdkWindow    *window,
	    GtkStateType  state_type,
	    GdkRectangle  *area,
	    GtkWidget     *widget,
	    INDUSTRIAL_CONST gchar   *detail,
	    gint          y1,
	    gint          y2,
	    gint          x)
{
  GdkGC *gc;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i\n", __FUNCTION__, widget, window, detail, y1, y2,
	  x);
#endif

  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], LINE_SHADE);

  if (area) {
    gdk_gc_set_clip_rectangle (gc, area);
  }
  
  gdk_draw_line (window, gc, x, y1, x, y2 - 1);
  
  if (area) {
    gdk_gc_set_clip_rectangle (gc, NULL);
  }
}

/**************************************************************************/
static void
draw_slider (GtkStyle      *style,
	     GdkWindow     *window,
	     GtkStateType   state_type,
	     GtkShadowType  shadow_type,
	     GdkRectangle  *area,
	     GtkWidget     *widget,
	     INDUSTRIAL_CONST gchar   *detail,
	     gint           x,
	     gint           y,
	     gint           width,
	     gint           height,
	     GtkOrientation orientation)
{
  int handle_width, handle_height;
  GdkGC *gc;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i  %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height, orientation);
#endif

  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  sanitize_size (window, &width, &height);

  if (widget && GTK_IS_SCROLLBAR (widget)) {
    GtkAdjustment *adjustment = GTK_RANGE (widget)->adjustment;
    if (adjustment->value ||  /* If all of these values are 0, don't do anything.  This fixes mozilla/galeon scrollbars. */
	adjustment->lower ||
	adjustment->upper ||
	adjustment->step_increment ||
	adjustment->page_increment ||
	adjustment->page_size) {
      if (adjustment->value <= adjustment->lower) {
	if (orientation == GTK_ORIENTATION_VERTICAL) {
	  y --;
	  height ++;
	} else {
	  x --;
	  width ++;
	}
      }
      if (adjustment->value >= adjustment->upper - adjustment->page_size) {
	if (orientation == GTK_ORIENTATION_VERTICAL) {
	  height ++;
	} else {
	  width ++;
	}
      }
    }
  }
  
  gtk_paint_box (style, window, state_type, shadow_type,
                 area, widget, detail, x, y, width, height);

  gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SLIDER_HANDLE_SHADE);

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  /* #define names assume vertical */
#define SLIDER_HANDLE_HEIGHT (4 * 4 + 1)
#define SLIDER_HANDLE_WIDTH (4 + 1)

  if (orientation == GTK_ORIENTATION_HORIZONTAL)
    {
      handle_width = MIN (width - 2, SLIDER_HANDLE_HEIGHT);
      handle_height = MIN (height - 2, SLIDER_HANDLE_WIDTH);
    }
  else
    {
      handle_width = MIN (width - 2, SLIDER_HANDLE_WIDTH);
      handle_height = MIN (height - 2, SLIDER_HANDLE_HEIGHT);
    }

  if (handle_width > 0 && handle_height > 0) {
    x += (width - handle_width) / 2;
    y += (height - handle_height) / 2;
    draw_grid (window, gc, x, y, handle_width, handle_height);
  }

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
real_draw_box (GtkStyle      *style,
	       GdkWindow     *window,
	       GtkStateType   state_type,
	       GtkShadowType  shadow_type,
	       GdkRectangle  *area,
	       GtkWidget     *widget,
	       INDUSTRIAL_CONST gchar   *detail,
	       gint           x,
	       gint           y,
	       gint           width,
	       gint           height,
	       gboolean       fill)
{
  if (shadow_type == GTK_SHADOW_NONE)
    return;
  
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  sanitize_size (window, &width, &height);

  if (DETAIL("button") ||
      DETAIL("togglebutton")) {
    /*
      .......... ...........
      ..+@@@@@@@ @@@@@@@@+..
      .+@....... ........@+.
      .@........ .......#.@.
      .@........ ......$%.@.
      .@........ .....$&%.@.
      .@........ ....*=&%.@.
      .@........ ...*#=&%.@.
      .@........ ..*$#=&%.@.
      .@........ .*-$#=&%.@.
		 
      .@........ .*-$#=&%.@.
      .@.......* **-$#=&%.@.
      .@......*- --$$#=&%.@.
      .@.....*$$ $$$##=&%.@.
      .@....*### ####==&%.@.
      .@...$==== =====&&%.@.
      .@..$&&&&& &&&&&&%%.@.
      .@.#%%%%%% %%%%%%%#.@.
      .+@....... ........@+.
      ..+@@@@@@@ @@@@@@@@+..
      .......... ...........

      The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
      Set of . around the edge not part of width & height.
    */

    GdkGC *gc;
    GdkColor *color;
    int gradient_lines = 7;

    if (! (GTK_WIDGET_HAS_DEFAULT (widget) &&
	   GTK_IS_BUTTON (widget) && 
	   GTK_BUTTON (widget)->relief == GTK_RELIEF_NORMAL/* &&
							      state_type != GTK_STATE_ACTIVE*/)) {
      /* if the button has default, we already drew the button shape and the background color */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_rectangle (window, gc, TRUE, x + 1, y + 1, width - 2, height - 2);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw @s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], BUTTON_BORDER_SHADE);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      if (GET_ROUNDED_BUTTONS (style)) {
	kaleidoscope_point (window, gc, NULL, x, y, width, height, 1, 1);
	kaleidoscope_line (window, gc, NULL, x, y, width, height, 0, 2);
      } else {
	kaleidoscope_line (window, gc, NULL, x, y, width, height, 0, 1);
      }
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw +s */
      color = get_color (style, &style->bg[state_type], &style->fg[state_type], BUTTON_BORDER_SHADE);
      gc = get_gc (style, &style->bg[state_type], color, SHADE_HALF);
      kaleidoscope_point (window, gc, area, x, y, width, height, 0, GET_ROUNDED_BUTTONS (style) ? 1 : 0);
    }

    /*
      Pushed button.
      ........... ..........
      ..+@@@@@@@@ @@@@@@@+..
      .+@'''''''' '''''''@+.
      .@'<<<<<<<< <<<<<<<<@.
      .@'<<"..... ....."<#@.
      .@'<"...... ......$%@.
      .@'<....... .....$&%@.
      .@'<....... ....*=&%@.
      .@'<....... ...*#=&%@.
      .@'<....... ..*$#=&%@.
      .@'<....... .*-$#=&%@.

      .@'<....... .*-$#=&%@.
      .@'<......* **-$#=&%@.
      .@'<.....*- --$$#=&%@.
      .@'<....*$$ $$$##=&%@.
      .@'<...*### ####==&%@.
      .@'<".$==== =====&&%@.
      .@'<<$&&&&& &&&&&&%%@.
      .+@<#%%%%%% %%%%%%%@+.
      ..+@@@@@@@@ @@@@@@@+.. 
      ......................
      The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
      Set of . around the edge not part of width & height.
    */
    if (state_type == GTK_STATE_ACTIVE) {
      /* Draw 's */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], BUTTON_DEPRESSED_SHADOW_SHADE_1);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      if (GET_ROUNDED_BUTTONS (style)) {
	gdk_draw_line (window, gc, x + 2, y + 1, x + width - 3, y + 1);
	gdk_draw_line (window, gc, x + 1, y + 2, x + 1, y + height - 3);
      } else {
	gdk_draw_line (window, gc, x + 1, y + 1, x + width - 2, y + 1);
	gdk_draw_line (window, gc, x + 1, y + 2, x + 1, y + height - 2);
      }
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw <s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], BUTTON_DEPRESSED_SHADOW_SHADE_2);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 2, y + 2, x + width - 2, y + 2);
      gdk_draw_line (window, gc, x + 2, y + 3, x + 2, y + height - 2);
      gdk_draw_point (window, gc, x + 3, y + 3);
      gdk_draw_point (window, gc, x + width - 3, y + 3);
      gdk_draw_point (window, gc, x + 3, y + height - 3);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw #s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], BUTTON_DEPRESSED_SHADOW_SHADE_3);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_point (window, gc, x + 3, y + 4);
      gdk_draw_point (window, gc, x + 4, y + 3);
      gdk_draw_point (window, gc, x + 3, y + height - 4);
      gdk_draw_point (window, gc, x + width - 4, y + 3);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);
    } else {
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF8);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_point (window, gc, x + width - 3, y + height - 3);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);
    }

    /* Only draw shadow if button is large enough to fit it. */
    if (width > 18 && height > 18) {

      /* Offset shadow if depressed. */
      if (state_type == GTK_STATE_ACTIVE) {
	x ++;
	y ++;
      }

      /* Draw *s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFC);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 8, y + height - 9, x + width - 9, y + height - 9);
      gdk_draw_line (window, gc, x + width - 9, y + 8, x + width - 9, y + height - 9);
      gdk_draw_point (window, gc, x + 5, y + height - 6);
      gdk_draw_point (window, gc, x + 6, y + height - 7);
      gdk_draw_point (window, gc, x + 7, y + height - 8);
      gdk_draw_point (window, gc, x + width - 6, y + 5);
      gdk_draw_point (window, gc, x + width - 7, y + 6);
      gdk_draw_point (window, gc, x + width - 8, y + 7);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw -s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFB);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 8, y + height - 8, x + width - 9, y + height - 8);
      gdk_draw_line (window, gc, x + width - 8, y + 8, x + width - 8, y + height - 9);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw $s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFA);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 7, y + height - 7, x + width - 8, y + height - 7);
      gdk_draw_line (window, gc, x + width - 7, y + 7, x + width - 7, y + height - 8);
      gdk_draw_point (window, gc, x + width - 8, y + height - 8);
      gdk_draw_point (window, gc, x + 3, y + height - 4);
      gdk_draw_point (window, gc, x + 4, y + height - 5);
      gdk_draw_point (window, gc, x + width - 4, y + 3);
      gdk_draw_point (window, gc, x + width - 5, y + 4);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw #s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF8);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 6, y + height - 6, x + width - 7, y + height - 6);
      gdk_draw_line (window, gc, x + width - 6, y + 6, x + width - 6, y + height - 7);
      gdk_draw_point (window, gc, x + width - 7, y + height - 7);
      gdk_draw_point (window, gc, x + 2, y + height - 3);
      gdk_draw_point (window, gc, x + width - 3, y + 2);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw =s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF6);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 5, y + height - 5, x + width - 6, y + height - 5);
      gdk_draw_line (window, gc, x + width - 5, y + 5, x + width - 5, y + height - 6);
      gdk_draw_point (window, gc, x + width - 6, y + height - 6);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw &s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF4);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      gdk_draw_line (window, gc, x + 4, y + height - 4, x + width - 5, y + height - 4);
      gdk_draw_line (window, gc, x + width - 4, y + 4, x + width - 4, y + height - 5);
      gdk_draw_point (window, gc, x + width - 5, y + height - 5);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);

      /* Draw %s */
      gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF3);
      if (area)
	gdk_gc_set_clip_rectangle (gc, area);
      if (GET_ROUNDED_BUTTONS (style)) {
	gdk_draw_line (window, gc, x + 3, y + height - 3, x + width - 4, y + height - 3);
	gdk_draw_line (window, gc, x + width - 3, y + 3, x + width - 3, y + height - 4);
      } else {
	gdk_draw_line (window, gc, x + 3, y + height - 3, x + width - 3, y + height - 3);
	gdk_draw_line (window, gc, x + width - 3, y + 3, x + width - 3, y + height - 4);
      }
      gdk_draw_point (window, gc, x + width - 4, y + height - 4);
      if (area)
	gdk_gc_set_clip_rectangle (gc, NULL);
    }
  } else if (DETAIL("buttondefault") ||
	     DETAIL("togglebuttondefault")) {
    /*
      .	c #FDFDFD
      +	c #FCFCFC
      @	c #FBFBFB
      #	c #FAFAFA
      0	c #F8F8F8
      -	c #F7F7F7
      a	c #F2F2F2
      3	c #EBEBEB
      6	c #EAEAEA
      =	c #E7E7E7
      2	c #D9D9D9
      4	c #D1D1D1
      <	c #C8C8C8
      '	c #BEBEBE
      )	c #BBBBBB
      {	c #B3B3B3
      ]	c #000000
      ......... .........
      .....+@## ##@+.....
      ...+0a3== ==3a0+...
      ..+-62<') )'<26-+..
      ..064{]]] ]]]{460..
      .+a2{]... ...]{2a+.
      .@3<].... ....]<3@.
      .#='].... ....]'=#.
      .#=)].... ....])=#.
      
      .#=)].... ....])=#.
      .#='].... ....]'=#.
      .@3<].... ....]<3@.
      .+a2{]... ...]{2a+.
      ..064{]]] ]]]{460..
      ..+-62<') )'<26-+..
      ...+0a3== ==3a0+...
      .....+@## ##@+.....
      ......... .........
      The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
      Set of . around the edge not part of width & height.
    */
    GdkGC *gc;

    gc = get_gc (style, &style->bg[GTK_WIDGET_STATE (widget)], &style->fg[GTK_WIDGET_STATE (widget)], SHADE_BG);
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    gdk_draw_rectangle (window, gc, TRUE, x + 4, y + 4, width - 8, height - 8);
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);

    /* Draw ]s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_FG);
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    kaleidoscope_point (window, gc, NULL, x, y, width, height, 4, 4);
    kaleidoscope_line (window, gc, NULL, x, y, width, height, 3, 5);
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);

    /* Draw {s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xB3);
    kaleidoscope_point (window, gc, area, x, y, width, height, 3, 4);

#if 1
    /* Remove this to add the shadow back for depressed buttons. */
    if (GTK_WIDGET_STATE (widget) == GTK_STATE_ACTIVE)
      return;
#endif

    /* Draw )s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xBB);
    kaleidoscope_line (window, gc, area, x, y, width, height, 2, 7);

    /* Draw 's */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xBE);
    kaleidoscope_point (window, gc, area, x, y, width, height, 2, 6);

    /* Draw <s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xC8);
    kaleidoscope_point (window, gc, area, x, y, width, height, 2, 5);

    /* Draw 4s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xD1);
    kaleidoscope_point (window, gc, area, x, y, width, height, 3, 3);

    /* Draw 2s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xD9);
    kaleidoscope_point (window, gc, area, x, y, width, height, 2, 4);

    /* Draw =s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xE7);
    kaleidoscope_line (window, gc, area, x, y, width, height, 1, 6);

    /* Draw 6s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xEA);
    kaleidoscope_point (window, gc, area, x, y, width, height, 2, 3);

    /* Draw 3s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xEB);
    kaleidoscope_point (window, gc, area, x, y, width, height, 1, 5);

    /* Draw as */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF2);
    kaleidoscope_point (window, gc, area, x, y, width, height, 1, 4);

    /* Draw -s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF7);
    kaleidoscope_point (window, gc, area, x, y, width, height, 2, 2);

    /* Draw 0s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF8);
    kaleidoscope_point (window, gc, area, x, y, width, height, 1, 3);

    /* Draw #s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFA);
    kaleidoscope_line (window, gc, area, x, y, width, height, 0, 6);

    /* Draw @s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFB);
    kaleidoscope_point (window, gc, area, x, y, width, height, 0, 5);

    /* Draw +s */
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFC);
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    kaleidoscope_point (window, gc, NULL, x, y, width, height, 0, 4);
    kaleidoscope_point (window, gc, NULL, x, y, width, height, 1, 2);
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);

  } else if (DETAIL("menuitem")) {
    GdkGC *bg_gc = fill ? get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG) : NULL;
    GdkGC *fg_gc = get_gc (style, &style->bg[state_type], &style->fg[GTK_STATE_NORMAL], MENUITEM_BORDER_SHADE);
    GdkColor *fg_color = get_color (style, &style->bg[state_type], &style->fg[GTK_STATE_NORMAL], MENUITEM_BORDER_SHADE);
    GdkGC *corner_gc = get_gc (style, &style->bg[GTK_STATE_NORMAL], fg_color, SHADE_HALF);

    draw_rounded_rect_one_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);
  } else if (DETAIL("trough") ||
	     DETAIL("menu") ||
	     DETAIL("dockitem_bin") ||
	     DETAIL("handlebox_bin") ||
	     DETAIL("toolbar") ||
	     DETAIL("dockitem") ||
	     WIDGET_TYPE_NAME("PanelAppletFrame")) {
    GdkGC *bg_gc = NULL;
    GdkGC *fg_gc;
    GdkColor *bg_color;
    GdkColor *fg_color;
    GdkGC *corner_gc;


    if (fill) {
      if (DETAIL("trough")) {
	if (state_type == GTK_STATE_ACTIVE)
	  state_type = GTK_STATE_NORMAL;
	fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], TROUGH_BORDER_SHADE);
	bg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], TROUGH_BG_SHADE);
	corner_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
      } else {
	fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], TROUGH_BORDER_SHADE);
	fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], TROUGH_BORDER_SHADE);
	bg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
	bg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
	corner_gc = get_gc (style, bg_color, fg_color, SHADE_HALF);
      }
    }

    draw_rounded_rect_one_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);
  } else if (DETAIL("menubar")) {
    GdkGC *bg_gc;
    GdkGC *fg_gc;
    GdkColor *bg_color;
    GdkColor *fg_color;
    GdkGC *corner_gc;

    bg_gc = fill ? get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG) : NULL;
    bg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
    fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], MENUBAR_BORDER_SHADE);
    fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], MENUBAR_BORDER_SHADE);
    corner_gc = get_gc (style, bg_color, fg_color, SHADE_HALF);

    draw_rounded_rect_one_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);
  } else if (DETAIL("spinbutton_up") ||
	     DETAIL("spinbutton_down")) {
    if (DETAIL("spinbutton_up")) {
      x += 1;
      y += 1;
      width -= 2;
      height -= 1;
    } else {
      x += 1;
      width -= 2;
      height -= 1;
    }

    parent_class->draw_flat_box (style, window, state_type, shadow_type, area,
				 widget, detail, x, y, width, height);
#if INDUSTRIAL_GTK_VERSION == 1
  } else if (DETAIL("slider")) {
    if (widget && GTK_IS_SCROLLBAR (widget)) {
      if (GTK_IS_VSCROLLBAR (widget))
	draw_slider (style, window, state_type, shadow_type, area, widget, "vscrollbar", x, y, width, height, GTK_ORIENTATION_VERTICAL);
      else
	draw_slider (style, window, state_type, shadow_type, area, widget, "hscrollbar", x, y, width, height, GTK_ORIENTATION_HORIZONTAL);
    } else {
      if (height > width)
	draw_slider (style, window, state_type, shadow_type, area, widget, "vscrollbar", x, y, width, height, GTK_ORIENTATION_VERTICAL);
      else
	draw_slider (style, window, state_type, shadow_type, area, widget, "hscrollbar", x, y, width, height, GTK_ORIENTATION_HORIZONTAL);
    }
#endif
  } else if (DETAIL ("slider") ||
	     DETAIL ("stepper") ||
	     DETAIL ("vscrollbar") ||
	     DETAIL ("hscrollbar")) {
    GdkGC *bg_gc = fill ? get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG) : NULL;
    /* This is different to merge with the trough bg. */
    GdkColor *bg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], TROUGH_BORDER_SHADE); 
    GdkGC *fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkColor *fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkGC *corner_gc = get_gc (style, bg_color, fg_color, SHADE_HALF);
    GdkGC *bevel_top_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BEVEL_TOP_SHADE);
    GdkGC *bevel_bottom_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BEVEL_BOTTOM_SHADE);

    draw_rounded_rect_two_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);
    draw_rotated_line (window, bevel_bottom_gc, area, GTK_POS_TOP, x, y, width, height, ROTATION_CORNER_TR, 1, 2, ROTATION_CORNER_BR, 1, 2);
    draw_rotated_line (window, bevel_bottom_gc, area, GTK_POS_TOP, x, y, width, height, ROTATION_CORNER_BR, 2, 1, ROTATION_CORNER_BL, 2, 1);
    draw_rotated_line (window, bevel_top_gc, area, GTK_POS_TOP, x, y, width, height, ROTATION_CORNER_BL, 1, 2, ROTATION_CORNER_TL, 1, 2);
    draw_rotated_line (window, bevel_top_gc, area, GTK_POS_TOP, x, y, width, height, ROTATION_CORNER_TL, 2, 1, ROTATION_CORNER_TR, 2, 1);
  } else if (DETAIL("optionmenu")) {
    GdkGC *bg_gc = fill ? get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG) : NULL;
    GdkGC *fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkColor *fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkGC *corner_gc = get_gc (style, &style->bg[state_type], fg_color, SHADE_HALF);
    int indicator_width;

    draw_rounded_rect_two_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);

    indicator_width = option_menu_get_indicator_width (widget);

    gtk_paint_vline (style, window, state_type, area, widget,
		     detail,
		     y + GET_YTHICKNESS (style) + 4,
		     y + height - GET_YTHICKNESS(style) - 4,
		     x + width - indicator_width - GET_XTHICKNESS(style) + 1);
  } else /* if (DETAIL("slider") ||
	     DETAIL("stepper") ||
	     DETAIL("vscrollbar") ||
	     DETAIL("hscrollbar") ||
	     DETAIL("vscale") ||
	     DETAIL("hscale") ||
	     DETAIL("optionmenu") ||
	     DETAIL("notebook") ||
	     DETAIL("text") ||
	     DETAIL("entry") ||
	     DETAIL("scrolled_window") ||
	     DETAIL("frame") ||
	     DETAIL("tab") ||
	     DETAIL("spinbutton"))*/ {
    GdkGC *bg_gc = fill ? get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG) : NULL;
    GdkGC *fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkColor *fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
    GdkGC *corner_gc = get_gc (style, &style->bg[state_type], fg_color, SHADE_HALF);

    draw_rounded_rect_one_pixel (window, bg_gc, fg_gc, corner_gc,
				 area, x, y, width, height);
  }
}

static void
draw_box (GtkStyle      *style,
	  GdkWindow     *window,
	  GtkStateType   state_type,
	  GtkShadowType  shadow_type,
	  GdkRectangle  *area,
	  GtkWidget     *widget,
	  INDUSTRIAL_CONST gchar   *detail,
	  gint           x,
	  gint           y,
	  gint           width,
	  gint           height)
{
#if DEBUG
  printf ("draw_box: %p %p %s %i %i %i %i\n", widget, window, detail, x, y,
	  width, height);
#endif

#if INDUSTRIAL_GTK_VERSION == 1
  if (DETAIL("hpaned")) {
    draw_handle (style, window, state_type, GTK_SHADOW_NONE, area, widget, "paned", x, y, width, height, GTK_ORIENTATION_VERTICAL);
  } else if (DETAIL("vpaned")) {
    draw_handle (style, window, state_type, GTK_SHADOW_NONE, area, widget, "paned", x, y, width, height, GTK_ORIENTATION_HORIZONTAL);
  } else {
#endif
    real_draw_box (style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, TRUE);
#if INDUSTRIAL_GTK_VERSION == 1
  }
#endif
}

static void
draw_shadow (GtkStyle        *style,
	     GdkWindow       *window,
	     GtkStateType     state_type,
	     GtkShadowType    shadow_type,
	     GdkRectangle    *area,
	     GtkWidget       *widget,
	     INDUSTRIAL_CONST gchar     *detail,
	     gint             x,
	     gint             y,
	     gint             width,
	     gint             height)
{
#if DEBUG
  printf ("draw_shadow: %p %p %s %i %i %i %i\n", widget, window, detail, x, y,
	  width, height);
#endif

#if INDUSTRIAL_GTK_VERSION == 1
  if ((DETAIL ("entry") ||
       DETAIL ("text")) &&
      GTK_WIDGET_HAS_FOCUS (widget)) {
    x --;
    y --;
    width += 2;
    height += 2;
  }
#endif

  real_draw_box (style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, FALSE);
}

/**************************************************************************/

static void 
real_draw_box_gap (GtkStyle       *style,
		   GdkWindow      *window,
		   GtkStateType    state_type,
		   GtkShadowType   shadow_type,
		   GdkRectangle   *area,
		   GtkWidget      *widget,
		   INDUSTRIAL_CONST gchar    *detail,
		   gint            x,
		   gint            y,
		   gint            width,
		   gint            height,
		   GtkPositionType gap_side,
		   gint            gap_x,
		   gint            gap_width,
		   gboolean        fill)
{
  GdkGC *gc;
  GdkColor *color;

  /*
    ... ...
    .+@ @+.
    .@. .@.

    .@. .@.
    .+@ @+.
    ... ...

    The spaces indicate repeat the line on either side (if they don't match, it's a bug in the drawing.)
    Set of . around the edge not part of width & height.
  */

  if (fill) {
    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);

    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    gdk_draw_rectangle (window, gc, TRUE, x + 1, y + 1, width - 2, height - 2);
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);
  }

  /* Draw +s */
  color = get_color (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
  gc = get_gc (style, &style->bg[state_type], color, SHADE_HALF);
  kaleidoscope_point (window, gc, area, x, y, width, height, 0, 0);

  gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  draw_rotated_line (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, MIN (gap_x, 1), 0, ROTATION_CORNER_TL, gap_x, 0);
  draw_rotated_line (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, gap_x + gap_width - 1, 0, ROTATION_CORNER_TR, 1, 0);
  draw_rotated_line (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TR, 0, 1, ROTATION_CORNER_BR, 0, 1);
  draw_rotated_line (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BR, 1, 0, ROTATION_CORNER_BL, 1, 0);
  draw_rotated_line (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 0, 1, ROTATION_CORNER_TL, 0, 1);

  if (gap_width >= 3)
    draw_rotated_line (window, get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG),
		       area, gap_side, x, y, width, height, ROTATION_CORNER_TL, gap_x + 1, 0, ROTATION_CORNER_TL, gap_x + gap_width - 2, 0);

  draw_rotated_point (window, gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, gap_x + gap_width - 1, 0);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);

  if (DETAIL("notebook"))
    draw_rotated_point (window, gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 0, 0);
}

static void 
draw_box_gap (GtkStyle       *style,
	      GdkWindow      *window,
	      GtkStateType    state_type,
	      GtkShadowType   shadow_type,
	      GdkRectangle   *area,
	      GtkWidget      *widget,
	      INDUSTRIAL_CONST gchar    *detail,
	      gint            x,
	      gint            y,
	      gint            width,
	      gint            height,
	      GtkPositionType gap_side,
	      gint            gap_x,
	      gint            gap_width)
{
#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i  %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height, gap_side);
#endif

  if (shadow_type == GTK_SHADOW_NONE)
    return;

  real_draw_box_gap (style, window, state_type, shadow_type, area, widget, detail,
		     x, y, width, height, gap_side, gap_x, gap_width, TRUE);
#if 0
  /* Unused stripe code. */
  if (DETAIL("notebook")) {
    GdkGC *gc;
    int i;

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xD5);
    draw_rotated_point (window, gc, area, x, y, width, height, ROTATION_CORNER_TL, 0, 0);
    draw_rotated_point (window, gc, area, x, y, width, height, ROTATION_CORNER_TR, 0, 0);
    draw_rotated_point (window, gc, area, x, y, width, height, ROTATION_CORNER_TR, 1, 1);
    for (i = 3; i < gap_width; i += 2) {
      draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TL, 1, i, ROTATION_CORNER_TR, i, 3);
    }

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xB3);
    draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_BL, 1, 0, ROTATION_CORNER_TL, 0, 1);
    draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TL, 1, 0, ROTATION_CORNER_TR, 0, 1);
    draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TR, 1, 0, ROTATION_CORNER_BR, 0, 1);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xE7);
    draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TR, 2, 1, ROTATION_CORNER_BR, 0, 2);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xCA);
    draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TL, 1, 1, ROTATION_CORNER_TR, 1, 3);
    for (i = 2; i < gap_width; i += 2) {
      draw_rotated_line (window, gc, area, x, y, width, height, ROTATION_CORNER_TL, 1, i, ROTATION_CORNER_TR, i, 3);
    }
  }
#endif
}

static void 
draw_shadow_gap (GtkStyle       *style,
		 GdkWindow      *window,
		 GtkStateType    state_type,
		 GtkShadowType   shadow_type,
		 GdkRectangle   *area,
		 GtkWidget      *widget,
		 INDUSTRIAL_CONST gchar    *detail,
		 gint            x,
		 gint            y,
		 gint            width,
		 gint            height,
		 GtkPositionType gap_side,
		 gint            gap_x,
		 gint            gap_width)
{
#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i  %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height, gap_side);
#endif

  if (shadow_type == GTK_SHADOW_NONE)
    return;

  real_draw_box_gap (style, window, state_type, shadow_type, area, widget, detail,
		     x, y, width, height, gap_side, gap_x, gap_width, FALSE);
  draw_box_gap (style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side, gap_x, gap_width);
}

static void 
draw_extension (GtkStyle       *style,
		GdkWindow      *window,
		GtkStateType    state_type,
		GtkShadowType   shadow_type,
		GdkRectangle   *area,
		GtkWidget      *widget,
		INDUSTRIAL_CONST gchar    *detail,
		gint            x,
		gint            y,
		gint            width,
		gint            height,
		GtkPositionType gap_side)
{
  GdkGC *bg_gc;
  GdkGC *fg_gc;
  GdkColor *fg_color;
  GdkGC *corner_gc;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i  %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height, gap_side);
#endif

  if (shadow_type == GTK_SHADOW_NONE)
    return;

  bg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_BG);
  fg_gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
  fg_color = get_color (style, &style->bg[state_type], &style->fg[state_type], STANDARD_BORDER_SHADE);
  corner_gc = get_gc (style, &style->bg[state_type], fg_color, SHADE_HALF);

  if (area) {
    gdk_gc_set_clip_rectangle (bg_gc, area);
    gdk_gc_set_clip_rectangle (fg_gc, area);
    gdk_gc_set_clip_rectangle (corner_gc, area);
  }

  gdk_draw_rectangle (window, bg_gc, TRUE, x + 1, y + 1, width - 1, height - 1);

  /* Draw @s */
  kaleidoscope_line  (window,     fg_gc, NULL, x, y, width, height, 0, 2);
  kaleidoscope_point (window, corner_gc, NULL, x, y, width, height, 0, 1);

  /* Draw shadow */
  if (state_type == GTK_STATE_ACTIVE) {
    GdkGC *gc;

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFB);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 6, ROTATION_CORNER_TR, 2, 6);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xFA);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 5, ROTATION_CORNER_TR, 2, 5);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF8);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 4, ROTATION_CORNER_TR, 2, 4);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF6);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 3, ROTATION_CORNER_TR, 2, 3);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TR, 1, 0, ROTATION_CORNER_BR, 1, 2);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF4);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 2, ROTATION_CORNER_TR, 2, 2);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF3);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 1, ROTATION_CORNER_TR, 2, 1);

    gc = get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_0xF2);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 2, 0, ROTATION_CORNER_TR, 2, 0);

    gc = get_gc (style, &style->bg[state_type], &style->bg[GTK_STATE_NORMAL], SHADE_HALF);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_BL, 2, 1, ROTATION_CORNER_BR, 2, 1);
    draw_rotated_line (window,     gc, area, gap_side, x, y, width, height, ROTATION_CORNER_TL, 1, 0, ROTATION_CORNER_BL, 1, 2);
  } else {
    draw_rotated_line (window,  bg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, 1, 0, ROTATION_CORNER_TR, 1, 0);
  }

  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, 0, 0);
  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TL, 0, 1);

  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TR, 0, 0);
  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_TR, 0, 1);

  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 1, 1);
  if (check_page (widget, x, y, width, height))
    draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 1, 0);
  else 
    draw_rotated_point (window, corner_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 1, 0);
  draw_rotated_point (window, corner_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 0, 1);
  draw_rotated_point (window,     bg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BL, 0, 0);

  draw_rotated_point (window,     fg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BR, 1, 1);
  draw_rotated_point (window, corner_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BR, 1, 0);
  draw_rotated_point (window, corner_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BR, 0, 1);
  draw_rotated_point (window,     bg_gc, NULL, gap_side, x, y, width, height, ROTATION_CORNER_BR, 0, 0);
  if (area) {
    gdk_gc_set_clip_rectangle (bg_gc, NULL);
    gdk_gc_set_clip_rectangle (fg_gc, NULL);
    gdk_gc_set_clip_rectangle (corner_gc, NULL);
  }
}

static void
real_draw_arrow (GdkWindow     *window,
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

/* Gtk 1 only.  A copy of the Gtk2 code. */
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
	    gint           height)
{
  gint original_width, original_x;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height);
#endif

  sanitize_size (window, &width, &height);

  original_width = width;
  original_x = x;


  if (DETAIL ("vscrollbar") ||
      DETAIL ("hscrollbar")) {
    gtk_paint_box (style, window, state, shadow, area, widget, "stepper", x, y, width, height);

    width -= 6;
    height -= 6;
    x += 3;
    y += 3;
  } else if (DETAIL ("spinbutton_up") ||
	     DETAIL ("spinbutton_down")) {
    width -= 4;
    height -= 4;
    x += 2;
    y += 2;
  } else {
    width -= 2;
    height -= 2;
    x++;
    y++;
  }

  calculate_arrow_geometry (arrow_type, &x, &y, &width, &height);
  
  if (DETAIL ("menuitem"))
    x = original_x + original_width - width;

  if (state == GTK_STATE_INSENSITIVE)
    real_draw_arrow (window, style->white_gc, area, arrow_type,
		     x + 1, y + 1, width, height);
  real_draw_arrow (window, get_gc (style, &style->bg[state], &style->fg[state], SHADE_FG),
		   area, arrow_type,
		   x, y, width, height);
}

static inline int
decode_shadow (GtkShadowType shadow_type)
{
  switch (shadow_type) {
  case GTK_SHADOW_IN:
    return 0;
  case GTK_SHADOW_ETCHED_IN:
    return 2;
  default:
    return 1;
  }
}

static void
draw_check (GtkStyle		*style,
	    GdkWindow		*window,
	    GtkStateType	 state_type,
	    GtkShadowType	 shadow_type,
	    GdkRectangle	*area,
	    GtkWidget		*widget,
	    INDUSTRIAL_CONST gchar		*detail,
	    gint		 x,
	    gint		 y,
	    gint		 width,
	    gint		 height)
{
  GdkPixmap *pixmap;
  GdkGC *gc;
  int src_width, src_height;
  int which;

  GdkColor *fg, *bg;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height);
#endif

#if INDUSTRIAL_GTK_VERSION == 1
  fg = &style->text[GTK_STATE_NORMAL];
  bg = &style->base[GTK_STATE_NORMAL];
#else
  if (state_type == GTK_STATE_NORMAL) {
    fg = &style->text[GTK_STATE_NORMAL];
    bg = &style->base[GTK_STATE_NORMAL];
  } else {
    fg = &style->fg[state_type];
    bg = &style->bg[state_type];
  } 
#endif

  if (width <= 8)
    which = PIXMAP_SMALL_CHECK_ACTIVE;
  else if (width <= 11)
    which = PIXMAP_MEDIUM_CHECK_ACTIVE;
  else
    which = PIXMAP_CHECK_ACTIVE;

  pixmap = get_pixmap (style, window, bg, fg, which + decode_shadow (shadow_type));
  gc = style->text_gc[state_type];

  gdk_window_get_size (pixmap, &src_width, &src_height);

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  gdk_gc_set_clip_mask (gc, get_mask (style, window, bg, fg, which + decode_shadow (shadow_type)));
  gdk_gc_set_clip_origin (gc, x, y);
  gdk_draw_pixmap (window, gc, pixmap, 0, 0, x, y, MIN (width, src_width), MIN (height, src_height));
  gdk_gc_set_clip_mask (gc, NULL);
  gdk_gc_set_clip_origin (gc, 0, 0);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

static void
draw_option (GtkStyle		*style,
	     GdkWindow		*window,
	     GtkStateType	 state_type,
	     GtkShadowType	 shadow_type,
	     GdkRectangle	*area,
	     GtkWidget		*widget,
	     INDUSTRIAL_CONST gchar	*detail,
	     gint		 x,
	     gint		 y,
	     gint		 width,
	     gint		 height)
{
  GdkPixmap *pixmap;
  GdkGC *gc;
  int src_width, src_height;
  int which;
  GdkColor *fg, *bg;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height);
#endif

#if INDUSTRIAL_GTK_VERSION == 1
  fg = &style->text[GTK_STATE_NORMAL];
  bg = &style->base[GTK_STATE_NORMAL];
#else
  if (state_type == GTK_STATE_NORMAL) {
    fg = &style->text[GTK_STATE_NORMAL];
    bg = &style->base[GTK_STATE_NORMAL];
  } else {
    fg = &style->fg[state_type];
    bg = &style->bg[state_type];
  } 
#endif

  if (width <= 8)
    which = PIXMAP_SMALL_RADIO_ACTIVE;
  else
    which = PIXMAP_RADIO_ACTIVE;

  pixmap = get_pixmap (style, window, bg, fg, which + decode_shadow (shadow_type));
  gc = style->text_gc[state_type];

  gdk_window_get_size (pixmap, &src_width, &src_height);

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);
  gdk_gc_set_clip_mask (gc, get_mask (style, window, bg, fg, which + decode_shadow (shadow_type)));
  gdk_gc_set_clip_origin (gc, x, y);
  gdk_draw_pixmap (window, gc, pixmap, 0, 0, x, y, MIN (width, src_width), MIN (height, src_height));
  gdk_gc_set_clip_mask (gc, NULL);
  gdk_gc_set_clip_origin (gc, 0, 0);
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

#if INDUSTRIAL_GTK_VERSION == 1
static void
draw_tab (GtkStyle		*style,
	     GdkWindow		*window,
	     GtkStateType	 state_type,
	     GtkShadowType	 shadow_type,
	     GdkRectangle	*area,
	     GtkWidget		*widget,
	     gchar		*detail,
	     gint		 x,
	     gint		 y,
	     gint		 width,
	     gint		 height)
{
#define ARROW_SPACE 4
  gint arrow_height;

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height);
#endif

#define INDICATOR_WIDTH 7
  arrow_height = INDICATOR_WIDTH / 2 + 1;

  x += (width - INDICATOR_WIDTH) / 2;
  y += (height - (2 * arrow_height + ARROW_SPACE)) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
      real_draw_arrow (window, style->white_gc, area,
		       GTK_ARROW_UP, x + 1, y + 1,
		       INDICATOR_WIDTH, arrow_height);
      
      real_draw_arrow (window, style->white_gc, area,
		       GTK_ARROW_DOWN, x + 1, y + arrow_height + ARROW_SPACE + 1,
		       INDICATOR_WIDTH, arrow_height);
    }
  
  real_draw_arrow (window, get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_FG),
		   area, GTK_ARROW_UP, x, y,
		   INDICATOR_WIDTH, arrow_height);

  real_draw_arrow (window, get_gc (style, &style->bg[state_type], &style->fg[state_type], SHADE_FG),
		   area, GTK_ARROW_DOWN, x, y + arrow_height + ARROW_SPACE,
		   INDICATOR_WIDTH, arrow_height);
}

static void 
draw_focus (GtkStyle      *style,
	    GdkWindow     *window,
	    GdkRectangle  *area,
	    GtkWidget     *widget,
	    gchar	  *detail,
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

#if DEBUG
  printf ("%s: %p %p %s %i %i %i %i\n", __FUNCTION__, widget, window, detail, x, y,
	  width, height);
#endif

#if INDUSTRIAL_GTK_VERSION == 1
  if (DETAIL ("entry") ||
      DETAIL ("text"))
    return;
#endif

  gc = get_gc (style, &style->fg[GTK_STATE_NORMAL], &style->bg[GTK_STATE_NORMAL], STANDARD_BORDER_SHADE);

  sanitize_size (window, &width, &height);
  
  if (DETAIL ("treeitem") ||
      DETAIL ("add-mode") ||
      detail == NULL ||
      DETAIL ("tab")) {
    width += 1;
    height += 1;
  } else if (DETAIL ("checkbutton")) {
    if (widget && GTK_IS_RADIO_BUTTON (widget)) {
      /* y -= 1 to center */
      /* y += 1 to make smaller, along with height -= 2 */
      height -= 2;
    }
    y += 3;
    height -= 4;
  } else if ((DETAIL ("button") ||
	      DETAIL ("togglebutton")) &&
	     !(widget && GTK_WIDGET_CAN_DEFAULT (widget))){
    x += 4;
    y += 4;
    width -= 7;
    height -= 7;
  } else if (DETAIL ("trough")) {
    x += 1;
    y += 1;
    width -= 2;
    height -= 2;
  } else {
    x += 1;
    y += 1;
    width -= 1;
    height -= 1;
  }

#if 0
  if (widget)
    {
      gtk_widget_style_get (widget,
			    "focus-line-width", &line_width,
			    "focus-line-pattern", (gchar *)&dash_list,
			    NULL);

      free_dash_list = TRUE;
  }
#endif

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


#if 0
  static GdkPixmap *small_stipple = NULL;
  static GdkPixmap *large_stipple = NULL;
  GdkPixmap *stipple;

  GdkGC *fg_gc = get_gc (style, &style->bg[GTK_STATE_NORMAL], &style->fg[GTK_STATE_NORMAL], STANDARD_BORDER_SHADE);
  GdkColor *fg_color = get_color (style, &style->bg[GTK_STATE_NORMAL], &style->fg[GTK_STATE_NORMAL], STANDARD_BORDER_SHADE);
  GdkGC *corner_gc = get_gc (style, &style->bg[GTK_STATE_NORMAL], fg_color, SHADE_HALF);

  if (!DETAIL ("add-mode") && small_stipple == NULL) {
    small_stipple = gdk_bitmap_create_from_data (window,
						 "\1\2", /* Checkerboard stipple */
						 2,
						 2);
    stipple = small_stipple;
  }

  if (DETAIL ("add-mode") && large_stipple == NULL) {
    large_stipple = gdk_bitmap_create_from_data (window,
						 "\x0f\x0f\x0f\x0f"
						 "\xf0\xf0\xf0\xf0", /* Large checkerboard stipple */
						 8,
						 8);
    stipple = large_stipple;
  }

  sanitize_size (window, &width, &height);
  
  gdk_gc_set_stipple (fg_gc, stipple);
  gdk_gc_set_stipple (corner_gc, stipple);

  draw_rounded_rect_one_pixel (window, NULL, fg_gc, corner_gc,
			       area, x, y, width, height);

  gdk_gc_set_stipple (fg_gc, NULL);
  gdk_gc_set_stipple (corner_gc, NULL);
#endif
}
#endif

#include "industrial_style_versioned_code.h"
