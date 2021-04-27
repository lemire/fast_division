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
std division                            :     0.56 ns/ops (+/- 7.3 %)
fast division                           :     0.27 ns/ops (+/- 1.1 %)
std remainder                           :     0.69 ns/ops (+/- 0.6 %)
fast remainder                          :     0.39 ns/ops (+/- 1.3 %)
divisor = 67910
std division                            :     0.62 ns/ops (+/- 0.9 %)
fast division                           :     0.26 ns/ops (+/- 0.9 %)
std remainder                           :     0.62 ns/ops (+/- 0.6 %)
fast remainder                          :     0.39 ns/ops (+/- 1.1 %)
divisor = 4096
std division                            :     0.36 ns/ops (+/- 0.9 %)
fast division                           :     0.36 ns/ops (+/- 0.9 %)
std remainder                           :     0.28 ns/ops (+/- 4.1 %)
fast remainder                          :     0.28 ns/ops (+/- 5.2 %)
```

Results will vary depending on your compiler and processor.

## Limitations and requirements

- We currently assume that the divisor is a compile-time constant. Extending to runtime constants is possible.
- We assume a recent compiler (C++11 or better). If you are interested in supporting legacy compilers, pull requests are invited.
- Currently, only 32-bit unsigned integers are supported. Adding other data types is merely a matter of extra programming effort.
- We assume a GCC-like compiler like GCC/LLVM clang. Pull requests to support Visual Studio and other compilers are invited.