#include "lighthouseblue_rc_style.h"
#include "lighthouseblue_style.h"

static void   lighthouseblue_rc_style_init (LighthouseBlueRcStyle *style);
static void   lighthouseblue_rc_style_class_init (LighthouseBlueRcStyleClass *klass);

static guint  lighthouseblue_rc_style_parse (GtkRcStyle *rc_style, GtkSettings *settings,
					     GScanner *scanner);

static void   lighthouseblue_rc_style_merge (GtkRcStyle *dest, GtkRcStyle *src);

static GtkStyle *lighthouseblue_rc_style_create_style (GtkRcStyle *rc_style);


static GtkRcStyleClass *parent_class;

GType lighthouseblue_type_rc_style = 0;

enum
  {
    TOKEN_NOTEBOOKPATCH = G_TOKEN_LAST + 1,
    TOKEN_COMBINETVSELECT,
    TOKEN_TRUE,
    TOKEN_FALSE
  };

static struct
{
  const gchar *name;
  guint token;
}
theme_symbols[] = 
  {
    { "has_notebook_patch", TOKEN_NOTEBOOKPATCH },
    { "combine_treeview_select", TOKEN_COMBINETVSELECT },
    { "TRUE", TOKEN_TRUE },
    { "FALSE", TOKEN_FALSE }
  };


void lighthouseblue_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (LighthouseBlueRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) lighthouseblue_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (LighthouseBlueRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) lighthouseblue_rc_style_init,
  };
  
  lighthouseblue_type_rc_style = g_type_module_register_type (module,
							      GTK_TYPE_RC_STYLE,
							      "LighthouseBlueRcStyle",
							      &object_info, 0);
}

static void lighthouseblue_rc_style_init (LighthouseBlueRcStyle *style)
{
  style->has_notebook_patch = FALSE;
  style->combine_treeview_select = FALSE;
}

static void lighthouseblue_rc_style_class_init (LighthouseBlueRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  rc_style_class->parse = lighthouseblue_rc_style_parse;
  rc_style_class->merge = lighthouseblue_rc_style_merge;
  rc_style_class->create_style = lighthouseblue_rc_style_create_style;
}

static guint theme_parse_boolean (GScanner *scanner, GTokenType wanted_token, guint *retval)
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
  if (token == TOKEN_TRUE)
    {
      *retval = TRUE;
    }
  else if (token == TOKEN_FALSE)
    {
      *retval = FALSE;
    }
  else
    {
      *retval = FALSE;
    }

  return G_TOKEN_NONE;
}

static guint lighthouseblue_rc_style_parse (GtkRcStyle *rc_style,
					    GtkSettings  *settings,
					    GScanner   *scanner)
{
  static GQuark scope_id = 0;
  LighthouseBlueRcStyle *lighthouseblue_style = LIGHTHOUSEBLUE_RC_STYLE (rc_style);

  guint old_scope;
  guint token;
  guint i;

  /* Set up a new scope in this scanner */
  if (!scope_id)
    {
      scope_id = g_quark_from_string ("lighthouseblue_theme_engine");
    }

  /* If we bail out due to errors, we don't reset the scope, so the
   * error messaging code can make sense of our tokens. */
  old_scope = g_scanner_set_scope (scanner, scope_id);

  /* Check if we already added our symbols to this scope */
  if (!g_scanner_lookup_symbol (scanner, theme_symbols[0].name))
    {
      g_scanner_freeze_symbol_table (scanner);
      for (i = 0; i < G_N_ELEMENTS (theme_symbols); i++)
	{
	  g_scanner_scope_add_symbol (scanner, scope_id, theme_symbols[i].name, 
				      GINT_TO_POINTER (theme_symbols[i].token));
	}
      g_scanner_thaw_symbol_table (scanner);
    }

  /* Read to go, now parse the top level */
  token = g_scanner_peek_next_token (scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
	case TOKEN_NOTEBOOKPATCH:
	  token = theme_parse_boolean (scanner, TOKEN_NOTEBOOKPATCH, &lighthouseblue_style->has_notebook_patch);
	  break;
	case TOKEN_COMBINETVSELECT:
	  token = theme_parse_boolean (scanner, TOKEN_COMBINETVSELECT, &lighthouseblue_style->combine_treeview_select);
	  break;
	default:
	  g_scanner_get_next_token (scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	{
	  return token;
	}

      token = g_scanner_peek_next_token (scanner);
    }


  g_scanner_get_next_token(scanner);
  g_scanner_set_scope (scanner, old_scope);

  return G_TOKEN_NONE;
}

static void
lighthouseblue_rc_style_merge (GtkRcStyle * dest,
			       GtkRcStyle * src)
{
  parent_class->merge (dest, src);

  if (LIGHTHOUSEBLUE_IS_RC_STYLE (src)) 
    {
      LighthouseBlueRcStyle *src_data = LIGHTHOUSEBLUE_RC_STYLE (src);
      LighthouseBlueRcStyle *dest_data = LIGHTHOUSEBLUE_RC_STYLE (dest);

      dest_data->has_notebook_patch = src_data->has_notebook_patch;
      dest_data->combine_treeview_select = src_data->combine_treeview_select;
    }
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *
lighthouseblue_rc_style_create_style (GtkRcStyle *rc_style)
{
  void *ptr;
  ptr = GTK_STYLE (g_object_new (LIGHTHOUSEBLUE_TYPE_STYLE, NULL));
  return (GtkStyle *)ptr;
}
