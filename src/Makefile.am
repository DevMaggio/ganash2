
bin_PROGRAMS = ganash panash
ganash_SOURCES = main.cpp
ganash_CPPFLAGS = $(AM_CPPFLAGS) \
                  $(GTK_CFLAGS) \
                  $(WEBKIT_CFLAGS) \
		  -I$(top_srcdir)/src/application \
		  -I$(top_srcdir)/src/library \
		  -DPACKAGE_PLUGIN_DIR=\"$(ganash_plugin_dir)\" \
		  -DPACKAGE_UI_DIR=\"$(ganash_ui_dir)\"

ganash_LDADD = $(GTK_LIBS) \
               $(WEBKIT_LIBS) \
                library/extension/libextension.la \
		$(top_builddir)/src/application/libapplication.la \
		$(top_builddir)/src/application/ui/libgui.la

ganash_LDFLAGS = -rpath $(pkglibdir)

#ganash_LDFLAGS =  -rdynamic

#  -rpath $(pkglibdir)

#AM_CPPFLAGS = -rdynamic

# $(top_builddir)
# $(top_srcdir)

panash_SOURCES = \
                 player.cpp \
                 $(top_srcdir)/src/application/player/player-application.cpp \
                 $(top_srcdir)/src/application/player/player-window.cpp


panash_CPPFLAGS = $(AM_CPPFLAGS) \
                  $(GTK_CFLAGS) \
                  $(WEBKIT_CFLAGS) \
                  $(XML_CFLAGS) \
                  -I$(top_srcdir)/src/application \
                  -I$(top_srcdir)/src/library

panash_LDADD = $(GTK_LIBS) \
               $(WEBKIT_LIBS) \
               $(XML_LIBS) \
               $(top_builddir)/src/library/svg/libsvg.la \
               $(top_builddir)/src/library/widget/libwidget.la \
               $(top_builddir)/src/library/display/libdisplay.la \
               $(top_builddir)/src/library/graphics/libgraphics.la \
               $(top_builddir)/src/library/motion/libmotion.la \
               $(top_builddir)/src/library/geom/libgeom.la \
               $(top_builddir)/src/library/math/libmath.la

panash_LDFLAGS = -rpath $(pkglibdir)

SUBDIRS = library \
	  application \
	  plugins

# Madon, normally you'd put shared libraries that binaries get linked to in libdir, not pkglibdir; pkglibdir would rather hold dlopen-able modules
# but still, you can try prog_LDFLAGS = -L $(pkglibdir) maybe?
# if you insist on shared libs in pkglibdir, be prepared to have to deal with RPATH weirdness, or having to play LD_LIBRARY_PATH games




# http://stackoverflow.com/questions/2272697/how-do-i-specify-in-a-makefile-am-script-that-i-only-want-to-compile-object-o-f

# http://www.flameeyes.eu/autotools-mythbuster/libtool/plugins.html
# http://www.openismus.com/documents/linux/using_libraries/using_libraries

# http://scentric.net/tutorial/treeview-tutorial.html
# http://www.gtk.org/tutorial1.2/gtk_tut-22.html
# http://developer.gnome.org/gtk-tutorial/2.24/x2200.html
