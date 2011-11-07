#include <gtk/gtkstyle.h>

typedef struct _ThiniceStyle ThiniceStyle;
typedef struct _ThiniceStyleClass ThiniceStyleClass;

extern GType thinice_type_style;

#define THINICE_TYPE_STYLE              thinice_type_style
#define THINICE_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), THINICE_TYPE_STYLE, ThiniceStyle))
#define THINICE_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), THINICE_TYPE_STYLE, ThiniceStyleClass))
#define THINICE_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), THINICE_TYPE_STYLE))
#define THINICE_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), THINICE_TYPE_STYLE))
#define THINICE_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), THINICE_TYPE_STYLE, ThiniceStyleClass))

struct _ThiniceStyle
{
  GtkStyle parent_instance;
};

struct _ThiniceStyleClass
{
  GtkStyleClass parent_class;
};

void thinice_style_register_type (GTypeModule *module);


