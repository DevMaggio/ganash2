noinst_LTLIBRARIES = libsvg.la
libsvg_la_SOURCES  = \
    parser.cpp \
    utils.cpp \
    template.cpp \
    element.cpp \
    rect-element.cpp \
    attribute.cpp \
    length.cpp

libsvg_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    $(XML_CFLAGS) \
    -I$(top_srcdir)/src/library

libsvg_la_LIBADD = \
    $(GTK_LIBS) \
    $(XML_LIBS)
