/* Industrial theme engine
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
 * modified by Christopher James Lahey <clahey@ximian.com>
 */

#include "industrial_style.h"
#include "industrial_rc_style.h"

static GtkRcStyleClass *parent_class;

GType industrial_type_rc_style = 0;

static void
industrial_rc_style_init (IndustrialRcStyle *industrial_rc)
{
  industrial_rc->contrast = 1.0;
  industrial_rc->contrast_center = 0.5;
  industrial_rc->rounded_buttons = TRUE;
  industrial_rc->wide = FALSE;
  industrial_rc->fields = 0;
}

/* Create an empty style suitable to this RC style
 */
static GtkStyle *
industrial_rc_style_create_style (GtkRcStyle *rc_style)
{
  return GTK_STYLE (g_object_new (INDUSTRIAL_TYPE_STYLE, NULL));
}

#include "parse_rc_style.h"

static guint
industrial_rc_style_parse (GtkRcStyle *rc_style,
			   GtkSettings  *settings,
			   GScanner   *scanner)
{
  IndustrialRcStyle *industrial_rc = INDUSTRIAL_RC_STYLE (rc_style);
  return parse_rc_style (scanner, &industrial_rc->contrast, &industrial_rc->contrast_center, &industrial_rc->rounded_buttons, &industrial_rc->wide, &industrial_rc->fields);
}

static void
industrial_rc_style_merge (GtkRcStyle *dest,
			   GtkRcStyle *src)
{
  IndustrialRcStyle *dest_w, *src_w;
  IndustrialFields fields;
  
  parent_class->merge (dest, src);

  if (!INDUSTRIAL_IS_RC_STYLE (src))
    return;
  
  src_w = INDUSTRIAL_RC_STYLE (src);
  dest_w = INDUSTRIAL_RC_STYLE (dest);

  fields = (~dest_w->fields) & src_w->fields;

  if (fields & INDUSTRIAL_FIELDS_CONTRAST)
    dest_w->contrast = src_w->contrast;
  if (fields & INDUSTRIAL_FIELDS_CONTRAST_CENTER)
    dest_w->contrast_center = src_w->contrast_center;
  if (fields & INDUSTRIAL_FIELDS_ROUNDED_BUTTONS)
    dest_w->rounded_buttons = src_w->rounded_buttons;
  if (fields & INDUSTRIAL_FIELDS_WIDE)
    dest_w->wide = src_w->wide;

  dest_w->fields = dest_w->fields | src_w->fields;
}

static void
industrial_rc_style_class_init (IndustrialRcStyleClass *klass)
{
  GtkRcStyleClass *rc_style_class = GTK_RC_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  rc_style_class->create_style = industrial_rc_style_create_style;
  rc_style_class->parse = industrial_rc_style_parse;
  rc_style_class->merge = industrial_rc_style_merge;
}

void
industrial_rc_style_register_type (GTypeModule *module)
{
  static const GTypeInfo object_info =
  {
    sizeof (IndustrialRcStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) industrial_rc_style_class_init,
    NULL,           /* class_finalize */
    NULL,           /* class_data */
    sizeof (IndustrialRcStyle),
    0,              /* n_preallocs */
    (GInstanceInitFunc) industrial_rc_style_init,
    NULL
  };
  
  industrial_type_rc_style = g_type_module_register_type (module,
						     GTK_TYPE_RC_STYLE,
						     "IndustrialRcStyle",
						     &object_info, 0);
}
