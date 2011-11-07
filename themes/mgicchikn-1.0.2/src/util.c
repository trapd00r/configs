/*  MagicChicken: src/util.c
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


#include "util.h"
#include "types.h"
#include "rc-style.h"


#define PIXEL_SIZE 3
#define PIXEL_SIZE_WITH_ALPHA 4

#define RED_OFFSET 0
#define GREEN_OFFSET 1
#define BLUE_OFFSET 2
#define ALPHA_OFFSET 3

/* Macro used to ensure valid values */
#define CLAMP_UCHAR(value) CLAMP(value,0,255)

/* Similar to EEL_RGB_COLOR_PACK(r,g,b) */
#define PIXEL_TO_GUINT32(pixel) \
	(((*(pixel + RED_OFFSET)) << 24) | \
	 ((*(pixel + GREEN_OFFSET)) << 16) | \
	 ((*(pixel + BLUE_OFFSET)) << 8) | \
	 (0xFF << 0))


typedef struct
{
	gint start;
	gint end;
}
ByteRange;


/* Scales or references a pixbuf to fit width/height */
GdkPixbuf *
mgicchikn_util_scale_or_ref (GdkPixbuf * src,
							 gint width,
							 gint height)
{
	if (width == gdk_pixbuf_get_width (src) && height == gdk_pixbuf_get_height (src))
	{
		gdk_pixbuf_ref (src);
		return src;
	}
	else
	{
		return gdk_pixbuf_scale_simple (src, width, height, GDK_INTERP_BILINEAR);
	}
}


/* Returns a copy of pixbuf with it's non-completely-transparent pixels to
   have an alpha level "alpha_percent" of their original value. */
GdkPixbuf *
mgicchikn_util_set_pixbuf_transparency (const GdkPixbuf * pixbuf,
										gfloat alpha_percent)
{
	GdkPixbuf *target;
	guchar *line,
	 *pixel;
	guint x,
	  y,
	  rowstride,
	  height,
	  width;

	g_return_val_if_fail (pixbuf != NULL, NULL);
	g_return_val_if_fail (GDK_IS_PIXBUF (pixbuf), NULL);

	if (alpha_percent == 1.0)
		return GDK_PIXBUF (pixbuf);

	target = gdk_pixbuf_add_alpha (pixbuf, FALSE, 0, 0, 0);

	width = gdk_pixbuf_get_width (target);
	height = gdk_pixbuf_get_height (target);
	rowstride = gdk_pixbuf_get_rowstride (target);

	line = gdk_pixbuf_get_pixels (target);

	for (y = 0; y < height; y++)
	{
		pixel = line;
		for (x = 0; x < width; x++)
		{
			pixel[ALPHA_OFFSET] = CLAMP_UCHAR (pixel[ALPHA_OFFSET] * alpha_percent);
			pixel += PIXEL_SIZE_WITH_ALPHA;
		}
		line += rowstride;
	}

	return target;
}


void
mgicchikn_util_set_pixbuf_brightness (GdkPixbuf * pixbuf,
									  gfloat level)
{
	guchar *pixel,
	 *line;
	guint x,
	  y,
	  rowstride,
	  height,
	  width,
	  bytes_per_pixel;
	gboolean has_alpha;

	g_return_if_fail (pixbuf != NULL);
	g_return_if_fail (GDK_IS_PIXBUF (pixbuf));
	g_return_if_fail (gdk_pixbuf_get_pixels (pixbuf) != NULL);

	if (level == 1.0)
		return;

	width = gdk_pixbuf_get_width (pixbuf);
	height = gdk_pixbuf_get_height (pixbuf);
	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	has_alpha = gdk_pixbuf_get_has_alpha (pixbuf);

	if (has_alpha)
		bytes_per_pixel = PIXEL_SIZE_WITH_ALPHA;
	else
		bytes_per_pixel = PIXEL_SIZE;

	line = gdk_pixbuf_get_pixels (pixbuf);

	for (y = 0; y < height; y++)
	{
		pixel = line;
		for (x = 0; x < width; x++)
		{
			pixel[RED_OFFSET] = CLAMP_UCHAR (pixel[RED_OFFSET] * level);
			pixel[GREEN_OFFSET] = CLAMP_UCHAR (pixel[GREEN_OFFSET] * level);
			pixel[BLUE_OFFSET] = CLAMP_UCHAR (pixel[BLUE_OFFSET] * level);
			pixel += bytes_per_pixel;
		}
		line += rowstride;
	}
}


MgicChiknShadowType
mgicchikn_util_get_rc_shadow_type (MgicChiknRcStyle * rc_style,
								   GtkWidget * widget,
								   GtkStateType * state,
								   GtkShadowType requested_shadow)
{
	if (rc_style == NULL || !MGICCHIKN_IS_RC_STYLE (rc_style) || widget == NULL
		|| !GTK_IS_WIDGET (widget))
		return requested_shadow;

	/* If the widget is not sensitive, let us know so we can find the shadow
	   type correctly */
	if (!GTK_WIDGET_IS_SENSITIVE (widget))
		*state = GTK_STATE_INSENSITIVE;

	if (rc_style->shadow[*state][requested_shadow] == MGICCHIKN_SHADOW_DEFAULT
		|| rc_style->shadow[*state][requested_shadow] == MGICCHIKN_SHADOW_UNSET)
		return requested_shadow;
	else
		return rc_style->shadow[*state][requested_shadow];
}


void
mgicchikn_util_get_rc_shadow_width (MgicChiknRcStyle * rc_style,
									GtkStyle * style,
									GtkWidget * widget,
									GtkStateType * state,
									GtkShadowType shadow_type,
									gint * xthickness,
									gint * ythickness)
{
	g_return_if_fail (style != NULL);
	g_return_if_fail (GTK_IS_STYLE (style));
	g_return_if_fail (xthickness != NULL);
	g_return_if_fail (ythickness != NULL);

	if (rc_style == NULL || !MGICCHIKN_IS_RC_STYLE (rc_style)
		|| widget == NULL || !GTK_IS_WIDGET (widget))
	{
		*xthickness = style->xthickness;
		*ythickness = style->ythickness;
		return;
	}

	/* If the widget is not sensitive, let us know so we can find the shadow
	   width correctly -- it's a pointer so this fix propagates back to the
	   caller. */
	if (!GTK_WIDGET_IS_SENSITIVE (widget))
		*state = GTK_STATE_INSENSITIVE;

	if (rc_style->shadow_width[*state][shadow_type] >= 0)
	{
		*xthickness = rc_style->shadow_width[*state][shadow_type];
		*ythickness = rc_style->shadow_width[*state][shadow_type];
	}
	else
	{
		*xthickness = style->xthickness;
		*ythickness = style->ythickness;
	}
}



static ByteRange *
range_new (gint start,
		   gint end)
{
	ByteRange *br = g_new (ByteRange, 1);

	br->start = start;
	br->end = end;

	return br;
}


/* I have really no idea how this function works at all.
   If you do, good for you, you're smarter than me. :-) */
PangoLayout *
mgicchikn_util_get_shadowed_pango_layout (PangoLayout * layout,
										  MgicChiknShadowType shadow)
{
	PangoLayout *target = NULL;
	GSList *embossed_ranges = NULL,
	 *stippled_ranges = NULL,
	 *tmp_list = NULL;
	PangoLayoutIter *iter;
	PangoAttrList *attrs;
	GdkBitmap *stipple = NULL;

	/* If the shadow is not special, and we have no layout, return the original layout */
	if (shadow != MGICCHIKN_SHADOW_ETCHED_IN && shadow != MGICCHIKN_SHADOW_ETCHED_OUT)
		return layout;


	iter = pango_layout_get_iter (layout);
	do
	{
		PangoLayoutRun *run;
		PangoAttribute *attr;
		gboolean need_stipple = FALSE;
		ByteRange *br;

		run = pango_layout_iter_get_run (iter);
		if (run)
		{
			tmp_list = run->item->analysis.extra_attrs;
			while (tmp_list != NULL)
			{
				attr = tmp_list->data;
				switch (attr->klass->type)
				{
				case PANGO_ATTR_FOREGROUND:
				case PANGO_ATTR_BACKGROUND:
					need_stipple = TRUE;
					break;
				default:
					break;
				}

				if (need_stipple)
					break;
				tmp_list = g_slist_next (tmp_list);
			}

			br = range_new (run->item->offset, run->item->offset + run->item->length);

			if (need_stipple)
				stippled_ranges = g_slist_prepend (stippled_ranges, br);
			else
				embossed_ranges = g_slist_prepend (embossed_ranges, br);
		}
	}
	while (pango_layout_iter_next_run (iter));

	pango_layout_iter_free (iter);

	target = pango_layout_copy (layout);

	attrs = pango_layout_get_attributes (target);
	if (attrs == NULL)
	{
		/* Create attr list if there wasn't one */
		attrs = pango_attr_list_new ();
		pango_layout_set_attributes (target, attrs);
		pango_attr_list_unref (attrs);
	}

	tmp_list = embossed_ranges;
	while (tmp_list != NULL)
	{
		PangoAttribute *attr;
		ByteRange *br = tmp_list->data;

		attr = gdk_pango_attr_embossed_new (TRUE);
		attr->start_index = br->start;
		attr->end_index = br->end;

		pango_attr_list_change (attrs, attr);
		g_free (br);

		tmp_list = g_slist_next (tmp_list);
	}

	g_slist_free (embossed_ranges);
	tmp_list = stippled_ranges;
	while (tmp_list != NULL)
	{
		PangoAttribute *attr;
		ByteRange *br = tmp_list->data;

		if (stipple == NULL)
		{
#define gray50_width 2
#define gray50_height 2
			static char gray50_bits[] = {
				0x02, 0x01
			};

			stipple = gdk_bitmap_create_from_data (NULL,
												   gray50_bits, gray50_width,
												   gray50_height);
		}

		attr = gdk_pango_attr_stipple_new (stipple);
		attr->start_index = br->start;
		attr->end_index = br->end;

		pango_attr_list_change (attrs, attr);
		g_free (br);

		tmp_list = g_slist_next (tmp_list);
	}

	g_slist_free (stippled_ranges);

	if (stipple)
		g_object_unref (G_OBJECT (stipple));

	return target;
}


void
mgicchikn_util_get_option_menu_props (GtkWidget * widget,
									  GtkRequisition * indicator_size,
									  GtkBorder * indicator_spacing)
{
	const GtkRequisition default_option_indicator_size = {
		7, 13
	};
	const GtkBorder default_option_indicator_spacing = {
		7, 5, 2, 2
	};
	GtkRequisition *tmp_size = NULL;
	GtkBorder *tmp_spacing = NULL;

	if (widget)
		gtk_widget_style_get (widget,
							  "indicator_size", &tmp_size,
							  "indicator_spacing", &tmp_spacing, NULL);
	if (tmp_size)
	{
		*indicator_size = *tmp_size;
		g_free (tmp_size);
	}
	else
		*indicator_size = default_option_indicator_size;
	if (tmp_spacing)
	{
		*indicator_spacing = *tmp_spacing;
		g_free (tmp_spacing);
	}
	else
		*indicator_spacing = default_option_indicator_spacing;
}


/* Recolors a pixbuf, replacing all black areas with the fg[state] */
GdkPixbuf *
mgicchikn_util_recolor_pixbuf (PixbufKey *key)
{
	GdkPixbuf *dest = NULL;
	guchar *pixel,
	 *line;
	guint x,
	  y,
	  rowstride,
	  height,
	  width,
	  bytes_per_pixel;
	guint32 pix_val;

	g_return_val_if_fail (key->orig_pixbuf != NULL, NULL);
	g_return_val_if_fail (GDK_IS_PIXBUF (key->orig_pixbuf), NULL);
	g_return_val_if_fail (gdk_pixbuf_get_pixels (key->orig_pixbuf) != NULL, NULL);

	dest = gdk_pixbuf_copy (key->orig_pixbuf);
	
	width = gdk_pixbuf_get_width (dest);
	height = gdk_pixbuf_get_height (dest);
	rowstride = gdk_pixbuf_get_rowstride (dest);
	line = gdk_pixbuf_get_pixels (dest);

	if (gdk_pixbuf_get_has_alpha (dest))
		bytes_per_pixel = PIXEL_SIZE_WITH_ALPHA;
	else
		bytes_per_pixel = PIXEL_SIZE;

	for (y = 0; y < height; y++)
	{
		pixel = line;

		for (x = 0; x < width; x++)
		{
			pix_val = PIXEL_TO_GUINT32 (pixel);

			switch (pix_val)
			{
				/* Black -> Text */
				case 0x000000FF:
					pixel[RED_OFFSET] = key->style->text[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->text[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->text[key->state].blue / 256;
					break;

				/* Green -> Text AA (between text/base) */
				case 0x00FF00FF:
					pixel[RED_OFFSET] = key->style->text_aa[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->text_aa[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->text_aa[key->state].blue / 256;
					break;

				/* White -> Base */
				case 0xFFFFFFFF:
					pixel[RED_OFFSET] = key->style->base[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->base[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->base[key->state].blue / 256;
					break;

				/* Red -> FG */
				case 0xFF0000FF:
					pixel[RED_OFFSET] = key->style->fg[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->fg[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->fg[key->state].blue / 256;
					break;

				/* Blue -> BG */
				case 0x0000FFFF:
					pixel[RED_OFFSET] = key->style->bg[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->bg[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->bg[key->state].blue / 256;
					break;

				/* Yellow -> Dark */
				case 0xFFFF00FF:
					pixel[RED_OFFSET] = key->style->dark[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->dark[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->dark[key->state].blue / 256;
					break;

				/* Cyan -> Mid */
				case 0x00FFFFFF:
					pixel[RED_OFFSET] = key->style->mid[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->mid[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->mid[key->state].blue / 256;
					break;

				/* Maroon -> Light */
				case 0xFF00FFFF:
					pixel[RED_OFFSET] = key->style->light[key->state].red / 256;
					pixel[GREEN_OFFSET] = key->style->light[key->state].green / 256;
					pixel[BLUE_OFFSET] = key->style->light[key->state].blue / 256;
					break;

				default:
					break;
			}

			pixel += bytes_per_pixel;
		}

		line += rowstride;
	}

	return dest;
}
