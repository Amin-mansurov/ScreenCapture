cmake_minimum_required(VERSION 3.5)
project(DisplayImage)

find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${X11_INCLUDE_DIRS})

add_executable(DisplayImage source/main.cpp)

target_link_libraries(DisplayImage ${OpenCV_LIBS} ${X11_LIBRARIES})
