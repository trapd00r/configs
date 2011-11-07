/* Industrial Engine
 * Copyright (C) 2001 Red Hat, Inc.
 * Copyright (C) 2002 Ximian, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Written by Owen Taylor <otaylor@redhat.com>
 * modified by Alexander Larsson <alexl@redhat.com>
 * modified by Christopher Lahey <clahey@ximian.com>
 */
#include <gtk/gtkstyle.h>

typedef struct _IndustrialStyle IndustrialStyle;
typedef struct _IndustrialStyleClass IndustrialStyleClass;

extern GType industrial_type_style;

#define INDUSTRIAL_TYPE_STYLE              industrial_type_style
#define INDUSTRIAL_STYLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), INDUSTRIAL_TYPE_STYLE, IndustrialStyle))
#define INDUSTRIAL_STYLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), INDUSTRIAL_TYPE_STYLE, IndustrialStyleClass))
#define INDUSTRIAL_IS_STYLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), INDUSTRIAL_TYPE_STYLE))
#define INDUSTRIAL_IS_STYLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), INDUSTRIAL_TYPE_STYLE))
#define INDUSTRIAL_STYLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), INDUSTRIAL_TYPE_STYLE, IndustrialStyleClass))

struct _IndustrialStyle
{
  GtkStyle parent_instance;

  double contrast;
  double contrast_center;
  gboolean rounded_buttons;

  /* from light to dark */
  GHashTable *shading_hash; /* Of type Shading */
};

struct _IndustrialStyleClass
{
  GtkStyleClass parent_class;
};

void industrial_style_register_type (GTypeModule *module);
