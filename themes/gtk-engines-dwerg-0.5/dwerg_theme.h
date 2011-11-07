#include <gtk/gtk.h>
#include <gmodule.h>

/* Default stuff */
#define DEFAULT_SCROLLSHAPE       SCROLL_SHAPED
#define DEFAULT_SCROLLBARMARKS    MARKS_ON
#define DEFAULT_SCROLLBUTTONMARKS MARKS_ON
#define DEFAULT_HANDLEBOXMARKS    MARKS_ON

#define DEFAULT_SLIDER_WIDTH      11
#define DEFAULT_MIN_SLIDER_SIZE   9

typedef struct {
	gint scrollbar_type;
	gint scrollbar_marks;
	gint scroll_button_marks;
	gint handlebox_marks;
	gboolean draw_button_focus;
	gboolean black_and_white;
	gboolean flat_arrows;
	gboolean flat_progress;
	gboolean flat_tooltips;
	gboolean small_menu_arrows;
	gboolean small_radio_buttons;
	gfloat lightness_multiplier;
	gfloat darkness_multiplier;
} ThemeRcData;

typedef struct {
	gint scrollbar_type;
	gint scrollbar_marks;
	gint scroll_button_marks;
	gint handlebox_marks;
	gboolean draw_button_focus;
	gboolean black_and_white;
	gboolean flat_arrows;
	gboolean flat_progress;
	gboolean flat_tooltips;
	gboolean small_menu_arrows;
	gboolean small_radio_buttons;
	gfloat lightness_multiplier;
	gfloat darkness_multiplier;
} ThemeStyleData;

enum {
	TOKEN_RECTSCROLLBAR = G_TOKEN_LAST + 1,
	TOKEN_SCROLLBARMARKS,
	TOKEN_SCROLLBUTTONMARKS,
	TOKEN_HANDLEBOXMARKS,
	TOKEN_TRUE,
	TOKEN_FALSE
};

enum {
	SCROLL_SHAPED = 0,
	SCROLL_RECT,
	MARKS_ON = 0,
	MARKS_OFF
};
