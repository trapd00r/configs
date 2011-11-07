/* eazel-theme.h -- definitions

   Copyright (C) 2000 Eazel, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   $Id: eazel-theme.h,v 1.1.1.1 2002/01/18 21:39:57 seth Exp $

   Authors: John Harper <jsh@eazel.com>  */

#ifndef EAZEL_THEME_H
#define EAZEL_THEME_H

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#define RANGE_WIDTH 15
#define MIN_THUMB_HEIGHT 24
#define SCALE_HEIGHT 16
#define CHECK_SIZE 10
#define CHECK_SPACING 3


/* parser / per-engine data */

enum {
    TOKEN_THICKNESS = GTK_RC_TOKEN_LAST + 1,
    TOKEN_FOCUS_THICKNESS,
    TOKEN_DEFAULT_THICKNESS,
    TOKEN_FOCUS_COLOR,
    TOKEN_INSENSITIVE_COLORS,
    TOKEN_NONE,
    TOKEN_VERTICAL,
    TOKEN_HORIZONTAL,
    TOKEN_GRADIENT,
    TOKEN_SHADOW,
    TOKEN_INVERSE_SHADOW,
    TOKEN_OUTLINE_SHADOW,
    TOKEN_YES,
    TOKEN_NO,
    TOKEN_STOCK,
    TOKEN_BORDER,
    TOKEN_RECOLOR,
    TOKEN_PALETTE,
    TOKEN_IMAGE,
    TOKEN_FG,
    TOKEN_BG,
    TOKEN_BASE,
    TOKEN_TEXT,
};

#define THEME_SYMBOLS						\
  { "thickness", TOKEN_THICKNESS }, 				\
  { "focus_thickness", TOKEN_FOCUS_THICKNESS },			\
  { "default_thickness", TOKEN_DEFAULT_THICKNESS },		\
  { "focus_color", TOKEN_FOCUS_COLOR },				\
  { "insensitive_colors", TOKEN_INSENSITIVE_COLORS },		\
  { "none", TOKEN_NONE },					\
  { "vertical", TOKEN_VERTICAL },				\
  { "horizontal", TOKEN_HORIZONTAL },				\
  { "gradient", TOKEN_GRADIENT },				\
  { "shadow", TOKEN_SHADOW },					\
  { "inverse_shadow", TOKEN_INVERSE_SHADOW },			\
  { "outline_shadow", TOKEN_OUTLINE_SHADOW },			\
  { "yes", TOKEN_YES },						\
  { "no", TOKEN_NO },						\
  { "stock", TOKEN_STOCK },					\
  { "border", TOKEN_BORDER },					\
  { "recolor", TOKEN_RECOLOR },					\
  { "palette", TOKEN_PALETTE },					\
  { "image", TOKEN_IMAGE },					\
  { "fg", TOKEN_FG },						\
  { "bg", TOKEN_BG },						\
  { "base", TOKEN_BASE },					\
  { "text", TOKEN_TEXT },					\
  { 0, G_TOKEN_NONE }

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

#define STOCK_SYMBOLS 									\
    { "CHECK", EAZEL_ENGINE_CHECK },							\
    { "CHECK_FOCUS", EAZEL_ENGINE_CHECK_FOCUS },					\
    { "CHECK_HI", EAZEL_ENGINE_CHECK_HI },						\
    { "CHECK_HI_FOCUS", EAZEL_ENGINE_CHECK_HI_FOCUS },					\
    { "CHECK_PRESSED", EAZEL_ENGINE_CHECK_PRESSED },					\
    { "CHECK_PRESSED_FOCUS", EAZEL_ENGINE_CHECK_PRESSED_FOCUS },			\
    { "CHECK_DISABLED", EAZEL_ENGINE_CHECK_DISABLED },					\
    { "CHECK_ACTIVE", EAZEL_ENGINE_CHECK_ACTIVE },					\
    { "CHECK_ACTIVE_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_FOCUS },				\
    { "CHECK_ACTIVE_HI", EAZEL_ENGINE_CHECK_ACTIVE_HI },				\
    { "CHECK_ACTIVE_HI_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_HI_FOCUS },			\
    { "CHECK_ACTIVE_PRESSED", EAZEL_ENGINE_CHECK_ACTIVE_PRESSED },			\
    { "CHECK_ACTIVE_PRESSED_FOCUS", EAZEL_ENGINE_CHECK_ACTIVE_PRESSED_FOCUS },		\
    { "CHECK_ACTIVE_DISABLED", EAZEL_ENGINE_CHECK_ACTIVE_DISABLED },			\
    { "OPTION", EAZEL_ENGINE_OPTION },							\
    { "OPTION_FOCUS", EAZEL_ENGINE_OPTION_FOCUS },					\
    { "OPTION_HI", EAZEL_ENGINE_OPTION_HI },						\
    { "OPTION_HI_FOCUS", EAZEL_ENGINE_OPTION_HI_FOCUS },				\
    { "OPTION_PRESSED", EAZEL_ENGINE_OPTION_PRESSED },					\
    { "OPTION_PRESSED_FOCUS", EAZEL_ENGINE_OPTION_PRESSED_FOCUS },			\
    { "OPTION_DISABLED", EAZEL_ENGINE_OPTION_DISABLED },				\
    { "OPTION_ACTIVE", EAZEL_ENGINE_OPTION_ACTIVE },					\
    { "OPTION_ACTIVE_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_FOCUS },			\
    { "OPTION_ACTIVE_HI", EAZEL_ENGINE_OPTION_ACTIVE_HI },				\
    { "OPTION_ACTIVE_HI_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_HI_FOCUS },			\
    { "OPTION_ACTIVE_PRESSED", EAZEL_ENGINE_OPTION_ACTIVE_PRESSED },			\
    { "OPTION_ACTIVE_PRESSED_FOCUS", EAZEL_ENGINE_OPTION_ACTIVE_PRESSED_FOCUS },	\
    { "OPTION_ACTIVE_DISABLED", EAZEL_ENGINE_OPTION_ACTIVE_DISABLED },			\
    { "H_TROUGH", EAZEL_ENGINE_H_TROUGH },						\
    { "V_TROUGH", EAZEL_ENGINE_V_TROUGH },						\
    { "ARROW_UP", EAZEL_ENGINE_ARROW_UP },						\
    { "ARROW_UP_HI", EAZEL_ENGINE_ARROW_UP_HI },					\
    { "ARROW_UP_ACTIVE", EAZEL_ENGINE_ARROW_UP_ACTIVE },				\
    { "ARROW_DOWN", EAZEL_ENGINE_ARROW_DOWN },						\
    { "ARROW_DOWN_HI", EAZEL_ENGINE_ARROW_DOWN_HI },					\
    { "ARROW_DOWN_ACTIVE", EAZEL_ENGINE_ARROW_DOWN_ACTIVE },				\
    { "ARROW_RIGHT", EAZEL_ENGINE_ARROW_RIGHT },					\
    { "ARROW_RIGHT_HI", EAZEL_ENGINE_ARROW_RIGHT_HI },					\
    { "ARROW_RIGHT_ACTIVE", EAZEL_ENGINE_ARROW_RIGHT_ACTIVE },				\
    { "ARROW_LEFT", EAZEL_ENGINE_ARROW_LEFT },						\
    { "ARROW_LEFT_HI", EAZEL_ENGINE_ARROW_LEFT_HI },					\
    { "ARROW_LEFT_ACTIVE", EAZEL_ENGINE_ARROW_LEFT_ACTIVE },				\
    { "H_SCROLLBAR", EAZEL_ENGINE_H_SCROLLBAR },					\
    { "H_SCROLLBAR_HI", EAZEL_ENGINE_H_SCROLLBAR_HI },					\
    { "H_SCROLLBAR_INACTIVE", EAZEL_ENGINE_H_SCROLLBAR_INACTIVE },			\
    { "H_SCROLLBAR_THUMB", EAZEL_ENGINE_H_SCROLLBAR_THUMB },				\
    { "H_SCROLLBAR_THUMB_HI", EAZEL_ENGINE_H_SCROLLBAR_THUMB_HI },			\
    { "H_SCROLLBAR_THUMB_INACTIVE", EAZEL_ENGINE_H_SCROLLBAR_THUMB_INACTIVE },		\
    { "V_SCROLLBAR", EAZEL_ENGINE_V_SCROLLBAR },					\
    { "V_SCROLLBAR_HI", EAZEL_ENGINE_V_SCROLLBAR_HI },					\
    { "V_SCROLLBAR_INACTIVE", EAZEL_ENGINE_V_SCROLLBAR_INACTIVE },			\
    { "V_SCROLLBAR_THUMB", EAZEL_ENGINE_V_SCROLLBAR_THUMB },				\
    { "V_SCROLLBAR_THUMB_HI", EAZEL_ENGINE_V_SCROLLBAR_THUMB_HI },			\
    { "V_SCROLLBAR_THUMB_INACTIVE", EAZEL_ENGINE_V_SCROLLBAR_THUMB_INACTIVE },		\
    { "PROGRESS_BAR", EAZEL_ENGINE_PROGRESS_BAR },					\
    { "PROGRESS_BAR_LEFT", EAZEL_ENGINE_PROGRESS_BAR_LEFT },				\
    { "PROGRESS_BAR_RIGHT", EAZEL_ENGINE_PROGRESS_BAR_RIGHT },				\
    { "PROGRESS_BAR_INACTIVE", EAZEL_ENGINE_PROGRESS_BAR_INACTIVE },			\
    { "PROGRESS_TROUGH", EAZEL_ENGINE_PROGRESS_TROUGH },				\
    { "H_SLIDER_THUMB", EAZEL_ENGINE_H_SLIDER_THUMB },					\
    { "H_SLIDER_THUMB_INACTIVE", EAZEL_ENGINE_H_SLIDER_THUMB_INACTIVE },		\
    { "H_SLIDER_TROUGH", EAZEL_ENGINE_H_SLIDER_TROUGH },				\
    { "H_SLIDER_TROUGH_ACTIVE", EAZEL_ENGINE_H_SLIDER_TROUGH_ACTIVE },			\
    { "V_SLIDER_THUMB", EAZEL_ENGINE_V_SLIDER_THUMB },					\
    { "V_SLIDER_THUMB_INACTIVE", EAZEL_ENGINE_V_SLIDER_THUMB_INACTIVE },		\
    { "V_SLIDER_TROUGH", EAZEL_ENGINE_V_SLIDER_TROUGH },				\
    { "V_SLIDER_TROUGH_ACTIVE", EAZEL_ENGINE_V_SLIDER_TROUGH_ACTIVE },			\
    { "TAB_TOP", EAZEL_ENGINE_TAB_TOP },						\
    { "TAB_TOP_LEFT", EAZEL_ENGINE_TAB_TOP_LEFT },					\
    { "TAB_TOP_ACTIVE", EAZEL_ENGINE_TAB_TOP_ACTIVE },					\
    { "TAB_BOTTOM", EAZEL_ENGINE_TAB_BOTTOM },						\
    { "TAB_BOTTOM_LEFT", EAZEL_ENGINE_TAB_BOTTOM_LEFT },				\
    { "TAB_BOTTOM_ACTIVE", EAZEL_ENGINE_TAB_BOTTOM_ACTIVE },				\
    { "SPIN_ARROW_UP", EAZEL_ENGINE_SPIN_ARROW_UP },					\
    { "SPIN_ARROW_DOWN", EAZEL_ENGINE_SPIN_ARROW_DOWN },				\
    { 0, 0 }

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

#define STYLE_THEME_DATA(s) ((eazel_theme_data *) ((s)->engine_data))


/* prototypes */

/* from eazel-theme-main.c */
extern gboolean eazel_engine_widget_in_focused_window_p (GtkWidget *widget);
extern void theme_init (GtkThemeEngine *engine);
extern void theme_exit (void);

/* from eazel-theme-draw.c */
extern GtkStyleClass eazel_class_0, eazel_class_1, eazel_class_2, eazel_class_3;

/* from eazel-theme-gradient.c */
extern eazel_engine_gradient *eazel_engine_gradient_new (eazel_engine_gradient_direction direction,
							 GdkColor *from,
							 GSList *components);
extern eazel_engine_gradient *eazel_engine_gradient_ref (eazel_engine_gradient *g);
extern void eazel_engine_gradient_unref (eazel_engine_gradient *g);
extern eazel_engine_gradient *eazel_engine_make_two_point_gradient (eazel_engine_gradient_direction direction,
								    gulong from_rgb,
								    gulong to_rgb);

extern void eazel_engine_fill_gradient_rgb_buffer (const eazel_engine_gradient *gradient,
						   int rgb_total, guchar *rgb_buf,
						   int rgb_first, int rgb_last);

extern void eazel_engine_draw_gradient (GdkDrawable *drawable,
					GdkGC *gc,
					const GdkRectangle *full_rect,
					const GdkRectangle *clip_rect,
					const eazel_engine_gradient *gradient);

extern void eazel_engine_set_bg_gradient (GdkWindow *window,
					  eazel_engine_gradient *gradient);

/* from eazel-theme-shadow.c */
extern void eazel_engine_draw_shadow (GtkStyle *style,
				      GdkWindow *window,
				      GtkStateType state_type,
				      GtkShadowType shadow_type,
				      GdkRectangle *area,
				      GtkWidget *widget,
				      gchar *detail,
				      gint x, gint y, gint width, gint height);

/* from eazel-theme-pixmaps.c */
extern void eazel_engine_stock_table_unref (eazel_engine_stock_table *table);
extern eazel_engine_stock_table *eazel_engine_stock_table_ref (eazel_engine_stock_table *table);
extern void eazel_engine_stock_pixmap_and_mask (eazel_engine_stock_table *table,
						eazel_engine_stock_image type,
						GdkPixmap **image,
						GdkBitmap **mask);
extern void eazel_engine_stock_pixmap_and_mask_scaled (eazel_engine_stock_table *table,
						       eazel_engine_stock_image type,
						       int width, int height,
						       GdkPixmap **image,
						       GdkBitmap **mask);
extern void eazel_engine_stock_free_pixmaps (eazel_engine_stock_table *table,
					     eazel_engine_stock_image type,
					     GdkPixmap *image, GdkPixmap *mask);
extern void eazel_engine_stock_get_size (eazel_engine_stock_table *table,
					 eazel_engine_stock_image type,
					 int *width, int *height);

/* from eazel-theme-hacks.c */
extern void eazel_engine_install_hacks (void);
extern void eazel_engine_remove_hacks (void);

#endif /* EAZEL_THEME_H */
