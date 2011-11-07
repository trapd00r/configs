
static void
industrial_style_init_from_rc (GtkStyle * style,
			       GtkRcStyle * rc_style)
{
  IndustrialStyle *industrial_style = INDUSTRIAL_STYLE (style);
#if 0
  GdkColor *spot_color;
  double shades[] = {1.065, 0.963, 0.896, 0.85, 0.768, 0.665, 0.4, 0.205};
  int i;
  double contrast;
  double contrast_center;
#endif

  parent_class->init_from_rc (style, rc_style);

  industrial_style->contrast = INDUSTRIAL_RC_STYLE (rc_style)->contrast;
  industrial_style->contrast_center = INDUSTRIAL_RC_STYLE (rc_style)->contrast_center;
  industrial_style->rounded_buttons = INDUSTRIAL_RC_STYLE (rc_style)->rounded_buttons;

#if 0
  /* Lighter to darker */
  for (i = 0; i < 8; i++)
    shade (&style->bg[GTK_STATE_NORMAL], &industrial_style->gray[i], (shades[i]-contrast_center) * contrast + contrast_center);
  
  spot_color = industrial_get_spot_color (INDUSTRIAL_RC_STYLE (rc_style));

  industrial_style->spot_color = *spot_color;
  shade (&industrial_style->spot_color, &industrial_style->spot1, 1.62);
  shade (&industrial_style->spot_color, &industrial_style->spot2, 1.05);
  shade (&industrial_style->spot_color, &industrial_style->spot3, 0.72);
#endif
}

static void
industrial_style_init (IndustrialStyle * style)
{
  style->contrast = 1.0;
  style->contrast_center = 0.5;
  style->rounded_buttons = TRUE;
}

static void
industrial_style_class_init (IndustrialStyleClass * klass)
{
  GtkStyleClass *style_class = GTK_STYLE_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

#if 0
  style_class->realize = industrial_style_realize;
  style_class->unrealize = industrial_style_unrealize;
#endif
  style_class->init_from_rc = industrial_style_init_from_rc;

  /*
  style_class->draw_polygon = draw_polygon;
  style_class->draw_diamond = draw_diamond;
  style_class->draw_string = draw_string;
  */
#if 0
  style_class->draw_focus = draw_focus;
  style_class->draw_resize_grip = draw_resize_grip;
#endif
  style_class->draw_handle = draw_handle;
  style_class->draw_vline = draw_vline;
  style_class->draw_hline = draw_hline;
  style_class->draw_slider = draw_slider;
#if 0
  style_class->draw_tab = draw_tab;
  style_class->draw_arrow = industrial_draw_arrow;
#endif
  style_class->draw_check = draw_check;
  style_class->draw_box = draw_box;
  /*style_class->draw_flat_box = draw_flat_box;*/
  style_class->draw_shadow = draw_shadow;
  style_class->draw_box_gap = draw_box_gap;
  style_class->draw_shadow_gap = draw_shadow_gap;
  style_class->draw_extension = draw_extension;
  style_class->draw_option = draw_option;
}

GType industrial_type_style = 0;

void
industrial_style_register_type (GTypeModule * module)
{
  static const GTypeInfo object_info =
  {
    sizeof (IndustrialStyleClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) industrial_style_class_init,
    NULL,			/* class_finalize */
    NULL,			/* class_data */
    sizeof (IndustrialStyle),
    0,				/* n_preallocs */
    (GInstanceInitFunc) industrial_style_init,
    NULL
  };

  industrial_type_style = g_type_module_register_type (module,
						  GTK_TYPE_STYLE,
						  "IndustrialStyle",
						  &object_info, 0);
}

struct _GtkNotebookPage
{
  GtkWidget *child;
  GtkWidget *tab_label;
  GtkWidget *menu_label;
  GtkWidget *last_focus_child;	/* Last descendant of the page that had focus */

  guint default_menu : 1;	/* If true, we create the menu label ourself */
  guint default_tab  : 1;	/* If true, we create the tab label ourself */
  guint expand       : 1;
  guint fill         : 1;
  guint pack         : 1;

  GtkRequisition requisition;
  GtkAllocation allocation;

  guint mnemonic_activate_signal;
};


static inline gboolean
page_matches (GtkNotebookPage *page, int x, int y, int width, int height)
{
  return page &&
    page->allocation.x == x &&
    page->allocation.y == y &&
    page->allocation.width == width &&
    page->allocation.height == height;
}

static gboolean
check_page (GtkWidget *widget, 
	    int x, int y,
	    int width, int height)
{
  if (GTK_IS_NOTEBOOK (widget)) {
    GtkNotebook *notebook = GTK_NOTEBOOK (widget);
    GtkNotebookPage *page = NULL;
  
    if (notebook->children)
      page = notebook->children->data;
    
    if (!page_matches (page, x, y, width, height) &&
	!page_matches (notebook->cur_page, x, y, width, height)) {
      return TRUE;
    }
  }
  return FALSE;
}
  
static GtkRequisition default_option_indicator_size = { 7, 13 };
static GtkBorder default_option_indicator_spacing = { 7, 5, 2, 2 };

static int
option_menu_get_indicator_width (GtkWidget      *widget)
{
  GtkRequisition *tmp_size = NULL;
  GtkBorder *tmp_spacing = NULL;

  GtkRequisition indicator_size;
  GtkBorder      indicator_spacing;
  
  if (widget)
    gtk_widget_style_get (widget, 
			  "indicator_size", &tmp_size,
			  "indicator_spacing", &tmp_spacing,
			  NULL);

  if (tmp_size)
    {
      indicator_size = *tmp_size;
      g_free (tmp_size);
    }
  else
    indicator_size = default_option_indicator_size;

  if (tmp_spacing)
    {
      indicator_spacing = *tmp_spacing;
      g_free (tmp_spacing);
    }
  else
    indicator_spacing = default_option_indicator_spacing;

  return indicator_size.width + indicator_spacing.left + indicator_spacing.right;
}
