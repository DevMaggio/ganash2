
noinst_LTLIBRARIES = libdialog.la
libdialog_la_SOURCES  = splash.cpp

libdialog_la_CPPFLAGS = $(AM_CPPFLAGS) \
			$(GTK_CFLAGS) \
			-DPACKAGE_IMG_DIR=\"$(ganash_image_dir)\"

libdialog_la_LIBADD = $(GTK_LIBS)
