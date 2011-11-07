#include <gtk/gtkstyle.h>

typedef struct _DwergStyle DwergStyle;
typedef struct _DwergStyleClass DwergStyleClass;

extern GType dwerg_type_style;

#define DWERG_TYPE_STYLE              dwerg_type_style
#define DWERG_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), DWERG_TYPE_STYLE, DwergStyle))
#define DWERG_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), DWERG_TYPE_STYLE, DwergStyleClass))
#define DWERG_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), DWERG_TYPE_STYLE))
#define DWERG_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), DWERG_TYPE_STYLE))
#define DWERG_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), DWERG_TYPE_STYLE, DwergStyleClass))

struct _DwergStyle {
	GtkStyle parent_instance;
};

struct _DwergStyleClass {
	GtkStyleClass parent_class;
};

void dwerg_style_register_type (GTypeModule * module);
