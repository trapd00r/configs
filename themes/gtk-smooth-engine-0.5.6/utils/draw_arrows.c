#include "misc_functions.h"

/* This function is based on XFCE's & CleanIce draw arrow routines, both which  were based on ThinIce's */
static void
do_draw_default_arrow(GdkWindow * window,
		        GdkRectangle * area,
			GtkArrowType arrow_type,
			GdkGC * gc,
			gint x,
			gint y,
			gint width,
			gint height)
{
  gint steps, extra;
  gint start, increment;
  gint i;

  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  if (arrow_type == GTK_ARROW_UP || arrow_type == GTK_ARROW_DOWN)
  {
    width = width + width % 2 - 1;	/* Force odd */

    steps = 1 + width / 2;

    extra = height - steps;

    if (arrow_type == GTK_ARROW_DOWN)
    {
      start = y;
      increment = 1;
    }
    else
    {
      start = y + height - 1;
      increment = -1;
    }

    for (i = 0; i < extra; i++)
    {
      gdk_draw_line (window, gc, x, start + i * increment, x + width - 1, start + i * increment);
    }
    for (; i < height; i++)
    {
      gdk_draw_line (window, gc, x + (i - extra), start + i * increment, x + width - (i - extra) - 1, start + i * increment);
    }
  }
  else
  {
    height = height + height % 2 - 1;	/* Force odd */

    steps = 1 + height / 2;

    extra = width - steps;

    if (arrow_type == GTK_ARROW_RIGHT)
    {
      start = x;
      increment = 1;
    }
    else
    {
      start = x + width - 1;
      increment = -1;
    }

    for (i = 0; i < extra; i++)
    {
      gdk_draw_line (window, gc, start + i * increment, y, start + i * increment, y + height - 1);
    }
    for (; i < width; i++)
    {
      gdk_draw_line (window, gc, start + i * increment, y + (i - extra), start + i * increment, y + height - (i - extra) - 1);
    }
  }
  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);
}

/* This function is based on EnGradient/IceGradient's draw arrow routines */
static void
do_draw_icegradient_arrow(GdkWindow * window,
		        GdkRectangle * area,
			GtkArrowType arrow_type,
			GdkGC * gc,
			gboolean fill,
			gint x,
			gint y,
			gint width,
			gint height)
{
  gint half_width, half_height,w;
  GdkPoint points[4];

  width &= 0xfffe;
  height &= 0xfffe;
  
  w = MIN(width, height);
  x += (width-w)/2;
  y += (height-w)/2;
  width = height = w;
  
  half_width = width / 2;
  half_height = height / 2;

  switch (arrow_type) {
    case GTK_ARROW_UP:
      points[0].x = x + half_width - 1;
      points[0].y = y;
      points[1].x = x;
      points[1].y = y + height - 1;
      points[2].x = x + width  - 1;
      points[2].y = y + height - 1;
      points[3].x = x + half_width;
      points[3].y = y;
      break;

    case GTK_ARROW_DOWN:
      points[0].x = x + half_width ;
      points[0].y = y + height     - 1;
      points[1].x = x + width - 1;
      points[1].y = y;
      points[2].x = x;
      points[2].y = y;
      points[3].x = x + half_width - 1;
      points[3].y = y + height     - 1;
      break;

    case GTK_ARROW_LEFT:
      points[0].x = x;
      points[0].y = y + half_height;
      points[1].x = x + width - 1;
      points[1].y = y + height - 1;
      points[2].x = x + width - 1;
      points[2].y = y;
      points[3].x = x;
      points[3].y = y + half_height - 1;
      break;

    case GTK_ARROW_RIGHT:
      points[0].x = x + width - 1;
      points[0].y = y + half_height - 1;
      points[1].x = x;
      points[1].y = y;
      points[2].x = x;
      points[2].y = y + height - 1;
      points[3].x = x + width - 1;
      points[3].y = y + half_height;
      break;

    default:
      return;
  }    

  if (gc) {
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    
    gdk_draw_polygon (window, gc, fill, points, 4);
    
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);
  }
}

/* This function is taken straight from the Wonderland 
 * theme engine, with no modifications whatsoever.(yet...)
 */
static void
arrow_draw_hline (GdkWindow     *window,
		  GdkGC         *gc,
		  int            x1,
		  int            x2,
		  int            y,
		  gboolean       last)
{
  if (x2 - x1 < 7 && !last) /* 7 to get garretts pixels, otherwise 6 */
    gdk_draw_line (window, gc, x1, y, x2, y);
  else if (last)
    {
      if (x2 - x1 <= 7)
	{
	  gdk_draw_line (window, gc, x1+1, y, x1+1, y);
	  gdk_draw_line (window, gc, x2-1, y, x2-1, y); 
	}
      else
	{
	  gdk_draw_line (window, gc, x1+2, y, x1+2, y);
	  gdk_draw_line (window, gc, x2-2, y, x2-2, y);
	}
    }
  else
    {
      gdk_draw_line (window, gc, x1, y, x1+2, y);
      gdk_draw_line (window, gc, x2-2, y, x2, y); 
    }
}

/* This function is taken straight from the Wonderland 
 * theme engine, with no modifications whatsoever.(yet...)
 */
static void
arrow_draw_vline (GdkWindow     *window,
		  GdkGC         *gc,
		  int            y1,
		  int            y2,
		  int            x,
		  gboolean       last)
{
  if (y2 - y1 < 7 && !last) /* 7 to get garretts pixels */
    gdk_draw_line (window, gc, x, y1, x, y2);
  else if (last)
    {
      gdk_draw_line (window, gc, x, y1+2, x, y1+2);
      gdk_draw_line (window, gc, x, y2-2, x, y2-2); 
    }
  else
    {
      gdk_draw_line (window, gc, x, y1, x, y1+2);
      gdk_draw_line (window, gc, x, y2-2, x, y2); 
    }
}

/* This function is based on the Wonderland theme engine, 
 * it is essentially calculate_arrow_geometry and draw_arrow,
 * concatted into one composite whole...
 */
static void
do_draw_wonderland_arrow(GdkWindow * window,
		        GdkRectangle * area,
			GtkArrowType arrow_type,
			GdkGC * gc,
			gint x,
			gint y,
			gint width,
			gint height)
{
  gint i, j;
  gint w = width;
  gint h = height;
  
  switch (arrow_type)
    {
    case GTK_ARROW_UP:
    case GTK_ARROW_DOWN:
      w += (w % 2) - 1;
      h = (w / 2 + 1) + 1;

      if (h > height)
	{
	  h = height;
	  w = 2 * (h - 1) - 1;
	}
      
      if (arrow_type == GTK_ARROW_DOWN)
	{
	  if (height % 2 == 1 || h % 2 == 0)
	    height += 1;
	}
      else
	{
	  if (height % 2 == 0 || h % 2 == 0)
	    height -= 1;
	}
      break;

    case GTK_ARROW_RIGHT:
    case GTK_ARROW_LEFT:
      h += (h % 2) - 1;
      w = (h / 2 + 1) + 1; 
      
      if (w > width)
	{
	  w = width;
	  h = 2 * (w - 1) - 1;
	}
      
      if (arrow_type == GTK_ARROW_RIGHT)
	{
	  if (width % 2 == 1 || w % 2 == 0)
	    width += 1;
	}
      else
	{
	  if (width % 2 == 0 || w % 2 == 0)
	    width -= 1;
	}
      break;
      
    default:
      /* should not be reached */
      return;
    }

  x += (width - w) / 2;
  y += (height - h) / 2;
  height = h;
  width = w;
  
  if (gc) {
    if (area)
      gdk_gc_set_clip_rectangle (gc, area);
    
    if (arrow_type == GTK_ARROW_DOWN)
      {
        for (i = 0, j = -1; i < height; i++, j++)
	  arrow_draw_hline (window, gc, x + j, x + width - j - 1, y + i, i == 0);
	  
      }
    else if (arrow_type == GTK_ARROW_UP)
      {
        for (i = height - 1, j = -1; i >= 0; i--, j++)
	  arrow_draw_hline (window, gc, x + j, x + width - j - 1, y + i, i == height - 1);
      }
    else if (arrow_type == GTK_ARROW_LEFT)
      {
        for (i = width - 1, j = -1; i >= 0; i--, j++)
	  arrow_draw_vline (window, gc, y + j, y + height - j - 1, x + i, i == width - 1);
      }
    else if (arrow_type == GTK_ARROW_RIGHT)
      {
        for (i = 0, j = -1; i < width; i++, j++)
	  arrow_draw_vline (window, gc, y + j, y + height - j - 1,  x + i, i == 0);
      }
    
    if (area)
      gdk_gc_set_clip_rectangle (gc, NULL);
  }
}

/* This function is another home grown routine simply for the
 * purpose of abstracting the multiple draw_arrow routines, so
 * that modifications such as new variants could easily be added 
 * later on with virtually no modifications anywhere else.
 */
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
	      gint arrow_style)
{
  gint aw=width, ah=height, extra_tail=0;

  switch (arrow_style) {
    case ARROW_STYLE_ICEGRADIENT : 
      ah -= 2;
      aw -= 2;
      x += (width - aw) / 2;
      y += (height - ah) / 2;
      do_draw_icegradient_arrow(window, area, arrow_type, fill_gc, TRUE, x, y, aw, ah);
      do_draw_icegradient_arrow(window, area, arrow_type, border_gc, FALSE, x, y, aw, ah);
      break;
    case ARROW_STYLE_WONDERLAND : 
      do_draw_wonderland_arrow(window, area, arrow_type, border_gc, x+1, y+1, width-2, height-2);
      break;
    case ARROW_STYLE_THINICE : 
    case ARROW_STYLE_XFCE :
    case ARROW_STYLE_DEFAULT : 
      if (arrow_style == ARROW_STYLE_THINICE) 
        extra_tail=3;
      else  
        if (arrow_style == ARROW_STYLE_XFCE) 
          extra_tail=1;

      ah -= 2;
      aw -= 2;
      if ((arrow_type == GTK_ARROW_LEFT) || (arrow_type == GTK_ARROW_RIGHT)) {
        gfloat tmp=((ah+1)/2) - ((width%2)?1:0);
        if (tmp > aw) {
          ah = 2*aw - 1 - ((width%2)?1:0);
          aw = (ah+1)/2;
        } else {
          aw = (gint) tmp;
          ah = 2*aw - 1;
        }  

        if ((ah < 5) || (aw < 3)) {
          ah = 5;
          aw = 3;
        }
	aw += extra_tail;
      } else { 
        gfloat tmp=((aw+1)/2) - ((height%2)?1:0);
      
        if (tmp > ah) {
          aw = 2*ah - 1 - ((height%2)?1:0);
          ah = (aw+1)/2;
        } else {
          ah = (gint) tmp;
          aw = 2*ah - 1;
        }  

        if ((aw < 5) || (ah < 3)) {
          aw = 5;
          ah = 3;
        }
	ah += extra_tail;
      }

      x += (width - aw) / 2 ;
      y += (height - ah) / 2;
      
      do_draw_default_arrow(window, area, arrow_type, border_gc, x, y, aw, ah);
      do_draw_default_arrow(window, area, arrow_type, fill_gc, x+1, y+1, aw-2, ah-2);
      break;
    case ARROW_STYLE_XPM : 
    default :
      do_draw_arrow(window, area, arrow_type, fill_gc, border_gc, x, y, width, height, ARROW_STYLE_ICEGRADIENT);
      break;
  }
}


gboolean 
TranslateArrowStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("icegradient"))
    *retval = ARROW_STYLE_ICEGRADIENT;
  else if (is_enum("thinice"))
    *retval = ARROW_STYLE_THINICE;
  else if (is_enum("wonderland"))
    *retval = ARROW_STYLE_WONDERLAND;
  else if (is_enum("default") || is_enum("cleanice"))
    *retval = ARROW_STYLE_DEFAULT;
  else if (is_enum("xfce"))
    *retval = ARROW_STYLE_XFCE;
  else if (is_enum("xpm"))
    *retval = ARROW_STYLE_XPM;
  else
    return FALSE; 

  return TRUE;
}
