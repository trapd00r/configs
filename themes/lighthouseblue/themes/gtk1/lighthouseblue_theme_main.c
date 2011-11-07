#include <gmodule.h>
#include <gtk/gtk.h>

#include "lighthouseblue.h"

extern GtkStyleClass lighthouseblue_default_class;

enum
  {
    TOKEN_NOTEBOOKPATCH = G_TOKEN_LAST + 1,
    TOKEN_COMBINETVSELECT,
    TOKEN_WIDE,
    TOKEN_TRUE,
    TOKEN_FALSE
  };

static struct
{
  const gchar *name;
  guint token;
}
theme_symbols[] =
  {
    { "has_notebook_patch", TOKEN_NOTEBOOKPATCH },
    { "combine_treeview_select", TOKEN_COMBINETVSELECT },
    { "wide", TOKEN_WIDE },
    { "TRUE", TOKEN_TRUE },
    { "FALSE", TOKEN_FALSE }
  };

static guint n_theme_symbols = sizeof (theme_symbols) / sizeof (theme_symbols[0]);

static void lighthouseblue_rc_data_ref (LighthouseBlueRcData *rc_data)
{
  rc_data->refcount++;
}


static void lighthouseblue_rc_data_unref (LighthouseBlueRcData *rc_data)
{
  rc_data->refcount--;
  if (rc_data->refcount == 0)
    {
      g_free (rc_data);
    }
}

static guint theme_parse_boolean (GScanner *scanner, GTokenType wanted_token, guint *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    {
      return G_TOKEN_EQUAL_SIGN;
    }

  token = g_scanner_get_next_token (scanner);
  if (token == TOKEN_TRUE)
    {
      *retval = TRUE;
    }
  else if (token == TOKEN_FALSE)
    {
      *retval = FALSE;
    }
  else
    {
      *retval = FALSE;
    }

  return G_TOKEN_NONE;
}

static guint theme_parse_rc_style (GScanner *scanner, GtkRcStyle *rc_style)
{
  static GQuark scope_id = 0;
  LighthouseBlueRcData *rc_data;
  guint old_scope;
  guint token;
  guint i;
  
  /* Set up a new scope in this scanner. */
  if (!scope_id)
    scope_id = g_quark_from_string("lighthouseblue_theme_engine");

  /* If we bail out due to errors, we *don't* reset the scope, so the
   * error messaging code can make sense of our tokens.
   */
  old_scope = g_scanner_set_scope(scanner, scope_id);

  /* Now check if we already added our symbols to this scope
   * (in some previous call to bluecurve_rc_style_parse for the
   * same scanner.
   */

  if (!g_scanner_lookup_symbol(scanner, theme_symbols[0].name))
    {
      g_scanner_freeze_symbol_table(scanner);
      for (i = 0; i < n_theme_symbols; i++)
	g_scanner_scope_add_symbol(scanner, scope_id,
				   theme_symbols[i].name,
				   GINT_TO_POINTER(theme_symbols[i].token));
      g_scanner_thaw_symbol_table(scanner);
    }


  /* We're ready to go, now parse the top level */
  rc_data = g_new(LighthouseBlueRcData, 1);
  rc_data->refcount = 1;
  rc_data->has_notebook_patch = FALSE;
  rc_data->combine_treeview_select = FALSE;
  rc_data->wide = FALSE;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
	case TOKEN_NOTEBOOKPATCH:
	  token = theme_parse_boolean (scanner, TOKEN_NOTEBOOKPATCH, &rc_data->has_notebook_patch);
	  break;
	case TOKEN_COMBINETVSELECT:
	  token = theme_parse_boolean (scanner, TOKEN_COMBINETVSELECT, &rc_data->combine_treeview_select);
	  break;
	case TOKEN_WIDE:
	  token = theme_parse_boolean (scanner, TOKEN_WIDE, &rc_data->wide);
	  break;
	default:
	  g_scanner_get_next_token (scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	return token;

      token = g_scanner_peek_next_token (scanner);
    }

  g_scanner_get_next_token (scanner);

  rc_style->engine_data = rc_data;
  g_scanner_set_scope (scanner, old_scope);

  return G_TOKEN_NONE;
}

static void theme_merge_rc_style (GtkRcStyle *dest, GtkRcStyle *src)
{
  LighthouseBlueRcData *src_data = src->engine_data;
  
  if (!dest->engine_data)
    {
      if (src_data)
	{
	  lighthouseblue_rc_data_ref (src_data);
	  dest->engine_data = src_data;
	}
    }
}

static void set_props (GtkStyle *style)
{
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
  gtk_style_set_prop_experimental (style, "GtkRange::trough_border", 0);
  gtk_style_set_prop_experimental (style, "GtkRange::slider_width", 15);
  gtk_style_set_prop_experimental (style, "GtkRange::stepper_size", 15);
  gtk_style_set_prop_experimental (style, "GtkRange::stepper_spacing", 0);
  gtk_style_set_prop_experimental (style, "GtkSpinButton::shadow_type", GTK_SHADOW_IN);
}

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

void lighthouseblue_shade (GdkColor * a, GdkColor * b, float k)
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

static void shade (GdkColor * a, GdkColor * b, float k)
{
  lighthouseblue_shade (a, b, k);
}

static void theme_rc_style_to_style(GtkStyle * style, GtkRcStyle * rc_style)
{
  static GtkStyleClass *class = NULL;
  static GtkStyleClass *wide_class = NULL;

  LighthouseBlueRcData *rc_data = rc_style->engine_data;
  LighthouseBlueData *lighthouseblue_data;

  double shades[] = {1.065, 0.963, 0.896, 0.90, 0.768, 0.665, 0.4, 0.205};
  gint i;

  if (!class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      class = g_new (GtkStyleClass, 1);

      lighthouseblue_initialize_style (class, style->klass);
      gtk_style_unref (tmp_style);
      class->xthickness = 1;
      class->ythickness = 1;
    }

  if (!wide_class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      wide_class = g_new (GtkStyleClass, 1);

      lighthouseblue_initialize_style (wide_class, style->klass);
      gtk_style_unref (tmp_style);
      class->xthickness = 2;
      class->ythickness = 2;
    }
  
  if (rc_data->wide)
    {
      style->klass = wide_class;
    }
  else
    {
      style->klass = class;
    }

  lighthouseblue_data = style->engine_data = g_new0 (LighthouseBlueData, 1);

  /* Lighter to darker */
  for (i = 0; i < 8; i++)
    {
      shade (&style->bg[GTK_STATE_NORMAL], &lighthouseblue_data->shade[i], shades[i]);
    }
  
  set_props (style);
}

static void theme_duplicate_style(GtkStyle * dest, GtkStyle * src)
{
  dest->engine_data = g_memdup (src->engine_data, sizeof (LighthouseBlueData));
  set_props (dest);
}


static GdkGC *realize_color (GtkStyle * style, GdkColor * color)
{
  GdkGCValues gc_values;

  gdk_colormap_alloc_color (style->colormap, color,
			    FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (style->depth, style->colormap,
		     &gc_values, GDK_GC_FOREGROUND);
}

static void theme_realize_style(GtkStyle * style)
{
  LighthouseBlueData *lighthouseblue_data = style->engine_data;
  gint i;

  for (i = 0; i < 8; i++)
    {
      lighthouseblue_data->shade_gc[i] = realize_color (style, &lighthouseblue_data->shade[i]);
    }
}

static void theme_unrealize_style(GtkStyle * style)
{
  LighthouseBlueData *lighthouseblue_data = style->engine_data;
  int i;
  
  /* We don't free the colors, because we don't know if
   * gtk_gc_release() actually freed the GC. FIXME - need
   * a way of ref'ing colors explicitely so GtkGC can
   * handle things properly.
   */
  for (i=0; i < 8; i++)
    {
      gtk_gc_release (lighthouseblue_data->shade_gc[i]);
    }
}

static void theme_destroy_rc_style(GtkRcStyle * rc_style)
{
  LighthouseBlueRcData *rc_data = rc_style->engine_data;
  lighthouseblue_rc_data_unref (rc_data);
}

static void theme_destroy_style(GtkStyle * style)
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
