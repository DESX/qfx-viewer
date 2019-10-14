cmake_minimum_required(VERSION 3.10)

project(qfx_viewer)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(${wxWidgets_USE_FILE})

add_executable(qfx_viewer main.cpp)

target_link_libraries(qfx_viewer ${wxWidgets_LIBRARIES})




