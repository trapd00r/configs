#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <gtk/gtkrc.h>

typedef struct _XfceRcStyle XfceRcStyle;
typedef struct _XfceRcStyleClass XfceRcStyleClass;

extern GType xfce_type_rc_style;

#define XFCE_TYPE_RC_STYLE              xfce_type_rc_style
#define XFCE_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), XFCE_TYPE_RC_STYLE, XfceRcStyle))
#define XFCE_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_RC_STYLE, XfceRcStyleClass))
#define XFCE_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), XFCE_TYPE_RC_STYLE))
#define XFCE_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), XFCE_TYPE_RC_STYLE))
#define XFCE_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), XFCE_TYPE_RC_STYLE, XfceRcStyleClass))

typedef enum
{
    XFCE_RC_GRADIENT_HORIZONTAL,
    XFCE_RC_GRADIENT_VERTICAL,
    XFCE_RC_GRADIENT_NORTHERN_DIAGONAL,
    XFCE_RC_GRADIENT_SOUTHERN_DIAGONAL,
    XFCE_RC_GRADIENT_AUTO
} XfceRcGradientType;

struct _XfceRcStyle
{
    GtkRcStyle parent_instance;

    gboolean smooth_edge;
    gboolean gradient;
    XfceRcGradientType gradient_type;
    gfloat shade_start;
    gfloat shade_end;
};

struct _XfceRcStyleClass
{
    GtkRcStyleClass parent_class;
};

void xfce_rc_style_register_type(GTypeModule * module);

enum
{
    TOKEN_SMOOTHEDGE = G_TOKEN_LAST + 1,
    TOKEN_BOXFILL,
    TOKEN_FILL_STYLE,
    TOKEN_GRADIENT,
    TOKEN_PLAIN,
    TOKEN_ORIENTATION,
    TOKEN_AUTO,
    TOKEN_HORIZONTAL,
    TOKEN_VERTICAL,
    TOKEN_NORTHERN_DIAGONAL,
    TOKEN_SOUTHERN_DIAGONAL,
    TOKEN_SHADE_START,
    TOKEN_SHADE_END,
    TOKEN_TRUE,
    TOKEN_FALSE
};
