/*  MagicChicken: src/draw.h
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


#ifndef __MGICCHIKN_THEME_DRAW_H__
#define __MGICCHIKN_THEME_DRAW_H__


#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


GdkPixbuf *mgicchikn_render_icon (GtkStyle * style,
								  const GtkIconSource * source,
								  GtkTextDirection direction,
								  GtkStateType state,
								  GtkIconSize size,
								  GtkWidget * widget,
								  const gchar * detail);
void mgicchikn_draw_shadow (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GtkShadowType shadow_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint x,
							gint y,
							gint width,
							gint height);
void mgicchikn_draw_string (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint x,
							gint y,
							const gchar * string);
void mgicchikn_draw_hline (GtkStyle * style,
						   GdkWindow * window,
						   GtkStateType state_type,
						   GdkRectangle * area,
						   GtkWidget * widget,
						   const gchar * detail,
						   gint x1,
						   gint x2,
						   gint y);
void mgicchikn_draw_vline (GtkStyle * style,
						   GdkWindow * window,
						   GtkStateType state_type,
						   GdkRectangle * area,
						   GtkWidget * widget,
						   const gchar * detail,
						   gint y1,
						   gint y2,
						   gint x);
void mgicchikn_draw_flat_box (GtkStyle * style,
							  GdkWindow * window,
							  GtkStateType state_type,
							  GtkShadowType shadow_type,
							  GdkRectangle * area,
							  GtkWidget * widget,
							  const gchar * detail,
							  gint x,
							  gint y,
							  gint width,
							  gint height);
void mgicchikn_draw_box (GtkStyle * style,
						 GdkWindow * window,
						 GtkStateType state_type,
						 GtkShadowType shadow_type,
						 GdkRectangle * area,
						 GtkWidget * widget,
						 const gchar * detail,
						 gint x,
						 gint y,
						 gint width,
						 gint height);
void mgicchikn_draw_option (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GtkShadowType shadow_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint x,
							gint y,
							gint width,
							gint height);
void mgicchikn_draw_check (GtkStyle * style,
						   GdkWindow * window,
						   GtkStateType state_type,
						   GtkShadowType shadow_type,
						   GdkRectangle * area,
						   GtkWidget * widget,
						   const gchar * detail,
						   gint x,
						   gint y,
						   gint width,
						   gint height);
void mgicchikn_draw_shadow_gap (GtkStyle * style,
								GdkWindow * window,
								GtkStateType state_type,
								GtkShadowType shadow_type,
								GdkRectangle * area,
								GtkWidget * widget,
								const gchar * detail,
								gint x,
								gint y,
								gint width,
								gint height,
								GtkPositionType gap_side,
								gint gap_x,
								gint gap_width);
void mgicchikn_draw_box_gap (GtkStyle * style,
							 GdkWindow * window,
							 GtkStateType state_type,
							 GtkShadowType shadow_type,
							 GdkRectangle * area,
							 GtkWidget * widget,
							 const gchar * detail,
							 gint x,
							 gint y,
							 gint width,
							 gint height,
							 GtkPositionType gap_side,
							 gint gap_x,
							 gint gap_width);
void mgicchikn_draw_extension (GtkStyle * style,
							   GdkWindow * window,
							   GtkStateType state_type,
							   GtkShadowType shadow_type,
							   GdkRectangle * area,
							   GtkWidget * widget,
							   const gchar * detail,
							   gint x,
							   gint y,
							   gint width,
							   gint height,
							   GtkPositionType gap_side);
void mgicchikn_draw_focus (GtkStyle * style,
						   GdkWindow * window,
						   GtkStateType state_type,
						   GdkRectangle * area,
						   GtkWidget * widget,
						   const gchar * detail,
						   gint x,
						   gint y,
						   gint width,
						   gint height);
void mgicchikn_draw_handle (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GtkShadowType shadow_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint req_x,
							gint req_y,
							gint req_width,
							gint req_height,
							GtkOrientation orientation);
void mgicchikn_draw_slider (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GtkShadowType shadow_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint x,
							gint y,
							gint width,
							gint height,
							GtkOrientation orientation);
void mgicchikn_draw_layout (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							gboolean use_text,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							gint x,
							gint y,
							PangoLayout * layout);
void mgicchikn_draw_resize_grip (GtkStyle * style,
								 GdkWindow * window,
								 GtkStateType state_type,
								 GdkRectangle * area,
								 GtkWidget * widget,
								 const gchar * detail,
								 GdkWindowEdge edge,
								 gint x,
								 gint y,
								 gint width,
								 gint height);

#endif /* __MGICCHIKN_THEME_DRAW_H__ */
