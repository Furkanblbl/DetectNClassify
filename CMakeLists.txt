cmake_minimum_required(VERSION 3.10)

project(DetectNClassify
        VERSION 1.0
        DESCRIPTION "Classical Image Segmentation and Object Detection in C++"
        LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug flags (optional)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    include
)

# Source files
set(SOURCES
    src/main.cpp
    src/histogram.cpp
    src/kmean.cpp
    src/segment.cpp
)

# Create executable
add_executable(DetectNClassify ${SOURCES})

# Link OpenCV
target_link_libraries(DetectNClassify ${OpenCV_LIBS})
