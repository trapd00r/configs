#ifndef _CLEANICE_STYLE_H_
#define _CLEANICE_STYLE_H_

typedef struct _CleanIceStyle CleanIceStyle;
typedef struct _CleanIceStyleClass CleanIceStyleClass;
typedef struct _CleanIceRCStyle CleanIceRCStyle;
typedef struct _CleanIceRCStyleClass CleanIceRCStyleClass;

extern GType cleanice_type_style;
extern GType cleanice_type_rc_style;

#define CLEANICE_TYPE_STYLE              cleanice_type_style
#define CLEANICE_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), CLEANICE_TYPE_STYLE, CleanIceStyle))
#define CLEANICE_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CLEANICE_TYPE_STYLE, CleanIceStyleClass))
#define CLEANICE_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), CLEANICE_TYPE_STYLE))
#define CLEANICE_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CLEANICE_TYPE_STYLE))
#define CLEANICE_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CLEANICE_TYPE_STYLE, CleanIceStyleClass))
#define CLEANICE_TYPE_RC_STYLE              cleanice_type_rc_style
#define CLEANICE_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), CLEANICE_TYPE_RC_STYLE, CleanIceRCStyle))
#define CLEANICE_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), CLEANICE_TYPE_RC_STYLE, CleanIceRCStyleClass))
#define CLEANICE_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), CLEANICE_TYPE_RC_STYLE))
#define CLEANICE_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), CLEANICE_TYPE_RC_STYLE))
#define CLEANICE_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), CLEANICE_TYPE_RC_STYLE, CleanIceRCStyleClass))

struct _CleanIceStyle {
  GtkStyle parent_instance;
};

struct _CleanIceStyleClass {
  GtkStyleClass parent_class;
};

struct _CleanIceRCStyle {
  GtkRcStyle parent_instance;
};

struct _CleanIceRCStyleClass {
  GtkRcStyleClass parent_class;
};

void cleanice_style_register_type (GTypeModule * module);
void cleanice_rc_style_register_type (GTypeModule * module);

#endif
