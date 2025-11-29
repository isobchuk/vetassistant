#pragma once

#include <concepts>

namespace gui
{

template<typename T>
concept Gui = requires(const T &gui)
{
    { gui.Initialize() } -> std::same_as<bool>;
    { gui.Stop() } -> std::same_as<bool>;
};

}