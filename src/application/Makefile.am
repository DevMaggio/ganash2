
noinst_LTLIBRARIES = libapplication.la

libapplication_la_SOURCES  = application.cpp \
			     bootstrap.cpp

libapplication_la_CPPFLAGS = $(AM_CPPFLAGS) \
			     $(GTK_CFLAGS) \
                             $(GDL_CFLAGS) \
                             $(XML_CFLAGS) \
                             -I$(top_srcdir)/src/application \
			     -I$(top_srcdir)/src/library \
			     -DPACKAGE_PLUGIN_DIR=\"$(ganash_plugin_dir)\" \
			     -DPACKAGE_UI_DIR=\"$(ganash_ui_dir)\"

libapplication_la_LIBADD = $(GTK_LIBS) \
                           $(XML_LIBS) \
                           $(top_builddir)/src/library/extension/libextension.la



SUBDIRS = \
    ui
