#include <gtk/gtkstyle.h>

typedef struct _MistStyle MistStyle;
typedef struct _MistStyleClass MistStyleClass;

extern GType mist_type_style;

#define MIST_TYPE_STYLE              mist_type_style
#define MIST_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), MIST_TYPE_STYLE, MistStyle))
#define MIST_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), MIST_TYPE_STYLE, MistStyleClass))
#define MIST_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), MIST_TYPE_STYLE))
#define MIST_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), MIST_TYPE_STYLE))
#define MIST_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), MIST_TYPE_STYLE, MistStyleClass))

struct _MistStyle
{
  GtkStyle parent_instance;
};

struct _MistStyleClass
{
  GtkStyleClass parent_class;
};

void mist_style_register_type (GTypeModule *module);


