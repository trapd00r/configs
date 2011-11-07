
enum
{
  TOKEN_CONTRAST = G_TOKEN_LAST + 1,
  TOKEN_CONTRAST_CENTER,
  TOKEN_ROUNDED_BUTTONS,
  TOKEN_WIDE,

  TOKEN_TRUE,
  TOKEN_FALSE
};

static struct
  {
    const gchar        *name;
    guint               token;
  }
theme_symbols[] =
{
  { "contrast", 	TOKEN_CONTRAST  },
  { "contrast_center",	TOKEN_CONTRAST_CENTER  },
  { "rounded_buttons",	TOKEN_ROUNDED_BUTTONS  },
  { "wide", 		TOKEN_WIDE  },

  { "TRUE",             TOKEN_TRUE },
  { "FALSE",            TOKEN_FALSE },
};

static guint
theme_parse_color(GScanner     *scanner,
		  GdkColor     *color)
{
  guint token;

  /* Skip 'blah_color' */
  token = g_scanner_get_next_token(scanner);

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    return G_TOKEN_EQUAL_SIGN;

  return gtk_rc_parse_color (scanner, color);
}

static guint
theme_parse_named_double(GScanner     *scanner,
			 double       *value)
{
  guint token;

  /* Skip name */
  token = g_scanner_get_next_token(scanner);

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    return G_TOKEN_EQUAL_SIGN;

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_FLOAT)
    return G_TOKEN_FLOAT;

  *value = scanner->value.v_float;
  
  return G_TOKEN_NONE;
}

static guint
theme_parse_boolean(GScanner *scanner,
                    GTokenType wanted_token,
                    guint *retval)
{
  guint token;
  
  token = g_scanner_get_next_token(scanner);
  if (token != wanted_token)
    return wanted_token;
  
  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    return G_TOKEN_EQUAL_SIGN;
  
  token = g_scanner_get_next_token(scanner);
  if (token == TOKEN_TRUE)
    *retval = TRUE;
  else if (token == TOKEN_FALSE)
    *retval = FALSE;
  else
    return TOKEN_TRUE;

  return G_TOKEN_NONE;
}

static guint
parse_rc_style (GScanner   *scanner,
		double     *contrast,
		double     *contrast_center,
		gboolean   *rounded_buttons,
		gboolean   *wide,
		IndustrialFields *fields)
{
  static GQuark scope_id = 0;
  guint old_scope;
  guint token;
  guint i;
  
  /* Set up a new scope in this scanner. */

  if (!scope_id)
    scope_id = g_quark_from_string("industrial_theme_engine");

  /* If we bail out due to errors, we *don't* reset the scope, so the
   * error messaging code can make sense of our tokens.
   */
  old_scope = g_scanner_set_scope(scanner, scope_id);

  /* Now check if we already added our symbols to this scope
   * (in some previous call to industrial_rc_style_parse for the
   * same scanner.
   */

  if (!g_scanner_lookup_symbol(scanner, theme_symbols[0].name))
    {
      g_scanner_freeze_symbol_table(scanner);
      for (i = 0; i < G_N_ELEMENTS (theme_symbols); i++)
	g_scanner_scope_add_symbol(scanner, scope_id,
				   theme_symbols[i].name,
				   GINT_TO_POINTER(theme_symbols[i].token));
      g_scanner_thaw_symbol_table(scanner);
    }

  /* We're ready to go, now parse the top level */

  token = g_scanner_peek_next_token(scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
	case TOKEN_CONTRAST:
	  token = theme_parse_named_double(scanner, contrast);
	  *fields |= INDUSTRIAL_FIELDS_CONTRAST;
	  break;
	case TOKEN_CONTRAST_CENTER:
	  token = theme_parse_named_double(scanner, contrast_center);
	  *fields |= INDUSTRIAL_FIELDS_CONTRAST_CENTER;
	  break;
	case TOKEN_ROUNDED_BUTTONS:
	  token = theme_parse_boolean(scanner, TOKEN_ROUNDED_BUTTONS, rounded_buttons);
	  *fields |= INDUSTRIAL_FIELDS_ROUNDED_BUTTONS;
	  break;
	case TOKEN_WIDE:
	  token = theme_parse_boolean(scanner, TOKEN_WIDE, wide);
	  *fields |= INDUSTRIAL_FIELDS_WIDE;
	  break;
	default:
	  g_scanner_get_next_token(scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	return token;

      token = g_scanner_peek_next_token(scanner);
    }

  g_scanner_get_next_token(scanner);

  g_scanner_set_scope(scanner, old_scope);

  return G_TOKEN_NONE;
}
