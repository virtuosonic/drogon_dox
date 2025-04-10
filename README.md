# drogon_dox
This program extract the restful api endpoints created by the [drogon](https://drogonframework.github.io/drogon-docs/) orm

# Requirements
C++ 20, no external libraries are needed.

# Build
To build you can use cmake
```
mkdir build
cd build
cmake ..
cmake --build .
```

# Usage

`drogon_dox <directory containing controllers>`

The output will be saved in myapidoc.md 