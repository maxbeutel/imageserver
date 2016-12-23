project(ImageServer)

cmake_minimum_required(VERSION 3.1)

MESSAGE("LIBEVENT_HOME: " ${LIBEVENT_HOME})
MESSAGE("GTEST_HOME: " ${GTEST_HOME})

include_directories("${LIBEVENT_HOME}/include")
include_directories("${GTEST_HOME}/googletest/include")
include_directories("${GTEST_HOME}/googlemock/include")

link_directories("${LIBEVENT_HOME}/.libs")
link_directories("${GTEST_HOME}/build/googlemock/gtest")
link_directories("${GTEST_HOME}/build/googlemock")

# build settings
include(CTest)

set(CTEST_MEMORYCHECK_COMMAND, "valgrind")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS, "--trace-children=yes --leak-check=full")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# server
add_executable(server src/server.cpp)
target_link_libraries(server event_custom) # @FIXME this should be passed in via variable?

# server helper module (@FIXME not used in server yet!)
set(libServerHelperSources
    src/ServerHelper.cpp
)

add_library(server_helper SHARED ${libServerHelperSources})
target_link_libraries(server_helper event_custom) # @FIXME this should be passed in via variable?

# image module related stuff
set(libImageSources
    src/ImageRequest.cpp
    src/ImageService.cpp
)

add_library(image SHARED ${libImageSources})

# test - server helper module
add_executable(server_helper_test tests/server_helper_test.cpp)
add_test(server_helper_test server_helper_test)

target_link_libraries(server_helper_test server_helper)
target_link_libraries(server_helper_test gmock)
target_link_libraries(server_helper_test gtest)

# test - image module
add_executable(image_test tests/image_test.cpp)
add_test(image_test image_test)

target_link_libraries(image_test image)
target_link_libraries(image_test gmock)
target_link_libraries(image_test gtest)
