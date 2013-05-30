//$Id: welcome.cpp 2 2003-01-21 13:41:59Z maggio $ -*- c++ -*-

/**
 * This file is part of Ganash
 * 
 * Copyright (C) 2012  Sergio DE VASCONCELOS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "animator.h"
#include "application.h"
#include "ui/action-manager.h"
#include "ui/application-window.h"
#include "ui/stock.h"
#include "display/shape.h"
#include "motion/property.h"
#include "motion/animator.h"
#include "motion/state.h"
#include "widget/stage.h"
//#include "widget/shape.h"


#include "gdl/gdl-dock.h"
#include "gdl/gdl-dock-frame.h"
#include "gdl/gdl-dock-item.h"
#include "gdl/gdl-dock-object.h"
#include "gdl/gdl-dock-master.h"
#include "gdl/gdl-dock-layout.h"
#include "gdl/gdl-dock-item-grip.h"


#include <gtkmm.h>

#include <iostream>

Ganash::Plugin::Animator::Animator() :
  Ganash::Extension::PluginAbstract(),
  m_is_setup(false)
{
  m_name = std::string("org.ganash.plugin.InkWave");
  g_print("new Ganash::Plugin::Animator()\n");

}

Ganash::Plugin::Animator::~Animator()
{
}

bool Ganash::Plugin::Animator::init()
{

  Ganash::Ui::ActionManager *actionManager = Ganash::Ui::ActionManager::instance();
  Glib::RefPtr<Gtk::Action> actionAnimation = Gtk::Action::create("DisplayWorkbenchAnimation", Gtk::Stock::NEW, "Animation", "Display animation workbench");

  Glib::ustring ui_info_plugin =
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='DisplayMenu'>"
        "     <placeholder name='DisplayHolder'>"
        "      <menu action='DisplayWorkbench'>"
        "        <menuitem action='DisplayWorkbenchAnimation'/>"
        "      </menu>"
        "     </placeholder>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

  actionManager->m_refActionGroup->add(actionAnimation, sigc::mem_fun(*this, &Ganash::Plugin::Animator::setup));

  actionManager->m_refUIManager->add_ui_from_string(ui_info_plugin);


  g_print("Ganash::Plugin::Animator::init()\n");
  return true;
}


void Ganash::Plugin::Animator::setup()
{
   std::cout << "<Display>Workbench>Animation>" << std::endl;
   Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

   if(!m_is_setup)
     {
       setupUi();
     }

   std::string filename("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/src/plugins/animator/layout.xml");
   win->set_layout(filename);

}

void Ganash::Plugin::Animator::setupUi()
{
  Ganash::ApplicationWindow *win = Ganash::Application::get_main_window();

  GError *error = NULL;
  GdkPixbuf *pixbuf;
  GtkWidget *dockbar   = win->_dockbar->gobj();

  // ----

  Gtk::Toolbar *tools = new Gtk::Toolbar();
  //tools->get_style_context()->add_class();
  tools->set_property("orientation", Gtk::ORIENTATION_VERTICAL);
  tools->set_property("toolbar-style", Gtk::TOOLBAR_ICONS);
  //tools->set_property("icon-size", Gtk::ICON_SIZE_SMALL_TOOLBAR);
  tools->set_property("icon-size", Gtk::ICON_SIZE_LARGE_TOOLBAR);

  //Gtk::Image * image = new Gtk::Image("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/stock-cursor-24.png");
/*
  Gtk::ToolButton *cursor_tool = new Gtk::ToolButton();
  cursor_tool->set_icon_widget(*image);
  tools->insert(*cursor_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));
*/



/*
  image = new Gtk::Image("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/stock-cursor-16.png");
  Gtk::ToolButton *cursor2_tool = new Gtk::ToolButton("my Tooltips");
  cursor2_tool->set_icon_widget(*image);
  tools->insert(*cursor2_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));

  image = new Gtk::Image("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/tools/stock-tool-paintbrush-16.png");
  Gtk::ToolButton *cursor3_tool = new Gtk::ToolButton();
  cursor3_tool->set_icon_widget(*image);
  tools->insert(*cursor3_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));

  //image = new Gtk::Image("/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/tools/stock-tool-pencil-16.png");
  Gtk::ToolButton *cursor4_tool = new Gtk::ToolButton(Gtk::StockID("gtk-dialog-error"));
  //cursor4_tool->set_icon_widget(*image);
  tools->insert(*cursor4_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));*/

  Gtk::ToolButton *cursor5_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::SELECT));
  Gtk::ToolButton *cursor6_tool = new Gtk::ToolButton(Gtk::StockID(Ganash::Ui::Stock::TRANSFORM));
  tools->insert(*cursor5_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));
  tools->insert(*cursor6_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));

  //Gtk::IconFactory::add(Gtk::StockID, )
  //Gtk::ToolButton *cursor6_tool = new Gtk::ToolButton(Ganash::StockID(Ganash::Stock::ADD));
  //tools->insert(*cursor6_tool, 0, sigc::mem_fun(*this, &Ganash::Plugin::Animator::on_cursor));
  // ----


  GdlDockLayout * layout = gdl_dock_layout_new(G_OBJECT(dockbar));
  GdlDockMaster * master = GDL_DOCK_MASTER (gdl_dock_object_get_master (GDL_DOCK_OBJECT (dockbar)));
/*
  error = NULL;
  pixbuf = gdk_pixbuf_new_from_file("/home/sergio/Images/inkscape.logo.png", &error);
  GtkWidget * dockItemTools = gdl_dock_item_new_with_pixbuf_icon("tools", "", pixbuf, GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemTools), GTK_WIDGET(tools->gobj()));

  FIXME: This have a bug, when deleting placeold object
*/
  GtkWidget * dockItemTools = gdl_dock_item_new("tools", "", GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemTools), GTK_WIDGET(tools->gobj()));


  //                                                 Shape -> DisplayObject -> EventDispatcher -> Object
  // Sprite -> DisplayObjectContainer -> InteractiveObject -> DisplayObject -> EventDispatcher -> Object

  Ganash::Graphics::Brush *brush = new Ganash::Graphics::Brush();
  Ganash::Graphics::Color *bg = new Ganash::Graphics::Color(0.0, 1.0, 0.0, 0.5);
  brush->setColor(bg);
  brush->setStyle(Ganash::Graphics::Brush::PatternSolid);

  Ganash::Graphics::Pen *pen = new Ganash::Graphics::Pen();
  Ganash::Graphics::Color *fg = new Ganash::Graphics::Color(1.0, 0.0, 1.0);
  pen->setLineStyle(Ganash::Graphics::Pen::LineSolid);
  pen->setCapStyle(Ganash::Graphics::Pen::CapSquare);
  pen->setJoinStyle(Ganash::Graphics::Pen::JoinRound);
  pen->setColor(fg);

  Ganash::Display::Shape *shape = new Ganash::Display::Shape();
  Ganash::Graphics::DataPath data;

  data.moveTo(20.0, 20.0);
  data.lineTo(300.0, 20.0);
  data.lineTo(300.0, 180.0);
  data.lineTo(200.0, 180.0);
  data.cubicTo(200.0, 20.0, 20.0, 400.0, 20.0, 20.0);
  /*
  data.moveTo(20.0, 20.0);
  data.quadTo(20.0, 50.0, 40.0, 50.0);
  data.lineTo(70.0, 50.0);
  data.lineTo(90.0, 30.0);
  data.lineTo(90.0, 10.0);
  data.lineTo(60.0, 30.0);
  data.lineTo(40.0, 10.0);
  data.cubicTo(40.0, 30.0, 20.0, 0.0, 20.0, 20.0);
  */
  /*
  data.moveTo(75.5, 37.5);
  data.quadTo(112.5, 75.5, 75.5, 112.5);
  data.quadTo(37.5, 75.5, 75.5, 37.5);
  */
  /*
  data.moveTo(75.5, 37.5);
  data.lineTo(112.5, 75.5);
  data.lineTo(75.5, 112.5);
  data.lineTo(37.5, 75.5);
  data.lineTo(75.5, 37.5);
  */
  /*
  data.moveTo(50.5, 50.5);
  data.lineTo(75.5, 37.5);
  data.lineTo(100.5, 50.5);
  data.lineTo(112.5, 75.5);
  data.lineTo(100.5, 100.5);
  data.lineTo(75.5, 112.5);
  data.lineTo(50.5, 100.5);
  data.lineTo(37.5, 75.5);
  data.lineTo(50.5, 50.5);
  */
  /*
  data.moveTo(50.5, 50.5);
  data.lineTo(75.5, 25.5);
  data.lineTo(100.5, 50.5);
  data.lineTo(125.5, 75.5);
  data.lineTo(100.5, 100.5);
  data.lineTo(75.5, 125.5);
  data.lineTo(50.5, 100.5);
  data.lineTo(25.5, 75.5);
  data.lineTo(50.5, 50.5);
  */
  /*
  data.moveTo(50.5, 50.5);
  data.lineTo(100.5, 50.5);
  data.lineTo(100.5, 100.5);
  data.lineTo(50.5, 100.5);
  data.lineTo(50.5, 50.5);
  */

  shape->graphics.setData(data);
  shape->graphics.setPen(pen);
  shape->graphics.setBrush(brush);
  //shape.graphics.setPen(pen);
  //shape.graphics.setBrush(brush);
  //shape.graphics.moveTo(50.0, 50.0);
  //shape.graphics.moveTo(50.0, 50.0);
  //shape.graphics.lineTo(100.0, 50.0);
  //shape.graphics.lineTo(100.0, 100.0);
  //shape.graphics.lineTo(50.0, 100.0);
  //shape.graphics.lineTo(50.0, 50.0);
  //shape.graphics.render(&renderer);

  Ganash::Display::Scene *scene = new Ganash::Display::Scene();
  scene->add(shape);

  Ganash::Widget::Stage *stage = new Ganash::Widget::Stage();
  stage->setScene(scene);
  /*
  // Ganash Graphics Shape
  // ----------------------------------------------------------------

  Ganash::Graphics::Brush *brush = new Ganash::Graphics::Brush();
  Ganash::Graphics::Color *bg = new Ganash::Graphics::Color(0.0, 1.0, 0.0, 0.5);
  brush->setColor(bg);
  brush->setStyle(Ganash::Graphics::Brush::PatternSolid);

  Ganash::Graphics::Pen *pen = new Ganash::Graphics::Pen();
  Ganash::Graphics::Color *fg = new Ganash::Graphics::Color(1.0, 0.0, 1.0);
  pen->setLineStyle(Ganash::Graphics::Pen::LineSolid);
  pen->setCapStyle(Ganash::Graphics::Pen::CapSquare);
  pen->setJoinStyle(Ganash::Graphics::Pen::JoinRound);
  pen->setColor(fg);

  Ganash::Display::Shape *shape = new Ganash::Display::Shape();
  shape->graphics.setPen(pen);
  shape->graphics.setBrush(brush);

  shape->graphics.moveTo(0.5, 0.5);
  shape->graphics.lineTo(0.5, 100.5);
  shape->graphics.lineTo(100.5, 100.5);
  shape->graphics.lineTo(0.5, 0.5);

  Ganash::Display::Scene *scene = new Ganash::Display::Scene();
  scene->add(shape);// <-------------------------------------------------------


  // Ganash::Display::AbstractWidget
  // Ganash::Display::PathWidget
  // Ganash::Display::ShapeWidget
  // Ganash::Display::RectangleWidget
  // Ganash::Display::EllipseWidget

  // Construct a 1-second timeline with a frame range of 0 - 100
  Ganash::Motion::TimeLine *timeLine = new Ganash::Motion::TimeLine(1000);
  timeLine->setFrameRange(0, 100);
  timeLine->start();
  g_print("elapsed %d\n", timeLine->currentTime());
  timeLine->stop();

  Glib::Variant<guint> var1;
  Glib::Variant<Glib::ustring> var2;
  Glib::Variant<gboolean> var3;

  Ganash::Geom::Rectangle rect(0.0, 0.0, 100.0, 100.0);
  Glib::Variant<Ganash::Geom::Rectangle> var4 = Glib::Variant<Ganash::Geom::Rectangle>::create(rect);
  //std::cout << "var.h = " << var4.get().height();
  g_print("Hello %f\n", var4.get().height());

  //  Glib::Variant<Ganash::Geom::Rectangle> var5;
//  Ganash::Variant<Ganash::Geom::Rectangle> var5;

  //Ganash::Motion::Property motionProperty1 = Ganash::Motion::Property::Factory("geometry");
  Ganash::Motion::Property motionProperty1;//(shape, "geometry");
  motionProperty1.setName("geometry");
  motionProperty1.setTarget(*shape);
  motionProperty1.setDuration(3000);
  motionProperty1.setEasing(Ganash::Motion::Easing::CurveOutBounce);
  motionProperty1.setTimeLine(timeLine);

  motionProperty1.setStartValue(var4);
  //Glib::Variant<Ganash::Geom::Rectangle> var(Ganash::Geom::Rectangle(0.0, 0.0, 100.0, 30.0));
  Glib::Variant<Ganash::Geom::Rectangle> var = Glib::Variant<Ganash::Geom::Rectangle>::create(Ganash::Geom::Rectangle(0.0, 0.0, 100.0, 30.0));
  motionProperty1.setEndValue(var);

  motionProperty1.start();

  // Ganash::Motion::Transition motionTransition1;

  //scene
  //shape
  // Animation
  // AnimationGroup
  //   AnimationGroupSequential
  //   AnimationGroupParallel
  // AnimationProperty
  // Motion
  //   State
  //
  //
  //scene->add(shape);// <-------------------------------------------------------

/ *
  QPushButton button("Animated Button");
  button.show();

  Ganash::Graphics::PropertyAnimation animation(&button, "geometry");
  animation.setDuration(10000);
  animation.setEasingCurve(QtEasingCurve::OutBounce);

  animation.setStartValue(QRect(0, 0, 100, 30));
  animation.setEndValue(QRect(250, 250, 100, 30));

  animation.setKeyValueAt(0, QRect(0, 0, 100, 30));
  animation.setKeyValueAt(0.8, QRect(250, 250, 100, 30));
  animation.setKeyValueAt(1, QRect(0, 0, 100, 30));

  animation.start();
* /
  //connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
  // Clicking the push button will start the progress bar animation
  //pushButton = new QPushButton(tr("Start animation"), this);
  //connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));


  Ganash::Widget::Stage *stage = new Ganash::Widget::Stage();
  stage->setScene(scene);
  stage->show();

  _box.pack_start(*stage, Gtk::PACK_EXPAND_WIDGET, 0);

   */

  Ganash::Motion::TimeLine *timeLine = new Ganash::Motion::TimeLine(5000);// 5s
  timeLine->setFrameRange(0, 120);// 24i/s => 120i/5s
  //timeLine->start();
  //g_print("elapsed %d\n", timeLine->currentTime());
  //timeLine->stop();

  Ganash::Motion::Property motionProperty1;//(shape, "geometry");
  motionProperty1.setName("geometry");
  motionProperty1.setTarget(shape);
  motionProperty1.setDuration(3000);
  motionProperty1.setEasing(Ganash::Motion::Easing::CurveOutBounce);
  motionProperty1.setTimeLine(timeLine);
  //motionProperty1.setStartValue(...);
  //motionProperty1.setEndValue(...);
  motionProperty1.start();

  /*
  Ganash::Motion::Transition transion(beginState, endState);

  Ganash::Motion::Animator animator;
  animator.addTransition(transion);
  */
  //Ganash::Motion::State state;
  //Ganash::Motion::KeyFrame keyFrame;



  GtkWidget * dockItemDrawing = gdl_dock_frame_new("main", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemDrawing), GTK_WIDGET(stage->gobj()));



  GtkWidget * dockItemProperties = gdl_dock_item_new("properties", "", GDL_DOCK_ITEM_BEH_NORMAL);
  gtk_container_add(GTK_CONTAINER(dockItemProperties), gtk_label_new("properties"));

  GtkWidget * dockItemBottom = gdl_dock_item_new("bottom", "", GDL_DOCK_ITEM_BEH_NO_GRIP);
  gtk_container_add(GTK_CONTAINER(dockItemBottom), gtk_label_new("bottom"));

  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemTools), GDL_DOCK_LEFT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemDrawing), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemProperties), GDL_DOCK_RIGHT);
  gdl_dock_add_item(GDL_DOCK(dockbar), GDL_DOCK_ITEM(dockItemBottom), GDL_DOCK_RIGHT);

  gtk_widget_show_all(dockItemTools);
  gtk_widget_show_all(dockItemDrawing);
  gtk_widget_show_all(dockItemProperties);
  gtk_widget_show_all(dockItemBottom);

  m_is_setup = true;
}

void Ganash::Plugin::Animator::on_cursor()
{
  g_print("cursor clicked");
}

/*
Gtk::Widget * Ganash::ApplicationWindow::setupTool()
{
  // Ganash::Ui::ActionManager::instance();
}
*/

Ganash::Extension::PluginAbstract * getInstance(void)
{
  Ganash::Extension::PluginAbstract *plugin = new Ganash::Plugin::Animator();
  return plugin;
}
