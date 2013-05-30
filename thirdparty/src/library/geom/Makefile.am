noinst_LTLIBRARIES = libgeom.la
libgeom_la_SOURCES  = \
    point.cpp \
    line.cpp \
    bezier.cpp \
    segment.cpp \
    rectangle.cpp

libgeom_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    -I$(top_srcdir)/src/library

libgeom_la_LIBADD = \
    $(GTK_LIBS)
