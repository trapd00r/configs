/*  MagicChicken: src/style.h
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


#ifndef __MGICCHIKN_THEME_STYLE_H__
#define __MGICCHIKN_THEME_STYLE_H__


#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "types.h"


extern GType mgicchikn_style_type;

#define MGICCHIKN_TYPE_STYLE			(mgicchikn_style_type)
#define MGICCHIKN_STYLE(object)			(G_TYPE_CHECK_INSTANCE_CAST((object), MGICCHIKN_TYPE_STYLE, MgicChiknStyle))
#define MGICCHIKN_STYLE_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), MGICCHIKN_TYPE_STYLE, MgicChiknStyleClass))
#define MGICCHIKN_IS_STYLE(object)		(G_TYPE_CHECK_INSTANCE_TYPE((object), MGICCHIKN_TYPE_STYLE))
#define MGICCHIKN_IS_STYLE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), MGICCHIKN_TYPE_STYLE))
#define MGICCHIKN_STYLE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), MGICCHIKN_TYPE_STYLE, MgicChiknStyleClass))


typedef struct _MgicChiknStyle MgicChiknStyle;
typedef struct _MgicChiknStyleClass MgicChiknStyleClass;


struct _MgicChiknStyle
{
	GtkStyle parent;

	GdkPixbuf *check_pixbuf[5][MGICCHIKN_SHADOW_LAST];
	GdkPixbuf *radio_pixbuf[5][MGICCHIKN_SHADOW_LAST];
};

struct _MgicChiknStyleClass
{
	GtkStyleClass parent_class;

	GCache *pixbufs;
};


void mgicchikn_style_register_type (GTypeModule *module);


#endif /* __MGICCHIKN_THEME_RC_STYLE_H__ */
