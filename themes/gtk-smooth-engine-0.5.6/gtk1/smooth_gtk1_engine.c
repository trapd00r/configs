#include <gmodule.h>
#include "../smooth_rc_style.h"
#include "../smooth_style.h"
#include "gtk1_patches.h"

/* The following function will be called by GTK+ when the module
 * is loaded and checks to see if we are compatible with the
 * version of GTK+ that loads us.
*/
G_MODULE_EXPORT const gchar *g_module_check_init (GModule * module);

const gchar *

g_module_check_init (GModule * module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}

/* Style Function Overrides */

static void
draw_shadow(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  smooth_draw_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height,  GTK_POS_RIGHT);
}

static void
draw_hline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   gint x1,
	   gint x2,
	   gint y)
{
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  smooth_draw_line(style, window, state_type, area, widget, detail, x1, x2, y, GTK_ORIENTATION_HORIZONTAL);
}


static void
draw_vline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   detail_char * detail,
	   gint y1,
	   gint y2,
	   gint x)
{
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  smooth_draw_line(style, window, state_type, area, widget, detail, y1, y2, x, GTK_ORIENTATION_VERTICAL);
}

static void
draw_polygon(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

  smooth_draw_polygon(style, window, state_type, shadow_type, area, widget, detail, points, npoints, fill);
}

static void
draw_arrow(GtkStyle * style,
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
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  if (DETAIL ("hscrollbar") || DETAIL ("vscrollbar") || 
      DETAIL("spinbutton_up") || DETAIL("spinbutton_down"))
  {	 
    gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
  }  
  
  reverse_engineer_arrow_box (widget, detail, arrow_type, &x, &y, &width, &height);

  x+=ARROW_XPADDING(style); 
  y+=ARROW_YPADDING(style); 
  width-=2*ARROW_XPADDING(style); 
  height-=2*ARROW_YPADDING(style);

  smooth_draw_arrow(style, window, state_type, shadow_type, area, widget, detail, arrow_type, fill, x, y, width, height);
}


static void
draw_focus(GtkStyle *style,
           GdkWindow *window,
           GdkRectangle *area,
           GtkWidget *widget,
           detail_char *detail,
           gint x,
           gint y,
           gint width,
           gint height)
{
  GtkStateType state_type = GTK_STATE_NORMAL;
  gboolean free_dash_list = FALSE;
  gint line_width = 1;
  gint8 *dash_list = NULL;
  gint dash_len;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  if (widget)
    state_type = GTK_WIDGET_STATE(widget);
 
  smooth_draw_focus(style, window, state_type, area, widget, detail, x, y, width, height, dash_list, line_width);
  
  if (free_dash_list)
    g_free (dash_list);
}

static void
draw_slider(GtkStyle * style,
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

  smooth_draw_slider(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
}

static void
draw_extension(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  smooth_draw_extension(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side);
}

static void
draw_box(GtkStyle * style,
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
  GtkOrientation orientation;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  if (DETAIL("buttondefault") || DETAIL("togglebutton") || DETAIL("button") || DETAIL("spinbutton_up") || DETAIL("spinbutton_down") || GTK_IS_BUTTON(widget))
    orientation = GTK_ORIENTATION_HORIZONTAL;
  else if (DETAIL("hscrollbar"))
    orientation = GTK_ORIENTATION_HORIZONTAL;
  else if (DETAIL("vscrollbar"))
    orientation = GTK_ORIENTATION_VERTICAL;
  else if (DETAIL("menubar") || DETAIL("menuitem") || DETAIL("optionmenu") || DETAIL("optionmenutab") || DETAIL("metacity"))
    orientation = GTK_ORIENTATION_HORIZONTAL;
  else if (DETAIL("hruler"))
    orientation = GTK_ORIENTATION_HORIZONTAL;
  else if (DETAIL("vruler"))
    orientation = GTK_ORIENTATION_VERTICAL;
  else if (GTK_IS_PROGRESS_BAR(widget)) 
    {
      switch (GTK_PROGRESS_BAR(widget)->orientation) {
	case GTK_PROGRESS_LEFT_TO_RIGHT:
        case GTK_PROGRESS_RIGHT_TO_LEFT:
          orientation = GTK_ORIENTATION_HORIZONTAL;
	  break;
	case GTK_PROGRESS_BOTTOM_TO_TOP:
        case GTK_PROGRESS_TOP_TO_BOTTOM:
          orientation = GTK_ORIENTATION_VERTICAL;
          break;
      }   
    }  
  else if (GTK_IS_SCROLLBAR(widget)) 
    orientation = (GTK_IS_VSCROLLBAR(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;
  else if (GTK_IS_SCALE(widget))
    orientation = (GTK_IS_VSCALE(widget))?GTK_ORIENTATION_VERTICAL:GTK_ORIENTATION_HORIZONTAL;
  else if (height > width)
    orientation = GTK_ORIENTATION_VERTICAL;
  else
    orientation = GTK_ORIENTATION_HORIZONTAL;     

  smooth_draw_box(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, orientation);
}

static void
draw_box_gap (GtkStyle * style, 
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
  
  smooth_draw_box_gap(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side, gap_pos-1, gap_width+1);
}

static void
draw_shadow_gap (GtkStyle * style, 
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
  
  smooth_draw_box_gap(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height, gap_side, gap_pos, gap_width);
}

static void
draw_option(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  smooth_draw_option(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

static void
draw_check(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  smooth_draw_check(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

static void
draw_diamond(GtkStyle * style,
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
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  smooth_draw_diamond(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height);
}

static void
draw_handle(GtkStyle * style,
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
    GdkGC              *light_gc, *dark_gc;
    GdkRectangle        dest;
    smooth_grip_style  *grip;
    gint ax=x, ay=y, aw=width, ah=height;
    gboolean toolbar_overlap = (GRIP_OVERLAP_TOOLBAR(style) && (DETAIL("dockitem")));
    gboolean horiz=(width<height);
    gint gap_size=(horiz)?y+height:x+width;
    gboolean vert=(!horiz);
    g_return_if_fail(sanitize_parameters(style, window, &width, &height));

    aw=width; ah=height;
     
    grip = GRIP_PART(style);
    
    if (!GTK_IS_PANED(widget)) {
      gint thick = 0;
      if (toolbar_overlap)
	thick = EDGE_LINE_THICKNESS(style, NULL)*2;
      gradient_fill_background(style, window, state_type, area, widget, THEME_PART(grip), x, y, width+thick*horiz, height+thick*vert, shadow_type == GTK_SHADOW_IN, orientation);
    } else  {
      FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, THEME_PART(grip), x, y, width, height);
    }
    switch (PART_STYLE(grip)) {
      case NO_GRIP:
        break;
      case BARS_IN_GRIP :
      case BARS_OUT_GRIP :
        {
          gint w=width, h=height;
		
          if (vert) {
	     if (DETAIL("handlebox")) {
               h+=1;
               gap_size=x+width;
	     }else
	     if (DETAIL("dockitem")) {
	       h+=1;
	       orientation = GTK_ORIENTATION_HORIZONTAL;
             } else 
	     {
               h+=1;
	       y-=1;
	       w = MIN(width+1, width/7 + height);
   	       x = x + (width - w)/2;
	     }
          } else {
	     if (DETAIL("handlebox")) {
              w+=1;
              gap_size=y+height;
              orientation = GTK_ORIENTATION_VERTICAL;
	     }else
	     if (DETAIL("dockitem")) {
               w+=1;
	       orientation = GTK_ORIENTATION_VERTICAL;
	     } else {
               w+=1;
	       x-=1;
	       h = MIN(height+1, width + height/7);
   	       y = y + (height - h)/2;
	     }
          }
		
          width = w;
          height = h;
        }
	break;
      case LINES_IN_GRIP :
      case LINES_OUT_GRIP :
        {
          gint w=width, h=height;
		
          if (vert) {
	     w+=1;
	     h = MIN(height+1, width + height/7);
	     y = y + (height - h)/2;
             if ((GTK_IS_PANED(widget)) || (GTK_IS_RANGE(widget))) orientation = GTK_ORIENTATION_HORIZONTAL;
	     if (!GRIP_OVERLAP_TOOLBAR(style) && DETAIL("dockitem")) y -=1;
          } else {
	     w = MIN(width+1, width/7 + height);
	     x = x + (width - w)/2;
	     if ((GTK_IS_PANED(widget)) || (GTK_IS_RANGE(widget))) orientation = GTK_ORIENTATION_VERTICAL;
	     if (!GRIP_OVERLAP_TOOLBAR(style) && DETAIL("dockitem")) x -=1;
          }
		
          if (DETAIL("dockitem") || DETAIL("handlebox"))
	    orientation = GTK_ORIENTATION_VERTICAL;
          break;

          width = w;
          height = h;
        }
	break;
      case SLASHES_GRIP:
	x -= 2;
	y -= 2;
	width += 4;
	height += 4;	
	break;
      case DOTS_OUT_GRIP:
      case DOTS_IN_GRIP:
      case SMALLDOTS_IN_GRIP :
      case SMALLDOTS_OUT_GRIP :
        if (DETAIL("dockitem") || DETAIL("handlebox"))
	  orientation = GTK_ORIENTATION_VERTICAL;
        break;
      case FIXEDLINES_OUT_GRIP:
      case FIXEDLINES_IN_GRIP:
        if (DETAIL("dockitem") || DETAIL("handlebox"))
	  orientation = GTK_ORIENTATION_VERTICAL;
        break;
      case MAC_BUDS_IN_GRIP:
      case MAC_BUDS_OUT_GRIP:
      case NS_BUDS_IN_GRIP:
      case NS_BUDS_OUT_GRIP:
	x += 3;
	y += 3;
	width -= 4;
	height -= 6;
        orientation = GTK_ORIENTATION_VERTICAL;
        break;
     }

    smooth_draw_grip(style, window, state_type, area, x+PART_XPADDING(grip), y+PART_YPADDING(grip), width-PART_XPADDING(grip)*2, height-PART_YPADDING(grip)*2, orientation);      

    switch (PART_STYLE(grip)) {
      case BARS_IN_GRIP :
      case BARS_OUT_GRIP :
      case LINES_IN_GRIP :
      case LINES_OUT_GRIP :
        x=ax; 
	y=ay; 
	width=aw; 
	height=ah;
	break;
	
      case SLASHES_GRIP:
	x += 2;
	y += 2;
	width -= 4;
	height -= 4;	
	break;
	
      case MAC_BUDS_IN_GRIP:
      case MAC_BUDS_OUT_GRIP:
      case NS_BUDS_IN_GRIP:
      case NS_BUDS_OUT_GRIP:
        x -= 3;
        y -= 3;
	width += 4;
	height += 6;
	break;
    }

  if ((THEME_PART(grip)->use_line || THEME_PART(grip)->edge.use_line)) {
    gint thick = 0;

    if (toolbar_overlap)
      thick = EDGE_LINE_THICKNESS(style, grip)*2;
    else
      gap_size = 0;    

    smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, THEME_PART(grip), x, y, width+horiz*thick, height+vert*thick, vert?GTK_POS_BOTTOM:GTK_POS_RIGHT, 0, gap_size);
  } else  {
    gint thick = 0;

    if (toolbar_overlap)
      thick = EDGE_LINE_THICKNESS(style, NULL)*2;
    else
      gap_size = 0;    
      
    smooth_draw_shadow_with_gap(style, window, state_type, shadow_type, area, widget, detail, NULL, x, y, width+horiz*thick, height+vert*thick, vert?GTK_POS_BOTTOM:GTK_POS_RIGHT, 0, gap_size);
  }
}

static void draw_cross (GtkStyle * style,
			GdkWindow * window,
			GtkStateType state_type,
			GtkShadowType shadow_type,
			GdkRectangle * area,
			GtkWidget * widget,
			gchar * detail,
			gint x, gint y, gint width, gint height)
{}

static void draw_ramp (GtkStyle * style,
		       GdkWindow * window,
		       GtkStateType state_type,
		       GtkShadowType shadow_type,
		       GdkRectangle * area,
		       GtkWidget * widget,
		       gchar * detail,
		       GtkArrowType arrow_type,
		       gint x, gint y, gint width, gint height)
{}


static void
draw_oval(GtkStyle * style,
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
{}

static void
draw_tab(GtkStyle * style,
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
#define ARROW_SPACE 4

  GtkRequisition indicator_size;
  gint arrow_height,arrow_width;
  gboolean solid = SOLID_ARROW(style);
  GdkGC * border_gc = style->fg_gc[state_type], * fill_gc = style->fg_gc[state_type];
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  alternate = ARROW_STYLE(style);

  if ((!solid))
    fill_gc = style->base_gc[state_type];
      
  arrow_height = height - 2;
  arrow_width = width - 2;
  x = widget->allocation.width - 20;
  y = 0;
  x += (19 - arrow_width) / 2;
  y += (widget->allocation.height - (2 * arrow_height + ARROW_SPACE)) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
     solid=TRUE;
     border_gc = style->dark_gc[state_type];
     fill_gc = style->dark_gc[state_type];
     do_draw_arrow(window, area, GTK_ARROW_UP, style->light_gc[state_type], style->light_gc[state_type], x+1, y+1, arrow_width, arrow_height, alternate); 
     do_draw_arrow(window, area, GTK_ARROW_DOWN, style->light_gc[state_type], style->light_gc[state_type], x+1, y + arrow_height + ARROW_SPACE + 1, indicator_size.width, arrow_height, alternate); 
    }
  
  do_draw_arrow(window, area, GTK_ARROW_UP, fill_gc, border_gc, x, y, arrow_width, arrow_height, alternate); 
  do_draw_arrow(window, area, GTK_ARROW_DOWN, fill_gc, border_gc, x, y + arrow_height + ARROW_SPACE, arrow_width, arrow_height, alternate); 
}

static void draw_string (GtkStyle * style,
			 GdkWindow * window,
			 GtkStateType state_type,
			 GdkRectangle * area,
			 GtkWidget * widget,
			 detail_char * detail,
			 gint x, gint y, 
			 const gchar * string)
{
  g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], area);
  }
  if (state_type == GTK_STATE_INSENSITIVE) {
    gdk_draw_string (window, style->font, style->light_gc[state_type], x + 1, y + 1,
		     string);
    gdk_draw_string (window, style->font, style->dark_gc[state_type], x, y,
	  	    string);
  } else {
    gdk_draw_string (window, style->font, style->fg_gc[state_type], x, y,
		   string);
  }  
  if (area) {
    gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], NULL);
  }
}

static void 
draw_flat_box (GtkStyle * style,
               GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       gchar * detail,
	       gint x, gint y, gint width, gint height)
{
   GdkGC *gc1;
 
   g_return_if_fail(sanitize_parameters(style, window, NULL, NULL));

   if (DETAIL("text") && (state_type == GTK_STATE_SELECTED))
     gc1 = style->bg_gc[state_type];
   else if (DETAIL("viewportbin"))
     gc1 = style->bg_gc[state_type];
   else if (DETAIL("entry_bg"))
     gc1 = style->base_gc[state_type];
   else 
     gc1 = style->bg_gc[state_type];
   
   if ((!style->bg_pixmap[state_type]) || (gc1 != style->bg_gc[state_type]) ||
     (gdk_window_get_type(window) == GDK_WINDOW_PIXMAP)) 
   {
     if (area) gdk_gc_set_clip_rectangle (gc1, area);
     gdk_draw_rectangle(window, gc1, TRUE, x, y, width, height);
     if (area) gdk_gc_set_clip_rectangle (gc1, NULL);
   } else {
     FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

     if (DETAIL("tooltip")) {
       if (area) gdk_gc_set_clip_rectangle (style->black_gc, area);
       gdk_draw_rectangle(window, style->black_gc, FALSE, x, y, width - 1, height - 1);
       if (area) gdk_gc_set_clip_rectangle (style->black_gc, NULL);
     }  
   }
   g_return_if_fail(sanitize_parameters(style, window, &width, &height));
}

GtkStyleClass smooth_default_class = {
  2,
  2,
  draw_hline,
  draw_vline,
  draw_shadow,
  draw_polygon,
  draw_arrow,
  draw_diamond,
  draw_oval,
  draw_string,
  draw_box,
  draw_flat_box,
  draw_check,
  draw_option,
  draw_cross,
  draw_ramp,
  draw_tab,
  draw_shadow_gap,
  draw_box_gap,
  draw_extension,
  draw_focus,
  draw_slider,
  draw_handle
};


/* Theme Style Function Overrides */

extern GtkStyleClass smooth_default_class;

void
smooth_style_duplicate (GtkStyle * dest, GtkStyle * src)
{
  SmoothRcStyle *dest_data = NEW_THEME_DATA(dest); 
  
  dest_data->refcount = 1;
  dest->klass = &smooth_default_class;
  smooth_rc_style_init(dest_data);
  SET_THEME_DATA(dest, dest_data);
}

void
smooth_style_realize (GtkStyle * style)
{
}

void
smooth_style_unrealize (GtkStyle * style)
{
}

static void
theme_data_ref (SmoothRcStyle * theme_data)
{
  if (theme_data) theme_data->refcount++;
}

static void
theme_data_unref (SmoothRcStyle * theme_data)
{
  if (theme_data) theme_data->refcount--;
  if ((theme_data) && (theme_data->refcount == 0)) {
    g_free (theme_data);
    theme_data = NULL;
  }  
}

static void
smooth_rc_style_destroy (GtkRcStyle * rc_style)
{
  theme_data_unref (SMOOTH_RC_DATA(rc_style));
}

static void
smooth_style_destroy (GtkStyle * style)
{
  theme_data_unref (THEME_DATA(style));
}

static void
smooth_rc_style_to_style(GtkStyle * style, 
                         GtkRcStyle * rc_style)
{
  SmoothRcStyle *data = SMOOTH_RC_DATA(rc_style);

  style->klass = &smooth_default_class;
  style->engine_data = data;
  
  if (data->xthickness >= 0)
  style->klass->xthickness = data->xthickness;

  if (data->ythickness >= 0)
  style->klass->ythickness = data->ythickness;
  
  theme_data_ref (data);
}

static void
theme_set_background (GtkStyle * style,
		      GdkWindow * window, 
		      GtkStateType state_type)
{
  GdkPixmap *pixmap;
  gint parent_relative;

  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if (style->bg_pixmap[state_type]) {
    if (style->bg_pixmap[state_type] == (GdkPixmap *) GDK_PARENT_RELATIVE) {
      pixmap = NULL;
      parent_relative = TRUE;
    } else {
      pixmap = style->bg_pixmap[state_type];
      parent_relative = FALSE;
    }

    gdk_window_set_back_pixmap (window, pixmap, parent_relative);
  } else {
    gdk_window_set_background (window, &style->bg[state_type]);
  }
}

/* Main Theme Functions */

G_MODULE_EXPORT void
theme_init (GtkThemeEngine * engine)
{
  gdk_rgb_init();
  engine->parse_rc_style = smooth_rc_style_parse;
  engine->merge_rc_style = smooth_rc_style_merge;
  engine->rc_style_to_style = smooth_rc_style_to_style;
  engine->duplicate_style = smooth_style_duplicate;
  engine->realize_style = smooth_style_realize;
  engine->unrealize_style = smooth_style_unrealize;
  engine->destroy_rc_style = smooth_rc_style_destroy;
  engine->destroy_style = smooth_style_destroy;
  engine->set_background = theme_set_background;

  patches_install();
}

G_MODULE_EXPORT void
theme_exit (void)
{
  patches_uninstall();
  cleanup_gdk_pixbuf_cache(TRUE);
}
