noinst_LTLIBRARIES = libdisplay.la
libdisplay_la_SOURCES  = \
    scene.cpp \
    graphics.cpp \
    object.cpp \
    container.cpp \
    rectangle.cpp \
    template.cpp \
    shape.cpp

libdisplay_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libdisplay_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
