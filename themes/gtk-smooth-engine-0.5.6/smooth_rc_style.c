#include "smooth_style.h"
#include "smooth_rc_style.h"
#include <stdio.h>

/* tab part styles*/
smooth_part_style 
*smooth_tab_part(GtkStyle * style, gboolean for_active_tab)
{
  smooth_tab_style tabs = THEME_DATA(style)->tabs;
  
  if ((for_active_tab) && (tabs.use_active_tab))
    return &THEME_DATA(style)->tabs.active_tab;
  else
    return THEME_PART(&THEME_DATA(style)->tabs);
}

gint
smooth_tab_get_style(GtkStyle * style, gboolean for_active_tab)
{
  smooth_tab_style tabs = THEME_DATA(style)->tabs;
  smooth_part_style active_tab = THEME_DATA(style)->tabs.active_tab;
  
  if ((for_active_tab) && (tabs.use_active_tab))
    return active_tab.style;
  else
    return THEME_PART(&tabs)->style;
}

smooth_fill_style *
smooth_tab_fill(GtkStyle * style, gboolean for_active_tab)
{
  smooth_tab_style tabs = THEME_DATA(style)->tabs;
  smooth_part_style active_tab = THEME_DATA(style)->tabs.active_tab;
  
  if ((for_active_tab) && (tabs.use_active_tab) && (active_tab.use_fill))
    return &THEME_DATA(style)->tabs.active_tab.fill;
  else
    return &THEME_PART(&THEME_DATA(style)->tabs)->fill;
}

gint
smooth_tab_edge_line_style(GtkStyle * style, gboolean for_active_tab)
{
  smooth_tab_style tabs = THEME_DATA(style)->tabs;
  smooth_part_style active_tab = THEME_DATA(style)->tabs.active_tab;
  
  if ((for_active_tab) && (tabs.use_active_tab) && (active_tab.edge.use_line || active_tab.use_line))
    return EDGE_LINE_STYLE(style, &active_tab);
  else
    return EDGE_LINE_STYLE(style, THEME_PART(&tabs));
}

gint
smooth_tab_edge_line_thickness(GtkStyle * style, gboolean for_active_tab)
{
  smooth_tab_style tabs = THEME_DATA(style)->tabs;
  smooth_part_style active_tab = THEME_DATA(style)->tabs.active_tab;
  
  if ((for_active_tab) && (tabs.use_active_tab) && (active_tab.edge.use_line || active_tab.use_line))
    return EDGE_LINE_THICKNESS(style, &active_tab);
  else
    return EDGE_LINE_THICKNESS(style, THEME_PART(&tabs));
}

/* button part styles*/
smooth_part_style 
*smooth_button_part(GtkStyle * style, gboolean for_button_default)
{
  smooth_button_style button = THEME_DATA(style)->button;
  
  if ((for_button_default) && (button.use_button_default))
    return &THEME_DATA(style)->button.button_default;
  else
    return THEME_PART(&THEME_DATA(style)->button);
}

gint
smooth_button_get_style(GtkStyle * style, gboolean for_button_default)
{
  smooth_button_style button = THEME_DATA(style)->button;
  smooth_part_style button_default = THEME_DATA(style)->button.button_default;
  
  if ((for_button_default) && (button.use_button_default))
    return button_default.style;
  else
    return THEME_PART(&button)->style;
}

gboolean
smooth_button_default_triangle(GtkStyle * style)
{
  smooth_button_style button = THEME_DATA(style)->button;
  smooth_part_style button_default = THEME_DATA(style)->button.button_default;
  
  if ((button.use_button_default))
    return ((button_default.style==SMOOTH_BUTTON_DEFAULT_TRIANGLE) || (button.default_triangle));
  else
    return (button.default_triangle);
}

smooth_fill_style *
smooth_button_fill(GtkStyle * style, gboolean for_button_default)
{
  smooth_button_style button = THEME_DATA(style)->button;
  smooth_part_style button_default = THEME_DATA(style)->button.button_default;
  
  if ((for_button_default) && (button.use_button_default) && (button_default.use_fill))
    return &THEME_DATA(style)->button.button_default.fill;
  else
    return &THEME_PART(&THEME_DATA(style)->button)->fill;
}

gint
smooth_button_edge_line_style(GtkStyle * style, gboolean for_button_default)
{
  smooth_button_style button = THEME_DATA(style)->button;
  smooth_part_style button_default = THEME_DATA(style)->button.button_default;
  
  if ((for_button_default) && (button.use_button_default) && (button_default.edge.use_line || button_default.use_line))
    return EDGE_LINE_STYLE(style, &button_default);
  else
    return EDGE_LINE_STYLE(style, THEME_PART(&button));
}

gint
smooth_button_edge_line_thickness(GtkStyle * style, gboolean for_button_default)
{
  smooth_button_style button = THEME_DATA(style)->button;
  smooth_part_style button_default = THEME_DATA(style)->button.button_default;
  
  if ((for_button_default) && (button.use_button_default) && (button_default.edge.use_line || button_default.use_line))
    return EDGE_LINE_THICKNESS(style, &button_default);
  else
    return EDGE_LINE_THICKNESS(style, THEME_PART(&button));
}

#if GTK1
  #define GtkSettings  int
#endif

#if GTK2
static void   smooth_rc_style_class_init (SmoothRcStyleClass *klass);
static guint  smooth_rc_style_parse (GtkRcStyle *rc_style, GtkSettings *settings,
					     GScanner *scanner);

static void   smooth_rc_style_merge (GtkRcStyle *dest, GtkRcStyle *src);

static GtkRcStyleClass *parent_rc_class;

GType smooth_type_rc_style = 0;
#endif

enum
  {
    TOKEN_GRADIENT = G_TOKEN_LAST + 1,

    TOKEN_REAL_SLIDERS,
    TOKEN_RESIZE_GRIP,

    TOKEN_STYLE,

    TOKEN_FILE,

    TOKEN_FILL,
    TOKEN_VDIRECTION,
    TOKEN_HDIRECTION,
    TOKEN_COLOR1,
    TOKEN_COLOR2,
    TOKEN_SHADE1_VALUE,
    TOKEN_SHADE2_VALUE,
    TOKEN_QUADRATIC_GRADIENT,

    TOKEN_EDGE,

    TOKEN_LINE,
    TOKEN_THICKNESS,

    TOKEN_FOREGROUND,

    TOKEN_ARROW,
    TOKEN_SOLID,
    TOKEN_ETCHED,

    TOKEN_FOCUS,
    TOKEN_PATTERN,

    TOKEN_BUTTON,
    TOKEN_BUTTON_DEFAULT,
    TOKEN_DEFAULT_TRIANGLE,

    TOKEN_TABS,
    TOKEN_ACTIVE_TAB,

    TOKEN_PROGRESS,
    
    TOKEN_TROUGH,
    TOKEN_TROUGH_SHOW_VALUE,
    
    TOKEN_GRIP,
    TOKEN_COUNT,
    TOKEN_SPACING,
    TOKEN_TOOLBAR_OVERLAP,
     
    TOKEN_MOTIF,

    TOKEN_CHECK,
    TOKEN_OPTION,

    TOKEN_XPADDING,
    TOKEN_YPADDING,

    TOKEN_DEPRECATED_TABSTYLE,//backward compatibility for 0.5.2 & 0.5.4
    
    #if GTK1
    TOKEN_XTHICKNESS,
    TOKEN_YTHICKNESS,
    #endif
  };
  
static struct
  {
    gchar       *name;
    guint        token;
  }

theme_symbols[] =
{
  { "use_gradient",        TOKEN_GRADIENT },

  { "real_sliders",        TOKEN_REAL_SLIDERS },
  { "resize_grip",         TOKEN_RESIZE_GRIP },

  { "style",               TOKEN_STYLE },

  { "file",                TOKEN_FILE },

  { "fill",                TOKEN_FILL },
  { "vdirection",          TOKEN_VDIRECTION },
  { "hdirection",          TOKEN_HDIRECTION },
  { "color1",              TOKEN_COLOR1 },
  { "color2",              TOKEN_COLOR2 },
  { "shade1",              TOKEN_SHADE1_VALUE },
  { "shade2",              TOKEN_SHADE2_VALUE },
  { "quadratic",           TOKEN_QUADRATIC_GRADIENT },

  { "edge",                TOKEN_EDGE },

  { "line",                TOKEN_LINE },
  { "thickness",           TOKEN_THICKNESS },

  { "foreground",          TOKEN_FOREGROUND },

  { "arrow",     	   TOKEN_ARROW },
  { "solid",               TOKEN_SOLID },
  { "etched",              TOKEN_ETCHED },

  { "focus",               TOKEN_FOCUS },
  { "pattern",             TOKEN_PATTERN },

  { "button",              TOKEN_BUTTON },
  { "default",             TOKEN_BUTTON_DEFAULT },
  { "show_triangle",       TOKEN_DEFAULT_TRIANGLE },

  { "tabs",                TOKEN_TABS },
  { "active_tab",          TOKEN_ACTIVE_TAB },

  { "progress",            TOKEN_PROGRESS },

  { "trough",              TOKEN_TROUGH },
  { "show_value",          TOKEN_TROUGH_SHOW_VALUE },

  { "grip",                TOKEN_GRIP },
  { "count",               TOKEN_COUNT },
  { "spacing",             TOKEN_SPACING },
  { "toolbar_overlap",     TOKEN_TOOLBAR_OVERLAP },

  { "motif",               TOKEN_MOTIF },
  { "check",               TOKEN_CHECK },

  { "option",              TOKEN_OPTION },

  { "xpadding",            TOKEN_XPADDING },
  { "ypadding",            TOKEN_YPADDING },

  { "tab_style",           TOKEN_DEPRECATED_TABSTYLE },//backward compatibility for 0.5.2 & 0.5.4

  #if GTK1
  { "xthickness",          TOKEN_XTHICKNESS },
  { "ythickness",          TOKEN_YTHICKNESS },
  #endif
};

static guint n_theme_symbols = sizeof(theme_symbols) / sizeof(theme_symbols[0]);

static gboolean 
TranslateFillStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("flat") || is_enum("solid"))
    *retval = SMOOTH_FILL_SOLID;
  else if (is_enum("gradient"))
    *retval = SMOOTH_FILL_GRADIENT;
  else if (is_enum("shade_gradient") || is_enum("shaded") || is_enum("shade"))
    *retval = SMOOTH_FILL_SHADE_GRADIENT;
  else if (is_enum("pixbuf") || is_enum("pixmap") || is_enum("xpm"))
    *retval = SMOOTH_FILL_PIXBUF;
  else
    return FALSE; 
  return TRUE;
}

static gboolean 
TranslateGradientDirectionName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("horizontal"))
    *retval = GDK_GRADIENT_HORIZONTAL;
  else if (is_enum("vertical"))
    *retval = GDK_GRADIENT_VERTICAL;
  else if (is_enum("fdiagonal") || is_enum("forward_diagonal") || is_enum("forwarddiagonal") || is_enum("ndiagonal") || is_enum("northern_diagonal") || is_enum("northerndiagonal"))
    *retval = GDK_GRADIENT_NORTHERN_DIAGONAL;
  else if (is_enum("bdiagonal") || is_enum("backward_diagonal") || is_enum("backwarddiagonal") || is_enum("sdiagonal") || is_enum("southern_diagonal") || is_enum("southerndiagonal"))
    *retval = GDK_GRADIENT_SOUTHERN_DIAGONAL;
  else
    return FALSE; 
  return TRUE;
}

static gboolean 
TranslateLineStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("none"))
    *retval = SMOOTH_LINE_NONE;
  else if (is_enum("flat"))
    *retval = SMOOTH_LINE_FLAT;
  else if (is_enum("thin"))
    *retval = SMOOTH_LINE_THIN;
  else if (is_enum("soft"))
    *retval = SMOOTH_LINE_SOFT;
  else if (is_enum("smoothbevel"))
    *retval = SMOOTH_LINE_SMOOTHBEVEL;
  else if (is_enum("bevel"))
    *retval = SMOOTH_LINE_BEVELED;
  else if (is_enum("standard") || is_enum("normal") || is_enum("default"))
    *retval = SMOOTH_LINE_STANDARD;
  else if (is_enum("smooth"))
    *retval = SMOOTH_LINE_SMOOTHED;
  else if (is_enum("cold") || is_enum("wonderland"))
    *retval = SMOOTH_LINE_COLD;
  else if (is_enum("win32") || is_enum("windows") || is_enum("redmond"))
    *retval = SMOOTH_LINE_WIN32;
  else
    return FALSE; 

  return TRUE;
}

static gboolean 
TranslateOptionStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("none"))
    *retval = NO_OPTION;
  else if (is_enum("circle"))
    *retval = CIRCLE_OPTION;
  else if (is_enum("diamond"))
    *retval = DIAMOND_OPTION;
  else if (is_enum("square"))
    *retval = SQUARE_OPTION;
  else if (is_enum("xpm"))
    *retval = XPM_OPTION;
  else
    return FALSE; 

  return TRUE;
}

static gboolean 
TranslateButtonDefaultStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("gtk") || is_enum("gtk1") || is_enum("default") || is_enum("normal") || is_enum("standard"))
    *retval = SMOOTH_BUTTON_DEFAULT_NORMAL;
  else if (is_enum("win32") || is_enum("windows") || is_enum("redmond"))
    *retval = SMOOTH_BUTTON_DEFAULT_WIN32;
  else if (is_enum("triangle"))
    *retval = SMOOTH_BUTTON_DEFAULT_TRIANGLE;
  else if (is_enum("none"))
    *retval = SMOOTH_BUTTON_DEFAULT_NONE;
  else
    return FALSE; 

  return TRUE;
}

static gboolean 
TranslateTabStyleName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("square") || is_enum("default") || is_enum("normal") || is_enum("standard"))
    *retval = SMOOTH_TAB_NORMAL;
  else if (is_enum("round"))
    *retval = SMOOTH_TAB_ROUND;
  else if (is_enum("triangle"))
    *retval = SMOOTH_TAB_TRIANGLE;
  else if (is_enum("xpm"))
    *retval = SMOOTH_TAB_PIXBUF;
  else
    return FALSE; 

  return TRUE;
}

static gboolean 
TranslateBooleanName (gchar * str, gint *retval)
{
#define is_enum(XX)  (g_ascii_strncasecmp(str, XX, strlen(XX))==0)
  if (is_enum("TRUE") || is_enum("T") || is_enum("YES") || is_enum("Y"))
    *retval = TRUE;
  else if (is_enum("FALSE") || is_enum("F") || is_enum("NO") || is_enum("N"))
    *retval = FALSE;
  else
    return FALSE; 

  return TRUE;
}

static void color_merge (GdkColor *dest_color, GdkColor *src_color)
{
  dest_color->red = src_color->red;
  dest_color->green = src_color->green;
  dest_color->blue = src_color->blue;
}

static void part_init (SmoothRcStyle *style, smooth_part_style *part, gint partstyle)
{
  gint i;
  
  part->style      	= partstyle;

  part->use_line  	= FALSE;
  part->line.style      = DEFAULT_LINESTYLE;
  part->line.thickness  = DEFAULT_LINETHICKNESS;

  part->use_fill  	= FALSE;
  part->fill.style      = DEFAULT_FILLSTYLE;
  part->fill.gradient_direction[0] = DEFAULT_HGRADIENTDIRECTION;
  part->fill.gradient_direction[1] = DEFAULT_VGRADIENTDIRECTION;
  part->fill.quadratic_gradient = FALSE;
  part->fill.shade1 = 1.3;
  part->fill.shade2 = 0.7;

  for (i=0; i < 5; i++) {
    part->fill.use_color1[i] = FALSE;
    part->fill.use_color2[i] = FALSE;
    part->fill.file_name[i] = NULL;
  }

  part->edge.use_line        = FALSE;
  part->edge.line.style      = DEFAULT_LINESTYLE;
  part->edge.line.thickness  = DEFAULT_LINETHICKNESS;

  part->xpadding      	= 0;
  part->ypadding  	= 0;
}

void smooth_rc_style_init (SmoothRcStyle *style)
{
  gint i;
  style->real_sliders    = DEFAULT_REAL_SLIDERS;
  style->line.style      = DEFAULT_LINESTYLE;
  style->line.thickness  = DEFAULT_LINETHICKNESS;

  style->edge.style           = DEFAULT_EDGESTYLE;
  style->edge.use_line        = FALSE;
  style->edge.line.style      = DEFAULT_LINESTYLE;
  style->edge.line.thickness  = DEFAULT_LINETHICKNESS;

  style->fill.style      = DEFAULT_FILLSTYLE;
  style->fill.gradient_direction[0] = DEFAULT_HGRADIENTDIRECTION;
  style->fill.gradient_direction[1] = DEFAULT_VGRADIENTDIRECTION;
  style->fill.quadratic_gradient = FALSE;
  style->fill.shade1 = 1.3;
  style->fill.shade2 = 0.7;
  
  style->buffered_fill = TRUE;

  for (i=0; i < 5; i++) {
    style->fill.use_color1[i] = FALSE;
    style->fill.use_color2[i] = FALSE;
    style->fill.file_name[i] = NULL;

    style->focus.use_foreground[i] = FALSE;
    style->focus.pattern[i] = NULL;

    style->colors.has_light[i] = FALSE;
    style->colors.has_dark[i] = FALSE;
    style->colors.has_mid[i] = FALSE;
    style->colors.has_middark[i] = FALSE;
    style->colors.has_midlight[i] = FALSE;
  }

#ifdef GTK1
  style->focus.interior = FALSE;
  style->focus.width = 1;
  style->focus.pad = 0;

  style->range.slider_width = 7;
  style->range.trough_border = 1;
  style->range.stepper_size = 11;
  style->range.stepper_spacing = 1;

  style->scale.slider_length = 7;

  style->scrollbar.min_slider_length = 13;
#endif

  style->arrow.style     = DEFAULT_ARROWSTYLE;
  style->arrow.solid     = DEFAULT_SOLIDARROW;
  style->arrow.etched    = DEFAULT_ETCHEDARROW;
  style->arrow.xpadding      	= 0;
  style->arrow.ypadding  	= 0;

  part_init(style, THEME_PART(&style->grip), DEFAULT_GRIPSTYLE);

  style->grip.count      = DEFAULT_GRIPCOUNT;
  style->grip.spacing    = DEFAULT_GRIPSPACING;
  style->grip.overlap    = DEFAULT_GRIPOVERLAP;

  part_init(style, THEME_PART(&style->check), DEFAULT_CHECKSTYLE);
  style->check.motif = TRUE;

  part_init(style, THEME_PART(&style->option), DEFAULT_OPTIONSTYLE);
  style->option.motif = TRUE;

  part_init(style, &style->progress, 0);
  part_init(style, THEME_PART(&style->trough), 0);
  style->trough.show_value = DEFAULT_TROUGH_SHOW_VALUE;
  
  part_init(style, THEME_PART(&style->button), 0);
  part_init(style, &style->button.button_default, DEFAULT_BUTTONDEFAULTSTYLE);
  style->button.default_triangle = DEFAULT_BUTTONDEFAULTTRIANGLE;
  style->button.use_button_default = FALSE;
  
  part_init(style, THEME_PART(&style->tabs), DEFAULT_TABSTYLE);
  part_init(style, &style->tabs.active_tab, DEFAULT_TABSTYLE);
  style->tabs.use_active_tab	= FALSE;

  #if GTK1
  style->xthickness       = -1;
  style->ythickness       = -1;

  style->paned_handle_size	  = 10;
  style->buffered_fill = FALSE;
  #endif
}

static guint 
theme_parse_int (GScanner *scanner, 
                 GTokenType wanted_token, 
		 guint return_default,
		 gint *retval, 
		 gint lower_limit, 
		 gint upper_limit)
{
  guint token;
  gboolean negate=FALSE;
  
  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    {
      return G_TOKEN_EQUAL_SIGN;
    }

  if (g_scanner_peek_next_token (scanner) == '-')
    {
      g_scanner_get_next_token (scanner); /* eat sign */
      negate = TRUE;
    }

  token = g_scanner_get_next_token (scanner);

  if (token != G_TOKEN_INT)
    *retval = return_default;
  else
    *retval = (guint) scanner->value.v_int;

  if (negate) *retval = -(*retval); 

  if (*retval < lower_limit) *retval = lower_limit; 
  if ((*retval > upper_limit) && (upper_limit > lower_limit)) *retval = upper_limit; 
  
  return G_TOKEN_NONE;
}

static guint 
theme_parse_float (GScanner *scanner, 
                 GTokenType wanted_token, 
		 gfloat return_default, 
		 gfloat *retval, 
		 gfloat lower_limit, 
		 gfloat upper_limit)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    {
      return G_TOKEN_EQUAL_SIGN;
    }

  token = g_scanner_get_next_token (scanner);

  if (token != G_TOKEN_FLOAT)
    *retval = return_default;
  else
    *retval = scanner->value.v_float;
  
  if (*retval < lower_limit) *retval = lower_limit; 
  if ((*retval > upper_limit) && (upper_limit > lower_limit)) *retval = upper_limit; 
  
  return G_TOKEN_NONE;
}

static guint 
theme_parse_color (GScanner *scanner, 
                 GTokenType wanted_token, 
		 GdkColor *retval) 
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    {
      return G_TOKEN_EQUAL_SIGN;
    }

  return gtk_rc_parse_color (scanner, retval);
}

static guint 
theme_parse_custom_enum (GScanner *scanner, 
                         GTokenType wanted_token, 
			 SmoothTranslateEnumFunc translate_enum,
			 guint return_default,
			 gint *retval)
{
  guint token;
  gchar * str_value = NULL;
   
  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    {
      return G_TOKEN_EQUAL_SIGN;
    }

  token = g_scanner_get_next_token (scanner);

  if (token != G_TOKEN_IDENTIFIER)
    *retval = return_default;
  else
    if (!translate_enum(scanner->value.v_identifier, retval)) *retval = return_default;
  
  return G_TOKEN_NONE;
}

static guint 
theme_parse_boolean(GScanner *scanner,  
                    GTokenType wanted_token, 
		    gboolean return_default, 
		    guint *retval)
{
  guint token;
  gint result=0;
  
  token = theme_parse_custom_enum (scanner, wanted_token, TranslateBooleanName, return_default, &result);	
  
  *retval = result;
  
  return token;
}

static guint theme_parse_line (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_line_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateLineStyleName, DEFAULT_LINESTYLE,  &retval->style);
      break;
    case TOKEN_THICKNESS:
      token = theme_parse_int (scanner, TOKEN_THICKNESS, 2, &retval->thickness, 1, 10);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_fill (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_fill_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateFillStyleName, DEFAULT_FILLSTYLE,  &THEME_PART(retval)->style);
      break;
    case TOKEN_HDIRECTION:
      token = theme_parse_custom_enum(scanner, TOKEN_HDIRECTION, TranslateGradientDirectionName, DEFAULT_HGRADIENTDIRECTION,  &retval->gradient_direction[0]);
      break;
    case TOKEN_VDIRECTION:
      token = theme_parse_custom_enum(scanner, TOKEN_VDIRECTION, TranslateGradientDirectionName, DEFAULT_VGRADIENTDIRECTION,  &retval->gradient_direction[1]);
      break;
    case TOKEN_SHADE1_VALUE:
      token = theme_parse_float (scanner, TOKEN_SHADE1_VALUE, 1.3, &retval->shade1, 0.0, 2.5);
      break;
    case TOKEN_SHADE2_VALUE:
      token = theme_parse_float (scanner, TOKEN_SHADE2_VALUE, 0.7, &retval->shade2, 0.0, 2.5);
      break;
    case TOKEN_COLOR1:
      {
        GtkStateType state;
  
        token = g_scanner_get_next_token (scanner);
        if (token != TOKEN_COLOR1)
          return TOKEN_COLOR1;
  
        token = gtk_rc_parse_state (scanner, &state);
        if (token != G_TOKEN_NONE)
          return token;
  
        token = g_scanner_get_next_token (scanner);
        if (token != G_TOKEN_EQUAL_SIGN)
          return G_TOKEN_EQUAL_SIGN;

        retval->use_color1[state] = TRUE;
        token = gtk_rc_parse_color (scanner, &retval->color1[state]);
      }
      break;
    case TOKEN_COLOR2:
      {
        GtkStateType state;
  
        token = g_scanner_get_next_token (scanner);
        if (token != TOKEN_COLOR2)
          return TOKEN_COLOR2;
	  
        token = gtk_rc_parse_state (scanner, &state);
        if (token != G_TOKEN_NONE)
          return token;
  
        token = g_scanner_get_next_token (scanner);
        if (token != G_TOKEN_EQUAL_SIGN)
          return G_TOKEN_EQUAL_SIGN;

        retval->use_color2[state] = TRUE;
        token = gtk_rc_parse_color (scanner, &retval->color2[state]);
      }
      break;
    case TOKEN_FILE:
      {
        GtkStateType state;
  
        token = g_scanner_get_next_token (scanner);
        if (token != TOKEN_FILE)
          return TOKEN_FILE;
  
        token = gtk_rc_parse_state (scanner, &state);
        if (token != G_TOKEN_NONE)
          return token;
  
        token = g_scanner_get_next_token (scanner);
        if (token != G_TOKEN_EQUAL_SIGN)
          return G_TOKEN_EQUAL_SIGN;

        token = g_scanner_get_next_token (scanner);
        if (token == G_TOKEN_STRING)
#ifdef GTK1
          retval->file_name[state] = gtk_rc_find_pixmap_in_path(scanner, scanner->value.v_string);
#endif
#ifdef GTK2
          retval->file_name[state] = gtk_rc_find_pixmap_in_path(settings, scanner, scanner->value.v_string);
#endif
      }	
      break;
    case TOKEN_QUADRATIC_GRADIENT:
      token = theme_parse_boolean (scanner, TOKEN_QUADRATIC_GRADIENT, FALSE, &retval->quadratic_gradient);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static 
guint theme_parse_focus (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_focus_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_PATTERN:
      {
        GtkStateType state;
        
        token = g_scanner_get_next_token (scanner);
  
        token = gtk_rc_parse_state (scanner, &state);
        if (token != G_TOKEN_NONE)
          return token;

        token = g_scanner_get_next_token (scanner);
        if (token != G_TOKEN_EQUAL_SIGN)
          return G_TOKEN_EQUAL_SIGN;

        token = g_scanner_get_next_token (scanner);
        if (token == G_TOKEN_STRING)
          if (scanner->value.v_string)
            retval->pattern[state]= g_strdup(scanner->value.v_string);   
      }

      break;
    case TOKEN_FOREGROUND:
      {
        GtkStateType state;
  
        token = g_scanner_get_next_token (scanner);
        if (token != TOKEN_FOREGROUND)
          return TOKEN_FOREGROUND;
	  
        token = gtk_rc_parse_state (scanner, &state);
        if (token != G_TOKEN_NONE)
          return token;
  
        token = g_scanner_get_next_token (scanner);
        if (token != G_TOKEN_EQUAL_SIGN)
          return G_TOKEN_EQUAL_SIGN;

        retval->use_foreground[state] = TRUE;
        token = gtk_rc_parse_color (scanner, &retval->foreground[state]);
      }
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_edge (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_edge_style *retval)
{
  smooth_edge_style junk_edge;
  smooth_fill_style junk_fill;
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateEdgeStyleName, DEFAULT_EDGESTYLE, &retval->style);
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &retval->line);
      retval->use_line = TRUE;
      break;
    case TOKEN_EDGE:    
      token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &junk_edge);
      break;
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &junk_fill);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_arrow (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_arrow_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
      case TOKEN_STYLE:
	token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateArrowStyleName, DEFAULT_ARROWSTYLE, &retval->style);
	break;
	
      case TOKEN_SOLID:
	token = theme_parse_boolean (scanner, TOKEN_SOLID, DEFAULT_SOLIDARROW, &retval->solid);
	break;	  
	
      case TOKEN_ETCHED:
	token = theme_parse_boolean (scanner, TOKEN_ETCHED, DEFAULT_ETCHEDARROW, &retval->etched);
	break;	  
      case TOKEN_XPADDING:
        token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &retval->xpadding, -25, 25);
        break;
      case TOKEN_YPADDING:
        token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &retval->ypadding, -25, 25);
        break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_button_default (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_part_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
      case TOKEN_STYLE:
	token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateButtonDefaultStyleName, DEFAULT_BUTTONDEFAULTSTYLE, &THEME_PART(retval)->style);
	break;
	
      case TOKEN_LINE:
        token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
        THEME_PART(retval)->use_line = TRUE;
        break;

      case TOKEN_FILL :
        token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
        THEME_PART(retval)->use_fill = TRUE;
        break;
  
      case TOKEN_EDGE:
        token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
        break;

      case TOKEN_XPADDING:
        token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
        break;

      case TOKEN_YPADDING:
        token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
        break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_button (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_button_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
      case TOKEN_BUTTON_DEFAULT:
	token = theme_parse_button_default (settings, scanner, TOKEN_BUTTON_DEFAULT, &retval->button_default);
	retval->use_button_default = TRUE;
	break;	  

      case TOKEN_DEFAULT_TRIANGLE:
	token = theme_parse_boolean (scanner, TOKEN_DEFAULT_TRIANGLE, DEFAULT_BUTTONDEFAULTTRIANGLE,  &retval->default_triangle);
	break;	  

      case TOKEN_LINE:
        token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
        THEME_PART(retval)->use_line = TRUE;
        break;

      case TOKEN_FILL :
        token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
        THEME_PART(retval)->use_fill = TRUE;
        break;

      case TOKEN_EDGE:
        token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
        break;

      case TOKEN_XPADDING:
        token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
        break;

      case TOKEN_YPADDING:
        token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
        break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_active_tab (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_part_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
      case TOKEN_STYLE:
	token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateTabStyleName, DEFAULT_TABSTYLE, &THEME_PART(retval)->style);
	break;
	
      case TOKEN_LINE:
        token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
        THEME_PART(retval)->use_line = TRUE;
        break;

      case TOKEN_FILL :
        token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
        THEME_PART(retval)->use_fill = TRUE;
        break;
  
      case TOKEN_EDGE:
        token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
        break;

      case TOKEN_XPADDING:
        token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
        break;

      case TOKEN_YPADDING:
        token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
        break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_tab (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_tab_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
      case TOKEN_STYLE:
	token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateTabStyleName, DEFAULT_TABSTYLE, &THEME_PART(retval)->style);
	break;
	
      case TOKEN_ACTIVE_TAB:
	token = theme_parse_active_tab (settings, scanner, TOKEN_ACTIVE_TAB, &retval->active_tab);
	retval->use_active_tab = TRUE;
	break;	  

      case TOKEN_LINE:
        token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
        THEME_PART(retval)->use_line = TRUE;
        break;

      case TOKEN_FILL :
        token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
        THEME_PART(retval)->use_fill = TRUE;
        break;

      case TOKEN_EDGE:
        token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
        break;

      case TOKEN_XPADDING:
        token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
        break;

      case TOKEN_YPADDING:
        token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
        break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_option (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_option_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateOptionStyleName, DEFAULT_OPTIONSTYLE, &THEME_PART(retval)->style);
      break;
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
      THEME_PART(retval)->use_fill = TRUE;
      break;
    case TOKEN_EDGE:
      token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
      break;
    case TOKEN_MOTIF:
      token = theme_parse_boolean (scanner, TOKEN_MOTIF, TRUE, &retval->motif);
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
      THEME_PART(retval)->use_line = TRUE;
      break;
    case TOKEN_XPADDING:
      token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
      break;
    case TOKEN_YPADDING:
      token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_grip (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_grip_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateGripStyleName, DEFAULT_GRIPSTYLE,  &THEME_PART(retval)->style);
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
      THEME_PART(retval)->use_line = TRUE;
      break;
    case TOKEN_EDGE:
      token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
      break;
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
      THEME_PART(retval)->use_fill = TRUE;
      break;
    case TOKEN_XPADDING:
      token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
      break;
    case TOKEN_YPADDING:
      token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
      break;
    case TOKEN_COUNT:
      token = theme_parse_int (scanner, TOKEN_COUNT, DEFAULT_GRIPCOUNT, &retval->count, 1, -1);
      break;
    case TOKEN_SPACING:
      token = theme_parse_int (scanner, TOKEN_SPACING, DEFAULT_GRIPSPACING, &retval->spacing, 0, -1);
      break;
    case TOKEN_TOOLBAR_OVERLAP:
      token = theme_parse_boolean (scanner, TOKEN_TOOLBAR_OVERLAP, DEFAULT_GRIPOVERLAP, &retval->overlap);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_check (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_check_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_STYLE:
      token = theme_parse_custom_enum(scanner, TOKEN_STYLE, TranslateCheckStyleName, DEFAULT_CHECKSTYLE,  &THEME_PART(retval)->style);
      break;
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
      THEME_PART(retval)->use_fill = TRUE;
      break;
    case TOKEN_MOTIF:
      token = theme_parse_boolean (scanner, TOKEN_MOTIF, TRUE, &retval->motif);
      break;
    case TOKEN_EDGE:
      token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
      break;
    case TOKEN_XPADDING:
      token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
      break;
    case TOKEN_YPADDING:
      token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
      THEME_PART(retval)->use_line = TRUE;
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_generic_part (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_part_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
      THEME_PART(retval)->use_fill = TRUE;
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
      THEME_PART(retval)->use_line = TRUE;
      break;
    case TOKEN_EDGE:
      token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &THEME_PART(retval)->edge);
      break;
    case TOKEN_XPADDING:
      token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
      break;
    case TOKEN_YPADDING:
      token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

static guint theme_parse_trough_part (GtkSettings  *settings, GScanner *scanner, GTokenType wanted_token, smooth_trough_style *retval)
{
  guint token;

  token = g_scanner_get_next_token (scanner);
  if (token != wanted_token)
    {
      return wanted_token;
    }

  token = g_scanner_get_next_token (scanner);
  if (token != G_TOKEN_LEFT_CURLY)
    return G_TOKEN_LEFT_CURLY;

  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY) {
    switch (token) {
    case TOKEN_TROUGH_SHOW_VALUE:
      token = theme_parse_boolean (scanner, TOKEN_TROUGH_SHOW_VALUE, DEFAULT_TROUGH_SHOW_VALUE, &retval->show_value);
      break;
    case TOKEN_FILL :
      token = theme_parse_fill (settings, scanner, TOKEN_FILL, &THEME_PART(retval)->fill);
      THEME_PART(retval)->use_fill = TRUE;
      break;
    case TOKEN_LINE:
      token = theme_parse_line (settings, scanner, TOKEN_LINE, &THEME_PART(retval)->line);
      THEME_PART(retval)->use_line = TRUE;
      break;
    case TOKEN_XPADDING:
      token = theme_parse_int (scanner, TOKEN_XPADDING, 0, &THEME_PART(retval)->xpadding, -25, 25);
      break;
    case TOKEN_YPADDING:
      token = theme_parse_int (scanner, TOKEN_YPADDING, 0, &THEME_PART(retval)->ypadding, -25, 25);
      break;
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_RIGHT_CURLY;
      break;
    }

    token = g_scanner_peek_next_token (scanner);
  }

  g_scanner_get_next_token (scanner);
  token = G_TOKEN_NONE;

  return token;
}

#if GTK1
static void
smooth_gtk1_style_overides(SmoothRcStyle *smooth_style, SmoothRcProperty * smooth_prop)
{		       
  #define is_class(xx) ((xx) && (!strcmp(xx, smooth_prop->class_name)))
  #define is_prop(xx) ((xx) && (!strcmp(xx, smooth_prop->property_name)))

  if (is_class("GtkRange"))
  {
    GtkRangeClass *rangeclass = (GtkRangeClass *)gtk_type_class(gtk_range_get_type());
    if (is_prop("slider-width") || is_prop("slider_width")) 
        smooth_style->range.slider_width = smooth_prop->value.d.long_data;
    if (is_prop("stepper_size") || is_prop("stepper-size")) 
        smooth_style->range.stepper_size = smooth_prop->value.d.long_data;
    if (is_prop("stepper_spacing") || is_prop("stepper-spacing")) 
        smooth_style->range.stepper_spacing = smooth_prop->value.d.long_data;
  } 
  else
    if (is_class("GtkPaned"))
    {
      if (is_prop("handle-size") || is_prop("handle_size")) 
        smooth_style->paned_handle_size = smooth_prop->value.d.long_data;
    }
  else
    if (is_class("GtkScrollbar"))
    {
      if (is_prop("min_slider_length") || is_prop("min-slider-length")) 
        smooth_style->scrollbar.min_slider_length = smooth_prop->value.d.long_data;
    }
  else
    if (is_class("GtkScale"))
    {
      GtkScaleClass *scaleclass = gtk_type_class(gtk_scale_get_type());
      GtkRangeClass *rangeclass = (GtkRangeClass *)scaleclass;
      if (is_prop("slider_width") || is_prop("slider-width")) 
        rangeclass->slider_width = smooth_prop->value.d.long_data;
      if (is_prop("slider_length") || is_prop("slider-length")) 
        smooth_style->scale.slider_length = smooth_prop->value.d.long_data;
    }
  else
    if (is_class("GtkCheckButton"))
    {
      GtkCheckButtonClass *checkbuttonclass = (GtkCheckButtonClass*)gtk_type_class (gtk_check_button_get_type ());
  
      if (is_prop("indicator_size") || is_prop("indicator-size")) 
        checkbuttonclass->indicator_size = smooth_prop->value.d.long_data;
    }
  else
    if (is_class("GtkRadioButton"))
    {
      GtkCheckButtonClass *checkbuttonclass = (GtkCheckButtonClass*)gtk_type_class (gtk_radio_button_get_type ());

      if (is_prop("indicator_size") || is_prop("indicator-size"))  
        checkbuttonclass->indicator_size = smooth_prop->value.d.long_data;
    }
  else 
    if (is_class("GtkWidget"))
    {
      if (is_prop("interior_focus") || is_prop("interior-focus"))  
        smooth_style->focus.interior = smooth_prop->value.d.long_data;

      if (is_prop("focus_line_width") || is_prop("focus-line-width"))  
        smooth_style->focus.width = smooth_prop->value.d.long_data;

      if (is_prop("focus_padding ") || is_prop("focus-padding"))  
        smooth_style->focus.pad = smooth_prop->value.d.long_data;
    }

   
}

static guint
gtk_rc_parse_assignment (GScanner      *scanner,
			 SmoothRcProperty *prop)
{
  gboolean scan_identifier = scanner->config->scan_identifier;
  gboolean scan_symbols = scanner->config->scan_symbols;
  gboolean identifier_2_string = scanner->config->identifier_2_string;
  gboolean char_2_token = scanner->config->char_2_token;
  gboolean scan_identifier_NULL = scanner->config->scan_identifier_NULL;
  gboolean numbers_2_int = scanner->config->numbers_2_int;
  gboolean negate = FALSE;
  guint token;

  /* check that this is an assignment */
  if (g_scanner_get_next_token (scanner) != '=')
    return '=';

  /* adjust scanner mode */
  scanner->config->scan_identifier = TRUE;
  scanner->config->scan_symbols = FALSE;
  scanner->config->identifier_2_string = FALSE;
  scanner->config->char_2_token = TRUE;
  scanner->config->scan_identifier_NULL = FALSE;
  scanner->config->numbers_2_int = TRUE;

  /* parse optional sign */
  if (g_scanner_peek_next_token (scanner) == '-')
    {
      g_scanner_get_next_token (scanner); /* eat sign */
      negate = TRUE;
    }

  /* parse one of LONG, DOUBLE and STRING or, if that fails, create an unparsed compund */
  token = g_scanner_peek_next_token (scanner);
  switch (token)
    {
    case G_TOKEN_INT:
      g_scanner_get_next_token (scanner);
      prop->value.type = GTK_TYPE_LONG;
      prop->value.d.long_data = negate ? -scanner->value.v_int : scanner->value.v_int;
      token = G_TOKEN_NONE;
      break;
    case G_TOKEN_FLOAT:
      g_scanner_get_next_token (scanner);
      prop->value.type = GTK_TYPE_DOUBLE;
      prop->value.d.double_data = negate ? -scanner->value.v_float : scanner->value.v_float;
      token = G_TOKEN_NONE;
      break;
    case G_TOKEN_STRING:
      g_scanner_get_next_token (scanner);
      if (negate)
	token = G_TOKEN_INT;
      else
	{
          prop->value.type = GTK_TYPE_STRING;
          prop->value.d.string_data = scanner->value.v_string;
	  token = G_TOKEN_NONE;
	}
      break;
    case G_TOKEN_LEFT_CURLY :
      while (token != G_TOKEN_RIGHT_CURLY) {
        g_scanner_peek_next_token (scanner);   
        g_scanner_get_next_token (scanner);
        token = g_scanner_peek_next_token (scanner);
      } 
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_NONE;      
      break;      
    default:
      g_scanner_get_next_token (scanner);
      token = G_TOKEN_INT;
      break;
    }

  /* restore scanner mode */
  scanner->config->scan_identifier = scan_identifier;
  scanner->config->scan_symbols = scan_symbols;
  scanner->config->identifier_2_string = identifier_2_string;
  scanner->config->char_2_token = char_2_token;
  scanner->config->scan_identifier_NULL = scan_identifier_NULL;
  scanner->config->numbers_2_int = numbers_2_int;

  return token;
}
#endif

#if GTK2
static guint 
smooth_rc_style_parse (GtkRcStyle *rc_style,
                       GtkSettings  *settings,
		       GScanner   *scanner)
#endif
#if GTK1
guint 
smooth_rc_style_parse (GScanner * scanner, 
                       GtkRcStyle * rc_style)
#endif
{
  static GQuark scope_id = 0;
  SmoothRcStyle *smooth_style = NEW_THEME_DATA(rc_style);
  
  guint old_scope;
  guint token;
  guint i;

  #if GTK1
    GtkSettings  *settings=NULL; 
  
  smooth_style->refcount = 1;
  smooth_rc_style_init (smooth_style);
  #endif

  /* Set up a new scope in this scanner */
  if (!scope_id)
    {
      scope_id = g_quark_from_string ("theme_engine");
    }

  /* If we bail out due to errors, we don't reset the scope, so the
   * error messaging code can make sense of our tokens. */
  old_scope = g_scanner_set_scope (scanner, scope_id);

  /* Check if we already added our symbols to this scope */
  if (!g_scanner_lookup_symbol (scanner, theme_symbols[0].name))
    {
      #ifdef GTK1
        g_scanner_freeze_symbol_table (scanner);
      #endif 	
      for (i = 0; i < n_theme_symbols; i++)
	{
	  g_scanner_scope_add_symbol (scanner, scope_id, theme_symbols[i].name, 
				      GINT_TO_POINTER (theme_symbols[i].token));
	}
      #ifdef GTK1
        g_scanner_thaw_symbol_table (scanner);
      #endif 	
    }

  /* Read to go, now parse the top level */
  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
        case TOKEN_EDGE:
          token = theme_parse_edge (settings, scanner, TOKEN_EDGE, &smooth_style->edge);
          break;
	case TOKEN_FILL :
   	  token = theme_parse_fill (settings, scanner, TOKEN_FILL, &smooth_style->fill);
    	  break;
        case TOKEN_TABS:
          token = theme_parse_tab (settings, scanner, TOKEN_TABS, &smooth_style->tabs);
          break;
        case TOKEN_BUTTON:
          token = theme_parse_button (settings, scanner, TOKEN_BUTTON, &smooth_style->button);
          break;
	case TOKEN_REAL_SLIDERS:
	  token = theme_parse_boolean (scanner, TOKEN_REAL_SLIDERS, DEFAULT_REAL_SLIDERS, &smooth_style->real_sliders);
	  break;
	case TOKEN_RESIZE_GRIP:
	  token = theme_parse_boolean (scanner, TOKEN_RESIZE_GRIP, DEFAULT_RESIZE_GRIP, &smooth_style->resize_grip);
	  break;
	case TOKEN_LINE:
	  token = theme_parse_line (settings, scanner, TOKEN_LINE, &smooth_style->line);
	  break;
	case TOKEN_GRIP:
	  token = theme_parse_grip (settings, scanner, TOKEN_GRIP, &smooth_style->grip);
	  break;
	case TOKEN_ARROW:
	  token = theme_parse_arrow (settings, scanner, TOKEN_ARROW, &smooth_style->arrow);
	  break;	  
        case TOKEN_FOCUS:
          token = theme_parse_focus (settings, scanner, TOKEN_FOCUS, &smooth_style->focus);
          break;
	case TOKEN_PROGRESS:
	  token = theme_parse_generic_part (settings, scanner, TOKEN_PROGRESS, &smooth_style->progress);
	  break;
	case TOKEN_TROUGH:
	  token = theme_parse_trough_part (settings, scanner, TOKEN_TROUGH, &smooth_style->trough);
	  break;
	case TOKEN_CHECK:
	  token = theme_parse_check (settings, scanner, TOKEN_CHECK, &smooth_style->check);
	  break;
	case TOKEN_OPTION:
	  token = theme_parse_option (settings, scanner, TOKEN_OPTION, &smooth_style->option);
	  break;
	case TOKEN_DEPRECATED_TABSTYLE:
	  token = theme_parse_custom_enum(scanner, TOKEN_DEPRECATED_TABSTYLE, TranslateTabStyleName, DEFAULT_TABSTYLE, 
						&THEME_PART(&smooth_style->tabs)->style);
	  break;
	#if GTK1
	case TOKEN_XTHICKNESS:
          token = theme_parse_int (scanner, TOKEN_XTHICKNESS, 2, &smooth_style->xthickness, 0, 100);
	  break;	  
	case TOKEN_YTHICKNESS:
          token = theme_parse_int (scanner, TOKEN_YTHICKNESS, 2, &smooth_style->ythickness, 0, 100);
	  break;	  
	case G_TOKEN_IDENTIFIER:
	    {
	      SmoothRcProperty prop = {NULL, NULL, {1, NULL,}};
	      
	      g_scanner_get_next_token (scanner); /* eat type name */
	      
	      prop.class_name = g_strdup(scanner->value.v_identifier);
	      
	      if (g_scanner_get_next_token (scanner) != ':' ||
		  g_scanner_get_next_token (scanner) != ':')
		{
		  token = ':';
		  break;
		}
	      
	      g_scanner_get_next_token (scanner);

	      prop.property_name = g_strdup(scanner->value.v_identifier);
	      token = gtk_rc_parse_assignment (scanner, &prop);
	      if (token == G_TOKEN_NONE)
		  smooth_gtk1_style_overides(smooth_style, &prop);
      	      if (prop.class_name) g_free(prop.class_name);
      	      if (prop.property_name) g_free(prop.property_name);
	    }
	  break;
	#endif  
	default:
	  g_scanner_get_next_token (scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	{
          g_free (smooth_style);
	  return token;
	}

      token = g_scanner_peek_next_token (scanner);
    }

  g_scanner_get_next_token(scanner);

  SET_THEME_DATA(rc_style, smooth_style);
  
  g_scanner_set_scope (scanner, old_scope);

  return G_TOKEN_NONE;
}
	
void part_merge (smooth_part_style *dest_part, smooth_part_style *src_part)
{
  gint i;
  
  dest_part->style           = src_part->style;

  dest_part->use_line  	     = src_part->use_line;
  dest_part->line.style      = src_part->line.style;
  dest_part->line.thickness  = src_part->line.thickness;

  dest_part->use_fill  	     = src_part->use_fill;
  dest_part->fill.style = src_part->fill.style;
  dest_part->fill.quadratic_gradient = src_part->fill.quadratic_gradient;
  dest_part->fill.gradient_direction[0] = src_part->fill.gradient_direction[0];
  dest_part->fill.gradient_direction[1] = src_part->fill.gradient_direction[1];
  dest_part->fill.shade1 = src_part->fill.shade1;
  dest_part->fill.shade2 = src_part->fill.shade2;
  
  for (i=0; i < 5; i++) {
    dest_part->fill.use_color1[i] = src_part->fill.use_color1[i];
    if (src_part->fill.use_color1[i])
      color_merge(&dest_part->fill.color1[i], &src_part->fill.color1[i]);

    dest_part->fill.use_color2[i] = src_part->fill.use_color2[i];
    if (src_part->fill.use_color2[i])
      color_merge(&dest_part->fill.color2[i], &src_part->fill.color2[i]);

    if (src_part->fill.file_name[i]) {
      if (dest_part->fill.file_name[i])
        g_free(dest_part->fill.file_name[i]);

      dest_part->fill.file_name[i] = g_strdup(src_part->fill.file_name[i]);
    }
  }
  
  dest_part->edge.use_line  	  = src_part->edge.use_line;
  dest_part->edge.line.style      = src_part->edge.line.style;
  dest_part->edge.line.thickness  = src_part->edge.line.thickness;

  dest_part->xpadding  	     = src_part->xpadding;
  dest_part->ypadding  	     = src_part->ypadding;
}

#if GTK2
static void
smooth_rc_style_merge (GtkRcStyle * dest,
                       GtkRcStyle * src)
#endif
#if GTK1
void
smooth_rc_style_merge (GtkRcStyle * dest,
                       GtkRcStyle * src)
#endif
{
  gint i;
  #if GTK2
  parent_rc_class->merge (dest, src);
  #endif
  
  #if GTK2
  if (SMOOTH_IS_RC_STYLE (src)) 
  #endif
    {     
      SmoothRcStyle *src_data = SMOOTH_RC_DATA (src);
      SmoothRcStyle *dest_data = SMOOTH_RC_DATA (dest);

      if (!dest_data) {
        dest_data = NEW_THEME_DATA(dest);
        #if GTK1
        dest_data->xthickness       = src_data->xthickness;
        dest_data->ythickness       = src_data->ythickness;
        dest_data->paned_handle_size = src_data->paned_handle_size;

	dest_data->refcount         = 1;
        #endif
      } 	
      
      dest_data->real_sliders = src_data->real_sliders;
      dest_data->line.style = src_data->line.style;
      dest_data->line.thickness = src_data->line.thickness;

      dest_data->edge.use_line        = src_data->edge.use_line;
      dest_data->edge.line.style      = src_data->edge.line.style;
      dest_data->edge.line.thickness  = src_data->edge.line.thickness;

      dest_data->fill.style = src_data->fill.style;
      dest_data->fill.quadratic_gradient = src_data->fill.quadratic_gradient;
      dest_data->fill.gradient_direction[0] = src_data->fill.gradient_direction[0];
      dest_data->fill.gradient_direction[1] = src_data->fill.gradient_direction[1];
      dest_data->fill.shade1 = src_data->fill.shade1;
      dest_data->fill.shade2 = src_data->fill.shade2;

      for (i=0; i < 5; i++) {
        dest_data->fill.use_color1[i] = src_data->fill.use_color1[i];
        if (src_data->fill.use_color1[i])
          color_merge(&dest_data->fill.color1[i], &src_data->fill.color1[i]);

        dest_data->fill.use_color2[i] = src_data->fill.use_color2[i];
        if (src_data->fill.use_color2[i])
          color_merge(&dest_data->fill.color2[i], &src_data->fill.color2[i]);

        dest_data->colors.has_dark[i] = src_data->colors.has_dark[i];
        if (src_data->colors.has_dark[i])
          color_merge(&dest_data->colors.dark[i], &src_data->colors.dark[i]);

        dest_data->colors.has_light[i] = src_data->colors.has_light[i];
        if (src_data->colors.has_light[i])
          color_merge(&dest_data->colors.light[i], &src_data->colors.light[i]);

        dest_data->colors.has_mid[i] = src_data->colors.has_mid[i];
        if (src_data->colors.has_mid[i])
          color_merge(&dest_data->colors.mid[i], &src_data->colors.mid[i]);

        dest_data->colors.has_middark[i] = src_data->colors.has_middark[i];
        if (src_data->colors.has_middark[i])
          color_merge(&dest_data->colors.middark[i], &src_data->colors.middark[i]);

        dest_data->colors.has_midlight[i] = src_data->colors.has_midlight[i];
        if (src_data->colors.has_midlight[i])
          color_merge(&dest_data->colors.midlight[i], &src_data->colors.midlight[i]);

        if (src_data->fill.file_name[i]) {
          if (dest_data->fill.file_name[i])
            g_free(dest_data->fill.file_name[i]);

          dest_data->fill.file_name[i] = g_strdup(src_data->fill.file_name[i]);
        }
        
        if (src_data->focus.pattern[i]) {
          if (dest_data->focus.pattern[i])
            g_free(dest_data->focus.pattern[i]);

          dest_data->focus.pattern[i] = g_strdup(src_data->focus.pattern[i]);
        }

        dest_data->focus.use_foreground[i] = src_data->focus.use_foreground[i];
        if (src_data->focus.use_foreground[i])
          color_merge(&dest_data->focus.foreground[i], &src_data->focus.foreground[i]);

      }

#ifdef GTK1
      dest_data->focus.interior = src_data->focus.interior;
      dest_data->focus.width = src_data->focus.width;
      dest_data->focus.pad = src_data->focus.pad;

      dest_data->range.slider_width = src_data->range.slider_width;
      dest_data->range.trough_border = src_data->range.trough_border;
      dest_data->range.stepper_size = src_data->range.stepper_size;
      dest_data->range.stepper_spacing = src_data->range.stepper_spacing;

      dest_data->scale.slider_length = src_data->scale.slider_length;

      dest_data->scrollbar.min_slider_length = src_data->scrollbar.min_slider_length;
#endif

      dest_data->arrow.style = src_data->arrow.style;
      dest_data->arrow.solid = src_data->arrow.solid;
      dest_data->arrow.etched = src_data->arrow.etched;
      dest_data->arrow.xpadding = src_data->arrow.xpadding;
      dest_data->arrow.ypadding = src_data->arrow.ypadding;

      part_merge(THEME_PART(&dest_data->grip),THEME_PART(&src_data->grip));
      dest_data->grip.count = src_data->grip.count;
      dest_data->grip.spacing = src_data->grip.spacing;
      dest_data->grip.overlap = src_data->grip.overlap;

      part_merge(THEME_PART(&dest_data->check),THEME_PART(&src_data->check));
      dest_data->check.motif = src_data->check.motif;
      
      part_merge(THEME_PART(&dest_data->option),THEME_PART(&src_data->option));
      dest_data->option.motif = src_data->option.motif;

      part_merge(THEME_PART(&dest_data->trough),THEME_PART(&src_data->trough));
      dest_data->trough.show_value = src_data->trough.show_value;
      
      part_merge(&dest_data->progress,&src_data->progress);

      part_merge(THEME_PART(&dest_data->button), THEME_PART(&src_data->button));
      dest_data->button.default_triangle = src_data->button.default_triangle;
      dest_data->button.use_button_default = src_data->button.use_button_default;
      part_merge(&dest_data->button.button_default,&src_data->button.button_default);

      part_merge(THEME_PART(&dest_data->tabs), THEME_PART(&src_data->tabs));
      dest_data->tabs.use_active_tab = src_data->tabs.use_active_tab;
      part_merge(&dest_data->tabs.active_tab,&src_data->tabs.active_tab);

      dest_data->buffered_fill = src_data->buffered_fill;

      SET_THEME_DATA(dest, dest_data);
    }
}

#if GTK2
void part_finalize (smooth_part_style *part)
{
  gint i;
  
  for (i=0; i < 5; i++) {
    if (part->fill.file_name[i])
      g_free(part->fill.file_name[i]);
  }
}

void smooth_rc_style_dispose (GObject *rc_style)
{
  gint i;
  if (SMOOTH_IS_RC_STYLE (rc_style)) 
    {     
      SmoothRcStyle *data = SMOOTH_RC_DATA(rc_style);

      if (data) {  
        for (i=0; i < 5; i++) {
          if (data->fill.file_name[i])
            g_free(data->fill.file_name[i]);

          if (data->focus.pattern[i])
            g_free(data->focus.pattern[i]);
        }
        part_finalize(THEME_PART(&data->grip));
        part_finalize(THEME_PART(&data->check));
        part_finalize(THEME_PART(&data->option));
        part_finalize(THEME_PART(&data->trough));
        part_finalize(&data->progress);
        part_finalize(THEME_PART(&data->button));
        part_finalize(&data->button.button_default);
        part_finalize(THEME_PART(&data->tabs));
        part_finalize(&data->tabs.active_tab);
      }
      G_OBJECT_CLASS(parent_rc_class)->dispose(G_OBJECT(rc_style));
   }
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *
smooth_rc_style_create_style (GtkRcStyle *rc_style)
{
  void *ptr;
  ptr = GTK_STYLE (g_object_new (SMOOTH_TYPE_STYLE, NULL));
  return (GtkStyle *)ptr;
}

static void smooth_rc_style_class_init (SmoothRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (klass);

  parent_rc_class = g_type_class_peek_parent (klass);

  G_OBJECT_CLASS(klass)->dispose = smooth_rc_style_dispose;

  rc_style_class->parse        = smooth_rc_style_parse;
  rc_style_class->merge        = smooth_rc_style_merge;
  rc_style_class->create_style = smooth_rc_style_create_style;
}

void smooth_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (SmoothRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) smooth_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (SmoothRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) smooth_rc_style_init,
  };
  
  smooth_type_rc_style = g_type_module_register_type (module,
							      GTK_TYPE_RC_STYLE,
							      "SmoothRcStyle",
							      &object_info, 0);
}
#endif
