/*  MagicChicken: src/main.c
 *
 *  Copyright 2001 (c) James M. Cape <jcape@ignore.your.tv>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gmodule.h>
#include <glib-object.h>
#include <gtk/gtk.h>


#include "style.h"
#include "rc-style.h"


G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
	mgicchikn_rc_style_register_type (module);
	mgicchikn_style_register_type (module);
}


G_MODULE_EXPORT void
theme_exit (void)
{
}


G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
	return GTK_RC_STYLE (g_object_new (MGICCHIKN_TYPE_RC_STYLE, NULL));
}


G_MODULE_EXPORT const gchar *g_module_check_init (GModule * module);
const gchar *
g_module_check_init (GModule * module)
{
	return gtk_check_version (GTK_MAJOR_VERSION,
							  GTK_MINOR_VERSION,
							  GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}
