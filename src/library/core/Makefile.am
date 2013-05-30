noinst_LTLIBRARIES = libcore.la
libcore_la_SOURCES  = \
    action.cpp \
    command.cpp \
    dock-manager.cpp \
    action-manager.cpp \
    action-container.cpp

libcore_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libcore_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
