#include "crux-style.h"
#include "crux-draw.h"
#include "crux-common.h"

#include <gtk/gtk.h>
#include <stdio.h>

GType crux_type_style = 0;

static GtkStyleClass *parent_class = NULL;

static void crux_style_class_init (CruxStyleClass *klass);

static void
crux_style_init (CruxStyle *style)
{
} 

void
crux_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (CruxStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) crux_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (CruxStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) crux_style_init,
  };
  
  crux_type_style = g_type_module_register_type (module,
						 GTK_TYPE_STYLE,
						 "CruxStyle",
						 &object_info, 0);
}

static void
crux_style_class_init (CruxStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;
  style_class->draw_polygon = draw_polygon;
  style_class->draw_arrow = draw_arrow;
  style_class->draw_diamond = draw_diamond;
  style_class->draw_string = draw_string;
  style_class->draw_box = draw_box;
  //style_class->draw_flat_box = draw_flat_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_focus = draw_focus;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;
}
    

