#include <gtk/gtkrc.h>

typedef struct _ThiniceRcStyle ThiniceRcStyle;
typedef struct _ThiniceRcStyleClass ThiniceRcStyleClass;

extern GType thinice_type_rc_style;

#define THINICE_TYPE_RC_STYLE              thinice_type_rc_style
#define THINICE_RC_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), THINICE_TYPE_RC_STYLE, ThiniceRcStyle))
#define THINICE_RC_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), THINICE_TYPE_RC_STYLE, ThiniceRcStyleClass))
#define THINICE_IS_RC_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), THINICE_TYPE_RC_STYLE))
#define THINICE_IS_RC_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), THINICE_TYPE_RC_STYLE))
#define THINICE_RC_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), THINICE_TYPE_RC_STYLE, ThiniceRcStyleClass))

struct _ThiniceRcStyle
{
  GtkRcStyle parent_instance;

  guint scrollbar_type:1;
  guint scrollbar_marks:1;
  guint scroll_button_marks:1;
  guint handlebox_marks:1;
  guint mark_type1;
  guint mark_type2;
  guint paned_dots;
};

struct _ThiniceRcStyleClass
{
  GtkRcStyleClass parent_class;
};

void thinice_rc_style_register_type (GTypeModule *module);

/* Default stuff */
#define DEFAULT_SCROLLSHAPE       SCROLL_SHAPED
#define DEFAULT_SCROLLBARMARKS    MARKS_ON 
#define DEFAULT_SCROLLBUTTONMARKS MARKS_ON
#define DEFAULT_HANDLEBOXMARKS    MARKS_ON
#define DEFAULT_MARKTYPE1         MARKS_SLASH
#define DEFAULT_MARKTYPE2         MARKS_INVSLASH
#define DEFAULT_PANEDDOTS         PANED_DOTSFULL

#define DEFAULT_SCROLLTHUMB_SIZE  12
#define DEFAULT_MIN_SLIDER_SIZE   9
#define SMALLEST_HANDLE           17

enum
  {
    TOKEN_RECTSCROLLBAR = G_TOKEN_LAST + 1,
    TOKEN_SCROLLBARMARKS,
    TOKEN_SCROLLBUTTONMARKS,
    TOKEN_HANDLEBOXMARKS,
    TOKEN_MARKTYPE1,
    TOKEN_MARKTYPE2,
    TOKEN_PANEDDOTS,

    TOKEN_TRUE,
    TOKEN_FALSE,

    TOKEN_NOTHING,
    TOKEN_SLASH,
    TOKEN_INVSLASH,
    TOKEN_DOT,
    TOKEN_INVDOT,
    TOKEN_ARROW,

    TOKEN_FULL,
    TOKEN_SOME,
    TOKEN_NONE
  };
  
enum
  {
    SCROLL_RECT = 0,
    SCROLL_SHAPED = 1,

    MARKS_OFF = 0,
    MARKS_ON = 1,

    MARKS_NOTHING = 0,
    MARKS_SLASH = 1,
    MARKS_INVSLASH = 2,
    MARKS_DOT = 3,
    MARKS_INVDOT = 4,
    MARKS_ARROW = 5,

    PANED_DOTSFULL = 0,
    PANED_DOTSSOME = 1,
    PANED_DOTSNONE = 2
  };

