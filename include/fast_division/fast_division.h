
#ifndef FAST_DIVISION_H
#define FAST_DIVISION_H

#include <cstdint>
#include <iostream>

namespace fast_division {
template <uint32_t divisor>
struct divide32 {

  constexpr static int leading_zeroes = __builtin_clz(divisor);
  constexpr static int log2_divisor = 31 - leading_zeroes;
  constexpr static uint32_t N = 0xFFFFFFFF; // max value

  // General case (multiply-shift)
  // 
  constexpr static uint64_t m = uint64_t(1) << (log2_divisor + 32);
  constexpr static uint64_t c_floor = m / divisor;

  constexpr static uint64_t c_ceiling = c_floor + 1;

  // Fallback on multiply-add-shift
  //
  // We need the fallback when 
  // ceiling(m/d)>=(1+1/N)*m/d
  // or 
  // ceiling(m/d) * d >= (1+1/N)*m
  // or
  // m + d - m%d >= m + m/N
  constexpr static bool need_fallback = (divisor - (m%divisor) >= m / N);
  constexpr static uint64_t c = need_fallback ? c_floor : c_ceiling;


  // To handle powers of two
  constexpr static bool is_power_2 = ((divisor & (divisor - 1)) == 0);
  constexpr static uint32_t power_2_mask = ~uint32_t(int32_t(0x80000000) >> leading_zeroes);
  
  static inline uint64_t quotient(uint32_t n) noexcept {
      if(is_power_2) { return n >> log2_divisor; }
      return internal_product(n) >> (32 + log2_divisor);
  }
  static inline uint64_t remainder(uint32_t n) noexcept {
      if(is_power_2) { return n & power_2_mask; }
      return ((internal_product(n) % m) * __uint128_t(divisor)) >> (32 + log2_divisor);
  }
  static inline uint64_t is_divisible(uint32_t n) noexcept {
      if(is_power_2) { return (n & power_2_mask) == 0; }
      return (internal_product(n) % m) < c;
  }
  private:
  static inline uint64_t internal_product(uint32_t n) noexcept {
      if(need_fallback) {
          return (c * n + c);
      } else {
          return c * n;
      }
  }
};
}
#endif