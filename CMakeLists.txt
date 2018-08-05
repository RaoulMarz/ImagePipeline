#CMake version
cmake_minimum_required(VERSION 3.5)
project(ImagePipeline)

set(EXECUTABLE_NAME "ImagePipeline")
set(VERSION_MAJOR 0)
set(VERSION_MINOR 2)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PNG REQUIRED libpng)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

find_package(Boost 1.6 REQUIRED
  COMPONENTS system filesystem
)

link_directories(${GTKMM_LIBRARY_DIRS} ${CAIRO_LIBRARY_DIRS} ${PNG_LIBRARY_DIRS} ${GTK3_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

include_directories(include)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CAIRO_LIBRARIES} ${PNG_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES} ${GTK3_LIBRARIES})

target_link_libraries(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT} ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

