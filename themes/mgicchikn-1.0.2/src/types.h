/*  MagicChicken: src/types.h
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


#ifndef __MGICCHIKN_THEME_TYPES_H__
#define __MGICCHIKN_THEME_TYPES_H__


#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <pango/pango-attributes.h>
#include <gtk/gtk.h>


typedef enum
{
	MGICCHIKN_STOCK_IMAGE_NONE = 0,
	MGICCHIKN_STOCK_IMAGE_SATURATION = 1 << 0,
	MGICCHIKN_STOCK_IMAGE_TRANSPARENCY = 1 << 1,
	MGICCHIKN_STOCK_IMAGE_BRIGHTNESS = 1 << 2
}
MgicChiknStockImageFlags;

typedef enum
{
	MGICCHIKN_UNDERLINE_NONE = PANGO_UNDERLINE_NONE,
	MGICCHIKN_UNDERLINE_SINGLE = PANGO_UNDERLINE_SINGLE,
	MGICCHIKN_UNDERLINE_DOUBLE = PANGO_UNDERLINE_DOUBLE,
	MGICCHIKN_UNDERLINE_UNSET
}
MgicChiknUnderlineStyle;


typedef enum
{
	MGICCHIKN_STATE_NORMAL = GTK_STATE_NORMAL,
	MGICCHIKN_STATE_PRELIGHT = GTK_STATE_PRELIGHT,
	MGICCHIKN_STATE_ACTIVE = GTK_STATE_ACTIVE,
	MGICCHIKN_STATE_SELECTED = GTK_STATE_SELECTED,
	MGICCHIKN_STATE_INSENSITIVE = GTK_STATE_INSENSITIVE,
	MGICCHIKN_STATE_DEFAULT
}
MgicChiknStateType;


typedef enum
{
	MGICCHIKN_SHADOW_NONE = GTK_SHADOW_NONE,
	MGICCHIKN_SHADOW_IN = GTK_SHADOW_IN,
	MGICCHIKN_SHADOW_OUT = GTK_SHADOW_OUT,
	MGICCHIKN_SHADOW_ETCHED_IN = GTK_SHADOW_ETCHED_IN,
	MGICCHIKN_SHADOW_ETCHED_OUT = GTK_SHADOW_ETCHED_OUT,

	MGICCHIKN_SHADOW_FLAT,

	MGICCHIKN_SHADOW_SHARP_IN,
	MGICCHIKN_SHADOW_SHARP_OUT,

	MGICCHIKN_SHADOW_ROUNDED_IN,
	MGICCHIKN_SHADOW_ROUNDED_OUT,

	MGICCHIKN_SHADOW_MOTIF_IN,
	MGICCHIKN_SHADOW_MOTIF_OUT,

	MGICCHIKN_SHADOW_UNSET,
	MGICCHIKN_SHADOW_DEFAULT,
	MGICCHIKN_SHADOW_LAST
}
MgicChiknShadowType;


typedef enum
{
	MGICCHIKN_GRIPPY_NONE,
	MGICCHIKN_GRIPPY_DOTS_IN,
	MGICCHIKN_GRIPPY_DOTS_OUT,
	MGICCHIKN_GRIPPY_LINES_IN,
	MGICCHIKN_GRIPPY_LINES_OUT,
	MGICCHIKN_GRIPPY_UNSET
}
MgicChiknGrippyStyle;


typedef struct
{
	GdkPixbuf *orig_pixbuf;

	GtkStyle *style;

	GtkStateType state:3;
}
PixbufKey;


#endif /* __MGICCHIKN_THEME_TYPES_H__ */
