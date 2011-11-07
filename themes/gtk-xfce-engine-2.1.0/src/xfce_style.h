#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtkstyle.h>

typedef struct _XfceStyle XfceStyle;
typedef struct _XfceStyleClass XfceStyleClass;

extern GType xfce_type_style;

#define XFCE_TYPE_STYLE              xfce_type_style
#define XFCE_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), XFCE_TYPE_STYLE, XfceStyle))
#define XFCE_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_STYLE, XfceStyleClass))
#define XFCE_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), XFCE_TYPE_STYLE))
#define XFCE_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), XFCE_TYPE_STYLE))
#define XFCE_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), XFCE_TYPE_STYLE, XfceStyleClass))

struct _XfceStyle
{
    GtkStyle parent_instance;
};

struct _XfceStyleClass
{
    GtkStyleClass parent_class;
};

void xfce_style_register_type(GTypeModule * module);
