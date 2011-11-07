/* eazel-theme-hacks.c -- override GtkWidgetClass methods

   Copyright (C) 1998 Randy Gordon, Integrand Systems
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

   $Id: eazel-theme-hacks.c,v 1.1.1.1 2002/01/18 21:39:57 seth Exp $

   Authors: Randy Gordon <randy@integrand.com>
	    John Harper <jsh@eazel.com>   */

#include "eazel-theme.h"

/* GTK+ sucks in places. This file contains dubious kludges to
   force it to do what we want. */


/* GtkRange code */
  /* The version of this method in gtkrange.c doesn't work
   * when the slider is as wide as the trough.
   */
/*
static gint
gtk_range_expose (GtkWidget *widget,
		  GdkEventExpose *event)
{
  GtkRange *range;

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
*/

/* GtkWidgetClass method-override framework */

typedef struct {
    GtkType (*get_type) (void);
    int offset;
    gpointer replacement;
    gpointer original;
} eazel_engine_class_hack;

static eazel_engine_class_hack class_hacks[] = { };

  /*  { gtk_range_get_type,
    G_STRUCT_OFFSET (GtkWidgetClass, expose_event),
    gtk_range_expose },

  { gtk_scale_get_type,
    G_STRUCT_OFFSET (GtkWidgetClass, expose_event),
    gtk_range_expose },

  { NULL }
  }; */

void
eazel_engine_install_hacks (void)
{
    eazel_engine_class_hack *hack;
    for (hack = class_hacks; hack->get_type != 0; hack++)
    {
	GtkWidgetClass *klass = gtk_type_class (hack->get_type ());
	hack->original = G_STRUCT_MEMBER (gpointer, klass, hack->offset);
	G_STRUCT_MEMBER (gpointer, klass, hack->offset) = hack->replacement;
    }
}

static void
restore_funcs (GtkObjectClass *klass,
	       int member_offset,
	       gpointer find_func,
	       gpointer replace_func)
{
    GList *child_list, *child;
    if (!GTK_IS_WIDGET_CLASS (klass))
	g_error ("Warning: restoring methods for non-widget");
    else
    {
	GtkWidgetClass *widget_klass = GTK_WIDGET_CLASS (klass);
	if (G_STRUCT_MEMBER (gpointer, widget_klass, member_offset) == find_func)
	    G_STRUCT_MEMBER (gpointer, widget_klass, member_offset) = replace_func;
    }
    /* FIXME GNOME2 child_list = gtk_type_children_types (klass->type); */
    for (child = child_list; child; child = child->next)
    {
	gpointer child_class = gtk_type_class (GPOINTER_TO_UINT (child->data));
	restore_funcs (GTK_OBJECT_CLASS (child_class),
		       member_offset, find_func, replace_func);
    }
}

void
eazel_engine_remove_hacks (void)
{
    eazel_engine_class_hack *hack;
    for (hack = class_hacks; hack->get_type != 0; hack++)
    {
	/* This is nasty: the methods we installed in init() may have
	   been copied into subclasses. */

	GtkWidgetClass *klass = gtk_type_class (hack->get_type ());
	restore_funcs (GTK_OBJECT_CLASS (klass), hack->offset,
		       hack->replacement, hack->original);
    }
}
