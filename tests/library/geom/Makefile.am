TESTS = test-geom
check_PROGRAMS = test-geom
test_geom_SOURCES  = \
    test-suite.cpp

test_geom_CPPFLAGS = \
    $(AM_CPPFLAGS) \
    $(GTK_CFLAGS) \
    -I$(top_srcdir)/src/library

test_geom_LDADD = \
    $(GTK_LIBS) \
    $(top_builddir)/src/library/geom/libgeom.la \
    $(top_builddir)/src/library/math/libmath.la
