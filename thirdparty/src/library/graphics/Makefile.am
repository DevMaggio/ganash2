noinst_LTLIBRARIES = libgraphics.la
libgraphics_la_SOURCES  = \
    color.cpp \
    pen.cpp \
    brush.cpp \
    renderer.cpp \
    data-path.cpp

libgraphics_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libgraphics_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
