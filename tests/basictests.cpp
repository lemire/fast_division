#include "fast_division/fast_division.h"
#include <iostream>
template <uint32_t divisor> void test32() {
  std::cout << "(32-bit) testing " << divisor << std::endl;
  for (uint32_t n = 1; n != 0; n++) {
    bool quotient_ok =
        fast_division::divide32<divisor>::quotient(n) == n / divisor;
    bool remainder_ok =
        fast_division::divide32<divisor>::remainder(n) == n % divisor;
    bool mult_ok =
        fast_division::divide32<divisor>::is_divisible(n) == (n % divisor == 0);
    if (!quotient_ok || !remainder_ok || !mult_ok) {
      std::cerr << "problem with n = " << n << std::endl;
      std::cout << "quotient: " << fast_division::divide32<divisor>::quotient(n)
                << " expected: " << n / divisor << std::endl;
      std::cout << "remainder: "
                << fast_division::divide32<divisor>::remainder(n)
                << " expected: " << n % divisor << std::endl;
      std::cout << "multiple: "
                << fast_division::divide32<divisor>::is_divisible(n)
                << " expected: " << (n % divisor == 0) << std::endl;

      std::cout << "need_fallback = "
                << fast_division::divide32<divisor>::need_fallback << std::endl;
      std::cout << "is_power_2    = "
                << fast_division::divide32<divisor>::is_power_2 << std::endl;
      std::cout << "c             = " << fast_division::divide32<divisor>::c
                << std::endl;
      std::cout << "leading_zeroes= "
                << fast_division::divide32<divisor>::leading_zeroes
                << std::endl;
      std::cout << "log2_divisor  = "
                << fast_division::divide32<divisor>::log2_divisor << std::endl;
      std::cout << "m             = " << fast_division::divide32<divisor>::m
                << std::endl;
      std::cout << "overflow      = "
                << fast_division::divide32<divisor>::overflow << std::endl;

      abort();
    }
  }
}

std::ostream &operator<<(std::ostream &dest, __uint128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    int len = int(std::end(buffer) - d);
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}
template <uint64_t divisor> void test64() {
  std::cout << "(64-bit) testing " << divisor << std::endl;
  for (uint64_t n = 1; n != 0; n++) {
    if (n == 1000000) {
      n = 0xFFFFFFFFFFFFFFFF - 1000000;
    }
    bool quotient_ok =
        fast_division::divide64<divisor>::quotient(n) == n / divisor;
    bool remainder_ok =
        fast_division::divide64<divisor>::remainder(n) == n % divisor;
    bool mult_ok =
        fast_division::divide64<divisor>::is_divisible(n) == (n % divisor == 0);
    if (!quotient_ok || !remainder_ok || !mult_ok) {
      std::cerr << "problem with n = " << n << std::endl;
      std::cout << "quotient: " << fast_division::divide64<divisor>::quotient(n)
                << " expected: " << n / divisor << std::endl;
      std::cout << "remainder: "
                << fast_division::divide64<divisor>::remainder(n)
                << " expected: " << n % divisor << std::endl;
      std::cout << "multiple: "
                << fast_division::divide64<divisor>::is_divisible(n)
                << " expected: " << (n % divisor == 0) << std::endl;

      std::cout << "need_fallback = "
                << fast_division::divide64<divisor>::need_fallback << std::endl;
      std::cout << "is_power_2    = "
                << fast_division::divide64<divisor>::is_power_2 << std::endl;
      std::cout << "c             = " << fast_division::divide64<divisor>::c
                << std::endl;
      std::cout << "leading_zeroes= "
                << fast_division::divide64<divisor>::leading_zeroes
                << std::endl;
      std::cout << "log2_divisor  = "
                << fast_division::divide64<divisor>::log2_divisor << std::endl;
      std::cout << "m             = " << fast_division::divide64<divisor>::m
                << std::endl;
      std::cout << "overflow      = "
                << fast_division::divide64<divisor>::overflow << std::endl;

      abort();
    }
  }
}
int main() {

  test64<1000000001>();
  test64<1232445>();
  test64<67910>();
  test64<8>();
  test64<19>();
  test64<461>();

  test32<1000000001>();
  test32<1232445>();
  test32<67910>();
  test32<8>();
  test32<19>();
  test32<461>();
  std::cout << "ok" << std::endl;
}