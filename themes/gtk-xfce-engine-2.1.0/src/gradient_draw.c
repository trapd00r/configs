/*
 * The code in this file is originated from the following theme:
 *
 * Smooth theme by       Andrew Johnson <ajgenius@ajgenius.us>
 * IceGradient theme by  Tim Gerla <timg@means.net>
 *                       Tomas Ögren <stric@ing.umu.se>
 *                       JM Perez <jose.perez@upcnet.es>
 * Wonderland theme by   Garrett LeSage
 *                       Alexander Larsson
 *                       Owen Taylor <otaylor@redhat.com>
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtk.h>
#include <math.h>
#include "gradient_draw.h"

static void gradient_rgb_to_hls(gdouble * r, gdouble * g, gdouble * b)
{
    gdouble red = *r, green = *g, blue = *b;
    gdouble h, l, s;
    gdouble min, max, delta;

    if(red > green)
    {
        max = MAX(red, blue);
        min = MIN(green, blue);
    }
    else
    {
        max = MAX(green, blue);
        min = MIN(red, blue);
    }

    l = (max + min) / 2;
    s = 0;
    h = 0;

    if(max != min)
    {
        if(l <= 0.5)
	{
            s = (max - min) / (max + min);
        }
        else
	{
            s = (max - min) / (2 - max - min);
        }

        delta = max - min;
        if(red == max)
	{
            h = (green - blue) / delta;
        }
	else if(green == max)
	{
            h = 2 + (blue - red) / delta;
        }
        else if(blue == max)
	{
            h = 4 + (red - green) / delta;
        }

        h *= 60;
        if(h < 0.0)
	{
            h += 360;
        }
    }

    *r = h;
    *g = l;
    *b = s;
}

static void gradient_hls_to_rgb(gdouble * h, gdouble * l, gdouble * s)
{
    gdouble hue = *h + 120;
    gdouble lightness = *l;
    gdouble saturation = *s;
    gdouble m1, m2;
    gdouble r, g, b;

    if(lightness <= 0.5)
    {
        m2 = lightness * (1 + saturation);
    }
    else
    {
        m2 = lightness + saturation - lightness * saturation;
    }
    m1 = 2 * lightness - m2;

    if(saturation == 0)
    {
        *h = lightness;
        *l = lightness;
        *s = lightness;
    }
    else
    {
        while(hue > 360)
	{
            hue -= 360;
        }
        while(hue < 0)
	{
            hue += 360;
        }

        if(hue < 60)
	{
            r = m1 + (m2 - m1) * hue / 60;
        }
        else if(hue < 180)
	{
            r = m2;
        }
        else if(hue < 240)
	{
            r = m1 + (m2 - m1) * (240 - hue) / 60;
        }
        else
	{
            r = m1;
        }

        hue = *h;
        while(hue > 360)
	{
            hue -= 360;
        }
        while(hue < 0)
	{
            hue += 360;
        }

        if(hue < 60)
	{
            g = m1 + (m2 - m1) * hue / 60;
        }
        else if(hue < 180)
	{
            g = m2;
        }
        else if(hue < 240)
	{
            g = m1 + (m2 - m1) * (240 - hue) / 60;
        }
        else
	{
            g = m1;
        }

        hue = *h - 120;
        while(hue > 360)
	{
            hue -= 360;
        }
	while(hue < 0)
        {
	    hue += 360;
        }
        if(hue < 60)
        {
            b = m1 + (m2 - m1) * hue / 60;
        }
        else if(hue < 180)
        {
            b = m2;
        }
        else if(hue < 240)
        {
            b = m1 + (m2 - m1) * (240 - hue) / 60;
        }
        else
        {
            b = m1;
        }

        *h = r;
        *l = g;
        *s = b;
    }
}

void gradient_shade(GdkColor * a, GdkColor * b, gdouble k)
{
    gdouble red = (gdouble) a->red / 65535.0;
    gdouble green = (gdouble) a->green / 65535.0;
    gdouble blue = (gdouble) a->blue / 65535.0;

    gradient_rgb_to_hls(&red, &green, &blue);

    green = MIN(green * k, 1.0);
    green = MAX(green, 0.0);

    blue = MIN(blue * k, 1.0);
    blue = MAX(blue, 0.0);

    gradient_hls_to_rgb(&red, &green, &blue);

    b->red = red * 65535.0;
    b->green = green * 65535.0;
    b->blue = blue * 65535.0;
}

void gradient_alloc_color(GdkColor * color, GdkColormap * colormap, GdkColor light, GdkColor dark, gint position, gint steps)
{
    gfloat delta;
    /* delta = i/steps */
    delta = ((float)position / (float)steps);
    color->red = light.red + (float)((dark.red - light.red)) * delta;
    color->green = light.green + (float)((dark.green - light.green)) * delta;
    color->blue = light.blue + (float)((dark.blue - light.blue)) * delta;
    gdk_colormap_alloc_color(colormap, color, FALSE, TRUE);
}

void gradient_draw(GdkWindow * window, GdkGC * gc, GdkColormap * colormap, GdkRectangle * area, gint x, gint y, gint width, gint height, GdkColor light, GdkColor dark, GradientType gradient_type, gboolean noclip)
{
    GdkRectangle clip;
    GdkColor color;
    gint i, steps = 0;
    gboolean horizontal = (gradient_type == GRADIENT_HORIZONTAL);
    gboolean northern = (gradient_type == GRADIENT_NORTHERN_DIAGONAL);
    gboolean diagonal = ((gradient_type == GRADIENT_NORTHERN_DIAGONAL) || (gradient_type == GRADIENT_SOUTHERN_DIAGONAL));

    clip.x = x;
    clip.y = y;
    clip.width = width;
    clip.height = height;

    g_return_if_fail(window != NULL);
    g_return_if_fail(colormap != NULL);
    g_return_if_fail(gc != NULL);

    if(diagonal)
    {
        steps = width + height - 1;
    }
    else if(horizontal)
    {
        steps = width;
    }
    else
    {
        steps = height;
    }

    if(!noclip)
    {
        if(area)
        {
            GdkRectangle clip2;
            if(gdk_rectangle_intersect(area, &clip, &clip2))
	    {
                gdk_gc_set_clip_rectangle(gc, &clip2);
            }
            else
	    {
                gdk_gc_set_clip_rectangle(gc, area);
            }
        }
        else
        {
            gdk_gc_set_clip_rectangle(gc, &clip);
        }
    }

    for(i = 0; i < steps; i++)
    {
        gradient_alloc_color(&color, colormap, light, dark, i, steps);
        gdk_gc_set_foreground(gc, &color);
        if(diagonal)
        {
            if(northern)
	    {
                gdk_draw_line(window, gc, x + i, y, x, y + i);
            }
	    else
            {
	        gdk_draw_line(window, gc, x + width - 1 - i, y, x + width - 1, y + i);
            }
	}
        else
        {
            if(horizontal)
	    {
                gdk_draw_line(window, gc, x + i, y, x + i, y + height);
            }
            else
	    {
                gdk_draw_line(window, gc, x, y + i, x + width, y + i);
            }
        }
        gdk_colormap_free_colors(colormap, &color, 1);
    }

    if(!noclip)
    {
        gdk_gc_set_clip_rectangle(gc, NULL);
    }
}

void gradient_draw_shaded(GdkWindow * window, GdkGC * gc, GdkColormap * colormap, GdkRectangle * area, gint x, gint y, gint width, gint height, GdkColor color, gfloat shine_value, gfloat gradient_shade_value, GradientType gradient_type, gboolean noclip)
{
    GdkColor light, dark;

    gradient_shade(&color, &dark, gradient_shade_value);
    gradient_shade(&color, &light, shine_value);

    gradient_draw(window, gc, colormap, area, x, y, width, height, light, dark, gradient_type, noclip);
}
