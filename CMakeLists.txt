cmake_minimum_required(VERSION 3.10)
project(qfx_viewer)
find_package(wxWidgets )
include(${wxWidgets_USE_FILE})
add_executable(qfx_viewer main.cpp)
#foreach(V ${wxWidgets_LIBRARIES})
#message("wxWidgets_LIBRARIES: ${V}")
#endforeach()
target_link_libraries(qfx_viewer  ${wxWidgets_LIBRARIES})




