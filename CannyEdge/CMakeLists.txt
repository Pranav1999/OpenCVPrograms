cmake_minimum_required(VERSION 2.8)
project( CannyEdge )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( CannyEdge CannyEdge.cpp )
target_link_libraries( CannyEdge ${OpenCV_LIBS} )
