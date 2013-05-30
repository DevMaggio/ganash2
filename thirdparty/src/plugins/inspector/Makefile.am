plugindir = $(ganash_plugin_dir)

plugin_LTLIBRARIES = libinspector.la
libinspector_la_SOURCES = inspector.cpp
libinspector_la_LDFLAGS = -no-undefined -module -avoid-version -version-info 1:0:0
libinspector_la_CPPFLAGS = $(AM_CPPFLAGS) \
			  $(GTK_CFLAGS) \
                          $(GDL_CFLAGS) \
                          $(XML_CFLAGS) \
                          $(WEBKIT_CFLAGS) \
                          -I$(top_srcdir)/src/library \
			  -I$(top_srcdir)/src/application


libinspector_la_LIBADD = $(GTK_LIBS) \
                        $(GDL_LIBS) \
                        $(XML_LIBS) \
                        $(WEBKIT_LIBS) \
                        $(top_builddir)/src/application/libapplication.la
