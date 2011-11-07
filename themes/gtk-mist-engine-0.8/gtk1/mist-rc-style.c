#include "mist-theme.h"
#include <gmodule.h>
#include <stdio.h>
#include <gtk/gtkcheckbutton.h>
#include <gtk/gtkradiobutton.h>

/* Theme functions to export */
void                theme_init(GtkThemeEngine * engine);
void                theme_exit(void);

/* Exported vtable from th_draw */

extern GtkStyleClass mist_default_class;

/* internals */

/* external theme functions called */

guint
theme_parse_rc_style (GScanner *scanner, GtkRcStyle *rc_style)
{
	ThemeRcData *theme_data;
	guint scope_id;
	guint old_scope;
	guint token;

	if (!scope_id)
		scope_id = g_quark_from_string("theme_engine");

	old_scope = g_scanner_set_scope (scanner, scope_id);
	
#if 0
	if (!g_scanner_lookup_symbol(scanner, theme_symbols[0].name)) {
		g_scanner_freeze_symbol_table(scanner);
		for (i = 0; i < n_theme_symbols; i++)
		{
			g_scanner_scope_add_symbol(scanner, scope_id,
						   theme_symbols[i].name,
						   GINT_TO_POINTER(theme_symbols[i].token));
		}
		g_scanner_thaw_symbol_table(scanner);
	}
#endif
	token = g_scanner_peek_next_token (scanner);
	
	while (token != G_TOKEN_RIGHT_CURLY) {
		token = g_scanner_peek_next_token (scanner);
	}
	g_scanner_get_next_token (scanner);
	g_scanner_set_scope (scanner, old_scope);

	theme_data = g_new0 (ThemeRcData, 1);
	rc_style->engine_data = theme_data;

	return G_TOKEN_NONE;
}

void
theme_merge_rc_style(GtkRcStyle * dest,
		     GtkRcStyle * src)
{
  ThemeRcData        *src_data = src->engine_data;
  ThemeRcData        *dest_data = dest->engine_data;

  /*
  g_print("theme_merge_rc_style(\"%s\", \"%s\")\n", dest->name, src->name);
  */
  if (!dest_data)
    {
      dest_data = g_new0(ThemeRcData, 1);
      dest->engine_data = dest_data;
    }
}

void
theme_rc_style_to_style(GtkStyle * style,
			GtkRcStyle * rc_style)
{
  ThemeRcData        *data = rc_style->engine_data;
  ThemeStyleData     *style_data;

  /*
  g_print("theme_rc_style_to_style(GtkStyle, \"%s\")\n", rc_style->name);
  */
  style_data = g_new0(ThemeStyleData, 1);

  style->klass = &mist_default_class;
  style->engine_data = style_data;

  gtk_style_set_prop_experimental (style, "GtkButton::default_spacing", 0);
}

void
theme_duplicate_style(GtkStyle * dest,
		      GtkStyle * src)
{
  ThemeStyleData     *dest_data;
  ThemeStyleData     *src_data = src->engine_data;

  /*
  g_print("theme_duplicate_style\n");
  */
  dest_data = g_new0(ThemeStyleData, 1);

  dest->klass = &mist_default_class;
  dest->engine_data = dest_data;
}

void
theme_realize_style(GtkStyle * style)
{
  /*
  g_print("theme_realize_style(\"%s\")\n", style->rc_style->name);
  */
}

void
theme_unrealize_style(GtkStyle * style)
{
  /*
  g_print("theme_unrealize_style(\"%s\")\n", style->rc_style->name);
  */
}

void
theme_destroy_rc_style(GtkRcStyle * rc_style)
{
  ThemeRcData        *data = rc_style->engine_data;

  /*
  g_print("theme_destroy_rc_style(\"%s\")\n", rc_style->name);
  */
  if (data)
    {
      g_free(data);
    }
}

void
theme_destroy_style(GtkStyle * style)
{
  ThemeStyleData     *data = style->engine_data;

  /*
  g_print("theme_destroy_style\n");
  */
  if (data)
    {
      g_free(data);
    }
}

void
theme_set_background(GtkStyle * style,
		     GdkWindow * window,
		     GtkStateType state_type)
{
  GdkPixmap          *pixmap;
  gint                parent_relative;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if (style->bg_pixmap[state_type])
    {
      if (style->bg_pixmap[state_type] == (GdkPixmap *) GDK_PARENT_RELATIVE)
	{
	  pixmap = NULL;
	  parent_relative = TRUE;
	}
      else
	{
	  pixmap = style->bg_pixmap[state_type];
	  parent_relative = FALSE;
	}

      gdk_window_set_back_pixmap(window, pixmap, parent_relative);
    }
  else
    gdk_window_set_background(window, &style->bg[state_type]);
}

void
theme_init(GtkThemeEngine * engine)
{
  GtkRangeClass *rangeclass;
  GtkCheckButtonClass *checkbuttonclass;
  GtkCheckButtonClass *radiobuttonclass;

  /*
  g_print("theme_init\n");
  */
  engine->parse_rc_style = theme_parse_rc_style;
  engine->merge_rc_style = theme_merge_rc_style;
  engine->rc_style_to_style = theme_rc_style_to_style;
  engine->duplicate_style = theme_duplicate_style;
  engine->realize_style = theme_realize_style;
  engine->unrealize_style = theme_unrealize_style;
  engine->destroy_rc_style = theme_destroy_rc_style;
  engine->destroy_style = theme_destroy_style;
  engine->set_background = theme_set_background;

  rangeclass = (GtkRangeClass *)gtk_type_class(gtk_range_get_type());
  rangeclass->slider_width = 11;
  rangeclass->stepper_size = 11;
  rangeclass->min_slider_size = 15;

  radiobuttonclass = (GtkCheckButtonClass*)gtk_type_class (gtk_radio_button_get_type ());
  radiobuttonclass->indicator_size = 12;
  
  checkbuttonclass = (GtkCheckButtonClass*)gtk_type_class (gtk_check_button_get_type ());
  checkbuttonclass->indicator_size = 10;
}

void
theme_exit(void)
{
  /*
  printf("ThinIce Theme Exit\n* Need to add memory deallocation code here *\n");
  */
  /* TODO: Dealloc mem? */
}

/* The following function will be called by GTK+ when the module
 * is loaded and checks to see if we are compatible with the
 * version of GTK+ that loads us.
*/
G_MODULE_EXPORT const gchar* g_module_check_init (GModule *module);

const gchar*
g_module_check_init (GModule *module)
{
	return gtk_check_version(GTK_MAJOR_VERSION,
				 GTK_MINOR_VERSION,
				 GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}
