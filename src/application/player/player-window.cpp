#include "geom/rectangle.h"
#include "display/shape.h"
#include "svg/parser.h"
#include "svg/template.h"
#include "display/template.h"
#include "motion/time-line.h"
#include "motion/property.h"
#include "motion/easing.h"

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlstring.h>
#include <string.h>


static void
test()
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile("/home/ganash/Workspace/Gtk3/projects/ganash/thread/share/ganash/pixmap/test.svg", NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file\n");
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    Ganash::Svg::Parser parser;
    Ganash::Display::Template *tpl = new Ganash::Display::Template();
    parser.setTemplate(tpl);
    parser.parse(root_element);
    //print_element_names(root_element);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}



#include "player-window.h"
#include "widget/stage.h"
#include "display/scene.h"
#include "display/shape.h"

#include <gtkmm/label.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/stock.h>

Ganash::PlayerWindow::PlayerWindow() :
  Gtk::ApplicationWindow(),
  _box(Gtk::ORIENTATION_VERTICAL, 0)
{
  set_title("Panash - Document.svg");
  set_default_size(200, 200);

  setup();
  test();

  add(_box);
}

Ganash::PlayerWindow::~PlayerWindow()
{
}

void Ganash::PlayerWindow::on_my_clicked()
{
    g_print("on my clicked\n");
}

void Ganash::PlayerWindow::setup()
{
  Gtk::Toolbar *toolbar = new Gtk::Toolbar();
  //toolbar->set_property("toolbar-style", Gtk::TOOLBAR_BOTH_HORIZ);
  toolbar->set_property("toolbar-style", Gtk::TOOLBAR_BOTH);
  toolbar->get_style_context()->add_class("primary-toolbar");

  Gtk::ToolButton *tool_back = new Gtk::ToolButton(Gtk::StockID(Gtk::Stock::GO_BACK));
  toolbar->insert(*tool_back, -1);

  Gtk::ToolButton *tool_prev = new Gtk::ToolButton(Gtk::StockID(Gtk::Stock::GOTO_FIRST));
  toolbar->insert(*tool_prev, -1);

  Gtk::ToolButton *tool_play = new Gtk::ToolButton(Gtk::StockID(Gtk::Stock::MEDIA_PLAY));// JUMP_TO
  toolbar->insert(*tool_play, -1);
  tool_play->signal_clicked().connect(sigc::mem_fun(*this, &Ganash::PlayerWindow::on_my_clicked));

  Gtk::ToolButton *tool_next = new Gtk::ToolButton(Gtk::StockID(Gtk::Stock::GOTO_LAST));
  toolbar->insert(*tool_next, -1);

  Gtk::ToolButton *tool_forward = new Gtk::ToolButton(Gtk::StockID(Gtk::Stock::GO_FORWARD));
  toolbar->insert(*tool_forward, -1);

  _box.pack_start(*toolbar, Gtk::PACK_START, 0);


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
  motionProperty1.setTarget(shape);
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

/*
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
*/
  //connect(timeLine, SIGNAL(frameChanged(int)), progressBar, SLOT(setValue(int)));
  // Clicking the push button will start the progress bar animation
  //pushButton = new QPushButton(tr("Start animation"), this);
  //connect(pushButton, SIGNAL(clicked()), timeLine, SLOT(start()));


  Ganash::Widget::Stage *stage = new Ganash::Widget::Stage();
  stage->setScene(scene);
  stage->show();

  _box.pack_start(*stage, Gtk::PACK_EXPAND_WIDGET, 0);
}
