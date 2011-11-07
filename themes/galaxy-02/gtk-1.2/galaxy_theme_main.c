/*  ggalaxy
 *  Copyright (C) 2003 Frederic Crozat - MandrakeSoft
 *  1999 Olivier Fourdan (fourdan@xfce.org) for XFCE code
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <gmodule.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "galaxy.h"

static unsigned char dot_intensity[] = {
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x78,0x99,0xa6,0x99,0x71,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x99,0x9d,0x7c,0x6e,0x55,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0xa6,0x7c,0x6e,0x66,0x4c,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x99,0x6e,0x66,0x52,0x55,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x71,0x55,0x4c,0x55,0x68,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,0x6e,
};
static unsigned char dot_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0xd4,0xff,0xd4,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x66,0xff,0xff,0xff,0xff,0xff,0x66,0x00,0x00,0x00,
0x00,0x00,0x00,0xd4,0xff,0xff,0xff,0xff,0xff,0xd4,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xd4,0xff,0xff,0xff,0xff,0xff,0xd4,0x00,0x00,0x00,
0x00,0x00,0x00,0x66,0xff,0xff,0xff,0xff,0xff,0x66,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0xd4,0xff,0xd4,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static unsigned char circle_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x23,0x62,0x92,0xb3,0xb2,0x95,0x2b,0x00,0x00,0x00,
0x00,0x00,0x3e,0xab,0xc9,0xeb,0xf9,0xf5,0xfd,0xff,0x57,0x00,0x00,
0x00,0x1f,0xb5,0xd8,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0x2b,0x00,
0x00,0x67,0xb9,0xf2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9c,0x00,
0x00,0x9a,0xe2,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0x00,
0x00,0xba,0xeb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,
0x00,0xc0,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe5,0x00,
0x00,0x9b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x9c,0x00,
0x00,0x2b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x2b,0x00,
0x00,0x00,0x57,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x57,0x00,0x00,
0x00,0x00,0x00,0x2b,0x9c,0xe5,0xff,0xe5,0x9c,0x2b,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
static unsigned char outline_alpha[] = {
0x00,0x00,0x00,0x4a,0xac,0xe9,0xff,0xe9,0xac,0x4a,0x00,0x00,0x00,
0x00,0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,0x00,
0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,
0x4a,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4a,
0xac,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xac,
0xe9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe9,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xe9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe9,
0xac,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xac,
0x4a,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x4a,
0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,
0x00,0x00,0x98,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x98,0x00,0x00,
0x00,0x00,0x00,0x4a,0xac,0xe9,0xff,0xe9,0xac,0x4a,0x00,0x00,0x00,
};
static unsigned char inconsistent_alpha[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};


enum
{
    TOKEN_GRADIENT = G_TOKEN_LAST + 1,
    TOKEN_THICKNESS,
    TOKEN_TRUE,
    TOKEN_FALSE,
};

static struct
{
  const gchar *name;
  guint        token;
}
theme_symbols[] =
{
  { "enable_gradient", TOKEN_GRADIENT },
  { "thickness",       TOKEN_THICKNESS},
  { "TRUE",            TOKEN_TRUE},
  { "FALSE",           TOKEN_FALSE},
};

static guint n_theme_symbols = sizeof(theme_symbols) / sizeof(theme_symbols[0]);

static void
galaxy_rc_data_ref (GalaxyRcData *galaxy_data)
{
  galaxy_data->refcount++;
}

static void
galaxy_rc_data_unref (GalaxyRcData *galaxy_data)
{
  galaxy_data->refcount--;
  if (galaxy_data->refcount == 0)
    {
      g_free (galaxy_data);
    }
}

static guint
theme_parse_thickness(GScanner     *scanner,
		      int          *thickness)
{
  guint token;

  /* Skip 'thickness' */
  token = g_scanner_get_next_token(scanner);

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_EQUAL_SIGN)
    return G_TOKEN_EQUAL_SIGN;

  token = g_scanner_get_next_token(scanner);
  if (token != G_TOKEN_INT)
    return G_TOKEN_INT;

  *thickness = scanner->value.v_int;
  
  return G_TOKEN_NONE;
}

static guint theme_parse_boolean(GScanner * scanner, GTokenType wanted_token, guint * retval)
{
    guint token;

    token = g_scanner_get_next_token(scanner);
    if(token != wanted_token)
        return wanted_token;

    token = g_scanner_get_next_token(scanner);
    if(token != G_TOKEN_EQUAL_SIGN)
        return G_TOKEN_EQUAL_SIGN;

    token = g_scanner_get_next_token(scanner);
    if(token == TOKEN_TRUE)
        *retval = TRUE;
    else if(token == TOKEN_FALSE)
        *retval = FALSE;
    else
        return TOKEN_TRUE;

    return G_TOKEN_NONE;
}


static guint theme_parse_rc_style(GScanner *scanner, GtkRcStyle * rc_style)
{
    static GQuark scope_id = 0;
    GalaxyRcData *rc_data;
    guint old_scope;
    guint token;
    guint i;

    /* Set up a new scope in this scanner. */

    if(!scope_id)
        scope_id = g_quark_from_string("galaxy_theme_engine");

    /* If we bail out due to errors, we *don't* reset the scope, so the
     * error messaging code can make sense of our tokens.
     */
    old_scope = g_scanner_set_scope(scanner, scope_id);

    /* Now check if we already added our symbols to this scope
     * (in some previous call to galaxy_rc_style_parse for the
     * same scanner.
     */

    if(!g_scanner_lookup_symbol(scanner, theme_symbols[0].name)) {
        for(i = 0; i < n_theme_symbols; i++)
        {
            g_scanner_scope_add_symbol(scanner, scope_id, theme_symbols[i].name, 
				       GINT_TO_POINTER(theme_symbols[i].token));
        }
    }
    rc_data = g_new(GalaxyRcData, 1);
    rc_data->refcount = 1;
    rc_data->enable_gradient = TRUE;
    rc_data->thickness = 2;

    token = g_scanner_peek_next_token(scanner);
    while(token != G_TOKEN_RIGHT_CURLY)
    {
      switch (token) {
      case TOKEN_GRADIENT:
	token = theme_parse_boolean(scanner, TOKEN_GRADIENT, 
				    &rc_data->enable_gradient);
	break;
      case TOKEN_THICKNESS:
	token = theme_parse_thickness (scanner,
				       &rc_data->thickness);
	break;
      default:
	g_scanner_get_next_token(scanner);
	token = G_TOKEN_RIGHT_CURLY;
	break;
      }


      if(token != G_TOKEN_NONE) {
	return token;
      }
      token = g_scanner_peek_next_token(scanner);
    }

    g_scanner_get_next_token(scanner);

    rc_style->engine_data = rc_data;

    g_scanner_set_scope(scanner, old_scope);

    return G_TOKEN_NONE;
}

static void theme_merge_rc_style(GtkRcStyle * dest, GtkRcStyle * src)
{
  GalaxyRcData *src_data = src->engine_data;
  
  if (!dest->engine_data)
    {
      if (src_data)
	{
	  galaxy_rc_data_ref (src_data);
	  dest->engine_data = src_data;
	}
    }
}

static void
set_props (GtkStyle *style)
{
#define OPTION_INDICATOR_WIDTH 7
#define OPTION_INDICATOR_LEFT_SPACING 7
#define OPTION_INDICATOR_RIGHT_SPACING 5
  gtk_style_set_prop_experimental (style,"GtkButton::default_spacing",6 );
  gtk_style_set_prop_experimental (style,"GtkCheckButton::indicator_size", 15 );
  gtk_style_set_prop_experimental (style,"GtkPaned::handle_width", 6 );
  gtk_style_set_prop_experimental (style,"GtkPaned::handle_full_size", 1 );
  gtk_style_set_prop_experimental (style,"GtkRange::trough_border",0 );
  gtk_style_set_prop_experimental (style,"GtkRange::always_draw_trough",1 );
  gtk_style_set_prop_experimental (style,"GtkRange::slider_width",15 );
  gtk_style_set_prop_experimental (style,"GtkRange::stepper_size",15 );
  gtk_style_set_prop_experimental (style,"GtkRange::stepper_spacing",0 );
}

static void
theme_duplicate_style(GtkStyle * dest,
		      GtkStyle * src)
{
  dest->engine_data = g_memdup (src->engine_data, sizeof (GalaxyData));
  
  set_props (dest);
}

static GdkGC *
realize_color (GtkStyle * style,
	       GdkColor * color)
{
  GdkGCValues gc_values;

  gdk_colormap_alloc_color (style->colormap, color,
			    FALSE, TRUE);

  gc_values.foreground = *color;

  return gtk_gc_get (style->depth, style->colormap,
		     &gc_values, GDK_GC_FOREGROUND);
}

static GdkPixbuf *
generate_bit (unsigned char alpha[], GdkColor *color, double mult)
{
  guint r, g, b;
  GdkPixbuf *pixbuf;
  unsigned char *pixels;
  int w, h, rs;
  int x, y;
  
  r = (color->red >> 8) * mult;
  r = MIN(r, 255);
  g = (color->green >> 8) * mult;
  g = MIN(g, 255);
  b = (color->blue >> 8) * mult;
  b = MIN(b, 255);

  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, RADIO_SIZE, RADIO_SIZE);

  w = gdk_pixbuf_get_width (pixbuf);
  h = gdk_pixbuf_get_height (pixbuf);
  rs = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);


  for (y=0; y < h; y++)
    {
      for (x=0; x < w; x++)
	{
	  pixels[y*rs + x*4 + 0] = r;
	  pixels[y*rs + x*4 + 1] = g;
	  pixels[y*rs + x*4 + 2] = b;
	  if (alpha)
	    pixels[y*rs + x*4 + 3] = alpha[y*w + x];
	  else
	    pixels[y*rs + x*4 + 3] = 255;
	}
    }

  return pixbuf;
}

#define CLAMP_UCHAR(v) ((guchar) (CLAMP (((int)v), (int)0, (int)255)))

static GdkPixbuf *
colorize_bit (unsigned char *bit,
	      unsigned char *alpha,
	      GdkColor  *new_color)
{
  GdkPixbuf *pixbuf;
  double intensity;
  int x, y;
  const guchar *src, *asrc;
  guchar *dest;
  int dest_rowstride;
  int width, height;
  guchar *dest_pixels;
  
  pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8,
			   RADIO_SIZE, RADIO_SIZE);

  if (pixbuf == NULL)
    return NULL;
  
  dest_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);
  dest_pixels = gdk_pixbuf_get_pixels (pixbuf);
  
  for (y = 0; y < RADIO_SIZE; y++)
    {
      src = bit + y * RADIO_SIZE;
      asrc = alpha + y * RADIO_SIZE;
      dest = dest_pixels + y * dest_rowstride;

      for (x = 0; x < RADIO_SIZE; x++)
        {
          double dr, dg, db;
          
          intensity = (src[x] + 0 )/ 255.0;

          if (intensity <= 0.5)
            {
              /* Go from black at intensity = 0.0 to new_color at intensity = 0.5 */
              dr = (new_color->red * intensity * 2.0) / 65535.0;
              dg = (new_color->green * intensity * 2.0) / 65535.0;
              db = (new_color->blue * intensity * 2.0) / 65535.0;
            }
          else
            {
              /* Go from new_color at intensity = 0.5 to white at intensity = 1.0 */
              dr = (new_color->red + (65535 - new_color->red) * (intensity - 0.5) * 2.0) / 65535.0;
              dg = (new_color->green + (65535 - new_color->green) * (intensity - 0.5) * 2.0) / 65535.0;
              db = (new_color->blue + (65535 - new_color->blue) * (intensity - 0.5) * 2.0) / 65535.0;
            }
          
          dest[0] = CLAMP_UCHAR (255 * dr);
          dest[1] = CLAMP_UCHAR (255 * dg);
          dest[2] = CLAMP_UCHAR (255 * db);

	  dest[3] = asrc[x];
	  dest += 4;
        }
    }

  return pixbuf;
}

static GdkPixmap *
pixbuf_to_pixmap (GtkStyle * style, GdkPixbuf *pixbuf)
{
  GdkGC *tmp_gc;
  GdkPixmap *pixmap;
  
  pixmap = gdk_pixmap_new (NULL,
			   gdk_pixbuf_get_width (pixbuf),
			   gdk_pixbuf_get_height (pixbuf),
			   style->depth);

  tmp_gc = gdk_gc_new (pixmap);
  
  gdk_pixbuf_render_to_drawable (pixbuf, pixmap, tmp_gc, 0, 0, 0, 0,
				 gdk_pixbuf_get_width (pixbuf),
				 gdk_pixbuf_get_height (pixbuf),
				 GDK_RGB_DITHER_NORMAL, 0, 0);
  gdk_gc_unref (tmp_gc);

  return pixmap;
}

static void theme_realize_style(GtkStyle * style)
{
  GalaxyData *galaxy_data = style->engine_data;
  GdkPixbuf *dot, *circle, *outline, *inconsistent, *composite, *check;
  GdkColor *composite_color;

  int i;

  gdk_color_parse ("#EFEFEF", &galaxy_data->gray[0]);
  gdk_color_parse ("#E6E7E6", &galaxy_data->gray[1]);
  gdk_color_parse ("#CECECE", &galaxy_data->gray[2]);
  gdk_color_parse ("#BDBEBD", &galaxy_data->gray[3]);
  gdk_color_parse ("#ADAAAD", &galaxy_data->gray[4]);
  gdk_color_parse ("#A5A6A5", &galaxy_data->gray[5]);
  gdk_color_parse ("#949694", &galaxy_data->gray[6]);
  gdk_color_parse ("#848684", &galaxy_data->gray[7]);
		                                  
  gdk_color_parse ("#7382BC", &galaxy_data->blue[0]);
  gdk_color_parse ("#4A61AD", &galaxy_data->blue[1]);
  gdk_color_parse ("#21459C", &galaxy_data->blue[2]);

  gdk_color_parse ("#333333", &galaxy_data->check_color);

  galaxy_data->check_gc = realize_color (style, &galaxy_data->check_color);

  for (i=0; i <8 ; i++) {
    galaxy_data->enable_gradient = galaxy_data->enable_gradient || gdk_color_equal (&galaxy_data->gray[i],&style->bg[GTK_STATE_NORMAL]);
    galaxy_data->gray_gc[i] = realize_color (style, &galaxy_data->gray[i]);
  }

  /* FIXME
  if (!galaxy_data->enable_gradient) {
    style->klass->xthickness = style->klass->ythickness = 1;
  }
*/
  for (i=0; i <3 ; i++) {
    galaxy_data->blue_gc[i] = realize_color (style, &galaxy_data->blue[i]);
  }

  inconsistent = generate_bit (inconsistent_alpha, &galaxy_data->gray[2], 1.0);
  outline = generate_bit (outline_alpha, &galaxy_data->gray[6], 1.0);
  dot = colorize_bit (dot_intensity, dot_alpha, &galaxy_data->check_color);

  gdk_pixbuf_render_pixmap_and_mask (outline,
				     NULL,
				     &galaxy_data->radio_pixmap_mask,
				     1);
  
  for (i = 0; i < 5; i++)
    {
      if (i == GTK_STATE_ACTIVE)
	{
	  composite_color = &style->bg[GTK_STATE_PRELIGHT];
	  circle = generate_bit (circle_alpha, &style->bg[i], 1.0);
	}   
      else
	{
	  composite_color = &style->bg[i];
	  circle = generate_bit (circle_alpha, &style->white, 1.0);
	}

      composite = generate_bit (NULL, composite_color, 1.0);

      gdk_pixbuf_composite (outline, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (circle, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);

      galaxy_data->radio_pixmap_nonactive[i] = pixbuf_to_pixmap (style, composite);
      
      gdk_pixbuf_composite (dot, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      
      galaxy_data->radio_pixmap_active[i] = pixbuf_to_pixmap (style, composite);
      
      gdk_pixbuf_unref (composite);

      composite = generate_bit (NULL, composite_color,1.0);

      gdk_pixbuf_composite (outline, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (circle, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      gdk_pixbuf_composite (inconsistent, composite,
			    0, 0, RADIO_SIZE, RADIO_SIZE, 0, 0,
			    1.0, 1.0, GDK_INTERP_NEAREST, 255);
      
      galaxy_data->radio_pixmap_inconsistent[i] = pixbuf_to_pixmap (style, composite);
      
      gdk_pixbuf_unref (composite);
      gdk_pixbuf_unref (circle);

    }
  gdk_pixbuf_unref (dot);  
  gdk_pixbuf_unref (inconsistent);
  gdk_pixbuf_unref (outline);

}

static void theme_unrealize_style(GtkStyle * style)
{  
  GalaxyData *galaxy_data = style->engine_data;
  int i;

  /* We don't free the colors, because we don't know if
   * gtk_gc_release() actually freed the GC. FIXME - need
   * a way of ref'ing colors explicitely so GtkGC can
   * handle things properly.
   */

  for (i=0; i <8 ; i++) {
    gtk_gc_release (galaxy_data->gray_gc[i]);
  }

  for (i=0; i <3 ; i++) {
    gtk_gc_release (galaxy_data->blue_gc[i]);
  }

  for (i = 0; i < 5; i++) {
    gdk_pixmap_unref (galaxy_data->radio_pixmap_nonactive[i]);
    gdk_pixmap_unref (galaxy_data->radio_pixmap_active[i]);
    gdk_pixmap_unref (galaxy_data->radio_pixmap_inconsistent[i]);
  }

  gdk_pixmap_unref (galaxy_data->radio_pixmap_mask);

}

static void
theme_rc_style_to_style(GtkStyle * style,
			GtkRcStyle * rc_style)
{
  static GtkStyleClass *class = NULL;
  static GtkStyleClass *button_class = NULL;
  static GtkStyleClass *thin_class = NULL;
  GalaxyRcData *rc_data = rc_style->engine_data;
  GalaxyData *galaxy_data;
  int i;

  if (!class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      class = g_new (GtkStyleClass, 1);

      galaxy_initialize_style (class, style->klass);
      gtk_style_unref (tmp_style);
      class->xthickness = 2;
      class->ythickness = 2;
    }


  if (!thin_class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      thin_class = g_new (GtkStyleClass, 1);

      galaxy_initialize_style (thin_class, style->klass);
      gtk_style_unref (tmp_style);
      thin_class->xthickness = 1;
      thin_class->ythickness = 1;
    }
  
  if (!button_class)
    {
      GtkStyle *tmp_style = gtk_style_new ();
      button_class = g_new (GtkStyleClass, 1);

      galaxy_initialize_style (button_class, style->klass);
      gtk_style_unref (tmp_style);
      button_class->xthickness = 4;
      button_class->ythickness = 4;
    }

  switch (rc_data->thickness) {
  case 1:
    style->klass = thin_class;
    break;
  case 2:
    style->klass = class;
    break;
  case 4:
    style->klass = button_class;
    break;
  default:
     style->klass = class;
     g_warning ("galaxy theme: Invalid thickness %d in RC file\n",
		rc_data->thickness);
     break;
  }

  galaxy_data = style->engine_data = g_new0 (GalaxyData, 1);

  galaxy_data->enable_gradient = rc_data->enable_gradient;

  set_props (style);

}


static void
theme_destroy_rc_style(GtkRcStyle * rc_style)
{
  GalaxyRcData *rc_data = rc_style->engine_data;
  galaxy_rc_data_unref (rc_data);
}


static void
theme_destroy_style(GtkStyle * style)
{
  g_free (style->engine_data);
}

/* grabbed from Crux engine */
/* GTK+ sucks in places. This part contains dubious kludges to
   force it to do what we want. */

/* GtkRange code */

static gint
gtk_range_expose (GtkWidget *widget,
		  GdkEventExpose *event)
{
  GtkRange *range;

  /* The version of this method in gtkrange.c doesn't work
   * when the slider is as wide as the trough.
   */
  g_return_val_if_fail (widget != NULL, FALSE);
  g_return_val_if_fail (GTK_IS_RANGE (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  range = GTK_RANGE (widget);

  if (event->window == range->trough)
    {
        gtk_range_draw_trough (range);
    }
  else if (event->window == widget->window)
    {
      gtk_range_draw_background (range);
    }
  else if (event->window == range->slider)
    {
      gtk_range_draw_slider (range);
    }
  else if (event->window == range->step_forw)
    {
      gtk_range_draw_step_forw (range);
    }
  else if (event->window == range->step_back)
    {
      gtk_range_draw_step_back (range);
    }
  return FALSE;
}

G_MODULE_EXPORT void theme_init(GtkThemeEngine * engine)
{
  engine->parse_rc_style = theme_parse_rc_style;
  engine->merge_rc_style = theme_merge_rc_style;
  engine->rc_style_to_style = theme_rc_style_to_style;
  engine->duplicate_style = theme_duplicate_style;
  engine->realize_style = theme_realize_style;
  engine->unrealize_style = theme_unrealize_style;
  engine->destroy_rc_style = theme_destroy_rc_style;
  engine->destroy_style = theme_destroy_style;
  engine->set_background = NULL;

  gdk_rgb_init ();
}

G_MODULE_EXPORT void theme_exit(void)
{
}

/* The following function will be called by GTK+ when the module
 * is loaded and checks to see if we are compatible with the
 * version of GTK+ that loads us.
 */

G_MODULE_EXPORT const gchar* g_module_check_init (GModule *module);
const gchar*
g_module_check_init (GModule *module)
{
  return gtk_check_version (GTK_MAJOR_VERSION,
			    GTK_MINOR_VERSION,
			    GTK_MICRO_VERSION - GTK_INTERFACE_AGE);
}

