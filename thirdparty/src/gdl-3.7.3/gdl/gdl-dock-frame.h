/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * gdl-dock-item.h
 *
 * Author: Gustavo Giráldez <gustavo.giraldez@gmx.net>
 *
 * Based on GnomeDockItem/BonoboDockItem.  Original copyright notice follows.
 *
 * Copyright (C) 1998 Ettore Perazzoli
 * Copyright (C) 1998 Elliot Lee
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GDL_DOCK_FRAME_H__
#define __GDL_DOCK_FRAME_H__

#include <gdl/gdl-dock-item.h>

G_BEGIN_DECLS

/* standard macros */
#define GDL_TYPE_DOCK_FRAME            (gdl_dock_frame_get_type ())
#define GDL_DOCK_FRAME(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDL_TYPE_DOCK_FRAME, GdlDockFrame))
#define GDL_DOCK_FRAME_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GDL_TYPE_DOCK_FRAME, GdlDockFrameClass))
#define GDL_IS_DOCK_FRAME(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDL_TYPE_DOCK_FRAME))
#define GDL_IS_DOCK_FRAME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GDL_TYPE_DOCK_FRAME))
#define GDL_DOCK_FRAME_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_DOCK_FRAME, GdlDockFrameClass))


typedef struct _GdlDockFrame             GdlDockFrame;
typedef struct _GdlDockFrameClass        GdlDockFrameClass;

struct _GdlDockFrame {
	GdlDockItem        object;

};

struct _GdlDockFrameClass {
	GdlDockItemClass  parent_class;
};

/* public interface */

GtkWidget     *gdl_dock_frame_new                   (const gchar         *name,
                                                    const gchar         *long_name,
                                                    GdlDockItemBehavior  behavior);
GtkWidget     *gdl_dock_frame_new_with_stock        (const gchar         *name,
                                                    const gchar         *long_name,
                                                    const gchar         *stock_id,
                                                    GdlDockItemBehavior  behavior);

GtkWidget     *gdl_dock_frame_new_with_pixbuf_icon  (const gchar      *name,
                                                    const gchar      *long_name,
                                                    const GdkPixbuf  *pixbuf_icon,
                                                    GdlDockItemBehavior  behavior);
G_END_DECLS

#endif
