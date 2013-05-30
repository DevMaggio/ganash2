noinst_LTLIBRARIES = libextension.la
libextension_la_SOURCES  = plugin-abstract.cpp \
                           plugin-interface.h \
                           plugin-loader.cpp \
                           plugin-manager.cpp \
                           thread-manager.cpp \
                           thread-abstract.cpp

libextension_la_CPPFLAGS = $(AM_CPPFLAGS) \
			   $(GTK_CFLAGS) \
			   -I$(top_srcdir)/src/library

libextension_la_LIBADD = $(GTK_LIBS)
