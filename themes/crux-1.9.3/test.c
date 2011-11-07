
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <gnome.h>
#include <unistd.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
    GladeXML *xml;
    GtkWidget *window;
    /*
#if defined (HAVE_SETENV)
    setenv ("GTK_RC_FILES", DATADIR "/themes/Crux/gtk/gtkrc", 0);
    setenv ("GNOME_DISABLE_CRASH_DIALOG", "1", 0);
#elif defined (HAVE_PUTENV)
    putenv ("GTK_RC_FILES=" DATADIR "/themes/Crux/gtk/gtkrc");
    putenv ("GNOME_DISABLE_CRASH_DIALOG=1");
#else
# warning "Need either setenv or putenv, test program is probably broken"
#endif
    */
    gnome_init ("foo", "0", argc, argv);
    glade_gnome_init ();

    if (access ("./test.glade", R_OK) == 0)
	xml = glade_xml_new ("./test.glade", "window1", NULL);
    else if (access ("../test.glade", R_OK) == 0)
	xml = glade_xml_new ("../test.glade", "window1", NULL);
    else
    {
	g_error ("can't load test.glade");
	exit (1);
    }

    window = glade_xml_get_widget (xml, "window1");
    glade_xml_signal_autoconnect (xml);
    gtk_object_destroy (GTK_OBJECT (xml));
    gtk_widget_show_all (window);

    gtk_main ();
}
