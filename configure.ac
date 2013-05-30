#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT(ganash, 0.1, dev.maggio@mail.com)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h:config.in])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB

AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T

#AM_PROG_LIBTOOL
LT_INIT

# Checks for libraries.

PKG_CHECK_MODULES(GTK, gtkmm-3.0 >= 3.4, with_gtkmm_3_0=yes, with_gtkmm_3_0=no)
AC_SUBST(GTK_CPPFLAGS)
AC_SUBST(GTK_LIBS)

AC_ARG_WITH(shared-gdl,
	AC_HELP_STRING([--with-shared-gdl], [compiling with the GDL library installed]),
	[with_shared_gdl=yes], [with_shared_gdl=no])

gdl_linked='static'
if test "x$with_shared_gdl" = "xno"; then
    AC_DEFINE(GDL_CFLAGS,"",[C compiler flags for GDL])
    AC_DEFINE(GDL_LIBS, "", [linker flags for GDL])
    AC_SUBST(GDL_CFLAGS, "-I\$(top_builddir)/thirdparty/include/libgdl-3.0")
    AC_SUBST(GDL_LIBS, "\$(top_builddir)/thirdparty/lib/libgdl-3.la")
else
    AC_MSG_ERROR([OPTION NOT SUPPORTED --with-shared-gdl: probleme de GDL_VERSION])
    PKG_CHECK_MODULES(GDL, gdl-3.0)
    AC_SUBST(GDL_CFLAGS)
    AC_SUBST(GDL_LIBS)
    gdl_linked='shared'
fi


PKG_CHECK_MODULES(XML, libxml-2.0 >= 2.6, with_xml=yes, with_xml=no)
AC_SUBST(XML_CFLAGS)
AC_SUBST(XML_LIBS)

#PKG_CHECK_MODULES(WEBKIT, libwebkit-3.0 >= 3.1, with_webkit=yes, with_webkit=no)
AC_SUBST(WEBKIT_CFLAGS, "-I\$(top_builddir)/thirdparty/include/webkitgtk-3.0 -I/usr/include/libsoup-2.4")
AC_SUBST(WEBKIT_LIBS, "\$(top_builddir)/thirdparty/lib/libwebkitgtk-3.0.la \$(top_builddir)/thirdparty/lib/libjavascriptcoregtk-3.0.la")


# Setup Plugin directories
# ------------------------
ganash_plugin_dir='$(libdir)/$(PACKAGE)/plugins'
ganash_data_dir='$(datadir)/$(PACKAGE)'
ganash_ui_dir='$(datadir)/$(PACKAGE)/ui'
ganash_image_dir='$(datadir)/$(PACKAGE)/pixmap'
AC_SUBST(ganash_plugin_dir)
AC_SUBST(ganash_data_dir)
AC_SUBST(ganash_ui_dir)
AC_SUBST(ganash_image_dir)


# Checks for header files.
AC_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS(memset)

#AC_CONFIG_FILES([Makefile
#                 src/Makefile])
#AC_OUTPUT

AC_OUTPUT([Makefile
                 src/Makefile
                 src/library/Makefile
                 src/library/core/Makefile
                 src/library/extension/Makefile
                 src/library/display/Makefile
                 src/library/graphics/Makefile
                 src/library/widget/Makefile
                 src/library/geom/Makefile
                 src/library/math/Makefile
                 src/library/motion/Makefile
                 src/library/xml/Makefile
                 src/library/dom/Makefile
                 src/library/svg/Makefile
                 src/plugins/Makefile
		 src/plugins/welcome/Makefile
		 src/plugins/inkscape/Makefile
		 src/plugins/animator/Makefile
                 src/plugins/inspector/Makefile
		 src/application/Makefile
		 src/application/ui/Makefile
		 src/application/ui/dialogs/Makefile
                 share/ganash/ui/Makefile
                 share/ganash/pixmap/Makefile
                 tests/Makefile
                 tests/library/Makefile
                 tests/library/geom/Makefile])

echo "
Configuration:
        sources                : ${srcdir}
        prefix                 : ${prefix}
        gtkmm                  : ${with_gtkmm_3_0}
        gdl                    : ${gdl_linked}
"
