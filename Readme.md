# Prerequisites
- `g++` / `clang++` (with `-std=c++0x` support)
- `CMake` (2.8 minimum)

## Ubuntu 12.04
To compile this g++ need to have `-std=c++0x` support and 12.04's does.

So simple solution is to enable [this](https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test) ppa (ppa:ubuntu-toolchain-r/test) if you want to use -std=c++11.

Also It's `std::thread::hardware_concurrency()` doesn't actually working in 12.04's old GCC because there's this function implementation in `/usr/include/c++/4.6.3/thread`:
```
// Returns a value that hints at the number of hardware thread contexts.
static unsigned int
hardware_concurrency()
{ return 0;  }
```
