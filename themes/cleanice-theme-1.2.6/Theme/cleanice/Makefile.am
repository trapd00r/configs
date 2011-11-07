metathemedir = $(datadir)/themes/CleanIce
metatheme_in_files = index.theme.in
metatheme_DATA = $(metatheme_in_files:.theme.in=.theme)

@INTLTOOL_THEME_RULE@

themedir = $(metathemedir)/gtk-2.0
theme_DATA = gtkrc 

mcthemedir = $(metathemedir)/metacity-1
mctheme_DATA = metacity-theme-1.xml

EXTRA_DIST = \
	$(metatheme_in_files) \
	$(metatheme_DATA) \
	$(mctheme_DATA) \
	$(theme_DATA)

CLEANFILES = $(metatheme_DATA)

