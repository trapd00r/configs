#ifndef CRUX_COMMON_H
#define CRUX_COMMON_H

typedef enum {
    GRADIENT_NONE = 0,
    GRADIENT_VERTICAL,
    GRADIENT_HORIZONTAL,
} eazel_engine_gradient_direction;

typedef enum {
    EAZEL_ENGINE_CHECK = 0,
    EAZEL_ENGINE_CHECK_FOCUS,
    EAZEL_ENGINE_CHECK_HI,
    EAZEL_ENGINE_CHECK_HI_FOCUS,
    EAZEL_ENGINE_CHECK_PRESSED,
    EAZEL_ENGINE_CHECK_PRESSED_FOCUS,
    EAZEL_ENGINE_CHECK_DISABLED,
    EAZEL_ENGINE_CHECK_ACTIVE,
    EAZEL_ENGINE_CHECK_ACTIVE_FOCUS,
    EAZEL_ENGINE_CHECK_ACTIVE_HI,
    EAZEL_ENGINE_CHECK_ACTIVE_HI_FOCUS,
    EAZEL_ENGINE_CHECK_ACTIVE_PRESSED,
    EAZEL_ENGINE_CHECK_ACTIVE_PRESSED_FOCUS,
    EAZEL_ENGINE_CHECK_ACTIVE_DISABLED,
    EAZEL_ENGINE_OPTION,
    EAZEL_ENGINE_OPTION_FOCUS,
    EAZEL_ENGINE_OPTION_HI,
    EAZEL_ENGINE_OPTION_HI_FOCUS,
    EAZEL_ENGINE_OPTION_PRESSED,
    EAZEL_ENGINE_OPTION_PRESSED_FOCUS,
    EAZEL_ENGINE_OPTION_DISABLED,
    EAZEL_ENGINE_OPTION_ACTIVE,
    EAZEL_ENGINE_OPTION_ACTIVE_FOCUS,
    EAZEL_ENGINE_OPTION_ACTIVE_HI,
    EAZEL_ENGINE_OPTION_ACTIVE_HI_FOCUS,
    EAZEL_ENGINE_OPTION_ACTIVE_PRESSED,
    EAZEL_ENGINE_OPTION_ACTIVE_PRESSED_FOCUS,
    EAZEL_ENGINE_OPTION_ACTIVE_DISABLED,
    EAZEL_ENGINE_H_TROUGH,
    EAZEL_ENGINE_V_TROUGH,
    EAZEL_ENGINE_ARROW_UP,
    EAZEL_ENGINE_ARROW_UP_HI,
    EAZEL_ENGINE_ARROW_UP_ACTIVE,
    EAZEL_ENGINE_ARROW_DOWN,
    EAZEL_ENGINE_ARROW_DOWN_HI,
    EAZEL_ENGINE_ARROW_DOWN_ACTIVE,
    EAZEL_ENGINE_ARROW_RIGHT,
    EAZEL_ENGINE_ARROW_RIGHT_HI,
    EAZEL_ENGINE_ARROW_RIGHT_ACTIVE,
    EAZEL_ENGINE_ARROW_LEFT,
    EAZEL_ENGINE_ARROW_LEFT_HI,
    EAZEL_ENGINE_ARROW_LEFT_ACTIVE,
    EAZEL_ENGINE_H_SCROLLBAR,
    EAZEL_ENGINE_H_SCROLLBAR_HI,
    EAZEL_ENGINE_H_SCROLLBAR_INACTIVE,
    EAZEL_ENGINE_H_SCROLLBAR_THUMB,
    EAZEL_ENGINE_H_SCROLLBAR_THUMB_HI,
    EAZEL_ENGINE_H_SCROLLBAR_THUMB_INACTIVE,
    EAZEL_ENGINE_V_SCROLLBAR,
    EAZEL_ENGINE_V_SCROLLBAR_HI,
    EAZEL_ENGINE_V_SCROLLBAR_INACTIVE,
    EAZEL_ENGINE_V_SCROLLBAR_THUMB,
    EAZEL_ENGINE_V_SCROLLBAR_THUMB_HI,
    EAZEL_ENGINE_V_SCROLLBAR_THUMB_INACTIVE,
    EAZEL_ENGINE_PROGRESS_BAR,
    EAZEL_ENGINE_PROGRESS_BAR_LEFT,
    EAZEL_ENGINE_PROGRESS_BAR_RIGHT,
    EAZEL_ENGINE_PROGRESS_BAR_INACTIVE,
    EAZEL_ENGINE_PROGRESS_TROUGH,
    EAZEL_ENGINE_H_SLIDER_THUMB,
    EAZEL_ENGINE_H_SLIDER_THUMB_INACTIVE,
    EAZEL_ENGINE_H_SLIDER_TROUGH,
    EAZEL_ENGINE_H_SLIDER_TROUGH_ACTIVE,
    EAZEL_ENGINE_V_SLIDER_THUMB,
    EAZEL_ENGINE_V_SLIDER_THUMB_INACTIVE,
    EAZEL_ENGINE_V_SLIDER_TROUGH,
    EAZEL_ENGINE_V_SLIDER_TROUGH_ACTIVE,
    EAZEL_ENGINE_TAB_TOP,
    EAZEL_ENGINE_TAB_TOP_LEFT,
    EAZEL_ENGINE_TAB_TOP_ACTIVE,
    EAZEL_ENGINE_TAB_BOTTOM,
    EAZEL_ENGINE_TAB_BOTTOM_LEFT,
    EAZEL_ENGINE_TAB_BOTTOM_ACTIVE,
    EAZEL_ENGINE_SPIN_ARROW_UP,
    EAZEL_ENGINE_SPIN_ARROW_DOWN,
    EAZEL_ENGINE_STOCK_MAX,
} eazel_engine_stock_image;

typedef struct eazel_engine_gradient_component_struct eazel_engine_gradient_component;
struct eazel_engine_gradient_component_struct {
    GdkColor color;
    float weight;
};

typedef struct {
    guint refcount;
    eazel_engine_gradient_direction direction;
    GdkColor from;
    GSList *components;
} eazel_engine_gradient;

typedef struct pixmap_cache_node_struct eazel_engine_pixmap_cache_node;

typedef struct {
    char *filename;
    int border[4];
    eazel_engine_gradient *recolor;
    GdkPixbuf *pixbuf;
    eazel_engine_pixmap_cache_node *pixmap_first, *pixmap_last;
} eazel_engine_image;

typedef struct {
    int ref_count;
    eazel_engine_image images[EAZEL_ENGINE_STOCK_MAX];
} eazel_engine_stock_table;

#define EAZEL_ENGINE_PALETTE_SIZE 4

/* Information about a single RC style */
typedef struct {
    guint refcount;

    guint thickness;
    guint focus_thickness;
    guint default_thickness;

    guint no_shadow : 1;
    guint inverse_shadow : 1;
    guint outline_shadow : 1;

    GdkColor focus_color;
    GdkColor insensitive_colors[2];	/* inner, outer */

    eazel_engine_gradient *palette[EAZEL_ENGINE_PALETTE_SIZE];

    /* for each GTK widget state */
    eazel_engine_gradient *gradients[5];

    eazel_engine_stock_table *stock;

} eazel_theme_data;

#define DEFAULT_THEME_DATA {			\
  0, 2, 2, 3, FALSE, FALSE, TRUE,		\
  { 0, 0x4a4a, 0x7d7d, 0x8484 },		\
  { { 0, 0x6363, 0x6565, 0x6363 },		\
    { 0, 0xcfcf, 0xd0d0, 0xcfcf } },		\
 }

#endif


