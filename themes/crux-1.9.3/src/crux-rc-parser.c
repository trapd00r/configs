#include "crux-rc-parser.h"
#include "crux-common.h"
#include "crux-gradient.h"
#include "crux-pixmaps.h"

#include "crux-rc-style.h"

#include <stdio.h>

struct symbol_struct {
    gchar *name;
    guint token;
};

enum {
    TOKEN_THICKNESS = GTK_RC_TOKEN_LAST + 1,
    TOKEN_FOCUS_THICKNESS,
    TOKEN_DEFAULT_THICKNESS,
    TOKEN_FOCUS_COLOR,
    TOKEN_INSENSITIVE_COLORS,
    TOKEN_NONE,
    TOKEN_VERTICAL,
    TOKEN_HORIZONTAL,
    TOKEN_GRADIENT,
    TOKEN_SHADOW,
    TOKEN_INVERSE_SHADOW,
    TOKEN_OUTLINE_SHADOW,
    TOKEN_YES,
    TOKEN_NO,
    TOKEN_STOCK,
    TOKEN_BORDER,
    TOKEN_RECOLOR,
    TOKEN_PALETTE,
    TOKEN_IMAGE,
    TOKEN_FG,
    TOKEN_BG,
    TOKEN_BASE,
    TOKEN_TEXT,
};

static struct symbol_struct theme_symbols[] = {
  { "thickness", TOKEN_THICKNESS },
  { "focus_thickness", TOKEN_FOCUS_THICKNESS },			
  { "default_thickness", TOKEN_DEFAULT_THICKNESS },		
  { "focus_color", TOKEN_FOCUS_COLOR },				
  { "insensitive_colors", TOKEN_INSENSITIVE_COLORS },		
  { "none", TOKEN_NONE },					
  { "vertical", TOKEN_VERTICAL },				
  { "horizontal", TOKEN_HORIZONTAL },				
  { "gradient", TOKEN_GRADIENT },				
  { "shadow", TOKEN_SHADOW },					
  { "inverse_shadow", TOKEN_INVERSE_SHADOW },			
  { "outline_shadow", TOKEN_OUTLINE_SHADOW },			
  { "yes", TOKEN_YES },						
  { "no", TOKEN_NO },						
  { "stock", TOKEN_STOCK },					
  { "border", TOKEN_BORDER },					
  { "recolor", TOKEN_RECOLOR },					
  { "palette", TOKEN_PALETTE },					
  { "image", TOKEN_IMAGE },					
  { "fg", TOKEN_FG },						
  { "bg", TOKEN_BG },						
  { "base", TOKEN_BASE },					
  { "text", TOKEN_TEXT },
  { 0, G_TOKEN_NONE }
};

#define STOCK_SYMBOLS 									\
    { "CHECK", EAZEL_ENGINE_CHECK },							\
    { "CHECK_FOCUS", EAZEL_ENGINE_CHECK_FOCUS },					\
    { "CHECK_HI", EAZEL_ENGINE_CHECK_HI },						\
    { "CHECK_HI_FOCUS", EAZEL_ENGINE_CHECK_HI_FOCUS },					\
    { "CHECK_PRESSED", EAZEL_ENGINE_CHECK_PRESSED },					\
    { "CHECK_PRESSED_FOCUS", EAZEL_ENGINE_CHECK_PRESSED_FOCUS },			\
    { "CHECK_DISABLED", EAZEL_ENGINE_CHECK_DISABLED },					\
    { "CHECK_ACTIVE", EAZEL_ENGINE_CHECK_ACTIVE },					\
    { "CHECK_ACTIVE_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_FOCUS },				\
    { "CHECK_ACTIVE_HI", EAZEL_ENGINE_CHECK_ACTIVE_HI },				\
    { "CHECK_ACTIVE_HI_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_HI_FOCUS },			\
    { "CHECK_ACTIVE_PRESSED", EAZEL_ENGINE_CHECK_ACTIVE_PRESSED },			\
    { "CHECK_ACTIVE_PRESSED_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_PRESSED_FOCUS },		\
    { "CHECK_ACTIVE_DISABLED", EAZEL_ENGINE_CHECK_ACTIVE_DISABLED },			\
    { "OPTION", EAZEL_ENGINE_OPTION },							\
    { "OPTION_FOCUS", EAZEL_ENGINE_OPTION_FOCUS },					\
    { "OPTION_HI", EAZEL_ENGINE_OPTION_HI },						\
    { "OPTION_HI_FOCUS", EAZEL_ENGINE_OPTION_HI_FOCUS },				\
    { "OPTION_PRESSED", EAZEL_ENGINE_OPTION_PRESSED },					\
    { "OPTION_PRESSED_FOCUS", EAZEL_ENGINE_OPTION_PRESSED_FOCUS },			\
    { "OPTION_DISABLED", EAZEL_ENGINE_OPTION_DISABLED },				\
    { "OPTION_ACTIVE", EAZEL_ENGINE_OPTION_ACTIVE },					\
    { "OPTION_ACTIVE_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_FOCUS },			\
    { "OPTION_ACTIVE_HI", EAZEL_ENGINE_OPTION_ACTIVE_HI },				\
    { "OPTION_ACTIVE_HI_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_HI_FOCUS },			\
    { "OPTION_ACTIVE_PRESSED", EAZEL_ENGINE_OPTION_ACTIVE_PRESSED },			\
    { "OPTION_ACTIVE_PRESSED_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_PRESSED_FOCUS },	\
    { "OPTION_ACTIVE_DISABLED", EAZEL_ENGINE_OPTION_ACTIVE_DISABLED },			\
    { "H_TROUGH", EAZEL_ENGINE_H_TROUGH },						\
    { "V_TROUGH", EAZEL_ENGINE_V_TROUGH },						\
    { "ARROW_UP", EAZEL_ENGINE_ARROW_UP },						\
    { "ARROW_UP_HI", EAZEL_ENGINE_ARROW_UP_HI },					\
    { "ARROW_UP_ACTIVE", EAZEL_ENGINE_ARROW_UP_ACTIVE },				\
    { "ARROW_DOWN", EAZEL_ENGINE_ARROW_DOWN },						\
    { "ARROW_DOWN_HI", EAZEL_ENGINE_ARROW_DOWN_HI },					\
    { "ARROW_DOWN_ACTIVE", EAZEL_ENGINE_ARROW_DOWN_ACTIVE },				\
    { "ARROW_RIGHT", EAZEL_ENGINE_ARROW_RIGHT },					\
    { "ARROW_RIGHT_HI", EAZEL_ENGINE_ARROW_RIGHT_HI },					\
    { "ARROW_RIGHT_ACTIVE", EAZEL_ENGINE_ARROW_RIGHT_ACTIVE },				\
    { "ARROW_LEFT", EAZEL_ENGINE_ARROW_LEFT },						\
    { "ARROW_LEFT_HI", EAZEL_ENGINE_ARROW_LEFT_HI },					\
    { "ARROW_LEFT_ACTIVE", EAZEL_ENGINE_ARROW_LEFT_ACTIVE },				\
    { "H_SCROLLBAR", EAZEL_ENGINE_H_SCROLLBAR },					\
    { "H_SCROLLBAR_HI", EAZEL_ENGINE_H_SCROLLBAR_HI },					\
    { "H_SCROLLBAR_INACTIVE", EAZEL_ENGINE_H_SCROLLBAR_INACTIVE },			\
    { "H_SCROLLBAR_THUMB", EAZEL_ENGINE_H_SCROLLBAR_THUMB },				\
    { "H_SCROLLBAR_THUMB_HI", EAZEL_ENGINE_H_SCROLLBAR_THUMB_HI },			\
    { "H_SCROLLBAR_THUMB_INACTIVE", EAZEL_ENGINE_H_SCROLLBAR_THUMB_INACTIVE },		\
    { "V_SCROLLBAR", EAZEL_ENGINE_V_SCROLLBAR },					\
    { "V_SCROLLBAR_HI", EAZEL_ENGINE_V_SCROLLBAR_HI },					\
    { "V_SCROLLBAR_INACTIVE", EAZEL_ENGINE_V_SCROLLBAR_INACTIVE },			\
    { "V_SCROLLBAR_THUMB", EAZEL_ENGINE_V_SCROLLBAR_THUMB },				\
    { "V_SCROLLBAR_THUMB_HI", EAZEL_ENGINE_V_SCROLLBAR_THUMB_HI },			\
    { "V_SCROLLBAR_THUMB_INACTIVE", EAZEL_ENGINE_V_SCROLLBAR_THUMB_INACTIVE },		\
    { "PROGRESS_BAR", EAZEL_ENGINE_PROGRESS_BAR },					\
    { "PROGRESS_BAR_LEFT", EAZEL_ENGINE_PROGRESS_BAR_LEFT },				\
    { "PROGRESS_BAR_RIGHT", EAZEL_ENGINE_PROGRESS_BAR_RIGHT },				\
    { "PROGRESS_BAR_INACTIVE", EAZEL_ENGINE_PROGRESS_BAR_INACTIVE },			\
    { "PROGRESS_TROUGH", EAZEL_ENGINE_PROGRESS_TROUGH },				\
    { "H_SLIDER_THUMB", EAZEL_ENGINE_H_SLIDER_THUMB },					\
    { "H_SLIDER_THUMB_INACTIVE", EAZEL_ENGINE_H_SLIDER_THUMB_INACTIVE },		\
    { "H_SLIDER_TROUGH", EAZEL_ENGINE_H_SLIDER_TROUGH },				\
    { "H_SLIDER_TROUGH_ACTIVE", EAZEL_ENGINE_H_SLIDER_TROUGH_ACTIVE },			\
    { "V_SLIDER_THUMB", EAZEL_ENGINE_V_SLIDER_THUMB },					\
    { "V_SLIDER_THUMB_INACTIVE", EAZEL_ENGINE_V_SLIDER_THUMB_INACTIVE },		\
    { "V_SLIDER_TROUGH", EAZEL_ENGINE_V_SLIDER_TROUGH },				\
    { "V_SLIDER_TROUGH_ACTIVE", EAZEL_ENGINE_V_SLIDER_TROUGH_ACTIVE },			\
    { "TAB_TOP", EAZEL_ENGINE_TAB_TOP },						\
    { "TAB_TOP_LEFT", EAZEL_ENGINE_TAB_TOP_LEFT },					\
    { "TAB_TOP_ACTIVE", EAZEL_ENGINE_TAB_TOP_ACTIVE },					\
    { "TAB_BOTTOM", EAZEL_ENGINE_TAB_BOTTOM },						\
    { "TAB_BOTTOM_LEFT", EAZEL_ENGINE_TAB_BOTTOM_LEFT },				\
    { "TAB_BOTTOM_ACTIVE", EAZEL_ENGINE_TAB_BOTTOM_ACTIVE },				\
    { "SPIN_ARROW_UP", EAZEL_ENGINE_SPIN_ARROW_UP },					\
    { "SPIN_ARROW_DOWN", EAZEL_ENGINE_SPIN_ARROW_DOWN },				\
    { 0, 0 }

//static struct symbol_struct theme_symbols[] = { THEME_SYMBOLS };

static guint n_theme_symbols = (sizeof(theme_symbols) / sizeof(theme_symbols[0])) - 1;

static struct symbol_struct stock_symbols[] = { STOCK_SYMBOLS };

static guint n_stock_symbols = (sizeof(stock_symbols) / sizeof(stock_symbols[0])) - 1;

static eazel_theme_data *default_theme_data;
static eazel_engine_stock_table *default_stock_data;

static eazel_theme_data original_theme_data = DEFAULT_THEME_DATA;

void crux_rc_parser_init_gradients (void)
{

    gdk_rgb_init ();

    /* Initialize default theme data */
    original_theme_data.gradients[0] = eazel_engine_make_two_point_gradient (GRADIENT_VERTICAL, 0xeeeeee, 0xaaaaaa);
    original_theme_data.gradients[1] = eazel_engine_make_two_point_gradient (GRADIENT_VERTICAL, 0xcccccc, 0x888888);
    original_theme_data.gradients[2] = eazel_engine_make_two_point_gradient (GRADIENT_VERTICAL, 0xffffff, 0xbbbbbb);
    original_theme_data.gradients[3] = eazel_engine_make_two_point_gradient (GRADIENT_VERTICAL, 0xcccccc, 0x888888);
}

/* utilities */

static char *
read_line_from_file (char *filename)
{
    gboolean free_filename = FALSE;
    FILE *fh;
    char *ret = 0;

    if (!g_path_is_absolute (filename))
    {
	const char *home = g_get_home_dir ();
	char buf[PATH_MAX];
	g_snprintf (buf, PATH_MAX, "%s/%s", home, filename);
	filename = g_strdup (buf);
	free_filename = TRUE;
    }

    fh = fopen (filename, "r");
    if (fh != 0)
    {
	char buf[256];
	if (fgets (buf, sizeof (buf), fh) != 0)
	{
	    int len = strlen (buf);
	    if (len > 0)
		buf[len-1] = 0;
	    ret = g_strdup (buf);
	}
	fclose (fh);
    }

    if (free_filename)
	g_free (filename);

    return ret;
}

static int
stock_index (const char *symbol)
{
    int i;
    for (i = 0; i < n_stock_symbols; i++)
    {
	if (strcmp (symbol, stock_symbols[i].name) == 0)
	    return i;
    }
    g_error ("Unknown stock symbol: `%s'\n", symbol);
    exit (1);
}

void
theme_data_ref (eazel_theme_data *theme_data)
{
    theme_data->refcount++;
}

void
theme_data_unref (eazel_theme_data *theme_data)
{
    theme_data->refcount--;
    if (theme_data->refcount == 0)
    {
	int i;
	for (i = 0; i < 5; i++)
	{
	    if (theme_data->gradients[i] != NULL)
		eazel_engine_gradient_unref (theme_data->gradients[i]);
	}
	eazel_engine_stock_table_unref (theme_data->stock);
	g_free (theme_data);
    }
}

static guint
parse_int_assign (GScanner *scanner, guint *value)
{
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_INT)
	return G_TOKEN_INT;

    *value = scanner->value.v_int;
    return G_TOKEN_NONE;
}

static guint
parse_int_array_assign (GScanner *scanner, guint *value, int size)
{
    guint token;
    int i;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_LEFT_CURLY)
	return G_TOKEN_LEFT_CURLY;

    for (i = 0; i < size; i++)
    {
	if (i != 0)
	{
	    token = g_scanner_get_next_token (scanner);
	    if (token != G_TOKEN_COMMA)
		return G_TOKEN_COMMA;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_INT)
	    return G_TOKEN_INT;

	value[i] = scanner->value.v_int;
    }

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_RIGHT_CURLY)
	return G_TOKEN_RIGHT_CURLY;

    return G_TOKEN_NONE;
}

static guint
parse_boolean_assign (GScanner *scanner, gboolean *value)
{
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token (scanner);
    if (token == TOKEN_YES)
    {
	*value = TRUE;
	return G_TOKEN_NONE;
    }
    else
    {
	*value = FALSE;
	return G_TOKEN_NONE;
    }
}

static guint
parse_string_assign (GScanner *scanner, char **value)
{
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_STRING)
	return G_TOKEN_STRING;

    *value = g_strdup (scanner->value.v_string);
    return G_TOKEN_NONE;
}

static guint
parse_color (eazel_theme_data *theme_data, GScanner *scanner, GdkColor *color)
{
    guint token;

    token = g_scanner_peek_next_token (scanner);
    if (theme_data != 0 && token == '<')
    {
	(void) g_scanner_get_next_token (scanner);

	token = g_scanner_get_next_token (scanner);

	if (token == G_TOKEN_INT)
	{
	    int index = scanner->value.v_int;

	    if (index < 0 || index >= EAZEL_ENGINE_PALETTE_SIZE)
	    {
		g_error ("Palette only has %d entries\n",
			 EAZEL_ENGINE_PALETTE_SIZE);
	    }
		    
	    index = CLAMP (index, 0, EAZEL_ENGINE_PALETTE_SIZE - 1);

	    /* XXX just taking the first color of the gradient.. */
	    if (theme_data->palette[index] != 0)
		*color = theme_data->palette[index]->from;
	    else
		g_error ("No color in palette with index %d", index);

	    token = g_scanner_peek_next_token (scanner);
	    if (token == G_TOKEN_COMMA)
	    {
		float tem;

		(void) g_scanner_get_next_token (scanner);

		token = g_scanner_get_next_token (scanner);
		if (token != G_TOKEN_FLOAT)
		    return G_TOKEN_FLOAT;

		tem = color->red;
		tem *= scanner->value.v_float;
		color->red = tem;

		tem = color->green;
		tem *= scanner->value.v_float;
		color->green = tem;

		tem = color->blue;
		tem *= scanner->value.v_float;
		color->blue = tem;
	    }
	}
	else if (token == G_TOKEN_STRING)
	{
	    char *string;
	    gboolean ret = FALSE;

	    string = read_line_from_file (scanner->value.v_string);
	    if (string != 0)
		ret = gdk_color_parse (string, color);

	    if (!ret)
	    {
		/* Default to the Eazel Teal color */
		color->red = 0x5050;
		color->green = 0x8080;
		color->blue = 0x8383;
	    }

	    g_free (string);
	}
	else
	    return G_TOKEN_INT;

	token = g_scanner_get_next_token (scanner);
	if (token != '>')
	  return '>';

	return G_TOKEN_NONE;
    }
    else
	return gtk_rc_parse_color (scanner, color);
}

static guint
parse_n_colors (eazel_theme_data *theme_data,
		GScanner *scanner, GdkColor *value, int n)
{
    guint token;
    int i;
    for (i = 0; i < n; i++)
    {
	if (i != 0)
	{
	    token = g_scanner_get_next_token (scanner);
	    if (token != G_TOKEN_COMMA)
		return G_TOKEN_COMMA;
	}

	token = parse_color (theme_data, scanner, value + i);
	if (token != G_TOKEN_NONE)
	    return token;
    }
    return G_TOKEN_NONE;
}

static guint
parse_n_color_assign (eazel_theme_data *theme_data,
		      GScanner *scanner, GdkColor *value, int n)
{
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    return parse_n_colors (theme_data, scanner, value, n);
}

static guint
parse_color_assign (eazel_theme_data *theme_data,
		    GScanner *scanner, GdkColor *color)
{
    return parse_n_color_assign (theme_data, scanner, color, 1);
}

static guint
parse_standard_color_assign (eazel_theme_data *theme_data, GScanner *scanner,
			     GtkRcStyle *rc_style, GdkColor *colors, int flag)
{
    GtkStateType state;
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = gtk_rc_parse_state (scanner, &state);
    if (token != G_TOKEN_NONE)
	return token;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = parse_color (theme_data, scanner, colors + state);
    if (token != G_TOKEN_NONE)
	return token;

    rc_style->color_flags[state] |= flag;
    return G_TOKEN_NONE;
}

static guint
parse_gradient (eazel_theme_data *theme_data, GScanner *scanner,
		eazel_engine_gradient **gradient)
{
    eazel_engine_gradient_direction direction;
    GdkColor from;
    GSList *colors = NULL;

    guint token;

    token = g_scanner_get_next_token (scanner);

    if (token == '<')
    {
	int index;

	/* a palette reference */

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_INT) {
	    return G_TOKEN_INT;
	}

	index = scanner->value.v_int;
	if (index < 0 || index >= EAZEL_ENGINE_PALETTE_SIZE)
	{
	    g_error ("Palette only has %d entries\n",
		     EAZEL_ENGINE_PALETTE_SIZE);
	}
		    
	if (theme_data->palette[index] != 0)
	    *gradient = eazel_engine_gradient_ref (theme_data->palette[index]);
	else
	    g_error ("No color in palette with index %d", index);

	token = g_scanner_get_next_token (scanner);
	if (token != '>')
	  return '>';

	return G_TOKEN_NONE;
    }
    else if (token != G_TOKEN_LEFT_CURLY)
	return G_TOKEN_LEFT_CURLY;

    token = g_scanner_peek_next_token (scanner);
    if (token == TOKEN_HORIZONTAL)
    {
	direction = GRADIENT_HORIZONTAL;
	(void) g_scanner_get_next_token (scanner);

	token = g_scanner_get_next_token (scanner);
	if (token != ':')
	  return ':';
    }
    else if (token == TOKEN_VERTICAL)
    {
	direction = GRADIENT_VERTICAL;
	(void) g_scanner_get_next_token (scanner);

	token = g_scanner_get_next_token (scanner);
	if (token != ':')
	  return ':';
    }
    else if (token == G_TOKEN_RIGHT_CURLY)
	direction = GRADIENT_NONE;
    else
	direction = GRADIENT_VERTICAL;

    if (direction != GRADIENT_NONE)
    {
	token = parse_color (theme_data, scanner, &from);
	if (token != G_TOKEN_NONE)
	    return token;

	while (1)
	{
	    float weight = 1.0;
	    GdkColor color;
	    eazel_engine_gradient_component *component;

	    token = g_scanner_peek_next_token (scanner);
	    if (token == G_TOKEN_COMMA)
		(void) g_scanner_get_next_token (scanner);
	    else if (token == G_TOKEN_LEFT_BRACE)
	    {
		(void) g_scanner_get_next_token (scanner);

		token = g_scanner_get_next_token (scanner);
		if (token == G_TOKEN_FLOAT)
		    weight = scanner->value.v_float;
		else if (token == G_TOKEN_INT)
		    weight = scanner->value.v_int;
		else
		    return G_TOKEN_FLOAT;

		token = g_scanner_get_next_token (scanner);
		if (token != G_TOKEN_RIGHT_BRACE)
		    return G_TOKEN_RIGHT_BRACE;
	    }
	    else
		break;

	    token = parse_color (theme_data, scanner, &color);
	    if (token != G_TOKEN_NONE)
		return token;

	    component = g_new (eazel_engine_gradient_component, 1);
	    component->color = color;
	    component->weight = weight;
	    colors = g_slist_prepend (colors, component);
	}

	colors = g_slist_reverse (colors);
    }

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_RIGHT_CURLY)
	return G_TOKEN_RIGHT_CURLY;

    if (*gradient != NULL)
	eazel_engine_gradient_unref (*gradient);
    *gradient = eazel_engine_gradient_new (direction, &from, colors);

    return G_TOKEN_NONE;
}

static guint
parse_gradient_assign (eazel_theme_data *theme_data, GScanner *scanner,
		       eazel_engine_gradient **gradients)
{
    guint token, state;

    (void) g_scanner_get_next_token (scanner);

    token = gtk_rc_parse_state (scanner, &state);
    if (token != G_TOKEN_NONE)
	return token;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = parse_gradient (theme_data, scanner, &(gradients[state]));
    if (token != G_TOKEN_NONE)
      return token;

    return G_TOKEN_NONE;
}

static guint
parse_1_gradient_assign (eazel_theme_data *theme_data, GScanner *scanner,
			 eazel_engine_gradient **gradient)
{
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = parse_gradient (theme_data, scanner, gradient);
    if (token != G_TOKEN_NONE)
	return token;

    return G_TOKEN_NONE;
}

static guint
parse_stock_stmt (GScanner *scanner, eazel_theme_data *theme_data,
		  eazel_engine_stock_table **table_ptr)
{
    eazel_engine_stock_table *table = g_new0 (eazel_engine_stock_table, 1);
    guint token;

    table->ref_count = 1;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_LEFT_CURLY)
	return G_TOKEN_LEFT_CURLY;

    token = g_scanner_peek_next_token (scanner);
    while (token != G_TOKEN_RIGHT_CURLY)
    {
	switch (token)
	{
	    guint stock;
	    eazel_engine_image *image;

	case G_TOKEN_STRING:
	    (void) g_scanner_get_next_token (scanner);

	    stock = stock_index (scanner->value.v_string);
	    image = &table->images[stock];

	    token = g_scanner_get_next_token (scanner);
	    if (token != G_TOKEN_LEFT_CURLY)
		return G_TOKEN_LEFT_CURLY;

	    token = g_scanner_peek_next_token (scanner);
	    while (token != G_TOKEN_RIGHT_CURLY)
	    {
		switch (token)
		{
		case TOKEN_IMAGE:
		    token = parse_string_assign (scanner, &image->filename);
		    break;

		case TOKEN_BORDER:
		    token = parse_int_array_assign (scanner, image->border, 4);
		    break;

		case TOKEN_RECOLOR:
		    token = parse_1_gradient_assign (theme_data, scanner,
						     &image->recolor);
		    break;

		default:
		    g_scanner_get_next_token (scanner);
		    token = G_TOKEN_RIGHT_CURLY;
		    break;
		}

		if (token != G_TOKEN_NONE)
		    goto out;

		token = g_scanner_peek_next_token (scanner);
	    }

	    token = g_scanner_get_next_token (scanner);
	    if (token == G_TOKEN_RIGHT_CURLY)
		token = G_TOKEN_NONE;
	    else
		token = G_TOKEN_RIGHT_CURLY;
	    break;

	default:
	    g_scanner_get_next_token (scanner);
	    token = G_TOKEN_RIGHT_CURLY;
	    break;
	}
    
    out:
	if (token != G_TOKEN_NONE)
	{
	    g_free (table);
	    return token;
	}

    	token = g_scanner_peek_next_token (scanner);
    }

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_RIGHT_CURLY)
	return G_TOKEN_RIGHT_CURLY;

    *table_ptr = table;
    return G_TOKEN_NONE;
}

static guint
parse_palette_assign (GScanner *scanner, eazel_theme_data *theme_data)
{
    int index;
    guint token;

    (void) g_scanner_get_next_token (scanner);

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_LEFT_BRACE)
	return G_TOKEN_LEFT_BRACE;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_INT)
	return G_TOKEN_INT;

    index = scanner->value.v_int;
    if (index < 0 || index >= EAZEL_ENGINE_PALETTE_SIZE)
    {
	g_error ("Only %d colors are allowed in the palette",
		 EAZEL_ENGINE_PALETTE_SIZE);
    }

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_RIGHT_BRACE)
	return G_TOKEN_RIGHT_BRACE;

    token = g_scanner_get_next_token (scanner);
    if (token != G_TOKEN_EQUAL_SIGN)
	return G_TOKEN_EQUAL_SIGN;

    token = parse_gradient (theme_data, scanner, &theme_data->palette[index]);
    if (token != G_TOKEN_NONE)
	return token;

    return G_TOKEN_NONE;
}


guint
crux_parse_rc_style  (GtkRcStyle   *rc_style,
                       GtkSettings  *settings,
                       GScanner     *scanner)
{
    static GQuark scope_id = 0;
    guint old_scope;
    guint token;
    eazel_theme_data *theme_data;
    gint i;
    gboolean had_stock_table = FALSE;

    /* Set up a new scope in this scanner. */

    if (!scope_id)
	scope_id = g_quark_from_string ("crux_theme_engine");

    /* If we bail out due to errors, we *don't* reset the scope, so the
       error messaging code can make sense of our tokens. */
    old_scope = g_scanner_set_scope (scanner, scope_id);

    /* Now check if we already added our symbols to this scope
      (in some previous call to theme_parse_rc_style for the
      same scanner. */

    if (!g_scanner_lookup_symbol (scanner, theme_symbols[0].name))
    {
	g_scanner_freeze_symbol_table(scanner);
	for (i = 0; i < n_theme_symbols; i++)
	{
	    g_scanner_scope_add_symbol (scanner, scope_id,
					theme_symbols[i].name,
					GINT_TO_POINTER(theme_symbols[i].token));
	}
	g_scanner_thaw_symbol_table (scanner);
    }

    /* We're ready to go, now parse the top level */

    theme_data = g_new (eazel_theme_data, 1);
    if (default_theme_data != 0) {
	memcpy (theme_data, default_theme_data, sizeof (eazel_theme_data));
    } else {
	memcpy (theme_data, &original_theme_data, sizeof (eazel_theme_data));
    }

    /* ref all gradients */
    for (i = 0; i < 5; i++)
    {
	if (theme_data->gradients[i] != NULL)
	    theme_data->gradients[i] = (eazel_engine_gradient_ref
					(theme_data->gradients[i]));
    }
    for (i = 0; i < EAZEL_ENGINE_PALETTE_SIZE; i++)
    {
	if (theme_data->palette[i] != NULL)
	    theme_data->palette[i] = (eazel_engine_gradient_ref
				      (theme_data->palette[i]));
    }

    theme_data->refcount = 1;

    if (default_stock_data != 0)
	theme_data->stock = eazel_engine_stock_table_ref (default_stock_data);
    else
	theme_data->stock = 0;

    token = g_scanner_peek_next_token(scanner);
    while (token != G_TOKEN_RIGHT_CURLY)
    {
	switch (token)
	{
	    gboolean tem;
	    eazel_engine_stock_table *stock_tem;

	case TOKEN_THICKNESS:
	    token = parse_int_assign (scanner, &theme_data->thickness);
	    break;

	case TOKEN_FOCUS_THICKNESS:
	    token = parse_int_assign (scanner, &theme_data->focus_thickness);
	    break;

	case TOKEN_DEFAULT_THICKNESS:
	    token = parse_int_assign (scanner, &theme_data->default_thickness);
	    break;

	case TOKEN_FOCUS_COLOR:
	    token = parse_color_assign (theme_data, scanner,
					&theme_data->focus_color);
	    break;

	case TOKEN_INSENSITIVE_COLORS:
	    token = parse_n_color_assign (theme_data, scanner,
					  theme_data->insensitive_colors, 2);
	    break;

	case TOKEN_GRADIENT:
	    token = parse_gradient_assign (theme_data, scanner,
					   theme_data->gradients);
	    break;

	case TOKEN_SHADOW:
	    token = parse_boolean_assign (scanner, &tem);
	    if (token == G_TOKEN_NONE)
		theme_data->no_shadow = !tem;
	    break;

	case TOKEN_INVERSE_SHADOW:
	    token = parse_boolean_assign (scanner, &tem);
	    if (token == G_TOKEN_NONE)
		theme_data->inverse_shadow = tem;
	    break;

	case TOKEN_OUTLINE_SHADOW:
	    token = parse_boolean_assign (scanner, &tem);
	    if (token == G_TOKEN_NONE)
		theme_data->outline_shadow = !tem;
	    break;

	case TOKEN_PALETTE:
	    token = parse_palette_assign (scanner, theme_data);
	    break;

	case TOKEN_STOCK:
	    token = parse_stock_stmt (scanner, theme_data, &stock_tem);
	    if (token == G_TOKEN_NONE)
	    {
		if (theme_data->stock != 0)
		    eazel_engine_stock_table_unref (theme_data->stock);

		theme_data->stock = stock_tem;
		had_stock_table = TRUE;
	    }
	    break;

	case TOKEN_FG:
	    token = parse_standard_color_assign (theme_data, scanner, rc_style,
						 rc_style->fg, GTK_RC_FG);
	    break;

	case TOKEN_BG:
	    token = parse_standard_color_assign (theme_data, scanner, rc_style,
						 rc_style->bg, GTK_RC_BG);
	    break;

	case TOKEN_BASE:
	    token = parse_standard_color_assign (theme_data, scanner, rc_style,
						 rc_style->base, GTK_RC_BASE);
	    break;

	case TOKEN_TEXT:
	    token = parse_standard_color_assign (theme_data, scanner, rc_style,
						 rc_style->text, GTK_RC_TEXT);
	    break;

	default:
	    g_scanner_get_next_token (scanner);
	    token = G_TOKEN_RIGHT_CURLY;
	    break;
	}

	if (token != G_TOKEN_NONE)
	{
	    g_free (theme_data);
	    return token;
	}

	token = g_scanner_peek_next_token (scanner);
    }

    g_scanner_get_next_token(scanner);

    if (theme_data->stock == 0)
	g_error ("First `engine' section must include a `stock' section.");

    if (had_stock_table)
    {
	/* Defining a stock table makes it the default for any
	   engine sections in the future that don't have one.. */

	if (default_stock_data != 0)
	    eazel_engine_stock_table_unref (default_stock_data);

	default_stock_data = eazel_engine_stock_table_ref (theme_data->stock);

	/* Engine data section with stock table (usually the first in
	   in the file) sets some other default values. A hack, but
	   a very useful one! */

	if (default_theme_data != 0)
	    theme_data_unref (default_theme_data);

	theme_data_ref (theme_data);
	default_theme_data = theme_data;
    }

    CRUX_RC_STYLE(rc_style)->theme_data = theme_data;
    g_scanner_set_scope (scanner, old_scope);

    return G_TOKEN_NONE;
}
   
