#ifndef CRUX_GRADIENT_H
#define CRUX_GRADIENT_H

#include <gtk/gtk.h>

#include "crux-common.h"

extern eazel_engine_gradient *eazel_engine_gradient_new (eazel_engine_gradient_direction direction,
							 GdkColor *from,
							 GSList *components);
extern eazel_engine_gradient *eazel_engine_gradient_ref (eazel_engine_gradient *g);
extern void eazel_engine_gradient_unref (eazel_engine_gradient *g);
extern eazel_engine_gradient *eazel_engine_make_two_point_gradient (eazel_engine_gradient_direction direction,
								    gulong from_rgb,
								    gulong to_rgb);

extern void eazel_engine_fill_gradient_rgb_buffer (const eazel_engine_gradient *gradient,
						   int rgb_total, guchar *rgb_buf,
						   int rgb_first, int rgb_last);

extern void eazel_engine_draw_gradient (GdkDrawable *drawable,
					GdkGC *gc,
					const GdkRectangle *full_rect,
					const GdkRectangle *clip_rect,
					const eazel_engine_gradient *gradient);

extern void eazel_engine_set_bg_gradient (GdkWindow *window,
					  eazel_engine_gradient *gradient);

#endif
