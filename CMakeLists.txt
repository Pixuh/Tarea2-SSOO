cmake_minimum_required(VERSION 3.17)
project(Tarea2-SSOO)

set(CMAKE_CXX_STANDARD 14)

# Especificar la ruta de instalacion opencv
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/opencv/install/share/OpenCV")

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Agrega los archivos fuente aquí
add_executable(Tarea2-SSOO_secuencial src/mainSecuencial.cpp)
add_executable(Tarea2-SSOO_paralelo_thread src/mainParalelo.cpp)

target_include_directories(Tarea2-SSOO_secuencial PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Tarea2-SSOO_secuencial PRIVATE ${OpenCV_LIBS} pthread)

target_include_directories(Tarea2-SSOO_paralelo_thread PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Tarea2-SSOO_paralelo_thread PRIVATE ${OpenCV_LIBS} pthread)

