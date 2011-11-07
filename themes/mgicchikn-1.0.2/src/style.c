/*  MagicChicken: src/style.c
 *
 *  Copyright 2001 (c) James M. Cape <jcape@ignore.your.tv>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "style.h"
#include "rc-style.h"
#include "types.h"
#include "draw.h"
#include "util.h"


static GtkStyleClass *style_parent_class = NULL;
GType mgicchikn_style_type = 0;


static PixbufKey *
pixbuf_key_dup (PixbufKey * src)
{
	return g_memdup (src, sizeof (PixbufKey));
}


static guint
pixbuf_key_hash (PixbufKey * key)
{
	return (GPOINTER_TO_INT (key->orig_pixbuf) ^ key->state);
}


static gboolean
pixbuf_key_equal (PixbufKey * key1,
				  PixbufKey * key2)
{
	return (key1->orig_pixbuf == key2->orig_pixbuf && key1->state == key2->state);
}


static void
mgicchikn_style_base_init (gpointer base)
{
	MgicChiknStyleClass *class = MGICCHIKN_STYLE_CLASS (base);

	class->pixbufs = g_cache_new ((GCacheNewFunc) mgicchikn_util_recolor_pixbuf,
								  g_object_unref,
								  (GCacheDupFunc) pixbuf_key_dup,
								  g_free,
								  (GHashFunc) pixbuf_key_hash,
								  g_direct_hash,
								  (GEqualFunc) pixbuf_key_equal);
}


static void
mgicchikn_style_base_finalize (gpointer base)
{
	MgicChiknStyleClass *class = MGICCHIKN_STYLE_CLASS (base);

	g_cache_destroy (class->pixbufs);
}


static void
mgicchikn_style_class_init (MgicChiknStyleClass * klass)
{
	GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

	style_parent_class = g_type_class_peek_parent (klass);

	style_class->render_icon = mgicchikn_render_icon;
	style_class->draw_shadow = mgicchikn_draw_shadow;
	style_class->draw_string = mgicchikn_draw_string;
	style_class->draw_hline = mgicchikn_draw_hline;
	style_class->draw_vline = mgicchikn_draw_vline;
	style_class->draw_flat_box = mgicchikn_draw_flat_box;
	style_class->draw_box = mgicchikn_draw_box;
	style_class->draw_shadow_gap = mgicchikn_draw_shadow_gap;
	style_class->draw_box_gap = mgicchikn_draw_box_gap;
	style_class->draw_extension = mgicchikn_draw_extension;
	style_class->draw_focus = mgicchikn_draw_focus;
	style_class->draw_handle = mgicchikn_draw_handle;
	style_class->draw_slider = mgicchikn_draw_slider;
	style_class->draw_layout = mgicchikn_draw_layout;
	style_class->draw_resize_grip = mgicchikn_draw_resize_grip;
	style_class->draw_check = mgicchikn_draw_check;
	style_class->draw_option = mgicchikn_draw_option;
}


static void
mgicchikn_style_init (MgicChiknStyle * style)
{
}


void
mgicchikn_style_register_type (GTypeModule * module)
{
	static const GTypeInfo info = {
		sizeof (MgicChiknStyleClass),
		(GBaseInitFunc) mgicchikn_style_base_init,
		(GBaseFinalizeFunc) mgicchikn_style_base_finalize,
		(GClassInitFunc) mgicchikn_style_class_init,
		NULL,
		NULL,
		sizeof (MgicChiknStyle),
		0,						/* n_preallocs */
		(GInstanceInitFunc) mgicchikn_style_init,
	};

	mgicchikn_style_type =
		g_type_module_register_type (module, GTK_TYPE_STYLE, "MgicChiknStyle", &info, 0);
}
