/* eazel-theme-gradient.c -- code for drawing gradients

   Copyright (C) 2000 Eazel, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   $Id: crux-gradient.c,v 1.4 2002/02/09 09:52:44 seth Exp $

   Authors: John Harper <jsh@eazel.com>  */

/* AIX requires this to be the first thing in the file.  */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifndef __GNUC__
# if HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifdef _AIX
 #pragma alloca
#  else
#   ifndef alloca /* predefined by HP cc +Olibcalls */
   char *alloca ();
#   endif
#  endif
# endif
#endif

#include "crux-gradient.h"
#include <gdk/gdkrgb.h>
#include <stdlib.h>
#include <stdio.h>

static GdkRgbDither dither_mode = GDK_RGB_DITHER_MAX;

eazel_engine_gradient *
eazel_engine_gradient_new (eazel_engine_gradient_direction direction,
			   GdkColor *from, GSList *components)
{
    eazel_engine_gradient *g;

    g_return_val_if_fail (from != NULL, NULL);

    g = g_new (eazel_engine_gradient, 1);

    g->refcount = 1;
    g->direction = direction;
    g->from = *from;
    g->components = components;
    return g;
}

eazel_engine_gradient *
eazel_engine_gradient_ref (eazel_engine_gradient *g)
{
    g_return_val_if_fail (g != NULL, NULL);

    g->refcount++;
    return g;
}

void
eazel_engine_gradient_unref (eazel_engine_gradient *g)
{
    g_return_if_fail (g != NULL);
    g->refcount--;

    if (g->refcount == 0)
    {
	GSList *x;
	for (x = g->components; x != 0; x = x->next)
	    g_free (x->data);
	g_slist_free (g->components);
	g_free (g);
    }
}

eazel_engine_gradient *
eazel_engine_make_two_point_gradient (eazel_engine_gradient_direction direction,
				      gulong from_rgb, gulong to_rgb)
{
    GdkColor from, to;
    eazel_engine_gradient_component *component;

    g_return_val_if_fail (direction != GRADIENT_NONE, NULL);

    from.red = (from_rgb >> 16) & 255;
    from.red |= from.red << 8;
    from.green = (from_rgb >> 8) & 255;
    from.green |= from.green << 8;
    from.blue = (from_rgb >> 0) & 255;
    from.blue |= from.blue << 8;

    to.red = (to_rgb >> 16) & 255;
    to.red |= to.red << 8;
    to.green = (to_rgb >> 8) & 255;
    to.green |= to.green << 8;
    to.blue = (to_rgb >> 0) & 255;
    to.blue |= to.blue << 8;

    component = g_new (eazel_engine_gradient_component, 1);
    component->color = to;
    component->weight = 1.0;

    return eazel_engine_gradient_new (direction, &from,
				      g_slist_prepend (NULL, component));
}


/* rendering */

static inline void
fill_gradient_rgb_buffer_1 (const GdkColor *from, const GdkColor *to,
			    int rgb_total, guchar *rgb_buf,
			    int rgb_first, int rgb_last)
{
    int delta_r = to->red - from->red;
    int delta_g = to->green - from->green;
    int delta_b = to->blue - from->blue;
    guchar *rgb_ptr = rgb_buf;
    int i;

    g_return_if_fail (rgb_first <= rgb_last && rgb_last <= rgb_total);

    for (i = rgb_first; i < rgb_last; i++)
    {
	*rgb_ptr++ = (from->red + (delta_r * i) / rgb_total) >> 8;
	*rgb_ptr++ = (from->green + (delta_g * i) / rgb_total) >> 8;
	*rgb_ptr++ = (from->blue + (delta_b * i) / rgb_total) >> 8;
    }
}

void
eazel_engine_fill_gradient_rgb_buffer (const eazel_engine_gradient *gradient,
				       int rgb_total, guchar *rgb_buf,
				       int rgb_first, int rgb_last)
{
    g_return_if_fail (gradient != NULL);
    g_return_if_fail (rgb_buf != NULL);

    if (gradient->components == 0)
    {
	/* Single color `gradient' */
	fill_gradient_rgb_buffer_1 (&gradient->from, &gradient->from,
				     rgb_total, rgb_buf, rgb_first, rgb_last);
    }
    else
    {
	float total_weight, weight_ptr;
	int rgb_ptr;
	GSList *x;
	const GdkColor *pred;

	total_weight = 0.0;
	for (x = gradient->components; x != 0; x = x->next)
	{
	    eazel_engine_gradient_component *c = x->data;
	    total_weight += c->weight;
	}

	rgb_ptr = 0;
	weight_ptr = 0.0;
	pred = &gradient->from;
	for (x = gradient->components; x != 0; x = x->next)
	{
	    eazel_engine_gradient_component *c = x->data;
	    int rgb_chunk = (c->weight * rgb_total) / total_weight;

	    int first = MAX (rgb_first, rgb_ptr);
	    int last = MIN (rgb_last, rgb_ptr + rgb_chunk);

	    if (x->next == 0)
		last = rgb_last;

	    if (last > first)
	    {
		fill_gradient_rgb_buffer_1 (pred, &c->color,
					    last - first,
					    rgb_buf + rgb_ptr * 3,
					    first - rgb_ptr,
					    last - rgb_ptr);
	    }

	    pred = &c->color;
	    weight_ptr += c->weight;
	    rgb_ptr += rgb_chunk;
	}
    }
}

static void
draw_vertical_gradient (GdkDrawable *drawable, GdkGC *gc,
			const GdkRectangle *full_rect,
			const GdkRectangle *clip_rect,
			const eazel_engine_gradient *gradient)
{
    int rgb_size = clip_rect->height;
    guchar *rgb = alloca (rgb_size * 3), *ptr;

    eazel_engine_fill_gradient_rgb_buffer (gradient, full_rect->height, rgb,
					   clip_rect->y - full_rect->y,
					   (clip_rect->y + clip_rect->height)
					   - full_rect->y);

    if (dither_mode == GDK_RGB_DITHER_NONE)
    {
	GdkColormap *sys_lut = gdk_colormap_get_system ();
	GdkGCValues old_values;
	int y;

	gdk_gc_get_values (gc, &old_values);

	ptr = rgb;
	for (y = clip_rect->y; y < clip_rect->y + clip_rect->height; y++)
	{
	    guchar r = *ptr++;
	    guchar g = *ptr++;
	    guchar b = *ptr++;
	    GdkColor color = { 0, r << 8, g << 8, b << 8 };
	    gdk_colormap_alloc_color (sys_lut, &color, FALSE, TRUE);
	    gdk_gc_set_foreground (gc, &color);
	    gdk_draw_line (drawable, gc, clip_rect->x, y,
			   clip_rect->x + clip_rect->width - 1, y);
	}

	gdk_gc_set_foreground (gc, &old_values.foreground);
    }
    else
    {
	guchar *xrgb = alloca (clip_rect->width * clip_rect->height * 3);
	int x, y;
	guchar *ptr_in = rgb, *ptr_out = xrgb;
	for (y = 0; y < clip_rect->height; y++)
	{
	    guchar r = *ptr_in++;
	    guchar g = *ptr_in++;
	    guchar b = *ptr_in++;
	    for (x = 0; x < clip_rect->width; x++)
	    {
		*ptr_out++ = r;
		*ptr_out++ = g;
		*ptr_out++ = b;
	    }
	}
	gdk_draw_rgb_image (drawable, gc, clip_rect->x, clip_rect->y,
			    clip_rect->width, clip_rect->height,
			    dither_mode, xrgb, clip_rect->width * 3);
    }
}

static void
draw_horizontal_gradient (GdkDrawable *drawable, GdkGC *gc,
			  const GdkRectangle *full_rect,
			  const GdkRectangle *clip_rect,
			  const eazel_engine_gradient *gradient)
{
    int rgb_size = clip_rect->width;
    guchar *rgb = alloca (rgb_size * 3), *ptr;

    eazel_engine_fill_gradient_rgb_buffer (gradient, full_rect->width, rgb,
					   clip_rect->x - full_rect->x,
					   (clip_rect->x + clip_rect->width)
					   - full_rect->x);

    if (dither_mode == GDK_RGB_DITHER_NONE)
    {
	GdkColormap *sys_lut = gdk_colormap_get_system ();
	GdkGCValues old_values;
	int x;

	gdk_gc_get_values (gc, &old_values);

	ptr = rgb;
	for (x = clip_rect->x; x < clip_rect->x + clip_rect->width; x++)
	{
	    guchar r = *ptr++;
	    guchar g = *ptr++;
	    guchar b = *ptr++;
	    GdkColor color = { 0, r << 8, g << 8, b << 8 };
	    gdk_colormap_alloc_color (sys_lut, &color, FALSE, TRUE);
	    gdk_gc_set_foreground (gc, &color);
	    gdk_draw_line (drawable, gc, x, clip_rect->y,
			   x, clip_rect->y + clip_rect->height - 1);
	}

	gdk_gc_set_foreground (gc, &old_values.foreground);
    }
    else
    {
	/* Using a row-stride of zero means we only need a single
	   row of rgb-data (inspired by nautilus-background.c) */
	gdk_draw_rgb_image (drawable, gc, clip_rect->x, clip_rect->y,
			    clip_rect->width, clip_rect->height,
			    dither_mode, rgb, 0);
    }
}

void
eazel_engine_draw_gradient (GdkDrawable *drawable,
			    GdkGC *gc,
			    const GdkRectangle *full_rect,
			    const GdkRectangle *clip_rect,
			    const eazel_engine_gradient *gradient)
{
    if (gradient->direction == GRADIENT_VERTICAL)
    {
	draw_vertical_gradient (drawable, gc, full_rect, clip_rect, gradient);
    }
    else if (gradient->direction == GRADIENT_HORIZONTAL)
    {
	draw_horizontal_gradient (drawable, gc, full_rect, clip_rect, gradient);
    }
}

void
eazel_engine_set_bg_gradient (GdkWindow *window,
			      eazel_engine_gradient *gradient)
{
    /* Render a tile of the specified gradient to a pixmap, then
       set it as the background pixmap of the window. */

    GdkRectangle area = { 0, 0 };
    GdkPixmap *pixmap;
    GdkGC *pixmap_gc;

    int window_x, window_y, window_width, window_height, window_depth;

    gdk_window_get_geometry (window, &window_x, &window_y,
			     &window_width, &window_height, &window_depth);

    if (gradient->direction == GRADIENT_VERTICAL)
    {
	area.width = 32;
	area.height = window_height;
    }
    else
    {
	area.width = window_width;
	area.height = 32;
    }
    
    pixmap = gdk_pixmap_new (window, area.width, area.height, window_depth);
    pixmap_gc = gdk_gc_new (pixmap);

    eazel_engine_draw_gradient (pixmap, pixmap_gc, &area, &area, gradient);

    gdk_window_set_back_pixmap (window, pixmap, FALSE);
    gdk_gc_unref (pixmap_gc);
    gdk_pixmap_unref (pixmap);
}
