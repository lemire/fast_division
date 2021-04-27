# fast_division
Simple C++ code to benchmark fast division algorithms relying on constant divisors.

The code is made of a single header file (`fast_division.h`).

## Usage

Copy `fast_division.h` in your C++ project. You can then use it as follows.

```C++
#include "fast_division/fast_division.h"

// for any compile-time constant 'divisor' we have:
assert(fast_division::divide32<divisor>::quotient(n) == n / divisor);
assert(fast_division::divide32<divisor>::remainder(n) == n % divisor)
assert(fast_division::divide32<divisor>::is_divisible(n) == (n % divisor == 0));
```

## Benchmarks

```
❯ cmake -B build && cmake --build build
./build/benchmark/benchmark
```

On an Apple M1 processor with clang 12, we get:

```
❯ ./build/benchmark/benchmark
divisor = 19
std division                            :     0.58 ns/ops (+/- 1.5 %)
fast division                           :     0.27 ns/ops (+/- 1.1 %)
std remainder                           :     0.72 ns/ops (+/- 0.4 %)
fast remainder                          :     0.39 ns/ops (+/- 2.0 %)
std divisibility test                   :     0.74 ns/ops (+/- 1.7 %)
fast divisibility test                  :     0.32 ns/ops (+/- 0.9 %)
divisor = 67910
std division                            :     0.64 ns/ops (+/- 1.4 %)
fast division                           :     0.27 ns/ops (+/- 2.0 %)
std remainder                           :     0.65 ns/ops (+/- 0.4 %)
fast remainder                          :     0.40 ns/ops (+/- 1.5 %)
std divisibility test                   :     0.65 ns/ops (+/- 0.6 %)
fast divisibility test                  :     0.27 ns/ops (+/- 8.1 %)
divisor = 4096
std division                            :     0.38 ns/ops (+/- 0.6 %)
fast division                           :     0.38 ns/ops (+/- 0.6 %)
std remainder                           :     0.29 ns/ops (+/- 5.2 %)
fast remainder                          :     0.29 ns/ops (+/- 2.5 %)
std divisibility test                   :     0.16 ns/ops (+/- 0.4 %)
fast divisibility test                  :     0.16 ns/ops (+/- 0.5 %)
```

## Limitations and requirements

- We currently assume that the divisor is a compile-time constant. Extending to runtime constants is possible.
- We assume a recent compiler (C++11 or better). If you are interested in supporting legacy compilers, pull requests are invited.
- Currently, only 32-bit unsigned integers are supported. Adding other data types is merely a matter of extra programming effort.
- We assume a GCC-like compiler like GCC/LLVM clang. Pull requests to support Visual Studio and other compilers are invited.