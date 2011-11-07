#include <gtk/gtkstyle.h>
#include "utils/misc_functions.h"

typedef struct _SmoothStyle SmoothStyle;
typedef struct _SmoothStyleClass SmoothStyleClass;

#if GTK2
extern GType smooth_type_style;
extern GtkStyleClass *style_parent_class;

#define SMOOTH_TYPE_STYLE              smooth_type_style
#define SMOOTH_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SMOOTH_TYPE_STYLE, SmoothStyle))
#define SMOOTH_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SMOOTH_TYPE_STYLE, SmoothStyleClass))
#define SMOOTH_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SMOOTH_TYPE_STYLE))
#define SMOOTH_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SMOOTH_TYPE_STYLE))
#define SMOOTH_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SMOOTH_TYPE_STYLE, SmoothStyleClass))
#endif

struct _SmoothStyle
{
  #if GTK2
  GtkStyle parent_instance;
  #endif
};

struct _SmoothStyleClass
{
  #if GTK2
  GtkStyleClass parent_class;
  #endif
};

#if GTK2
void smooth_style_register_type (GTypeModule *module);
#endif

#if GTK2
extern GMemChunk	  *	smooth_style_data_chunk;
#endif

#define FLAT_FILL_BACKGROUND(style, window, state_type, area, widget, part, x, y, width, height) (smooth_fill_background(style, window, state_type, GTK_SHADOW_NONE, area, NULL, widget, part, x, y, width, height, FALSE, FALSE, GTK_ORIENTATION_VERTICAL,FALSE))		
#define gradient_fill_background(style, window, state_type, area, widget, part, x, y, width, height, invert, orientation) (smooth_fill_background(style, window, state_type, GTK_SHADOW_NONE, area, NULL, widget, part, x, y, width, height, TRUE, invert, orientation,FALSE))

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
		       gboolean arc_fill);

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
			    gint gap_size);

void 
smooth_draw_grip(GtkStyle * style,
                 GdkWindow * window,
                 GtkStateType state_type,
                 GdkRectangle * area,
	         gint x,
	         gint y,
	         gint width,
	         gint height,
	         GtkOrientation orientation);

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
                   gint gap_pos);

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
	         GtkOrientation orientation);

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
	            gint fill);

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
	          gint height);

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
                  gint dash_width);

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
                           gint height);

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
	           GtkOrientation orientation);
	           
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
	              GtkPositionType gap_side);
	              
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
                GtkOrientation orientation);

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
	            gint gap_x, 
	            gint gap_width);
	             
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
                   gint height);
	             	              
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
	          gint height);

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
	            gint height);
	           
