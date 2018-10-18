#include <gtkmm-2.4/gtkmm.h>
#include <cstring>
#include <valarray>

class MyDrawArea : public Gtk::DrawingArea
{
public:
    MyDrawArea(){}

protected:
    virtual bool on_expose_event( GdkEventExpose* e );
};

double f(double Vds) {
	return Vds * Vds * 10;
}


bool MyDrawArea::on_expose_event( GdkEventExpose* event )
{
    int width  = get_width();
    int height = get_height();
	double resolution = get_pango_context()->get_resolution();
	int i;
	double d, r;
	char s[50];

    Cairo::RefPtr< Cairo::Context > ctx = get_window()->create_cairo_context();

	ctx->set_source_rgb(1.0, 1.0, 1.0);
    ctx->paint();

	ctx->set_source_rgb(0.0, 0.0, 0.0);
    ctx->set_line_width( 1 );

	ctx->select_font_face("Serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
	ctx->set_font_size(10 * resolution / 72);


	for (i = 0; i <= 5; i++) {
		ctx->move_to(40, 20 + (540 / 5 * i));
		ctx->line_to(40 + 5, 20 + (540 / 5 * i));
		ctx->stroke();

		sprintf(s, "%3d", 50 * (5 - i));
		ctx->move_to(40 - 20, 20 + (540 / 5 * i) + 5);
		ctx->show_text(s);
	}

	for (i = 0; i <= 5; i++) {
		ctx->move_to(40 + (740 / 5 * i), 20 + 540 - 5);
		ctx->line_to(40 + (740 / 5 * i), 20 + 540);
		ctx->stroke();

		sprintf(s, "%d", i);
		ctx->move_to(40 + (740 / 5 * i) - 5, 20 + 540 + 15);
		ctx->show_text(s);
	}

	ctx->rectangle(40, 20, 740, 540);
	ctx->stroke();

	ctx->set_dash((std::valarray<double>){20.0, 10.0}, 0.0);
	ctx->rectangle(40, 20, 740, 540);
	ctx->clip();
	ctx->move_to(40, 20 + 540);
	for (i = 0; i < 5 * 100; i++) {
		d = i / 100.0;
		r = f(d);
		double px = 40 + (740 / 5.0 * d), py = 20 + 540 - (r * 540 / 250.0);
		ctx->line_to(px, py);
	}
	ctx->stroke();

	ctx->reset_clip();
	ctx->unset_dash();
	for (i = 0; i <= 5; i++) {
		d = i;
		r = f(d);
		double px = 40 + (740 / 5.0 * d), py = 20 + 540 - (r * 540 / 250.0);
		ctx->move_to(px, py - 16);
		ctx->line_to(px - 8 * 1.73, py + 8);
		ctx->line_to(px + 8 * 1.73, py + 8);
		ctx->close_path();
		auto *pth = ctx->copy_path();
		ctx->set_source_rgb(1.0, 1.0, 1.0);
		ctx->fill();
		ctx->append_path(*pth);
		ctx->set_source_rgb(0.0, 0.0, 0.0);
		ctx->stroke();
		ctx->arc(px, py, 3, 0, 6.28);
		ctx->fill();
	}

	ctx->save();
	ctx->move_to(40 - 10 - 20 + 5, 20 + 400);
	ctx->rotate(-0.5 * 3.142);
	ctx->show_text("ドレイン-ソース間電流(Id) [mA]");
	ctx->restore();
	ctx->move_to(300, 20 + 540 + 25);
	ctx->show_text("ドレイン-ソース間電圧(Vds) [V]");



    return true;
}


class MainWin : public Gtk::Window
{
    MyDrawArea m_drawarea;
public:
    MainWin(){
        add( m_drawarea );
        show_all_children();
    }
};
int main(int argc, char **argv) {
	// Gtk::Main kit( argc, argv );
	int argc2 = 1;
	char *argv2[] = {
		strdup("cygraph"),
		strdup("")
	};
	char **argv3 = argv2;
	Gtk::Main kit( argc2, argv3 );
    MainWin mainwin;
	mainwin.resize(800, 600);
    Gtk::Main::run( mainwin );
	return 0;
}


