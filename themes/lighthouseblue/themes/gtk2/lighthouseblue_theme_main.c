#include <gmodule.h>
#include <gtk/gtk.h>

#include "lighthouseblue_rc_style.h"
#include "lighthouseblue_style.h"

/* 
 * Called by GTK+ after this module
 * is loaded to let us setup anything we need to
 */
G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
  lighthouseblue_rc_style_register_type (module);
  lighthouseblue_style_register_type (module);
}

/* 
 * Called before GTK+ unloads this module
 * to let us do any neccesary clean up
 */
G_MODULE_EXPORT void
theme_exit (void)
{}

/* 
 * Creates a GtkRcStyle object that holds
 * our style definitions
 */
G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
  void *ptr;
  
  ptr = GTK_RC_STYLE (g_object_new (LIGHTHOUSEBLUE_TYPE_RC_STYLE, NULL));  
  return (GtkRcStyle *)ptr;
}

/* 
 * Called by GTK+ when the module
 * is loaded to check if we are compatible with the
 * version of GTK+ that loads us.
 *
G_MODULE_EXPORT const gchar*
g_module_check_init (GModule *module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}*/
