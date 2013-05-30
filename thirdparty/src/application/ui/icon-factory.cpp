#include "icon-factory.h"
#include "stock.h"

#include <gtkmm/stockitem.h>
#include <gtkmm/stockid.h>
#include <gtkmm/stock.h>

#include <iostream>

namespace Ganash { namespace Ui {

class IconSet : public Gtk::IconSet
{
public:
    static Glib::RefPtr<Gtk::IconSet> create()
    {
        return Gtk::IconSet::create();
    }
    Glib::RefPtr<Gdk::Pixbuf> render_icon_pixbuf()
    {
        std::cout << "Render icon pixbuf" << std::endl;
        return Glib::RefPtr<Gdk::Pixbuf>();
    }
};

}}

Ganash::Ui::IconFactory::IconFactory() :
  Gtk::IconFactory()
{
  std::string path = "/home/sergio/Workspaces/Cpp/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/tools/";

  // Ink::Stock::SELECT
  Glib::RefPtr<Gtk::IconSet> icon_select = Gtk::IconSet::create();
  //icon_select->render_icon_pixbuf()
  Gtk::IconSource *source;
  source = new Gtk::IconSource();
  source->set_filename(path + "stock-tool-airbrush-16.png");
  source->set_size(Gtk::ICON_SIZE_SMALL_TOOLBAR);
  //source->set_size_wildcarded(false);
  icon_select->add_source(*source);

  source = new Gtk::IconSource();
  source->set_filename("/home/ganash/Workspace/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/tools/select.svg");
  source->set_size(Gtk::ICON_SIZE_LARGE_TOOLBAR);
  source->set_size_wildcarded(true);
  icon_select->add_source(*source);

  icon_select->add_source(create_source(path + "stock-tool-airbrush-22.png", Gtk::ICON_SIZE_BUTTON));
  icon_select->add_source(create_source(path + "stock-tool-airbrush-16.png", Gtk::ICON_SIZE_MENU));

  const Gtk::StockID stock_select(Ganash::Ui::Stock::SELECT);
  add(stock_select, icon_select);
  Gtk::Stock::add(Gtk::StockItem(stock_select, "Selection"));
  /*
  Gtk::ICON_SIZE_BUTTON;
  Gtk::ICON_SIZE_DIALOG;
  Gtk::ICON_SIZE_DND;
  Gtk::ICON_SIZE_INVALID;
  Gtk::ICON_SIZE_LARGE_TOOLBAR;
  Gtk::ICON_SIZE_MENU;
  Gtk::ICON_SIZE_SMALL_TOOLBAR;
  */


  //ganash-transform
  Glib::RefPtr<Gtk::IconSet> icon_transform = Gtk::IconSet::create();
  source = new Gtk::IconSource();
  source->set_filename(path + "stock-tool-align-16.png");
  source->set_size(Gtk::ICON_SIZE_SMALL_TOOLBAR);
  //source->set_size_wildcarded(false);
  icon_transform->add_source(*source);

  source = new Gtk::IconSource();
  source->set_filename("/home/ganash/Workspace/Gtk3/projects/ganash/thread/share/ganash/themes/Default/images/tools/manipulate.svg");
  source->set_size(Gtk::ICON_SIZE_LARGE_TOOLBAR);
  //source->set_size_wildcarded(false);
  icon_transform->add_source(*source);

  icon_transform->add_source(create_source(path + "stock-tool-align-22.png", Gtk::ICON_SIZE_BUTTON));
  icon_transform->add_source(create_source(path + "stock-tool-align-16.png", Gtk::ICON_SIZE_MENU));
  const Gtk::StockID stock_transform(Ganash::Ui::Stock::TRANSFORM);
  add(stock_transform, icon_transform);
  Gtk::Stock::add(Gtk::StockItem(stock_transform, "Transform"));

}

Ganash::Ui::IconFactory::~IconFactory()
{
}

Glib::RefPtr<Ganash::Ui::IconFactory> Ganash::Ui::IconFactory::create()
{
  return Glib::RefPtr<Ganash::Ui::IconFactory> (new Ganash::Ui::IconFactory());
}

const Gtk::IconSource Ganash::Ui::IconFactory::create_source(std::string filename, Gtk::BuiltinIconSize size)
{
  Gtk::IconSource source;
  try
  {
    //This throws an exception if the file is not found:
    source.set_pixbuf( Gdk::Pixbuf::create_from_file(filename) );
  }
  catch(const Glib::Exception& ex)
  {
    std::cout << ex.what() << std::endl;
    // return not found
  }

  source.set_size(size);
  source.set_size_wildcarded(false);//Icon may be scaled.

  return source;
}
