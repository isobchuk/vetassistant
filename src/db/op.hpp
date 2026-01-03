#pragma once

#include "iso/string/string.hpp"

namespace db
{

template<typename T>
concept OpR = requires (const T& op)
{
  { op.Read(iso::string::string<"table">, iso::string::string<"id">, iso::string::string<"user">) } -> iso::string::const_string;
};

}