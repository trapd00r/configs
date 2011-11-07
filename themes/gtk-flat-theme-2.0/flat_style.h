
#include <gtk/gtkstyle.h>

typedef struct _FlatStyle FlatStyle;
typedef struct _FlatStyleClass FlatStyleClass;

extern GType flat_type_style;

#define FLAT_TYPE_STYLE              flat_type_style
#define FLAT_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FLAT_TYPE_STYLE, FlatStyle))
#define FLAT_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FLAT_TYPE_STYLE, FlatStyleClass))
#define FLAT_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FLAT_TYPE_STYLE))
#define FLAT_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FLAT_TYPE_STYLE))
#define FLAT_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FLAT_TYPE_STYLE, FlatStyleClass))

struct _FlatStyle
{
  GtkStyle parent_instance;
  gboolean is_made;
  GdkPixmap *nw[5];
  GdkPixmap *ne[5];
  GdkPixmap *sw[5];
  GdkPixmap *se[5];
  GdkPixmap *fnw[5];
  GdkPixmap *fne[5];
  GdkPixmap *fsw[5];
  GdkPixmap *fse[5];
  GdkPixmap *radio[5];
  GdkPixmap *radio_on[5];
};

struct _FlatStyleClass
{
  GtkStyleClass parent_class;
};

void flat_style_register_type (GTypeModule *module);
