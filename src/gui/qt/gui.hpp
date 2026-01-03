#pragma once

#include <string>
#include <vector>

#include "gui/gui.hpp"

namespace gui::qt
{

class UserInterface
{
    public:
        UserInterface(const ::std::string &fl, const ::std::string &s_p);

        bool Initialize(const std::vector<std::vector<std::string>> &staff) const;
        bool Start() const;
        bool Stop() const;
        bool Update() const;
    
    private:
        const ::std::string &qml_file;
        const ::std::string &image_staff_path;
        
        static_assert(::gui::Gui<UserInterface>, "The UserInterface class should implement a whole concept interface!");
};


}