
#include "flat_rc_style.h"
#include "flat_style.h"

static void      flat_rc_style_init         (FlatRcStyle      *style);
static void      flat_rc_style_class_init   (FlatRcStyleClass *klass);
static void      flat_rc_style_finalize     (GObject             *object);
static guint     flat_rc_style_parse        (GtkRcStyle          *rc_style,
					       GtkSettings          *settings,
					       GScanner             *scanner);
static void      flat_rc_style_merge       (GtkRcStyle           *dest,
					       GtkRcStyle           *src);

static GtkStyle *flat_rc_style_create_style (GtkRcStyle          *rc_style);

static GtkRcStyleClass *parent_class;

GType flat_type_rc_style = 0;

void
flat_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (FlatRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) flat_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (FlatRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) flat_rc_style_init,
  };
  
  flat_type_rc_style = g_type_module_register_type (module,
						      GTK_TYPE_RC_STYLE,
						      "FlatRcStyle",
						      &object_info, 0);
}

static void
flat_rc_style_init (FlatRcStyle *style)
{
}

static void
flat_rc_style_class_init (FlatRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (klass);
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  rc_style_class->parse = flat_rc_style_parse;
  rc_style_class->merge = flat_rc_style_merge;
  rc_style_class->create_style = flat_rc_style_create_style;
}

static guint
flat_rc_style_parse (GtkRcStyle *rc_style,
			GtkSettings  *settings,
			GScanner   *scanner)
{
  static GQuark       scope_id = 0;
  FlatRcStyle     *theme_data = FLAT_RC_STYLE (rc_style);
  guint               old_scope;
  guint               token;
  guint               i;

  if (!scope_id)
    scope_id = g_quark_from_string("theme_engine");

  old_scope = g_scanner_set_scope(scanner, scope_id);
  
  token = g_scanner_peek_next_token(scanner);
  while (token != G_TOKEN_RIGHT_CURLY)
    {
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
flat_rc_style_merge (GtkRcStyle * dest,
			GtkRcStyle * src)
{
  parent_class->merge (dest, src);
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *
flat_rc_style_create_style (GtkRcStyle *rc_style)
{
  void *ptr;
  ptr = GTK_STYLE (g_object_new (FLAT_TYPE_STYLE, NULL));
  return (GtkStyle *)ptr;
}
