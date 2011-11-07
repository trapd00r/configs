/* eazel-theme-pixmaps.c -- image manipulation and caching

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

   $Id: crux-pixmaps.c,v 1.2 2002/01/18 22:33:03 seth Exp $

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

#include "crux-pixmaps.h"
#include "crux-gradient.h"

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* pixmap caching, borrowed from sawfish */

static gulong cached_pixels, max_cached_pixels = 64 * 1024;
static gulong hits, misses;

typedef struct pixmap_cache_node_struct pixmap_cache_node;

struct pixmap_cache_node_struct {
    pixmap_cache_node *next, *pred;
    pixmap_cache_node *newer, *older;
    eazel_engine_image *im;
    int width, height;
    GdkPixmap *p1;
    GdkBitmap *p2;
    int ref_count;
};

static pixmap_cache_node *oldest, *newest;

/* list manipulators */

static void
remove_from_age_list (pixmap_cache_node *n)
{
    if (n->newer != 0)
	n->newer->older = n->older;
    else
	newest = n->older;
    if (n->older != 0)
	n->older->newer = n->newer;
    else
	oldest = n->newer;
}

static void
prepend_to_age_list (pixmap_cache_node *n)
{
    n->newer = oldest;
    if (n->newer != 0)
	n->newer->older = n;
    oldest = n;
    n->older = 0;
    if (newest == 0)
	newest = n;
}

static void
remove_from_image (pixmap_cache_node *n)
{
    if (n->next != 0)
	n->next->pred = n->pred;
    else
	n->im->pixmap_last = n->pred;
    if (n->pred != 0)
	n->pred->next = n->next;
    else
	n->im->pixmap_first = n->next;
}

static void
prepend_to_image (pixmap_cache_node *n)
{
    eazel_engine_image *im = n->im;
    n->next = im->pixmap_first;
    if (n->next != 0)
	n->next->pred = n;
    im->pixmap_first = n;
    n->pred = 0;
    if (im->pixmap_last == 0)
	im->pixmap_last = n;
}

static void
free_node (pixmap_cache_node *n, gboolean dealloc)
{
    if (n->p1 != 0)
	gdk_pixmap_unref (n->p1);
    if (n->p2 != 0)
	gdk_bitmap_unref (n->p2);
    if (dealloc)
	g_free (n);
}

static void
delete_node (pixmap_cache_node *n, gboolean dealloc)
{
    remove_from_image (n);
    remove_from_age_list (n);
    cached_pixels -= n->width * n->height;
    free_node (n, dealloc);
}

/* public interface */

static gboolean
pixmap_cache_ref (eazel_engine_image *im, int width, int height,
		  GdkPixmap **p1, GdkBitmap **p2)
{
    pixmap_cache_node *n;
    for (n = im->pixmap_first; n != 0; n = n->next)
    {
	if (n->width == width && n->height == height)
	{
	    remove_from_image (n);
	    prepend_to_image (n);
	    remove_from_age_list (n);
	    prepend_to_age_list (n);
	    n->ref_count++;
	    *p1 = n->p1;
	    *p2 = n->p2;
	    hits++;
	    return TRUE;
	}
    }
    misses++;
    return FALSE;
}

static void
pixmap_cache_unref (eazel_engine_image *im, GdkPixmap *p1, GdkBitmap *p2)
{
    pixmap_cache_node *n;
    for (n = im->pixmap_first; n != 0; n = n->next)
    {
	if (n->p1 == p1 && n->p2 == p2)
	{
	    n->ref_count--;
#ifdef DISABLE_CACHE
	    if (n->ref_count == 0)
		delete_node (n, TRUE);
#endif		
	    return;
	}
    }
    fprintf (stderr, "warning: unref'ing unknown image in pixmap-cache\n");
}

static void
pixmap_cache_set (eazel_engine_image *im, int width, int height,
		  GdkPixmap *p1, GdkBitmap *p2)
{
    int pixel_count = width * height;
    pixmap_cache_node *n = 0;

    while (pixel_count + cached_pixels > max_cached_pixels)
    {
	/* remove oldest node */
	pixmap_cache_node *this = oldest;
	while (this != 0 && this->ref_count > 0)
	    this = this->newer;
	if (this == 0)
	    break;
	delete_node (this, n != 0);
	if (n == 0)
	    n = this;
    }

    if (n == 0)
	n = g_new0 (pixmap_cache_node, 1);

    n->im = im;
    n->width = width;
    n->height = height;
    n->p1 = p1;
    n->p2 = p2;
    n->ref_count = 1;

    prepend_to_image (n);
    prepend_to_age_list (n);
    cached_pixels += pixel_count;
}

static void
pixmap_cache_flush_image (eazel_engine_image *im)
{
    pixmap_cache_node *n, *next;
    for (n = im->pixmap_first; n != 0; n = next)
    {
	next = n->next;
	remove_from_age_list (n);
	free_node (n, TRUE);
    }
    im->pixmap_first = im->pixmap_last = 0;
}


/* image filtering */

typedef struct {
    guchar red, green, blue;
    guchar alpha;
} pixbuf_pixel;

/* Returns either a new pixbuf, or PIXBUF with its ref-count incremented */
static GdkPixbuf *
map_pixbuf (GdkPixbuf *pixbuf, void (*fun)(pixbuf_pixel *, void *), void *data)
{
    int width, height, row_stride;
    guchar *pixels;
    int x, y;

    if (gdk_pixbuf_get_n_channels (pixbuf) == 3)
	pixbuf = gdk_pixbuf_add_alpha (pixbuf, FALSE, 0, 0, 0);
    else
	gdk_pixbuf_ref (pixbuf);

    width = gdk_pixbuf_get_width (pixbuf);
    height = gdk_pixbuf_get_height (pixbuf);
    row_stride = gdk_pixbuf_get_rowstride (pixbuf);
    pixels = gdk_pixbuf_get_pixels (pixbuf);

    g_assert (gdk_pixbuf_get_n_channels (pixbuf) == 4);

    for (y = 0; y < height; y++)
    {
	guchar *row_pixels = pixels +  y * row_stride;

	for (x = 0; x < width; x++)
	{
	    pixbuf_pixel pixel;

	    pixel.red = row_pixels[0];
	    pixel.green = row_pixels[1];
	    pixel.blue = row_pixels[2];
	    pixel.alpha = row_pixels[3];

	    fun (&pixel, data);

	    row_pixels[0] = pixel.red;
	    row_pixels[1] = pixel.green;
	    row_pixels[2] = pixel.blue;
	    row_pixels[3] = pixel.alpha;

	    row_pixels += 4;
	}
    }

    return pixbuf;
}

struct recolor_closure {
    guchar rgb_buf[256*3];
};

static void
recolor_callback (pixbuf_pixel *pixel, void *data)
{
    struct recolor_closure *rc = data;
    int base;

    /* The trick is this:

       Recolorable pixels must have zero red and blue channels. The
       green channel gives a notional grey-scale value that is multiplied
       by the values in the closure */

    if (pixel->red != 0 || pixel->blue != 0)
	return;

    base = pixel->green * 3;

    pixel->red = rc->rgb_buf[base+0];
    pixel->green = rc->rgb_buf[base+1];
    pixel->blue = rc->rgb_buf[base+2];
}

static GdkPixbuf *
recolor_pixbuf (GdkPixbuf *pixbuf, eazel_engine_gradient *gradient)
{
    struct recolor_closure rc;

    eazel_engine_fill_gradient_rgb_buffer (gradient, 256, rc.rgb_buf, 0, 256);

    return map_pixbuf (pixbuf, recolor_callback, &rc);
}


/* image loading */

/* XXX move to gtkrc */
static char *image_path[] = {
    DATADIR,
    0
};

static GdkPixbuf *
load_image (const char *file)
{
    char **path = image_path;
    while (*path != 0)
    {
	GdkPixbuf *pixbuf;
	size_t len = strlen (*path) + strlen (file) + 2;
	char *buf = alloca (len);
	sprintf (buf, "%s/%s", *path, file);
	pixbuf = gdk_pixbuf_new_from_file (buf, NULL);
	if (pixbuf != 0)
	    return pixbuf;
	path++;
    }
    /* XXX error handling here */
    g_error ("No such image: %s", file);
    return 0;
}

static GdkPixbuf *
eazel_engine_image_get_pixbuf (eazel_engine_image *p)
{
    if (p->pixbuf == 0)
    {
	g_assert (p->filename != 0);
	p->pixbuf = load_image (p->filename);

	if (p->pixbuf == 0)
	    return 0;

	if (p->recolor != 0)
	{
	    GdkPixbuf *new;
	    new = recolor_pixbuf (p->pixbuf, p->recolor);
	    if (new != NULL)
	    {
		gdk_pixbuf_unref (p->pixbuf);
		p->pixbuf = new;
	    }
	}

    }
    return p->pixbuf;
}


/* image rendering */

static void
do_scale (GdkPixbuf *src, int src_x, int src_y, int src_w, int src_h,
	  GdkPixbuf *dst, int dst_x, int dst_y, int dst_w, int dst_h)
{
    double scale_x, scale_y;
    double off_x, off_y;

    if (src_w <= 0 || src_h <= 0 || dst_w <= 0 || dst_h <= 0)
	return;

    scale_x = dst_w / (double) src_w;
    scale_y = dst_h / (double) src_h;

    off_x = dst_x - scale_x * src_x;
    off_y = dst_y - scale_y * src_y;

    gdk_pixbuf_scale (src, dst,
		      dst_x, dst_y,
		      dst_w, dst_h,
		      off_x, off_y,
		      scale_x, scale_y,
		      GDK_INTERP_NEAREST);
}

static void
eazel_engine_image_render (eazel_engine_image *image, int width, int height,
			   GdkPixmap **pixmap, GdkBitmap **mask)
{
    GdkPixbuf *im = eazel_engine_image_get_pixbuf (image);
    GdkPixbuf *scaled = im;
    gboolean need_to_unref = FALSE;
    int im_width = gdk_pixbuf_get_width (im);
    int im_height = gdk_pixbuf_get_height (im);

    g_assert (im != 0);
    g_return_if_fail (width > 0);
    g_return_if_fail (height > 0);

    if (pixmap_cache_ref (image, width, height, pixmap, mask))
	return;

    /* XXX handle cases where combined image borders are larger
       XXX than the destination image.. */

    if (im_width != width || im_height != height)
    {
	/* need to scale to width by height */

	int border[4];
	border[0] = image->border[0];
	border[1] = image->border[1];
	border[2] = image->border[2];
	border[3] = image->border[3];

	/* truncate borders if dest image is too small */
	if (border[0] + border[1] > width)
	{
	    border[0] = MIN (border[0], width / 2);
	    border[1] = MIN (border[1], width / 2);
	}
	if (border[2] + border[3] > height
	    || image->border[2] + image->border[3] >= im_height)
	{
	    border[2] = MIN (border[2], height / 2);
	    border[3] = MIN (border[3], height / 2);
	}

	g_assert (border[0] + border[1] <= width);
	g_assert (border[2] + border[3] <= height);

	/* create a new buffer */
	scaled = gdk_pixbuf_new (gdk_pixbuf_get_colorspace (im),
				 gdk_pixbuf_get_has_alpha (im),
				 gdk_pixbuf_get_bits_per_sample (im),
				 width, height);
	need_to_unref = TRUE;

	/* stretch borders to fit scaled image */

	if (border[0] > 0)
	{
	    do_scale (im, 0, image->border[2], image->border[0],
		      im_height - (image->border[2] + image->border[3]),
		      scaled, 0, border[2], border[0],
		      height - (border[2] + border[3]));
	}
	if (border[1] > 0)
	{
	    do_scale (im, im_width - image->border[1], image->border[2],
		      image->border[1],
		      im_height - (image->border[2] + image->border[3]),
		      scaled, width - border[1], border[2], border[1],
		      height - (border[2] + border[3]));
	}

	if (border[2] > 0)
	{
	    do_scale (im, image->border[0], 0,
		      im_width - (image->border[0] + image->border[1]),
		      image->border[2],
		      scaled, border[0], 0,
		      width - (border[0] + border[1]), border[2]);
	}
	if (border[3] > 0)
	{
	    do_scale (im, image->border[0], im_height - image->border[3],
		      im_width - (image->border[0] + image->border[1]),
		      image->border[3],
		      scaled, border[0], height - border[3],
		      width - (border[0] + border[1]), border[3]);
	}

	/* now do corner intersections between borders */

	if (border[0] > 0 && border[2] > 0)
	{
	    do_scale (im, 0, 0, image->border[0], image->border[2],
		      scaled, 0, 0, border[0], border[2]);
	}
	if (border[1] > 0 && border[2] > 0)
	{
	    do_scale (im, im_width - image->border[1], 0,
		      image->border[1], image->border[2],
		      scaled, width - border[1], 0, border[1], border[2]);
	}
	if (border[0] > 0 && border[3] > 0)
	{
	    do_scale (im, 0, im_height - image->border[3],
		      image->border[0], image->border[3],
		      scaled, 0, height - border[3], border[0], border[3]);
	}
	if (border[1] > 0 && border[3] > 0)
	{
	    do_scale (im, im_width - image->border[1],
		      im_height - image->border[3],
		      image->border[1], image->border[3],
		      scaled, width - border[1], height - border[3],
		      border[1], border[3]);
	}

	/* scale the inner parts of the image */
	if (border[0] + border[1] < width
	    || border[2] + border[3] < height)
	{
	    do_scale (im, image->border[0], image->border[2],
		      im_width - (image->border[0] + image->border[1]),
		      im_height - (image->border[2] + image->border[3]),
		      scaled, border[0], border[2],
		      width - (border[0] + border[1]),
		      height - (border[2] + border[3]));
	}
    }

    gdk_pixbuf_render_pixmap_and_mask (scaled, pixmap, mask, 128);
    if (need_to_unref)
	gdk_pixbuf_unref (scaled);

    pixmap_cache_set (image, width, height, *pixmap, *mask);
}

static void
eazel_engine_image_free_pixmaps (eazel_engine_image *image,
				 GdkPixmap *pixmap, GdkBitmap *mask)
{
    pixmap_cache_unref (image, pixmap, mask);
}


/* stock images */

void
eazel_engine_stock_table_unref (eazel_engine_stock_table *table)
{
    table->ref_count--;

    if (table->ref_count == 0)
    {
	int i;
	for (i = 0; i < EAZEL_ENGINE_STOCK_MAX; i++)
	{
	    if (table->images[i].pixbuf != 0)
		gdk_pixbuf_unref (table->images[i].pixbuf);
	    pixmap_cache_flush_image (&table->images[i]);
	}
	g_free (table);
    }
}

eazel_engine_stock_table *
eazel_engine_stock_table_ref (eazel_engine_stock_table *table)
{
    table->ref_count++;
    return table;
}

static inline eazel_engine_image *
get_stock_image (eazel_engine_stock_table *table,
		 eazel_engine_stock_image type)
{
    g_assert (type >= 0 && type < EAZEL_ENGINE_STOCK_MAX);

    return &table->images[type];
}

void
eazel_engine_stock_pixmap_and_mask_scaled (eazel_engine_stock_table *table,
					   eazel_engine_stock_image type,
					   int width, int height,
					   GdkPixmap **image, GdkBitmap **mask)
{
    eazel_engine_image *img = get_stock_image (table, type);
    eazel_engine_image_render (img, width, height, image, mask);
}

void
eazel_engine_stock_pixmap_and_mask (eazel_engine_stock_table *table,
				    eazel_engine_stock_image type,
				    GdkPixmap **image, GdkBitmap **mask)
{
    eazel_engine_image *img = get_stock_image (table, type);
    GdkPixbuf *pixbuf = eazel_engine_image_get_pixbuf (img);

    eazel_engine_image_render (img, gdk_pixbuf_get_width (pixbuf),
			       gdk_pixbuf_get_height (pixbuf),
			       image, mask);
}

void
eazel_engine_stock_free_pixmaps (eazel_engine_stock_table *table,
				 eazel_engine_stock_image type,
				 GdkPixmap *image, GdkPixmap *mask)
{
    eazel_engine_image *img = get_stock_image (table, type);
    eazel_engine_image_free_pixmaps (img, image, mask);
}

void
eazel_engine_stock_get_size (eazel_engine_stock_table *table,
			     eazel_engine_stock_image type,
			     int *width, int *height)
{
    eazel_engine_image *img = get_stock_image (table, type);
    GdkPixbuf *pixbuf = eazel_engine_image_get_pixbuf (img);

    if (width != 0)
	*width = gdk_pixbuf_get_width (pixbuf);
    if (height != 0)
	*height = gdk_pixbuf_get_height (pixbuf);
}
