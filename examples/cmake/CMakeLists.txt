cmake_minimum_required (VERSION 3.10)

project(example)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# list of source files
set(srcs example.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I.")

include(GNUInstallDirs)
find_package(PkgConfig)
message("PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH}")

pkg_check_modules (LAVU REQUIRED liblavu>=0.0.1)
link_directories(${LAVU_LIBRARY_DIRS})

add_executable(example ${srcs})
include_directories(example ${LAVU_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LAVU_LIBRARIES})
message("libs: ${LIBS}")
target_link_libraries(example PRIVATE ${LIBS})

add_custom_target(cclean COMMAND rm -rf CMakeCache.txt  CMakeFiles)

# enable_testing()
# add_subdirectory(test)
