cmake_minimum_required(VERSION 2.8)
project( 402524_furkan_bulbul_image_processing )

find_package( OpenCV REQUIRED )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )

add_executable( 402524_furkan_bulbul_image_processing src/main.cpp src/histogram.cpp  src/kmean.cpp src/segment.cpp)

target_link_libraries( 402524_furkan_bulbul_image_processing ${OpenCV_LIBS} )