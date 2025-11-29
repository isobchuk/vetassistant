#pragma once

#include <string>

#include "gui/gui.hpp"

namespace gui::qt
{

class UserInterface
{
    public:
        UserInterface(const ::std::string &fl);

        bool Initialize() const;
        bool Stop() const;
    
    private:
        const ::std::string &qml_file;
        
        static_assert(::gui::Gui<UserInterface>, "The UserInterface class should implement a whole concept interface!");
};


}