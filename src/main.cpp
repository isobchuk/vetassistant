#include "opts.hpp"

#include <gui/qt/gui.hpp>

int main(int argc, char *argv[])
{
    const auto opts(vetassistant::Opts::Parse(argc, argv));
    
    const gui::qt::UserInterface user_interface(opts.qml_file);
    
    user_interface.Initialize();

    return 0;
}