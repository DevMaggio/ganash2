/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * gdl-dock-item.c
 *
 * Author: Gustavo Giráldez <gustavo.giraldez@gmx.net>
 *         Naba Kumar  <naba@gnome.org>
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "gdl-dock.h"
#include "gdl-dock-frame.h"

/* ----- Private prototypes ----- */

static void  gdl_dock_frame_class_init	  (GdlDockFrameClass *class);
static void  gdl_dock_frame_init		  (GdlDockFrame *item);
//static void  gdl_dock_frame_realize		  (GtkWidget *item);
static void  gdl_dock_frame_draw		  (GtkWidget *item, cairo_t *cr);


static gpointer gdl_dock_frame_parent_class = NULL;

GType
gdl_dock_frame_get_type (void)
{
    static GType gtype = 0;

    if (G_UNLIKELY (gtype == 0)) {
        const GTypeInfo gtype_info = {
	    sizeof (GdlDockFrameClass),
	    NULL, /*(GBaseInitFunc) gdl_dock_frame_base_class_init, */
	    NULL,
	    (GClassInitFunc) gdl_dock_frame_class_init,
	    NULL,		/* class_finalize */
	    NULL,		/* class_data */
	    sizeof (GdlDockFrame),
	    0,		/* n_preallocs */
	    (GInstanceInitFunc) gdl_dock_frame_init,
	    NULL,		/* value_table */
        };

        gtype = g_type_register_static (GDL_TYPE_DOCK_ITEM,
                                        "GdlDockFrame",
                                        &gtype_info,
                                        0);

    }

    return gtype;
}


static void
gdl_dock_frame_class_init (GdlDockFrameClass *klass)
{
    GObjectClass       *object_class;
    GtkWidgetClass     *widget_class;
	
	object_class = G_OBJECT_CLASS (klass);
	widget_class = GTK_WIDGET_CLASS (klass);
	
    gdl_dock_frame_parent_class = g_type_class_peek_parent (klass);
	
//	widget_class->realize = gdl_dock_frame_realize;
	widget_class->draw    = gdl_dock_frame_draw;
}

static void
gdl_dock_frame_init (GdlDockFrame *item)
{
	
}


static void
gdl_dock_frame_draw (GtkWidget *item, cairo_t *cr)
{
	/*
	g_print("draw ---------------------------------\n");
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_rectangle(cr, 0, 0, 100, 100);
	cairo_fill(cr);
	*/
	GtkStyleContext *context;
	GtkAllocation allocation;
	/*static const gchar style[] =
	"* {\n"
		"padding: 0px;\n"
		"background-color: #FF00FF;\n"
	"}";*/
	
	gtk_widget_get_allocation(GTK_WIDGET(item), &allocation);
	context = gtk_widget_get_style_context(item);
	
	/*GtkCssProvider * css = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (css, style, -1, NULL);
	
	GdkScreen *screen = gdk_screen_get_default();
	gtk_style_context_add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);*/
	
	GtkStyle    *style = gtk_widget_get_style(item);
	GtkStateType state_type = GTK_STATE_PRELIGHT;
	const gchar *detail = "";//button
	/*
	gtk_paint_focus(style, cr, state_type, item, detail,
					allocation.x,
					allocation.y,
					allocation.width,
					allocation.height);
	*/
	gtk_render_background(context, cr, allocation.x, 0, allocation.width, allocation.height);

	/*
	gtk_render_frame(context,
							cr,
							allocation.x,
							allocation.y,
							allocation.width,
							allocation.height);
	*/
	GTK_WIDGET_CLASS(gdl_dock_frame_parent_class)->draw(item, cr);
}


/* ----- Public interface ----- */

/**
 * gdl_dock_frame_new:
 * @name: Unique name for identifying the dock object.
 * @long_name: Human readable name for the dock object.
 * @behavior: General behavior for the dock item (i.e. whether it can
 *            float, if it's locked, etc.), as specified by
 *            #GdlDockItemBehavior flags.
 *
 * Creates a new dock item widget.
 * Returns: The newly created dock item grip widget.
 **/
GtkWidget *
gdl_dock_frame_new (const gchar         *name,
                   const gchar         *long_name,
                   GdlDockItemBehavior  behavior)
{
    GdlDockFrame *item;

    item = GDL_DOCK_FRAME (g_object_new (GDL_TYPE_DOCK_FRAME,
                                        "name", name,
                                        "long-name", long_name,
                                        "behavior", behavior,
                                        NULL));
    gdl_dock_object_set_manual (GDL_DOCK_OBJECT (item));
    gtk_widget_show (GTK_WIDGET (item));

    return GTK_WIDGET (item);
}

/**
 * gdl_dock_frame_new_with_stock:
 * @name: Unique name for identifying the dock object.
 * @long_name: Human readable name for the dock object.
 * @stock_id: Stock icon for the dock object.
 * @behavior: General behavior for the dock item (i.e. whether it can
 *            float, if it's locked, etc.), as specified by
 *            #GdlDockItemBehavior flags.
 *
 * Creates a new dock item grip widget with a given stock id.
 * Returns: The newly created dock item grip widget.
 **/
GtkWidget *
gdl_dock_frame_new_with_stock (const gchar         *name,
                              const gchar         *long_name,
                              const gchar         *stock_id,
                              GdlDockItemBehavior  behavior)
{
	GdlDockFrame *item;

	item = GDL_DOCK_FRAME (g_object_new (GDL_TYPE_DOCK_FRAME,
                                        "name", name,
                                        "long-name", long_name,
                                        "stock-id", stock_id,
                                        "behavior", behavior,
                                        NULL));
   gdl_dock_object_set_manual (GDL_DOCK_OBJECT (item));

    return GTK_WIDGET (item);
}

/**
 * gdl_dock_frame_new_with_pixbuf_icon:
 * @name: Unique name for identifying the dock object.
 * @long_name: Human readable name for the dock object.
 * @pixbuf_icon: Pixbuf icon for the dock object.
 * @behavior: General behavior for the dock item (i.e. whether it can
 *            float, if it's locked, etc.), as specified by
 *            #GdlDockItemBehavior flags.
 *
 * Creates a new dock item grip widget with a given pixbuf icon.
 * Returns: The newly created dock item grip widget.
 *
 * Since: 3.3.2
 **/
GtkWidget *
gdl_dock_frame_new_with_pixbuf_icon (const gchar         *name,
                                    const gchar         *long_name,
                                    const GdkPixbuf     *pixbuf_icon,
                                    GdlDockItemBehavior  behavior)
{
	GdlDockFrame *item;

	item = GDL_DOCK_FRAME (g_object_new (GDL_TYPE_DOCK_FRAME,
                                        "name", name,
                                        "long-name", long_name,
                                        "pixbuf-icon", pixbuf_icon,
                                        "behavior", behavior,
                                        NULL));

    gdl_dock_object_set_manual (GDL_DOCK_OBJECT (item));
    gdl_dock_item_set_tablabel (GDL_DOCK_ITEM(item), gtk_label_new (long_name));
	gtk_widget_show (GTK_WIDGET (item));
	
    return GTK_WIDGET (item);
}
