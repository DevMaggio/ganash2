noinst_LTLIBRARIES = libdom.la
libdom_la_SOURCES  = \
    document.cpp

libdom_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libdom_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
