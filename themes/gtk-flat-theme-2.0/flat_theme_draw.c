/* gtk-flat-theme - A gtk+ theme engine.
   Copyright (C) 2000  Mark Slicker <jamess1@wwnet.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <math.h>
#include <gtk/gtk.h>

#include "flat_rc_style.h"
#include "flat_style.h"

#define DETAIL(xx)   ((detail) && (!strcmp(xx, detail)))

/* internal functions */

static void flat_style_init (FlatStyle *style);

static void flat_style_class_init (FlatStyleClass *klass);

static void         draw_hline(GtkStyle * style,
			       GdkWindow * window,
			       GtkStateType state_type,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       gint x1,
			       gint x2,
			       gint y);
static void         draw_vline(GtkStyle * style,
			       GdkWindow * window,
			       GtkStateType state_type,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       gint y1,
			       gint y2,
			       gint x);
static void         draw_shadow(GtkStyle * style,
				GdkWindow * window,
				GtkStateType state_type,
				GtkShadowType shadow_type,
				GdkRectangle * area,
				GtkWidget * widget,
				const gchar * detail,
				gint x,
				gint y,
				gint width,
				gint height);

static void         draw_polygon(GtkStyle * style,
				 GdkWindow * window,
				 GtkStateType state_type,
				 GtkShadowType shadow_type,
				 GdkRectangle * area,
				 GtkWidget * widget,
				 const gchar * detail,
				 GdkPoint * point,
				 gint npoints,
				 gint fill);
static void         draw_arrow(GtkStyle * style,
			       GdkWindow * window,
			       GtkStateType state_type,
			       GtkShadowType shadow_type,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       GtkArrowType arrow_type,
			       gint fill,
			       gint x,
			       gint y,
			       gint width,
			       gint height);
static void         draw_diamond(GtkStyle * style,
				 GdkWindow * window,
				 GtkStateType state_type,
				 GtkShadowType shadow_type,
				 GdkRectangle * area,
				 GtkWidget * widget,
				 const gchar * detail,
				 gint x,
				 gint y,
				 gint width,
				 gint height);
static void         draw_oval(GtkStyle * style,
			      GdkWindow * window,
			      GtkStateType state_type,
			      GtkShadowType shadow_type,
			      GdkRectangle * area,
			      GtkWidget * widget,
			      const gchar * detail,
			      gint x,
			      gint y,
			      gint width,
			      gint height);
static void         draw_string(GtkStyle * style,
				GdkWindow * window,
				GtkStateType state_type,
				GdkRectangle * area,
				GtkWidget * widget,
				const gchar * detail,
				gint x,
				gint y,
				const gchar * string);
static void         draw_box(GtkStyle * style,
			     GdkWindow * window,
			     GtkStateType state_type,
			     GtkShadowType shadow_type,
			     GdkRectangle * area,
			     GtkWidget * widget,
			     const gchar * detail,
			     gint x,
			     gint y,
			     gint width,
			     gint height);
static void         draw_flat_box(GtkStyle * style,
				  GdkWindow * window,
				  GtkStateType state_type,
				  GtkShadowType shadow_type,
				  GdkRectangle * area,
				  GtkWidget * widget,
				  const gchar * detail,
				  gint x,
				  gint y,
				  gint width,
				  gint height);
static void         draw_check(GtkStyle * style,
			       GdkWindow * window,
			       GtkStateType state_type,
			       GtkShadowType shadow_type,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       gint x,
			       gint y,
			       gint width,
			       gint height);
static void         draw_option(GtkStyle * style,
				GdkWindow * window,
				GtkStateType state_type,
				GtkShadowType shadow_type,
				GdkRectangle * area,
				GtkWidget * widget,
				const gchar * detail,
				gint x,
				gint y,
				gint width,
				gint height);
static void         draw_cross(GtkStyle * style,
			       GdkWindow * window,
			       GtkStateType state_type,
			       GtkShadowType shadow_type,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       gint x,
			       gint y,
			       gint width,
			       gint height);
static void         draw_ramp(GtkStyle * style,
			      GdkWindow * window,
			      GtkStateType state_type,
			      GtkShadowType shadow_type,
			      GdkRectangle * area,
			      GtkWidget * widget,
			      const gchar * detail,
			      GtkArrowType arrow_type,
			      gint x,
			      gint y,
			      gint width,
			      gint height);
static void         draw_tab(GtkStyle * style,
			     GdkWindow * window,
			     GtkStateType state_type,
			     GtkShadowType shadow_type,
			     GdkRectangle * area,
			     GtkWidget * widget,
			     const gchar * detail,
			     gint x,
			     gint y,
			     gint width,
			     gint height);
static void         draw_shadow_gap(GtkStyle * style,
				    GdkWindow * window,
				    GtkStateType state_type,
				    GtkShadowType shadow_type,
				    GdkRectangle * area,
				    GtkWidget * widget,
				    const gchar * detail,
				    gint x,
				    gint y,
				    gint width,
				    gint height,
				    GtkPositionType gap_side,
				    gint gap_x,
				    gint gap_width);
static void         draw_box_gap(GtkStyle * style,
				 GdkWindow * window,
				 GtkStateType state_type,
				 GtkShadowType shadow_type,
				 GdkRectangle * area,
				 GtkWidget * widget,
				 const gchar * detail,
				 gint x,
				 gint y,
				 gint width,
				 gint height,
				 GtkPositionType gap_side,
				 gint gap_x,
				 gint gap_width);
static void         draw_extension(GtkStyle * style,
				   GdkWindow * window,
				   GtkStateType state_type,
				   GtkShadowType shadow_type,
				   GdkRectangle * area,
				   GtkWidget * widget,
				   const gchar * detail,
				   gint x,
				   gint y,
				   gint width,
				   gint height,
				   GtkPositionType gap_side);
static void         draw_focus(GtkStyle * style,
			       GdkWindow * window,
			       GdkRectangle * area,
			       GtkWidget * widget,
			       const gchar * detail,
			       gint x,
			       gint y,
			       gint width,
			       gint height);
static void         draw_slider(GtkStyle * style,
				GdkWindow * window,
				GtkStateType state_type,
				GtkShadowType shadow_type,
				GdkRectangle * area,
				GtkWidget * widget,
				const gchar * detail,
				gint x,
				gint y,
				gint width,
				gint height,
				GtkOrientation orientation);
static void         draw_handle(GtkStyle * style,
				GdkWindow * window,
				GtkStateType state_type,
				GtkShadowType shadow_type,
				GdkRectangle * area,
				GtkWidget * widget,
				const gchar * detail,
				gint x,
				gint y,
				gint width,
				gint height,
				GtkOrientation orientation);

static void
flat_button(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height);


static GtkStyleClass *parent_class = NULL;
GType flat_type_style = 0;

void
flat_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (FlatStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) flat_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (FlatStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) flat_style_init,
  };
  
  flat_type_style = g_type_module_register_type (module,
						    GTK_TYPE_STYLE,
						    "FlatStyle",
						    &object_info, 0);
}

static void
fill_color (GdkColor *color, GdkColormap *cmap)
{
  GdkVisual *visual = gdk_colormap_get_visual (cmap);
  gulong pixel = color->pixel;

  switch (visual->type) {
  case GDK_VISUAL_STATIC_GRAY:
  case GDK_VISUAL_GRAYSCALE:
  case GDK_VISUAL_STATIC_COLOR:
  case GDK_VISUAL_PSEUDO_COLOR:
    color->red = cmap->colors[pixel].red;
    color->green = cmap->colors[pixel].green;
    color->blue = cmap->colors[pixel].blue;
    break;
  case GDK_VISUAL_TRUE_COLOR:
  case GDK_VISUAL_DIRECT_COLOR:
    color->red = (pixel & visual->red_mask) >> visual->red_shift << (16 - visual->red_prec);
    color->green = (pixel & visual->green_mask) >> visual->green_shift << (16 - visual->green_prec);
    color->blue = (pixel & visual->blue_mask) >> visual->blue_shift << (16 - visual->blue_prec);
    break;
  }
}

static void
blend_images (GdkImage *c, GdkImage *a, GdkImage *b, float *bias_array,
              int width, int height, GdkColormap *cmap)
{
  int x, y;
  GdkColor ca, cb, cc;

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      float bias = bias_array[y*height+x];
      ca.pixel = gdk_image_get_pixel (a, x, y);
      cb.pixel = gdk_image_get_pixel (b, x, y);
      fill_color (&ca, cmap);
      fill_color (&cb, cmap);
      cc.red = (gushort)(ca.red * (1.0f - bias) + cb.red * bias);
      cc.green = (gushort)(ca.green * (1.0f - bias) + cb.green * bias);
      cc.blue = (gushort)(ca.blue * (1.0f - bias) + cb.blue * bias);
      gdk_color_alloc (cmap, &cc);
      gdk_image_put_pixel (c, x, y, cc.pixel); 
    }
  }
}

static void
copy_image (GdkImage *b, GdkImage *a, int xsrc, int ysrc,
            int xdest, int ydest, int width, int height)
{
  int x, y;
  gulong pixel;

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      pixel = gdk_image_get_pixel (a, xsrc+x, ysrc+y);
      gdk_image_put_pixel (b, xdest+x, xdest+y, pixel); 
    }
  }
}

static void
set_image_color (GdkImage *a, GdkColor *c, int width, int height)
{
  int x, y;
  gulong pixel = c->pixel;

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      gdk_image_put_pixel (a, x, y, pixel); 
    }
  }
}

static float corner_bias_a[4][4][4] = {
  {{          0, .196078431f, .690106078f, .960784314f},
   {.196078431f, .960784314f,           0,           0},
   {.690106078f,           0,           0,           0},
   {.960784314f,           0,           0,           0}},
  {0},
  {0},
  {0}
};

static float corner_bias_b[4][4][4] = {
  {{0,           0,           0,          0},
   {0,           0, .415686275f, .050980392},
   {0, .415686275f,           0,          0},
   {0, .050980392f,           0,          0}},
  {0},
  {0},
  {0}
};

static float corner_bias_c[4][4][4] = {
  {{0,    0,    0,    0},
   {0,    0, 1.0f, 1.0f},
   {0, 1.0f, 1.0f, 1.0f},
   {0, 1.0f, 1.0f, 1.0f}},
  {0},
  {0},
  {0}
};

static float focused_corner_bias_a[4][4][4] = {
  {{.960784314f, 0, 0, 0},
   {0}, {0}, {0}},
  {0}, {0}, {0}
};

static float focused_corner_bias_b[4][4][4] = {
  {{   0,        1.0f,        1.0f, 1.0f},
   {1.0f, .623529412f, .082352941f,    0},
   {1.0f, .082352941f,           0,    0},
   {1.0f,           0,           0,    0}},
  {0}, {0}, {0}
};

static float focused_corner_bias_c[4][4][4] = {
  {{0,    1.0f, 1.0f, 1.0f},
   {1.0f, 1.0f, 1.0f, 1.0f},
   {1.0f, 1.0f, 1.0f, 1.0f},
   {1.0f, 1.0f, 1.0f, 1.0f}},
  {0}, {0}, {0}
};

static float radio_bias[12][12] = {
  {0, 0, 0, .454901961f, .796078431f, .976470588f, 0, 0, 0, 0, 0, 0},
  {0, .133333333f, .796078431f, .650980392f, .247058824f, .031372549, 0, 0, 0, 0, 0, 0},
  {0, .796078431f, .450980392f, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {.454901961f, .650980392f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {.796078431f, .247058824f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {.976470588f, .031372549f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0}, {0}, {0}, {0}, {0}
};

static float radio_on_bias[12][12] = {
  {0},
  {0},
  {0},
  {0, 0, 0, 0, .584213725f, .949019608f, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, .584213725f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, .949019608f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 0},
  {0}, {0}, {0}, {0}, {0}
};

#define flip(b, a, l, x, y)			\
do {						\
  for (i = 0; i < l; i++)			\
    for (j = 0; j < l; j++)			\
      b[i][j] = a[y?l-i-1:i][x?l-j-1:j];	\
} while (0)

static void
init ()
{
  int i, j;

  /* make the other corner biases */
  flip (corner_bias_a[1], corner_bias_a[0], 4, 0, 1);
  flip (corner_bias_a[2], corner_bias_a[0], 4, 1, 0);
  flip (corner_bias_a[3], corner_bias_a[0], 4, 1, 1);
  flip (corner_bias_b[1], corner_bias_b[0], 4, 0, 1);
  flip (corner_bias_b[2], corner_bias_b[0], 4, 1, 0);
  flip (corner_bias_b[3], corner_bias_b[0], 4, 1, 1);
  flip (corner_bias_c[1], corner_bias_c[0], 4, 0, 1);
  flip (corner_bias_c[2], corner_bias_c[0], 4, 1, 0);
  flip (corner_bias_c[3], corner_bias_c[0], 4, 1, 1);
  flip (focused_corner_bias_a[1], focused_corner_bias_a[0], 4, 0, 1);
  flip (focused_corner_bias_a[2], focused_corner_bias_a[0], 4, 1, 0);
  flip (focused_corner_bias_a[3], focused_corner_bias_a[0], 4, 1, 1);
  flip (focused_corner_bias_b[1], focused_corner_bias_b[0], 4, 0, 1);
  flip (focused_corner_bias_b[2], focused_corner_bias_b[0], 4, 1, 0);
  flip (focused_corner_bias_b[3], focused_corner_bias_b[0], 4, 1, 1);
  flip (focused_corner_bias_c[1], focused_corner_bias_c[0], 4, 0, 1);
  flip (focused_corner_bias_c[2], focused_corner_bias_c[0], 4, 1, 0);
  flip (focused_corner_bias_c[3], focused_corner_bias_c[0], 4, 1, 1);
  
  /* fill in the rest of the radio biases*/
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      radio_bias[6+i][j] = radio_bias[5-i][j];
      radio_bias[i][6+j] = radio_bias[i][5-j];
      radio_bias[6+i][6+j] = radio_bias[5-i][5-j];
      radio_on_bias[6+i][j] = radio_on_bias[5-i][j];
      radio_on_bias[i][6+j] = radio_on_bias[i][5-j];
      radio_on_bias[6+i][6+j] = radio_on_bias[5-i][5-j];
    }
  }
}

static void
flat_style_init (FlatStyle *style)
{
  style->is_made = FALSE;
}

static void
make_the_stupid_things (FlatStyle *style)
{
  GdkColormap *cmap = GTK_STYLE(style)->colormap;
  GdkGC *gc = GTK_STYLE(style)->white_gc;
  GdkImage *a, *b, *c, *d, *e;
  GdkVisual *visual = gdk_colormap_get_visual (cmap);
  GdkPixmap *p[4];
  int i, j, width, height;
  style->is_made = TRUE;
  init ();

  a = gdk_image_new (GDK_IMAGE_NORMAL, visual, 12, 12);
  b = gdk_image_new (GDK_IMAGE_NORMAL, visual, 12, 12);
  c = gdk_image_new (GDK_IMAGE_NORMAL, visual, 4, 4);
  d = gdk_image_new (GDK_IMAGE_NORMAL, visual, 4, 4);
  e = gdk_image_new (GDK_IMAGE_NORMAL, visual, 4, 4);

  for (i = 0; i < 5; i++) {
    /* draw rounded corners */
    p[0] = style->nw[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[1] = style->sw[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[2] = style->ne[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[3] = style->se[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);

    for (j = 0; j < 4; j++) {
        set_image_color (a, &GTK_STYLE(style)->bg[GTK_STATE_NORMAL], 4, 4);
    
      set_image_color (b, &GTK_STYLE(style)->fg[i], 4, 4);
      blend_images (c, a, b, &corner_bias_a[j][0][0], 4, 4, cmap);

        set_image_color (a, &GTK_STYLE(style)->bg[i], 4, 4);

      blend_images (d, a, b, &corner_bias_b[j][0][0], 4, 4, cmap);
      blend_images (e, c, d, &corner_bias_c[j][0][0], 4, 4, cmap);
	  if (p[j] != NULL)
      gdk_draw_image (p[j], GTK_STYLE(style)->white_gc,
                      e, 0, 0, 0, 0, 4, 4);
    }

    /* draw rounded corner focus */
    p[0] = style->fnw[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[1] = style->fsw[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[2] = style->fne[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);
    p[3] = style->fse[i] = gdk_pixmap_new (NULL, 4, 4, GTK_STYLE(style)->depth);

    for (j = 0; j < 4; j++) {
        set_image_color (a, &GTK_STYLE(style)->bg[GTK_STATE_NORMAL], 4, 4);
    
      set_image_color (b, &GTK_STYLE(style)->fg[i], 4, 4);
      blend_images (c, a, b, &focused_corner_bias_a[j][0][0], 4, 4, cmap);

        set_image_color (a, &GTK_STYLE(style)->bg[i], 4, 4);

      blend_images (d, a, b, &focused_corner_bias_b[j][0][0], 4, 4, cmap);
      blend_images (e, c, d, &focused_corner_bias_c[j][0][0], 4, 4, cmap);
	  if (p[j] != NULL)
      gdk_draw_image (p[j], GTK_STYLE(style)->white_gc,
                      e, 0, 0, 0, 0, 4, 4);
    }

    /* draw radio buttons */
    style->radio[i] = gdk_pixmap_new (NULL, 12, 12, GTK_STYLE(style)->depth);
    style->radio_on[i] = gdk_pixmap_new (NULL, 12, 12, GTK_STYLE(style)->depth);
    set_image_color (b, &GTK_STYLE(style)->fg[i], 12, 12);
      set_image_color (a, &GTK_STYLE(style)->bg[i], 12, 12);
      blend_images (a, a, b, &radio_bias[0][0], 12, 12, cmap);
	  if (style->radio[i] != NULL)
      gdk_draw_image (style->radio[i], GTK_STYLE(style)->white_gc,
                      a, 0, 0, 0, 0, 12, 12);
      blend_images (a, a, b, &radio_on_bias[0][0], 12, 12, cmap);
	  if (style->radio_on[i] != NULL)
      gdk_draw_image (style->radio_on[i], GTK_STYLE(style)->white_gc,
                      a, 0, 0, 0, 0, 12, 12);
  }

  gdk_image_destroy (a);
  gdk_image_destroy (b);
  gdk_image_destroy (c);
  gdk_image_destroy (d);
  gdk_image_destroy (e);
}

static void
flat_style_class_init (FlatStyleClass *klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);
  parent_class = g_type_class_peek_parent (klass);
  style_class->draw_hline = draw_hline;
  style_class->draw_vline = draw_vline;
  style_class->draw_shadow = draw_shadow;
  style_class->draw_polygon = draw_polygon;
  style_class->draw_arrow = draw_arrow;
  style_class->draw_diamond = draw_diamond;
  style_class->draw_box = draw_box;
  style_class->draw_check = draw_check;
  style_class->draw_option = draw_option;
  style_class->draw_tab = draw_tab;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_slider = draw_slider;
  style_class->draw_handle = draw_handle;
}

static void
draw_hline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   gint x1,
	   gint x2,
	   gint y)
{
  gint thickness;
  gint i;
  GdkGC *darkgc;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));
  thickness = style->ythickness;

  darkgc  = style->dark_gc[state_type];

  if (area)
    gdk_gc_set_clip_rectangle(darkgc,  area);

  for (i = 0; i < thickness; i++)
    gdk_draw_line(window, darkgc, x1, y + i, x2 - 1, y + i);

  if (area)
    gdk_gc_set_clip_rectangle(darkgc,  NULL);
}
/**************************************************************************/
static void
draw_vline(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   gint y1,
	   gint y2,
	   gint x)
{
  gint thickness;
  gint i;
  GdkGC *darkgc;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  thickness = style->xthickness;

  darkgc  = style->dark_gc[state_type];

  if (area)
    gdk_gc_set_clip_rectangle(darkgc,  area);

  for (i = 0; i < thickness; i++)
    gdk_draw_line(window, darkgc, x + i, y1, x + i, y2 - 1);

  if (area)
    gdk_gc_set_clip_rectangle(darkgc,  NULL);
}
/**************************************************************************/
static void
draw_shadow(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height)
{
  GdkGC *gc1 = NULL;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if (shadow_type == GTK_SHADOW_NONE)
    return;

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  if (area) {
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  gdk_draw_rectangle (window, style->fg_gc[state_type], FALSE, x, y, width-1, height-1);

  if (!style->bg_gc[state_type] && DETAIL("entry")) {
    if (area) {
      gdk_gc_set_clip_rectangle(style->base_gc[state_type], area);
    }
    gdk_draw_rectangle(window, style->base_gc[state_type], FALSE, x+1, y+1, width-3, height-3);
    if (area) {
      gdk_gc_set_clip_rectangle(style->base_gc[state_type], NULL);
    }
  }

  if (area) {
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }

}
/**************************************************************************/
static void
draw_polygon(GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail,
	     GdkPoint * points,
	     gint npoints,
	     gint fill)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);
  g_return_if_fail(points != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  if (fill)
    gdk_draw_polygon(window, style->bg_gc[state_type], TRUE, points, npoints);
  gdk_draw_polygon(window, style->fg_gc[state_type], FALSE, points, npoints);

  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
static void
draw_arrow(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   GtkArrowType arrow_type,
	   gint fill,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{
  GdkGC              *gc;
  gint                half_width;
  gint                half_height;
  gint                xthik, ythik;
  GdkPoint            points[3];
  gchar               border = 1;
   int base, span, xoffset, yoffset;
   int i;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  xthik = style->xthickness;
  ythik = style->ythickness;

  gc = style->fg_gc[state_type];

  if (DETAIL("menuitem") || DETAIL("arrow")) {
    border = 0;
  }

  if (area) gdk_gc_set_clip_rectangle(gc, area);

  if ((fill) && (border)) {
    draw_box(style, window, state_type, GTK_SHADOW_ETCHED_IN, area, widget, detail,
	     x, y, width, height);
  }

  switch (arrow_type) {
  case GTK_ARROW_UP:
    if (border)
      base = width / 2;
    else
      base    = width/2 +3;
    if (base%2 == 0) base++;
    xoffset = (width-base)/2;
    span = base/2 + 1;
    yoffset = (height+span)/2-1;
    for (i=0; i<span; i++) {
      gdk_draw_line(window, gc, x+xoffset+i, y+yoffset-i, 
		    x+xoffset+base-1-i, y+yoffset-i);
    }
    break;
  case GTK_ARROW_DOWN:
    if (border)
      base = width / 2;
    else
      base    = width/2 +3;
    if (base%2 == 0) base++;
    xoffset = (width-base)/2;
    span = base/2 + 1;
    yoffset = (height-span)/2;
    for (i=0; i<span; i++) {
      gdk_draw_line(window, gc, x+xoffset+i, y+yoffset+i, 
		    x+xoffset+base-1-i, y+yoffset+i);
    }
    break;
  case GTK_ARROW_RIGHT:
    if (GTK_CHECK_TYPE(widget, gtk_menu_item_get_type()))
      base = 7;
    else if (border)
      base = height / 2;
    else
      base = height/2 +3;
    if (base%2 == 0) base++;
    yoffset = (height-base)/2;
    span = base/2 + 1;
    xoffset = (width-span)/2;
    if (!border)
      xoffset++;

    for (i=0; i<span; i++) {
      gdk_draw_line(window, gc, x+xoffset+i, y+yoffset+i, 
		    x+xoffset+i, y+yoffset+base-1-i);
    }
    break;
  case GTK_ARROW_LEFT:
    if (border)
      base = height / 2;
    else
      base    = height/2 +3;
    if (base%2 == 0) base++;
    yoffset = (height-base)/2;
    span = base/2 + 1;
    xoffset = (width+span)/2-1;
    if (!border)
      xoffset--;
    for (i=0; i<span; i++) {
      gdk_draw_line(window, gc, x+xoffset-i, y+yoffset+i, 
		    x+xoffset-i, y+yoffset+base-1-i);
    }
    break;
  }

  if (area) gdk_gc_set_clip_rectangle(gc, NULL);
}
/**************************************************************************/
static void
draw_diamond(GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail,
	     gint x,
	     gint y,
	     gint width,
	     gint height)
{
  gint                half_width;
  gint                half_height;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  half_width = width / 2;
  half_height = height / 2;

  if (area) {
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  gdk_draw_line(window, style->fg_gc[state_type],
		x, y + half_height,
		x + half_width, y);
  gdk_draw_line(window, style->fg_gc[state_type],
	        x + half_width, y,
	        x + width - 1, y + half_height);
  gdk_draw_line(window, style->fg_gc[state_type],
         	x + half_width, y + height-1,
      	        x + width-1, y + half_height);
  gdk_draw_line(window, style->fg_gc[state_type],
		x, y + half_height,
		x + half_width, y + height-1);

  if (area) {
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
static void
draw_oval(GtkStyle * style,
	  GdkWindow * window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle * area,
	  GtkWidget * widget,
	  const gchar * detail,
	  gint x,
	  gint y,
	  gint width,
	  gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));
}
/**************************************************************************/
/*static void
draw_string(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    const gchar * string)
{
  GdkGC *fggc;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  fggc = style->fg_gc[state_type];

  if (area) {
    gdk_gc_set_clip_rectangle(fggc, area);
  }

  gdk_draw_string(window, style->font, fggc, x, y, string);

  if (area) {
    gdk_gc_set_clip_rectangle(fggc, NULL);
  }
}*/

/**************************************************************************/
static void
draw_box(GtkStyle * style,
	 GdkWindow * window,
	 GtkStateType state_type,
	 GtkShadowType shadow_type,
	 GdkRectangle * area,
	 GtkWidget * widget,
	 const gchar * detail,
	 gint x,
	 gint y,
	 gint width,
	 gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  if (DETAIL("button") || DETAIL("togglebutton") || DETAIL("buttondefault")) {
    flat_button(style, window, state_type, shadow_type,
		area, widget, detail, x, y, width, height);
  } else if (DETAIL ("menubar")) {
    if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
      if (area)
        gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);

      gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, width, height);
      if (area)
        gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    } else
      gtk_style_apply_default_background (style, window,
                                          widget && !GTK_WIDGET_NO_WINDOW (widget),
                                          state_type, area, x, y, width, height);
  } else {
    if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
      if (area)
        gdk_gc_set_clip_rectangle (style->bg_gc[state_type], area);

      gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, width, height);
      if (area)
        gdk_gc_set_clip_rectangle (style->bg_gc[state_type], NULL);
    } else
      gtk_style_apply_default_background (style, window,
                                          widget && !GTK_WIDGET_NO_WINDOW (widget),
                                          state_type, area, x, y, width, height);
  
    gtk_paint_shadow (style, window, state_type, shadow_type,
                      area, widget, detail, x, y, width, height);
  }
}

/**************************************************************************/
static void 
flat_button(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height)
{
  FlatStyle *data = FLAT_STYLE(style);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  /* Set Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  if (GTK_WIDGET_HAS_FOCUS(widget) && !DETAIL ("buttondefault")) {
    x--;
    y--;
    width += 2;
    height += 2;
  }
    
  
  if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, width, height);
  } else
    gtk_style_apply_default_background (style, window,
                                        widget && !GTK_WIDGET_NO_WINDOW (widget),
                                        state_type, area, x, y, width, height);
  gdk_draw_rectangle(window, style->fg_gc[state_type], FALSE, x, y, width-1, height-1);

  gdk_draw_drawable (window, style->fg_gc[state_type], data->nw[state_type],
		   0, 0, x, y, 4, 4);
  gdk_draw_drawable (window, style->fg_gc[state_type], data->ne[state_type],
		   0, 0, x+width-4, y, 4, 4);
  gdk_draw_drawable (window, style->fg_gc[state_type], data->sw[state_type],
		   0, 0, x, y+height-4, 4, 4);
  gdk_draw_drawable (window, style->fg_gc[state_type], data->se[state_type],
		   0, 0, x+width-4, y+height-4, 4, 4);


  /* Reset Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
/*static void
draw_flat_box(GtkStyle * style,
	      GdkWindow * window,
	      GtkStateType state_type,
	      GtkShadowType shadow_type,
	      GdkRectangle * area,
	      GtkWidget * widget,
	      const gchar * detail,
	      gint x,
	      gint y,
	      gint width,
	      gint height)
{
  GdkGC *gc1;
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);
  
  if (detail) {
    if (!strcmp ("text", detail) && state_type == GTK_STATE_SELECTED)
      gc1 = style->bg_gc[GTK_STATE_SELECTED];
    else if (!strcmp ("viewportbin", detail))
      gc1 = style->bg_gc[GTK_STATE_NORMAL];
    else if (!strcmp ("entry_bg", detail))
      gc1 = style->base_gc[state_type];
    else
      gc1 = style->bg_gc[state_type];
  } else
    gc1 = style->bg_gc[state_type];

  if (area) {
    gdk_gc_set_clip_rectangle(gc1, area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  if (!style->bg_pixmap[state_type] || gc1 != style->bg_gc[state_type] ||
      gdk_window_get_type (window) == GDK_WINDOW_PIXMAP) {
    gdk_draw_rectangle(window, gc1, TRUE, x, y, width, height);
    if (DETAIL("tooltip")) {
      gdk_draw_rectangle(window, style->fg_gc[state_type], FALSE, x, y, width - 1, height - 1);
    }
  } else {
    gtk_style_apply_default_pixmap(style, window, state_type, area, x, y, width, height);
    if (DETAIL("tooltip")) {
      gdk_draw_rectangle(window, style->fg_gc[state_type], FALSE, x, y, width - 1, height - 1);
    }
  }

  if (area) {
    gdk_gc_set_clip_rectangle(gc1, NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}*/
/**************************************************************************/
static void
draw_check(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{
  /* Fixed size only */

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  /* Draw box */
  if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, 8, 8);
  } else
    gtk_style_apply_default_background (style, window,
                                        widget && !GTK_WIDGET_NO_WINDOW (widget),
                                        state_type, area, x, y, 8, 8);

  gdk_draw_rectangle(window, style->fg_gc[state_type], FALSE, x, y, 8, 8);

  if (shadow_type == GTK_SHADOW_IN) {
    gdk_draw_line(window, style->fg_gc[state_type], x+1, y+3, x+1, y+7);
    gdk_draw_line(window, style->fg_gc[state_type], x+2, y+3, x+2, y+7);
    gdk_draw_line(window, style->fg_gc[state_type], x+3, y+6, x+7, y+2);
    gdk_draw_line(window, style->fg_gc[state_type], x+3, y+5, x+7, y+1);
  }

  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
static void
draw_option(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height)
{
  FlatStyle *data = FLAT_STYLE(style);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  x -= 1;
  y -= 1;

  if (area)
    gdk_gc_set_clip_rectangle(style->white_gc, area);

  if (state_type != GTK_STATE_PRELIGHT)
    state_type = GTK_STATE_NORMAL;

  if (shadow_type == GTK_SHADOW_IN)
    gdk_draw_drawable (window, style->white_gc,
                     data->radio_on[state_type],
                     0, 0, x, y, 12, 12);    
  else
    gdk_draw_drawable (window, style->white_gc,
                     data->radio[state_type],
                     0, 0, x, y, 12, 12);

  if (area)
    gdk_gc_set_clip_rectangle(style->white_gc, NULL);
}
/**************************************************************************/
static void
draw_cross(GtkStyle * style,
	   GdkWindow * window,
	   GtkStateType state_type,
	   GtkShadowType shadow_type,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));
}

/**************************************************************************/
static void
draw_ramp(GtkStyle * style,
	  GdkWindow * window,
	  GtkStateType state_type,
	  GtkShadowType shadow_type,
	  GdkRectangle * area,
	  GtkWidget * widget,
	  const gchar * detail,
	  GtkArrowType arrow_type,
	  gint x,
	  gint y,
	  gint width,
	  gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));
}

/**************************************************************************/
static void
draw_tab(GtkStyle * style,
	 GdkWindow * window,
	 GtkStateType state_type,
	 GtkShadowType shadow_type,
	 GdkRectangle * area,
	 GtkWidget * widget,
	 const gchar * detail,
	 gint x,
	 gint y,
	 gint width,
	 gint height)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  gtk_paint_arrow (style, window, state_type, shadow_type, area,
                   widget, "arrow", GTK_ARROW_UP, TRUE, x, y-height/2, width, height);
  gtk_paint_arrow (style, window, state_type, shadow_type, area,
                   widget, "arrow", GTK_ARROW_DOWN, TRUE, x, y+height/2, width, height);
}

/**************************************************************************/
static void
draw_shadow_gap(GtkStyle * style,
		GdkWindow * window,
		GtkStateType state_type,
		GtkShadowType shadow_type,
		GdkRectangle * area,
		GtkWidget * widget,
		const gchar * detail,
		gint x,
		gint y,
		gint width,
		gint height,
		GtkPositionType gap_side,
		gint gap_x,
		gint gap_width)
{
  GdkRectangle        rect;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  gtk_paint_shadow(style, window, state_type, shadow_type, area, widget, detail,
		   x, y, width, height);

  switch (gap_side)
    {
    case GTK_POS_TOP:
      rect.x = x + gap_x;
      rect.y = y;
      rect.width = gap_width;
      rect.height = 2;
      break;
    case GTK_POS_BOTTOM:
      rect.x = x + gap_x;
      rect.y = y + height - 2;
      rect.width = gap_width;
      rect.height = 2;
      break;
    case GTK_POS_LEFT:
      rect.x = x;
      rect.y = y + gap_x;
      rect.width = 2;
      rect.height = gap_width;
      break;
    case GTK_POS_RIGHT:
      rect.x = x + width - 2;
      rect.y = y + gap_x;
      rect.width = 2;
      rect.height = gap_width;
      break;
  }

  gtk_style_apply_default_pixmap(style, window, state_type, area,
				 rect.x, rect.y, rect.width, rect.height);
}
/**************************************************************************/
static void
draw_box_gap(GtkStyle * style,
	     GdkWindow * window,
	     GtkStateType state_type,
	     GtkShadowType shadow_type,
	     GdkRectangle * area,
	     GtkWidget * widget,
	     const gchar * detail,
	     gint x,
	     gint y,
	     gint width,
	     gint height,
	     GtkPositionType gap_side,
	     gint gap_x,
	     gint gap_width)
{
  GdkRectangle        rect;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  gtk_paint_box(style, window, state_type, shadow_type, area, widget, detail,
		x, y, width, height);

  if (gap_x == 0) {
    gap_x++;
    gap_width--;
  }

  switch (gap_side) {
    case GTK_POS_TOP:
      rect.x = x + gap_x;
      rect.y = y;
      rect.width = gap_width;
      rect.height = 2;
      break;
    case GTK_POS_BOTTOM:
      rect.x = x + gap_x;
      rect.y = y + height - 2;
      rect.width = gap_width;
      rect.height = 2;
      break;
    case GTK_POS_LEFT:
      rect.x = x;
      rect.y = y + gap_x;
      rect.width = 2;
      rect.height = gap_width;
      break;
    case GTK_POS_RIGHT:
      rect.x = x + width - 2;
      rect.y = y + gap_x;
      rect.width = 2;
      rect.height = gap_width;
      break;
  }

  gtk_style_apply_default_pixmap(style, window, state_type, area,
				 rect.x, rect.y, rect.width, rect.height);

}
/**************************************************************************/
static void
draw_extension(GtkStyle * style,
	       GdkWindow * window,
	       GtkStateType state_type,
	       GtkShadowType shadow_type,
	       GdkRectangle * area,
	       GtkWidget * widget,
	       const gchar * detail,
	       gint x,
	       gint y,
	       gint width,
	       gint height,
	       GtkPositionType gap_side)
{
  FlatStyle *data = FLAT_STYLE(style);
  
  g_return_if_fail (style != NULL);
  g_return_if_fail (window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));
  
  gtk_style_apply_default_background (style, window,
                                      widget && !GTK_WIDGET_NO_WINDOW (widget),
                                      GTK_STATE_NORMAL, area, x, y, width, height);
  
  if (width == -1 && height == -1)
    gdk_window_get_size (window, &width, &height);
  else if (width == -1)
    gdk_window_get_size (window, &width, NULL);
  else if (height == -1)
    gdk_window_get_size (window, NULL, &height);
  
  if (shadow_type == GTK_SHADOW_NONE)
    return;

  if (area)
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], area);

  switch (gap_side) {
  case GTK_POS_TOP:
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					state_type, area,
					x + 1, 
					y, 
					width - 2, 
					height - 1);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y, x, y + height-2); 
    gdk_draw_line (window, style->fg_gc[state_type],
		   x + 4, y + height - 1, x + width - 2, y + height - 1);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x + width - 1, y, x + width - 1, y + height - 2);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->sw[state_type], 0, 0, x, y+height-4, 4, 4);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->se[state_type], 0, 0, x+width-4, y+height-4, 4, 4);  

    break;
  case GTK_POS_BOTTOM:
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					state_type, area,
					x + 1, 
					y + 1, 
					width - 2, 
					height - 1);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y, x, y + height-1); 
    gdk_draw_line (window, style->fg_gc[state_type],
		   x + 4, y, x + width - 2, y);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x + width - 1, y, x + width - 1, y + height - 1);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->nw[state_type], 0, 0, x, y, 4, 4);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->ne[state_type], 0, 0, x+width-4, y, 4, 4);
    break;
  case GTK_POS_LEFT:
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					state_type, area,
					x, 
					y + 1, 
					width - 1, 
					height - 2);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y, x+width-1, y); 
    gdk_draw_line (window, style->fg_gc[state_type],
		   x + width-1, y, x + width - 1, y+height-1);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y+height-1, x + width - 1, y + height - 1);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->ne[state_type], 0, 0, x+width-4, y, 4, 4);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->se[state_type], 0, 0, x+width-4, y+height-4, 4, 4);

    break;
  case GTK_POS_RIGHT:
    gtk_style_apply_default_background (style, window,
					widget && !GTK_WIDGET_NO_WINDOW (widget),
					state_type, area,
					x + 1, 
					y + 1, 
					width - 1, 
					height - 2);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y, x+width-1, y); 
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y, x, y+height-1);
    gdk_draw_line (window, style->fg_gc[state_type],
		   x, y+height-1, x + width - 1, y + height - 1);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->nw[state_type], 0, 0, x, y, 4, 4);
    gdk_draw_drawable (window, style->fg_gc[state_type],
		     data->sw[state_type], 0, 0, x, y+height-4, 4, 4);
    break;
  }

  if (area) {
    gdk_gc_set_clip_rectangle (style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
static void
draw_focus(GtkStyle * style,
	   GdkWindow * window,
	   GdkRectangle * area,
	   GtkWidget * widget,
	   const gchar * detail,
	   gint x,
	   gint y,
	   gint width,
	   gint height)
{
  GdkGC *focusgc;
  FlatStyle *data = FLAT_STYLE(style);
  int state;

  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  state = GTK_WIDGET_STATE(widget);
  focusgc = style->fg_gc[state];

  if (area) {
    gdk_gc_set_clip_rectangle(focusgc, area);
  }

  if (DETAIL("button") || DETAIL("togglebutton") || 
      DETAIL("buttondefault")) {
    gdk_draw_rectangle(window, focusgc, FALSE, x+1, y+1, width-2, height-2);
     
    gdk_draw_drawable (window, focusgc, data->fnw[state],
		     0, 0, x+1, y+1, 4, 4);
    gdk_draw_drawable (window, focusgc, data->fne[state],
		     0, 0, x+width-4, y+1, 4, 4);
    gdk_draw_drawable (window, focusgc, data->fsw[state],
		     0, 0, x+1, y+height-4, 4, 4);
    gdk_draw_drawable (window, focusgc, data->fse[state],
		     0, 0, x+width-4, y+height-4, 4, 4);
  } else if (DETAIL("checkbutton") || DETAIL("radiobutton")) {
    gdk_gc_set_line_attributes (focusgc, 1, GDK_LINE_ON_OFF_DASH,
                                GDK_CAP_BUTT, GDK_JOIN_MITER);
    gdk_draw_rectangle(window, focusgc, FALSE, x, y, width-1, height-1);
    gdk_gc_set_line_attributes (focusgc, 1, GDK_LINE_SOLID,
                                GDK_CAP_BUTT, GDK_JOIN_MITER);
  } else {
    gdk_draw_rectangle(window, focusgc, FALSE, x, y, width-1, height-1);
  }

  if (area) {
    gdk_gc_set_clip_rectangle(focusgc, NULL);
  }
}
/**************************************************************************/
static void
draw_slider(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height,
	    GtkOrientation orientation)
{
  g_return_if_fail(style != NULL);
  g_return_if_fail(window != NULL);

  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  if ((width == -1) && (height == -1)) gdk_window_get_size(window, &width, &height);
  else if (width == -1)                gdk_window_get_size(window, &width, NULL);
  else if (height == -1)               gdk_window_get_size(window, NULL, &height);

  /* Set Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  /* Draw backgound */
  if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, width, height);
  } else
    gtk_style_apply_default_background (style, window,
                                        widget && !GTK_WIDGET_NO_WINDOW (widget),
                                        state_type, area, x, y, width, height);

  /* Draw border */
  gdk_draw_rectangle(window, style->fg_gc[state_type], FALSE,
                     x, y, width-1, height-1);

  /* Draw middle line */
  if (GTK_CHECK_TYPE(widget, gtk_hscale_get_type())) {
    gdk_draw_line(window, style->fg_gc[state_type],
                  x+width/2, y+2, x+width/2, y+height-4);
  } else {
    gdk_draw_line(window, style->fg_gc[state_type],
                  x+2, y+height/2, x+width-4, y+height/2);
  }


  /* Reset Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
/**************************************************************************/
static void
draw_handle(GtkStyle * style,
	    GdkWindow * window,
	    GtkStateType state_type,
	    GtkShadowType shadow_type,
	    GdkRectangle * area,
	    GtkWidget * widget,
	    const gchar * detail,
	    gint x,
	    gint y,
	    gint width,
	    gint height,
	    GtkOrientation orientation)
{
  if(FLAT_STYLE(style)->is_made == FALSE)
    make_the_stupid_things(FLAT_STYLE(style));

  /* Set Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], area);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], area);
  }

  /* Draw backgound */
  if (!style->bg_gc[state_type] || GDK_IS_PIXMAP (window)) {
    gdk_draw_rectangle (window, style->bg_gc[state_type], TRUE,
		  	  x, y, width, height);
  } else
    gtk_style_apply_default_background (style, window,
                                        widget && !GTK_WIDGET_NO_WINDOW (widget),
                                        state_type, area, x, y, width, height);

  /* Draw border */
  gdk_draw_rectangle(window, style->fg_gc[state_type],  FALSE, x, y, width-1, height-1);

  /* Reset Clip Region */
  if (area) {
    gdk_gc_set_clip_rectangle(style->bg_gc[state_type], NULL);
    gdk_gc_set_clip_rectangle(style->fg_gc[state_type], NULL);
  }
}
