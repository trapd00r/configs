#include <crux.h>

#include <gtk/gtk.h>
#include <gmodule.h>
#include <stdio.h>

#include "crux-rc-style.h"
#include "crux-rc-parser.h"
#include "crux-style.h"
#include "crux-draw.h"

#include "debug.h"


G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
  GtkRangeClass *rangeclass;
  GtkScaleClass *scaleclass;
  GtkCheckButtonClass *checkclass;

  /*make_warnings_and_criticals_stop_in_debugger ();*/
  
  crux_rc_style_register_type (module);
  crux_style_register_type (module);
  crux_rc_parser_init_gradients();
}
    
G_MODULE_EXPORT void
theme_exit(void)
{
  uninstall_all_focus_hooks();
}
    
G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
  return GTK_RC_STYLE (g_object_new (CRUX_TYPE_RC_STYLE, NULL));
}

const gchar*
g_module_check_init (GModule *module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}

