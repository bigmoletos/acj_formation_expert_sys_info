#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main() {
    Fl_Window *window = new Fl_Window(340, 180, "FLTK Window");
    window->end();
    window->show();
    return Fl::run();
}
