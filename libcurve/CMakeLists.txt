cmake_minimum_required (VERSION 3.10)

project (curve)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_USE_MATH_DEFINES)

add_library(curve SHARED include/Circle.hpp
                            include/Curve.hpp
                            include/Curves.hpp
                            include/Ellipse.hpp
                            include/Helix.hpp
                            include/Vector3.hpp

                            src/Circle.cpp 
                            src/Ellipse.cpp 
                            src/Helix.cpp
                            src/Vector3.cpp)

target_include_directories(curve PUBLIC include)
set(PROPERTIES VERSION 42)