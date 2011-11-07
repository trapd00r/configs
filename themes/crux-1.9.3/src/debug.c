#include "debug.h"

#include <glib/glist.h>
#include <glib/gmessages.h>

#include <signal.h>
#include <stdio.h>

/* Raise a SIGINT signal to get the attention of the debugger.
 * When not running under the debugger, we don't want to stop,
 * so we ignore the signal for just the moment that we raise it.
 */
void
stop_in_debugger (void)
{
        void (* saved_handler) (int);

        saved_handler = signal (SIGINT, SIG_IGN);
        raise (SIGINT);
        signal (SIGINT, saved_handler);
}

/* Stop in the debugger after running the default log handler.
 * This makes certain kinds of messages stop in the debugger
 * without making them fatal (you can continue).
 */
static void
log_handler (const char *domain,
	     GLogLevelFlags level,
	     const char *message,
	     gpointer data)
{
	g_log_default_handler (domain, level, message, data);
	if ((level & (G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING)) != 0) {
		stop_in_debugger ();
	}
}

static void
set_log_handler (const char *domain)
{
	g_log_set_handler (domain, G_LOG_LEVEL_MASK, log_handler, NULL);
}

void
make_warnings_and_criticals_stop_in_debugger (void)
{
	guint i;

	/* This is a workaround for the fact that there is not way to 
	 * make this useful debugging feature happen for ALL domains.
	 *
	 * What we did here is list all the ones we could think of that
	 * were interesting to us. It's OK to add more to the list.
	 */
	static const char * const standard_log_domains[] = {
		"",
		"Bonobo",
		"BonoboUI",
		"Echo",
		"Eel",
		"GConf",
		"GConf-Backends",
		"GConf-Tests",
		"GConfEd",
		"GLib",
		"GLib-GObject",
		"GModule",
		"GThread",
		"Gdk",
		"Gdk-Pixbuf",
		"GdkPixbuf",
		"Glib",
		"Gnome",
		"GnomeCanvas",
		"GnomePrint",
		"GnomeUI",
		"GnomeVFS",
		"GnomeVFS-CORBA",
		"GnomeVFS-pthread",
		"GnomeVFSMonikers",
		"Gtk",
		"Nautilus",
		"Nautilus-Adapter",
		"Nautilus-Authenticate",
		"Nautilus-Hardware"
		"Nautilus-Mozilla",
		"Nautilus-Music",
		"Nautilus-Notes",
		"Nautilus-Sample",
		"Nautilus-Test",
		"Nautilus-Text",
		"Nautilus-Throbber",
		"Nautilus-Throbber-Control",
		"Nautilus-Tree",
		"NautilusErrorDialog",
		"ORBit",
		"ZVT",
		"libIDL",
		"libgconf-scm",
		"libglade",
		"libgnomevfs",
		"librsvg",
	};

	for (i = 0; i < G_N_ELEMENTS (standard_log_domains); i++) {
		set_log_handler (standard_log_domains[i]);
	}
}
