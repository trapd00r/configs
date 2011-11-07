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

#include <gmodule.h>
#include "xfce_rc_style.h"
#include "xfce_style.h"

#define SCROLLBAR_WIDTH 15

static gint range_slider_width;
static gint range_min_slider_size;
static gint range_stepper_size;
static gint range_stepper_slider_spacing;


G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
  xfce_rc_style_register_type (module);
  xfce_style_register_type (module);
}

G_MODULE_EXPORT void
theme_exit (void)
{
}

G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
  void *ptr;
  ptr = GTK_RC_STYLE (g_object_new (XFCE_TYPE_RC_STYLE, NULL));  
  return (GtkRcStyle *)ptr;
}
