# fast_division
Simple C++ code to benchmark fast division algorithms relying on constant divisors.


The code is a companion to the paper [Integer Division by Constants: Optimal Bounds](https://arxiv.org/abs/2012.12369) in the sense that it illustrates the results. We are not claiming that this code, as is, is faster than your compiler generated assembly. Thus it should be viewed as a research artefact.


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
❯ ./benchmark/benchmark
divisor = 19
std division                            :     0.94 ns/ops (+/- 1.0 %)
fast division                           :     0.44 ns/ops (+/- 1.9 %)
std remainder                           :     0.78 ns/ops (+/- 0.5 %)
fast remainder                          :     0.71 ns/ops (+/- 0.5 %)
divisor = 67910
std division                            :     0.86 ns/ops (+/- 0.7 %)
fast division                           :     0.44 ns/ops (+/- 0.6 %)
std remainder                           :     0.65 ns/ops (+/- 0.5 %)
fast remainder                          :     0.63 ns/ops (+/- 0.8 %)
divisor = 4096
std division                            :     0.60 ns/ops (+/- 1.6 %)
fast division                           :     0.60 ns/ops (+/- 2.1 %)
std remainder                           :     0.75 ns/ops (+/- 0.5 %)
fast remainder                          :     0.74 ns/ops (+/- 1.3 %)
```

Results will vary depending on your compiler and processor.

## Assembly ouputs (LLVM, ARM) for divisor = 67910

The variable `x` is of type `uint32_t`.

`x/67910` compiles to:

```asm
        mov     w8, #64905
        movk    w8, #63244, lsl #16
        umull   x8, w0, w8
        lsr     x0, x8, #48
```

`divide32<67910>::quotient(x)` compiles to:

```asm
        mov     w8, #64905
        movk    w8, #63244, lsl #16
        umull   x8, w0, w8
        lsr     x0, x8, #48
```

`x%67910` compiles to:

```asm
        mov     w8, #64905
        movk    w8, #63244, lsl #16
        umull   x8, w0, w8
        mov     w9, #2374
        lsr     x8, x8, #48
        movk    w9, #1, lsl #16
        msub    w0, w8, w9, w0
        ret
```

`divide32<67910>::remainder(x)` compiles to:

```asm
        mov     w8, #64905
        movk    w8, #63244, lsl #16
        umull   x8, w0, w8
        mov     w9, #2374
        and     x8, x8, #0xffffffffffff
        movk    w9, #1, lsl #16
        mul     x8, x8, x9
        lsr     x0, x8, #48
```
## Further reading and code


For a practical library with performance claims, see [fastmod](https://github.com/lemire/fastmod) and the manuscript:

- Daniel Lemire, Owen Kaser, Nathan Kurz, [Faster Remainder by Direct Computation: Applications to Compilers and Software Libraries](https://arxiv.org/abs/1902.01961), Software: Practice and Experience 49 (6), 2019

## Limitations and requirements

- We currently assume that the divisor is a compile-time constant. Extending to runtime constants is possible.
- We assume a recent compiler (C++11 or better). If you are interested in supporting legacy compilers, pull requests are invited.
- Currently, only 32-bit unsigned integers are supported. Adding other data types is merely a matter of extra programming effort.
- We assume a GCC-like compiler like GCC/LLVM clang. Pull requests to support Visual Studio and other compilers are invited.