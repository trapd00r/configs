/*  MagicChicken: src/rc-style.h
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


#ifndef __MGICCHIKN_THEME_RC_STYLE_H__
#define __MGICCHIKN_THEME_RC_STYLE_H__


#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


#include "types.h"

extern GType mgicchikn_rc_style_type;

#define MGICCHIKN_TYPE_RC_STYLE				(mgicchikn_rc_style_type)
#define MGICCHIKN_RC_STYLE(object)			(G_TYPE_CHECK_INSTANCE_CAST((object), MGICCHIKN_TYPE_RC_STYLE, MgicChiknRcStyle))
#define MGICCHIKN_RC_STYLE_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST((klass), MGICCHIKN_TYPE_RC_STYLE, MgicChiknRcStyleClass))
#define MGICCHIKN_IS_RC_STYLE(object)		(G_TYPE_CHECK_INSTANCE_TYPE((object), MGICCHIKN_TYPE_RC_STYLE))
#define MGICCHIKN_IS_RC_STYLE_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), MGICCHIKN_TYPE_RC_STYLE))
#define MGICCHIKN_RC_STYLE_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), MGICCHIKN_TYPE_RC_STYLE, MgicChiknRcStyleClass))


typedef struct _MgicChiknRcStyle MgicChiknRcStyle;
typedef struct _MgicChiknRcStyleClass MgicChiknRcStyleClass;


struct _MgicChiknRcStyle
{
	GtkRcStyle parent;

	MgicChiknStockImageFlags stock_image_flags[5];
	gfloat stock_image_transparency[5];
	gfloat stock_image_saturation[5];
	gfloat stock_image_brightness[5];

	/* [<state>][<shadow_type>] */
	/* Shadows & their widths */
	MgicChiknShadowType shadow[5][MGICCHIKN_SHADOW_LAST];
	gint8 shadow_width[5][MGICCHIKN_SHADOW_LAST];

	/* Fonts */
	MgicChiknShadowType font_shadow[5];
	MgicChiknUnderlineStyle font_underline[5];

	/* Grippy style */
	MgicChiknGrippyStyle grippy_style[5][MGICCHIKN_SHADOW_LAST];
	/* Percentage of the available room the grippy will use */
	gfloat grippy_size[5][MGICCHIKN_SHADOW_LAST];

	/* Check/radio filenames */
	gchar *check_image[5][MGICCHIKN_SHADOW_LAST];
	gchar *radio_image[5][MGICCHIKN_SHADOW_LAST];
};

struct _MgicChiknRcStyleClass
{
	GtkRcStyleClass parent_class;

	GCache *raw_pixbufs;
};


void mgicchikn_rc_style_register_type (GTypeModule * module);

#endif /* __MGICCHIKN_THEME_RC_STYLE_H__ */
