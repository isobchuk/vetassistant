/**
 * @file    format.hpp
 * @author  Ivan Sobchuk (i.a.sobchuk.1994@gmail.com)
 * @brief   The string literals formatter with compile-time
 *          checks and calculation.
 *          Please, check Readme for the details
 *
 * @version 1.0.0
 * @date 2023-09-12
 *
 * @copyright Ivan Sobchuk (c) 2023
 *
 * License Apache 2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

// C++ concepts should be enabled
static_assert((__cplusplus >= 201703L) && (__cpp_concepts), "Supported only with C++20 and newer!");

// Basic namespace to work with constant strings and formatting
namespace iso::string {

/**
 * @brief Concept to check that type is String
 *
 * @tparam S The type should be checked
 */
template <typename S>
concept const_string = requires(S) {
  typename S::StringT;
  S::string;
};

/**
 * @brief Trait to check that type is String
 *
 * @tparam T
 */
template <typename T, typename U = void> struct is_string {
  static constexpr auto value = false;
};
template <typename T> struct is_string<T, typename T::StringT::type> {
  static constexpr auto value = true;
};
template <typename T> inline constexpr auto is_string_v = is_string<T>::value;

// Contains some wrappers that is suggested as additional for the external users
namespace wrappers {
/**
 * @brief Struct that saves a string in array inside constexpr object
 */
template <const size_t N> struct Wrap {
  static constexpr auto size = N; // Size of the array
  char elems[N];                  // Array that contains string

  /**
   * @brief   Compile-time constructor that saves string in the array
   *
   * @param s Reference to an array (usually just const char[])
   */
  consteval Wrap(const char (&s)[N]) {
    size_t i = 0;
    while (i < N) {
      elems[i] = s[i];
      i++;
    }
  }

  /**
   * @brief     Concatenate the source string with the passed
   *
   * @tparam S  struct Wrap
   * @param s   object
   * @return    New consteval Wrap object
   */
  template <typename S> consteval auto operator+(const S s) const {
    char str[size - 1 + S::size];
    size_t i = 0;
    while (i < (size - 1)) {
      str[i] = elems[i];
      i++;
    }
    i = 0;
    while (i < S::size) {
      str[i + (size - 1)] = s.elems[i];
      i++;
    }
    return Wrap<size - 1 + S::size>(str);
  }
};
// Deduction guide for the Wrap
template <const size_t N> Wrap(char const (&)[N]) -> Wrap<N>;

/**
 * @brief Type that transform array from Wrap to the type property
 *
 */
template <const auto str> struct String {
  static constexpr auto &instance = str;     // Instance of Wrap
  static constexpr auto &string = str.elems; // Reference to an array
  struct StringT {
    using type = void;
  };

  /**
   * @brief   Concatenate the source string with the passed
   *
   * @tparam  S String type
   * @return  New consteval String object
   */
  template <const_string S> consteval auto operator+(const S) const { return String<instance + S::instance>{}; }

  /**
   * @brief   Returns raw pointer to an array
   *
   * @return  Pointer to char
   */
  consteval auto c_str() const { return string; }
};
} // namespace wrappers

/**
 * @brief   Inline variable that supposed to be used to create strings
 *
 * @example string<"This is string!">, constexpr auto my_str = string<"My string!!!">
 */
template <const wrappers::Wrap str> inline constexpr auto string = wrappers::String<str>{};

/**
 * @brief   Type for string
 */
template <const wrappers::Wrap str>
using String = wrappers::String<str>;

}
