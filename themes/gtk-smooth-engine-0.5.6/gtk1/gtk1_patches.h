#ifndef GTK1_PATCHES_H
#define	GTK1_PATCHES_H

enum {
	PATCH_SCROLLBAR		= 0x0001,
	PATCH_SCALE			= 0x0002,
	PATCH_PANED			= 0x0010,
	PATCH_SPIN_BUTTON		= 0x0020,
	PATCH_CHECK_BUTTON		= 0x0030,
	PATCH_MENU_ITEM			= 0x0040,
	PATCH_SCROLLED_WINDOW	= 0x0100,
	
	PATCH_DEFAULT			= 0x01FF,
	PATCH_ALL				= 0x01FF
};

extern guint16 patch_config;

void	patches_install ();
void	patches_uninstall ();
 
#endif /* GTK1_PATCHES_H */
