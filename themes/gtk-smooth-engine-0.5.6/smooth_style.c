/*******************************************************************************************
 * Smooth theme for gtk, based on the ThinIce, CleanIce, XFCE, EnGradient, IceGradient, XFCE, 
 *                                    Xenophilia, Wonderland/Bluecurve, & LighthouseBlue GTK+ Engines
 *
 * Author: Andrew Johnson <ajgenius@ajgenius.us>
 *
 * A nice simple engine, designed to be clean, smooth and highly configurable. It is based
 * initially upon EnGradient, but highly modified to include some of the best features from 
 * many other (some popular) engines. While very little of this code is initially my own,
 * it is been so highly modified it at times might apear to be.
 *
 *******************************************************************************************
 *   
 * EnGradient Header -->
 * 
 * My gradient engine for gtk+.  slightly modified from the IceGradient theme,
 * to include checkboxes, scrollbars, arrows, and a few other things from the
 * Mac2 theme engine, in order to make it look like a standard toolkit.  Almost
 * no code in this theme is my own.  It is mostly the IceGradient theme, with
 * large chunks of the Mac2 theme (by Ken Lynch <kenny@lynch42.freeserve.co.uk>)
 *   
 *   IceGradient theme for gtk, hacked over ThinIce by Tim Gerla and Tomas Ögren ThinIce,
 *     which is based on raster's Motif theme and the Metal theme.
 *     Authors: Tim Gerla <timg@means.net>
 *              Tomas Ögren <stric@ing.umu.se>
 *              JM Perez <jose.perez@upcnet.es>
 *   
 * <-- EnGradient Header
 *   
 *******************************************************************************************   
 *   
 * IceGradient Header -->
 *   
 * IceGradient theme for gtk, hacked over ThinIce by Tim Gerla and Tomas Ögren ThinIce,
 *   which is based on raster's Motif theme and the Metal theme.
 *   Authors: Tim Gerla <timg@means.net>
 *            Tomas Ögren <stric@ing.umu.se>
 *            JM Perez <jose.perez@upcnet.es>
 *   
 * <-- IceGradient Header
 *   
 *******************************************************************************************    
 *   
 * CleanIce Header -->
 *
 * CleanIce theme for gtk, based on the ThinIce, Clean and Cleanice GTK+ Engines
 *   Author: Bastien Nocera <hadess@hadess.net>
 *   Cleanice original author:  Rodney Dawes <dobez@fnmail.com>
 *   ThinIce Authors: Tim Gerla <timg@means.net>
 *   	  Tomas Ögren <stric@ing.umu.se>
 *   Clean Author: dengen40@yahoo.com
 *
 * <-- CleanIce Header
 *
 *******************************************************************************************/

#include <gtk/gtk.h>

#include "smooth_style.h"
#include "smooth_rc_style.h"

#include "utils/misc_functions.h"

#include <math.h>

#include <gtk/gtk.h>

static double shades[] = {1.065, 0.963, 0.896, 0.85, 0.768, 0.665, 0.4, 0.205, 0.112};

/* This function is based on a similar routine from IceGradient */
void 
smooth_fill_background(GtkStyle * style,
     	               GdkWindow * window,
	               GtkStateType state_type,
		       GtkShadowType shadow_type,
	               GdkRectangle * area,
	               GdkRegion * rgn,
 	               GtkWidget * widget,
		       void * part,
	               gint x,
	               gint y,
	               gint width,
	               gint height,
		       gboolean use_gradient,  
	               gboolean invert,
		       GtkOrientation orientation,
		       gboolean arc_fill)
{
  gint buffered=BUFFERED_FILL(style);
  GdkPixmap *buffer=NULL;
  
  GdkRectangle clip_area;
  GdkBitmap * clip_mask = NULL;
  gint fill_style;
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  if (!part) part = THEME_PART(BACKGROUND_PART(style));
  
  fill_style = FILL_STYLE(style, part);  

  clip_area.x = x;
  clip_area.y = y;
  clip_area.width = width;
  clip_area.height = height;
  	
  if (fill_style == SMOOTH_FILL_PIXBUF) {
    if (!FILL_FILE_NAME(style, part, state_type)) 
      fill_style = SMOOTH_FILL_SOLID;
  } else {
    if (!use_gradient) 
       fill_style = SMOOTH_FILL_SOLID;
  }

  switch (fill_style) {
    case SMOOTH_FILL_PIXBUF : 
      { 
        GdkGC *gc = gdk_gc_new(window);
	GdkGCValues gc_values;

        gdk_gc_get_values(style->bg_gc[state_type], &gc_values);
	gdk_gc_set_function(gc, GDK_COPY);
        gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, gc_values.cap_style, gc_values.join_style);
               
        if (!arc_fill) {
	  if (rgn) {
	    arc_fill = TRUE;
	    gdk_gc_set_clip_region(gc, rgn);
	  } else 
	    if (area) gdk_gc_set_clip_rectangle(gc, area);
	} 
	else {
  	  gdk_gc_set_clip_rectangle(gc, NULL);
          clip_mask = arc_clip_mask(clip_area.width+1, clip_area.height+1);
	  gdk_gc_set_clip_origin(gc, clip_area.x, clip_area.y);	  
          gdk_gc_set_clip_mask(gc, clip_mask);
        }
        
        gdk_tile_pixbuf_fill (window, gc, FILL_FILE_NAME(style, part, state_type), area, 0, 0, x, y, width, height, arc_fill, buffered);

        gdk_gc_set_clip_mask(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
        gdk_gc_destroy(gc);
      }
      break;
    case SMOOTH_FILL_GRADIENT : 
    case SMOOTH_FILL_SHADE_GRADIENT : 
      {
        GdkGC *gc = gdk_gc_new(window);
	GdkGCValues gc_values;
        gint direction=FILL_GRADIENT_DIRECTION(style, part, orientation);
        gboolean quadratic=FILL_QUADRATIC_GRADIENT(style, part);

       
        gdk_gc_get_values(style->bg_gc[state_type], &gc_values);
	gdk_gc_set_function(gc, GDK_COPY);
        gdk_gc_set_line_attributes(gc, 1, GDK_LINE_SOLID, gc_values.cap_style, gc_values.join_style);
        
        if (!arc_fill) {
	  if (rgn) {
	    arc_fill = TRUE;
	    gdk_gc_set_clip_region(gc, rgn);
	  } else 
	    if (area) gdk_gc_set_clip_rectangle(gc, area);
	} 
	else
          if (arc_fill) {
  	    gdk_gc_set_clip_rectangle(gc, NULL);
            clip_mask = arc_clip_mask(clip_area.width+1, clip_area.height+1);
	    gdk_gc_set_clip_origin(gc, clip_area.x, clip_area.y);	  
            gdk_gc_set_clip_mask(gc, clip_mask);
          }
	  
	if (fill_style == SMOOTH_FILL_GRADIENT) {
          GdkColor color1=FILL_COLOR1(style, part, state_type), color2=FILL_COLOR2(style, part, state_type);

          gdk_draw_gradient(window, gc, style->colormap, area, x, y, width, height, color1, color2, direction, quadratic, arc_fill);
        } else {
          gfloat shade2=FILL_SHADE2_VALUE(style, part), shade1=FILL_SHADE1_VALUE(style, part); 
  
          gdk_draw_shaded_gradient(window, gc, style->colormap, area, x, y, width, height, style->bg[state_type], shade2, shade1, direction, quadratic, arc_fill);
        }
        gdk_gc_set_clip_mask(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
        gdk_gc_destroy(gc);
      }
      break;
    default :
      if ((!style->bg_pixmap[state_type]) || (arc_fill) || (rgn)) {
        GdkGC *gc = ((!(OPTION_MOTIF(style))) && (shadow_type!=GTK_SHADOW_NONE))?style->base_gc[state_type]:style->bg_gc[state_type];

        if (area) gdk_gc_set_clip_rectangle(gc, area);
	if (rgn) gdk_gc_set_clip_region(gc, rgn);

        if (!arc_fill) {
         gdk_draw_rectangle(window, gc, TRUE, x, y, width, height); 
	} 
	else 
	{
  	  gdk_draw_arc(window, gc, TRUE, x, y, width, height, 0, 360 * 64);
          gdk_draw_arc(window, gc, FALSE, x, y, width, height, 0, 360 * 64);
        }

        gdk_gc_set_clip_region(gc, NULL);
        gdk_gc_set_clip_rectangle(gc, NULL);
      } else
         gtk_style_apply_default_background(style, window, widget && !GTK_WIDGET_NO_WINDOW(widget),
                                          state_type, area, x, y, width, height);
  }
  if (clip_mask)
    gdk_bitmap_unref(clip_mask);
}

void
smooth_draw_shadow_with_gap(GtkStyle * style,
                            GdkWindow * window,
			    GtkStateType state_type,
	  		    GtkShadowType shadow_type,
			    GdkRectangle * area,
			    GtkWidget * widget,
			    detail_char * detail,
			    void * part,
			    gint x,
			    gint y,
			    gint width,
			    gint height,
			    GtkPositionType gap_side,
			    gint gap_pos,
			    gint gap_size)
{
  GdkGC              *gc1 = NULL;
  GdkGC              *gc2 = NULL;
  GdkGC              *gc3 = NULL;
  GdkGC              *gc4 = NULL;
  GdkGC              *shade = NULL;
  GdkGC              *dark, *light, *mid, *middark=NULL, *midlight=NULL;
  gboolean 	     line_overlap = FALSE;

  if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_NONE) return;
  
  if (shadow_type == GTK_SHADOW_NONE) return;

  dark = darktone_gc(style, state_type);
  if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_FLAT) {
    gc1 = dark;
    if DETAIL("SMOOTH_DRAW_OPTION")
      do_draw_option_shadow(window, area, gc1, gc1, x, y, width, height);
    else
      do_draw_shadow_with_gap(window, area, gc1, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
    if (dark) gtk_gc_release (dark);
    return;
  }   
    
  light = lighttone_gc(style, state_type);
  mid = midtone_gc(style, state_type);
  
  switch (shadow_type)
    {
    case GTK_SHADOW_ETCHED_IN:
      gc1 = light;
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_SOFT)      
        gc2 = mid;
      else  
        gc2 = dark;
      if DETAIL("SMOOTH_DRAW_OPTION") {
        do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
        do_draw_option_shadow(window, area, gc1, gc2, x+1, y+1, width-2, height-2);
      } else {
        do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos+1, gap_size-1, TRUE);
        do_draw_shadow_with_gap(window, area, gc1, gc2, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size-2, TRUE);
      }
      break;
    case GTK_SHADOW_ETCHED_OUT:
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_SOFT)      
        gc1 = mid;
      else  
        gc1 = dark;
      gc2 = light;
      if DETAIL("SMOOTH_DRAW_OPTION") {
        do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
        do_draw_option_shadow(window, area, gc1, gc2, x+1, y+1, width-2, height-2);
      } else {
        do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos+1, gap_size-1, TRUE);
        do_draw_shadow_with_gap(window, area, gc1, gc2, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size-2, TRUE);
      }
      break;
    case GTK_SHADOW_IN:
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_BEVELED) {
        gc1 = light;
        gc2 = dark;
        if DETAIL("SMOOTH_DRAW_OPTION")
          do_draw_option_bevel(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part));
        else
	  do_draw_bevel_with_gap(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part), gap_side, gap_pos, gap_size);
      } else
        if ((EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN) || (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_SOFT)) {
          gc1 = light;
          gc2 = (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN)?dark:mid;
          if DETAIL("SMOOTH_DRAW_OPTION")
            do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
          else
	    do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else
        if ((EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_WIN32) && DETAIL ("button") && (widget) && GTK_WIDGET_HAS_DEFAULT(widget)) {
          do_draw_shadow_with_gap(window, area, dark, dark, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else {
        switch (EDGE_LINE_STYLE(style, part))
	{
	  case SMOOTH_LINE_SMOOTHED :
            gc1 = mid;
            gc2 = dark;
            gc3 = light;
            gc4 = mid;
	    line_overlap = FALSE;
            break;
	  case SMOOTH_LINE_SMOOTHBEVEL :
            midlight = midlighttone_gc(style, state_type);
            middark = middarktone_gc(style, state_type);
            gc1 = middark;
            gc2 = dark;
            gc3 = light;
            gc4 = midlight;
	    line_overlap = FALSE;
            break;
	  case SMOOTH_LINE_COLD :
            if (DETAIL ("button") || DETAIL ("togglebutton") || DETAIL ("optionmenu") || 
	        DETAIL ("slider") || DETAIL ("vscrollbar") || DETAIL ("hscrollbar"))
	    { 
              shade = shaded_color (style, state_type, shades[6]);
              gc2 = mid;
              gc4 = light;
	    } else {
              shade = shaded_color (style, state_type, shades[5]);
              gc2 = style->bg_gc[state_type];
              gc4 = style->bg_gc[state_type];
            }
            gc1 = shade;
            gc3 = shade;
	    line_overlap = FALSE;
            break;
	  case SMOOTH_LINE_WIN32 :
            shade = shaded_color (style, state_type, shades[8]);
            gc1 = dark;
            gc2 = shade;
            gc3 = light;
            gc4 = style->bg_gc[state_type];
	    line_overlap = TRUE;
            break;
          default :
            gc1 = dark;
            gc2 = style->black_gc;
            gc3 = light;
            gc4 = mid;
	    line_overlap = FALSE;
	    break;
	} 
        if DETAIL("SMOOTH_DRAW_OPTION") {
          do_draw_option_shadow(window, area, gc1, gc3, x, y, width, height);
          do_draw_option_shadow(window, area, gc2, gc4, x+1, y+1, width-2, height-2);
        } else {
          do_draw_shadow_with_gap(window, area, gc1, gc3, x, y, width, height, gap_side, gap_pos+1, gap_size-1, line_overlap);
          do_draw_shadow_with_gap(window, area, gc2, gc4, x+1, y+1, width-2, height-2, gap_side, gap_pos, gap_size, line_overlap);
	}  
      } 	
      break;
    case GTK_SHADOW_OUT:
      if (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_BEVELED) {
        gc1 = dark;
        gc2 = light;
        if DETAIL("SMOOTH_DRAW_OPTION")
          do_draw_option_bevel(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part));
        else
          do_draw_bevel_with_gap(window, area, gc2, gc1, x, y, width, height, EDGE_LINE_THICKNESS(style, part), gap_side, gap_pos, gap_size);
      } else
        if ((EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN) || (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_SOFT)) {
          gc1 = (EDGE_LINE_STYLE(style, part)==SMOOTH_LINE_THIN)?dark:mid;
          gc2 = light;
          if DETAIL("SMOOTH_DRAW_OPTION")
            do_draw_option_shadow(window, area, gc2, gc1, x, y, width, height);
          else
            do_draw_shadow_with_gap(window, area, gc2, gc1, x, y, width, height, gap_side, gap_pos, gap_size, TRUE);
      } else {
        switch (EDGE_LINE_STYLE(style, part)) 
	{
	  case SMOOTH_LINE_SMOOTHED :
            gc1 = mid;
            gc2 = light;
            gc3 = dark;
            gc4 = mid;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_SMOOTHBEVEL :
            midlight = midlighttone_gc(style, state_type);
            middark = middarktone_gc(style, state_type);
            gc1 = midlight;
            gc2 = light;
            gc3 = dark;
            gc4 = middark;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_COLD :
            shade = shaded_color (style, state_type, shades[6]);
            gc1 = shade;
            gc2 = light;
            gc3 = shade;
            gc4 = mid;
	    line_overlap = TRUE;
            break;
	  case SMOOTH_LINE_WIN32 :
            shade = shaded_color (style, state_type, shades[8]);
            gc1 = light;
            gc2 = style->bg_gc[state_type];
            gc3 = shade;
            gc4 = dark;
	    line_overlap = FALSE;
            break;
          default :
            gc1 = mid;
            gc2 = light;
            gc3 = style->black_gc;
            gc4 = dark;
	    line_overlap = TRUE;
	    break;
	} 
        if DETAIL("SMOOTH_DRAW_OPTION") {
          do_draw_option_shadow(window, area, gc1, gc3, x, y, width, height);
          do_draw_option_shadow(window, area, gc2, gc4, x+1, y+1, width-2, height-2);
        } else {
          do_draw_shadow_with_gap(window, area, gc1, gc3, x, y, width, height, gap_side, gap_pos+1, gap_size-1, line_overlap);
          do_draw_shadow_with_gap(window, area, gc2, gc4, x+1, y+1, width-2, height-2, gap_side, gap_pos+1, gap_size-1, line_overlap);
	}  
      } 	
      break;
    }
  if (shade) {
    gtk_gc_release (shade);
  }  
  if (dark) gtk_gc_release (dark);
  if (mid) gtk_gc_release (mid);
  if (light) gtk_gc_release (light);
  if (middark) gtk_gc_release (middark);
  if (midlight) gtk_gc_release (midlight);
}

void 
smooth_draw_grip(GtkStyle * style,
                 GdkWindow * window,
                 GtkStateType state_type,
                 GdkRectangle * area,
	         gint x,
	         gint y,
	         gint width,
	         gint height,
	         GtkOrientation orientation)
{
  gint	x2, y2;
  GdkGC * light_gc, * dark_gc, * mid_gc;
  GdkGC              *dark, *light, *mid;
  GdkRectangle dest;
  smooth_grip_style * grip = GRIP_PART(style);
  
  dark = darktone_gc(style, state_type);
  light = lighttone_gc(style, state_type);
  mid = midtone_gc(style, state_type);

  dest.x = x + EDGE_LINE_THICKNESS(style, grip);
  dest.y = y + EDGE_LINE_THICKNESS(style, grip);
  dest.width = width - 2*EDGE_LINE_THICKNESS(style, grip);
  dest.height = height - 2*EDGE_LINE_THICKNESS(style, grip);

  if (LINE_STYLE(style, grip) == SMOOTH_LINE_NONE) return;
  if (LINE_STYLE(style, grip) == SMOOTH_LINE_FLAT){
    light_gc=dark;
    dark_gc=NULL;
  } else {
    light_gc=light;
    if (LINE_STYLE(style, grip) == SMOOTH_LINE_SOFT)
      dark_gc=mid;
    else  
      dark_gc=dark;
  } 

  switch PART_STYLE(grip)
  {
    case NO_GRIP:
      break;
    case BARS_IN_GRIP :
    case BARS_OUT_GRIP :
       dest.x = x + 2;
       dest.y = y + 2;
       dest.width = width - 4;
       dest.height = height - 4;

      do_draw_lines(window, &dest, light_gc, dark_gc, mid, x, y, width, height, orientation, (PART_STYLE(grip)==BARS_IN_GRIP));
      break; 
    case LINES_IN_GRIP :
    case LINES_OUT_GRIP :
      do_draw_lines(window, &dest, light_gc, dark_gc, mid, x, y, width, height, orientation, (PART_STYLE(grip)==LINES_IN_GRIP));
      break; 
    case FIXEDLINES_IN_GRIP :
    case FIXEDLINES_OUT_GRIP :
      do_draw_fixed_midlines(window, &dest, light_gc, dark_gc, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), (PART_STYLE(grip)==FIXEDLINES_OUT_GRIP), FALSE, FALSE);
      break; 
    case SLASHES_GRIP :
      x = dest.x;
      y = dest.y;
      width = dest.width;
      height = dest.height;
      do_draw_fixed_midlines(window, &dest, light_gc, dark_gc, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), FALSE, TRUE, FALSE);
      break; 
    case DOTS_IN_GRIP :
    case DOTS_OUT_GRIP :
    case SMALLDOTS_IN_GRIP :
    case SMALLDOTS_OUT_GRIP :
      {
        gboolean small = ((PART_STYLE(grip) == SMALLDOTS_IN_GRIP) || (PART_STYLE(grip) == SMALLDOTS_OUT_GRIP));
	if (LINE_STYLE(style, grip) == SMOOTH_LINE_FLAT){
          dark_gc=dark;
        } else {
          if ((PART_STYLE(grip) == DOTS_IN_GRIP) || (PART_STYLE(grip) == SMALLDOTS_IN_GRIP)) {
            light_gc=dark_gc;
            dark_gc=light;
          } else {
            if (orientation == GTK_ORIENTATION_HORIZONTAL)
	      y -= 1;
            else
  	      x -= 1;
          }      
        } 
        do_draw_fixed_dots(window, &dest, light_gc, dark_gc, mid, x, y, width, height, orientation, GRIP_COUNT(style), GRIP_SPACING(style), small);
      }
      break; 
    case MAC_BUDS_IN_GRIP :
    case MAC_BUDS_OUT_GRIP : 
    case NS_BUDS_IN_GRIP :
    case NS_BUDS_OUT_GRIP : 
      {
        gboolean in = ((PART_STYLE(grip) == MAC_BUDS_IN_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
        gboolean ns = ((PART_STYLE(grip) == NS_BUDS_OUT_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
       
        if (!in) {
          light_gc = style->white_gc;
          mid_gc = mid;
        } else {
          light_gc = dark;
          mid_gc = mid;
          dark_gc = light;
        }
   
        do_draw_buds(window, area, light_gc, dark_gc, mid_gc, x, y, width, height, orientation, ns);
      }
      break; 
    default:
      break; 
  }

  if (dark) gtk_gc_release (dark);
  if (light) gtk_gc_release (light);
  if (mid) gtk_gc_release (mid);
}

static void 
smooth_draw_slider_grip(GtkStyle * style,
                        GdkWindow * window,
	    	        GtkStateType state_type,
		        GtkShadowType shadow_type,
		        GdkRectangle * area,
		        GtkWidget * widget,
		        detail_char * detail,
		        gint x,
		        gint y,
		        gint width,
		        gint height,
		        GtkOrientation orientation)
{
  gboolean BAIL = FALSE;
  smooth_grip_style *grip = GRIP_PART(style);
 
 switch (PART_STYLE(grip))
   {
   case NO_GRIP:
     break;
   case BARS_IN_GRIP:
   case BARS_OUT_GRIP:
      {
      gint w, h;
		
      w = width;
      h = height;
      if (orientation == GTK_ORIENTATION_VERTICAL) {
	h = MIN(height, width + height/7);
	y = y + (height - h)/2;
	orientation = GTK_ORIENTATION_HORIZONTAL; 
      } else {
	w = MIN(width, width/7 + height);
	x = x + (width - w)/2;
	orientation = GTK_ORIENTATION_VERTICAL;
      }
		
      width = w;
      height = h;
     } 
      /* too small no bars */
     if ((width <= 13) && (height <= 11))
       BAIL = TRUE;

     break;
   case LINES_IN_GRIP:
   case LINES_OUT_GRIP:
      {
      gint w, h;
		
      w = width;
      h = height;
      if (orientation == GTK_ORIENTATION_VERTICAL) {
	h = MIN(height, width + height/7);
	y = y + (height - h)/2;
      } else {
	w = MIN(width, width/7 + height);
	x = x + (width - w)/2;
      }
		
      width = w;
      height = h;
     } 
      /* too small no lines */
     if ((width <= 13) && (height <= 11))
       BAIL = TRUE;

     break;

   case FIXEDLINES_IN_GRIP:
   case FIXEDLINES_OUT_GRIP:
       /* too small no midlines */
      if (((width <= 13) && (orientation == GTK_ORIENTATION_HORIZONTAL)) ||
          ((height <= 13) && (orientation == GTK_ORIENTATION_VERTICAL)))
         BAIL = TRUE;
	
     break;
   case SLASHES_GRIP:
      if (((width <= 13) && (orientation == GTK_ORIENTATION_HORIZONTAL)) ||
          ((height <= 13) && (orientation == GTK_ORIENTATION_VERTICAL)))
         BAIL = TRUE;

     break;
   case DOTS_IN_GRIP:
   case DOTS_OUT_GRIP:
   case SMALLDOTS_IN_GRIP :
   case SMALLDOTS_OUT_GRIP :
      if ((width <= 7) && (height <= 7))
         BAIL = TRUE;

      break;
   case MAC_BUDS_IN_GRIP:
   case MAC_BUDS_OUT_GRIP:
   case NS_BUDS_IN_GRIP:
   case NS_BUDS_OUT_GRIP:
     {
       gboolean ns = ((PART_STYLE(grip) == NS_BUDS_OUT_GRIP) || (PART_STYLE(grip) == NS_BUDS_IN_GRIP));
       gint w = width, h = height;

       if (orientation == GTK_ORIENTATION_VERTICAL) {
         h = MIN(height, width + height/7);
         y = y + (height - h)/2;
       } else {
         w = MIN(width, width/7 + height);
         x = x + (width - w)/2;
       }

       #if GTK1
       x += 1 + (gint)(ns);
       y += 1 + (gint)(ns);
       width = w - 3;
       height = h - 3;
//       g_warning("GTK1.2 SPECIFIC CODE STILL IN smooth_draw_slider_grip!!!");
       #endif

       #if GTK2
       x += 2 + (gint)(ns);
       y += 3 + (gint)(ns);
       width = w - 4;
       height = h - 6;
//       g_warning("GTK2 SPECIFIC CODE STILL IN smooth_draw_slider_grip!!!");
       #endif
      
        /* too small no buds */
       if ((width <= 13) && (height <= 11))
         BAIL = TRUE;
     }
     break;
   default :
     BAIL = TRUE;
   }	  
   if (!BAIL)
     smooth_draw_grip(style, window, state_type, area, x+PART_XPADDING(grip), y+PART_YPADDING(grip), width-PART_XPADDING(grip)*2, height-PART_YPADDING(grip)*2, orientation);      
}

void
smooth_draw_shadow(GtkStyle * style,
   	           GdkWindow * window,
	           GtkStateType state_type,
	           GtkShadowType shadow_type,
	           GdkRectangle * area,
	           GtkWidget * widget,
	           detail_char * detail,
	           gint x,
	           gint y,
	           gint width,
	           gint height,
                   gint gap_pos)
{
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  if ((EDGE_LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT)  && DETAIL ("entry") && widget && (GTK_IS_SPIN_BUTTON (widget) || (widget->parent && GTK_IS_COMBO(widget->parent)))) 
  {
       gtk_paint_flat_box(style, window, widget->state, GTK_SHADOW_NONE, area, widget, "entry_bg", x, y, width, height);

       smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height,  gap_pos, 0, height);
  } else 
    smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height, 0, 0, 0);
}

void
smooth_draw_line(GtkStyle * style,
	         GdkWindow * window,
	         GtkStateType state_type,
	         GdkRectangle * area,
	         GtkWidget * widget,
	         detail_char * detail,
	         gint start,
	         gint end,
	         gint base,
                 GtkOrientation orientation)
{
  gint                thickness_light;
  gint                thickness_dark;
  gint                i;
  GdkGC * gc1, * gc2;
  GdkGC              *dark, *light, *mid;
  
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  thickness_light = ythickness(style) / 2;
  thickness_dark = ythickness(style) - thickness_light;
  
  dark = darktone_gc(style, state_type);
  light = lighttone_gc(style, state_type);
  mid = midtone_gc(style, state_type);

  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_NONE) return;
  if (LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT) 
  {
    gc1 =dark;
    gc2 = NULL;
  } else {
    gc1 = light;
    if (LINE_STYLE(style, NULL) == SMOOTH_LINE_SOFT)
      gc2 = mid;
    else  
      gc2 = dark;
  }

  if (area)
  {
    if (gc1) gdk_gc_set_clip_rectangle(gc1, area);
    if (gc2) gdk_gc_set_clip_rectangle(gc2, area);
  }
 
  for (i = 0; i < thickness_dark; i++)
  {
    if (orientation==GTK_ORIENTATION_HORIZONTAL) {
      if (gc1) gdk_draw_line(window, gc1, end - i, base + i, end, base + i);
      if (gc2) gdk_draw_line(window, gc2, start, base + i, end - i, base + i);
    } else {
      if (gc1) gdk_draw_line(window, gc1, base + i, end - i, base + i, end);
      if (gc2) gdk_draw_line(window, gc2, base + i, start, base + i, end - i);
    }   
  }

  base += thickness_dark;
  for (i = 0; i < thickness_light; i++)
  {
    if (orientation==GTK_ORIENTATION_HORIZONTAL) {
      if (gc2) gdk_draw_line(window, gc2, start, base + i, start + thickness_light - i - 1, base + i);
      if (gc1) gdk_draw_line(window, gc1, start + thickness_light - i - 1, base + i, end, base + i);
    } else {
      if (gc2) gdk_draw_line(window, gc2, base + i, start, base + i, start + thickness_light - i - 1);
      if (gc1) gdk_draw_line(window, gc1, base + i, start + thickness_light - i - 1, base + i, end);
    }   
  }

  if (area)
  {
    if (gc1) gdk_gc_set_clip_rectangle(gc1, NULL);
    if (gc2) gdk_gc_set_clip_rectangle(gc2, NULL);
  }

  if (dark) gtk_gc_release (dark);
  if (light) gtk_gc_release (light);
  if (mid) gtk_gc_release (mid);
}

void
smooth_draw_polygon(GtkStyle * style,
	            GdkWindow * window,
	            GtkStateType state_type,
	            GtkShadowType shadow_type,
	            GdkRectangle * area,
	            GtkWidget * widget,
	            detail_char * detail,
	            GdkPoint * points,
	            gint npoints,
	            gint fill)
{
  static const gdouble pi_over_4 = M_PI_4;
  static const gdouble pi_3_over_4 = M_PI_4 * 3;

  GdkGC *light=NULL, *dark=NULL;

  GdkGC              *gc1;
  GdkGC              *gc2;
  GdkGC              *gc3;
  GdkGC              *gc4;
  gdouble             angle;
  gint                xadjust;
  gint                yadjust;
  gint                i;

  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));
  g_return_if_fail(points != NULL);

  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
      dark = darktone_gc(style, state_type);
      light = lighttone_gc(style, state_type);

      gc1 = light;
      gc2 = dark;
      gc3 = light;
      gc4 = dark;
      break;
    case GTK_SHADOW_ETCHED_IN:
      dark = darktone_gc(style, state_type);
      light = lighttone_gc(style, state_type);

      gc1 = light;
      gc2 = dark;
      gc3 = dark;
      gc4 = light;
      break;
    case GTK_SHADOW_OUT:
      dark = darktone_gc(style, state_type);
      light = lighttone_gc(style, state_type);

      gc1 = dark;
      gc2 = light;
      gc3 = dark;
      gc4 = light;
      break;
    case GTK_SHADOW_ETCHED_OUT:
      dark = darktone_gc(style, state_type);
      light = lighttone_gc(style, state_type);

      gc1 = dark;
      gc2 = light;
      gc3 = light;
      gc4 = dark;
      break;
    default:
      return;
    }

  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, area);
      gdk_gc_set_clip_rectangle(gc2, area);
      gdk_gc_set_clip_rectangle(gc3, area);
      gdk_gc_set_clip_rectangle(gc4, area);
    }

  if (fill)
    gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);

  npoints--;

  for (i = 0; i < npoints; i++)
    {
      if ((points[i].x == points[i + 1].x) &&
	  (points[i].y == points[i + 1].y))
	{
	  angle = 0;
	}
      else
	{
	  angle = atan2(points[i + 1].y - points[i].y,
			points[i + 1].x - points[i].x);
	}

      if ((angle > -pi_3_over_4) && (angle < pi_over_4))
	{
	  if (angle > -pi_over_4)
	    {
	      xadjust = 0;
	      yadjust = 1;
	    }
	  else
	    {
	      xadjust = 1;
	      yadjust = 0;
	    }

	  gdk_draw_line(window, gc1,
			points[i].x - xadjust, points[i].y - yadjust,
			points[i + 1].x - xadjust, points[i + 1].y - yadjust);
	  gdk_draw_line(window, gc3,
			points[i].x, points[i].y,
			points[i + 1].x, points[i + 1].y);
	}
      else
	{
	  if ((angle < -pi_3_over_4) || (angle > pi_3_over_4))
	    {
	      xadjust = 0;
	      yadjust = 1;
	    }
	  else
	    {
	      xadjust = 1;
	      yadjust = 0;
	    }

	  gdk_draw_line(window, gc4,
			points[i].x + xadjust, points[i].y + yadjust,
			points[i + 1].x + xadjust, points[i + 1].y + yadjust);
	  gdk_draw_line(window, gc2,
			points[i].x, points[i].y,
			points[i + 1].x, points[i + 1].y);
	}
    }
  if (area)
    {
      gdk_gc_set_clip_rectangle(gc1, NULL);
      gdk_gc_set_clip_rectangle(gc2, NULL);
      gdk_gc_set_clip_rectangle(gc3, NULL);
      gdk_gc_set_clip_rectangle(gc4, NULL);
    }

  if (light) gtk_gc_release (light);
  if (dark) gtk_gc_release (dark);
}

void
smooth_draw_arrow(GtkStyle * style,
	          GdkWindow * window,
	          GtkStateType state_type,
	          GtkShadowType shadow_type,
	          GdkRectangle * area,
	          GtkWidget * widget,
	          detail_char * detail,
	          GtkArrowType arrow_type,
	          gint fill,
	          gint x,
	          gint y,
	          gint width,
	          gint height)
{
  gint arrow_style;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  arrow_style = ARROW_STYLE(style);
   
  if (ETCHED_ARROW(style)) {
    GdkGC *light=NULL, *dark=NULL;

    dark = darktone_gc(style, state_type);
    light = lighttone_gc(style, state_type);

    do_draw_arrow(window, area, arrow_type, light, light, x+1, y+1, width, height, arrow_style);
    do_draw_arrow(window, area, arrow_type, dark, dark, x, y, width, height, arrow_style);

    if (light) gtk_gc_release (light);
    if (dark) gtk_gc_release (dark);
  } else  {   
    gboolean solid = SOLID_ARROW(style);
    GdkGC * fill_gc = style->fg_gc[state_type];

    if (!solid)
      fill_gc = style->base_gc[state_type];

    do_draw_arrow(window, area, arrow_type, fill_gc, style->fg_gc[state_type], x, y, width, height, arrow_style); 
  }
}

void
smooth_draw_focus(GtkStyle *style,
                  GdkWindow *window,
                  GtkStateType state_type,
                  GdkRectangle *area,
                  GtkWidget *widget,
                  detail_char *detail,
                  gint x,
                  gint y,
                  gint width,
                  gint height,
                  gint8 *dashes,
                  gint dash_width)
{
  GdkPoint points[5];
  GdkGC    *gc;
  gboolean free_gc = FALSE;
  gint line_width = 1;
  gint8 *dash_list = "\1\1";
  gint dash_len;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  if (FOCUS_USE_FOREGROUND(style, state_type)) {
    gc = new_color_gc (style, &FOCUS_FOREGROUND(style, state_type));
    free_gc = TRUE;
  } else
    gc = style->fg_gc[state_type];  

  if (FOCUS_USE_PATTERN(style, state_type))
     dash_list = FOCUS_PATTERN(style, state_type);
  else
    if (dashes) {
       dash_list = dashes;
       line_width = dash_width;
    } 
  
  if (area)
    gdk_gc_set_clip_rectangle (gc, area);

  gdk_gc_set_line_attributes (gc, line_width,
			      dash_list[0] ? GDK_LINE_ON_OFF_DASH : GDK_LINE_SOLID,
			      GDK_CAP_BUTT, GDK_JOIN_MITER);


  if (DETAIL("add-mode"))
    {
      dash_list = "\4\4";
    }

  points[0].x = x + line_width / 2;
  points[0].y = y + line_width / 2;
  points[1].x = x + width - line_width + line_width / 2;
  points[1].y = y + line_width / 2;
  points[2].x = x + width - line_width + line_width / 2;
  points[2].y = y + height - line_width + line_width / 2;
  points[3].x = x + line_width / 2;
  points[3].y = y + height - line_width + line_width / 2;
  points[4] = points[0];

  if (!dash_list[0])
    {
      gdk_draw_lines (window, gc, points, 5);
    }
  else
    {
      /* We go through all the pain below because the X rasterization
       * rules don't really work right for dashed lines if you
       * want continuity in segments that go between top/right
       * and left/bottom. For instance, a top left corner
       * with a 1-1 dash is drawn as:
       *
       *  X X X 
       *  X
       *
       *  X
       *
       * This is because pixels on the top and left boundaries
       * of polygons are drawn, but not on the bottom and right.
       * So, if you have a line going up that turns the corner
       * and goes right, there is a one pixel shift in the pattern.
       *
       * So, to fix this, we drawn the top and right in one call,
       * then the left and bottom in another call, fixing up
       * the dash offset for the second call ourselves to get
       * continuity at the upper left.
       *
       * It's not perfect since we really should have a join at
       * the upper left and lower right instead of two intersecting
       * lines but that's only really apparent for no-dashes,
       * which (for this reason) are done as one polygon and
       * don't to through this code path.
       */
      
      dash_len = strlen (dash_list);
      
      if (dash_list[0])
	gdk_gc_set_dashes (gc, 0, dash_list, dash_len);
      
      gdk_draw_lines (window, gc, points, 3);
      
      /* We draw this line one farther over than it is "supposed" to
       * because of another rasterization problem ... if two 1 pixel
       * unjoined lines meet at the lower right, there will be a missing
       * pixel.
       */
      points[2].x += 1;
      
      if (dash_list[0])
	{
	  gint dash_pixels = 0;
	  gint i;
	  
	  /* Adjust the dash offset for the bottom and left so we
	   * match up at the upper left.
	   */
	  for (i = 0; i < dash_len; i++)
	    dash_pixels += dash_list[i];
      
	  if (dash_len % 2 == 1)
	    dash_pixels *= 2;
	  
	  gdk_gc_set_dashes (gc, dash_pixels - (width + height - 2 * line_width) % dash_pixels, dash_list, dash_len);
	}
      
      gdk_draw_lines (window, gc, points + 2, 3);
    }

  gdk_gc_set_line_attributes (gc, 0, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_MITER);

  if (area)
    gdk_gc_set_clip_rectangle (gc, NULL);

  if (free_gc)
    gtk_gc_release(gc);
}

void
smooth_draw_button_default(GtkStyle *style,
                           GdkWindow *window,
                           GtkStateType state_type,
                           GdkRectangle *clip,
                           GdkRectangle *button,
                           GtkWidget *widget,
                           gint x,
                           gint y,
                           gint width,
                           gint height)
{
	GdkRectangle button_area;
	smooth_part_style *button_default=smooth_button_part(style, TRUE);
	
	if (button)
	{
		button_area.x = button->x;
		button_area.y = button->y;
		button_area.width = button->width;
		button_area.height = button->height;
	}
	else
	{
		//if no button area was passed assume the button area is 1 pixel inside, eg. assume there is room for win32 focus
		button_area.x = x+1;
		button_area.y = y+1;
		button_area.width = width+1;
		button_area.height = height+1;
	}
	
	switch (smooth_button_get_style(style, TRUE))
	{
		case SMOOTH_BUTTON_DEFAULT_NORMAL:
		{
			/*paint fill with a gradient, invert if GTK_SHADOW_IN */
			gradient_fill_background(style, window, GTK_SHADOW_IN, clip, widget, button_default, x, y, width, height, TRUE, GTK_ORIENTATION_VERTICAL);

			/* paint shadow */
			smooth_draw_shadow_with_gap(style, window, state_type, GTK_SHADOW_IN, clip, widget, "button", button_default, x, y, width, height, 0, 0, 0);     
		}	
		break;

		case SMOOTH_BUTTON_DEFAULT_NONE:
		case SMOOTH_BUTTON_DEFAULT_TRIANGLE:/* draw the triangle on button draw, not here */
		case SMOOTH_BUTTON_DEFAULT_WIN32:/* draw background first */
		default:
		{
			/*try and paint fill with parent style */
			GtkStyle *parent_style = style;
			GtkStateType parent_state = GTK_STATE_NORMAL;
			
			if ((widget) && (widget->parent)) {
				parent_style = widget->parent->style;
				parent_state = widget->parent->state;
			}

			smooth_fill_background(parent_style, window, parent_state, GTK_SHADOW_NONE, clip, NULL, widget, button_default, x, y, width, height, FALSE, FALSE,
						GTK_ORIENTATION_VERTICAL,FALSE);
		}				
	}	

	if (smooth_button_get_style(style, TRUE) == SMOOTH_BUTTON_DEFAULT_WIN32)
	{
		GdkGC *shade = shaded_color (style, state_type, shades[8]);
		do_draw_shadow_with_gap(window, clip, shade, shade, button_area.x+1, button_area.y+1, button_area.width-2, button_area.height-2, 0, 0, 0, TRUE);
		if (shade) gtk_gc_release (shade);
	}
}

void
smooth_draw_slider(GtkStyle * style,
     	           GdkWindow * window,
	           GtkStateType state_type,
	           GtkShadowType shadow_type,
	           GdkRectangle * area,
	           GtkWidget * widget,
	           detail_char * detail,
	           gint x,
	           gint y,
	           gint width,
	           gint height,
	           GtkOrientation orientation)
{
  SmoothRcStyle *data = NULL;
  smooth_grip_style  *grip;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  data = THEME_DATA(style);
  grip = GRIP_PART(style);

  gradient_fill_background(style, window, state_type, area, widget, THEME_PART(grip), x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);
     
  if ((THEME_PART(grip)->use_line || THEME_PART(grip)->edge.use_line))
    smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(grip), x, y, width, height, 0, 0, 0);
  else  
    gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);

  smooth_draw_slider_grip(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
}

/* This routine is mostly based on the Xenophilia draw_extension & draw_polygon
 * routines, though the LighthouseBlue draw_extension routine, & the XFCE
 * draw_shadow routine were also useful resources.
 */
void
smooth_draw_extension(GtkStyle * style,
   	              GdkWindow * window,
	              GtkStateType state_type,
	              GtkShadowType shadow_type,
	              GdkRectangle * area,
	              GtkWidget * widget,
	              detail_char * detail,
	              gint x,
	              gint y,
	              gint width,
	              gint height,
	              GtkPositionType gap_side)
{
  GtkStateType parent_state;
  GdkPoint	 fill_points[8], edge_points[8];
  GdkRectangle tab_area, draw_area;
  GtkStyle	 *parent_style;
  gint		 x2, y2;
  gboolean	 triangular;
  gint 		 orientation=0, selected=0;
  GtkNotebook *notebook=NULL;
  GdkGC              *shade = NULL;
  GdkGC              *dark=NULL, *light=NULL, *mid=NULL, *midlight=NULL, *middark=NULL;
  gint thickness=0;      
  GdkRectangle        rect;
  SmoothRcStyle *data = NULL;
  smooth_part_style * tab;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
    
  data = THEME_DATA(style); 

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  tab_area.x = x;
  tab_area.y = y;
  tab_area.width = width;
  tab_area.height = height;
	
  if (area) {
    gdk_rectangle_intersect (&tab_area, area, &draw_area);
    area = &draw_area;
  } else {
    area = &tab_area;
  }
	
  if (GTK_IS_NOTEBOOK(widget)) {
    notebook = GTK_NOTEBOOK(widget);
    orientation = notebook->tab_pos;
    selected = (state_type == GTK_STATE_NORMAL);
  }  

  x2 = x + width -1;
  y2 = y + height - !selected;
	  
  tab = smooth_tab_part(style, selected);
  
  switch (smooth_tab_get_style(style,selected))
    {
    case SMOOTH_TAB_NORMAL:
      goto square;
      break;
    case SMOOTH_TAB_ROUND:
      if ((rounded_extension_points(x, y, width, height, selected, TRUE, gap_side, fill_points)) && 
          (rounded_extension_points(x, y, width, height, selected, FALSE, gap_side, edge_points))) 
        goto draw;	    
      else
        return;

      break;   	
    case SMOOTH_TAB_TRIANGLE:
	if ( DETAIL("tab") && widget && GTK_IS_NOTEBOOK(widget)) {
          gint i, t;

          switch (gap_side) {
            case GTK_POS_BOTTOM:
            case GTK_POS_TOP:
	        t = height - 5 + 2;
                i = t / 3;
                if (!(i > 0)) 
                  goto square;
		
                if (notebook->tab_hborder == 2) {
                  gtk_notebook_set_tab_hborder (notebook, i + 2);
                  goto square;
               }
                if (notebook->tab_vborder != 2) {
                  gtk_notebook_set_tab_vborder (notebook, 2);
                  goto square;
               }
               break;               
            case GTK_POS_LEFT:
            case GTK_POS_RIGHT:
	        t = width - 5 + 2;
                i = t / 3;
                if (!(i > 0)) 
                  goto square;
		
                if (notebook->tab_vborder == 2) {
                  gtk_notebook_set_tab_vborder (notebook, i + 2);
                  goto square;
               }
                if (notebook->tab_hborder != 2) {
                  gtk_notebook_set_tab_hborder (notebook, 2);
                  goto square;
               }
               break;
          }
          if ((triangle_extension_points(x, y, width, height, selected, TRUE, gap_side, fill_points)) && 
             (triangle_extension_points(x, y, width, height, selected, FALSE, gap_side, edge_points))) 
            goto draw;	    
          else
            return;
	} else goto square;
      break;
    }
    
    square:
      if ((square_extension_points(x, y, width, height, selected, TRUE, gap_side, fill_points)) && 
          (square_extension_points(x, y, width, height, selected, FALSE, gap_side, edge_points))) 
        goto draw;	    
      else
        return;
    
    draw :	
	parent_style = style;
	parent_state = GTK_STATE_NORMAL;
	if (widget) {
		if (widget->state == GTK_STATE_INSENSITIVE)
			state_type = GTK_STATE_INSENSITIVE;
		
		if (widget->parent) {
			parent_style = widget->parent->style;
			parent_state = widget->parent->state;
		}
	}

        smooth_fill_background(parent_style, window, parent_state, GTK_SHADOW_NONE, area, NULL, widget, tab, x, y, width, height, FALSE, FALSE,
				 GTK_ORIENTATION_VERTICAL,FALSE);
	  
	
	/* draw inner shadow line(s)  */	
	{
	  GdkGC		*gc[3], *use_gc=NULL, *mid_gc=NULL, *bg_gc=style->bg_gc[state_type];
	  gdouble		angle;
	  gint		j,i, x1,y1, x2,y2, xt, yt, mx=0,my=0, sign;
	
          switch (smooth_tab_edge_line_style(style, selected)) {
	    case SMOOTH_LINE_NONE : return;

            case SMOOTH_LINE_THIN :
              dark = darktone_gc(style, state_type);
              light = lighttone_gc(style, state_type);
              gc[0] = light;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = dark;
              break;

            case SMOOTH_LINE_SOFT :
              light = lighttone_gc(style, state_type);
              mid = midtone_gc(style, state_type);
              gc[0] = light;
              gc[1] = light;
              gc[2] = mid;
              gc[3] = mid;
              break;
	    
            case SMOOTH_LINE_BEVELED :
              light = lighttone_gc(style, state_type);
              mid = midtone_gc(style, state_type);
              gc[0] = light;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = dark;
	      thickness = smooth_tab_edge_line_thickness(style, selected) - 1;
              break;
	    
            case SMOOTH_LINE_FLAT :
              dark = darktone_gc(style, state_type);
              gc[0] = dark;
              gc[1] = NULL;
              gc[2] = NULL;
              gc[3] = dark;
              thickness = 1;
              break;

            case SMOOTH_LINE_SMOOTHED :
              dark = darktone_gc(style, state_type);
              light = lighttone_gc(style, state_type);
              mid = midtone_gc(style, state_type);
              gc[0] = mid;
              gc[1] = light;
              gc[2] = mid;
              gc[3] = dark;
              thickness = 1;
              break;

            case SMOOTH_LINE_COLD :
              light = lighttone_gc(style, state_type);
              mid = midtone_gc(style, state_type);
              shade = shaded_color (style, state_type, shades[6]);
              gc[0] = shade;
              gc[1] = light;
              gc[2] = mid;
              gc[3] = shade;
              thickness = 1;
	      break;

            case SMOOTH_LINE_WIN32 :
              dark = darktone_gc(style, state_type);
              light = lighttone_gc(style, state_type);
              shade = shaded_color (style, state_type, shades[8]);
              gc[0] = light;
              gc[1] = style->bg_gc[state_type];
              gc[2] = dark;
              gc[3] = shade;
              thickness = 1;
              break;

            case SMOOTH_LINE_SMOOTHBEVEL :
              dark = darktone_gc(style, state_type);
              light = lighttone_gc(style, state_type);
              midlight = midlighttone_gc(style, state_type);
              middark = middarktone_gc(style, state_type);
  
              gc[0] = midlight;
              gc[1] = light;
              gc[2] = middark;
              gc[3] = dark;
              thickness = 1;
              break;
	    
            default :			 
              dark = darktone_gc(style, state_type);
              light = lighttone_gc(style, state_type);
              mid = midtone_gc(style, state_type);
              gc[0] = mid;
              gc[1] = light;
              gc[2] = dark;
              gc[3] = style->black_gc;
              thickness = 1;
          }
          {
            GdkRegion *cliprgn = gdk_region_polygon(fill_points, 8, GDK_EVEN_ODD_RULE);
            if (area) {
              #ifdef GTK1
              GdkRegion *temp = gdk_region_new();
              GdkRegion *cliprgn2 = gdk_region_union_with_rect(temp, area);

              gdk_region_destroy(temp);

              temp = gdk_regions_intersect(cliprgn, cliprgn2);

              gdk_region_destroy(cliprgn);
              gdk_region_destroy(cliprgn2);

              cliprgn = temp;
//              g_warning("GTK1.2 SPECIFIC CODE STILL IN smooth_draw_extension!!!");
              #endif
              #ifdef GTK2
              GdkRegion *cliprgn2 = gdk_region_rectangle(area);
              gdk_region_intersect(cliprgn, cliprgn2);
              gdk_region_destroy(cliprgn2);
//              g_warning("GTK2 SPECIFIC CODE STILL IN smooth_draw_extension!!!");
              #endif
            }
              
            smooth_fill_background(style, window, state_type, GTK_SHADOW_NONE, NULL, cliprgn, widget, tab, x, y, width, height, FALSE, FALSE,
					 GTK_ORIENTATION_VERTICAL,FALSE);
	    gdk_gc_set_clip_region (bg_gc, NULL);
            gdk_region_destroy(cliprgn);
	  }

	  sign = 0;
	  for (i = thickness; i >= 0; --i) {
	    for (j = 0; j < 7; ++j) {
		x1	= edge_points[j].x;
		y1	= edge_points[j].y;
		x2	= edge_points[j+1].x;
		y2	= edge_points[j+1].y;
			
		if ((x1 == x2) && (y1 == y2)) {
		  angle = 0;
		} else {
		  angle = atan2 (y2 - y1, x2 - x1);
		}
			
		if ((angle > - (M_PI_4 * 3) - 0.0625) && (angle < M_PI_4 - 0.0625)) {
		  if (i!=1) {
		    use_gc = gc[3];
		  } else {
		    use_gc = gc[2];
		  } 
		  mid_gc = use_gc;
		  if (angle > -M_PI_4) {
   	            y1  -= i;
		    y2 -= i;
		  } else {
		    x1  -= i;
		    x2 -= i;
		  }
		  if (sign != 0) {
		    sign = 0;
  		    mx = x1 + i;
  		    if (i!=1) {
		      mid_gc = gc[3];
		    } else {
		      mid_gc = gc[2];
		    } 
		  }
		} else {
		  if (i!=1) {
		    use_gc = gc[0];
		  } else {
     		    use_gc = gc[1];
		  }  
		  mid_gc = use_gc;
		  if ((angle < -(M_PI_4 * 3)) || (angle > (M_PI_4 * 3))) {
   	            y1  += i;
		    y2 += i;
		  } else {
		    x1  += i;
		    x2 += i;
		  }
		  if (sign != 1) {
		    sign = 1;
  		    mx = x1 - i;
  		    if (i!=1) {
		      mid_gc = gc[0];
		    } else {
		      mid_gc = gc[1];
		    } 
		  }
	        }
	        my = y1;
		if (use_gc) {
	  	  if (y2 < y1) {
		    xt = x1; x1 = x2; x2 = xt;
		    yt = y1; y1 = y2; y2 = yt;
	          }
	          gdk_draw_line (window, use_gc, x1, y1, x2, y2);
	        }
		
		if ((j > 0) && (mid_gc) && (mid_gc != use_gc))
		  gdk_draw_point (window, mid_gc, mx, my);
            }
	  }  
	}  
  if (shade) gtk_gc_release (shade);
  if (mid) gtk_gc_release (mid);
  if (light) gtk_gc_release (light);
  if (dark) gtk_gc_release (dark);
  if (middark) gtk_gc_release (middark);
  if (midlight) gtk_gc_release (midlight);
}

void
smooth_draw_box(GtkStyle * style,
	        GdkWindow * window,
	        GtkStateType state_type,
	        GtkShadowType shadow_type,
	        GdkRectangle * area,
	        GtkWidget * widget,
	        detail_char * detail,
	        gint x,
	        gint y,
	        gint width,
	        gint height,
                GtkOrientation orientation)
{
    g_return_if_fail(sanitize_parameters(style, window, &width, &height));

    if (DETAIL("handlebox_bin")) {
      FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
    } else if (DETAIL("menubar")) {
        gint thick = 0;
	gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && IS_BONOBO_DOCK_ITEM(widget));
	if (toolbar_overlap)
	  thick = EDGE_LINE_THICKNESS(style, NULL);
 
        gradient_fill_background(style, window, state_type, area, widget, NULL, -thick, y, x+width+thick, height, TRUE, orientation);
	if (toolbar_overlap)
          smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x-thick, y, x+width+thick, height, GTK_POS_LEFT, 0, height);
        else
	  gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x, y, width, height);
    } else if (DETAIL("toolbar")) {
	gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && (IS_BONOBO_DOCK_ITEM(widget)));

        gboolean horiz=(orientation==GTK_ORIENTATION_HORIZONTAL);
	gboolean vert=(!horiz);
	gint hthick = 0, vthick = 0;
	
	if (toolbar_overlap) {
	  if (horiz)
	    hthick = EDGE_LINE_THICKNESS(style, NULL);
	  else
	    vthick = EDGE_LINE_THICKNESS(style, NULL);  
        }

        FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
	  
	gradient_fill_background(style, window, state_type, area, widget, NULL, x-hthick, y-vthick, width+hthick, height+vthick, TRUE, orientation);
	if (toolbar_overlap)
          smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x-hthick, y-vthick, width+hthick, height+vthick, horiz?GTK_POS_LEFT:GTK_POS_TOP, 0, vert?width:height);
        else
          gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,detail, x-hthick, y-vthick, width+hthick, height+vthick);
    } else if (DETAIL("trough")) {
        if (GTK_IS_SCALE (widget) && REAL_SLIDERS(style)) {
          FLAT_FILL_BACKGROUND(style, window, GTK_STATE_NORMAL, area, widget, NULL, x, y, width, height);
          if GTK_IS_HSCALE (widget) {
	    smooth_draw_line (style, window, state_type, area, widget, detail,
	   	        x, x + width, y + (height / 2), GTK_ORIENTATION_HORIZONTAL);
          } else {
	    smooth_draw_line (style, window, state_type, area, widget, detail,
		        y, y + height, x + (width / 2), GTK_ORIENTATION_VERTICAL);
          }
        } else {
  	  smooth_part_style * trough = THEME_PART(TROUGH_PART(style));
	  gradient_fill_background(style, window, state_type, area, widget, trough, 
	                           x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                           width-PART_XPADDING(trough)*2, height-PART_YPADDING(trough)*2, 
	                           shadow_type == GTK_SHADOW_IN, orientation);

          if (GTK_IS_SCALE(widget) && TROUGH_SHOW_VALUE(style)) {	    
	    GtkAdjustment * adjustment = gtk_range_get_adjustment(GTK_RANGE(widget));
	    gfloat value = 0;
  
            value = gtk_range_get_value(GTK_RANGE(widget));
	    
	    if (orientation == GTK_ORIENTATION_HORIZONTAL) {
              gint w=0;           
              
              if (gtk_range_get_inverted(GTK_RANGE(widget)))
  	        w = (width-PART_XPADDING(trough)*2)*(1-(value- adjustment->lower) / (adjustment->upper - adjustment->lower));
	      else  
  	        w = (width-PART_XPADDING(trough)*2)*((value- adjustment->lower) / (adjustment->upper - adjustment->lower));
	      w = MAX (2, w);
	      w = MIN(w, width-PART_XPADDING(trough)*2);              
              
	      gradient_fill_background(style, window, GTK_STATE_SELECTED, area, widget, trough, 
	                               x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                               w, height-PART_YPADDING(trough)*2, 
	                               shadow_type == GTK_SHADOW_IN, orientation);
            } else {
              gint h;           
              
              if (gtk_range_get_inverted(GTK_RANGE(widget)))
	        h = (height-PART_YPADDING(trough)*2)*((value - adjustment->lower) / (adjustment->upper - adjustment->lower));
	      else  
	        h = (height-PART_YPADDING(trough)*2)*(1-(value - adjustment->lower) / (adjustment->upper - adjustment->lower));

              h = MAX (2, h);
              h = MIN(h, height-PART_YPADDING(trough)*2);
	      
              gradient_fill_background(style, window, GTK_STATE_SELECTED, area, widget, trough, 
	                               x+PART_XPADDING(trough), y+height-PART_YPADDING(trough)-h, 
	                               width-PART_XPADDING(trough)*2, h,
	                               shadow_type == GTK_SHADOW_IN, orientation);
            }
          }
	  
          smooth_draw_shadow_with_gap(style, window, GTK_STATE_NORMAL, shadow_type, area, widget, detail,
	                            trough, x+PART_XPADDING(trough), y+PART_YPADDING(trough), 
	                            width-PART_XPADDING(trough)*2, height-PART_YPADDING(trough)*2, 
				    0, 0, 0);
      }
    } else if (DETAIL("hruler") || DETAIL("vruler") || DETAIL("metacity") || DETAIL("bar") || DETAIL("spinbutton_up") || DETAIL("spinbutton_down") || 
               DETAIL("optionmenu") || DETAIL("optionmenutab") || DETAIL("slider") || DETAIL("menuitem") || 
               DETAIL("togglebutton") || DETAIL("button") || DETAIL ("hscrollbar") || DETAIL ("vscrollbar")) 
    {
 	smooth_part_style * part = NULL;

        /* per widget size/state/shadow adjustments */ 
        if ((EDGE_LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT) && DETAIL("spinbutton_down")) 
          {
            y -= 1;
            height += 1;
          } 
        else if ((shadow_type == GTK_SHADOW_NONE) && (EDGE_LINE_STYLE(style, NULL) != SMOOTH_LINE_NONE) && DETAIL("menuitem"))
	  shadow_type = GTK_SHADOW_OUT;
        else if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar"))
          {
            if (EDGE_LINE_STYLE(style,NULL) == SMOOTH_LINE_FLAT) 
              {
                if (DETAIL ("vscrollbar")) 
                  {
                    if (y < widget->allocation.y + widget->allocation.height/2) {
                        if ((area) && (area->height >= height))
                          area->height = height + 1;
			height +=1;
                    } else 
                      {
                        if ((area) && (area->y <= y))
                          area->y = y - 1;
                        y -= 1; 

                        if ((area) && (area->height >= height))
                          area->height = height + 1;
                        height +=1;
                      }
                  } 
                else 
                  {
                    if (x < widget->allocation.x + widget->allocation.width/2) {
                        if ((area) && (area->width >= width))
                          area->width = width + 1;

                        width +=1;
                    } else 
                      {
                        if ((area) && (area->x <= x))
                          area->x = x - 1;
                        x -= 1; 

                        if ((area) && (area->width >= width))
                          area->width = width + 1;
                        width +=1;
                      }
                  }        
            }
          }
        else if (DETAIL("bar") && GTK_IS_PROGRESS_BAR(widget))
          {
            part = PROGRESS_PART(style);

	    x += PART_XPADDING(part);
            y += PART_YPADDING(part), 
	    width -= PART_XPADDING(part)*2;
            height -= PART_YPADDING(part)*2; 
          } 
        else if (DETAIL("button"))
          {
            part = smooth_button_part(style, FALSE);
          }
        
        /*paint fill of orientation with a gradient, invert if GTK_SHADOW_IN */
        gradient_fill_background(style, window, state_type, area, widget, part, x, y, width, height, shadow_type == GTK_SHADOW_IN, orientation);

        /* per widget special drawing */ 
        if (DETAIL("slider"))
          smooth_draw_slider_grip(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
        else if (DETAIL("optionmenu")) 
          smooth_draw_line (style, window, state_type,
  		  area, widget, detail,
		  y + ythickness(style) + 1,
		  y + height - ythickness(style) - 2,
		  x + width - 19 - xthickness(style), 
                  GTK_ORIENTATION_VERTICAL);
        else if (DETAIL("button") && (smooth_button_default_triangle(style))) {
            /* Paint a triangle here instead of in "buttondefault"
               which is drawn _behind_ the current button */
            draw_default_triangle(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
	}
          
        /* paint shadow */
        smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, part, x, y, width, height, 0, 0, 0);     
    } else {
        FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);
        gtk_paint_shadow(style, window, state_type, shadow_type, area, widget,
                detail, x, y, width, height);
    }
}

void
smooth_draw_box_gap(GtkStyle * style, 
                    GdkWindow * window, 
	            GtkStateType state_type, 
	            GtkShadowType shadow_type, 
	            GdkRectangle * area, 
	            GtkWidget * widget, 
	            detail_char * detail, 
	            gint x, 
	            gint y, 
	            gint width, 
	            gint height, 
	            GtkPositionType gap_side, 
	            gint gap_pos, 
	            gint gap_width)
{
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

  smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width, height, gap_side, gap_pos, gap_width);
}

void
smooth_draw_option(GtkStyle * style,
                   GdkWindow * window,
                   GtkStateType state_type,
                   GtkShadowType shadow_type,
                   GdkRectangle * area,
                   GtkWidget * widget,
                   detail_char *detail,
                   gint x,
                   gint y,
                   gint width,
                   gint height)
{
  smooth_option_style * option;
  smooth_line_style * line_style;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  option = OPTION_PART(style);
  if (THEME_PART(option)->use_line) 
    line_style = &THEME_PART(option)->line;
  else if (EDGE_PART(style)->use_line) 
    line_style = &EDGE_PART(style)->line;
  else  
    line_style = &THEME_DATA(style)->line;

    if (((shadow_type == GTK_SHADOW_IN) || (!OPTION_MOTIF(style))) && (PART_STYLE(option) == NO_OPTION))
      state_type = GTK_STATE_ACTIVE;

      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN) && (line_style->style != SMOOTH_LINE_SOFT))
        {x++; y++; width-=2; height-=2;}     

      smooth_fill_background(style, window, state_type, shadow_type, area, NULL, widget, THEME_PART(option), x, y, width, height, (OPTION_MOTIF(style)), TRUE, GTK_ORIENTATION_VERTICAL, TRUE);
     
      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN) && (line_style->style != SMOOTH_LINE_SOFT))
        {x--; y--; width+=2; height+=2;}

      smooth_draw_shadow_with_gap(style, window, state_type, OPTION_MOTIF(style)?shadow_type:GTK_SHADOW_IN, area, widget, "SMOOTH_DRAW_OPTION", NULL, x, y, width, height, 0, 0, 0);
  
      if ((line_style->style != SMOOTH_LINE_BEVELED) && (line_style->style != SMOOTH_LINE_THIN) && (line_style->style != SMOOTH_LINE_SOFT))
         {x+=2; y+=2; width-=3; height-=3;}
      else
         {x++; y++; width-=2; height-=2;}   
    
    if ((shadow_type == GTK_SHADOW_IN) && (PART_STYLE(option) != NO_OPTION)) {
      
      if (area)
	 gdk_gc_set_clip_rectangle(style->text_gc[state_type], area);
      
      if ((line_style->style != SMOOTH_LINE_FLAT) && (line_style->style != SMOOTH_LINE_NONE))
      {
	gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
	gdk_draw_arc (window, style->text_gc[state_type], FALSE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
      }
      else		      
      { 	
	gdk_draw_arc (window, style->text_gc[state_type], TRUE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
	gdk_draw_arc (window, style->text_gc[state_type], FALSE,
		      x + width / 4,
		      y + height / 4,
		      width / 2, height / 2,
		      0, 360 * 64); 
      }		      

      if (area)
        gdk_gc_set_clip_rectangle(style->text_gc[state_type], NULL);
    }    
}

void
smooth_draw_check(GtkStyle * style,
	          GdkWindow * window,
	          GtkStateType state_type,
	          GtkShadowType shadow_type,
	          GdkRectangle * area,
	          GtkWidget * widget,
	          detail_char * detail,
	          gint x,
	          gint y,
	          gint width,
	          gint height)
{  
  smooth_check_style * check;
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  check = CHECK_PART(style);
  
  if GTK_IS_CHECK_MENU_ITEM(widget) {
    x -= 2;
    y -= 2;
    width += 4;
    height += 4;
  }
  
  if (!((GTK_IS_CHECK_MENU_ITEM(widget) && (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_NONE)))) {
    if ((shadow_type == GTK_SHADOW_IN) && (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_BEVELED) &&
       (PART_STYLE(check) == NO_CHECK))
    {
      state_type = GTK_STATE_ACTIVE;
    }   
    if (CHECK_MOTIF(style)) 
      gradient_fill_background(style, window, state_type, area, widget, THEME_PART(check), x, y, width, height, FALSE, GTK_ORIENTATION_HORIZONTAL);
    else
      gdk_draw_rectangle(window, style->base_gc[state_type], TRUE, x, y, width, height);		     
  }


  if (shadow_type == GTK_SHADOW_IN)
  {
     gint thick = EDGE_LINE_THICKNESS(style, check);
     if (EDGE_LINE_STYLE(style, check) == SMOOTH_LINE_COLD) thick = 1;

     draw_check_mark(window, style->text_gc[state_type], area, x+thick, y+thick, width-thick*2, height-thick*2, PART_STYLE(check));
  }

  if (!CHECK_MOTIF(style))
    shadow_type = GTK_SHADOW_IN;
  
  if (THEME_PART(check)->use_line || THEME_PART(check)->edge.use_line)
    smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(check), x, y, width, height, 0, 0, 0);
  else  
    gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

void
smooth_draw_diamond(GtkStyle * style,
	            GdkWindow * window,
	            GtkStateType state_type,
	            GtkShadowType shadow_type,
	            GdkRectangle * area,
	            GtkWidget * widget,
	            detail_char * detail,
	            gint x,
	            gint y,
	            gint width,
	            gint height)
{
  GdkGC *light=NULL, *dark=NULL;

  gint                half_width;
  gint                half_height;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  half_width = width / 2;
  half_height = height / 2;

  switch (shadow_type)
    {
    case GTK_SHADOW_IN:
    {
      light = lighttone_gc(style, state_type);

      if (light) {
        if (area) gdk_gc_set_clip_rectangle(light, area);
        
        gdk_draw_line(window, light,
		    x + 2, y + half_height,
		    x + half_width, y + height - 2);
        gdk_draw_line(window, light,
		    x + half_width, y + height - 2,
		    x + width - 2, y + half_height);
        gdk_draw_line(window, light,
		    x + 1, y + half_height,
		    x + half_width, y + height - 1);
        gdk_draw_line(window, light,
		    x + half_width, y + height - 1,
		    x + width - 1, y + half_height);
        gdk_draw_line(window, light,
		    x, y + half_height,
		    x + half_width, y + height);
        gdk_draw_line(window, light,
		    x + half_width, y + height,
		    x + width, y + half_height);

        if (area) gdk_gc_set_clip_rectangle(light, NULL);

        gtk_gc_release (light);
      }

      dark = darktone_gc(style, state_type);

      if (dark) {
        if (area) gdk_gc_set_clip_rectangle(dark, area);
        
        gdk_draw_line(window, dark,
		    x + 2, y + half_height,
		    x + half_width, y + 2);
        gdk_draw_line(window, dark,
		    x + half_width, y + 2,
  		    x + width - 2, y + half_height);
        gdk_draw_line(window, dark,
		    x + 1, y + half_height,
		    x + half_width, y + 1);
        gdk_draw_line(window, dark,
		    x + half_width, y + 1,
		    x + width - 1, y + half_height);
        gdk_draw_line(window, dark,
		    x, y + half_height,
		    x + half_width, y);
        gdk_draw_line(window, dark,
		    x + half_width, y,
		    x + width, y + half_height);

        if (area) gdk_gc_set_clip_rectangle(dark, NULL);

        gtk_gc_release (dark);
      }

      break;
    }  
    case GTK_SHADOW_OUT:
    {
      dark = darktone_gc(style, state_type);

      if (dark) {
        if (area) gdk_gc_set_clip_rectangle(dark, area);
        
        gdk_draw_line(window, dark,
		    x + 2, y + half_height,
		    x + half_width, y + height - 2);
        gdk_draw_line(window, dark,
		    x + half_width, y + height - 2,
		    x + width - 2, y + half_height);
        gdk_draw_line(window, dark,
		    x + 1, y + half_height,
		    x + half_width, y + height - 1);
        gdk_draw_line(window, dark,
		    x + half_width, y + height - 1,
  		    x + width - 1, y + half_height);
        gdk_draw_line(window, dark,
		    x, y + half_height,
		    x + half_width, y + height);
        gdk_draw_line(window, dark,
		    x + half_width, y + height,
		    x + width, y + half_height);

        if (area) gdk_gc_set_clip_rectangle(dark, NULL);

        gtk_gc_release (dark);
      }

      light = lighttone_gc(style, state_type);

      if (light) {
        if (area) gdk_gc_set_clip_rectangle(light, area);
        
        gdk_draw_line(window, light,
		    x + 2, y + half_height,
		    x + half_width, y + 2);
        gdk_draw_line(window, light,
		    x + half_width, y + 2,
		    x + width - 2, y + half_height);
        gdk_draw_line(window, light,
		    x + 1, y + half_height,
		    x + half_width, y + 1);
        gdk_draw_line(window, light,
		    x + half_width, y + 1,
		    x + width - 1, y + half_height);
        gdk_draw_line(window, light,
		    x, y + half_height,
		    x + half_width, y);
        gdk_draw_line(window, light,
  		    x + half_width, y,
		    x + width, y + half_height);

        if (area) gdk_gc_set_clip_rectangle(light, NULL);

        gtk_gc_release (light);
      }

      break;
    }  
    default:
      return;
    }
}
