#include "cleanice.h"

static void cleanice_rc_style_init (CleanIceRCStyle * style);
static void cleanice_rc_style_class_init (CleanIceRCStyleClass * klass);

static void cleanice_rc_style_merge (GtkRcStyle * dest, GtkRcStyle * src);
static GtkStyle *cleanice_rc_style_create_style (GtkRcStyle * rc_style);

static GtkRcStyleClass * parent_class;
GType cleanice_type_rc_style = 0;

void cleanice_rc_style_register_type (GTypeModule * module) {
  static const GTypeInfo object_info = {
    sizeof (CleanIceRCStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) cleanice_rc_style_class_init,
    NULL,
    NULL,
    sizeof (CleanIceRCStyle),
    0,
    (GInstanceInitFunc) cleanice_rc_style_init,
  };

  cleanice_type_rc_style = g_type_module_register_type (module,
							GTK_TYPE_RC_STYLE,
							"CleanIceRCStyle",
							&object_info, 0);
}

static void cleanice_rc_style_init (CleanIceRCStyle * style) {
}

static void cleanice_rc_style_class_init (CleanIceRCStyleClass * klass) {
  GtkRcStyleClass * rc_style_class = GTK_RC_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  rc_style_class->merge = cleanice_rc_style_merge;
  rc_style_class->create_style = cleanice_rc_style_create_style;

  gtk_rc_parse_string ("style \"cleanice-main-defaults\" {\n"
		       "  GtkCheckButton::indicator-size = 10\n"
		       "  GtkPaned::handle-size = 9\n"
		       "} widget_class \"*\""
		       " style \"cleanice-main-defaults\"");

  gtk_rc_parse_string ("style \"cleanice-scales-defaults\" {\n"
		       "  GtkRange::slider-width = 20\n"
		       "  GtkScale::slider-length = 10\n"
		       "} widget_class \"*Scale*\""
		       " style \"cleanice-scales-defaults\"");

  gtk_rc_parse_string ("style \"cleanice-sbar-defaults\" {\n"
		       "  GtkRange::slider-width = 13\n"
		       "  GtkRange::stepper-size = 13\n"
		       "  GtkScrollbar::min-slider-length = 18\n"
		       "  GtkScrollbar::has_forward_stepper = 1\n"
		       "  GtkScrollbar::has_backward_stepper = 1\n"
		       "  GtkScrollbar::has_secondary_backward_stepper = 1\n"
		       "} widget_class \"*Scrollbar*\""
		       " style \"cleanice-sbar-defaults\"");
}

static void cleanice_rc_style_merge (GtkRcStyle * dest, GtkRcStyle * src) {
  parent_class->merge (dest, src);
}

static GtkStyle * cleanice_rc_style_create_style (GtkRcStyle * rc_style) {
  void * ptr;

  ptr = g_object_new (CLEANICE_TYPE_STYLE, NULL);
  return (GtkStyle *) ptr;
}
