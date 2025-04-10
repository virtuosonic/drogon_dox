cmake_minimum_required(VERSION 3.16)

project(drogon_dox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(drogon_dox main.cpp)

include(GNUInstallDirs)
install(TARGETS drogon_dox
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
