
#ifndef FAST_DIVISION_H
#define FAST_DIVISION_H

#include <cstdint>
#include <iostream>

namespace fast_division {
template <uint32_t divisor> struct divide32 {

  constexpr static int leading_zeroes = __builtin_clz(divisor);
  constexpr static int log2_divisor = 31 - leading_zeroes;
  constexpr static uint32_t N = 0xFFFFFFFF; // max value

  constexpr static bool overflow = log2_divisor + 32 + log2_divisor + 1 >= 64;

  constexpr static bool is_even = ((divisor & 1) == 0);

  // General case (multiply-shift)
  //
  constexpr static uint64_t m = uint64_t(1) << (log2_divisor + 32);
  constexpr static uint64_t c_floor = m / divisor;

  constexpr static uint64_t c_ceiling = c_floor + 1;



  // Fallback on multiply-add-shift
  //
  constexpr static bool need_fallback = (divisor - (m % divisor) >= m / N  + 1);
  constexpr static uint64_t c = need_fallback ? c_floor : c_ceiling;

  // To handle powers of two
  constexpr static bool is_power_2 = ((divisor & (divisor - 1)) == 0);
  constexpr static uint32_t power_2_mask =
      ~uint32_t(int32_t(0x80000000) >> leading_zeroes);

  static inline uint32_t quotient(uint32_t n) noexcept {
    if (is_power_2) {
      return n >> log2_divisor;
    }
    return uint32_t(internal_product(n) >> (32 + log2_divisor));
  }
  static inline uint32_t remainder(uint32_t n) noexcept {
    if (is_power_2) {
      return n & power_2_mask;
    }
    if (overflow) {
      return n - quotient(n) * divisor;
    } else {
      return uint32_t(((internal_product(n) % m) * divisor) >>
                      (32 + log2_divisor));
    }
  }
  static inline bool is_divisible(uint32_t n) noexcept {
    if (is_power_2) {
      return (n & power_2_mask) == 0;
    }
    return (internal_product(n) % m) < c;
  }

private:
  static inline uint64_t internal_product(uint32_t n) noexcept {
    if (need_fallback) {
      return (c * n + c);
    } else {
      return c * n;
    }
  }
};

template <uint64_t divisor> struct divide64 {

  constexpr static int leading_zeroes = __builtin_clzll(divisor);
  constexpr static int log2_divisor = 63 - leading_zeroes;
  constexpr static uint64_t N = UINT64_C(0xFFFFFFFFFFFFFFFF); // max value

  constexpr static bool overflow = log2_divisor + 64 + log2_divisor + 1 >= 128;
  constexpr static bool is_even = ((divisor & 1) == 0);

  // General case (multiply-shift)
  //
  constexpr static __uint128_t m = __uint128_t(1) << (log2_divisor + 64);
  constexpr static uint64_t c_floor = uint64_t(m / divisor);

  constexpr static uint64_t c_ceiling = c_floor + 1;

  // Fallback on multiply-add-shift
  //
  constexpr static bool need_fallback = (divisor - (m % divisor) >= m / N + 1);
  constexpr static uint64_t c = need_fallback ? c_floor : c_ceiling;

  // To handle powers of two
  constexpr static bool is_power_2 = ((divisor & (divisor - 1)) == 0);
  constexpr static uint32_t power_2_mask =
      ~uint64_t(int64_t(0x8000000000000000) >> leading_zeroes);

  static inline uint64_t quotient(uint64_t n) noexcept {
    if (is_power_2) {
      return n >> log2_divisor;
    }
    return uint64_t(internal_product(n) >> (64 + log2_divisor));
  }
  static inline uint64_t remainder(uint64_t n) noexcept {
    if (is_power_2) {
      return n & power_2_mask;
    }
    if (overflow) {
      return n - quotient(n) * divisor;
    } else {
      return uint64_t(((internal_product(n) % m) * divisor) >>
                      (64 + log2_divisor));
    }
  }
  static inline bool is_divisible(uint64_t n) noexcept {
    if (is_power_2) {
      return (n & power_2_mask) == 0;
    }
    return (internal_product(n) % m) < c;
  }

private:
  static inline __uint128_t internal_product(uint64_t n) noexcept {
    if (need_fallback) {
      return (c * __uint128_t(n) + c);
    } else {
      return c * __uint128_t(n);
    }
  }
};
} // namespace fast_division
#endif
