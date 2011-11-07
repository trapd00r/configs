#include "xfce_rc_style.h"
#include "xfce_style.h"

static void      xfce_rc_style_init         (XfceRcStyle      *style);
static void      xfce_rc_style_class_init   (XfceRcStyleClass *klass);
static void      xfce_rc_style_finalize     (GObject          *object);
static guint     xfce_rc_style_parse        (GtkRcStyle       *rc_style,
					     GtkSettings      *settings,
					     GScanner	      *scanner);
static void      xfce_rc_style_merge        (GtkRcStyle       *dest,
					     GtkRcStyle       *src);

static struct
  {
    gchar       *name;
    guint        token;
  }
theme_symbols[] =
{
  { "smooth_edge", TOKEN_SMOOTHEDGE },
  { "TRUE",        TOKEN_TRUE },
  { "FALSE",       TOKEN_FALSE },
};

static guint n_theme_symbols = sizeof(theme_symbols) / sizeof(theme_symbols[0]);

static GtkStyle *xfce_rc_style_create_style (GtkRcStyle       *rc_style);

static GtkRcStyleClass *parent_class;

GType xfce_type_rc_style = 0;

void
xfce_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (XfceRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) xfce_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (XfceRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) xfce_rc_style_init,
  };
  
  xfce_type_rc_style = g_type_module_register_type (module, GTK_TYPE_RC_STYLE, "XfceRcStyle", &object_info, 0);
}

static void
xfce_rc_style_init (XfceRcStyle *style)
{
}

static void
xfce_rc_style_class_init (XfceRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (klass);
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  rc_style_class->parse = xfce_rc_style_parse;
  rc_style_class->merge = xfce_rc_style_merge;
  rc_style_class->create_style = xfce_rc_style_create_style;
}

static guint
theme_parse_boolean(GScanner *scanner, GTokenType wanted_token, guint *retval)
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
xfce_rc_style_parse (GtkRcStyle *rc_style, GtkSettings *settings, GScanner *scanner)
{
  static GQuark scope_id = 0;
  XfceRcStyle  *theme_data = XFCE_RC_STYLE (rc_style);
  guint         old_scope;
  guint         token;
  guint         i;

  /* Set up a new scope in this scanner. */

  if (!scope_id)
    scope_id = g_quark_from_string("theme_engine");

  old_scope = g_scanner_set_scope(scanner, scope_id);
  if (!g_scanner_lookup_symbol(scanner, theme_symbols[0].name))
    {
      for (i = 0; i < n_theme_symbols; i++)
        {
          g_scanner_scope_add_symbol(scanner, scope_id, theme_symbols[i].name, GINT_TO_POINTER(theme_symbols[i].token));
        }
    }
  theme_data->smooth_edge = FALSE;
  token = g_scanner_peek_next_token(scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token)
	{
        case TOKEN_SMOOTHEDGE:
          token = theme_parse_boolean(scanner, TOKEN_SMOOTHEDGE, &i);
          if (token != G_TOKEN_NONE)
	  {
            break;
          }
	  theme_data->smooth_edge = i;
          break;
	default:
	  g_scanner_get_next_token(scanner);
	  token = G_TOKEN_RIGHT_CURLY;
	  break;
	}

      if (token != G_TOKEN_NONE)
	{
	  g_free(theme_data);
	  return token;
	}
      token = g_scanner_peek_next_token(scanner);
    }

  g_scanner_get_next_token(scanner);

  g_scanner_set_scope(scanner, old_scope);

  return G_TOKEN_NONE;
}

static void
xfce_rc_style_merge (GtkRcStyle * dest, GtkRcStyle * src)
{
  if (XFCE_IS_RC_STYLE (src)) {
    XfceRcStyle        *src_data = XFCE_RC_STYLE (src);
    XfceRcStyle        *dest_data = XFCE_RC_STYLE (dest);

    dest_data->smooth_edge = src_data->smooth_edge;
  }
  
  parent_class->merge (dest, src);
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *
xfce_rc_style_create_style (GtkRcStyle *rc_style)
{
  void *ptr;
  ptr = GTK_STYLE (g_object_new (XFCE_TYPE_STYLE, NULL));
  return (GtkStyle *)ptr;
}
