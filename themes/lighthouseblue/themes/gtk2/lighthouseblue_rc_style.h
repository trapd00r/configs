#include <gtk/gtkrc.h>

typedef struct _LighthouseBlueRcStyle LighthouseBlueRcStyle;
typedef struct _LighthouseBlueRcStyleClass LighthouseBlueRcStyleClass;

extern GType lighthouseblue_type_rc_style;

#define LIGHTHOUSEBLUE_TYPE_RC_STYLE              lighthouseblue_type_rc_style
#define LIGHTHOUSEBLUE_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), LIGHTHOUSEBLUE_TYPE_RC_STYLE, LighthouseBlueRcStyle))
#define LIGHTHOUSEBLUE_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), LIGHTHOUSEBLUE_TYPE_RC_STYLE, LighthouseBlueRcStyleClass))
#define LIGHTHOUSEBLUE_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), LIGHTHOUSEBLUE_TYPE_RC_STYLE))
#define LIGHTHOUSEBLUE_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), LIGHTHOUSEBLUE_TYPE_RC_STYLE))
#define LIGHTHOUSEBLUE_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), LIGHTHOUSEBLUE_TYPE_RC_STYLE, LighthouseBlueRcStyleClass))

struct _LighthouseBlueRcStyle
{
  GtkRcStyle parent_instance;

  gboolean has_notebook_patch;
  gboolean combine_treeview_select;
};

struct _LighthouseBlueRcStyleClass
{
  GtkRcStyleClass parent_class;
};

void lighthouseblue_rc_style_register_type (GTypeModule *module);

