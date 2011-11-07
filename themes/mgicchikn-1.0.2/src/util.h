/*  MagicChicken: src/util.h
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


#ifndef __MGICCHIKN_THEME_UTIL_H__
#define __MGICCHIKN_THEME_UTIL_H__

#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


#include "types.h"
#include "style.h"
#include "rc-style.h"

gboolean mgicchikn_util_sanitize_size (GdkWindow * window,
									   gint * width,
									   gint * height);

GdkPixbuf *mgicchikn_util_set_pixbuf_transparency (const GdkPixbuf * pixbuf,
												   gfloat alpha_percent);
void mgicchikn_util_set_pixbuf_brightness (GdkPixbuf * pixbuf,
										   gfloat level);
GdkPixbuf *mgicchikn_util_scale_or_ref (GdkPixbuf * src,
										gint width,
										gint height);

MgicChiknShadowType mgicchikn_util_get_rc_shadow_type (MgicChiknRcStyle * rc_style,
													   GtkWidget * widget,
													   GtkStateType * state,
													   GtkShadowType requested_shadow);
void mgicchikn_util_get_rc_shadow_width (MgicChiknRcStyle * rc_style,
										 GtkStyle * style,
										 GtkWidget * widget,
										 GtkStateType * state,
										 GtkShadowType shadow_type,
										 gint * xthickness,
										 gint * ythickness);

PangoLayout *mgicchikn_util_get_shadowed_pango_layout (PangoLayout * layout,
													   MgicChiknShadowType shadow);

void mgicchikn_util_get_option_menu_props (GtkWidget * widget,
										   GtkRequisition * indicator_size,
										   GtkBorder * indicator_spacing);

GdkPixbuf *mgicchikn_util_recolor_pixbuf (PixbufKey *key);


#endif /* __MGICCHIKN_THEME_UTIL_H__ */
