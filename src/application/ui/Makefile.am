
pkglib_LTLIBRARIES = libgui.la

pkginclude_HEADERS        = application-window.h
noinst_HEADERS            = application-window.h

libgui_la_SOURCES  = application-window.cpp \
                     action-manager.cpp \
                     action-container.cpp \
                     icon-factory.cpp \
		     stock.cpp

libgui_la_LDFLAGS  = -version 1:0:0

libgui_la_CPPFLAGS = $(AM_CPPFLAGS) \
			     $(GTK_CFLAGS) \
			     $(GDL_CFLAGS) \
                             $(XML_CFLAGS) \
                             -I$(top_srcdir)/src/application \
			     -I$(top_srcdir)/src/library \
			     -DPACKAGE_PLUGIN_DIR=\"$(ganash_plugin_dir)\" \
			     -DPACKAGE_UI_DIR=\"$(ganash_ui_dir)\"

libgui_la_LIBADD = $(GTK_LIBS) \
		   $(GDL_LIBS) \
                   $(XML_LIBS) \
		   $(top_builddir)/src/application/ui/dialogs/libdialog.la \
                   $(top_builddir)/src/library/core/libcore.la \
                   $(top_builddir)/src/library/widget/libwidget.la \
                   $(top_builddir)/src/library/display/libdisplay.la \
                   $(top_builddir)/src/library/graphics/libgraphics.la \
                   $(top_builddir)/src/library/motion/libmotion.la \
                   $(top_builddir)/src/library/math/libmath.la \
                   $(top_builddir)/src/library/geom/libgeom.la

SUBDIRS = dialogs
