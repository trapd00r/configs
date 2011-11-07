#include <stdlib.h>		/* for alloca() */
#include <stddef.h>		/* for offsetof() */
#include <string.h>
#include <stdio.h>

#include "../smooth_rc_style.h"
#include "gtk1_patches.h"

/* Patch control */
static void patch_install (GtkObjectClass *klass, size_t offset,
								GtkFunction func, GtkFunction * old_func_ptr);
static void patch_restore (GtkObjectClass *klass, size_t offset,
								GtkFunction func, GtkFunction old_func);

/* Patches */
static void _scale_size_request(GtkWidget *, GtkRequisition *);
static void _scale_size_allocate(GtkWidget *, GtkAllocation *);

static void _scale_slider_update (GtkRange *);

static gint _scale_expose_event(GtkWidget *, GdkEventExpose *);
static void _scale_draw_focus (GtkWidget *);

static void _vscale_size_allocate(GtkWidget *, GtkAllocation *);
static void _hscale_size_allocate(GtkWidget *, GtkAllocation *);
static void _vscale_size_request(GtkWidget *, GtkRequisition *);
static void _hscale_size_request(GtkWidget *, GtkRequisition *);
static void _vscale_draw_trough (GtkRange *);
static void _hscale_draw_trough (GtkRange *);
static void _vscale_draw_slider (GtkRange *);
static void _hscale_draw_slider (GtkRange *);

static void _scrollbar_size_request(GtkWidget *, GtkRequisition *);

static void _hscrollbar_slider_update (GtkRange *range);
static void _hscrollbar_realize (GtkWidget *);
static void _hscrollbar_size_request(GtkWidget *, GtkRequisition *);
static void _hscrollbar_size_allocate(GtkWidget *, GtkAllocation *);

static void _vscrollbar_slider_update (GtkRange *range);
static void _vscrollbar_realize (GtkWidget *);
static void _vscrollbar_size_request(GtkWidget *, GtkRequisition *);
static void _vscrollbar_size_allocate(GtkWidget *, GtkAllocation *);

static void _paned_expose_event (GtkWidget *, GdkEventExpose *);
static void _paned_draw (GtkWidget *, GdkRectangle *);

static gint _paned_button_press_event (GtkWidget *, GdkEventButton *);
static gint _paned_button_release_event (GtkWidget *, GdkEventButton *);
static gint _paned_motion_notify_event (GtkWidget *, GdkEventMotion *);

static void _vpaned_realize (GtkWidget *);
static void _hpaned_realize (GtkWidget *);
static void _vpaned_size_allocate(GtkWidget *, GtkAllocation *);
static void _hpaned_size_allocate(GtkWidget *, GtkAllocation *);

static gint _vpaned_enter_notify_event (GtkWidget *, GdkEventCrossing *);
static gint _hpaned_enter_notify_event (GtkWidget *, GdkEventCrossing *);
static gint _vpaned_leave_notify_event (GtkWidget *, GdkEventCrossing *);
static gint _hpaned_leave_notify_event (GtkWidget *, GdkEventCrossing *);

static void _spin_button_size_allocate (GtkWidget *, GtkAllocation *);
static void _spin_button_changed (GtkEditable *);
static void _spin_button_realize (GtkWidget *);
static gint _spin_button_button_press_event (GtkWidget *, GdkEventButton *);

static void _check_button_draw_indicator(GtkCheckButton *, GdkRectangle *);
static void _check_button_draw (GtkWidget *, GdkRectangle *);
static gint _check_button_expose_event (GtkWidget *, GdkEventExpose *);

static void _radio_button_draw_indicator(GtkCheckButton *, GdkRectangle *);

static void _menu_item_draw (GtkWidget *, GdkRectangle *);
static gint _menu_item_expose_event (GtkWidget *, GdkEventExpose *);

/*
 *	Original (or previous) functions and values
 */
static void (* old_paned_expose_event)(GtkWidget *, GdkEventExpose *);
static void (* old_paned_draw) (GtkWidget *, GdkRectangle *);

static gint (* old_paned_button_press_event) (GtkWidget *, GdkEventButton *);
static gint (* old_paned_button_release_event) (GtkWidget *, GdkEventButton *);
static gint (* old_paned_motion_notify_event) (GtkWidget *, GdkEventMotion *);

static void (* old_vpaned_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_hpaned_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_vpaned_realize)(GtkWidget *);
static void (* old_hpaned_realize)(GtkWidget *);

static gint (* old_vpaned_enter_notify_event)(GtkWidget *, GdkEventCrossing *);
static gint (* old_hpaned_enter_notify_event)(GtkWidget *, GdkEventCrossing *);
static gint (* old_vpaned_leave_notify_event)(GtkWidget *, GdkEventCrossing *);
static gint (* old_hpaned_leave_notify_event)(GtkWidget *, GdkEventCrossing *);

static gint (* old_scale_expose_event)(GtkWidget *, GdkEventExpose *);
static void (* old_scale_draw_focus)(GtkWidget *);
static void (* old_scale_slider_update) (GtkRange *range);

static void (* old_hscale_draw_trough)(GtkRange *);
static void (* old_hscale_draw_slider)(GtkRange *);
static void (* old_hscale_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_hscale_size_request)(GtkWidget *, GtkRequisition *);

static void (* old_vscale_draw_trough)(GtkRange *);
static void (* old_vscale_draw_slider)(GtkRange *);
static void (* old_vscale_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_vscale_size_request)(GtkWidget *, GtkRequisition *);


static void (* old_hscrollbar_slider_update) (GtkRange *);
static void (* old_hscrollbar_realize)(GtkWidget *);
static void (* old_hscrollbar_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_hscrollbar_size_request)(GtkWidget *, GtkRequisition *);

static void (* old_vscrollbar_slider_update) (GtkRange *);
static void (* old_vscrollbar_realize)(GtkWidget *);
static void (* old_vscrollbar_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_vscrollbar_size_request)(GtkWidget *, GtkRequisition *);

static void (* old_spin_button_size_allocate)(GtkWidget *, GtkAllocation *);
static void (* old_spin_button_changed)(GtkEditable *);
static void (* old_spin_button_realize)(GtkWidget *);
static gint (* old_spin_button_button_press_event)(GtkWidget *, GdkEventButton *);

static void (* old_check_button_draw_indicator)(GtkCheckButton *, GdkRectangle *);
static void (* old_check_button_draw) (GtkWidget *, GdkRectangle *);
static gint (* old_check_button_expose_event)(GtkWidget *, GdkEventExpose *);
static void (* old_radio_button_draw_indicator)(GtkCheckButton *, GdkRectangle *);

static void (* old_menu_item_draw) (GtkWidget *, GdkRectangle *);
static gint (* old_menu_item_expose_event) (GtkWidget *, GdkEventExpose *);

static GtkWidgetClass * spin_button_parent_class = NULL;

static gint old_scrollbar_spacing;

static gint patch_count = 0;

/*
	Install and Remove
*/

#define PATCH_INSTALL(klass, type, name, field) \
	patch_install ((GtkObjectClass *)klass, offsetof(type, field), \
						(GtkFunction) _ ## name ## _ ## field, (GtkFunction *) &old_ ## name ## _ ## field)

#define PATCH_RESTORE(klass, type, name, field) \
	patch_restore ((GtkObjectClass *)klass, offsetof(type, field), \
						(GtkFunction) _ ## name ## _ ## field, (GtkFunction) old_ ## name ## _ ## field)

/* remember what is patched */

guint16 patch_config	= PATCH_DEFAULT;

void patches_install () {
	GtkWidgetClass	*widget_class;
	const char *config, *token;
	int n, mod, invert;
	
	/* Test if we should install patches */
	if (patch_count++ != 0)
		return;
	
	/* Make entire panes sensitive */
	if (patch_config & PATCH_PANED) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vpaned_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, expose_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, draw);

		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, button_press_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, button_release_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, motion_notify_event);		

		PATCH_INSTALL(widget_class, GtkWidgetClass, vpaned, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vpaned, realize);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vpaned, enter_notify_event);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vpaned, leave_notify_event);
		
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hpaned_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, expose_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, draw);

		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, button_press_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, button_release_event);		
		PATCH_INSTALL(widget_class, GtkWidgetClass, paned, motion_notify_event);		

		PATCH_INSTALL(widget_class, GtkWidgetClass, hpaned, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hpaned, realize);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hpaned, enter_notify_event);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hpaned, leave_notify_event);
	}

	/* Draw sliders differently */
	if (patch_config & PATCH_SCALE) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hscale_get_type());
		PATCH_INSTALL(widget_class, GtkRangeClass, hscale, draw_trough);
		PATCH_INSTALL(widget_class, GtkRangeClass, hscale, draw_slider);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hscale, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hscale, size_request);

		PATCH_INSTALL(widget_class, GtkRangeClass, scale, slider_update);

		PATCH_INSTALL(widget_class, GtkWidgetClass, scale, expose_event);
		PATCH_INSTALL(widget_class, GtkWidgetClass, scale, draw_focus);
		
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vscale_get_type());
		PATCH_INSTALL(widget_class, GtkRangeClass, vscale, draw_trough);
		PATCH_INSTALL(widget_class, GtkRangeClass, vscale, draw_slider);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vscale, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vscale, size_request);

		PATCH_INSTALL(widget_class, GtkRangeClass, scale, slider_update);

		PATCH_INSTALL(widget_class, GtkWidgetClass, scale, expose_event);
		PATCH_INSTALL(widget_class, GtkWidgetClass, scale, draw_focus);
	}
	
	/* GtkScrollbar */
	if (patch_config & PATCH_SCROLLBAR) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hscrollbar_get_type());
		PATCH_INSTALL(widget_class, GtkRangeClass, hscrollbar, slider_update);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hscrollbar, realize);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hscrollbar, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, hscrollbar, size_request);

		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vscrollbar_get_type());
		PATCH_INSTALL(widget_class, GtkRangeClass, vscrollbar, slider_update);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vscrollbar, realize);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vscrollbar, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, vscrollbar, size_request);
	}

	/* GtkSpinButton */
	if (patch_config & PATCH_SPIN_BUTTON) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_spin_button_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, spin_button, size_allocate);
		PATCH_INSTALL(widget_class, GtkWidgetClass, spin_button, realize);
		PATCH_INSTALL(widget_class, GtkEditableClass, spin_button, changed);
		PATCH_INSTALL(widget_class, GtkWidgetClass, spin_button, button_press_event);
		spin_button_parent_class = GTK_WIDGET_CLASS(gtk_type_parent_class(gtk_spin_button_get_type()));
	}

	/* GtkCheckButton */
	if (patch_config & PATCH_CHECK_BUTTON) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_check_button_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, check_button, draw);
		PATCH_INSTALL(widget_class, GtkWidgetClass, check_button, expose_event);
		PATCH_INSTALL(widget_class, GtkCheckButtonClass, check_button, draw_indicator);

		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_radio_button_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, check_button, draw);
		PATCH_INSTALL(widget_class, GtkWidgetClass, check_button, expose_event);
		PATCH_INSTALL(widget_class, GtkCheckButtonClass, radio_button, draw_indicator);
	}

	/* GtkMenuItem */
	if (patch_config & PATCH_MENU_ITEM) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_menu_item_get_type());
		PATCH_INSTALL(widget_class, GtkWidgetClass, menu_item, draw);
		PATCH_INSTALL(widget_class, GtkWidgetClass, menu_item, expose_event);
	}
}


void patches_uninstall () {
	GtkWidgetClass	*widget_class;
	
	if (patch_count == 0)
		return;
	
	patch_count = 0;

	/* GtkMenuItem */
	if (patch_config & PATCH_MENU_ITEM) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_menu_item_get_type());
		PATCH_RESTORE(widget_class, GtkWidgetClass, menu_item, draw);
		PATCH_RESTORE(widget_class, GtkWidgetClass, menu_item, expose_event);
	}

	/* GtkSpinButton */
	if (patch_config & PATCH_SPIN_BUTTON) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_spin_button_get_type());
		PATCH_RESTORE(widget_class, GtkWidgetClass, spin_button, button_press_event);
		PATCH_RESTORE(widget_class, GtkEditableClass, spin_button, changed);
		PATCH_RESTORE(widget_class, GtkWidgetClass, spin_button, realize);
		PATCH_RESTORE(widget_class, GtkWidgetClass, spin_button, size_allocate);
	}

	/* GtkCheckButton */
	if (patch_config & PATCH_CHECK_BUTTON) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_check_button_get_type());
		PATCH_RESTORE(widget_class, GtkCheckButtonClass, check_button, draw_indicator);
		PATCH_RESTORE(widget_class, GtkWidgetClass, check_button, draw);
		PATCH_RESTORE(widget_class, GtkWidgetClass, check_button, expose_event);

		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_radio_button_get_type());
		PATCH_RESTORE(widget_class, GtkCheckButtonClass, radio_button, draw_indicator);
		PATCH_RESTORE(widget_class, GtkWidgetClass, check_button, draw);
		PATCH_RESTORE(widget_class, GtkWidgetClass, check_button, expose_event);
	}

	/* GtkVScale, GtkHScale */
	if (patch_config & PATCH_SCALE) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hscale_get_type());
		PATCH_RESTORE(widget_class, GtkRangeClass, hscale, draw_trough);
		PATCH_RESTORE(widget_class, GtkRangeClass, hscale, draw_slider);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hscale, size_allocate);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hscale, size_request);

		PATCH_RESTORE(widget_class, GtkRangeClass, scale, slider_update);

		PATCH_RESTORE(widget_class, GtkWidgetClass, scale, expose_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, scale, draw_focus);
		
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vscale_get_type());
		PATCH_RESTORE(widget_class, GtkRangeClass, vscale, draw_trough);
		PATCH_RESTORE(widget_class, GtkRangeClass, vscale, draw_slider);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vscale, size_allocate);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vscale, size_request);

		PATCH_RESTORE(widget_class, GtkRangeClass, scale, slider_update);

		PATCH_RESTORE(widget_class, GtkWidgetClass, scale, expose_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, scale, draw_focus);
	}

	/* GtkScrollbar */
	if (patch_config & PATCH_SCROLLBAR) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hscrollbar_get_type());
		PATCH_RESTORE(widget_class, GtkRangeClass, hscrollbar, slider_update);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hscrollbar, realize);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hscrollbar, size_allocate);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hscrollbar, size_request);

		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vscrollbar_get_type());
		PATCH_RESTORE(widget_class, GtkRangeClass, vscrollbar, slider_update);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vscrollbar, realize);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vscrollbar, size_allocate);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vscrollbar, size_request);
	}

	/* GtkVPaned, GtkHPaned.. they suck btw, use my new paned table class and be happy!
	   You can find it at <http://www.obsession.se/johan/gtk.html>.
	*/
	if (patch_config & PATCH_PANED) {
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_hpaned_get_type());
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, expose_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, draw);

		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, button_press_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, button_release_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, motion_notify_event);		

		PATCH_RESTORE(widget_class, GtkWidgetClass, hpaned, leave_notify_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hpaned, enter_notify_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hpaned, realize);
		PATCH_RESTORE(widget_class, GtkWidgetClass, hpaned, size_allocate);
	
		widget_class = (GtkWidgetClass *)gtk_type_class(gtk_vpaned_get_type());
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, expose_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, draw);

		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, button_press_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, button_release_event);		
		PATCH_RESTORE(widget_class, GtkWidgetClass, paned, motion_notify_event);		

		PATCH_RESTORE(widget_class, GtkWidgetClass, vpaned, leave_notify_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vpaned, enter_notify_event);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vpaned, realize);
		PATCH_RESTORE(widget_class, GtkWidgetClass, vpaned, size_allocate);
	}
}



/*
 *	Patch Control
 */
void patch_install (GtkObjectClass *klass, size_t offset,
						 GtkFunction func, GtkFunction * old_func_ptr)
{
	GtkFunction	*ptr;
	
	ptr = (GtkFunction *)((guchar *)klass + offset);
	
	*old_func_ptr = *ptr;
	if (*ptr == func) {
	}
	
	*ptr = func;
}


void patch_restore (GtkObjectClass *klass, size_t offset,
						 GtkFunction func, GtkFunction old_func)
{
	GList		*child;
	GtkFunction	*ptr;

	ptr = (GtkFunction *)((guchar *)klass + offset);
	if (*ptr == func)
		*ptr = old_func;

	for (child = gtk_type_children_types(klass->type); child; child = child->next)
		patch_restore (gtk_type_class(GPOINTER_TO_UINT(child->data)),
							offset, func, old_func);
}


/*
 * Patched functions
 */
#define RANGE_CLASS(widget) \
	GTK_RANGE_CLASS(GTK_OBJECT(widget)->klass)

/* Panes */

static void _paned_expose_event (GtkWidget *widget, GdkEventExpose *event)
{
  GtkPaned *paned = GTK_PANED (widget);
  gboolean handle_full_size = _gtk_paned_is_handle_full_size (paned);
  GdkEventExpose child_event;
  
  if (GTK_WIDGET_DRAWABLE (widget))
    {
      /* An expose event for the handle */
      if (event->window == paned->handle)
	{
          GtkStateType state_type;
          GtkOrientation orientation;
          gint mouse_x, mouse_y, handle_w, handle_h;
	  gint x=0,y=0,width, height;
	  gchar *detail;
	  
          detail = GTK_IS_HPANED (widget) ? "hpaned" : "vpaned";

	  state_type = GTK_WIDGET_STATE(widget);
          		
          if ((PANED_HANDLE_SIZE(widget->style) > 2) && (paned->handle_size != PANED_HANDLE_SIZE(widget->style))) {
            gtk_paned_set_gutter_size(paned, PANED_HANDLE_SIZE(widget->style));
            gtk_paned_set_handle_size(paned, PANED_HANDLE_SIZE(widget->style));
          }

	  gdk_window_get_size (paned->handle, &width, &height);
          gdk_window_get_pointer (paned->handle, &mouse_x, &mouse_y, NULL);
          gdk_window_get_size (paned->handle, &handle_w, &handle_h);
      

         if GTK_IS_VPANED(widget) {
            orientation = GTK_ORIENTATION_HORIZONTAL;
	    y -= 3;
	    height += 6;
          } else {
            orientation = GTK_ORIENTATION_VERTICAL;
	    x -= 3;
	    width += 6;
          }
      	
          if (paned->in_drag)
            state_type = GTK_STATE_PRELIGHT;
          else
            if ((mouse_x >= 0) && (mouse_x < handle_w) && (mouse_y >= 0) && (mouse_y < handle_h))
              state_type = GTK_STATE_PRELIGHT;
                
          state_type = ((GTK_WIDGET_STATE(widget)==GTK_STATE_INSENSITIVE)?GTK_STATE_INSENSITIVE:state_type);
          
          gtk_paint_handle(widget->style, paned->handle, state_type, GTK_SHADOW_NONE, &event->area, widget, detail, x, y, width, height, orientation);     
	}
      else
	{
	  child_event = *event;
	  if (paned->child1 &&
	      GTK_WIDGET_NO_WINDOW (paned->child1) &&
	      gtk_widget_intersect (paned->child1, &event->area, &child_event.area))
	    gtk_widget_event (paned->child1, (GdkEvent*) &child_event);
	  
	  if (paned->child2 &&
	      GTK_WIDGET_NO_WINDOW (paned->child2) &&
	      gtk_widget_intersect (paned->child2, &event->area, &child_event.area))
	    gtk_widget_event (paned->child2, (GdkEvent*) &child_event);
	  
	  /* redraw the groove if necessary */
	  if (gdk_rectangle_intersect (&paned->groove_rectangle, 
				       &event->area, 
				       &child_event.area))
	    gtk_widget_draw (widget, &child_event.area);
	}
    }
}

static void _paned_draw (GtkWidget *widget, GdkRectangle *area)
{
  GtkPaned *paned = GTK_PANED (widget);
  GdkRectangle handle_area, child_area;
  guint16 border_width;
  gboolean handle_full_size = _gtk_paned_is_handle_full_size (paned);

  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_PANED (widget));

  if (GTK_WIDGET_VISIBLE (widget) && GTK_WIDGET_MAPPED (widget))
    {
      gint width, height;
      
      border_width = GTK_CONTAINER (paned)->border_width;

      gdk_window_clear_area (widget->window,
			     area->x, area->y, area->width, area->height);

      /* Redraw the handle
       */
      gdk_window_get_size (paned->handle, &width, &height);
      
      handle_area.x = paned->handle_xpos;
      handle_area.y = paned->handle_ypos;
      handle_area.width = width;
      handle_area.height = height;

      if (gdk_rectangle_intersect (&handle_area, area, &child_area))
	{
          GtkStateType state_type;
          GtkOrientation orientation;
          gint mouse_x, mouse_y, handle_w, handle_h;
	  gint x=0,y=0,width, height;
	  gchar *detail;
	  
          detail = GTK_IS_HPANED (widget) ? "hpaned" : "vpaned";
	    
	  state_type = GTK_WIDGET_STATE(widget);
          		
          if ((PANED_HANDLE_SIZE(widget->style) > 2) && (paned->handle_size != PANED_HANDLE_SIZE(widget->style))) {
            gtk_paned_set_gutter_size(paned, PANED_HANDLE_SIZE(widget->style));
            gtk_paned_set_handle_size(paned, PANED_HANDLE_SIZE(widget->style));
          }

	  gdk_window_get_size (paned->handle, &width, &height);
          gdk_window_get_pointer (paned->handle, &mouse_x, &mouse_y, NULL);
          gdk_window_get_size (paned->handle, &handle_w, &handle_h);
      

         if GTK_IS_VPANED(widget) {
            orientation = GTK_ORIENTATION_HORIZONTAL;
	    y -= 3;
	    height += 6;
          } else {
            orientation = GTK_ORIENTATION_VERTICAL;
	    x -= 3;
	    width += 6;
          }
      	
          if (paned->in_drag)
            state_type = GTK_STATE_PRELIGHT;
          else
            if ((mouse_x >= 0) && (mouse_x < handle_w) && (mouse_y >= 0) && (mouse_y < handle_h))
              state_type = GTK_STATE_PRELIGHT;
                
          state_type = ((GTK_WIDGET_STATE(widget)==GTK_STATE_INSENSITIVE)?GTK_STATE_INSENSITIVE:state_type);
          
          gtk_paint_handle(widget->style, paned->handle, state_type, GTK_SHADOW_NONE, NULL, widget, detail, x, y, width, height, orientation);     
	}

      /* Redraw the children
       */
      if (paned->child1 &&
	  gtk_widget_intersect (paned->child1, area, &child_area))
        gtk_widget_draw (paned->child1, &child_area);
      if (paned->child2 &&
	  gtk_widget_intersect (paned->child2, area, &child_area))
        gtk_widget_draw (paned->child2, &child_area);
    }
}

static gint _paned_button_press_event(GtkWidget *widget, GdkEventButton *event)
{
  GtkPaned *paned = GTK_PANED (widget);
  gint gutter_size = _gtk_paned_get_gutter_size (paned);

  if (!paned->in_drag &&
      (event->window == paned->handle) && (event->button == 1))
    {
      paned->in_drag = TRUE;
      paned->child1_size += event->x - paned->handle_size / 2;
      paned->child1_size = CLAMP (paned->child1_size, 0,
                                  widget->allocation.width - gutter_size
                                  - 2 * GTK_CONTAINER (paned)->border_width);
    }

  return TRUE;
}

static gint _paned_button_release_event (GtkWidget *widget, GdkEventButton *event)
{
  GtkPaned *paned;

  g_return_val_if_fail (widget != NULL,FALSE);
  g_return_val_if_fail (GTK_IS_PANED (widget),FALSE);

  paned = GTK_PANED (widget);

  if (paned->in_drag && (event->button == 1))
    {
      paned->in_drag = FALSE;
      paned->position_set = TRUE;
    }

  return TRUE;
}

static gint _paned_motion_notify_event (GtkWidget *widget, GdkEventMotion *event)
{
  GtkPaned *paned;
  gint x;

  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_PANED (widget), FALSE);

  paned = GTK_PANED (widget);

  if (event->is_hint || event->window != widget->window)
    gtk_widget_get_pointer(widget, &x, NULL);
  else
    x = event->x;

  if (paned->in_drag)
    {
      gint size = x - GTK_CONTAINER (paned)->border_width - _gtk_paned_get_gutter_size (paned) / 2;
      
      if (paned->child1_size != CLAMP (size, paned->min_position, paned->max_position))
      {
        paned->child1_size = CLAMP (size,
	  			    paned->min_position,
				    paned->max_position);

        gtk_widget_queue_resize (GTK_WIDGET (paned));
      }  
    }

  return TRUE;
}

static void 
_hpaned_realize (GtkWidget *widget) {
	GdkCursor *crsr;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_HPANED(widget));

	old_hpaned_realize(widget);
		crsr = gdk_cursor_new(GDK_SB_H_DOUBLE_ARROW);
		gdk_window_set_cursor(GTK_PANED(widget)->handle, crsr);
		gdk_cursor_destroy(crsr);
		gdk_window_set_events(GTK_PANED(widget)->handle,
							    gdk_window_get_events(GTK_PANED(widget)->handle)
							  | GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
		_hpaned_size_allocate (widget, &(widget->allocation));
}

static void 
_hpaned_size_allocate (GtkWidget *widget, GtkAllocation *allocation) {
	GtkPaned	*paned;
	gint		x, width, bw;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_HPANED(widget));

		paned = ((GtkPaned*)widget);
		paned->handle_size = paned->gutter_size;
	
		old_hpaned_size_allocate (widget, allocation);
		if (GTK_WIDGET_REALIZED(widget)) {
			gdk_window_get_geometry(paned->handle, &x, NULL, &width, NULL, NULL);
			bw = ((GtkContainer *)widget)->border_width;
			gdk_window_move_resize (paned->handle,
									x + (paned->handle_size - 6)/2,
									bw,
									6,
									widget->allocation.height - bw - bw);
		}
		gtk_widget_queue_draw(widget);
}

static void _vpaned_realize (GtkWidget *widget) {
	GdkCursor *crsr;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_VPANED(widget));

	old_vpaned_realize(widget);
		crsr = gdk_cursor_new(GDK_SB_V_DOUBLE_ARROW);
		gdk_window_set_cursor(GTK_PANED(widget)->handle, crsr);
		gdk_cursor_destroy(crsr);
		gdk_window_set_events(GTK_PANED(widget)->handle,
							    gdk_window_get_events(GTK_PANED(widget)->handle)
							  | GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
		_vpaned_size_allocate (widget, &(widget->allocation));
}

static void 
_vpaned_size_allocate (GtkWidget *widget, GtkAllocation *allocation) {
	GtkPaned	*paned;
	gint		y, height, bw;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_VPANED(widget));

		paned = ((GtkPaned*)widget);
		paned->handle_size = paned->gutter_size;
	
		old_vpaned_size_allocate (widget, allocation);
		if (GTK_WIDGET_REALIZED(widget)) {
			gdk_window_get_geometry(paned->handle, NULL, &y, NULL, &height, NULL);
			bw = ((GtkContainer *)widget)->border_width;
			gdk_window_move_resize (paned->handle,
									bw,
									y + (paned->handle_size - 6)/2,
									widget->allocation.width - bw - bw,
									6);
		}
		gtk_widget_queue_draw(widget);
}

static void paned_fake_event (GtkWidget *widget) {
	GdkEventExpose event;
	gint width, height;
	
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_PANED(widget));
	
	event.type = GDK_EXPOSE;
	event.send_event = 1;
	event.window = GTK_PANED(widget)->handle;
	gdk_window_get_size (event.window, &width, &height);
	event.area.x = event.area.y = 0;
	event.area.width = width;
	event.area.height = height;
	event.count = 0;
	
	gdk_event_put ((GdkEvent *)&event);
}

static gint 
_vpaned_enter_notify_event (GtkWidget *widget, GdkEventCrossing *event) {
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_VPANED(widget), FALSE);
	
	paned_fake_event(widget);
	return TRUE;
}

static gint 
_vpaned_leave_notify_event (GtkWidget *widget, GdkEventCrossing *event) {
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_VPANED(widget), FALSE);
	
	paned_fake_event(widget);
	return TRUE;
}

static gint 
_hpaned_enter_notify_event (GtkWidget *widget, GdkEventCrossing *event) {
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_HPANED(widget), FALSE);

	paned_fake_event(widget);
	return TRUE;
}

static gint 
_hpaned_leave_notify_event (GtkWidget *widget, GdkEventCrossing *event) {
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_HPANED(widget), FALSE);
	
	paned_fake_event(widget);
	return TRUE;
}

/* GtkScale */
static void _range_trough_hdims (GtkRange *range,
			gint     *left,
			gint     *right)
{
  GtkWidget *widget;

  gint trough_width;
  gint slider_length;
  gint tmp_width;
  gint tleft;
  gint tright;
  gint stepper_spacing;
  gint trough_border;

  g_return_if_fail (range != NULL);

  gdk_window_get_size (range->trough, &trough_width, NULL);
  gdk_window_get_size (range->slider, &slider_length, NULL);

  widget = GTK_WIDGET (range);

  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
  }
  
  tleft = trough_border;
  tright = trough_width - slider_length - trough_border;

  if (range->step_back)
    {
      gdk_window_get_size (range->step_back, &tmp_width, NULL);
      tleft += (tmp_width + stepper_spacing);
    }

  if (range->step_forw)
    {
      gdk_window_get_size (range->step_forw, &tmp_width, NULL);
      tright -= (tmp_width + stepper_spacing);
    }

  if (left)
    *left = tleft;
  if (right)
    *right = tright;
}

static void _range_trough_vdims (GtkRange *range,
			gint     *top,
			gint     *bottom)
{
  GtkWidget *widget;

  gint trough_height;
  gint slider_length;
  gint tmp_height;
  gint ttop;
  gint tbottom;
  gint trough_border;
  gint stepper_spacing;

  g_return_if_fail (range != NULL);

  widget = GTK_WIDGET (range);

  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
  }
    
  gdk_window_get_size (range->trough, NULL, &trough_height);
  gdk_window_get_size (range->slider, NULL, &slider_length);

  ttop = trough_border;
  tbottom = trough_height - slider_length - trough_border;

  if (range->step_back)
    {
      gdk_window_get_size (range->step_back, NULL, &tmp_height);
      ttop += (tmp_height + stepper_spacing);
    }

  if (range->step_forw)
    {
      gdk_window_get_size (range->step_forw, NULL, &tmp_height);
      tbottom -= (tmp_height + stepper_spacing);
    }

  if (top)
    *top = ttop;
  if (bottom)
    *bottom = tbottom;
}

static void _scale_calc_request (GtkWidget     *widget,
                                 gint           slider_width,
                                 gint           stepper_spacing,
                                 gint           stepper_size,
                                 gint           trough_border,
                                 gint           slider_length,
                                 GdkRectangle  *range_rect)
{
  range_rect->x = 0;
  range_rect->y = 0;
  
  /* We never expand to fill available space in the small dimension
   * (i.e. vertical scales are always a fixed width)
   */
  if (GTK_IS_VSCALE(widget))
    {
      range_rect->width = trough_border * 2 + slider_width;
      range_rect->height = stepper_spacing * 2 + trough_border * 2 + 1;
    }
  else
    {
      range_rect->width = stepper_spacing * 2 + trough_border * 2 + 1;
      range_rect->height = trough_border * 2 + slider_width;
    }
}

static void
_scale_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkRectangle range_rect;
  
  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCALE_SLIDER_LENGTH(widget->style);    
  }

  _scale_calc_request (widget, slider_width, slider_length, stepper_size, trough_border, stepper_spacing, &range_rect);

  requisition->width = MAX(requisition->width, range_rect.width);
  requisition->height = MAX(requisition->height, range_rect.height);

  if (GTK_IS_VSCALE(range))
    old_vscale_size_request (widget, requisition);
  else
    old_hscale_size_request (widget, requisition);

  if (GTK_WIDGET_REALIZED (range)) {
    if (GTK_IS_VSCALE(range))
      gdk_window_resize (range->trough, trough_border * 2 + slider_width, requisition->height);
    else
      gdk_window_resize (range->trough, requisition->width, trough_border * 2 + slider_width);
    _scale_slider_update(range);
  }  
}

static void
_scale_size_allocate (GtkWidget     *widget,
                         GtkAllocation *allocation)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkRectangle range_rect;
  
  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCALE_SLIDER_LENGTH(widget->style);    
  }

  _scale_calc_request (widget, slider_width, slider_length, stepper_size, trough_border, stepper_spacing, &range_rect);
  
  allocation->width = MAX(allocation->width, range_rect.width);
  allocation->height = MAX(allocation->height, range_rect.height);
  
  if (GTK_IS_VSCALE(range))
    old_vscale_size_allocate (widget, allocation);
  else
    old_hscale_size_allocate (widget, allocation);

  if (GTK_WIDGET_REALIZED (range)) {
    if (GTK_IS_VSCALE(range))
      gdk_window_resize (range->trough, trough_border * 2 + slider_width, allocation->height);
    else
      gdk_window_resize (range->trough, allocation->width, trough_border * 2 + slider_width);
    _scale_slider_update(range);
  }  
}

static gint 
_scale_expose_event(GtkWidget *widget, GdkEventExpose *event) {
	GtkRange *range;
	
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_SCALE (widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	
	range = GTK_RANGE (widget);
	
	if (event->window == range->trough) {
		/* no declining to draw */
		gtk_range_draw_trough(range);
	} else if (event->window == range->slider) {
		gtk_range_draw_slider(range);
	} else if (event->window == range->step_forw) {
		gtk_range_draw_step_forw(range);
	} else if (event->window == range->step_back) {
		gtk_range_draw_step_back(range);
	} else if (event->window == widget->window) {
		gtk_range_draw_background(range);
	}
	return FALSE;
}

static void 
_scale_draw_focus (GtkWidget *widget) {
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_SCALE (widget));
	
	if (GTK_WIDGET_DRAWABLE (widget))
		gtk_range_draw_slider (GTK_RANGE (widget));
}


static void _scale_slider_update (GtkRange *range) 
{
  GtkWidget *widget;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkRectangle range_rect;

  g_return_if_fail (range != NULL);
  g_return_if_fail (GTK_IS_RANGE (range));
 
  widget = GTK_WIDGET (range);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCALE_SLIDER_LENGTH(widget->style);    
  }

  _scale_calc_request (widget, slider_width, slider_length, stepper_size, trough_border, stepper_spacing, &range_rect);

  if (GTK_WIDGET_REALIZED (range))
    {
      gint dim1, dim2, lbound, rbound, size1, size2, sbound;
      
      if (range->adjustment->value < range->adjustment->lower)
	{
	  range->adjustment->value = range->adjustment->lower;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}
      else if (range->adjustment->value > range->adjustment->upper)
	{
	  range->adjustment->value = range->adjustment->upper;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}

     /* Slider fits into the trough, with stepper_spacing on either side,
      * and the size/position based on the adjustment or fixed, depending.
      */
      if (GTK_IS_VSCALE(range)) {
        _range_trough_vdims (range, &lbound, &rbound);
        sbound = (range_rect.height - stepper_spacing * 2);
      } else {
        _range_trough_hdims (range, &lbound, &rbound);
        sbound = (range_rect.width - stepper_spacing * 2);
      }

      dim1 = lbound;
      size1 = MIN (slider_length, sbound);
      dim2 = trough_border;
      size2 = slider_width;
             
      if (range->adjustment->lower != (range->adjustment->upper - range->adjustment->page_size))
        dim1 += ((rbound - lbound) * (range->adjustment->value - range->adjustment->lower) /
                 (range->adjustment->upper - range->adjustment->lower - range->adjustment->page_size));

      dim1 = CLAMP (dim1, lbound, rbound);
     
      if (GTK_IS_VSCALE(range))
        gdk_window_move_resize (range->slider, dim2, lbound - (dim1 - lbound + size1), size2, size1);
      else
        gdk_window_move_resize (range->slider, dim1, dim2, size1, size2);
    }
}

/* GtkHScale */
static void _hscale_draw_trough (GtkRange *range) {
	GtkStyle *style;
	int trough_y, trough_width, trough_height, xt, yt;
	
	g_return_if_fail (range != NULL);
	g_return_if_fail (GTK_IS_HSCALE (range));
	
	if (range->trough) {
		style = ((GtkWidget *)range)->style;
		
		gtk_paint_flat_box (((GtkWidget *)range)->parent->style, range->trough,
							((GtkWidget *)range)->parent->state, GTK_SHADOW_NONE, NULL,
							(GtkWidget *)range, "scale trough", 0, 0, -1, -1);
		gtk_paint_box (style, range->trough,
					   ((GtkWidget*)range)->state==GTK_STATE_INSENSITIVE
					   ? GTK_STATE_INSENSITIVE
					   : GTK_STATE_ACTIVE,
					   GTK_SHADOW_IN, NULL,
					   (GtkWidget *)range, "trough", 0, 0, -1, -1);
	}
}

static void 
_hscale_draw_slider (GtkRange *range) {
	GtkStateType state_type;
	
	g_return_if_fail (range != NULL);
	g_return_if_fail (GTK_IS_HSCALE (range));
	
	if (range->slider) {
		if ((range->in_child == RANGE_CLASS (range)->slider) ||
			(range->click_child == RANGE_CLASS (range)->slider))
			state_type = GTK_STATE_PRELIGHT;
		else
			state_type = GTK_STATE_NORMAL;
		
  		gtk_paint_slider (GTK_WIDGET (range)->style, range->slider, state_type, 
					  GTK_SHADOW_OUT, NULL, GTK_WIDGET (range), "hscale",
					  0, 0, -1, -1, GTK_ORIENTATION_HORIZONTAL);
		
	}
}

static void
_hscale_size_allocate (GtkWidget     *widget,
                         GtkAllocation *allocation)
{
  _scale_size_allocate (widget, allocation);
}

static void
_hscale_size_request (GtkWidget     *widget,
                         GtkRequisition *requisition)
{
  _scale_size_request (widget, requisition);
}

/* GtkVScale */
static void 
_vscale_draw_trough (GtkRange *range) {
	GtkStyle *style;

	g_return_if_fail (range != NULL);
	g_return_if_fail (GTK_IS_VSCALE (range));
	
	if (range->trough) {
		style = ((GtkWidget *)range)->style;
			
		gtk_paint_flat_box (((GtkWidget *)range)->parent->style, range->trough,
							((GtkWidget *)range)->parent->state, GTK_SHADOW_NONE, NULL,
							(GtkWidget *)range, "scale trough", 0, 0, -1, -1);
		gtk_paint_box (style, range->trough,
					   ((GtkWidget*)range)->state==GTK_STATE_INSENSITIVE
					   ? GTK_STATE_INSENSITIVE
					   : GTK_STATE_ACTIVE,
					   GTK_SHADOW_IN, NULL,
					   (GtkWidget *)range, "trough", 0, 0, -1, -1);
	}
}

static void 
_vscale_draw_slider (GtkRange *range) {
	GtkStateType state_type;
	
	g_return_if_fail (range != NULL);
	g_return_if_fail (GTK_IS_VSCALE (range));
	
	if (range->slider) {
		if ((range->in_child == RANGE_CLASS (range)->slider) ||
			(range->click_child == RANGE_CLASS (range)->slider))
			state_type = GTK_STATE_PRELIGHT;
		else
			state_type = GTK_STATE_NORMAL;

		gtk_paint_slider (GTK_WIDGET (range)->style, range->slider, state_type,
						  GTK_SHADOW_OUT, NULL, GTK_WIDGET (range), "hscale",
						  0, 0, -1, -1, GTK_ORIENTATION_VERTICAL);
	}
}

static void
_vscale_size_allocate (GtkWidget     *widget,
                         GtkAllocation *allocation)
{
  _scale_size_allocate (widget, allocation);
}


static void
_vscale_size_request (GtkWidget     *widget,
                         GtkRequisition *requisition)
{
  _scale_size_request (widget, requisition);
}

/* GtkScrollbar */
static void
_scrollbar_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkRectangle range_rect;
    
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_SCROLLBAR (widget));
  g_return_if_fail (requisition != NULL);

  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }

  int size1 = (slider_length + stepper_size + stepper_spacing + trough_border) * 2;
  int size2 = (slider_width + trough_border * 2);
   
  if (GTK_IS_HSCROLLBAR(widget)) {
    requisition->width = size1;
    requisition->height = size2;
  } else {
    requisition->width = size2;
    requisition->height = size1;
  }  
}

/* GtkHScrollbar */
static void
_hscrollbar_calc_slider_size (GtkHScrollbar *hscrollbar)
{
  GtkWidget *widget;
  GtkRange *range;
  gint slider_length, stepper_spacing;
  gint slider_width;
  gint slider_height;
  gint step_back_x;
  gint step_back_width;
  gint step_forw_x;
  gint left, right;
  gint width;
    
  g_return_if_fail (hscrollbar != NULL);
  g_return_if_fail (GTK_IS_HSCROLLBAR (hscrollbar));

  widget = GTK_WIDGET(hscrollbar);
  range = GTK_RANGE (hscrollbar);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }
  
  if (GTK_WIDGET_REALIZED (hscrollbar))
    {
      gdk_window_get_size (range->step_back, &step_back_width, NULL);
      gdk_window_get_position (range->step_back, &step_back_x, NULL);
      gdk_window_get_position (range->step_forw, &step_forw_x, NULL);
      
      left = (step_back_x +
              step_back_width +
              stepper_spacing);
      right = step_forw_x - stepper_spacing;
      width = right - left;
      
      if ((range->adjustment->page_size > 0) &&
          (range->adjustment->lower != range->adjustment->upper))
        {
          if (range->adjustment->page_size >
              (range->adjustment->upper - range->adjustment->lower))
            range->adjustment->page_size = range->adjustment->upper - range->adjustment->lower;
          
          width = (width * range->adjustment->page_size /
                   (range->adjustment->upper - range->adjustment->lower));
          
          if (width < slider_length)
            width = slider_length;
        }
      
      gdk_window_get_size (range->slider, &slider_width, &slider_height);
      
      if (slider_width != width)
        gdk_window_resize (range->slider, width, slider_height);
    }
}

static void
_hscrollbar_slider_update (GtkRange *range)
{
  gint left;
  gint right;
  gint x;
  gint trough_border;

  g_return_if_fail (range != NULL);
  g_return_if_fail (GTK_IS_HSCROLLBAR (range));
  
  _hscrollbar_calc_slider_size (GTK_HSCROLLBAR (range));
  	
  if ((range) && (GTK_WIDGET(range)->style) && THEME_DATA(GTK_WIDGET(range)->style)) {
    trough_border = RANGE_TROUGH_BORDER(GTK_WIDGET(range)->style);    
  }

  if (GTK_WIDGET_REALIZED (range))
    {
      _range_trough_hdims (range, &left, &right);
      x = left;

      if (range->adjustment->value < range->adjustment->lower)
	{
	  range->adjustment->value = range->adjustment->lower;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}
      else if (range->adjustment->value > range->adjustment->upper)
	{
	  range->adjustment->value = range->adjustment->upper;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}

      if (range->adjustment->lower != (range->adjustment->upper - range->adjustment->page_size))
	x += ((right - left) * (range->adjustment->value - range->adjustment->lower) /
	      (range->adjustment->upper - range->adjustment->lower - range->adjustment->page_size));

      if (x < left)
	x = left;
      else if (x > right)
	x = right;

      gdk_window_move (range->slider, x, trough_border);
    }
}

static void
_hscrollbar_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  _scrollbar_size_request (widget, requisition);
}

static void
_hscrollbar_size_allocate (GtkWidget      *widget,
                              GtkAllocation *allocation)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkRectangle range_rect;
   
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_HSCROLLBAR (widget));
  g_return_if_fail (allocation != NULL);

  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }
  
  widget->allocation = *allocation;
  if (GTK_WIDGET_REALIZED (widget))
    {
      gdk_window_move_resize (range->trough,
                              allocation->x,
                              allocation->y + (allocation->height - widget->requisition.height) / 2,
                              allocation->width, widget->requisition.height);
      gdk_window_move_resize (range->step_back,
                              trough_border,
                              trough_border,
                              stepper_size,
                              widget->requisition.height - trough_border * 2);
      gdk_window_move_resize (range->step_forw,
                              allocation->width - trough_border -
                              stepper_size,
                              trough_border,
                              stepper_size,
                              widget->requisition.height - trough_border * 2);
      gdk_window_resize (range->slider,
                         slider_length,
                         widget->requisition.height - trough_border * 2);
      
      _hscrollbar_slider_update (range);
    }
}

static void _hscrollbar_realize (GtkWidget *widget)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkWindowAttr attributes;
  gint attributes_mask;
  
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_HSCROLLBAR (widget));
  
  GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
  
  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }

  attributes.x = widget->allocation.x;
  attributes.y = widget->allocation.y + (widget->allocation.height - widget->requisition.height) / 2;
  attributes.width = widget->allocation.width;
  attributes.height = widget->requisition.height;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.visual = gtk_widget_get_visual (widget);
  attributes.colormap = gtk_widget_get_colormap (widget);
  attributes.event_mask = gtk_widget_get_events (widget);
  attributes.event_mask |= (GDK_EXPOSURE_MASK |
                            GDK_BUTTON_PRESS_MASK |
                            GDK_BUTTON_RELEASE_MASK |
                            GDK_ENTER_NOTIFY_MASK |
                            GDK_LEAVE_NOTIFY_MASK);
  
  attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
  widget->window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes, attributes_mask);
  
  range->trough = widget->window;
  gdk_window_ref (range->trough);
  
  attributes.x = trough_border;
  attributes.y = trough_border;
  attributes.width = stepper_size;
  attributes.height = stepper_size;
  
  range->step_back = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  attributes.x = (widget->allocation.width -
                  trough_border -
                  stepper_size);
  
  range->step_forw = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  attributes.x = 0;
  attributes.y = trough_border;
  attributes.width = slider_length;
  attributes.height = slider_width;
  attributes.event_mask |= (GDK_BUTTON_MOTION_MASK |
                            GDK_POINTER_MOTION_HINT_MASK);
  
  range->slider = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  _hscrollbar_calc_slider_size (GTK_HSCROLLBAR (widget));
  _hscrollbar_slider_update (GTK_RANGE (widget));
  
  widget->style = gtk_style_attach (widget->style, widget->window);
  
  gdk_window_set_user_data (range->trough, widget);
  gdk_window_set_user_data (range->slider, widget);
  gdk_window_set_user_data (range->step_forw, widget);
  gdk_window_set_user_data (range->step_back, widget);
  
  gtk_style_set_background (widget->style, range->trough, GTK_STATE_ACTIVE);
  gtk_style_set_background (widget->style, range->slider, GTK_STATE_NORMAL);
  gtk_style_set_background (widget->style, range->step_forw, GTK_STATE_ACTIVE);
  gtk_style_set_background (widget->style, range->step_back, GTK_STATE_ACTIVE);
  
  gdk_window_show (range->slider);
  gdk_window_show (range->step_forw);
  gdk_window_show (range->step_back);

  _hscrollbar_size_allocate (widget, &(widget->allocation));
}

/* GtkVScrollbar */
static void
_vscrollbar_calc_slider_size (GtkVScrollbar *vscrollbar)
{
  GtkWidget *widget;
  GtkRange *range;
  gint slider_length, stepper_spacing;
  gint slider_width;
  gint slider_height;
  gint step_back_y;
  gint step_back_height;
  gint step_forw_y;
  gint top, bottom;
  gint height;
    
  g_return_if_fail (vscrollbar != NULL);
  g_return_if_fail (GTK_IS_VSCROLLBAR (vscrollbar));

  widget = GTK_WIDGET(vscrollbar);
  range = GTK_RANGE (vscrollbar);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }
  
  if (GTK_WIDGET_REALIZED (vscrollbar))
    {
      gdk_window_get_size (range->step_back, NULL, &step_back_height);
      gdk_window_get_position (range->step_back, NULL, &step_back_y);
      gdk_window_get_position (range->step_forw, NULL, &step_forw_y);
      
      top = (step_back_y +
             step_back_height +
             stepper_spacing);
      bottom = step_forw_y - stepper_spacing;
      height = bottom - top;
      
      if ((range->adjustment->page_size > 0) &&
          (range->adjustment->lower != range->adjustment->upper))
        {
          if (range->adjustment->page_size >
              (range->adjustment->upper - range->adjustment->lower))
            range->adjustment->page_size = range->adjustment->upper - range->adjustment->lower;
          
          height = (height * range->adjustment->page_size /
                    (range->adjustment->upper - range->adjustment->lower));
          
          if (height < slider_length)
            height = slider_length;
        }
      
      gdk_window_get_size (range->slider, &slider_width, &slider_height);
      
      if (slider_height != height)
        gdk_window_resize (range->slider, slider_width, height);
    }
}

static void
_vscrollbar_slider_update (GtkRange *range)
{
  gint top;
  gint bottom;
  gint y;
  gint trough_border;

  g_return_if_fail (range != NULL);
  g_return_if_fail (GTK_IS_VSCROLLBAR (range));
  
  _vscrollbar_calc_slider_size (GTK_VSCROLLBAR (range));

  if ((range) && (GTK_WIDGET(range)->style) && THEME_DATA(GTK_WIDGET(range)->style)) {
    trough_border = RANGE_TROUGH_BORDER(GTK_WIDGET(range)->style);    
  }

  if (GTK_WIDGET_REALIZED (range))
    {
      _range_trough_vdims (range, &top, &bottom);
      y = top;

      if (range->adjustment->value < range->adjustment->lower)
	{
	  range->adjustment->value = range->adjustment->lower;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}
      else if (range->adjustment->value > range->adjustment->upper)
	{
	  range->adjustment->value = range->adjustment->upper;
	  gtk_signal_emit_by_name (GTK_OBJECT (range->adjustment), "value_changed");
	}

      if (range->adjustment->lower != (range->adjustment->upper - range->adjustment->page_size))
	y += ((bottom - top) * (range->adjustment->value - range->adjustment->lower) /
	      (range->adjustment->upper - range->adjustment->lower - range->adjustment->page_size));

      if (y < top)
	y = top;
      else if (y > bottom)
	y = bottom;

      gdk_window_move (range->slider, trough_border, y);
    }
}

static void
_vscrollbar_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  _scrollbar_size_request (widget, requisition);
}

static void
_vscrollbar_size_allocate (GtkWidget      *widget,
                              GtkAllocation *allocation)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
   
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_VSCROLLBAR (widget));
  g_return_if_fail (allocation != NULL);

  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }
  
  widget->allocation = *allocation;	
  if (GTK_WIDGET_REALIZED (widget))
    {
      gdk_window_move_resize (range->trough,
                              allocation->x + (allocation->width - widget->requisition.width) / 2,
                              allocation->y,
                              widget->requisition.width, allocation->height);
      gdk_window_move_resize (range->step_back,
                              trough_border,
                              trough_border,
                              widget->requisition.width - trough_border * 2,
                              stepper_size);
      gdk_window_move_resize (range->step_forw,
                              trough_border,
                              allocation->height - trough_border -
                              stepper_size,
                              widget->requisition.width - trough_border * 2,
                              stepper_size);
      gdk_window_resize (range->slider,
                         widget->requisition.width - trough_border * 2,
                         slider_length);
      
      _vscrollbar_slider_update (GTK_RANGE (widget));
    }
}

static void 
_vscrollbar_realize (GtkWidget *widget)
{
  GtkRange *range;
  gint slider_width, slider_length, stepper_size, trough_border, stepper_spacing;
  GdkWindowAttr attributes;
  gint attributes_mask;
  
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_VSCROLLBAR (widget));
  
  GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);

  range = GTK_RANGE (widget);
  
  if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
    slider_width = RANGE_SLIDER_WIDTH(widget->style);
    trough_border = RANGE_TROUGH_BORDER(widget->style);    
    stepper_size = RANGE_STEPPER_SIZE(widget->style);    
    stepper_spacing = RANGE_STEPPER_SPACING(widget->style);    
    slider_length = SCROLLBAR_MIN_SLIDER_LENGTH(widget->style);    
  }

  attributes.x = widget->allocation.x + (widget->allocation.width - widget->requisition.width) / 2;
  attributes.y = widget->allocation.y;
  attributes.width = widget->requisition.width;
  attributes.height = widget->allocation.height;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.visual = gtk_widget_get_visual (widget);
  attributes.colormap = gtk_widget_get_colormap (widget);
  attributes.event_mask = gtk_widget_get_events (widget);
  attributes.event_mask |= (GDK_EXPOSURE_MASK |
                            GDK_BUTTON_PRESS_MASK |
                            GDK_BUTTON_RELEASE_MASK |
                            GDK_ENTER_NOTIFY_MASK |
                            GDK_LEAVE_NOTIFY_MASK);
  
  attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
  widget->window = gdk_window_new (gtk_widget_get_parent_window (widget), &attributes, attributes_mask);
  
  range->trough = widget->window;
  gdk_window_ref (range->trough);
  
  attributes.x = trough_border;
  attributes.y = trough_border;
  attributes.width = stepper_size;
  attributes.height = stepper_size;
  
  range->step_back = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  attributes.y = (widget->allocation.height -
                  trough_border -
                  stepper_size);
  
  range->step_forw = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  attributes.x = trough_border;
  attributes.y = 0;
  attributes.width = slider_width;
  attributes.height = slider_length;
  attributes.event_mask |= (GDK_BUTTON_MOTION_MASK |
                            GDK_POINTER_MOTION_HINT_MASK);
  
  range->slider = gdk_window_new (range->trough, &attributes, attributes_mask);
  
  _vscrollbar_calc_slider_size (GTK_VSCROLLBAR (widget));
  _vscrollbar_slider_update (GTK_RANGE (widget));
  
  widget->style = gtk_style_attach (widget->style, widget->window);
  
  gdk_window_set_user_data (range->trough, widget);
  gdk_window_set_user_data (range->slider, widget);
  gdk_window_set_user_data (range->step_forw, widget);
  gdk_window_set_user_data (range->step_back, widget);
  
  gtk_style_set_background (widget->style, range->trough, GTK_STATE_ACTIVE);
  gtk_style_set_background (widget->style, range->slider, GTK_STATE_NORMAL);
  gtk_style_set_background (widget->style, range->step_forw, GTK_STATE_ACTIVE);
  gtk_style_set_background (widget->style, range->step_back, GTK_STATE_ACTIVE);
  
  gdk_window_show (range->slider);
  gdk_window_show (range->step_forw);
  gdk_window_show (range->step_back);

  _vscrollbar_size_allocate (widget, &(widget->allocation));
}

/* GtkSpinButton */

static void
_spin_button_changed (GtkEditable *editable)
{
	GtkEntry	*entry;
	gint		text_area_width;
	gint		char_width, text_width;
	
	g_return_if_fail (editable != NULL);
	g_return_if_fail (GTK_IS_ENTRY (editable));
	g_return_if_fail (GTK_IS_SPIN_BUTTON (editable));
	
	entry = GTK_ENTRY(editable);
	
	if (!entry->text_area)
		return;
	
	gdk_window_get_size (entry->text_area, &text_area_width, NULL);
	
	char_width = gdk_char_width (GTK_WIDGET(entry)->style->font, (gchar)'X');
	
	entry->scroll_offset = 0;
	
	/* Right-justify numbers */
	if (entry->text) {
		text_width = gdk_text_width (GTK_WIDGET(entry)->style->font,
									 gtk_entry_get_text (entry),
									 strlen (gtk_entry_get_text(entry)));

		entry->scroll_offset = -(text_area_width - text_width) + 4;
	} else {
		entry->scroll_offset = -text_area_width;
	}
	
	gtk_widget_queue_draw(GTK_WIDGET(entry));
}

static void
_spin_button_size_allocate (GtkWidget		*widget,
								GtkAllocation	*allocation)
{
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_SPIN_BUTTON (widget));
	g_return_if_fail (allocation != NULL);
	
	widget->allocation = *allocation;
	old_spin_button_size_allocate (widget, allocation);
	
	if (GTK_WIDGET_REALIZED (widget))
		_spin_button_changed ((GtkEditable *)widget);
}

static void
_spin_button_realize (GtkWidget *widget) {
	g_return_if_fail (widget != NULL);
	g_return_if_fail (GTK_IS_SPIN_BUTTON(widget));
	
	old_spin_button_realize (widget);
	_spin_button_changed ((GtkEditable *)widget);
}

static gint
_spin_button_button_press_event (GtkWidget *widget, GdkEventButton *event)
{
	g_return_val_if_fail (widget != NULL, FALSE);
	g_return_val_if_fail (GTK_IS_SPIN_BUTTON(widget), FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	
	if (!GTK_WIDGET_HAS_FOCUS (widget))
		gtk_widget_grab_focus(widget);
	
	return old_spin_button_button_press_event (widget, event);
}

/* GtkCheckButton */

static void _check_button_draw_indicator (GtkCheckButton *check_button, GdkRectangle   *area)
{
  GtkWidget *widget;
  GtkWidget *child;
  GtkButton *button;
  GtkToggleButton *toggle_button;
  GtkStateType state_type;
  GtkShadowType shadow_type;
  gint x, y;
  gint indicator_size;
  gint indicator_spacing;
  gint focus_width=1;
  gint focus_pad=0;
  gboolean interior_focus=FALSE;
   
  if (GTK_WIDGET_DRAWABLE (check_button))
    {
      widget = GTK_WIDGET (check_button);
      button = GTK_BUTTON (check_button);
      toggle_button = GTK_TOGGLE_BUTTON (check_button);
  
      if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
        interior_focus = FOCUS_INTERIOR(widget->style);
        focus_width = FOCUS_WIDTH(widget->style);    
        focus_pad = FOCUS_PAD(widget->style);    
      }
      
      _gtk_check_button_get_props (check_button, &indicator_size, &indicator_spacing);

      x = widget->allocation.x + indicator_spacing + GTK_CONTAINER (widget)->border_width;
      y = widget->allocation.y + (widget->allocation.height - indicator_size) / 2;

      child = GTK_BIN (check_button)->child;
      if (!interior_focus || !(child && GTK_WIDGET_VISIBLE (child)))
	x += focus_width + focus_pad;      

      if (toggle_button->active)
	shadow_type = GTK_SHADOW_IN;
      else
	shadow_type = GTK_SHADOW_OUT;

      if (button->button_down && button->in_button)
	state_type = GTK_STATE_ACTIVE;
      else if (button->in_button)
	state_type = GTK_STATE_PRELIGHT;
      else if (!GTK_WIDGET_IS_SENSITIVE (widget))
	state_type = GTK_STATE_INSENSITIVE;
      else
	state_type = GTK_STATE_NORMAL;
      
      if (GTK_WIDGET_STATE (toggle_button) == GTK_STATE_PRELIGHT)
	{
	  GdkRectangle restrict_area;
	  GdkRectangle new_area;
	      
	  restrict_area.x = widget->allocation.x + GTK_CONTAINER (widget)->border_width;
	  restrict_area.y = widget->allocation.y + GTK_CONTAINER (widget)->border_width;
	  restrict_area.width = widget->allocation.width - (2 * GTK_CONTAINER (widget)->border_width);
	  restrict_area.height = widget->allocation.height - (2 * GTK_CONTAINER (widget)->border_width);
	  
	  if (gdk_rectangle_intersect (area, &restrict_area, &new_area))
	    {
	      gtk_paint_flat_box (widget->style, widget->window, GTK_STATE_PRELIGHT,
				  GTK_SHADOW_ETCHED_OUT, 
				  area, widget, "checkbutton",
				  new_area.x, new_area.y,
				  new_area.width, new_area.height);
	    }
	}

      gtk_paint_check (widget->style, widget->window,
		       state_type, shadow_type,
		       area, widget, "checkbutton",
		       x, y, indicator_size, indicator_size);
    }
}

/* This should only be called when toggle_button->draw_indicator
 * is true.
 */
#define CHECK_BUTTON_CLASS(w)  GTK_CHECK_BUTTON_CLASS (GTK_OBJECT (w)->klass)
static void _check_button_paint (GtkWidget *widget, GdkRectangle *area)
{
  GtkCheckButton *check_button = GTK_CHECK_BUTTON (widget);
  GtkCheckButtonClass *class;
  
  if (GTK_WIDGET_DRAWABLE (widget))
    {
      gint border_width;
      gint focus_width=1;
      gint focus_pad=0;
      gboolean interior_focus=FALSE;
	   
      if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
        interior_focus = FOCUS_INTERIOR(widget->style);
        focus_width = FOCUS_WIDTH(widget->style);    
        focus_pad = FOCUS_PAD(widget->style);    
      }

      class = CHECK_BUTTON_CLASS (check_button);

      if (class->draw_indicator)
         (* class->draw_indicator) (check_button, area);
      
      border_width = GTK_CONTAINER (widget)->border_width;
      if (GTK_WIDGET_HAS_FOCUS (widget))
	{
	  GtkWidget *child = GTK_BIN (widget)->child;
	  
	  if (interior_focus && child && GTK_WIDGET_VISIBLE (child))
	    gtk_paint_focus (widget->style, widget->window,
			     NULL, widget, "checkbutton",
			     child->allocation.x - focus_width - focus_pad,
			     child->allocation.y - focus_width - focus_pad,
			     child->allocation.width + 2 * (focus_width + focus_pad),
			     child->allocation.height + 2 * (focus_width + focus_pad));
	  else
	    gtk_paint_focus (widget->style, widget->window,
			     NULL, widget, "checkbutton",
			     border_width + widget->allocation.x,
			     border_width + widget->allocation.y,
			     widget->allocation.width - 2 * border_width,
			     widget->allocation.height - 2 * border_width);
	}
    }
}

static void _check_button_draw (GtkWidget *widget, GdkRectangle *area)
{
  GtkCheckButton *check_button;
  GtkToggleButton *toggle_button;
  GtkBin *bin;
  GdkRectangle child_area;
  GtkTypeClass *parent_class = NULL;
  
  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_CHECK_BUTTON (widget));
  g_return_if_fail (area != NULL);
  
  check_button = GTK_CHECK_BUTTON (widget);
  toggle_button = GTK_TOGGLE_BUTTON (widget);
  bin = GTK_BIN (widget);
  
  if (GTK_WIDGET_DRAWABLE (widget))
    {
      parent_class =  gtk_type_class (gtk_toggle_button_get_type ());
   
      if (toggle_button->draw_indicator)
	{
	  _check_button_paint (widget, area);

	  if (bin->child && gtk_widget_intersect (bin->child, area, &child_area))
	    gtk_widget_draw (bin->child, &child_area);
	}
      else
	{
	  if (GTK_WIDGET_CLASS (parent_class)->draw)
	    (* GTK_WIDGET_CLASS (parent_class)->draw) (widget, area);
	}
    }
}

static gint _check_button_expose_event (GtkWidget *widget, GdkEventExpose *event)
{
  GtkCheckButton *check_button;
  GtkToggleButton *toggle_button;
  GtkBin *bin;
  GdkEventExpose child_event;
  GtkTypeClass *parent_class = NULL;

  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_CHECK_BUTTON (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);
  
  check_button = GTK_CHECK_BUTTON (widget);
  toggle_button = GTK_TOGGLE_BUTTON (widget);
  bin = GTK_BIN (widget);
  
  parent_class =  gtk_type_class (gtk_toggle_button_get_type ());

  if (GTK_WIDGET_DRAWABLE (widget))
    {
      if (toggle_button->draw_indicator)
	{
	  _check_button_paint (widget, &event->area);
	  
	  child_event = *event;
	  if (bin->child && GTK_WIDGET_NO_WINDOW (bin->child) &&
	      gtk_widget_intersect (bin->child, &event->area, &child_event.area))
	    gtk_widget_event (bin->child, (GdkEvent*) &child_event);
	}
      else
	{
	  if (GTK_WIDGET_CLASS (parent_class)->expose_event)
	    (* GTK_WIDGET_CLASS (parent_class)->expose_event) (widget, event);
	}
    }
  
  return FALSE;
}

/* GtkRadioButton */

static void _radio_button_draw_indicator (GtkCheckButton *check_button, GdkRectangle   *area)
{
  GtkWidget *widget;
  GtkWidget *child;
  GtkButton *button;
  GtkToggleButton *toggle_button;
  GtkStateType state_type;
  GtkShadowType shadow_type;
  gint x, y;
  gint indicator_size, indicator_spacing;
  gint focus_width=1;
  gint focus_pad=0;
  gboolean interior_focus=FALSE;
 
  if (GTK_WIDGET_DRAWABLE (check_button))
    {
      widget = GTK_WIDGET (check_button);
      button = GTK_BUTTON (check_button);
      toggle_button = GTK_TOGGLE_BUTTON (check_button);

      if ((widget) && (widget->style) && THEME_DATA(widget->style)) {
        interior_focus = FOCUS_INTERIOR(widget->style);
        focus_width = FOCUS_WIDTH(widget->style);    
        focus_pad = FOCUS_PAD(widget->style);    
      }
      
      _gtk_check_button_get_props (check_button, &indicator_size, &indicator_spacing);

      x = widget->allocation.x + indicator_spacing + GTK_CONTAINER (widget)->border_width;
      y = widget->allocation.y + (widget->allocation.height - indicator_size) / 2;

      child = GTK_BIN (check_button)->child;
      if (!interior_focus || !(child && GTK_WIDGET_VISIBLE (child)))
	x += focus_width + focus_pad;      

      if (toggle_button->active)
	shadow_type = GTK_SHADOW_IN;
      else
	shadow_type = GTK_SHADOW_OUT;

      if (button->button_down && button->in_button)
	state_type = GTK_STATE_ACTIVE;
      else if (button->in_button)
	state_type = GTK_STATE_PRELIGHT;
      else if (!GTK_WIDGET_IS_SENSITIVE (widget))
	state_type = GTK_STATE_INSENSITIVE;
      else
	state_type = GTK_STATE_NORMAL;

      if (GTK_WIDGET_STATE (toggle_button) == GTK_STATE_PRELIGHT)
	{
	  GdkRectangle restrict_area;
	  GdkRectangle new_area;
	      
	  restrict_area.x = widget->allocation.x + GTK_CONTAINER (widget)->border_width;
	  restrict_area.y = widget->allocation.y + GTK_CONTAINER (widget)->border_width;
	  restrict_area.width = widget->allocation.width - (2 * GTK_CONTAINER (widget)->border_width);
	  restrict_area.height = widget->allocation.height - (2 * GTK_CONTAINER (widget)->border_width);
	  
	  if (gdk_rectangle_intersect (area, &restrict_area, &new_area))
	    {
	      gtk_paint_flat_box (widget->style, widget->window, GTK_STATE_PRELIGHT,
				  GTK_SHADOW_ETCHED_OUT, 
				  area, widget, "checkbutton",
				  new_area.x, new_area.y,
				  new_area.width, new_area.height);
	    }
	}

      gtk_paint_option (widget->style, widget->window,
			state_type, shadow_type,
			area, widget, "radiobutton",
			x, y, indicator_size, indicator_size);
    }
}

/* GtkMenuItem */

static void
do_menu_item_paint (GtkWidget    *widget,
		     GdkRectangle *area)
{
  GtkMenuItem *menu_item;
  GtkStateType state_type;
  GtkShadowType shadow_type;
  gint width, height;
  gint x, y;

  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_MENU_ITEM (widget));
  
  if (GTK_WIDGET_DRAWABLE (widget))
    {
      menu_item = GTK_MENU_ITEM (widget);

      state_type = widget->state;

      x = GTK_CONTAINER (menu_item)->border_width;
      y = GTK_CONTAINER (menu_item)->border_width;
      width = widget->allocation.width - x * 2;
      height = widget->allocation.height - y * 2;
      if ((state_type == GTK_STATE_PRELIGHT) &&
	  (GTK_BIN (menu_item)->child))
	gtk_paint_box (widget->style,
		       widget->window,
		       GTK_STATE_PRELIGHT,
		       GTK_SHADOW_OUT,
		       area, widget, "menuitem",
		       x, y, width, height);
      else {
        gint w=-1, h=-1;
	if (sanitize_parameters(widget->parent->style, widget->parent->window, &w, &h))
          gtk_paint_box (widget->parent->style,
		         widget->window,
		         GTK_STATE_NORMAL,
	                 GTK_SHADOW_NONE,
		         area, widget->parent, "menubar",
		         -widget->allocation.x, -widget->allocation.y,
		         w, h);
      }		       
   }
}

static void
_menu_item_draw (GtkWidget *widget, GdkRectangle *area)
{
  GtkBin *bin;
  GdkRectangle child_area;

  g_return_if_fail (widget != NULL);
  g_return_if_fail (GTK_IS_MENU_ITEM (widget));
  g_return_if_fail (area != NULL);
 
  if ((widget->parent) && GTK_IS_MENU_BAR(widget->parent))
    {
      do_menu_item_paint (widget, area);

      bin = GTK_BIN (widget);

      if (bin->child)
        {
          if (gtk_widget_intersect (bin->child, area, &child_area))
            gtk_widget_draw (bin->child, &child_area);
        }
    } else
      old_menu_item_draw (widget, area);
}

static gint
_menu_item_expose_event (GtkWidget *widget, GdkEventExpose *event)
{
  GtkBin *bin;
  GdkEventExpose child_event;

  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_MENU_ITEM (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  if ((widget->parent) && GTK_IS_MENU_BAR(widget->parent))
    {
      do_menu_item_paint (widget, &event->area);

      bin = GTK_BIN (widget);

      if (bin->child)
        {
          child_event = *event;

          if (GTK_WIDGET_NO_WINDOW (bin->child) &&
              gtk_widget_intersect (bin->child, &event->area, &child_event.area))
            gtk_widget_event (bin->child, (GdkEvent*) &child_event);
        }
    } else
      return old_menu_item_expose_event (widget, event);

  return FALSE;
}
