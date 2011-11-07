/*  galaxy
 *  Copyright (C) 2003 Frederic Crozat - MandrakeSoft
 *                1999 Olivier Fourdan (fourdan@xfce.org) for XFCE code
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

#include <gtk/gtkstyle.h>

#define RADIO_SIZE 13

typedef struct
{
  guint refcount;
  gboolean enable_gradient;
  int thickness;
} GalaxyRcData;


typedef struct
{
  GdkColor gray[8]; /* from light to dark */
  GdkColor blue[3]; /* from light to dark */
  GdkColor check_color;
  
  GdkGC *gray_gc[8]; /* from light to dark */
  GdkGC *blue_gc[3]; /* from light to dark */

  GdkGC *check_gc;

  GdkPixmap *radio_pixmap_nonactive[5];
  GdkPixmap *radio_pixmap_active[5];
  GdkPixmap *radio_pixmap_inconsistent[5];
  GdkBitmap *radio_pixmap_mask; /* All masks are the same */
  gboolean enable_gradient;

} GalaxyData;

void galaxy_initialize_style(GtkStyleClass *klass,
			     GtkStyleClass *parent);
