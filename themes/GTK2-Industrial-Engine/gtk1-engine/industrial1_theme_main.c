#include <gmodule.h>
#include <gtk/gtk.h>

#include "industrial1.h"

#include "../gtk2-engine/bits.c"

/* #define DEBUG 1 */

extern GtkStyleClass industrial_default_class;

#define G_N_ELEMENTS(x) (sizeof((x)) / sizeof((x)[0]))

#include "parse_rc_style.h"

static void
industrial_rc_data_ref (IndustrialRcData *industrial_data)
{
  industrial_data->refcount++;
}

static void
industrial_rc_data_unref (IndustrialRcData *industrial_data)
{
  industrial_data->refcount--;
  if (industrial_data->refcount == 0)
    {
      g_free (industrial_data);
    }
}

static guint
theme_parse_rc_style (GScanner   *scanner,
		      GtkRcStyle *rc_style)
		     
{
  IndustrialRcData *rc_data = rc_style->engine_data;

  rc_style->engine_data = rc_data = g_new(IndustrialRcData, 1);

  rc_data->refcount = 1;
  rc_data->contrast = 1.0;
  rc_data->contrast_center = 0.5;
  rc_data->rounded_buttons = TRUE;
  rc_data->wide = FALSE;
  rc_data->fields = 0;

  return parse_rc_style (scanner, &rc_data->contrast, &rc_data->contrast_center, &rc_data->rounded_buttons, &rc_data->wide, &rc_data->fields);
}

static void
theme_merge_rc_style (GtkRcStyle *dest,
		      GtkRcStyle *src)
{
  IndustrialRcData *src_data = src->engine_data;
  IndustrialRcData *dest_data = dest->engine_data;
  IndustrialFields fields;
  
  if (src_data) {
    if (!dest_data) {
      dest->engine_data = dest_data = g_new(IndustrialRcData, 1);

      dest_data->refcount = 1;
      dest_data->contrast = 1.0;
      dest_data->contrast_center = 0.5;
      dest_data->rounded_buttons = TRUE;
      dest_data->wide = FALSE;
      dest_data->fields = 0;
    }

    fields = (~dest_data->fields) & src_data->fields;

    if (fields & INDUSTRIAL_FIELDS_CONTRAST)
      dest_data->contrast = src_data->contrast;
    if (fields & INDUSTRIAL_FIELDS_CONTRAST_CENTER)
      dest_data->contrast_center = src_data->contrast_center;
    if (fields & INDUSTRIAL_FIELDS_ROUNDED_BUTTONS)
      dest_data->rounded_buttons = src_data->rounded_buttons;
    if (fields & INDUSTRIAL_FIELDS_WIDE)
      dest_data->wide = src_data->wide;

    dest_data->fields = dest_data->fields | src_data->fields;
  }
}

static void
set_props (GtkStyle *style)
{
  /* TODO: Change and/or add to these: */
#define OPTION_INDICATOR_WIDTH 7
#define OPTION_INDICATOR_LEFT_SPACING 7
#define OPTION_INDICATOR_RIGHT_SPACING 5
  gtk_style_set_prop_experimental (style, "GtkButton::default_spacing", 6);
  gtk_style_set_prop_experimental (style, "GtkCheckButton::indicator_size", 13);
  gtk_style_set_prop_experimental (style, "GtkOptionMenu::indicator_width", OPTION_INDICATOR_WIDTH);
  gtk_style_set_prop_experimental (style, "GtkOptionMenu::indicator_left_spacing", OPTION_INDICATOR_LEFT_SPACING);
  gtk_style_set_prop_experimental (style, "GtkOptionMenu::indicator_right_spacing", OPTION_INDICATOR_RIGHT_SPACING);
  gtk_style_set_prop_experimental (style, "GtkPaned::handle_full_size", 1);
  gtk_style_set_prop_experimental (style, "GtkPaned::handle_width", 6);
  gtk_style_set_prop_experimental (style, "GtkRange::always_draw_trough", 1);
  gtk_style_set_prop_experimental (style, "GtkRange::always_redraw", 1);
  gtk_style_set_prop_experimental (style, "GtkRange::trough_border", 0);
  gtk_style_set_prop_experimental (style, "GtkRange::slider_width", 15);
  gtk_style_set_prop_experimental (style, "GtkRange::stepper_size", 15);
  gtk_style_set_prop_experimental (style, "GtkRange::stepper_spacing", 0);
  gtk_style_set_prop_experimental (style, "GtkScrollbar::min_slider_length", 30);
  gtk_style_set_prop_experimental (style, "GtkSpinButton::shadow_type", GTK_SHADOW_IN);
}

/****************************************************************************/

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

void
industrial_shade (GdkColor * a, GdkColor * b, float k)
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
shade (GdkColor * a, GdkColor * b, float k)
{
  industrial_shade (a, b, k);
}

/**************************************************************************/

static void
theme_rc_style_to_style(GtkStyle * style,
			GtkRcStyle * rc_style)
{
  static GtkStyleClass *class = NULL;
  static GtkStyleClass *wide_class = NULL;
  IndustrialRcData *rc_data = rc_style->engine_data;
  IndustrialData *industrial_data;

  if (!class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      class = g_new (GtkStyleClass, 1);


      industrial_initialize_style (class, style->klass);
      gtk_style_unref (tmp_style);
      class->xthickness = 1;
      class->ythickness = 1;
    }
  
  if (!wide_class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      wide_class = g_new (GtkStyleClass, 1);

      industrial_initialize_style (wide_class, style->klass);
      gtk_style_unref (tmp_style);
      class->xthickness = 2;
      class->ythickness = 2;
    }

  if (rc_data->wide)
    style->klass = wide_class;
  else
    style->klass = class;
  industrial_data = style->engine_data = g_new0 (IndustrialData, 1);

  set_props (style);

  industrial_data->contrast = rc_data->contrast;
  industrial_data->contrast_center = rc_data->contrast_center;
  industrial_data->rounded_buttons = rc_data->rounded_buttons;
  industrial_data->shading_hash = NULL;
}

static void
theme_duplicate_style(GtkStyle * dest,
		      GtkStyle * src)
{
  IndustrialData *dest_data;
  IndustrialData *src_data = src->engine_data;

  dest_data = dest->engine_data = g_new0 (IndustrialData, 1);

  dest_data->contrast = src_data->contrast;
  dest_data->contrast_center = src_data->contrast_center;
  dest_data->rounded_buttons = src_data->rounded_buttons;
  dest_data->shading_hash = NULL;

  set_props (dest);
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

static void
theme_realize_style(GtkStyle * style)
{
}

static void
theme_unrealize_style(GtkStyle * style)
{
}

static void
theme_destroy_rc_style(GtkRcStyle * rc_style)
{
  IndustrialRcData *rc_data = rc_style->engine_data;
  industrial_rc_data_unref (rc_data);
}

static void
theme_destroy_style(GtkStyle * style)
{
  g_free (style->engine_data);
}

G_MODULE_EXPORT void
theme_init (GtkThemeEngine * engine)
{
  engine->parse_rc_style = theme_parse_rc_style;
  engine->merge_rc_style = theme_merge_rc_style;
  engine->rc_style_to_style = theme_rc_style_to_style;
  engine->duplicate_style = theme_duplicate_style;
  engine->realize_style = theme_realize_style;
  engine->unrealize_style = theme_unrealize_style;
  engine->destroy_rc_style = theme_destroy_rc_style;
  engine->destroy_style = theme_destroy_style;
  engine->set_background = NULL;

  gdk_rgb_init ();
}

G_MODULE_EXPORT void
theme_exit (void)
{
}

/* The following function will be called by GTK+ when the module
 * is loaded and checks to see if we are compatible with the
 * version of GTK+ that loads us.
 */
G_MODULE_EXPORT const gchar* g_module_check_init (GModule *module);
const gchar*
g_module_check_init (GModule *module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}
