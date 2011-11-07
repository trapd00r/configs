#include <gtk/gtk.h>

#include "crux-rc-style.h"
#include "crux-style.h"
#include "crux-rc-parser.h"

#include "debug.h"

#include <stdio.h>

GType crux_type_rc_style = 0;

static GtkStyle *crux_rc_style_create_style (GtkRcStyle *rc_style);
static void crux_rc_style_merge (GtkRcStyle *dest, GtkRcStyle *src);

static void crux_rc_style_finalize (GObject *object);

GtkRcStyleClass *rc_parent_class;

static void
crux_rc_style_init (CruxRcStyle *style)
{
  style->theme_data = NULL;
}

static void
crux_rc_style_class_init (CruxRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class;
  GObjectClass *object_class;

  rc_style_class = GTK_RC_STYLE_CLASS (klass);
  object_class = G_OBJECT_CLASS (klass);

  rc_parent_class = g_type_class_peek_parent (klass);

  rc_style_class->parse = &crux_parse_rc_style;
  rc_style_class->merge = &crux_rc_style_merge;
  rc_style_class->create_style = &crux_rc_style_create_style;

  object_class->finalize = crux_rc_style_finalize;
}

static void
crux_rc_style_finalize (GObject *object)
{
  CruxRcStyle *rc_style = CRUX_RC_STYLE (object);

  theme_data_unref (rc_style->theme_data);

  G_OBJECT_CLASS (rc_parent_class)->finalize (object);
}

void
crux_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (CruxRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) crux_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (CruxRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) crux_rc_style_init,
  };
  
  crux_type_rc_style = g_type_module_register_type (module,
                                                      GTK_TYPE_RC_STYLE,
                                                      "CruxRcStyle",
                                                      &object_info, 0);
}


static void
crux_rc_style_merge (GtkRcStyle *dest,
		       GtkRcStyle *src)
{
  if (CRUX_IS_RC_STYLE (src)) {
    CruxRcStyle *crux_dest;
    CruxRcStyle *crux_src;

    crux_dest = CRUX_RC_STYLE (dest);
    crux_src  = CRUX_RC_STYLE (src);
    
    if (!crux_dest->theme_data) {
      if (crux_src->theme_data) {
	theme_data_ref (crux_src->theme_data);
	crux_dest->theme_data = crux_src->theme_data;
      }
    }
  }
  
  rc_parent_class->merge (dest, src);
}

    
static GtkStyle *
crux_rc_style_create_style (GtkRcStyle *rc_style)
{
  return GTK_STYLE (g_object_new (CRUX_TYPE_STYLE, NULL));
}
    





