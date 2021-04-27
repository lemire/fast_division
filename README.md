# fast_division
Simple C++ code to benchmark fast division algorithms relying on constant divisors.

The code is made of a single header file (`fast_division.h`).

## Usage

Copy `fast_division.h` in your C++ project.


## Limitations and requirements

- We currently assume that the divisor is a compile-time constant. Extending to runtime constants is possible.
- We assume a recent compiler (C++11 or better). If you are interested in supporting legacy compilers, pull requests are invited.
- Currently, only 32-bit unsigned integers are supported. Adding other data types is merely a matter of extra programming effort.
- We assume a GCC-like compiler like GCC/LLVM clang. Pull requests to support Visual Studio and other compilers are invited.