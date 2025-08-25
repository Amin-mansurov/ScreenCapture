cmake_minimum_required(VERSION 3.10)
project(ScreenCapture LANGUAGES CXX)

# Use at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)

add_executable(ScreenCapture source/main.cpp)

target_include_directories(ScreenCapture PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
)

target_link_libraries(ScreenCapture PRIVATE
    ${OpenCV_LIBS}
    ${X11_LIBRARIES}
)
