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

#ifndef INC_GRADIENT_DRAW_H
#define INC_GRADIENT_DRAW_H

typedef enum
{
    GRADIENT_HORIZONTAL,
    GRADIENT_VERTICAL,
    GRADIENT_NORTHERN_DIAGONAL,
    GRADIENT_SOUTHERN_DIAGONAL
} GradientType;

#define GRADIENT(horizontal) (horizontal ? GRADIENT_HORIZONTAL : GRADIENT_VERTICAL)
#define DIAGONALGRADIENT(northern) (northern ? GRADIENT_NORTHERN_DIAGONAL : GRADIENT_SOUTHERN_DIAGONAL)

void gradient_alloc_color(GdkColor * color, GdkColormap * colormap, GdkColor light, GdkColor dark, gint position, gint steps);

void gradient_shade(GdkColor * a, GdkColor * b, gdouble k);

void gradient_draw(GdkWindow * window, GdkGC * gc, GdkColormap * colormap, GdkRectangle * area, gint x, gint y, gint width, gint height, GdkColor light, GdkColor dark, GradientType gradient_type, gboolean noclip);

void gradient_draw_shaded(GdkWindow * window, GdkGC * gc, GdkColormap * colormap, GdkRectangle * area, gint x, gint y, gint width, gint height, GdkColor color, gfloat shine_value, gfloat shade_value, GradientType gradient_type, gboolean noclip);

#endif /* INC_GRADIENT_DRAW_H */
