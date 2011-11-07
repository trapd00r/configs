#define RADIO_SIZE 13
#define CHECK_SIZE 13

#define SCALE_SIZE 5

typedef enum {
  INDUSTRIAL_FIELDS_CONTRAST,
  INDUSTRIAL_FIELDS_CONTRAST_CENTER,
  INDUSTRIAL_FIELDS_ROUNDED_BUTTONS,
  INDUSTRIAL_FIELDS_WIDE
} IndustrialFields;

typedef struct 
{
  guint refcount;
  double contrast;
  double contrast_center;
  gboolean rounded_buttons;
  gboolean wide;
  IndustrialFields fields;
} IndustrialRcData;

typedef struct 
{
  GHashTable *shading_hash;

  double contrast;
  double contrast_center;
  gboolean rounded_buttons;
} IndustrialData;

void industrial_initialize_style (GtkStyleClass *klass,
				  GtkStyleClass *parent);
void industrial_shade (GdkColor * a, GdkColor * b, float k);
