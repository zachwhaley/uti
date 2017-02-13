cmake_minimum_required(VERSION 3.2)
project(uti)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
    )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download
    )

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
    ${CMAKE_BINARY_DIR}/googletest/src
    ${CMAKE_BINARY_DIR}/googletest/bin
    )

include_directories(
    ${CMAKE_SOURCE_DIR}
    )

add_executable(uti
    test/test.cpp
    test/array_test.cpp
    )
set_target_properties(uti PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON)
target_link_libraries(uti gtest)
