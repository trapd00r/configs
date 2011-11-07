/*  MagicChicken: src/rc-style.c
 *
 *  Copyright 2001 (c) James M. Cape <jcape@ignore.your.tv>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "rc-style.h"
#include "style.h"
#include "checkradio-images.h"


#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gdk-pixdata.h>

#include <string.h>


#define GTK_STATE_LAST 5
#define MAX_SHADOW_WIDTH 3
#define CLAMP_PERCENT_FLOAT(num) \
	CLAMP(num, 0.01, 1.0)


enum
{
	MGICCHIKN_TOKEN_INVALID = GTK_RC_TOKEN_LAST,

	MGICCHIKN_TOKEN_STOCK_IMAGE_TRANSPARENCY,
	MGICCHIKN_TOKEN_STOCK_IMAGE_SATURATION,
	MGICCHIKN_TOKEN_STOCK_IMAGE_BRIGHTNESS,
	MGICCHIKN_TOKEN_FONT_SHADOW,
	MGICCHIKN_TOKEN_SHADOW,
	MGICCHIKN_TOKEN_SHADOW_WIDTH,
	MGICCHIKN_TOKEN_GRIPPY_STYLE,
	MGICCHIKN_TOKEN_FONT_UNDERLINE,
	MGICCHIKN_TOKEN_CHECK_IMAGE,
	MGICCHIKN_TOKEN_RADIO_IMAGE,

	MGICCHIKN_TOKEN_NORMAL,
	MGICCHIKN_TOKEN_PRELIGHT,
	MGICCHIKN_TOKEN_ACTIVE,
	MGICCHIKN_TOKEN_SELECTED,
	MGICCHIKN_TOKEN_INSENSITIVE,

	MGICCHIKN_TOKEN_ALL,
	MGICCHIKN_TOKEN_NONE,
	MGICCHIKN_TOKEN_IN,
	MGICCHIKN_TOKEN_OUT,
	MGICCHIKN_TOKEN_ETCHED_IN,
	MGICCHIKN_TOKEN_ETCHED_OUT,
	MGICCHIKN_TOKEN_FLAT,
	MGICCHIKN_TOKEN_SHARP_IN,
	MGICCHIKN_TOKEN_SHARP_OUT,
	MGICCHIKN_TOKEN_SHARP_ENTRY_IN,
	MGICCHIKN_TOKEN_ROUNDED_IN,
	MGICCHIKN_TOKEN_ROUNDED_OUT,
	MGICCHIKN_TOKEN_MOTIF_IN,
	MGICCHIKN_TOKEN_MOTIF_OUT,

	MGICCHIKN_TOKEN_DOTS_IN,
	MGICCHIKN_TOKEN_DOTS_OUT,
	MGICCHIKN_TOKEN_LINES_IN,
	MGICCHIKN_TOKEN_LINES_OUT,

	MGICCHIKN_TOKEN_SINGLE,
	MGICCHIKN_TOKEN_DOUBLE,

	MGICCHIKN_TOKEN_TRUE,
	MGICCHIKN_TOKEN_FALSE,

	MGICCHIKN_TOKEN_LAST
};

typedef struct
{
	const gchar *name;
	guint token;
}
MgicChiknSymbol;


/* *INDENT-OFF* */
static const MgicChiknSymbol symbols[] = {
	/* Keys -- settings names */
	{ "stock-image-transparency",	MGICCHIKN_TOKEN_STOCK_IMAGE_TRANSPARENCY },
	{ "stock-image-saturation",		MGICCHIKN_TOKEN_STOCK_IMAGE_SATURATION },
	{ "stock-image-brightness",		MGICCHIKN_TOKEN_STOCK_IMAGE_BRIGHTNESS },
	{ "font-shadow",				MGICCHIKN_TOKEN_FONT_SHADOW },
	{ "shadow-width",				MGICCHIKN_TOKEN_SHADOW_WIDTH },
	{ "grippy-style",				MGICCHIKN_TOKEN_GRIPPY_STYLE },
	{ "font-underline",				MGICCHIKN_TOKEN_FONT_UNDERLINE },
	{ "check-image",				MGICCHIKN_TOKEN_CHECK_IMAGE },
	{ "radio-image",				MGICCHIKN_TOKEN_RADIO_IMAGE },
	{ "shadow",						MGICCHIKN_TOKEN_SHADOW },

	/* Examples:
	   # Draws NORMAL & PRELIGHT widgets using a picture background without a gtk-style shadow
		bg_style[NORMAL, PRELIGHT][OUT] = { FALSE, PICTURE }
	
	   # defaults to drawing gtk-style shadows in all states & shadow styles
		bg_style[ALL][ALL] = { TRUE }

	   # draws gtk-style outlines around all insensitive widgets
		bg_style[INSENSITIVE][ALL] = { TRUE, GRADIENT }

	   # Overrides insensitive widgets of all shadows types to use the "FLAT" shadow
		shadow[INSENSITIVE][ALL] = FLAT 

	   # Sets INSENSITIVE widgets with "IN" or "OUT" shadows to use single-pixel-wide shadows
		shadow_width[INSENSITIVE][IN, OUT] = 1

	   Note that this [<state>][<shadow_type>] parse stuff only applies
	   to bg_style, shadow, shadow_width, picture, & gradient.
	   font_shadow & stock_image_{*} still use the standard 
	   <setting>[<state>] = <value> syntax -- Also, all these settings only
	   apply to the widgets that the style which contains them applies to...
	   That is, if you've got a shadow_width setting in a style that only
	   applies to GtkButton, only GtkButton will use that setting. */

    /* Values */
	{ "NORMAL",						MGICCHIKN_TOKEN_NORMAL },
	{ "PRELIGHT",					MGICCHIKN_TOKEN_PRELIGHT },
	{ "ACTIVE",						MGICCHIKN_TOKEN_ACTIVE },
	{ "SELECTED",					MGICCHIKN_TOKEN_SELECTED },
	{ "INSENSITIVE",				MGICCHIKN_TOKEN_INSENSITIVE },

	{ "ALL",						MGICCHIKN_TOKEN_ALL },
	{ "NONE",						MGICCHIKN_TOKEN_NONE },
	/* GTK+ shadows */
	{ "IN",							MGICCHIKN_TOKEN_IN },
	{ "OUT",						MGICCHIKN_TOKEN_OUT },
	{ "ETCHED_IN",					MGICCHIKN_TOKEN_ETCHED_IN },
	{ "ETCHED_OUT",					MGICCHIKN_TOKEN_ETCHED_OUT },
	/* Basic, fg-color flat */
	{ "FLAT",						MGICCHIKN_TOKEN_FLAT },
	/* Crux/BlueCurve/MacOS sharp-cornered style */
	{ "SHARP_IN",					MGICCHIKN_TOKEN_SHARP_IN },
	{ "SHARP_OUT",					MGICCHIKN_TOKEN_SHARP_OUT },
	/* MacOS/BeOS rounded-corner style */
	{ "ROUNDED_IN",					MGICCHIKN_TOKEN_ROUNDED_IN },
	{ "ROUNDED_OUT",				MGICCHIKN_TOKEN_ROUNDED_OUT },
	/* Motif */
	{ "MOTIF_IN",					MGICCHIKN_TOKEN_MOTIF_IN },
	{ "MOTIF_OUT",					MGICCHIKN_TOKEN_MOTIF_OUT },

	{ "DOTS_IN",					MGICCHIKN_TOKEN_DOTS_IN },
	{ "DOTS_OUT",					MGICCHIKN_TOKEN_DOTS_OUT },
	{ "LINES_IN",					MGICCHIKN_TOKEN_LINES_IN },
	{ "LINES_OUT",					MGICCHIKN_TOKEN_LINES_OUT },

	{ "SINGLE",						MGICCHIKN_TOKEN_SINGLE },
	{ "DOUBLE",						MGICCHIKN_TOKEN_DOUBLE },

	{ "true",						MGICCHIKN_TOKEN_TRUE },
	{ "false",						MGICCHIKN_TOKEN_FALSE },
	{ "on",							MGICCHIKN_TOKEN_TRUE },
	{ "off",						MGICCHIKN_TOKEN_FALSE },
	{ "yes",						MGICCHIKN_TOKEN_TRUE },
	{ "no",							MGICCHIKN_TOKEN_FALSE },
	{ "TRUE",						MGICCHIKN_TOKEN_TRUE },
	{ "FALSE",						MGICCHIKN_TOKEN_FALSE },
	{ "ON",							MGICCHIKN_TOKEN_TRUE },
	{ "OFF",						MGICCHIKN_TOKEN_FALSE },
	{ "YES",						MGICCHIKN_TOKEN_TRUE },
	{ "NO",							MGICCHIKN_TOKEN_FALSE }
};
/* *INDENT-ON* */


static GtkRcStyleClass *rc_style_parent_class;
GType mgicchikn_rc_style_type = 0;


static guint
mgicchikn_rc_parse_state_equals (GScanner * scanner,
								 GtkStateType * state)
{
	guint token;

	/* Clear the setting name */
	g_scanner_get_next_token (scanner);

	token = gtk_rc_parse_state (scanner, state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_EQUAL_SIGN)
	{
		return G_TOKEN_EQUAL_SIGN;
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_state_shadow_equals (GScanner * scanner,
										gboolean state_mask[GTK_STATE_LAST],
										gboolean shadow_mask[MGICCHIKN_SHADOW_LAST])
{
	guint token,
	  i;

	/* Clear the mask arrays */
	for (i = 0; i < GTK_STATE_LAST; i++)
		state_mask[i] = FALSE;

	for (i = 0; i < MGICCHIKN_SHADOW_LAST; i++)
		shadow_mask[i] = FALSE;

	/* Clear the setting name */
	g_scanner_get_next_token (scanner);

	token = g_scanner_get_next_token (scanner);
	if (token == G_TOKEN_EQUAL_SIGN)
	{
		for (i = 0; i < GTK_STATE_LAST; i++)
			state_mask[i] = TRUE;

		for (i = 0; i < MGICCHIKN_SHADOW_LAST; i++)
			shadow_mask[i] = TRUE;

		return G_TOKEN_NONE;
	}
	if (token != G_TOKEN_LEFT_BRACE)
	{
		return G_TOKEN_LEFT_BRACE;
	}

	/* States */
	token = g_scanner_get_next_token (scanner);
	while (token != G_TOKEN_RIGHT_BRACE)
	{
		switch (token)
		{
		case MGICCHIKN_TOKEN_ALL:
			for (i = 0; i < GTK_STATE_LAST; i++)
				state_mask[i] = TRUE;
			break;

		case MGICCHIKN_TOKEN_NORMAL:
			state_mask[GTK_STATE_NORMAL] = TRUE;
			break;

		case MGICCHIKN_TOKEN_ACTIVE:
			state_mask[GTK_STATE_ACTIVE] = TRUE;
			break;

		case MGICCHIKN_TOKEN_PRELIGHT:
			state_mask[GTK_STATE_PRELIGHT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_SELECTED:
			state_mask[GTK_STATE_SELECTED] = TRUE;
			break;

		case MGICCHIKN_TOKEN_INSENSITIVE:
			state_mask[GTK_STATE_INSENSITIVE] = TRUE;
			break;

		case G_TOKEN_RIGHT_BRACE:
		case G_TOKEN_COMMA:
			break;

		default:
			return G_TOKEN_RIGHT_BRACE;
			break;
		}

		token = g_scanner_get_next_token (scanner);
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_LEFT_BRACE)
	{
		return G_TOKEN_LEFT_BRACE;
	}

	/* Shadows */
	while (token != G_TOKEN_RIGHT_BRACE)
	{
		token = g_scanner_get_next_token (scanner);
		switch (token)
		{
		case MGICCHIKN_TOKEN_ALL:
			for (i = 0; i < GTK_STATE_LAST; i++)
				shadow_mask[i] = TRUE;
			break;

		case MGICCHIKN_TOKEN_NONE:
			shadow_mask[MGICCHIKN_SHADOW_NONE] = TRUE;
			break;

		case MGICCHIKN_TOKEN_IN:
			shadow_mask[MGICCHIKN_SHADOW_IN] = TRUE;
			break;
		case MGICCHIKN_TOKEN_OUT:
			shadow_mask[MGICCHIKN_SHADOW_OUT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_ETCHED_IN:
			shadow_mask[MGICCHIKN_SHADOW_ETCHED_IN] = TRUE;
			break;
		case MGICCHIKN_TOKEN_ETCHED_OUT:
			shadow_mask[MGICCHIKN_SHADOW_ETCHED_OUT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_FLAT:
			shadow_mask[MGICCHIKN_SHADOW_FLAT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_SHARP_IN:
			shadow_mask[MGICCHIKN_SHADOW_SHARP_IN] = TRUE;
			break;
		case MGICCHIKN_TOKEN_SHARP_OUT:
			shadow_mask[MGICCHIKN_SHADOW_SHARP_OUT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_ROUNDED_IN:
			shadow_mask[MGICCHIKN_SHADOW_ROUNDED_IN] = TRUE;
			break;
		case MGICCHIKN_TOKEN_ROUNDED_OUT:
			shadow_mask[MGICCHIKN_SHADOW_ROUNDED_OUT] = TRUE;
			break;

		case MGICCHIKN_TOKEN_MOTIF_IN:
			shadow_mask[MGICCHIKN_SHADOW_MOTIF_IN] = TRUE;
			break;
		case MGICCHIKN_TOKEN_MOTIF_OUT:
			shadow_mask[MGICCHIKN_SHADOW_MOTIF_OUT] = TRUE;
			break;

		case G_TOKEN_RIGHT_BRACE:
		case G_TOKEN_COMMA:
			break;

		default:
			return MGICCHIKN_TOKEN_IN;
			break;
		}
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_EQUAL_SIGN)
	{
		return G_TOKEN_EQUAL_SIGN;
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_stock_image_transparency (MgicChiknRcStyle * rc_style,
											 GScanner * scanner)
{
	GtkStateType state;
	guint token;

	token = mgicchikn_rc_parse_state_equals (scanner, &state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_FLOAT)
	{
		return G_TOKEN_FLOAT;
	}
	rc_style->stock_image_flags[state] |= MGICCHIKN_STOCK_IMAGE_TRANSPARENCY;
	rc_style->stock_image_transparency[state] = scanner->value.v_float;

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_stock_image_saturation (MgicChiknRcStyle * style,
										   GScanner * scanner)
{
	GtkStateType state;
	guint token;

	token = mgicchikn_rc_parse_state_equals (scanner, &state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_FLOAT)
	{
		return G_TOKEN_FLOAT;
	}
	style->stock_image_flags[state] |= MGICCHIKN_STOCK_IMAGE_SATURATION;
	style->stock_image_saturation[state] = scanner->value.v_float;

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_stock_image_brightness (MgicChiknRcStyle * style,
										   GScanner * scanner)
{
	GtkStateType state;
	guint token;

	token = mgicchikn_rc_parse_state_equals (scanner, &state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_FLOAT)
	{
		return G_TOKEN_FLOAT;
	}
	style->stock_image_flags[state] |= MGICCHIKN_STOCK_IMAGE_BRIGHTNESS;
	style->stock_image_brightness[state] = scanner->value.v_float;

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_font_shadow (MgicChiknRcStyle * style,
								GScanner * scanner)
{
	MgicChiknShadowType shadow_type;
	GtkStateType state;
	guint token;

	token = mgicchikn_rc_parse_state_equals (scanner, &state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	switch (token)
	{
	case MGICCHIKN_TOKEN_NONE:
	case MGICCHIKN_TOKEN_FLAT:
		shadow_type = MGICCHIKN_SHADOW_NONE;
		break;
	case MGICCHIKN_TOKEN_IN:
	case MGICCHIKN_TOKEN_ETCHED_IN:
	case MGICCHIKN_TOKEN_SHARP_IN:
	case MGICCHIKN_TOKEN_ROUNDED_IN:
	case MGICCHIKN_TOKEN_MOTIF_IN:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_IN;
		break;
	case MGICCHIKN_TOKEN_OUT:
	case MGICCHIKN_TOKEN_ETCHED_OUT:
	case MGICCHIKN_TOKEN_SHARP_OUT:
	case MGICCHIKN_TOKEN_ROUNDED_OUT:
	case MGICCHIKN_TOKEN_MOTIF_OUT:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_OUT;
		break;
	default:
		return MGICCHIKN_TOKEN_IN;
		break;
	}

	/* Put the shadows into the array */
	style->font_shadow[state] = shadow_type;

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_shadow (MgicChiknRcStyle * style,
						   GScanner * scanner)
{
	MgicChiknShadowType shadow_type;
	gboolean state_mask[GTK_STATE_LAST],
	  shadow_mask[MGICCHIKN_SHADOW_LAST];
	guint token,
	  i,
	  i2;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	switch (token)
	{
	case MGICCHIKN_TOKEN_NONE:
		shadow_type = MGICCHIKN_SHADOW_NONE;
		break;
	case MGICCHIKN_TOKEN_IN:
		shadow_type = MGICCHIKN_SHADOW_IN;
		break;
	case MGICCHIKN_TOKEN_OUT:
		shadow_type = MGICCHIKN_SHADOW_OUT;
		break;

	case MGICCHIKN_TOKEN_ETCHED_IN:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_IN;
		break;
	case MGICCHIKN_TOKEN_ETCHED_OUT:
		shadow_type = MGICCHIKN_SHADOW_ETCHED_OUT;
		break;

	case MGICCHIKN_TOKEN_FLAT:
		shadow_type = MGICCHIKN_SHADOW_FLAT;
		break;

	case MGICCHIKN_TOKEN_SHARP_IN:
		shadow_type = MGICCHIKN_SHADOW_SHARP_IN;
		break;
	case MGICCHIKN_TOKEN_SHARP_OUT:
		shadow_type = MGICCHIKN_SHADOW_SHARP_OUT;
		break;

	case MGICCHIKN_TOKEN_ROUNDED_IN:
		shadow_type = MGICCHIKN_SHADOW_ROUNDED_IN;
		break;
	case MGICCHIKN_TOKEN_ROUNDED_OUT:
		shadow_type = MGICCHIKN_SHADOW_ROUNDED_OUT;
		break;

	case MGICCHIKN_TOKEN_MOTIF_IN:
		shadow_type = MGICCHIKN_SHADOW_MOTIF_IN;
		break;
	case MGICCHIKN_TOKEN_MOTIF_OUT:
		shadow_type = MGICCHIKN_SHADOW_MOTIF_OUT;
		break;
	default:
		return MGICCHIKN_TOKEN_IN;
		break;
	}

	/* Put the shadows into the RC Style */
	for (i = 0; i < GTK_STATE_LAST; i++)
	{
		if (state_mask[i])
		{
			for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
			{
				if (shadow_mask[i2])
				{
					style->shadow[i][i2] = shadow_type;
				}
			}
		}
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_shadow_width (MgicChiknRcStyle * style,
								 GScanner * scanner)
{
	gboolean state_mask[GTK_STATE_LAST],
	  shadow_mask[MGICCHIKN_SHADOW_LAST];
	guint token,
	  i,
	  i2,
	  value;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_INT)
	{
		return G_TOKEN_INT;
	}
	value = CLAMP (scanner->value.v_int, 0, MAX_SHADOW_WIDTH);

	for (i = 0; i < GTK_STATE_LAST; i++)
	{
		if (state_mask[i])
		{
			for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
			{
				if (shadow_mask[i2])
				{
					style->shadow_width[i][i2] = value;
				}
			}
		}
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_grippy_style (MgicChiknRcStyle * style,
								 GScanner * scanner)
{
	gboolean state_mask[GTK_STATE_LAST],
	  shadow_mask[MGICCHIKN_SHADOW_LAST];
	MgicChiknGrippyStyle grippy_style;
	gdouble grippy_size;
	guint token,
	  i,
	  i2;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	/* Opening curly */
	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_LEFT_CURLY)
	{
		return G_TOKEN_LEFT_CURLY;
	}

	/* Gradient direction */
	token = g_scanner_get_next_token (scanner);
	switch (token)
	{
	case MGICCHIKN_TOKEN_NONE:
		grippy_style = MGICCHIKN_GRIPPY_NONE;
		break;
	case MGICCHIKN_TOKEN_DOTS_IN:
		grippy_style = MGICCHIKN_GRIPPY_DOTS_IN;
		break;
	case MGICCHIKN_TOKEN_DOTS_OUT:
		grippy_style = MGICCHIKN_GRIPPY_DOTS_OUT;
		break;
	case MGICCHIKN_TOKEN_LINES_IN:
		grippy_style = MGICCHIKN_GRIPPY_LINES_IN;
		break;
	case MGICCHIKN_TOKEN_LINES_OUT:
		grippy_style = MGICCHIKN_GRIPPY_LINES_OUT;
		break;
	default:
		return G_TOKEN_ERROR;
		break;
	}

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_COMMA)
	{
		return G_TOKEN_COMMA;
	}

	/* Closing curly */
	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_FLOAT)
	{
		return G_TOKEN_FLOAT;
	}
	grippy_size = CLAMP_PERCENT_FLOAT (scanner->value.v_float);

	/* Closing curly */
	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_RIGHT_CURLY)
	{
		return G_TOKEN_RIGHT_CURLY;
	}

	for (i = 0; i < GTK_STATE_LAST; i++)
	{
		for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
		{
			if (state_mask[i] && shadow_mask[i2])
			{
				style->grippy_style[i][i2] = grippy_style;
				style->grippy_size[i][i2] = grippy_size;
			}
		}
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_font_underline (MgicChiknRcStyle * rc_style,
								   GScanner * scanner)
{
	GtkStateType state;
	guint token;

	token = mgicchikn_rc_parse_state_equals (scanner, &state);
	if (token != G_TOKEN_NONE)
	{
		return token;
	}

	token = g_scanner_get_next_token (scanner);

	switch (token)
	{
	case MGICCHIKN_TOKEN_TRUE:
	case MGICCHIKN_TOKEN_SINGLE:
		rc_style->font_underline[state] = MGICCHIKN_UNDERLINE_SINGLE;
		break;
	case MGICCHIKN_TOKEN_FALSE:
	case MGICCHIKN_TOKEN_NONE:
		rc_style->font_underline[state] = MGICCHIKN_UNDERLINE_NONE;
		break;
	case MGICCHIKN_TOKEN_DOUBLE:
		rc_style->font_underline[state] = MGICCHIKN_UNDERLINE_DOUBLE;
		break;
	default:
		return MGICCHIKN_TOKEN_SINGLE;
		break;
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_radio_image (MgicChiknRcStyle * rc_style,
								GtkSettings * settings,
								GScanner * scanner)
{
	guint token;
	gchar *value = NULL;
	gboolean state_mask[GTK_STATE_LAST] = { 0 },
	  shadow_mask[MGICCHIKN_SHADOW_LAST] = { 0 };
	gint i, i2;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
		return token;

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_STRING)
		return G_TOKEN_STRING;

	value = gtk_rc_find_pixmap_in_path (settings, scanner, scanner->value.v_string);

	if (value != NULL)
	{
		g_cache_insert (MGICCHIKN_RC_STYLE_GET_CLASS (rc_style)->raw_pixbufs, value);
		for (i = 0; i < GTK_STATE_LAST; i++)
		{
			if (state_mask[i] == TRUE)
			{
				for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i++)
				{
					if (shadow_mask[i] == TRUE)
					{
						rc_style->radio_image[i][i2] = value;
					}
				}
			}
		}
	}

	return G_TOKEN_NONE;
}


static guint
mgicchikn_rc_parse_check_image (MgicChiknRcStyle * rc_style,
								GtkSettings * settings,
								GScanner * scanner)
{
	guint token;
	gchar *value = NULL;
	gboolean state_mask[GTK_STATE_LAST] = { 0 },
	  shadow_mask[MGICCHIKN_SHADOW_LAST] = { 0 };
	gint i, i2;

	token = mgicchikn_rc_parse_state_shadow_equals (scanner, state_mask, shadow_mask);
	if (token != G_TOKEN_NONE)
		return token;

	token = g_scanner_get_next_token (scanner);
	if (token != G_TOKEN_STRING)
		return G_TOKEN_STRING;

	value = gtk_rc_find_pixmap_in_path (settings, scanner, scanner->value.v_string);

	if (value != NULL)
	{
		g_cache_insert (MGICCHIKN_RC_STYLE_GET_CLASS (rc_style)->raw_pixbufs, value);
		for (i = 0; i < GTK_STATE_LAST; i++)
		{
			if (state_mask[i] == TRUE)
			{
				for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i++)
				{
					if (shadow_mask[i] == TRUE)
					{
						rc_style->check_image[i][i2] = value;
					}
				}
			}
		}
	}

	return G_TOKEN_NONE;
}



static guint
mgicchikn_rc_style_parse (GtkRcStyle * rc_style,
						  GtkSettings * settings,
						  GScanner * scanner)
{
	MgicChiknRcStyle *style;
	static GQuark scope = 0;
	GQuark old_scope;
	guint token;
	gint i;

	g_return_val_if_fail (rc_style != NULL, G_TOKEN_NONE);
	g_return_val_if_fail (MGICCHIKN_IS_RC_STYLE (rc_style), G_TOKEN_NONE);
	style = MGICCHIKN_RC_STYLE (rc_style);
	if (!scope)
		scope = g_quark_from_string ("theme_engine");
	old_scope = g_scanner_set_scope (scanner, scope);
	/* If we don't have the symbol table inside scanner, put it in there */
	if (!g_scanner_lookup_symbol (scanner, symbols[0].name))
	{
		for (i = 0; i < G_N_ELEMENTS (symbols); i++)
		{
			g_scanner_scope_add_symbol (scanner, scope,
										symbols[i].name,
										GUINT_TO_POINTER (symbols[i].token));
		}
	}

	token = g_scanner_peek_next_token (scanner);
	while (token != G_TOKEN_RIGHT_CURLY)
	{
		switch (token)
		{
		case MGICCHIKN_TOKEN_STOCK_IMAGE_TRANSPARENCY:
			token = mgicchikn_rc_parse_stock_image_transparency (style, scanner);
			break;
		case MGICCHIKN_TOKEN_STOCK_IMAGE_SATURATION:
			token = mgicchikn_rc_parse_stock_image_saturation (style, scanner);
			break;
		case MGICCHIKN_TOKEN_STOCK_IMAGE_BRIGHTNESS:
			token = mgicchikn_rc_parse_stock_image_brightness (style, scanner);
			break;
		case MGICCHIKN_TOKEN_SHADOW:
			token = mgicchikn_rc_parse_shadow (style, scanner);
			break;
		case MGICCHIKN_TOKEN_SHADOW_WIDTH:
			token = mgicchikn_rc_parse_shadow_width (style, scanner);
			break;
		case MGICCHIKN_TOKEN_GRIPPY_STYLE:
			token = mgicchikn_rc_parse_grippy_style (style, scanner);
			break;
		case MGICCHIKN_TOKEN_FONT_SHADOW:
			token = mgicchikn_rc_parse_font_shadow (style, scanner);
			break;
		case MGICCHIKN_TOKEN_FONT_UNDERLINE:
			token = mgicchikn_rc_parse_font_underline (style, scanner);
			break;
		case MGICCHIKN_TOKEN_CHECK_IMAGE:
			token = mgicchikn_rc_parse_check_image (style, settings, scanner);
			break;
		case MGICCHIKN_TOKEN_RADIO_IMAGE:
			token = mgicchikn_rc_parse_radio_image (style, settings, scanner);
			break;
		default:
			break;
		}

		if (token != G_TOKEN_NONE)
			return token;
		token = g_scanner_peek_next_token (scanner);
	}

	g_scanner_get_next_token (scanner);
	g_scanner_set_scope (scanner, old_scope);
	return G_TOKEN_NONE;
}


static void
mgicchikn_rc_style_merge (GtkRcStyle * destination,
						  GtkRcStyle * source)
{
	gint i,
	  i2;
	MgicChiknRcStyle *dest = NULL;
	MgicChiknRcStyle *src = NULL;

	g_return_if_fail (destination != NULL);
	g_return_if_fail (GTK_IS_RC_STYLE (destination));
	g_return_if_fail (source != NULL);
	g_return_if_fail (GTK_IS_RC_STYLE (source));
	rc_style_parent_class->merge (destination, source);
	if (MGICCHIKN_IS_RC_STYLE (source) && MGICCHIKN_IS_RC_STYLE (destination))
	{
		dest = MGICCHIKN_RC_STYLE (destination);
		src = MGICCHIKN_RC_STYLE (source);
		for (i = 0; i < GTK_STATE_INSENSITIVE + 1; i++)
		{
			if (!
				(dest->
				 stock_image_flags[i] &
				 MGICCHIKN_STOCK_IMAGE_TRANSPARENCY)
				&& (src->stock_image_flags[i] & MGICCHIKN_STOCK_IMAGE_TRANSPARENCY))
			{
				dest->stock_image_flags[i] |= MGICCHIKN_STOCK_IMAGE_TRANSPARENCY;
				dest->stock_image_transparency[i] = src->stock_image_transparency[i];
			}
			if (!
				(dest->
				 stock_image_flags[i] &
				 MGICCHIKN_STOCK_IMAGE_SATURATION)
				&& (src->stock_image_flags[i] & MGICCHIKN_STOCK_IMAGE_SATURATION))
			{
				dest->stock_image_flags[i] |= MGICCHIKN_STOCK_IMAGE_SATURATION;
				dest->stock_image_saturation[i] = src->stock_image_saturation[i];
			}
			if (!
				(dest->
				 stock_image_flags[i] &
				 MGICCHIKN_STOCK_IMAGE_BRIGHTNESS)
				&& (src->stock_image_flags[i] & MGICCHIKN_STOCK_IMAGE_BRIGHTNESS))
			{
				dest->stock_image_flags[i] |= MGICCHIKN_STOCK_IMAGE_BRIGHTNESS;
				dest->stock_image_brightness[i] = src->stock_image_brightness[i];
			}


			if (dest->font_shadow[i] == MGICCHIKN_SHADOW_UNSET
				&& src->font_shadow[i] != MGICCHIKN_SHADOW_UNSET)
			{
				dest->font_shadow[i] = src->font_shadow[i];
			}

			if (dest->font_underline[i] == MGICCHIKN_UNDERLINE_UNSET
				&& src->font_underline[i] != MGICCHIKN_UNDERLINE_UNSET)
			{
				dest->font_underline[i] = src->font_underline[i];
			}

			for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
			{
				if (dest->shadow[i][i2] == MGICCHIKN_SHADOW_UNSET
					&& src->shadow[i][i2] != MGICCHIKN_SHADOW_UNSET)
				{
					dest->shadow[i][i2] = src->shadow[i][i2];
				}

				if (dest->shadow_width[i][i2] < 0 && src->shadow_width[i][i2] >= 0)
				{
					dest->shadow_width[i][i2] = src->shadow_width[i][i2];
				}

				if (dest->grippy_style[i][i2] == MGICCHIKN_GRIPPY_UNSET
					&& src->grippy_style[i][i2] != MGICCHIKN_GRIPPY_UNSET)
				{
					dest->grippy_style[i][i2] = src->grippy_style[i][i2];
					dest->grippy_size[i][i2] = src->grippy_size[i][i2];
				}

				if (dest->check_image[i][i2] == NULL && src->check_image[i][i2] != NULL)
				{
					dest->check_image[i][i2] = src->check_image[i][i2];
				}

				if (dest->radio_image[i][i2] == NULL && src->radio_image[i][i2] != NULL)
				{
					dest->radio_image[i][i2] = src->radio_image[i][i2];
				}
			}
		}
	}
}


static GtkStyle *
mgicchikn_rc_style_create_style (GtkRcStyle * gtk_rc_style)
{
	MgicChiknStyle *style = g_object_new (MGICCHIKN_TYPE_STYLE, NULL);

	return GTK_STYLE (style);
}


static GdkPixbuf *
load_raw_pixbuf (const gchar * file)
{
	GError *err = NULL;
	GdkPixbuf *pixbuf;

	if (strcmp (file, "<default-check>") == 0)
		pixbuf = gdk_pixbuf_from_pixdata (&check_img, TRUE, &err);
	else if (strcmp (file, "<default-uncheck>") == 0)
		pixbuf = gdk_pixbuf_from_pixdata (&uncheck_img, TRUE, &err);
	else if (strcmp (file, "<default-incheck>") == 0)
		pixbuf = gdk_pixbuf_from_pixdata (&incheck_img, TRUE, &err);
	else if (strcmp (file, "<default-radio>") == 0)
	   pixbuf = gdk_pixbuf_from_pixdata (&radio_img, TRUE, &err);
	else if (strcmp (file, "<default-unradio>") == 0)
	   pixbuf = gdk_pixbuf_from_pixdata (&unradio_img, TRUE, &err);
	else if (strcmp (file, "<default-inradio>") == 0)
	   pixbuf = gdk_pixbuf_from_pixdata (&inradio_img, TRUE, &err);
	else
		pixbuf = gdk_pixbuf_new_from_file (file, &err);
	if (err != NULL)
		g_warning ("Unable to load \"%s\" (%s).", file, err->message);
	return pixbuf;
}


static void
mgicchikn_rc_style_base_init (MgicChiknRcStyleClass * class)
{
	class->raw_pixbufs =
		g_cache_new ((GCacheNewFunc) load_raw_pixbuf,
					 g_object_unref, (GCacheDupFunc) g_strdup,
					 g_free, g_str_hash, g_direct_hash, g_str_equal);
}


static void
mgicchikn_rc_style_base_finalize (MgicChiknRcStyleClass * class)
{
	g_cache_destroy (class->raw_pixbufs);
}


static void
mgicchikn_rc_style_class_init (MgicChiknRcStyleClass * class)
{
	GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (class);

	rc_style_parent_class = g_type_class_peek_parent (class);
	rc_style_class->parse = mgicchikn_rc_style_parse;
	rc_style_class->merge = mgicchikn_rc_style_merge;
	rc_style_class->create_style = mgicchikn_rc_style_create_style;
}


static void
mgicchikn_rc_style_init (MgicChiknRcStyle * rc_style)
{
	guint i,
	  i2;

	for (i = 0; i < GTK_STATE_LAST; i++)
	{
		rc_style->stock_image_flags[i] = MGICCHIKN_STOCK_IMAGE_NONE;
		rc_style->stock_image_transparency[i] = 1.0;
		rc_style->stock_image_saturation[i] = 1.0;
		rc_style->stock_image_brightness[i] = 1.0;
		rc_style->font_shadow[i] = MGICCHIKN_SHADOW_UNSET;
		rc_style->font_underline[i] = MGICCHIKN_UNDERLINE_UNSET;

		for (i2 = 0; i2 < MGICCHIKN_SHADOW_LAST; i2++)
		{
			rc_style->shadow[i][i2] = MGICCHIKN_SHADOW_UNSET;
			rc_style->shadow_width[i][i2] = -1;
			
			rc_style->grippy_style[i][i2] = MGICCHIKN_GRIPPY_UNSET;
			rc_style->grippy_size[i][i2] = 1.0;

			rc_style->check_image[i][i2] = "<default-uncheck>";
			rc_style->radio_image[i][i2] = "<default-unradio>";
		}

		rc_style->check_image[i][MGICCHIKN_SHADOW_IN] = "<default-check>";
		rc_style->radio_image[i][MGICCHIKN_SHADOW_IN] = "<default-radio>";

		rc_style->check_image[i][MGICCHIKN_SHADOW_ETCHED_IN] = "<default-incheck>";
		rc_style->radio_image[i][MGICCHIKN_SHADOW_ETCHED_IN] = "<default-inradio>";
	}
}


void
mgicchikn_rc_style_register_type (GTypeModule * module)
{
	if (!mgicchikn_rc_style_type)
	{
		static const GTypeInfo info = {
			sizeof (MgicChiknRcStyleClass),
			(GBaseInitFunc) mgicchikn_rc_style_base_init,
			(GBaseFinalizeFunc) mgicchikn_rc_style_base_finalize,
			(GClassInitFunc) mgicchikn_rc_style_class_init,
			NULL, NULL,
			sizeof (MgicChiknRcStyle),
			0,	/* n_preallocs */
			(GInstanceInitFunc) mgicchikn_rc_style_init,
		};

		mgicchikn_rc_style_type =
			g_type_module_register_type (module, GTK_TYPE_RC_STYLE,
										 "MgicChiknRcStyle", &info, 0);
	}
}
