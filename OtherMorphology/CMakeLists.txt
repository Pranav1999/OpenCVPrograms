cmake_minimum_required(VERSION 2.8)
project( OtherMorphology )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( OtherMorphology OtherMorphology.cpp )
target_link_libraries( OtherMorphology ${OpenCV_LIBS} )
