cmake_minimum_required(VERSION 3.17)
project(Tarea2-SSOO)

set(CMAKE_CXX_STANDARD 14)

# Especificar la ruta de instalación opencv
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/opencv/share/OpenCV")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Tarea2-SSOO src/main.cpp)

target_include_directories(Tarea2-SSOO PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Tarea2-SSOO PRIVATE ${OpenCV_LIBS} pthread)

