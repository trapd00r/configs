/* gtk-flat-theme - A gtk+ theme engine.
   Copyright (C) 2000  Mark Slicker <jamess1@wwnet.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkrc.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtkcheckbutton.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>

typedef struct _FlatRcStyle FlatRcStyle;
typedef struct _FlatRcStyleClass FlatRcStyleClass;

extern GType flat_type_rc_style;

#define FLAT_TYPE_RC_STYLE              flat_type_rc_style
#define FLAT_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FLAT_TYPE_RC_STYLE, FlatRcStyle))
#define FLAT_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FLAT_TYPE_RC_STYLE, FlatRcStyleClass))
#define FLAT_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FLAT_TYPE_RC_STYLE))
#define FLAT_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FLAT_TYPE_RC_STYLE))
#define FLAT_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FLAT_TYPE_RC_STYLE, FlatRcStyleClass))

struct _FlatRcStyle
{
  GtkRcStyle parent_instance;
};

struct _FlatRcStyleClass
{
  GtkRcStyleClass parent_class;
};

void flat_rc_style_register_type (GTypeModule *module);
