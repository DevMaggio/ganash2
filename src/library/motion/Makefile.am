noinst_LTLIBRARIES = libmotion.la
libmotion_la_SOURCES  = \
    animator.cpp \
    engine.cpp \
    state.cpp \
    easing.cpp \
    abstract-animation.cpp \
    property.cpp \
    time-line.cpp

libmotion_la_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    -I$(top_srcdir)/src/library

libmotion_la_LIBADD = \
    $(GTK_LIBS)
