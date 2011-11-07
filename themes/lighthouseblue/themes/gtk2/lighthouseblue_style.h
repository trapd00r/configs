/*
 * Lighthouseblue Theme Engine
 *
 * This is the definition of the main style class that realizes our style
 */
#include <gtk/gtkstyle.h>

typedef struct _LighthouseBlueStyle LighthouseBlueStyle;
typedef struct _LighthouseBlueStyleClass LighthouseBlueStyleClass;

extern GType lighthouseblue_type_style;

#define LIGHTHOUSEBLUE_TYPE_STYLE              lighthouseblue_type_style
#define LIGHTHOUSEBLUE_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), LIGHTHOUSEBLUE_TYPE_STYLE, LighthouseBlueStyle))
#define LIGHTHOUSEBLUE_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), LIGHTHOUSEBLUE_TYPE_STYLE, LighthouseBlueStyleClass))
#define LIGHTHOUSEBLUE_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), LIGHTHOUSEBLUE_TYPE_STYLE))
#define LIGHTHOUSEBLUE_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), LIGHTHOUSEBLUE_TYPE_STYLE))
#define LIGHTHOUSEBLUE_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), LIGHTHOUSEBLUE_TYPE_STYLE, LighthouseBlueStyleClass))

struct _LighthouseBlueStyle
{
  GtkStyle parent_instance;

  GdkColor shade[8];
  GdkGC *shade_gc[8];
};

struct _LighthouseBlueStyleClass
{
  GtkStyleClass parent_class;
};

void lighthouseblue_style_register_type (GTypeModule *module);


