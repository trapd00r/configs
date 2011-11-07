#ifndef DRAW_FILL_H
#define DRAW_FILL_H

typedef enum {
  GDK_GRADIENT_HORIZONTAL,
  GDK_GRADIENT_VERTICAL,
  GDK_GRADIENT_NORTHERN_DIAGONAL,
  GDK_GRADIENT_SOUTHERN_DIAGONAL
} GdkGradientType;

#define GRADIENT(horizontal) (horizontal ? GDK_GRADIENT_HORIZONTAL : GDK_GRADIENT_VERTICAL)
#define DIAGONALGRADIENT(northern) (northern ? GDK_GRADIENT_NORTHERN_DIAGONAL : GDK_GRADIENT_SOUTHERN_DIAGONAL)

void 
alloc_gradient_color(GdkColor * color,
                     GdkColormap * colormap,
                     GdkColor light, 
                     GdkColor dark,
                     gint position,
                     gint steps,
                     gboolean quadratic);

void
shade (GdkColor * a, GdkColor * b, gdouble k);

void
gdk_draw_gradient (GdkWindow * window,
	           GdkGC * gc,
	           GdkColormap * colormap,
	           GdkRectangle * area,
	           gint x,
	           gint y,
	           gint width,
	           gint height,
	           GdkColor light, 
	           GdkColor dark, 
	           GdkGradientType gradient_type,
		   gboolean quadratic,
		   gboolean noclip);

void
gdk_draw_shaded_gradient (GdkWindow * window,
	                  GdkGC * gc,
			  GdkColormap * colormap,
			  GdkRectangle * area,
			  gint x,
			  gint y,
			  gint width,
			  gint height,
			  GdkColor color, 
			  gfloat shade_value, 
			  gfloat shine_value, 
			  GdkGradientType gradient_type,
			  gboolean quadratic,
			  gboolean noclip);

void
gdk_tile_pixbuf_fill (GdkWindow * window,
                      GdkGC * gc,
		      gchar * file_name,
		      GdkRectangle * area,
		      gint xoffset, 
		      gint yoffset,
		      gint x,
		      gint y,
		      gint width,
		      gint height,
		      gboolean noclip, 
                      gboolean window_is_buffered);
		      
void cleanup_gdk_pixbuf_cache(gboolean force);
		      

#endif /* DRAW_FILL_H */
