#ifndef CRUX_PIXMAPS_H
#define CRUX_PIXMAPS_H

#include <gtk/gtk.h>

#include "crux-common.h"

extern void eazel_engine_stock_table_unref (eazel_engine_stock_table *table);
extern eazel_engine_stock_table *eazel_engine_stock_table_ref (eazel_engine_stock_table *table);
extern void eazel_engine_stock_pixmap_and_mask (eazel_engine_stock_table *table,
						eazel_engine_stock_image type,
						GdkPixmap **image,
						GdkBitmap **mask);
extern void eazel_engine_stock_pixmap_and_mask_scaled (eazel_engine_stock_table *table,
						       eazel_engine_stock_image type,
						       int width, int height,
						       GdkPixmap **image,
						       GdkBitmap **mask);
extern void eazel_engine_stock_free_pixmaps (eazel_engine_stock_table *table,
					     eazel_engine_stock_image type,
					     GdkPixmap *image, GdkPixmap *mask);
extern void eazel_engine_stock_get_size (eazel_engine_stock_table *table,
					 eazel_engine_stock_image type,
					 int *width, int *height);

#endif
