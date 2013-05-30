
pkglib_LTLIBRARIES = libplayer.la

pkginclude_HEADERS    = player-window.h
noinst_HEADERS        = player-window.h

libplayer_la_SOURCES  = player-window.cpp

libplayer_la_LDFLAGS  = -version 1:0:0

libplayer_la_CPPFLAGS = $(AM_CPPFLAGS) \
                        $(XML_CFLAGS) \
                        -I$(top_srcdir)/src/application \
                        -I$(top_srcdir)/src/library \
                        -DPACKAGE_PLUGIN_DIR=\"$(ganash_plugin_dir)\" \
                        -DPACKAGE_UI_DIR=\"$(ganash_ui_dir)\"

libplayer_la_LIBADD   = \
    $(XML_LIBS)
