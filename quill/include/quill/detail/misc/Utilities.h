/**
 * Copyright(c) 2020-present, Odysseas Georgoudis & quill contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */

#pragma once

#include "quill/detail/misc/Attributes.h"
#include <array>
#include <cassert>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

namespace quill
{
namespace detail
{
/**
 * Check if a number is a power of 2
 * @param number the number to check against
 * @return true if the number is power of 2
 *         false otherwise
 */
QUILL_NODISCARD constexpr bool is_pow_of_two(uint64_t number) noexcept
{
  return (number != 0) && ((number & (number - 1)) == 0);
}

/**
 * Constexpr string length
 * @param str input string
 * @return the length of the string
 */
QUILL_NODISCARD constexpr size_t strlen(char const* str) { return *str ? 1 + strlen(str + 1) : 0; }

/**
 * Convert a string to wstring
 * @param str input string
 * @return the value of input string as wide string
 */
QUILL_NODISCARD std::wstring s2ws(std::string const& str) noexcept;

/**
 * wstring to string
 * @param wstr input wide string
 * @return the value of input wide string as string
 */
QUILL_NODISCARD std::string ws2s(std::wstring const& wstr) noexcept;

/**
 * Same as strncpy.
 * Compared to normal strncpy :
 * a) It copies only the required bytes and b) always null terminates.
 * @tparam N max buffer size
 * @param destination destination buffer
 * @param source source string
 */
template <size_t N>
void safe_strncpy(std::array<char, N>& destination, char const* source) noexcept
{
  assert(source && "source pointer can not be nullptr");
  size_t const len = (std::min)(std::strlen(source), N - 1);
  std::memcpy(destination.data(), source, len);
  destination[len] = '\0';
}

/**
 * align a pointer to the given alignment
 * @tparam alignment desired alignment
 * @tparam T desired return type
 * @param pointer a pointer the object
 * @return an aligned pointer for the given object
 */
template <uint64_t alignment, typename T>
QUILL_NODISCARD_ALWAYS_INLINE_HOT constexpr T* align_pointer(void* pointer) noexcept
{
  static_assert(is_pow_of_two(alignment), "alignment must be a power of two");
  return reinterpret_cast<T*>((reinterpret_cast<uintptr_t>(pointer) + (alignment - 1ul)) & ~(alignment - 1ul));
}
} // namespace detail
} // namespace quill