project(ImageServer)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

SET(LIBEVENT_NAME "event" CACHE STRING "Name of the libevent library (as used in the linker argument).")
SET(LIBEVENT_LIB_DIR "/usr/local/lib" CACHE STRING "Path to libevent libraries.")
SET(LIBEVENT_INCLUDE_DIR "/usr/local/include" CACHE STRING "Path to libevent headers.")

SET(GTEST_HOME_DIR "/usr/local/include" CACHE STRING "Path to Googles test framework.")

SET(OPENCV_LIB_DIR "/usr/local/lib" CACHE STRING "Path to OpenCV libraries.")
SET(OPENCV_INCLUDE_DIR "/usr/local/include" CACHE STRING "Path to OpenCV headers.")

include_directories("${LIBEVENT_INCLUDE_DIR}")
include_directories("${GTEST_HOME_DIR}/googletest/include")
include_directories("${GTEST_HOME_DIR}/googlemock/include")
include_directories(${OPENCV_INCLUDE_DIR})

link_directories("${LIBEVENT_LIB_DIR}")
link_directories("${GTEST_HOME_DIR}/build/googlemock/gtest")
link_directories("${GTEST_HOME_DIR}/build/googlemock")
link_directories("${OPENCV_LIB_DIR}")

# build settings
include(CTest)

set(CTEST_MEMORYCHECK_COMMAND, "valgrind")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS, "--trace-children=yes --leak-check=full")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# server executable
add_executable(imageserver src/server.cpp)
target_link_libraries(imageserver ${LIBEVENT_NAME})
target_link_libraries(imageserver server)
target_link_libraries(imageserver image)

# server module
set(libServerSources
    src/ServerHelper.cpp
)

add_library(server SHARED ${libServerSources})
target_link_libraries(server ${LIBEVENT_NAME})

# image module
set(libImageSources
    src/SourceImageFile.cpp
    src/ImageService.cpp
)

add_library(image SHARED ${libImageSources})
target_link_libraries(image opencv_calib3d opencv_core opencv_features2d opencv_flann opencv_highgui opencv_imgcodecs opencv_imgproc opencv_ml opencv_objdetect opencv_photo opencv_shape opencv_stitching opencv_superres opencv_video opencv_videoio opencv_videostab)

# test - server module
add_executable(server_test tests/server_test.cpp)
add_test(server_test server_test)

target_link_libraries(server_test server)
target_link_libraries(server_test gmock)
target_link_libraries(server_test gtest)

# test - image module
add_executable(image_test tests/image_test.cpp)
add_test(image_test image_test)

target_link_libraries(image_test image)
target_link_libraries(image_test gmock)
target_link_libraries(image_test gtest)
