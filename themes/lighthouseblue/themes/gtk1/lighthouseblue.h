#define SCALE_SIZE 5

typedef struct
{
  guint refcount;
  gboolean has_notebook_patch;
  gboolean combine_treeview_select;
  gboolean wide;
} LighthouseBlueRcData;

typedef struct
{
  GdkColor shade[8];
  GdkGC *shade_gc[8];
} LighthouseBlueData;

void lighthouseblue_initialize_style (GtkStyleClass *klass, GtkStyleClass *parent);
void lighthouseblue_shade (GdkColor * a, GdkColor * b, float k);

