#pragma once

#include <concepts>

namespace gui
{

template<typename T>
concept Gui = requires(const T &gui)
{
    { gui.Initialize(*new std::vector<std::vector<std::string>>) } -> std::same_as<bool>;
    { gui.Start() } -> std::same_as<bool>;
    { gui.Stop() } -> std::same_as<bool>;
    { gui.Update() } -> std::same_as<bool>;
};

}