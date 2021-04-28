# fast_division
Simple C++ code to benchmark fast division algorithms relying on constant divisors.


The code is a companion to the paper [Integer Division by Constants: Optimal Bounds](https://arxiv.org/abs/2012.12369) in the sense that it illustrates the results. It should be viewed as a research artefact.


## Usage

The code is made of a single header file (`fast_division.h`).

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
std division                            :     0.91 ns/ops (+/- 3.8 %)
fast division                           :     0.31 ns/ops (+/- 1.0 %)
std remainder                           :     0.76 ns/ops (+/- 0.7 %)
fast remainder                          :     0.62 ns/ops (+/- 4.7 %)
divisor = 123456
std division                            :     0.84 ns/ops (+/- 0.7 %)
fast division                           :     0.31 ns/ops (+/- 1.1 %)
std remainder                           :     0.62 ns/ops (+/- 0.6 %)
fast remainder                          :     0.31 ns/ops (+/- 16.0 %)
divisor = 4096
std division                            :     0.58 ns/ops (+/- 1.8 %)
fast division                           :     0.58 ns/ops (+/- 1.8 %)
std remainder                           :     0.72 ns/ops (+/- 0.7 %)
fast remainder                          :     0.72 ns/ops (+/- 0.6 %)
```

On an AMD Zen 2 processor with GCC 10, we get:

```
$ ./build/benchmark/benchmark
divisor = 19
std division                            :     0.87 ns/ops (+/- 1.0 %)
fast division                           :     0.44 ns/ops (+/- 3.4 %)
std remainder                           :     1.15 ns/ops (+/- 0.1 %)
fast remainder                          :     0.82 ns/ops (+/- 0.3 %)
divisor = 123456
std division                            :     0.59 ns/ops (+/- 2.9 %)
fast division                           :     0.43 ns/ops (+/- 4.3 %)
std remainder                           :     0.76 ns/ops (+/- 10.5 %)
fast remainder                          :     0.64 ns/ops (+/- 1.0 %)
divisor = 4096
std division                            :     0.29 ns/ops (+/- 0.4 %)
fast division                           :     0.29 ns/ops (+/- 0.3 %)
std remainder                           :     0.29 ns/ops (+/- 0.4 %)
fast remainder                          :     0.29 ns/ops (+/- 0.4 %)
```

Results will vary depending on your compiler and processor. They also depend on the divisor.

The benchmark measures throughput, not latency.

## Further reading and code


For a practical library with performance claims, see [fastmod](https://github.com/lemire/fastmod) and the manuscript:

- Daniel Lemire, Owen Kaser, Nathan Kurz, [Faster Remainder by Direct Computation: Applications to Compilers and Software Libraries](https://arxiv.org/abs/1902.01961), Software: Practice and Experience 49 (6), 2019

## Limitations and requirements

- We currently assume that the divisor is a compile-time constant. Extending to runtime constants is possible.
- We assume a recent compiler (C++11 or better). If you are interested in supporting legacy compilers, pull requests are invited.
- Currently, only 32-bit unsigned integers are supported. Adding other data types is merely a matter of extra programming effort.
- We assume a GCC-like compiler like GCC/LLVM clang. Pull requests to support Visual Studio and other compilers are invited.
