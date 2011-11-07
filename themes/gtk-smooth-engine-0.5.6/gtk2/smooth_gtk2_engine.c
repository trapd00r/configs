#include <gmodule.h>
#include "../smooth_rc_style.h"
#include "../smooth_style.h"

/* Main Theme Functions */

G_MODULE_EXPORT void
theme_init (GTypeModule *module)
{
  smooth_rc_style_register_type (module);
  smooth_style_register_type (module);
}

G_MODULE_EXPORT void
theme_exit (void)
{
  cleanup_gdk_pixbuf_cache(TRUE);
}

G_MODULE_EXPORT GtkRcStyle *
theme_create_rc_style (void)
{
  void *ptr;
  
  ptr = GTK_RC_STYLE (g_object_new (SMOOTH_TYPE_RC_STYLE, NULL));  
  return (GtkRcStyle *)ptr;
}

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

  if (!(widget) || (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_LTR)) 
    smooth_draw_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height,  GTK_POS_RIGHT);
  else   
    smooth_draw_shadow(style, window, state_type, shadow_type, area, widget, detail, x, y, width, height,  GTK_POS_LEFT);
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
           GtkStateType state_type,
           GdkRectangle *area,
           GtkWidget *widget,
           detail_char *detail,
           gint x,
           gint y,
           gint width,
           gint height)
{
  gboolean free_dash_list = FALSE;
  gint line_width = 1;
  gint8 *dash_list = NULL;
  gint dash_len;

  g_return_if_fail(sanitize_parameters(style, window, &width, &height));

  if (widget)
    {
      if (FOCUS_USE_PATTERN(style, state_type))
        gtk_widget_style_get (widget,
			      "focus-line-width", &line_width,
			      NULL);
      else {
        gtk_widget_style_get (widget,
	  		      "focus-line-width", &line_width,
			      "focus-line-pattern", (gchar *)&dash_list,
			      NULL);

        free_dash_list = TRUE;
      }  
  }
  
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

static const GtkBorder default_default_border = { 1, 1, 1, 1 };
static const GtkBorder default_default_outside_border = { 0, 0, 0, 0 };

static void
gtk_button_get_props (GtkWidget *widget,
		      GtkBorder *default_border,
		      GtkBorder *default_outside_border,
		      gboolean  *interior_focus)
{
  GtkBorder *tmp_border;

  if (default_border)
    {
      gtk_widget_style_get (widget, "default_border", &tmp_border, NULL);

      if (tmp_border)
	{
	  *default_border = *tmp_border;
	  g_free (tmp_border);
	}
      else
	*default_border = default_default_border;
    }

  if (default_outside_border)
    {
      gtk_widget_style_get (widget, "default_outside_border", &tmp_border, NULL);

      if (tmp_border)
	{
	  *default_outside_border = *tmp_border;
	  g_free (tmp_border);
	}
      else
	*default_outside_border = default_default_outside_border;
    }

  if (interior_focus)
    gtk_widget_style_get (widget, "interior_focus", interior_focus, NULL);
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
    
	if (DETAIL("buttondefault"))
	{
		GdkRectangle button;

		gint border_width = GTK_CONTAINER (widget)->border_width;
		GtkBorder default_border;
		GtkBorder default_outside_border;
		gboolean interior_focus;
		gint focus_width;
		gint focus_pad;

		gtk_button_get_props (widget, &default_border, &default_outside_border, &interior_focus);
		gtk_widget_style_get (widget,
					"focus-line-width", &focus_width,
					"focus-padding", &focus_pad,
					NULL); 
	
		button.x = widget->allocation.x + border_width + default_outside_border.left;
		button.y = widget->allocation.y + border_width + default_outside_border.top;
		button.width = (widget->allocation.width - border_width * 2) - (default_outside_border.left + default_outside_border.right);
		button.height = (widget->allocation.height - border_width * 2) - (default_outside_border.top + default_outside_border.bottom);

		if (!interior_focus)
		{
			button.x += focus_width + focus_pad;
			button.y += focus_width + focus_pad;
			button.width -= 2 * (focus_width + focus_pad);
			button.height -= 2 * (focus_width + focus_pad);
		}

		smooth_draw_button_default(style, window, state_type, area, &button, widget, x, y, width, height);

		return;
	}	

  if (DETAIL("togglebutton") || DETAIL("button") || DETAIL("spinbutton_up") || DETAIL("spinbutton_down") || GTK_IS_BUTTON(widget))
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
    gboolean horiz=(DETAIL("handlebox") || (DETAIL("dockitem") && !IS_HANDLE_BOX_ITEM(widget)))?(orientation==GTK_ORIENTATION_HORIZONTAL):(orientation==GTK_ORIENTATION_VERTICAL);
    gint gap_size=(!horiz)?y+height:x+width;
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
	        w+=1;
	        h = MIN(height+1, width + height/7);
   	        y = y + (height - h)/2;
	        orientation = GTK_ORIENTATION_HORIZONTAL;
	        if (!toolbar_overlap) y -=1;
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
               h+=1;
	       w = MIN(width+1, width/7 + height);
   	       x = x + (width - w)/2;
	       orientation = GTK_ORIENTATION_VERTICAL;
               if (!toolbar_overlap) x -=1;
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

static void make_square(gint * value1, gint * value2) 
{ 
  if (*value1 < *value2) 
    *value2 = *value1;
}

static void make_square_offset(gint * value1, gint * value2, gint * value3) 
{ 
  if (*value1 < *value2) 
  {
    *value3 += (*value1 - *value2);
    *value2 = *value1;
  }
}
   
static void
draw_resize_grip (GtkStyle       *style,
                              GdkWindow      *window,
                              GtkStateType    state_type,
                              GdkRectangle   *area,
                              GtkWidget      *widget,
                              const gchar    *detail,
                              GdkWindowEdge   edge,
                              gint            x,
                              gint            y,
                              gint            width,
                              gint            height)
{
  g_return_if_fail (GTK_IS_STYLE (style));
  g_return_if_fail (window != NULL);
  
  if (widget && GTK_IS_STATUSBAR(widget) && !RESIZE_GRIP(style)) {
    gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(widget), FALSE);
    return;
  }
    
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], area);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);
    }
  
  switch (edge)
    {
    case GDK_WINDOW_EDGE_WEST:
    case GDK_WINDOW_EDGE_EAST:
      {
	gint xi;

        if (edge==GDK_WINDOW_EDGE_WEST) 
          make_square(&height, &width); 
        else 
          make_square_offset(&height, &width, &x);
	
	xi = x;

	while (xi < x + width)
	  {
	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   xi, y,
			   xi, y + height);

	    xi++;
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   xi, y + height);

	    xi += 2;
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH:
    case GDK_WINDOW_EDGE_SOUTH:
      {
	gint yi;

        if (edge==GDK_WINDOW_EDGE_NORTH) 
          make_square(&width, &height); 
        else 
          make_square_offset(&width, &height, &y);

	yi = y;

	while (yi < y + height)
	  {
	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   x, yi,
			   x + width, yi);

	    yi++;
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   x + width, yi);

	    yi+= 2;
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH_WEST:
      {
	gint xi, yi;

        make_square(&width, &height);
        make_square(&height, &width);
	
	xi = x + width;
	yi = y + height;

	while (xi > x + 3)
	  {
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   x, yi);

	    --xi;
	    --yi;

	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   xi, y,
			   x, yi);

	    --xi;
	    --yi;

	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   xi, y,
			   x, yi);

	    xi -= 3;
	    yi -= 3;
	    
	  }
      }
      break;
    case GDK_WINDOW_EDGE_NORTH_EAST:
      {
        gint xi, yi;

        make_square(&width, &height);
        make_square_offset(&height, &width, &x);

        xi = x;
        yi = y + height;

        while (xi < (x + width - 3))
          {
            gdk_draw_line (window,
                           style->light_gc[state_type],
                           xi, y,
                           x + width, yi);                           

            ++xi;
            --yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y,
                           x + width, yi);                           

            ++xi;
            --yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y,
                           x + width, yi);

            xi += 3;
            yi -= 3;
          }
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_WEST:
      {
	gint xi, yi;

        make_square_offset(&width, &height, &y);
        make_square(&height, &width);
	
	xi = x + width;
	yi = y;

	while (xi > x + 3)
	  {
	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   xi, y + height);

	    --xi;
	    ++yi;

	    gdk_draw_line (window,
			   style->dark_gc[state_type],
			   x, yi,
			   xi, y + height);

	    --xi;
	    ++yi;

	    gdk_draw_line (window,
			   style->light_gc[state_type],
			   x, yi,
			   xi, y + height);

	    xi -= 3;
	    yi += 3;
	    
	  }
      }
      break;
    case GDK_WINDOW_EDGE_SOUTH_EAST:
      {
        gint xi, yi;

        make_square_offset(&width, &height, &y);
        make_square_offset(&height, &width, &x);
     
        xi = x;
        yi = y;

        while (xi < (x + width - 3))
          {
            gdk_draw_line (window,
                           style->light_gc[state_type],
                           xi, y + height,
                           x + width, yi);                           

            ++xi;
            ++yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y + height,
                           x + width, yi);                           

            ++xi;
            ++yi;
            
            gdk_draw_line (window,
                           style->dark_gc[state_type],
                           xi, y + height,
                           x + width, yi);

            xi += 3;
            yi += 3;
          }
      }
      break;
    default:
      return;
      break;
    }
  
  if (area)
    {
      gdk_gc_set_clip_rectangle (style->light_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->dark_gc[state_type], NULL);
      gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    }
}

static const GtkRequisition default_option_indicator_size = { 7, 13 };
static const GtkBorder default_option_indicator_spacing = { 7, 5, 2, 2 };

static void
option_menu_get_props (GtkWidget      *widget,
		       GtkRequisition *indicator_size,
		       GtkBorder      *indicator_spacing)
{
  GtkRequisition *tmp_size = NULL;
  GtkBorder *tmp_spacing = NULL;
  
  if (widget)
    gtk_widget_style_get (widget, 
			  "indicator_size", &tmp_size,
			  "indicator_spacing", &tmp_spacing,
			  NULL);

  if (tmp_size)
    {
      *indicator_size = *tmp_size;
      g_free (tmp_size);
    }
  else
    *indicator_size = default_option_indicator_size;

  if (tmp_spacing)
    {
      *indicator_spacing = *tmp_spacing;
      g_free (tmp_spacing);
    }
  else
    *indicator_spacing = default_option_indicator_spacing;
}

static void
draw_tab (GtkStyle      *style,
		      GdkWindow     *window,
		      GtkStateType   state_type,
		      GtkShadowType  shadow_type,
		      GdkRectangle  *area,
		      GtkWidget     *widget,
		      const gchar   *detail,
		      gint           x,
		      gint           y,
		      gint           width,
		      gint           height)
{
#define ARROW_SPACE 0

  GtkRequisition indicator_size;
  GtkBorder indicator_spacing;
  gint arrow_height;
  gboolean solid = SOLID_ARROW(style);
  GdkGC * border_gc = style->fg_gc[state_type], * fill_gc = style->fg_gc[state_type];
  gint alternate;
  
  g_return_if_fail(sanitize_parameters(style, window, &width, &height));
  
  alternate = ARROW_STYLE(style);

  if ((!solid))
    fill_gc = style->base_gc[state_type];
      
  option_menu_get_props (widget, &indicator_size, &indicator_spacing);

  indicator_size.width += 2;
  arrow_height = indicator_size.width;

  x += (width - indicator_size.width) / 2;
  y += (height - (2 * arrow_height + ARROW_SPACE)) / 2;

  if (state_type == GTK_STATE_INSENSITIVE)
    {
     solid=TRUE;
     border_gc = style->dark_gc[state_type];
     fill_gc = style->dark_gc[state_type];
     do_draw_arrow(window, area, GTK_ARROW_UP, style->light_gc[state_type], style->light_gc[state_type], x+1, y+1, indicator_size.width, arrow_height, alternate); 
     do_draw_arrow(window, area, GTK_ARROW_DOWN, style->light_gc[state_type], style->light_gc[state_type], x+1, y + arrow_height + ARROW_SPACE + 1, indicator_size.width, arrow_height, alternate); 
    }
  
  do_draw_arrow(window, area, GTK_ARROW_UP, fill_gc, border_gc, x, y, indicator_size.width, arrow_height, alternate); 
  do_draw_arrow(window, area, GTK_ARROW_DOWN, fill_gc, border_gc, x, y + arrow_height + ARROW_SPACE, indicator_size.width, arrow_height, alternate); 
}

static void 
draw_flat_box (GtkStyle * style,
               GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       const gchar * detail,
	       gint x, gint y, gint width, gint height)
{
   g_return_if_fail(sanitize_parameters(style, window, &width, &height));

   /* we always want call to the default for treeviews and such */  
 
   if ((DETAIL("text")) || (DETAIL("viewportbin")) || (DETAIL("entry_bg")) || ((DETAIL("cell_even")) || 
      (DETAIL("cell_odd")) || (DETAIL("cell_even_ruled")) || (DETAIL("cell_odd_ruled")) || (DETAIL("cell_even_sorted")) ||
      (DETAIL("cell_odd_sorted")) || (DETAIL("cell_even_ruled_sorted")) || (DETAIL("cell_odd_ruled_sorted"))))
   {
     parent_class->draw_flat_box (style, window, state_type, shadow_type,
			          area, widget, detail, x, y, width, height);
  
   } else {
     FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, NULL, x, y, width, height);

     if (DETAIL("tooltip")) 
       gdk_draw_rectangle(window, style->dark_gc[state_type], FALSE, x, y, width - 1, height - 1);
   }
}                                             

static void
smooth_style_class_init (SmoothStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;

  style_class->draw_polygon = draw_polygon;
  style_class->draw_diamond = draw_diamond;

  style_class->draw_box = draw_box;
  style_class->draw_flat_box = draw_flat_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;

  style_class->draw_focus = draw_focus;

  style_class->draw_arrow = draw_arrow;
  style_class->draw_resize_grip = draw_resize_grip;
}

GType smooth_type_style = 0;

void
smooth_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (SmoothStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) smooth_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (SmoothStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) NULL,
  };
  
  smooth_type_style = g_type_module_register_type (module,
							   GTK_TYPE_STYLE,
							   "SmoothStyle",
							   &object_info, 0);
}
