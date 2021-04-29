
#include "fast_division/fast_division.h"
#include <iostream>
#include <cmath>
#include <chrono>
const static size_t volume = 1024*1024;
uint32_t buffer[volume+1];

#ifdef __GNUC__
#define GCC_COMPILER
#endif 
#ifdef __clang__
#undef GCC_COMPILER
#endif

template<uint32_t divisor>
__attribute__ ((noinline))
#ifdef GCC_COMPILER
__attribute__((optimize("no-tree-vectorize")))
__attribute__((optimize("no-unroll-loops")))
#endif
void std_div() {
#pragma clang loop vectorize(disable)
#pragma clang loop unroll(disable)
  for(uint32_t n = 1; n < volume + 1; n++) {
    if(buffer[n] != ( n / divisor)) { throw std::runtime_error("bug"); }
  }
}

template<uint32_t divisor>
void compute_div() {
  for(uint32_t n = 1; n < volume + 1; n++) {
    buffer[n] = n / divisor;
  }
}

template<uint32_t divisor>
__attribute__ ((noinline))
#ifdef GCC_COMPILER
__attribute__((optimize("no-tree-vectorize")))
__attribute__((optimize("no-unroll-loops")))
#endif
void fast_div() {
  uint32_t sum = 0;
#pragma clang loop vectorize(disable)
#pragma clang loop unroll(disable)
  for(uint32_t n = 1; n < volume + 1; n++) {
    if(buffer[n] != fast_division::divide32<divisor>::quotient(n)) { throw std::runtime_error("bug"); }
  }
}


template<uint32_t divisor>
void compute_mod() {
  for(uint32_t n = 1; n < volume + 1; n++) {
    buffer[n] = n % divisor;
  }
}

template<uint32_t divisor>
__attribute__ ((noinline))
#ifdef GCC_COMPILER
__attribute__((optimize("no-tree-vectorize")))
__attribute__((optimize("no-unroll-loops")))
#endif
void std_mod() {
#pragma clang loop vectorize(disable)
#pragma clang loop unroll(disable)
  for(uint32_t n = 1; n < volume + 1; n++) {
    if(buffer[n] != (n % divisor)) { throw std::runtime_error("bug"); }
  }
}


template<uint32_t divisor>
__attribute__ ((noinline))
#ifdef GCC_COMPILER
__attribute__((optimize("no-tree-vectorize")))
__attribute__((optimize("no-unroll-loops")))
#endif
void fast_mod() {
#pragma clang loop vectorize(disable)
#pragma clang loop unroll(disable)
  for(uint32_t n = 1; n < volume + 1; n++) {
    if(buffer[n] != fast_division::divide32<divisor>::remainder(n)) { throw std::runtime_error("bug"); }
  }
}

template <class T>
std::pair<double, double> time_it_ns(T const &function, size_t repeat) {
  std::chrono::high_resolution_clock::time_point t1, t2;
  double average = 0;
  double min_value = 1e300;
  for (size_t i = 0; i < repeat; i++) {
    t1 = std::chrono::high_resolution_clock::now();
    function();
    t2 = std::chrono::high_resolution_clock::now();
    double dif =
        std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    average += dif;
    min_value = min_value < dif ? min_value : dif;
  }
  average /= repeat;
  return std::make_pair(min_value, average);
}


void pretty_print(size_t number_of_ops, std::string name, std::pair<double,double> result) {
  printf("%-40s: %8.2f ns/ops (+/- %.1f %%) \n", name.data(),
           result.first / number_of_ops,
           (result.second - result.first) * 100.0 / result.second);
}


template<uint32_t divisor>
void process() {
  size_t repeat = 100;
  std::cout << "divisor = " << divisor << std::endl;
  compute_div<divisor>();
  size_t trial = 2;
  std::cout << "repeating each measure " << trial << " times." << std::endl;
  for(size_t i = 0; i < trial; i++) {
    pretty_print(volume, "std division", time_it_ns(std_div<divisor>, repeat));
  }
  for(size_t i = 0; i < trial; i++) {
    pretty_print(volume, "fast division", time_it_ns(fast_div<divisor>, repeat));
  }   
  compute_mod<divisor>();
  for(size_t i = 0; i < trial; i++) {
    pretty_print(volume, "std remainder", time_it_ns(std_mod<divisor>, repeat));
  }
  for(size_t i = 0; i < trial; i++) {
    pretty_print(volume, "fast remainder", time_it_ns(fast_mod<divisor>, repeat));
  }
  std::cout << "==========" << std::endl;
}

int main() {
  std::cout << "We measure operation throughput." << std::endl; 
  std::cout << "==========" << std::endl;

  process<19>();
  process<123456>();
  //process<4096>();  
  //process<1024>();  

}
