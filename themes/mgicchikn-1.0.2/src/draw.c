/*  MagicChicken: src/draw.c
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


#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include <string.h>
#include <math.h>

#include "types.h"
#include "style.h"
#include "rc-style.h"
#include "draw.h"
#include "util.h"


/* ******************* *
 *  UTILITY FUNCTIONS  *
 * ******************* */


static gboolean
sanitize_size (GdkWindow * window,
			   gint * width,
			   gint * height)
{
	gboolean set_bg = FALSE;

	if ((*width == -1) && (*height == -1))
	{
		set_bg = GDK_IS_WINDOW (window);
		gdk_window_get_size (window, width, height);
	}
	else if (*width == -1)
		gdk_window_get_size (window, width, NULL);
	else if (*height == -1)
		gdk_window_get_size (window, NULL, height);

	return set_bg;
}


static gboolean
get_gcs (GtkWidget * widget,
		 GtkStyle * style,
		 GtkStateType state_type,
		 MgicChiknShadowType shadow,
		 gint xthickness,
		 gint ythickness,
		 GdkGC ** gc1,
		 GdkGC ** gc2,
		 GdkGC ** gc3,
		 GdkGC ** gc4,
		 GdkGC ** gc5,
		 GdkGC ** gc6)
{
	gboolean focused_entry = (widget
							  && (GTK_IS_ENTRY (widget) || GTK_IS_TEXT_VIEW (widget))
							  && GTK_WIDGET_HAS_FOCUS (widget));

	switch (shadow)
	{
	case GTK_SHADOW_IN:
		*gc1 = style->mid_gc[state_type];
		*gc2 = style->dark_gc[state_type];
		*gc3 = style->black_gc;

		*gc4 = style->bg_gc[state_type];
		*gc5 = style->mid_gc[state_type];
		*gc6 = style->light_gc[state_type];
		break;
	case GTK_SHADOW_OUT:
		*gc1 = style->white_gc;
		*gc2 = style->light_gc[state_type];
		*gc3 = style->bg_gc[state_type];

		*gc4 = style->mid_gc[state_type];
		*gc5 = style->dark_gc[state_type];
		*gc6 = style->black_gc;
		break;

	case GTK_SHADOW_ETCHED_IN:
		if (xthickness > 2 && ythickness > 2)
		{
			*gc1 = style->dark_gc[state_type];
			*gc2 = style->black_gc;

			*gc4 = style->dark_gc[state_type];
			*gc5 = style->black_gc;
		}
		else
		{
			*gc1 = style->mid_gc[state_type];
			*gc2 = style->dark_gc[state_type];

			*gc4 = style->mid_gc[state_type];
			*gc5 = style->dark_gc[state_type];
		}
		*gc3 = style->light_gc[state_type];

		*gc6 = style->light_gc[state_type];
		break;
	case GTK_SHADOW_ETCHED_OUT:
		*gc1 = style->light_gc[state_type];
		*gc2 = style->mid_gc[state_type];
		*gc3 = style->dark_gc[state_type];

		*gc4 = style->light_gc[state_type];
		*gc5 = style->mid_gc[state_type];
		*gc6 = style->dark_gc[state_type];
		break;

	case MGICCHIKN_SHADOW_FLAT:
		*gc1 = *gc2 = *gc3 = *gc4 = *gc5 = *gc6 = style->fg_gc[state_type];
		break;

	case MGICCHIKN_SHADOW_SHARP_IN:
		if (focused_entry)
		{
			*gc1 = *gc2 = style->base_gc[GTK_STATE_SELECTED];
			*gc3 = style->mid_gc[state_type];

			*gc4 = style->bg_gc[state_type];
			*gc5 = *gc6 = style->base_gc[GTK_STATE_SELECTED];
		}
		else
		{
			*gc1 = style->fg_gc[state_type];
			*gc2 = style->dark_gc[state_type];
			*gc3 = style->mid_gc[state_type];

			*gc4 = style->bg_gc[state_type];
			*gc5 = style->mid_gc[state_type];
			*gc6 = style->fg_gc[state_type];
		}
		break;
	case MGICCHIKN_SHADOW_SHARP_OUT:
		if (xthickness > 2 || ythickness > 2)
		{
			if (state_type == GTK_STATE_INSENSITIVE)
				*gc1 = *gc6 = style->fg_gc[state_type];
			else
				*gc1 = *gc6 = style->black_gc;
			*gc2 = style->mid_gc[state_type];
			*gc3 = style->light_gc[state_type];

			*gc4 = style->mid_gc[state_type];
			*gc5 = style->dark_gc[state_type];
		}
		else
		{
			*gc1 = *gc4 = style->bg_gc[state_type];

			if (state_type == GTK_STATE_INSENSITIVE)
				*gc2 = *gc6 = style->fg_gc[state_type];
			else
				*gc2 = *gc6 = style->black_gc;

			*gc3 = style->light_gc[state_type];
			*gc5 = style->dark_gc[state_type];
		}
		break;

	case MGICCHIKN_SHADOW_MOTIF_IN:
		*gc1 = *gc2 = *gc3 = style->dark_gc[state_type];
		*gc4 = *gc5 = *gc6 = style->light_gc[state_type];
		break;
	case MGICCHIKN_SHADOW_MOTIF_OUT:
		*gc1 = *gc2 = *gc3 = style->light_gc[state_type];
		*gc4 = *gc5 = *gc6 = style->dark_gc[state_type];
		break;

	case MGICCHIKN_SHADOW_ROUNDED_IN:
		if (state_type == GTK_STATE_INSENSITIVE)
			*gc1 = style->fg_gc[state_type];
		else
			*gc1 = style->black_gc;

		*gc2 = style->dark_gc[state_type];
		*gc3 = style->mid_gc[state_type];

		if (xthickness > 2 || ythickness > 2)
		{
			*gc4 = style->light_gc[state_type];
			*gc5 = style->mid_gc[state_type];
		}
		else
		{
			*gc4 = style->mid_gc[state_type];
			*gc5 = style->light_gc[state_type];
		}

		if (widget
			&& widget->parent
			&& widget->parent->style
			&& widget->parent->style->bg_gc[widget->parent->state])
		{
			*gc6 = widget->parent->style->bg_gc[widget->parent->state];
		}
		else
		{
			*gc6 = style->bg_gc[state_type];
		}
		break;
	case MGICCHIKN_SHADOW_ROUNDED_OUT:
		if (state_type == GTK_STATE_INSENSITIVE)
			*gc1 = style->fg_gc[state_type];
		else
			*gc1 = style->black_gc;

		if (xthickness > 2 || ythickness > 2)
		{
			*gc2 = style->mid_gc[state_type];
			*gc3 = style->light_gc[state_type];
		}
		else
		{
			*gc2 = style->light_gc[state_type];
			*gc3 = style->mid_gc[state_type];
		}

		*gc4 = style->mid_gc[state_type];
		*gc5 = style->dark_gc[state_type];

		if (widget
			&& widget->parent
			&& widget->parent->style
			&& widget->parent->style->bg_gc[widget->parent->state])
		{
			*gc6 = widget->parent->style->bg_gc[widget->parent->state];
		}
		else
		{
			*gc6 = style->bg_gc[state_type];
		}
		break;

	default:
		return TRUE;
	}

	return FALSE;
}


/* ******************* *
 *  Drawing Functions  *
 * ******************* */

GdkPixbuf *
mgicchikn_render_icon (GtkStyle * style,
					   const GtkIconSource * source,
					   GtkTextDirection direction,
					   GtkStateType state,
					   GtkIconSize size,
					   GtkWidget * widget,
					   const gchar * detail)
{
	gint width = 1;
	gint height = 1;
	GdkPixbuf *scaled,
	 *stated,
	 *base_pixbuf,
	 *tmp;

	MgicChiknRcStyle *rc_style = MGICCHIKN_RC_STYLE (style->rc_style);

	/* Oddly, style can be NULL in this function, because
	 * GtkIconSet can be used without a style and if so
	 * it uses this function.
	 */

	base_pixbuf = gtk_icon_source_get_pixbuf (source);
	g_return_val_if_fail (base_pixbuf != NULL, NULL);

	if (size != -1 && !gtk_icon_size_lookup (size, &width, &height))
	{
		g_warning (G_STRLOC ": invalid icon size `%d'", size);
		return NULL;
	}

	/* If the size was wildcarded, then scale; otherwise, leave it
	 * alone.
	 */
	if (size != -1 && gtk_icon_source_get_size_wildcarded (source))
	{
		scaled = mgicchikn_util_scale_or_ref (base_pixbuf, width, height);
	}
	else
	{
		scaled = g_object_ref (base_pixbuf);
	}

	/* If the state was wildcarded, then generate a state. */
	if (gtk_icon_source_get_state_wildcarded (source))
	{
		tmp = gdk_pixbuf_copy (scaled);

		if (rc_style->stock_image_flags[state] & MGICCHIKN_STOCK_IMAGE_SATURATION)
		{
			gdk_pixbuf_saturate_and_pixelate (scaled, tmp,
											  rc_style->
											  stock_image_saturation[state], FALSE);
		}

		if (rc_style->stock_image_flags[state] & MGICCHIKN_STOCK_IMAGE_TRANSPARENCY)
		{
			stated =
				mgicchikn_util_set_pixbuf_transparency (tmp,
														rc_style->
														stock_image_transparency[state]);
		}
		else
		{
			stated = g_object_ref (tmp);
		}

		if (rc_style->stock_image_flags[state] & MGICCHIKN_STOCK_IMAGE_BRIGHTNESS)
		{
			mgicchikn_util_set_pixbuf_brightness (stated,
												  rc_style->
												  stock_image_brightness[state]);
		}
		g_object_unref (scaled);
	}
	else
	{
		stated = scaled;
	}

	return stated;
}


void
mgicchikn_draw_hline (GtkStyle * style,
					  GdkWindow * window,
					  GtkStateType state_type,
					  GdkRectangle * area,
					  GtkWidget * widget,
					  const gchar * detail,
					  gint x1,
					  gint x2,
					  gint y)
{
	MgicChiknRcStyle *mc_rc_style;
	gint xthickness,
	  ythickness,
	  thickness_light,
	  thickness_dark,
	  i;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	if (MGICCHIKN_IS_RC_STYLE (style->rc_style))
	{
		mc_rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	}
	else
	{
		return;
	}

	mgicchikn_util_get_rc_shadow_width (mc_rc_style, style, widget, &state_type,
										GTK_SHADOW_ETCHED_IN, &xthickness, &ythickness);

	if (ythickness > 1)
	{
		thickness_light = ythickness / 2;
		thickness_dark = ythickness - thickness_light;
	}
	else
	{
		thickness_light = 0;
		thickness_dark = 1;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
	}

	if (detail && !strcmp (detail, "label"))
	{
		if (state_type == GTK_STATE_INSENSITIVE)
		{
			gdk_draw_line (window, style->white_gc, x1 + 1, y + 1, x2 + 1, y + 1);
		}
		gdk_draw_line (window, style->fg_gc[state_type], x1, y, x2, y);
	}
	else
	{
		for (i = 0; i < thickness_dark; i++)
		{
			gdk_draw_line (window, style->light_gc[state_type], x2 - i - 1,
						   y + i, x2, y + i);
			gdk_draw_line (window, style->dark_gc[state_type], x1, y + i,
						   x2 - i - 1, y + i);
		}

		y += thickness_dark;
		for (i = 0; i < thickness_light; i++)
		{
			gdk_draw_line (window, style->dark_gc[state_type], x1, y + i,
						   x1 + thickness_light - i - 1, y + i);
			gdk_draw_line (window, style->light_gc[state_type],
						   x1 + thickness_light - i - 1, y + i, x2, y + i);
		}
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
	}
}


void
mgicchikn_draw_vline (GtkStyle * style,
					  GdkWindow * window,
					  GtkStateType state_type,
					  GdkRectangle * area,
					  GtkWidget * widget,
					  const gchar * detail,
					  gint y1,
					  gint y2,
					  gint x)
{
	MgicChiknRcStyle *mc_rc_style;
	gint xthickness,
	  ythickness,
	  thickness_light,
	  thickness_dark,
	  i;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	if (MGICCHIKN_IS_RC_STYLE (style->rc_style))
	{
		mc_rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	}
	else
	{
		return;
	}

	mgicchikn_util_get_rc_shadow_width (mc_rc_style, style, widget, &state_type,
										GTK_SHADOW_ETCHED_IN, &xthickness, &ythickness);

	if (xthickness > 1)
	{
		thickness_light = xthickness / 2;
		thickness_dark = xthickness - thickness_light;
	}
	else
	{
		thickness_light = 0;
		thickness_dark = 1;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
	}

	for (i = 0; i < thickness_dark; i++)
	{
		gdk_draw_line (window, style->light_gc[state_type], x + i, y2 - i - 1, x + i, y2);
		gdk_draw_line (window, style->dark_gc[state_type], x + i, y1, x + i, y2 - i - 1);
	}

	x += thickness_dark;
	for (i = 0; i < thickness_light; i++)
	{
		gdk_draw_line (window, style->dark_gc[state_type], x + i, y1, x + i,
					   y1 + thickness_light - i);
		gdk_draw_line (window, style->light_gc[state_type], x + i,
					   y1 + thickness_light - i, x + i, y2);
	}
	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
	}
}


/* Stolen from gtkstyle.c */
static void
draw_spinbutton_shadow (GtkStyle * style,
						GdkWindow * window,
						GtkStateType state,
						GtkTextDirection direction,
						GdkRectangle * area,
						gint x,
						gint y,
						gint width,
						gint height)
{
	sanitize_size (window, &width, &height);

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->black_gc, area);
		gdk_gc_set_clip_rectangle (style->bg_gc[state], area);
		gdk_gc_set_clip_rectangle (style->dark_gc[state], area);
		gdk_gc_set_clip_rectangle (style->light_gc[state], area);
	}

	if (direction == GTK_TEXT_DIR_LTR)
	{
		gdk_draw_line (window, style->dark_gc[state], x, y, x + width - 1, y);
		gdk_draw_line (window, style->black_gc, x, y + 1, x + width - 2, y + 1);
		gdk_draw_line (window, style->black_gc,
					   x + width - 2, y + 2, x + width - 2, y + height - 3);
		gdk_draw_line (window, style->light_gc[state],
					   x + width - 1, y + 1, x + width - 1, y + height - 2);
		gdk_draw_line (window, style->light_gc[state],
					   x, y + height - 1, x + width - 1, y + height - 1);
		gdk_draw_line (window, style->bg_gc[state],
					   x, y + height - 2, x + width - 2, y + height - 2);
		gdk_draw_line (window, style->black_gc, x, y + 2, x, y + height - 3);
	}
	else
	{
		gdk_draw_line (window, style->dark_gc[state], x, y, x + width - 1, y);
		gdk_draw_line (window, style->dark_gc[state], x, y + 1, x, y + height - 1);
		gdk_draw_line (window, style->black_gc, x + 1, y + 1, x + width - 1, y + 1);
		gdk_draw_line (window, style->black_gc, x + 1, y + 2, x + 1, y + height - 2);
		gdk_draw_line (window, style->black_gc,
					   x + width - 1, y + 2, x + width - 1, y + height - 3);
		gdk_draw_line (window, style->light_gc[state],
					   x + 1, y + height - 1, x + width - 1, y + height - 1);
		gdk_draw_line (window, style->bg_gc[state],
					   x + 2, y + height - 2, x + width - 1, y + height - 2);
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->black_gc, NULL);
		gdk_gc_set_clip_rectangle (style->bg_gc[state], NULL);
		gdk_gc_set_clip_rectangle (style->dark_gc[state], NULL);
		gdk_gc_set_clip_rectangle (style->light_gc[state], NULL);
	}
}


void
mgicchikn_draw_shadow (GtkStyle * style,
					   GdkWindow * window,
					   GtkStateType state_type,
					   GtkShadowType shadow_type,
					   GdkRectangle * area,
					   GtkWidget * widget,
					   const gchar * detail,
					   gint x,
					   gint y,
					   gint width,
					   gint height)
{
	MgicChiknStyle *mc_style;
	MgicChiknRcStyle *mc_rc_style;
	MgicChiknShadowType shadow;
	GdkGC *gc1 = NULL,
	 *gc2 = NULL,
	 *gc3 = NULL,
	 *gc4 = NULL,
	 *gc5 = NULL,
	 *gc6 = NULL;
	gint xthickness,
	  ythickness;
	gboolean focused_entry;

	if (MGICCHIKN_IS_STYLE (style) && MGICCHIKN_IS_RC_STYLE (style->rc_style))
	{
		mc_style = MGICCHIKN_STYLE (style);
		mc_rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	}
	else
	{
		return;
	}

	sanitize_size (window, &width, &height);

	shadow = mgicchikn_util_get_rc_shadow_type (mc_rc_style, widget, &state_type,
												shadow_type);
	mgicchikn_util_get_rc_shadow_width (mc_rc_style, style, widget, &state_type,
										shadow_type, &xthickness, &ythickness);

	/* Special Shadows */
	if (shadow_type == GTK_SHADOW_IN)
	{
		if (detail && (strcmp (detail, "buttondefault") == 0))
		{
			if (shadow == MGICCHIKN_SHADOW_ROUNDED_IN)
			{
				gdk_draw_rectangle (window, widget->parent->style->bg_gc[state_type],
									FALSE, x, y, width - 1, height - 1);
				gdk_draw_line (window, style->black_gc, x + 4, y + height - 1,
							   x + width - 5, y + height - 1);
				gdk_draw_line (window, style->black_gc, x + width - 1, y + 4,
							   x + width - 1, y + height - 5);
				gdk_draw_point (window, style->black_gc, x + width - 3, y + height - 2);
				gdk_draw_point (window, style->black_gc, x + width - 2, y + height - 3);
			}
			else
			{
				if (area)
					gdk_gc_set_clip_rectangle (style->text_gc[state_type], area);

				gdk_draw_rectangle (window, style->text_gc[state_type], FALSE, x, y,
									width - 1, height - 1);

				if (area)
					gdk_gc_set_clip_rectangle (style->text_gc[state_type], NULL);
			}
			return;
		}
		if (detail && (strcmp (detail, "trough") == 0) && state_type == GTK_STATE_ACTIVE)
		{
			state_type = GTK_STATE_NORMAL;
		}
		else if (detail && strcmp (detail, "spinbutton") == 0)
		{
			draw_spinbutton_shadow (style, window, state_type,
									gtk_widget_get_direction (widget), area, x,
									y, width, height);
			return;
		}
	}

	focused_entry = (widget && GTK_IS_ENTRY (widget) && GTK_WIDGET_HAS_FOCUS (widget));

	if (get_gcs (widget, style, state_type, shadow, xthickness, ythickness, &gc1, &gc2,
				 &gc3, &gc4, &gc5, &gc6))
	{
		return;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, area);
		gdk_gc_set_clip_rectangle (gc2, area);
		gdk_gc_set_clip_rectangle (gc3, area);
		gdk_gc_set_clip_rectangle (gc4, area);
		gdk_gc_set_clip_rectangle (gc5, area);
		gdk_gc_set_clip_rectangle (gc6, area);
	}

	switch (shadow)
	{
	case GTK_SHADOW_NONE:
		break;

	case GTK_SHADOW_ETCHED_IN:
	case GTK_SHADOW_ETCHED_OUT:
		if (xthickness == 1)
			xthickness = 2;
		if (ythickness == 1)
			ythickness = 2;
	case GTK_SHADOW_IN:
	case GTK_SHADOW_OUT:
	case MGICCHIKN_SHADOW_FLAT:
	case MGICCHIKN_SHADOW_MOTIF_IN:
	case MGICCHIKN_SHADOW_MOTIF_OUT:
	case MGICCHIKN_SHADOW_SHARP_IN:
	case MGICCHIKN_SHADOW_SHARP_OUT:
		switch (ythickness)
		{
		case 3:
			/* Top */
			gdk_draw_line (window, gc1, x, y, x + width - 1, y);
			gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
			gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 3, y + 2);

			/* Bottom */
			gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 3,
						   y + height - 3);
			gdk_draw_line (window, gc5, x + 2, y + height - 2, x + width - 2,
						   y + height - 2);
			gdk_draw_line (window, gc6, x + 1, y + height - 1, x + width - 1,
						   y + height - 1);
			break;
		case 2:
			gdk_draw_line (window, gc2, x, y, x + width - 1, y);
			gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);

			gdk_draw_line (window, gc5, x + 2, y + height - 2, x + width - 2,
						   y + height - 2);
			gdk_draw_line (window, gc6, x + 1, y + height - 1, x + width - 1,
						   y + height - 1);
			break;
		case 1:
			gdk_draw_line (window, gc2, x, y, x + width - 1, y);

			gdk_draw_line (window, gc5, x + 1, y + height - 1, x + width - 1,
						   y + height - 1);
			break;
		default:
			break;
		}

		switch (xthickness)
		{
		case 3:
			gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
			gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 2);
			gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 3);

			gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
						   y + height - 3);
			gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
						   y + height - 2);
			gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
						   y + height - 1);
			break;
		case 2:
			gdk_draw_line (window, gc2, x, y + 1, x, y + height - 1);
			gdk_draw_line (window, gc3, x + 1, y + 2, x + 1, y + height - 2);

			gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
						   y + height - 2);
			gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
						   y + height - 1);
			break;
		case 1:
			gdk_draw_line (window, gc2, x, y + 1, x, y + height - 1);
			gdk_draw_line (window, gc5, x + width - 1, y + 1, x + width - 1,
						   y + height - 1);
			break;
		default:
			break;
		}

		if (focused_entry)
		{
			gdk_draw_rectangle (window, style->base_gc[GTK_STATE_SELECTED],
								FALSE, x, y, width - 1, height - 1);
		}
		break;

	case MGICCHIKN_SHADOW_ROUNDED_IN:
	case MGICCHIKN_SHADOW_ROUNDED_OUT:
		switch (ythickness)
		{
		case 3:
			/* Top */
			/* Black */
			gdk_draw_line (window, gc1, x + 2, y, x + width - 3, y);
			gdk_draw_point (window, gc1, x + 1, y + 1);
			gdk_draw_point (window, gc1, x + width - 2, y + 1);

			/* Mid */
			gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 3, y + 1);

			/* Light */
			gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 4, y + 2);
			gdk_draw_point (window, gc3, x + 3, y + 3);

			/* Parent BG */
			gdk_draw_point (window, gc6, x, y);
			gdk_draw_point (window, gc6, x + 1, y);
			gdk_draw_point (window, gc6, x + width - 1, y);
			gdk_draw_point (window, gc6, x + width - 2, y);

			/* Bottom */
			/* Mid */
			gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 4,
						   y + height - 3);
			gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

			/* Dark */
			gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 3,
						   y + height - 2);
			gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

			gdk_draw_point (window, gc4, x + 2, y + height - 2);

			/* Black */
			gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 3,
						   y + height - 1);
			gdk_draw_point (window, gc1, x + 1, y + height - 2);
			gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

			/* Parent BG */
			gdk_draw_point (window, gc6, x, y + height - 1);
			gdk_draw_point (window, gc6, x + 1, y + height - 1);
			gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
			gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
			break;

		case 2:
			gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);

			gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
						   y + height - 2);
		case 1:
			gdk_draw_line (window, gc1, x + 1, y, x + width - 2, y);
			gdk_draw_point (window, gc6, x, y);
			gdk_draw_point (window, gc6, x + width - 1, y);

			gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 2,
						   y + height - 1);
			gdk_draw_point (window, gc6, x, y + height - 1);
			gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
			break;
		default:
			break;
		}

		switch (xthickness)
		{
		case 3:
			/* Left */
			/* Black */
			gdk_draw_line (window, gc1, x, y + 2, x, y + height - 3);

			/* Mid */
			gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 3);

			/* Dark */
			gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 4);

			/* Parent BG */
			gdk_draw_point (window, gc6, x, y + 1);
			gdk_draw_point (window, gc6, x, y + height - 2);

			/* Right */
			/* Mid */
			gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
						   y + height - 4);

			/* Dark */
			gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
						   y + height - 3);

			gdk_draw_point (window, gc4, x + width - 2, y + 2);

			/* Black */
			gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
						   y + height - 3);

			/* Parent BG */
			gdk_draw_point (window, gc6, x + width - 1, y + 1);
			gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
			break;

		case 2:
			gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
			gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
						   y + height - 2);
		case 1:
			gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
			gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
						   y + height - 2);
			break;
		default:
			break;
		}
		break;

	default:
		return;
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, NULL);
		gdk_gc_set_clip_rectangle (gc2, NULL);
		gdk_gc_set_clip_rectangle (gc3, NULL);
		gdk_gc_set_clip_rectangle (gc4, NULL);
		gdk_gc_set_clip_rectangle (gc5, NULL);
		gdk_gc_set_clip_rectangle (gc6, NULL);
	}
}


void
mgicchikn_draw_string (GtkStyle * style,
					   GdkWindow * window,
					   GtkStateType state_type,
					   GdkRectangle * area,
					   GtkWidget * widget,
					   const gchar * detail,
					   gint x,
					   gint y,
					   const gchar * str)
{
	GdkGC *gc1 = NULL,
	 *gc2 = NULL;
	MgicChiknRcStyle *rc_style;
	MgicChiknShadowType shadow;
	gint width = -1,
	  height = -1;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	rc_style = MGICCHIKN_RC_STYLE (style->rc_style);

	sanitize_size (window, &width, &height);

	if (rc_style->font_shadow[state_type] < 0)
	{
		if (state_type == GTK_STATE_INSENSITIVE)
			shadow = MGICCHIKN_SHADOW_ETCHED_IN;
		else
			shadow = MGICCHIKN_SHADOW_NONE;
	}
	else
	{
		shadow = rc_style->font_shadow[state_type];
	}

	switch (shadow)
	{
	case MGICCHIKN_SHADOW_ETCHED_IN:
		gc1 = style->fg_gc[state_type];
		gc2 = style->light_gc[state_type];
		break;
	case MGICCHIKN_SHADOW_ETCHED_OUT:
		gc1 = style->light_gc[state_type];
		gc2 = style->fg_gc[state_type];
		break;
	default:
		gc1 = style->fg_gc[state_type];
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, area);
		gdk_gc_set_clip_rectangle (gc2, area);
	}

	switch (shadow)
	{
	case MGICCHIKN_SHADOW_IN:
	case MGICCHIKN_SHADOW_ETCHED_IN:
	case MGICCHIKN_SHADOW_OUT:
	case MGICCHIKN_SHADOW_ETCHED_OUT:
		gdk_draw_string (window, gtk_style_get_font (style), gc1, x, y, str);
		gdk_draw_string (window, gtk_style_get_font (style), gc2, x + 1, y + 1, str);
		break;

	default:
		gdk_draw_string (window, gtk_style_get_font (style), gc1, x, y, str);
		break;
	}


	switch (rc_style->font_underline[state_type])
	{
	case MGICCHIKN_UNDERLINE_DOUBLE:
		gdk_draw_line (window, gc1, x, y + height - 3, x + width - 1, y + height - 3);
	case MGICCHIKN_UNDERLINE_SINGLE:
		gdk_draw_line (window, gc1, x, y + height - 1, x + width - 1, y + height - 1);
		break;
	default:
		break;
	}


	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, NULL);
		gdk_gc_set_clip_rectangle (gc2, NULL);
	}
}


void
mgicchikn_draw_flat_box (GtkStyle * style,
						 GdkWindow * window,
						 GtkStateType state_type,
						 GtkShadowType shadow_type,
						 GdkRectangle * area,
						 GtkWidget * widget,
						 const gchar * detail,
						 gint x,
						 gint y,
						 gint width,
						 gint height)
{
	MgicChiknRcStyle *rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	MgicChiknShadowType shadow;
	GdkGC *gc1 = NULL;

	sanitize_size (window, &width, &height);

	shadow = mgicchikn_util_get_rc_shadow_type (rc_style, widget, &state_type,
												shadow_type);

	if (detail)
	{
		if (state_type == GTK_STATE_SELECTED)
		{
			if (!strcmp ("text", detail))
				gc1 = style->bg_gc[GTK_STATE_SELECTED];
			else if (!strncmp ("cell_even", detail, strlen ("cell_even")) ||
					 !strncmp ("cell_odd", detail, strlen ("cell_odd")))
			{
				gc1 = style->base_gc[state_type];
			}
			else
			{
				gc1 = style->bg_gc[state_type];
			}
		}
		else
		{
			if (strcmp ("viewportbin", detail) == 0)
			{
				gc1 = style->bg_gc[GTK_STATE_NORMAL];
			}
			else if (strcmp ("entry_bg", detail) == 0)
			{
				gc1 = style->base_gc[state_type];
			}
			/* For trees: even rows are base NORMAL, odd rows are base
			 * ACTIVE, the sort column base ACTIVE tpp.
			 * FIXME when we have style properties, clean this up.
			 */
			else if (strcmp ("cell_even", detail) == 0 ||
					 strcmp ("cell_odd", detail) == 0 ||
					 strcmp ("cell_even_ruled", detail) == 0)
			{
				gc1 = style->base_gc[state_type];
			}
			else if (strcmp ("cell_even_sorted", detail) == 0 ||
					 strcmp ("cell_odd_sorted", detail) == 0 ||
					 strcmp ("cell_odd_ruled", detail) == 0 ||
					 strcmp ("cell_even_ruled_sorted", detail) == 0)
			{
				gc1 = style->base_gc[GTK_STATE_ACTIVE];
			}
			else if (strcmp ("cell_odd_ruled_sorted", detail) == 0)
			{
				gc1 = style->base_gc[GTK_STATE_PRELIGHT];
			}
			else
			{
				gc1 = style->bg_gc[state_type];
			}
		}
	}
	else
	{
		gc1 = style->bg_gc[state_type];
	}

	if (!style->bg_pixmap[state_type] || gc1 != style->bg_gc[state_type])
	{
		if (area)
			gdk_gc_set_clip_rectangle (gc1, area);

		gdk_draw_rectangle (window, gc1, TRUE, x, y, width, height);

		if (detail && !strcmp ("tooltip", detail))
			gdk_draw_rectangle (window, style->black_gc, FALSE,
								x, y, width - 1, height - 1);

		if (area)
			gdk_gc_set_clip_rectangle (gc1, NULL);
	}
	else
	{
		gtk_style_apply_default_background (style, window,
											widget &&
											!GTK_WIDGET_NO_WINDOW (widget),
											state_type, area, x, y, width, height);
	}

	/* Necessary hack because the entry's shadow is drawn first */
	if (widget && (GTK_IS_ENTRY (widget) || GTK_IS_TEXT_VIEW (widget))
		&& shadow == MGICCHIKN_SHADOW_SHARP_IN)
	{
		if (area)
			gdk_gc_set_clip_rectangle (style->mid_gc[state_type], area);

		gdk_draw_line (window, style->mid_gc[state_type], x, y, x + width - 1, y);
		gdk_draw_line (window, style->mid_gc[state_type], x, y, x, y + height - 1);

		if (area)
			gdk_gc_set_clip_rectangle (style->mid_gc[state_type], NULL);
	}

	/* We've got a requested shadow type, so we should draw it, even though
	   this is supposed to be a a flat box -- we don't do it for GtkEntry because
	   then it'll have a double shadow, one for the actual shadow, and one for
	   the white part. We don't do it for GtkEventBox or GtkDrawingArea either,
	   because that's just silly to do it for those widgets. */
	if (shadow != MGICCHIKN_SHADOW_UNSET && shadow != MGICCHIKN_SHADOW_DEFAULT
		&& !(widget && (GTK_IS_ENTRY (widget) || GTK_IS_EVENT_BOX (widget)
						|| GTK_IS_DRAWING_AREA (widget))))
	{
		gtk_paint_shadow (style, window, state_type, shadow_type, area, widget,
						  detail, x, y, width, height);
	}
}


void
mgicchikn_draw_box (GtkStyle * style,
					GdkWindow * window,
					GtkStateType state_type,
					GtkShadowType shadow_type,
					GdkRectangle * area,
					GtkWidget * widget,
					const gchar * detail,
					gint x,
					gint y,
					gint width,
					gint height)
{
	MgicChiknRcStyle *rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	MgicChiknShadowType shadow;
	GtkRequisition indicator_size;
	GtkBorder indicator_spacing;

	sanitize_size (window, &width, &height);

	shadow = mgicchikn_util_get_rc_shadow_type (rc_style, widget, &state_type,
												shadow_type);

	if (!style->bg_pixmap[state_type] || GDK_IS_PIXMAP (window))
	{
		if (area)
			gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);

		gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE, x, y, width, height);

		if (area)
			gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	}
	else
	{
		gtk_style_apply_default_background (style, window,
											widget &&
											!GTK_WIDGET_NO_WINDOW (widget),
											state_type, area, x, y, width, height);
	}

	gtk_paint_shadow (style, window, state_type, shadow_type, area, widget,
					  detail, x, y, width, height);

	if (detail && (strcmp (detail, "optionmenu") == 0))
	{
		mgicchikn_util_get_option_menu_props (widget, &indicator_size,
											  &indicator_spacing);
		gtk_paint_vline (style, window, state_type, area, widget, detail,
						 y + style->ythickness + 1,
						 y + height - style->ythickness - 3,
						 x + width - (indicator_size.width +
									  indicator_spacing.left +
									  indicator_spacing.right) - style->xthickness);
	}

}


void
mgicchikn_draw_option (GtkStyle * style,
					   GdkWindow * window,
					   GtkStateType state_type,
					   GtkShadowType shadow_type,
					   GdkRectangle * area,
					   GtkWidget * widget,
					   const gchar * detail,
					   gint x,
					   gint y,
					   gint width,
					   gint height)
{
	if (MGICCHIKN_STYLE (style)->radio_pixbuf[state_type][shadow_type] == NULL)
	{
		MgicChiknRcStyle *rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
		MgicChiknRcStyleClass *rc_class = MGICCHIKN_RC_STYLE_GET_CLASS (style->rc_style);
		PixbufKey *key;

		key = g_new0 (PixbufKey, 1);
		key->orig_pixbuf = g_cache_insert (rc_class->raw_pixbufs,
										   rc_style->
										   radio_image[state_type][shadow_type]);
		key->style = style;
		key->state = state_type;

		MGICCHIKN_STYLE (style)->radio_pixbuf[state_type][shadow_type] =
			g_cache_insert (MGICCHIKN_STYLE_GET_CLASS (style)->pixbufs, key);
	}

	if (strcmp (detail, "option") == 0)
	{
		x -= 3;
		y -= 3;
		width += 5;
		height += 5;
	}

	gdk_pixbuf_render_to_drawable_alpha (MGICCHIKN_STYLE (style)->
										 radio_pixbuf[state_type][shadow_type],
										 window, 0, 0, x, y, width, height,
										 GDK_PIXBUF_ALPHA_FULL, 0,
										 GDK_RGB_DITHER_NORMAL, 0, 0);
}


void
mgicchikn_draw_check (GtkStyle * style,
					  GdkWindow * window,
					  GtkStateType state_type,
					  GtkShadowType shadow_type,
					  GdkRectangle * area,
					  GtkWidget * widget,
					  const gchar * detail,
					  gint x,
					  gint y,
					  gint width,
					  gint height)
{
	if (MGICCHIKN_STYLE (style)->check_pixbuf[state_type][shadow_type] == NULL)
	{
		MgicChiknRcStyle *rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
		MgicChiknRcStyleClass *rc_class = MGICCHIKN_RC_STYLE_GET_CLASS (style->rc_style);
		PixbufKey *key;

		key = g_new0 (PixbufKey, 1);
		key->orig_pixbuf = g_cache_insert (rc_class->raw_pixbufs,
										   rc_style->
										   check_image[state_type][shadow_type]);
		key->style = style;
		key->state = state_type;

		MGICCHIKN_STYLE (style)->check_pixbuf[state_type][shadow_type] =
			g_cache_insert (MGICCHIKN_STYLE_GET_CLASS (style)->pixbufs, key);
	}

	if (strcmp (detail, "check") == 0 || strcmp (detail, "cellcheck") == 0)
	{
		x -= 1;
		y -= 1;
		width = height = 13;
	}

	gdk_pixbuf_render_to_drawable_alpha (MGICCHIKN_STYLE (style)->
										 check_pixbuf[state_type][shadow_type],
										 window, 0, 0, x, y, width, height,
										 GDK_PIXBUF_ALPHA_FULL, 0,
										 GDK_RGB_DITHER_NORMAL, 0, 0);
}


void
mgicchikn_draw_shadow_gap (GtkStyle * style,
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
						   gint gap_pos,
						   gint gap_size)
{
	GdkGC *gc1 = NULL,
	 *gc2 = NULL,
	 *gc3 = NULL,
	 *gc4 = NULL,
	 *gc5 = NULL,
	 *gc6 = NULL;
	gint xthickness,
	  ythickness;
	MgicChiknShadowType shadow;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	sanitize_size (window, &width, &height);

	shadow = mgicchikn_util_get_rc_shadow_type (MGICCHIKN_RC_STYLE (style->rc_style),
												widget, &state_type, shadow_type);

	mgicchikn_util_get_rc_shadow_width (MGICCHIKN_RC_STYLE (style->rc_style),
										style, widget, &state_type,
										shadow, &xthickness, &ythickness);

	if (get_gcs (widget, style, state_type, shadow, xthickness, ythickness, &gc1, &gc2,
				 &gc3, &gc4, &gc5, &gc6))
	{
		return;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, area);
		gdk_gc_set_clip_rectangle (gc2, area);
		gdk_gc_set_clip_rectangle (gc3, area);
		gdk_gc_set_clip_rectangle (gc4, area);
		gdk_gc_set_clip_rectangle (gc5, area);
		gdk_gc_set_clip_rectangle (gc6, area);
	}

	switch (shadow)
	{
	case GTK_SHADOW_ETCHED_IN:
	case GTK_SHADOW_ETCHED_OUT:
		if (ythickness < 2)
			ythickness = 2;
		if (xthickness < 2)
			xthickness = 2;
	case GTK_SHADOW_IN:
	case GTK_SHADOW_OUT:
	case MGICCHIKN_SHADOW_FLAT:
	case MGICCHIKN_SHADOW_SHARP_IN:
	case MGICCHIKN_SHADOW_SHARP_OUT:
	case MGICCHIKN_SHADOW_MOTIF_IN:
	case MGICCHIKN_SHADOW_MOTIF_OUT:
		switch (gap_side)
		{
		case GTK_POS_TOP:
			switch (ythickness)
			{
			case 3:
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc1, x, y, x + gap_pos, y);
					gdk_draw_line (window, gc2, x + 1, y + 1, x + gap_pos + 1, y + 1);
					gdk_draw_point (window, gc2, x + gap_pos + 1, y);
					gdk_draw_line (window, gc3, x + 2, y + 2, x + gap_pos + 2, y + 2);
					gdk_draw_point (window, gc3, x + gap_pos + 2, y);
					gdk_draw_point (window, gc3, x + gap_pos + 2, y + 1);
				}
				gdk_draw_line (window, gc1, x + gap_pos + gap_size - 1, y, x + width - 1,
							   y);
				gdk_draw_line (window, gc2, x + gap_pos + gap_size, y + 1, x + width - 2,
							   y + 1);
				gdk_draw_line (window, gc3, x + gap_pos + gap_size + 1, y + 2,
							   x + width - 3, y + 2);

				gdk_draw_line (window, gc4, x + 1, y + height - 3, x + width - 2,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc2, x, y, x + gap_pos, y);
					gdk_draw_line (window, gc3, x + 1, y + 1, x + gap_pos + 1, y + 1);
					gdk_draw_point (window, gc3, x + gap_pos + 1, y);
				}
				gdk_draw_line (window, gc2, x + gap_pos + gap_size - 1, y, x + width - 1,
							   y);
				gdk_draw_line (window, gc3, x + gap_pos + gap_size, y + 1, x + width - 2,
							   y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				if (gap_pos > 0)
				{
					gdk_draw_line (window, gc2, x, y, x + gap_pos, y);
				}
				gdk_draw_line (window, gc2, x + gap_pos + gap_size - 1, y, x + width - 1,
							   y);

				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				if (gap_pos == 0)
				{
					gdk_draw_point (window, gc2, x + 1, y);
					gdk_draw_point (window, gc3, x + 2, y);
				}
				gdk_draw_line (window, gc1, x, y, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + 2, y + height - 3);

				gdk_draw_line (window, gc4, x + width - 3, y + 2, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc5, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_BOTTOM:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 3, y + 2);

				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc4, x + 2, y + height - 3, x + gap_pos - 2,
								   y + height - 3);
					gdk_draw_line (window, gc5, x + 1, y + height - 2, x + gap_pos - 1,
								   y + height - 2);
					gdk_draw_line (window, gc6, x, y + height - 1, x + gap_pos,
								   y + height - 1);
				}
				gdk_draw_line (window, gc4, x + gap_pos + gap_size - 3, y + height - 3,
							   x + width - 2, y + height - 3);
				gdk_draw_point (window, gc4, x + gap_pos + gap_size - 3, y + height - 2);
				gdk_draw_point (window, gc4, x + gap_pos + gap_size - 3, y + height - 1);

				gdk_draw_line (window, gc5, x + gap_pos + gap_size - 2, y + height - 2,
							   x + width - 2, y + height - 2);
				gdk_draw_point (window, gc5, x + gap_pos + gap_size - 2, y + height - 1);
				gdk_draw_line (window, gc6, x + gap_pos + gap_size - 1, y + height - 1,
							   x + width - 1, y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);

				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc5, x + 1, y + height - 2, gap_pos,
								   y + height - 2);
					gdk_draw_line (window, gc6, x, y + height - 1, gap_pos,
								   y + 2 + height - 1);
				}
				gdk_draw_line (window, gc5, x + gap_pos + gap_size - 2, y + height - 2,
							   x + width - 2, y + height - 2);
				gdk_draw_point (window, gc5, x + gap_pos + gap_size - 2, y + height - 1);
				gdk_draw_line (window, gc6, x + gap_pos + gap_size - 1, y + height - 1,
							   x + width - 1, y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);

				if (gap_pos > 0)
				{
					gdk_draw_line (window, gc5, x, y + height - 1, x + gap_pos,
								   y + 2 + height - 1);
				}
				gdk_draw_line (window, gc5, x + gap_pos + gap_size, y + height - 1,
							   x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 3);

				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + 2, x + 1, y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_LEFT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 3, y + 2);

				gdk_draw_line (window, gc4, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc1, x, y, x, y + gap_pos);

					gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + gap_pos + 1);
					gdk_draw_point (window, gc2, x, y + gap_pos + 1);

					gdk_draw_line (window, gc3, x + 2, y + 2, x + 2, y + gap_pos + 2);
					gdk_draw_point (window, gc3, x, y + gap_pos + 2);
					gdk_draw_point (window, gc3, x + 1, y + gap_pos + 2);
				}
				gdk_draw_line (window, gc1, x, y + gap_pos + gap_size - 1, x,
							   y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + gap_pos + gap_size, x + 1,
							   y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y + gap_pos + gap_size + 1, x + 2,
							   y + height - 3);

				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc2, x, y, x, y + gap_pos);
					gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + gap_pos + 1);
					gdk_draw_point (window, gc3, x, y + gap_pos + 1);
				}
				gdk_draw_line (window, gc2, x, y + gap_pos + gap_size - 1, x,
							   y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + gap_pos + gap_size, x + 1,
							   y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				if (gap_pos > 0)
				{
					gdk_draw_line (window, gc2, x, y, x, y + gap_pos);
				}
				gdk_draw_line (window, gc2, x, y + gap_pos + gap_size, x, y + height - 1);

				gdk_draw_line (window, gc5, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_RIGHT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 3, y + 2);

				gdk_draw_line (window, gc4, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 3);

				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc4, x + width - 3, y, x + width - 3,
								   y + gap_pos - 2);
					gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
								   y + gap_pos - 1);
					gdk_draw_line (window, gc6, x + width - 1, y + 2, x + width - 1,
								   y + gap_pos);
				}
				gdk_draw_line (window, gc4, x + width - 3, y + gap_pos + gap_size - 3,
							   x + width - 3, y + height - 3);
				gdk_draw_point (window, gc4, x + width - 2, y + gap_pos + gap_size - 3);
				gdk_draw_point (window, gc4, x + width - 1, y + gap_pos + gap_size - 3);

				gdk_draw_line (window, gc5, x + width - 2, y + gap_pos + gap_size - 2,
							   x + width - 2, y + height - 2);
				gdk_draw_point (window, gc5, x + width - 1, y + gap_pos + gap_size - 2);

				gdk_draw_line (window, gc6, x + width - 1, y + gap_pos + gap_size - 1,
							   x + width - 1, y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + height - 2);

				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc5, x + width - 2, y, x + width - 2,
								   y + gap_pos - 1);
					gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
								   y + gap_pos);
				}
				gdk_draw_line (window, gc5, x + width - 2, y + gap_pos + gap_size - 2,
							   x + width - 2, y + height - 2);
				gdk_draw_point (window, gc5, x + width - 1, y + gap_pos + gap_size - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + gap_pos + gap_size - 1,
							   x + width - 1, y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);

				if (gap_pos > 0)
				{
					gdk_draw_line (window, gc5, x + width - 1, y, x + width - 1,
								   y + gap_pos);
				}
				gdk_draw_line (window, gc5, x + width - 1, y + gap_pos + gap_size,
							   x + width - 1, y + height - 1);
				break;
			default:
				break;
			}
			break;
		}
		break;

	case MGICCHIKN_SHADOW_ROUNDED_IN:
	case MGICCHIKN_SHADOW_ROUNDED_OUT:
		switch (gap_side)
		{
		case GTK_POS_TOP:
			switch (ythickness)
			{
			case 3:
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc1, x + 2, y, x + gap_pos - 1, y);
					gdk_draw_point (window, gc1, x + 1, y + 1);

					gdk_draw_line (window, gc2, x + 2, y + 1, x + gap_pos - 1, y + 1);
					gdk_draw_point (window, gc2, x + 2, y + 2);
					gdk_draw_point (window, gc2, x + gap_pos, y);

					gdk_draw_line (window, gc3, x + 3, y + 2, x + gap_pos - 1, y + 2);
					gdk_draw_point (window, gc3, x + 3, y + 3);
					gdk_draw_point (window, gc3, x + gap_pos, y + 1);
					gdk_draw_point (window, gc3, x + gap_pos + 1, y);

					gdk_draw_point (window, gc1, x, y);
					gdk_draw_point (window, gc2, x + 1, y);
					gdk_draw_point (window, gc6, x + width - 1, y);
					gdk_draw_point (window, gc6, x + width - 2, y);
				}

				/* Top */
				/* Black */
				gdk_draw_line (window, gc1, x + gap_pos + gap_size, y, x + width - 3, y);
				gdk_draw_point (window, gc1, x + width - 2, y + 1);

				/* Mid */
				gdk_draw_line (window, gc2, x + gap_pos + gap_size, y + 1, x + width - 3,
							   y + 1);

				/* Light */
				gdk_draw_line (window, gc3, x + gap_pos + gap_size, y + 2, x + width - 4,
							   y + 2);

				/* Bottom */
				/* Mid */
				gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 4,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);
				gdk_draw_point (window, gc4, x + 2, y + height - 2);

				/* Dark */
				gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 3,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				/* Black */
				gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 3,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc2, x + 1, y + 1, x + gap_pos + 1, y + 1);
				}

				gdk_draw_line (window, gc2, x + gap_pos + gap_size - 1, y + 1,
							   x + width - 2, y + 1);
				gdk_draw_point (window, gc2, x + gap_pos + 1, y);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc1, x + 1, y, x + gap_pos, y);
				}

				gdk_draw_line (window, gc1, x + gap_pos + gap_size, y, x + width - 2, y);

				gdk_draw_point (window, gc6, x + width - 1, y);

				gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 2,
							   y + height - 1);
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				/* Left */
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc1, x, y + 2, x, y + height - 3);
					gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 3);
					gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 4);

					gdk_draw_point (window, gc1, x, y + 1);
				}
				else
				{
					gdk_draw_line (window, gc1, x, y, x, y + height - 3);
					gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 3);
					gdk_draw_line (window, gc3, x + 2, y, x + 2, y + height - 4);
				}
				gdk_draw_point (window, gc6, x, y + height - 2);

				/* Right */
				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 4);
				gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
							   y + height - 3);

				gdk_draw_point (window, gc4, x + width - 2, y + 2);
				gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
							   y + height - 3);

				gdk_draw_point (window, gc6, x + width - 1, y + 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				if (gap_pos > 2)
					gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
				else
					gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
			case 1:
				if (gap_pos > 1)
					gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
				else
					gdk_draw_line (window, gc1, x, y, x, y + height - 2);

				gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_BOTTOM:
			switch (ythickness)
			{
			case 3:
				/* Top */
				/* Black */
				gdk_draw_line (window, gc1, x + 2, y, x + width - 3, y);
				gdk_draw_point (window, gc1, x + 1, y + 1);
				gdk_draw_point (window, gc1, x + width - 2, y + 1);

				/* Mid */
				gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 3, y + 1);

				/* Light */
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 4, y + 2);
				gdk_draw_point (window, gc3, x + 3, y + 3);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + 1, y);
				gdk_draw_point (window, gc6, x + width - 1, y);
				gdk_draw_point (window, gc6, x + width - 2, y);

				/* Bottom */
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc4, x + 3, y + height - 3, x + gap_pos - 3,
								   y + height - 3);
					gdk_draw_line (window, gc5, x + 3, y + height - 2, x + gap_pos - 2,
								   y + height - 2);
					gdk_draw_line (window, gc1, x + 2, y + height - 1, x + gap_pos - 1,
								   y + height - 1);

					gdk_draw_point (window, gc1, x, y + height - 1);
					gdk_draw_point (window, gc2, x + 1, y + height - 1);
				}

				/* Mid */
				gdk_draw_line (window, gc4, x + gap_pos + gap_size, y + height - 3,
							   x + width - 4, y + height - 3);
				gdk_draw_point (window, gc4, x + gap_pos + gap_size - 1, y + height - 2);
				gdk_draw_point (window, gc4, x + gap_pos + gap_size - 2, y + height - 1);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

				/* Dark */
				gdk_draw_line (window, gc5, x + gap_pos + gap_size, y + height - 2,
							   x + width - 3, y + height - 2);
				gdk_draw_point (window, gc5, x + gap_pos + gap_size - 1, y + height - 1);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				/* Black */
				gdk_draw_line (window, gc1, x + gap_pos + gap_size, y + height - 1,
							   x + width - 3, y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);

				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc5, x + 1, y + height - 2, x + gap_pos - 2,
								   y + height - 2);
				}

				gdk_draw_line (window, gc5, x + gap_pos + gap_size, y + height - 2,
							   x + width - 2, y + height - 2);
				gdk_draw_point (window, gc5, x + gap_pos + gap_size - 1, y + height - 1);
			case 1:
				gdk_draw_line (window, gc1, x + 1, y, x + width - 2, y);
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + width - 1, y);

				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc1, x + 1, y + height - 1, x + gap_pos - 1,
								   y + height - 1);
				}

				gdk_draw_line (window, gc1, x + gap_pos + gap_size, y + height - 1,
							   x + width - 2, y + height - 1);

				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				/* Left */
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc1, x, y + 2, x, y + height - 3);
					gdk_draw_point (window, gc2, x, y + 1);
					gdk_draw_point (window, gc1, x, y + height - 2);

					gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 3);
					gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 4);
				}
				else
				{
					gdk_draw_line (window, gc1, x, y + 2, x, y + height - 1);
					gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 1);
					gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 1);
				}

				/* Right */
				/* Mid */
				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 4);
				gdk_draw_point (window, gc4, x + width - 2, y + 2);

				/* Dark */
				gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
							   y + height - 3);

				/* Black */
				gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
							   y + height - 3);

				/* Parent BG */
				gdk_draw_point (window, gc6, x + width - 1, y + 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				if (gap_pos > 2)
					gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
				else
					gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
			case 1:
				if (gap_pos > 1)
					gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
				else
					gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);

				gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_LEFT:
			switch (ythickness)
			{
			case 3:
				/* Top */
				if (gap_pos > 3)
				{
					/* Black */
					gdk_draw_line (window, gc1, x + 2, y, x + width - 3, y);
					gdk_draw_point (window, gc1, x + 1, y + 1);
					gdk_draw_point (window, gc1, x + width - 2, y + 1);
					gdk_draw_point (window, gc1, x, y);
					gdk_draw_point (window, gc1, x + 1, y);

					/* Mid */
					gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 3, y + 1);
					gdk_draw_point (window, gc2, x, y + 1);
					gdk_draw_point (window, gc2, x + 2, y + 2);

					/* Light */
					gdk_draw_line (window, gc3, x + 3, y + 2, x + width - 4, y + 2);
					gdk_draw_point (window, gc3, x + 3, y + 3);

					/* Parent BG */
					gdk_draw_point (window, gc6, x + width - 1, y);
					gdk_draw_point (window, gc6, x + width - 2, y);
				}
				else
				{
					/* Black */
					gdk_draw_line (window, gc1, x, y, x + width - 3, y);

					/* Mid */
					gdk_draw_line (window, gc2, x, y + 1, x + width - 3, y + 1);

					/* Light */
					gdk_draw_line (window, gc3, x, y + 2, x + width - 4, y + 2);
				}

				/* Bottom */
				/* Mid */
				gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 4,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

				/* Dark */
				gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 3,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				gdk_draw_point (window, gc4, x + 2, y + height - 2);

				/* Black */
				gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 3,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				}
				else
				{
					gdk_draw_line (window, gc2, x, y + 1, x + width - 2, y);
				}

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc1, x + 1, y, x + width - 2, y);
					gdk_draw_point (window, gc6, x, y);
					gdk_draw_point (window, gc6, x + width - 1, y);
				}
				else
				{
					gdk_draw_line (window, gc1, x, y, x + width - 2, y);
				}

				gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 2,
							   y + height - 1);
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				/* Left */
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc1, x, y + 2, x, y + gap_pos - 1);

					gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + gap_pos - 1);
					gdk_draw_point (window, gc2, x, y + gap_pos);

					gdk_draw_line (window, gc3, x + 2, y + 2, x + 2, y + gap_pos - 1);
					gdk_draw_point (window, gc3, x, y + gap_pos + 1);
					gdk_draw_point (window, gc3, x + 1, y + gap_pos);
				}

				/* Black */
				gdk_draw_line (window, gc1, x, y + gap_pos + gap_size, x, y + height - 3);

				/* Mid */
				gdk_draw_line (window, gc2, x + 1, y + gap_pos + gap_size + 1, x + 1,
							   y + height - 3);

				/* Dark */
				gdk_draw_line (window, gc3, x + 2, y + gap_pos + gap_size + 2, x + 2,
							   y + height - 4);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y + height - 2);

				/* Right */
				/* Mid */
				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 4);

				/* Dark */
				gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
							   y + height - 3);

				gdk_draw_point (window, gc4, x + width - 2, y + 2);

				/* Black */
				gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
							   y + height - 3);

				/* Parent BG */
				gdk_draw_point (window, gc6, x + width - 1, y + 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + gap_pos - 1);
					gdk_draw_point (window, gc2, x, y + gap_pos);
				}
				gdk_draw_line (window, gc2, x + 1, y + gap_pos + gap_size + 1, x + 1,
							   y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
			case 1:
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc1, x, y + 1, x, y + gap_pos - 1);
				}
				gdk_draw_line (window, gc1, x, y + gap_pos + gap_size, x, y + height - 2);

				gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_RIGHT:
			switch (ythickness)
			{
			case 3:
				/* Top */
				if (gap_pos > 3)
				{
					/* Black */
					gdk_draw_line (window, gc1, x + 2, y, x + width - 1, y);
					gdk_draw_point (window, gc1, x + width - 2, y + 1);

					/* Mid */
					gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 3, y + 1);

					/* Light */
					gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 4, y + 2);
				}
				else
				{
					gdk_draw_line (window, gc1, x + 2, y, x + width - 1, y);
					gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 1, y + 1);
					gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 1, y + 2);
				}
				
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + 1, y);
				gdk_draw_point (window, gc1, x + 1, y + 1);
				gdk_draw_point (window, gc2, x + 2, y + 2);
				gdk_draw_point (window, gc3, x + 3, y + 3);

				/* Bottom */
				/* Mid */
				gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 4,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

				/* Dark */
				gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 3,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				gdk_draw_point (window, gc4, x + 2, y + height - 2);

				/* Black */
				gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 3,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				if (gap_pos > 2)
					gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				else
					gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 1, y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x + 1, y, x + width - 1, y);
				gdk_draw_point (window, gc6, x, y);

				gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 2,
							   y + height - 1);
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				/* Left */
				/* Black */
				gdk_draw_line (window, gc1, x, y + 2, x, y + height - 3);

				/* Mid */
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 3);

				/* Dark */
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 4);

				/* Parent BG */
				gdk_draw_point (window, gc6, x, y + 1);
				gdk_draw_point (window, gc6, x, y + height - 2);

				/* Right */
				if (gap_pos > 3)
				{
					gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
								   y + gap_pos - 3);
					gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
								   y + gap_pos - 2);
					gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
								   y + gap_pos - 1);

					gdk_draw_point (window, gc1, x + width - 1, y);
					gdk_draw_point (window, gc2, x + width - 1, y + 1);
				}
				/* Mid */
				gdk_draw_line (window, gc4, x + width - 3, y + gap_pos + gap_size,
							   x + width - 3, y + height - 4);
				gdk_draw_point (window, gc4, x + width - 2, y + gap_pos + gap_size - 1);
				gdk_draw_point (window, gc4, x + width - 1, y + gap_pos + gap_size - 2);

				/* Dark */
				gdk_draw_line (window, gc5, x + width - 2, y + gap_pos + gap_size,
							   x + width - 2, y + height - 3);
				gdk_draw_point (window, gc5, x + width - 1, y + gap_pos + gap_size - 1);

				/* Black */
				gdk_draw_line (window, gc1, x + width - 1, y + gap_pos + gap_size,
							   x + width - 1, y + height - 3);

				/* Parent BG */
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
				
				if (gap_pos > 2)
				{
					gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
								   y + gap_pos - 2);
				}
				gdk_draw_line (window, gc5, x + width - 2, y + gap_pos + gap_size, x + width - 2,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 1, y + gap_pos + gap_size - 1);
			case 1:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
				
				if (gap_pos > 1)
				{
					gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
								   y + gap_pos - 1);
				}
				gdk_draw_line (window, gc1, x + width - 1, y + gap_pos + gap_size, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;
		}
		break;

	default:
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, NULL);
		gdk_gc_set_clip_rectangle (gc2, NULL);
		gdk_gc_set_clip_rectangle (gc3, NULL);
		gdk_gc_set_clip_rectangle (gc4, NULL);
		gdk_gc_set_clip_rectangle (gc5, NULL);
		gdk_gc_set_clip_rectangle (gc6, NULL);
	}
}


void
mgicchikn_draw_box_gap (GtkStyle * style,
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
						gint gap_pos,
						gint gap_size)
{
	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	sanitize_size (window, &width, &height);

	gtk_style_apply_default_background (style, window,
										widget && !GTK_WIDGET_NO_WINDOW (widget),
										state_type, area, x, y, width, height);

	gtk_paint_shadow_gap (style, window, state_type, shadow_type, area, widget,
						  (gchar *) detail, x, y, width, height, gap_side, gap_pos,
						  gap_size);
}


void
mgicchikn_draw_extension (GtkStyle * style,
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
						  GtkPositionType gap_side)
{
	GdkGC *gc1 = NULL,
	 *gc2 = NULL,
	 *gc3 = NULL,
	 *gc4 = NULL,
	 *gc5 = NULL,
	 *gc6 = NULL;
	gint xthickness,
	  ythickness;
	MgicChiknShadowType shadow;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	sanitize_size (window, &width, &height);

	shadow = mgicchikn_util_get_rc_shadow_type (MGICCHIKN_RC_STYLE (style->rc_style),
												widget, &state_type, shadow_type);
	mgicchikn_util_get_rc_shadow_width (MGICCHIKN_RC_STYLE (style->rc_style),
										style, widget, &state_type,
										shadow, &xthickness, &ythickness);

	gtk_style_apply_default_background (style, window,
										widget
										&& !GTK_WIDGET_NO_WINDOW (widget),
										state_type, area, x, y, width, height);

	if (get_gcs (widget, style, state_type, shadow, xthickness, ythickness, &gc1, &gc2,
				 &gc3, &gc4, &gc5, &gc6))
	{
		return;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, area);
		gdk_gc_set_clip_rectangle (gc2, area);
		gdk_gc_set_clip_rectangle (gc3, area);
		gdk_gc_set_clip_rectangle (gc4, area);
		gdk_gc_set_clip_rectangle (gc5, area);
		gdk_gc_set_clip_rectangle (gc6, area);
	}

	switch (shadow)
	{
	case GTK_SHADOW_ETCHED_IN:
	case GTK_SHADOW_ETCHED_OUT:
		if (xthickness < 2)
			xthickness = 2;
		if (ythickness < 2)
			ythickness = 2;
	case GTK_SHADOW_IN:
	case GTK_SHADOW_OUT:
	case MGICCHIKN_SHADOW_FLAT:
	case MGICCHIKN_SHADOW_SHARP_IN:
	case MGICCHIKN_SHADOW_SHARP_OUT:
	case MGICCHIKN_SHADOW_MOTIF_IN:
	case MGICCHIKN_SHADOW_MOTIF_OUT:
		switch (gap_side)
		{
		case GTK_POS_TOP:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc4, x + 2, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y, x + 2, y + height - 3);

				gdk_draw_line (window, gc4, x + width - 3, y, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y, x + 1, y + height - 2);

				gdk_draw_line (window, gc5, x + width - 2, y, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc5, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_BOTTOM:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 3, y + 2);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 2, y + 1);
				break;
			case 1:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + 2, y + height - 1);

				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + height - 1);

				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 1);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc5, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_LEFT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x, y + 1, x + width - 2, y + 1);
				gdk_draw_line (window, gc3, x, y + 2, x + width - 3, y + 2);

				gdk_draw_line (window, gc4, x, y + height - 3, x + width - 2,
							   y + height - 3);
				gdk_draw_line (window, gc5, x, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x, y + 1, x + width - 2, y + 1);

				gdk_draw_line (window, gc5, x, y + height - 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc5, x + width - 2, y + 2, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc6, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc5, x + width - 1, y, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

		case GTK_POS_RIGHT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y, x + width - 1, y);
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 1, y + 1);
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 1, y + 2);

				gdk_draw_line (window, gc4, x + 1, y + height - 3, x + width - 1,
							   y + height - 3);
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 1,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + width - 1, y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 1,
							   y + height - 2);
				gdk_draw_line (window, gc6, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x + width - 1, y);
				gdk_draw_line (window, gc5, x, y + height - 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 2);
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 3);
				break;
			case 2:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				gdk_draw_line (window, gc3, x + 1, y + 1, x + 1, y + height - 2);
				break;
			case 1:
				gdk_draw_line (window, gc2, x, y, x, y + height - 1);
				break;
			default:
				break;
			}
			break;
		}
		break;

	case MGICCHIKN_SHADOW_ROUNDED_OUT:
	case MGICCHIKN_SHADOW_ROUNDED_IN:
		switch (gap_side)
		{
			/* Extension on top */
		case GTK_POS_BOTTOM:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 4, y + 2);
				gdk_draw_point (window, gc3, x + 3, y + 3);

				/* Mid or Dark on Top */
				gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 3, y + 1);

				/* Black */
				/* Top */
				gdk_draw_line (window, gc1, x + 2, y, x + width - 3, y);
				gdk_draw_point (window, gc1, x + 1, y + 1);
				gdk_draw_point (window, gc1, x + width - 2, y + 1);

				/* Parent BG */
				/* Top */
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + 1, y);
				gdk_draw_point (window, gc6, x + width - 1, y);
				gdk_draw_point (window, gc6, x + width - 2, y);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 2, y + 1);
			case 1:
				gdk_draw_line (window, gc1, x + 1, y, x + width - 2, y);
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + width - 1, y);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				/* Left */
				gdk_draw_line (window, gc1, x, y + 2, x, y + height - 1);
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 1);
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 1);
				gdk_draw_point (window, gc6, x, y + 1);

				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 2, y + 2);
				gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
							   y + height - 2);
				gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
							   y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + 1);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 1);
				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 1);
				gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
							   y + height - 1);
				break;
			default:
				break;
			}
			break;

			/* Extension on bottom */
		case GTK_POS_TOP:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 4,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

				/* Dark or Mid on Bottom */
				gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 3,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				gdk_draw_point (window, gc4, x + 2, y + height - 2);

				/* Black */
				/* Bottom */
				gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 3,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				/* Bottom */
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 2,
							   y + height - 1);
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc3, x + 2, y, x + 2, y + height - 4);

				gdk_draw_line (window, gc4, x + width - 3, y, x + width - 3,
							   y + height - 4);

				/* Mid or Dark on Left */
				gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 3);

				/* Dark or Mid on Right */
				gdk_draw_line (window, gc5, x + width - 2, y, x + width - 2,
							   y + height - 3);

				/* Black */
				/* Left */
				gdk_draw_line (window, gc1, x, y, x, y + height - 3);
				/* Right */
				gdk_draw_line (window, gc1, x + width - 1, y, x + width - 1,
							   y + height - 3);

				/* Parent BG */
				/* Left */
				gdk_draw_point (window, gc6, x, y + height - 2);
				/* Right */
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y, x + 1, y + height - 2);
				gdk_draw_line (window, gc5, x + width - 2, y, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x, y, x, y + height - 2);
				gdk_draw_line (window, gc1, x + width - 1, y, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;

			/* Extension on right */
		case GTK_POS_LEFT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc3, x, y + 2, x + width - 4, y + 2);

				gdk_draw_line (window, gc4, x, y + height - 3, x + width - 4,
							   y + height - 3);
				gdk_draw_point (window, gc4, x + width - 4, y + height - 4);

				/* Mid or Dark on Top */
				gdk_draw_line (window, gc2, x, y + 1, x + width - 3, y + 1);

				/* Dark or Mid on Bottom */
				gdk_draw_line (window, gc5, x, y + height - 2, x + width - 3,
							   y + height - 2);
				gdk_draw_point (window, gc5, x + width - 3, y + height - 3);

				/* Black */
				/* Top */
				gdk_draw_line (window, gc1, x, y, x + width - 3, y);
				gdk_draw_point (window, gc1, x + width - 2, y + 1);
				/* Bottom */
				gdk_draw_line (window, gc1, x, y + height - 1, x + width - 3,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + width - 2, y + height - 2);

				/* Parent BG */
				/* Top */
				gdk_draw_point (window, gc6, x + width - 1, y);
				gdk_draw_point (window, gc6, x + width - 2, y);
				/* Bottom */
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				gdk_draw_point (window, gc6, x + width - 2, y + height - 1);
				break;

			case 2:
				gdk_draw_line (window, gc2, x, y + 1, x + width - 2, y + 1);

				gdk_draw_line (window, gc5, x, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x, y, x + width - 2, y);
				gdk_draw_point (window, gc6, x + width - 1, y);

				gdk_draw_line (window, gc1, x, y + height - 1, x + width - 2,
							   y + height - 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc4, x + width - 3, y + 3, x + width - 3,
							   y + height - 4);

				/* Dark or Mid on Right */
				gdk_draw_line (window, gc5, x + width - 2, y + 3, x + width - 2,
							   y + height - 3);

				gdk_draw_point (window, gc4, x + width - 2, y + 2);

				/* Black */
				/* Right */
				gdk_draw_line (window, gc1, x + width - 1, y + 2, x + width - 1,
							   y + height - 3);

				/* Parent BG */
				/* Right */
				gdk_draw_point (window, gc6, x + width - 1, y + 1);
				gdk_draw_point (window, gc6, x + width - 1, y + height - 2);
				break;

			case 2:
				gdk_draw_line (window, gc5, x + width - 2, y + 1, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x + width - 1, y + 1, x + width - 1,
							   y + height - 2);
				break;
			default:
				break;
			}
			break;

			/* Extension on left */
		case GTK_POS_RIGHT:
			switch (ythickness)
			{
			case 3:
				gdk_draw_line (window, gc3, x + 2, y + 2, x + width - 1, y + 2);
				gdk_draw_point (window, gc3, x + 3, y + 3);

				gdk_draw_line (window, gc4, x + 3, y + height - 3, x + width - 3,
							   y + height - 3);

				/* Mid or Dark on Top */
				gdk_draw_line (window, gc2, x + 2, y + 1, x + width - 1, y + 1);

				/* Dark or Mid on Bottom */
				gdk_draw_line (window, gc5, x + 3, y + height - 2, x + width - 2,
							   y + height - 2);

				gdk_draw_point (window, gc4, x + 2, y + height - 2);

				/* Black */
				/* Top */
				gdk_draw_line (window, gc1, x + 2, y, x + width - 1, y);
				gdk_draw_point (window, gc1, x + 1, y + 1);
				/* Bottom */
				gdk_draw_line (window, gc1, x + 2, y + height - 1, x + width - 1,
							   y + height - 1);
				gdk_draw_point (window, gc1, x + 1, y + height - 2);

				/* Parent BG */
				/* Top */
				gdk_draw_point (window, gc6, x, y);
				gdk_draw_point (window, gc6, x + 1, y);
				/* Bottom */
				gdk_draw_point (window, gc6, x, y + height - 1);
				gdk_draw_point (window, gc6, x + 1, y + height - 1);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + width - 1, y + 1);

				gdk_draw_line (window, gc5, x + 1, y + height - 2, x + width - 2,
							   y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x + 1, y, x + width - 1, y);
				gdk_draw_point (window, gc6, x, y);

				gdk_draw_line (window, gc1, x + 1, y + height - 1, x + width - 1,
							   y + height - 1);
				gdk_draw_point (window, gc6, x, y + height - 1);
				break;
			default:
				break;
			}

			switch (xthickness)
			{
			case 3:
				gdk_draw_line (window, gc3, x + 2, y + 3, x + 2, y + height - 4);


				/* Mid or Dark on Left */
				gdk_draw_line (window, gc2, x + 1, y + 2, x + 1, y + height - 3);

				/* Black */
				/* Left */
				gdk_draw_line (window, gc1, x, y + 2, x, y + height - 3);

				/* Parent BG */
				/* Left */
				gdk_draw_point (window, gc6, x, y + 1);
				gdk_draw_point (window, gc6, x, y + height - 2);
				break;

			case 2:
				gdk_draw_line (window, gc2, x + 1, y + 1, x + 1, y + height - 2);
			case 1:
				gdk_draw_line (window, gc1, x, y + 1, x, y + height - 2);
				break;
			default:
				break;
			}
			break;
		}
		break;

	default:
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (gc1, NULL);
		gdk_gc_set_clip_rectangle (gc2, NULL);
		gdk_gc_set_clip_rectangle (gc3, NULL);
		gdk_gc_set_clip_rectangle (gc4, NULL);
		gdk_gc_set_clip_rectangle (gc5, NULL);
		gdk_gc_set_clip_rectangle (gc6, NULL);
	}
}


void
mgicchikn_draw_focus (GtkStyle * style,
					  GdkWindow * window,
					  GtkStateType state_type,
					  GdkRectangle * area,
					  GtkWidget * widget,
					  const gchar * detail,
					  gint x,
					  gint y,
					  gint width,
					  gint height)
{
	GdkGC *gc = style->base_gc[GTK_STATE_SELECTED];
	GdkPoint points[5];
	gint line_width = 1,
	  dash_len;
	gchar *dash_list = "\1\1";
	gboolean free_dash_list = FALSE;

	sanitize_size (window, &width, &height);

	if (widget)
	{
		gtk_widget_style_get (widget,
							  "focus-line-width", &line_width,
							  "focus-line-pattern", (gchar *) & dash_list, NULL);

		free_dash_list = TRUE;
	}

	if (area)
		gdk_gc_set_clip_rectangle (gc, area);

	gdk_gc_set_line_attributes (gc, line_width,
								dash_list[0] ? GDK_LINE_ON_OFF_DASH :
								GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);

	if (detail && !strcmp (detail, "add-mode"))
	{
		if (free_dash_list)
			g_free (dash_list);

		dash_list = "\4\4";
		free_dash_list = FALSE;
	}

	points[0].x = x + line_width / 2;
	points[0].y = y + line_width / 2;
	points[1].x = x + width - line_width + line_width / 2;
	points[1].y = y + line_width / 2;
	points[2].x = x + width - line_width + line_width / 2;
	points[2].y = y + height - line_width + line_width / 2;
	points[3].x = x + line_width / 2;
	points[3].y = y + height - line_width + line_width / 2;
	points[4] = points[0];

	if (!dash_list[0])
	{
		gdk_draw_lines (window, gc, points, 5);
	}
	else
	{
		/* We go through all the pain below because the X rasterization
		 * rules don't really work right for dashed lines if you
		 * want continuity in segments that go between top/right
		 * and left/bottom. For instance, a top left corner
		 * with a 1-1 dash is drawn as:
		 *
		 *  X X X 
		 *  X
		 *
		 *  X
		 *
		 * This is because pixels on the top and left boundaries
		 * of polygons are drawn, but not on the bottom and right.
		 * So, if you have a line going up that turns the corner
		 * and goes right, there is a one pixel shift in the pattern.
		 *
		 * So, to fix this, we drawn the top and right in one call,
		 * then the left and bottom in another call, fixing up
		 * the dash offset for the second call ourselves to get
		 * continuity at the upper left.
		 *
		 * It's not perfect since we really should have a join at
		 * the upper left and lower right instead of two intersecting
		 * lines but that's only really apparent for no-dashes,
		 * which (for this reason) are done as one polygon and
		 * don't to through this code path.
		 */

		dash_len = strlen (dash_list);

		if (dash_list[0])
			gdk_gc_set_dashes (gc, 0, dash_list, dash_len);

		gdk_draw_lines (window, gc, points, 3);

		/* We draw this line one farther over than it is "supposed" to
		 * because of another rasterization problem ... if two 1 pixel
		 * unjoined lines meet at the lower right, there will be a missing
		 * pixel.
		 */
		points[2].x += 1;

		if (dash_list[0])
		{
			gint dash_pixels = 0;
			gint i;

			/* Adjust the dash offset for the bottom and left so we
			 * match up at the upper left.
			 */
			for (i = 0; i < dash_len; i++)
				dash_pixels += dash_list[i];

			if (dash_len % 2 == 1)
				dash_pixels *= 2;

			gdk_gc_set_dashes (gc,
							   dash_pixels - (width + height -
											  2 * line_width) % dash_pixels,
							   dash_list, dash_len);
		}

		gdk_draw_lines (window, gc, points + 2, 3);
	}

	gdk_gc_set_line_attributes (gc, 0, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);

	if (area)
		gdk_gc_set_clip_rectangle (gc, NULL);

	if (free_dash_list)
		g_free (dash_list);
}


void
mgicchikn_draw_handle (GtkStyle * style,
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
					   GtkOrientation orientation)
{
	MgicChiknRcStyle *mc_rc_style = MGICCHIKN_RC_STYLE (style->rc_style);
	MgicChiknShadowType shadow;
	gint x,
	  y,
	  width,
	  height,
	  xthickness,
	  ythickness;
	GdkGC *top_gc = NULL,
	 *bottom_gc = NULL,
	 *mid_gc = NULL;

	g_return_if_fail (style != NULL);
	g_return_if_fail (window != NULL);

	sanitize_size (window, &req_width, &req_height);

	gtk_paint_box (style, window, state_type, shadow_type, area, widget, detail,
				   req_x, req_y, req_width, req_height);

	shadow = mgicchikn_util_get_rc_shadow_type (mc_rc_style, widget,
												&state_type, shadow_type);

	if (shadow != GTK_SHADOW_NONE)
	{
		mgicchikn_util_get_rc_shadow_width (mc_rc_style, style, widget,
											&state_type, shadow_type,
											&xthickness, &ythickness);
	}
	else
	{
		xthickness = 0;
		ythickness = 0;
	}

	if (orientation == GTK_ORIENTATION_HORIZONTAL)
	{
		width =
			CLAMP ((mc_rc_style->grippy_size[state_type][shadow] * req_width),
				   2, req_width);
		height = req_height;
	}
	else
	{
		height =
			CLAMP ((mc_rc_style->grippy_size[state_type][shadow] * req_height),
				   2, req_height);
		width = req_width;
	}

	width -= xthickness * 2;
	height -= ythickness * 2;

	if (width < 2 || height < 2)
		return;

	/* Center the starting point based on the requested size. */
	req_x += (gint) rint ((req_width - width) / 2.0);
	req_y += (gint) rint ((req_height - height) / 2.0);

	/* Hack to make paned's not look like ass */
	if (detail && (strcmp (detail, "paned") == 0))
	{
		if (orientation == GTK_ORIENTATION_HORIZONTAL)
		{
			height -= 4;
			req_y += 2;
		}
		else
		{
			width -= 4;
			req_x += 2;
		}
	}

	switch (mc_rc_style->grippy_style[state_type][shadow])
	{
	case MGICCHIKN_GRIPPY_NONE:
		return;
		break;
	case MGICCHIKN_GRIPPY_UNSET:
	case MGICCHIKN_GRIPPY_DOTS_IN:
	case MGICCHIKN_GRIPPY_LINES_IN:
		top_gc = style->dark_gc[state_type];
		bottom_gc = style->light_gc[state_type];
		break;
	case MGICCHIKN_GRIPPY_DOTS_OUT:
	case MGICCHIKN_GRIPPY_LINES_OUT:
		top_gc = style->light_gc[state_type];
		bottom_gc = style->dark_gc[state_type];
		break;
	default:
		return;
		break;
	}

	mid_gc = style->mid_gc[state_type];

	if (area)
	{
		gdk_gc_set_clip_rectangle (top_gc, area);
		gdk_gc_set_clip_rectangle (mid_gc, area);
		gdk_gc_set_clip_rectangle (bottom_gc, area);
	}

	switch (mc_rc_style->grippy_style[state_type][shadow])
	{
	case MGICCHIKN_GRIPPY_NONE:
		return;
		break;
	case MGICCHIKN_GRIPPY_UNSET:
	case MGICCHIKN_GRIPPY_DOTS_IN:
	case MGICCHIKN_GRIPPY_DOTS_OUT:
		for (y = req_y; y < req_y + height; y += 3)
		{
			for (x = req_x; x < req_x + width; x += 3)
			{
				gdk_draw_point (window, top_gc, x, y);
				gdk_draw_point (window, mid_gc, x + 1, y);
				gdk_draw_point (window, mid_gc, x, y + 1);
				gdk_draw_point (window, bottom_gc, x + 1, y + 1);
			}
		}
		break;
	case MGICCHIKN_GRIPPY_LINES_IN:
	case MGICCHIKN_GRIPPY_LINES_OUT:
		if (orientation == GTK_ORIENTATION_HORIZONTAL)
		{
			for (y = req_y; y < req_y + height; y += 3)
			{
				gdk_draw_line (window, top_gc, req_x, y, req_x + width, y);
				gdk_draw_line (window, bottom_gc, req_x, y + 1, req_x + width, y + 1);
				gdk_draw_point (window, mid_gc, req_x, y);
				gdk_draw_point (window, mid_gc, req_x + width, y + 1);
			}
		}
		else
		{
			for (x = req_x; x < req_x + width; x += 3)
			{
				gdk_draw_line (window, top_gc, x, req_y, x, req_y + height);
				gdk_draw_line (window, bottom_gc, x + 1, req_y, x + 1, req_y + height);
				gdk_draw_point (window, mid_gc, x + 1, req_y);
				gdk_draw_point (window, mid_gc, x, req_y + height);
			}
		}
		break;
	default:
		return;
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (top_gc, NULL);
		gdk_gc_set_clip_rectangle (mid_gc, NULL);
		gdk_gc_set_clip_rectangle (bottom_gc, NULL);
	}
}


void
mgicchikn_draw_layout (GtkStyle * style,
					   GdkWindow * window,
					   GtkStateType state_type,
					   gboolean use_text,
					   GdkRectangle * area,
					   GtkWidget * widget,
					   const gchar * detail,
					   gint x,
					   gint y,
					   PangoLayout * layout)
{
	GdkGC *gc;
	PangoLayout *tmp_layout,
	 *target_layout;
	PangoAttribute *attr;
	PangoAttrList *attrs;
	MgicChiknRcStyle *rc_style;

	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	gc = use_text ? style->text_gc[state_type] : style->fg_gc[state_type];

	rc_style = MGICCHIKN_RC_STYLE (style->rc_style);

	tmp_layout =
		mgicchikn_util_get_shadowed_pango_layout (layout,
												  rc_style->font_shadow[state_type]);

	switch (rc_style->font_underline[state_type])
	{
	case MGICCHIKN_UNDERLINE_UNSET:
	case MGICCHIKN_UNDERLINE_NONE:
		target_layout = tmp_layout;
		break;

	default:
		target_layout = pango_layout_copy (tmp_layout);

		if (tmp_layout != layout)
			g_object_unref (tmp_layout);

		attrs = pango_layout_get_attributes (target_layout);
		if (attrs == NULL)
		{
			/* Create attr list if there wasn't one */
			attrs = pango_attr_list_new ();
			pango_layout_set_attributes (target_layout, attrs);
			pango_attr_list_unref (attrs);
		}

		attr = pango_attr_underline_new (rc_style->font_underline[state_type]);
		attr->start_index = 0;
		attr->end_index = G_MAXINT;
		pango_attr_list_change (attrs, attr);

		break;
	}

	if (area)
		gdk_gc_set_clip_rectangle (gc, area);

	gdk_draw_layout (window, gc, x, y, target_layout);

	if (area)
		gdk_gc_set_clip_rectangle (gc, NULL);

	if (target_layout != layout)
		g_object_unref (target_layout);
}


void
mgicchikn_draw_resize_grip (GtkStyle * style,
							GdkWindow * window,
							GtkStateType state_type,
							GdkRectangle * area,
							GtkWidget * widget,
							const gchar * detail,
							GdkWindowEdge edge,
							gint x,
							gint y,
							gint width,
							gint height)
{

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
		gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
	}

	/* make it square, aligning to bottom right */
	if (width < height)
	{
		y += (height - width);
		height = width;
	}
	else if (height < width)
	{
		x += (width - height);
		width = height;
	}

	/* Clear background */
	gtk_style_apply_default_background (style, window, FALSE,
										state_type, area, x, y, width, height);

	switch (edge)
	{
	case GDK_WINDOW_EDGE_SOUTH_EAST:
		{
			gint xi,
			  yi;

			xi = x;
			yi = y;

			while (xi < (x + width - 3))
			{
				gdk_draw_line (window,
							   style->light_gc[state_type], xi, y + height, x + width,
							   yi);

				++xi;
				++yi;

				gdk_draw_line (window,
							   style->dark_gc[state_type], xi, y + height, x + width, yi);

				++xi;
				++yi;

				gdk_draw_line (window,
							   style->dark_gc[state_type], xi, y + height, x + width, yi);

				xi += 3;
				yi += 3;
			}
		}
		break;
	default:
		g_assert_not_reached ();
		break;
	}

	if (area)
	{
		gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
		gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
		gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
	}
}


void
mgicchikn_draw_slider (GtkStyle * style,
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
					   GtkOrientation orientation)
{
	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (window != NULL);

	sanitize_size (window, &width, &height);

	gtk_paint_box (style, window, state_type, shadow_type,
				   area, widget, detail, x, y, width, height);

	if (detail && (strcmp ("hscale", detail) == 0 || strcmp ("vscale", detail) == 0))
	{
		if (orientation == GTK_ORIENTATION_HORIZONTAL)
			gtk_paint_vline (style, window, state_type, area, widget, detail,
							 y + style->ythickness,
							 y + height - style->ythickness - 1, x + width / 2);
		else
			gtk_paint_hline (style, window, state_type, area, widget, detail,
							 x + style->xthickness,
							 x + width - style->xthickness - 1, y + height / 2);
	}
}
