cmake_minimum_required(VERSION 2.8)
project( BrightnessAndContrast )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( BrightnessAndContrast BrightnessAndContrast.cpp )
target_link_libraries( BrightnessAndContrast ${OpenCV_LIBS} )
