
void 
industrial_initialize_style (GtkStyleClass *klass,
			     GtkStyleClass *parent)
{
  parent_class = parent;	/* Save for later use */

  *klass = *parent;

  klass->draw_arrow = draw_arrow;
  klass->draw_tab = draw_tab;
  klass->draw_shadow = draw_shadow;
  klass->draw_box_gap = draw_box_gap;
  klass->draw_extension = draw_extension;
  klass->draw_handle = draw_handle;
  klass->draw_box = draw_box;
  klass->draw_check = draw_check;
  klass->draw_slider = draw_slider;
  klass->draw_option = draw_option;
  klass->draw_shadow_gap = draw_shadow_gap;
  klass->draw_hline = draw_hline;
  klass->draw_vline = draw_vline;
  klass->draw_focus = draw_focus;
}

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

static int
option_menu_get_indicator_width (GtkWidget      *widget)
{
  return 19;
}
