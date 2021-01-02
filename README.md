# data-loader

This project is targeting to build a C++ library for thread-safe data hot reloading.

## Features

* Header-only library.
* `TimerReloader`
    * Supports reloading in a timer cicle.
    * Supports get data instance, with thread-safe. Moreover, the gotten instance of data object is safe, even if a reloading occurs.
    * Supports terminating.

## How to build

1. Clone: `git clone https://github.com/Liam0205/data-reloader.git`.
2. Change Directory: `cd data-reloader`.
3. Initialize sub-modules: `git submodule init`.
4. Clone sub-modules: `git submodule update`.
5. Build: `./blade build -p release ...` or `./blade build -p debug ...` for debug mode.
6. Test: `./blade test`.
