plugindir = $(ganash_plugin_dir)

plugin_LTLIBRARIES = libwelcome.la
libwelcome_la_SOURCES = welcome.cpp
libwelcome_la_LDFLAGS = -no-undefined -module -avoid-version -version-info 1:0:0
libwelcome_la_CPPFLAGS = $(AM_CPPFLAGS) \
                         $(GTK_CFLAGS) \
                         $(GDL_CFLAGS) \
                         $(XML_CFLAGS) \
                         -I$(top_srcdir)/src/library \
			 -I$(top_srcdir)/src/application

libwelcome_la_LIBADD = $(GTK_LIBS) \
                       $(GDL_LIBS) \
                       $(XML_LIBS) \
                       $(top_builddir)/src/application/libapplication.la
