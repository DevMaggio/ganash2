noinst_LTLIBRARIES = libwidget.la
libwidget_la_SOURCES  = \
    stage.cpp
#    display.cpp
#    shape.cpp

libwidget_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libwidget_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
