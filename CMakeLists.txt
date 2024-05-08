# Minimum required version of CMake
cmake_minimum_required(VERSION 3.28) # Specifies the minimum version of CMake required to build this project.

project(Tetris)
set(CMAKE_CXX_STANDARD 17) # Sets the C++ standard to C++17.

# Set the output directory for the build executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Retrieves the VCPKG_ROOT environment variable.
set(VCPKG_ROOT $ENV{VCPKG_ROOT})

if(NOT DEFINED VCPKG_ROOT)
    message(FATAL_ERROR "VCPKG_ROOT is not defined. Please set it in your environment.")
endif()

# Include vcpkg toolchain file if it exists
set(VCPKG_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake") # Sets the path to the vcpkg toolchain file.

if(EXISTS ${VCPKG_TOOLCHAIN_FILE})
    include(${VCPKG_TOOLCHAIN_FILE})
else()
    message(FATAL_ERROR "Cannot find vcpkg.cmake at VCPKG_ROOT: ${VCPKG_ROOT}")
endif()

# Adds the 'include' directory to the list of directories to be searched for header files.
include_directories(bin/include)

# Retrieves all .cpp files in the 'source' directory.
file(GLOB SOURCES "bin/source/*.cpp")

# Add executable with all .cpp files found in /source
add_executable(Tetris ${SOURCES})

# Search for raylib package
find_package(raylib CONFIG REQUIRED)

# Link raylib to your executable
target_link_libraries(Tetris PRIVATE raylib)

# Sets the path to the directory containing raylib.dll.
set(RAYLIB_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/vcpkg_installed/x64-mingw-dynamic/bin)

# Adds a post-build command to copy raylib.dll to the output directory.
add_custom_command(TARGET Tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${RAYLIB_DLL_DIR}/libraylib.dll
        ${CMAKE_CURRENT_SOURCE_DIR}/libraylib.dll)
