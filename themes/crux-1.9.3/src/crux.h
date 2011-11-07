#ifndef CRUX_THEME_H
#define CRUX_THEME_H

#include <glib.h>
#include <gmodule.h>
#include <gtk/gtkrc.h>

G_BEGIN_DECLS

G_MODULE_EXPORT void theme_init (GTypeModule *module);
G_MODULE_EXPORT void theme_exit (void);

G_MODULE_EXPORT GtkRcStyle *theme_create_rc_style (void);

G_MODULE_EXPORT const gchar* g_module_check_init (GModule *module);
    
G_END_DECLS

#endif
