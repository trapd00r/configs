#include <gtk/gtk.h>
#include "utils/misc_functions.h"

#define SMOOTH_LINE_NONE		1
#define SMOOTH_LINE_FLAT		2
#define SMOOTH_LINE_THIN		3
#define SMOOTH_LINE_BEVELED		4
#define SMOOTH_LINE_STANDARD		5
#define SMOOTH_LINE_SMOOTHED		6
#define SMOOTH_LINE_COLD		7
#define SMOOTH_LINE_WIN32		8
#define SMOOTH_LINE_SMOOTHBEVEL		9
#define SMOOTH_LINE_SOFT		10

#define SMOOTH_FILL_SOLID		1
#define SMOOTH_FILL_GRADIENT		2
#define SMOOTH_FILL_SHADE_GRADIENT	3
#define SMOOTH_FILL_PIXBUF		4

#define SMOOTH_FONT_NORMAL		1
#define SMOOTH_FONT_BOLD		2
#define SMOOTH_FONT_ITALIC		3
#define SMOOTH_FONT_BOLD_ITALIC		4

#define SMOOTH_TEXT_INHERITED		1
#define SMOOTH_TEXT_DEFAULT		2
#define SMOOTH_TEXT_CUSTOM		3

#define SMOOTH_EDGE_NONE		1
#define SMOOTH_EDGE_LINE		2
#define SMOOTH_EDGE_GRADIENT		3
#define SMOOTH_EDGE_PIXBUF		4

#define SMOOTH_BUTTON_DEFAULT_NONE	1
#define SMOOTH_BUTTON_DEFAULT_NORMAL	2
#define SMOOTH_BUTTON_DEFAULT_WIN32	3
#define SMOOTH_BUTTON_DEFAULT_TRIANGLE	4

#define SMOOTH_TAB_NORMAL		1
#define SMOOTH_TAB_ROUND		2
#define SMOOTH_TAB_TRIANGLE		3
#define SMOOTH_TAB_PIXBUF		4

#define DEFAULT_CHECKSTYLE		FAST_CHECK
#define DEFAULT_GRADIENT		TRUE
#define DEFAULT_HGRADIENTDIRECTION	GDK_GRADIENT_HORIZONTAL
#define DEFAULT_VGRADIENTDIRECTION	GDK_GRADIENT_VERTICAL
#define DEFAULT_FILLSTYLE		SMOOTH_FILL_SOLID
#define DEFAULT_EDGESTYLE		LINE_EDGE
#define DEFAULT_LINETHICKNESS		2
#define DEFAULT_LINESTYLE		SMOOTH_LINE_STANDARD
#define DEFAULT_BUTTONDEFAULTSTYLE	SMOOTH_BUTTON_DEFAULT_NORMAL
#define DEFAULT_BUTTONDEFAULTTRIANGLE	TRUE
#define DEFAULT_TABSTYLE		SMOOTH_TAB_NORMAL
#define DEFAULT_GRIPSTYLE		FIXEDLINES_IN_GRIP
#define DEFAULT_ARROWSTYLE		ARROW_STYLE_THINICE
#define DEFAULT_SOLIDARROW		FALSE
#define DEFAULT_ETCHEDARROW		FALSE
#define DEFAULT_GRIPCOUNT		3
#define DEFAULT_GRIPSPACING		2
#define DEFAULT_OPTIONSTYLE		CIRCLE_OPTION
#define DEFAULT_REAL_SLIDERS		FALSE
#define DEFAULT_RESIZE_GRIP		TRUE
#define DEFAULT_TROUGH_SHOW_VALUE	FALSE
#define DEFAULT_GRIPOVERLAP		FALSE


typedef struct _SmoothRcStyle SmoothRcStyle;

#if GTK1
typedef struct _SmoothRcProperty SmoothRcProperty;
#endif

#if GTK2
typedef struct _SmoothRcStyleClass SmoothRcStyleClass;
#endif

typedef struct _smooth_line_style smooth_line_style;
typedef struct _smooth_fill_style smooth_fill_style;
typedef struct _smooth_focus_style smooth_focus_style;

typedef struct _smooth_part_style smooth_part_style;

typedef struct _smooth_edge_style smooth_edge_style;

typedef struct _smooth_bg_style smooth_bg_style;
typedef struct _smooth_fg_style smooth_fg_style;
typedef struct _smooth_grip_style smooth_grip_style;
typedef struct _smooth_check_style smooth_check_style;
typedef struct _smooth_option_style smooth_option_style;
typedef struct _smooth_arrow_style smooth_arrow_style;
typedef struct _smooth_button_style smooth_button_style;
typedef struct _smooth_tab_style smooth_tab_style;
typedef struct _smooth_trough_style smooth_trough_style;

typedef gboolean (*SmoothTranslateEnumFunc) (gchar * str, gint *retval);

#define THEME_PART(part)                 ((smooth_part_style *) (part))

#if GTK2
extern GType smooth_type_rc_style;

#define SMOOTH_TYPE_RC_STYLE              smooth_type_rc_style
#define SMOOTH_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), SMOOTH_TYPE_RC_STYLE, SmoothRcStyle))
#define SMOOTH_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), SMOOTH_TYPE_RC_STYLE, SmoothRcStyleClass))
#define SMOOTH_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), SMOOTH_TYPE_RC_STYLE))
#define SMOOTH_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), SMOOTH_TYPE_RC_STYLE))
#define SMOOTH_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), SMOOTH_TYPE_RC_STYLE, SmoothRcStyleClass))
#define SMOOTH_RC_DATA(rc_style)          (SMOOTH_RC_STYLE (rc_style))

#define THEME_DATA(style)                 (SMOOTH_RC_STYLE (style->rc_style))
#define NEW_THEME_DATA(rc_style)          (SMOOTH_RC_STYLE (rc_style))
#define SET_THEME_DATA(rc_style, data)    (SMOOTH_RC_DATA (rc_style))
#endif

#if GTK1
#define SMOOTH_RC_DATA(rc_style)          ((SmoothRcStyle *) ((rc_style)->engine_data))

#define THEME_DATA(style)                 ((SmoothRcStyle *) (((GtkStyle *)style)->engine_data))
#define NEW_THEME_DATA(rc_style)          ((SmoothRcStyle *) (g_new0 (SmoothRcStyle, 1)))
#define SET_THEME_DATA(rc_style, data)    (rc_style->engine_data=data)

#define PANED_HANDLE_SIZE(style)(THEME_DATA(style)->paned_handle_size)
#endif

#define REAL_SLIDERS(style)(THEME_DATA(style)->real_sliders)
#define RESIZE_GRIP(style)(THEME_DATA(style)->resize_grip)
#define DO_CHECK_LINE_THICKNESS(line,thickness)(((line==SMOOTH_LINE_BEVELED) || (line==SMOOTH_LINE_FLAT) || (line==SMOOTH_LINE_NONE))?thickness:2)

#define PART_STYLE(part)(THEME_PART(part)->style)
#define PART_XPADDING(part)(THEME_PART(part)->ypadding)
#define PART_YPADDING(part)(THEME_PART(part)->xpadding)

#define LINE_STYLE(style, part)(((part) && THEME_PART(part)->use_line)?THEME_PART(part)->line.style:THEME_DATA(style)->line.style)
#define LINE_THICKNESS(style, part) (((part) && THEME_PART(part)->use_line)?DO_CHECK_LINE_THICKNESS(THEME_PART(part)->line.style, THEME_PART(part)->line.thickness):DO_CHECK_LINE_THICKNESS(THEME_DATA(style)->line.style, THEME_DATA(style)->line.thickness))

#define EDGE_PART(style)(&THEME_DATA(style)->edge)
#define BACKGROUND_PART(style)(&THEME_DATA(style)->background)

#define EDGE_LINE_STYLE(style, part)((((part) && THEME_PART(part)->edge.use_line))?THEME_PART(part)->edge.line.style:(EDGE_PART(style)->use_line?EDGE_PART(style)->line.style:LINE_STYLE(style, part)))
#define EDGE_LINE_THICKNESS(style, part) ((((part) && THEME_PART(part)->edge.use_line))?DO_CHECK_LINE_THICKNESS(THEME_PART(part)->edge.line.style, THEME_PART(part)->edge.line.thickness):(EDGE_PART(style)->use_line?DO_CHECK_LINE_THICKNESS(EDGE_PART(style)->line.style, EDGE_PART(style)->line.thickness):LINE_THICKNESS(style, part)))

#define GRIP_PART(style)(&THEME_DATA(style)->grip)
#define GRIP_COUNT(style)(GRIP_PART(style)->count)
#define GRIP_SPACING(style)(GRIP_PART(style)->spacing)
#define GRIP_OVERLAP_TOOLBAR(style)(GRIP_PART(style)->overlap)

#define CHECK_PART(style)(&THEME_DATA(style)->check)
#define CHECK_MOTIF(style)(CHECK_PART(style)->motif)

#define OPTION_PART(style)(&THEME_DATA(style)->option)
#define OPTION_MOTIF(style)(THEME_DATA(style)->option.motif)

#define TROUGH_PART(style)(&THEME_DATA(style)->trough)
#define TROUGH_SHOW_VALUE(style) (THEME_DATA(style)->trough.show_value)
#define PROGRESS_PART(style)(&THEME_DATA(style)->progress)

/* macros for retrieving fill/background properties */
#define FILL_STYLE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.style:THEME_DATA(style)->fill.style)
#define FILL_GRADIENT_DIRECTION(style, part, orientation) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.gradient_direction[orientation]:THEME_DATA(style)->fill.gradient_direction[orientation])
#define FILL_QUADRATIC_GRADIENT(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.quadratic_gradient:THEME_DATA(style)->fill.quadratic_gradient)
#define FILL_SHADE1_VALUE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.shade1:THEME_DATA(style)->fill.shade1)
#define FILL_SHADE2_VALUE(style, part) (((part) && THEME_PART(part)->use_fill)?THEME_PART(part)->fill.shade2:THEME_DATA(style)->fill.shade2)
#define FILL_COLOR1(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.use_color1[state])?THEME_PART(part)->fill.color1[state]:((THEME_DATA(style)->fill.use_color1[state])?THEME_DATA(style)->fill.color1[state]:style->bg[state])):((THEME_DATA(style)->fill.use_color1[state])?THEME_DATA(style)->fill.color1[state]:style->bg[state]))
#define FILL_COLOR2(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.use_color2[state])?THEME_PART(part)->fill.color2[state]:((THEME_DATA(style)->fill.use_color2[state])?THEME_DATA(style)->fill.color2[state]:style->bg[state])):((THEME_DATA(style)->fill.use_color2[state])?THEME_DATA(style)->fill.color2[state]:style->bg[state]))
#define FILL_FILE_NAME(style, part, state) (((part) && THEME_PART(part)->use_fill)?((THEME_PART(part)->fill.file_name[state])?THEME_PART(part)->fill.file_name[state]:((THEME_DATA(style)->fill.file_name[state])?THEME_DATA(style)->fill.file_name[state]:NULL)):((THEME_DATA(style)->fill.file_name[state])?THEME_DATA(style)->fill.file_name[state]:NULL))

#define ARROW_STYLE(style)(THEME_DATA(style)->arrow.style)
#define SOLID_ARROW(style)(THEME_DATA(style)->arrow.solid)
#define ETCHED_ARROW(style)(THEME_DATA(style)->arrow.etched)
#define ARROW_XPADDING(part)(THEME_DATA(style)->arrow.ypadding)
#define ARROW_YPADDING(part)(THEME_DATA(style)->arrow.xpadding)

#ifdef GTK1
#define FOCUS_INTERIOR(style)(THEME_DATA(style)->focus.interior)
#define FOCUS_WIDTH(style)(THEME_DATA(style)->focus.width)
#define FOCUS_PAD(style)(THEME_DATA(style)->focus.pad)
#endif

#define FOCUS_USE_FOREGROUND(style, state)(THEME_DATA(style)->focus.use_foreground[state])
#define FOCUS_FOREGROUND(style, state)(THEME_DATA(style)->focus.foreground[state])

#define FOCUS_USE_PATTERN(style, state)(THEME_DATA(style)->focus.pattern[state]!=NULL)
#define FOCUS_PATTERN(style, state)(THEME_DATA(style)->focus.pattern[state])

#ifdef GTK1
  #define RANGE_SLIDER_WIDTH(style)(THEME_DATA(style)->range.slider_width)
  #define RANGE_TROUGH_BORDER(style)(THEME_DATA(style)->range.trough_border)
  #define RANGE_STEPPER_SIZE(style)(THEME_DATA(style)->range.stepper_size)
  #define RANGE_STEPPER_SPACING(style)(THEME_DATA(style)->range.stepper_spacing)
  
  #define SCALE_SLIDER_LENGTH(style)(THEME_DATA(style)->scale.slider_length)

  #define SCROLLBAR_MIN_SLIDER_LENGTH(style)(THEME_DATA(style)->scrollbar.min_slider_length)
#endif

#define BUFFERED_FILL(style)(THEME_DATA(style)->buffered_fill)

struct _smooth_line_style {
  gint style;
  gint thickness;
};

struct _smooth_fill_style {
  gint style;//none/flat/gradient/shaded

  gint gradient_direction[2];//horizontal/vertical/fdiagonal/bdiagonal
  gint quadratic_gradient;

  gfloat shade1;//0.0/2.5
  gfloat shade2;//0.0/2.5

  gboolean use_color1[5];//GtkStateType
  gboolean use_color2[5];//GtkStateType

  GdkColor color1[5];//GtkStateType
  GdkColor color2[5];//GtkStateType

  gchar * file_name[5];//GtkStateType
};

struct _smooth_edge_style {
  gint style;

  smooth_line_style line;
  smooth_fill_style fill;
  gboolean use_line;
};

struct _smooth_focus_style {
#ifdef GTK1
  gboolean interior;
  gint width;
  gint pad;
#endif
  gboolean use_foreground[5];//GtkStateType
  GdkColor foreground[5];//GtkStateType

  gchar * pattern[5];//GtkStateType
};

struct _smooth_part_style {
  gint style;

  smooth_edge_style edge;

  smooth_line_style line;
  smooth_fill_style fill;

  gboolean use_line;
  gboolean use_fill;

  gchar * file_name;
  GdkPixmap * part;

  gint xpadding;
  gint ypadding;
};

struct _smooth_bg_style {
  smooth_part_style part;
};

struct _smooth_fg_style {
  smooth_part_style part;
};

struct _smooth_grip_style {
  smooth_part_style part;

  gint count;
  gint spacing;
  gboolean overlap;
};

struct _smooth_check_style {
  smooth_part_style part;
  gboolean motif;  
};

struct _smooth_option_style {
  smooth_part_style part;
  gboolean motif;  
};

struct _smooth_arrow_style {
  gint style;
  gboolean solid;
  gboolean etched;

  gint xpadding;
  gint ypadding;

  /*smooth_part_style part;
  gint border;
  gint fill;*/
};

struct _smooth_button_style {
  smooth_part_style part;
  gboolean default_triangle;

  gboolean use_button_default;

  smooth_part_style button_default;
};

struct _smooth_tab_style {
  smooth_part_style part;

  gboolean use_active_tab;

  smooth_part_style active_tab;
};

struct _smooth_trough_style {
  smooth_part_style part;
  gboolean show_value;
};

struct _SmoothRcStyle
{
  #if GTK2
  GtkRcStyle parent_instance;
  #endif

  #if GTK1
  gint			  refcount;
  #endif
  
  gboolean buffered_fill;
  
  struct {
    gboolean has_dark[5];//GtkStateType
    GdkColor dark[5];//GtkStateType

    gboolean has_light[5];//GtkStateType
    GdkColor light[5];//GtkStateType

    gboolean has_mid[5];//GtkStateType
    GdkColor mid[5];//GtkStateType

    gboolean has_midlight[5];//GtkStateType
    GdkColor midlight[5];//GtkStateType

    gboolean has_middark[5];//GtkStateType
    GdkColor middark[5];//GtkStateType
  } colors;

  gboolean		  real_sliders;
  gboolean		  resize_grip;
  
  smooth_fill_style	  fill;
  smooth_line_style	  line;
  smooth_edge_style	  edge;

  smooth_focus_style	  focus;

  smooth_bg_style	  background;
  smooth_fg_style	  foreground;

  smooth_trough_style     trough;

  smooth_part_style       progress;

  smooth_grip_style	  grip;
  smooth_check_style	  check;
  smooth_option_style	  option;
  smooth_arrow_style      arrow;
  smooth_button_style	  button;
  smooth_tab_style	  tabs;

  #if GTK1
  struct {
    gint slider_width;
    gint trough_border;
    gint stepper_size;
    gint stepper_spacing;
  } range;

  struct {
    gint slider_length;
  } scale;

  struct {
    gint min_slider_length;
  } scrollbar;

  gint			  xthickness;
  gint			  ythickness;

  guint16		  paned_handle_size;
  #endif
};

void smooth_rc_style_init (SmoothRcStyle *style);

#if GTK2
struct _SmoothRcStyleClass
{
  GtkRcStyleClass parent_class;
};

void smooth_rc_style_register_type (GTypeModule *module);
#endif

#if GTK1
void
smooth_rc_style_merge (GtkRcStyle * dest,
                       GtkRcStyle * src);
		       
guint 
smooth_rc_style_parse (GScanner * scanner, 
                       GtkRcStyle * rc_style);

struct _SmoothRcProperty
{
  gchar * class_name;
  gchar * property_name;
  GtkArg value;
};
#endif

/* tab part styles*/
smooth_part_style *smooth_tab_part(GtkStyle * style, gboolean for_active_tab);

gint smooth_tab_get_style(GtkStyle * style, gboolean for_active_tab);

smooth_fill_style *smooth_tab_fill(GtkStyle * style, gboolean for_active_tab);

gint smooth_tab_edge_line_style(GtkStyle * style, gboolean for_active_tab);
gint smooth_tab_edge_line_thickness(GtkStyle * style, gboolean for_active_tab);

/* button part styles*/
smooth_part_style *smooth_button_part(GtkStyle * style, gboolean for_default_button);

gint smooth_button_get_style(GtkStyle * style, gboolean for_default_button);

gboolean smooth_button_default_triangle(GtkStyle * style);

smooth_fill_style *smooth_button_fill(GtkStyle * style, gboolean for_default_button);

gint smooth_button_edge_line_style(GtkStyle * style, gboolean for_default_button);
gint smooth_button_edge_line_thickness(GtkStyle * style, gboolean for_default_button);
