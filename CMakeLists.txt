cmake_minimum_required(VERSION 3.10)
project(Lizon)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable(Lizon mframe.cpp main.cpp)

target_link_libraries(Lizon ${wxWidgets_LIBRARIES})