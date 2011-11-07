#ifndef DRAW_ARROWS_H
#define DRAW_ARROWS_H

#define ARROW_STYLE_ICEGRADIENT	1
#define ARROW_STYLE_THINICE	2
#define ARROW_STYLE_WONDERLAND	3
#define ARROW_STYLE_DEFAULT	4
#define ARROW_STYLE_XFCE	5
#define ARROW_STYLE_XPM		6

void
do_draw_arrow(GdkWindow * window,
              GdkRectangle * area,
	      GtkArrowType arrow_type,
	      GdkGC * fill_gc,
  	      GdkGC * border_gc,
	      gint x,
	      gint y,
	      gint width,
	      gint height,
	      gint arrow_style);

gboolean TranslateArrowStyleName (gchar * str, gint *retval);

#endif /* DRAW_ARROWS_H */
