#pragma once

#include <concepts>

#include "iso/string/string.hpp"

namespace db
{

template<typename T>
concept DbR = requires(T &db)
{
    typename T::Cell;
    typename T::Row;
    typename T::Table;

    { db.Connect() } -> std::convertible_to<bool>;
    { db.Read(iso::string::string<"SELECT id, name FROM table;">) } -> std::convertible_to<typename T::Table>;
};

}