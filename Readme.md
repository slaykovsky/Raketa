# Prerequisites
- `g++` / `clang++` (with `-std=c++11` support)
- `CMake` (2.8 minimum)

## Ubuntu 12.04
To compile this g++ need to have `-std=c++11` support but 12.04's doesn't.

So simple solution is to enable [this](https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test) ppa (ppa:ubuntu-toolchain-r/test). Or maybe edit `CMakeLists.txt` definitions to `-std=c++0x` (I didn't test that case);
