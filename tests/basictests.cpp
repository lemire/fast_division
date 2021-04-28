#include "fast_division/fast_division.h"
#include <iostream>
template<uint32_t divisor>
void test() {
  std::cout << "testing " << divisor << std::endl;
  for(uint32_t n = 1; n != 0; n++) {
    bool quotient_ok = fast_division::divide32<divisor>::quotient(n) == n / divisor;
    bool remainder_ok = fast_division::divide32<divisor>::remainder(n) == n % divisor;
    bool mult_ok = fast_division::divide32<divisor>::is_divisible(n) == (n % divisor == 0);
    if(!quotient_ok || !remainder_ok || !mult_ok) {
        std::cerr << "problem with n = " << n << std::endl;
        std::cout << "quotient: " << fast_division::divide32<divisor>::quotient(n) << " expected: "<< n / divisor <<std::endl;
        std::cout << "remainder: " << fast_division::divide32<divisor>::remainder(n) << " expected: "<< n % divisor <<std::endl;
        std::cout << "multiple: " << fast_division::divide32<divisor>::is_divisible(n) << " expected: "<< (n % divisor == 0) <<std::endl;

        std::cout << "need_fallback = " << fast_division::divide32<divisor>::need_fallback << std::endl;
        std::cout << "is_power_2    = " << fast_division::divide32<divisor>::is_power_2 << std::endl;
        std::cout << "c             = " << fast_division::divide32<divisor>::c << std::endl;
        std::cout << "leading_zeroes= " << fast_division::divide32<divisor>::leading_zeroes << std::endl;
        std::cout << "log2_divisor  = " << fast_division::divide32<divisor>::log2_divisor << std::endl;
        std::cout << "m             = " << fast_division::divide32<divisor>::m << std::endl;
        std::cout << "overflow      = " << fast_division::divide32<divisor>::overflow << std::endl;
        std::cout << "c_overflow_ceiling      = " << uint64_t(fast_division::divide32<divisor>::c_overflow_ceiling) << std::endl;

        abort();
    }
  }
}

int main() {
    test<1000000001>();
    test<1232445>();
    test<67910>();
    test<8>();
    test<19>();
    test<461>();
    std::cout << "ok"<<std::endl;
}