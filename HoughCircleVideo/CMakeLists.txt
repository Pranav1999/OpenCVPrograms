cmake_minimum_required(VERSION 2.8)
project( HoughCircleVideo )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( HoughCircleVideo HoughCircleVideo.cpp )
target_link_libraries( HoughCircleVideo ${OpenCV_LIBS} )
