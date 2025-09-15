# CMakeList.txt : Top-level CMake project file
cmake_minimum_required(VERSION 3.28)

# clangd (much better than intellisense) needs the compile_commands.json in the
# root folder or build folder. For IDE setup, see
# https://clangd.llvm.org/installation#project-setup If not explicitly set, we
# enable it:
if(NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS
      ON
      CACHE BOOL "" FORCE)
  message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS not set explicitly")
endif()
message(
  STATUS "Using CMAKE_EXPORT_COMPILE_COMMANDS=${CMAKE_EXPORT_COMPILE_COMMANDS}")

# Use sccache if it is available on the system
find_program(SCCACHE sccache)
if(SCCACHE)
  message(STATUS "Using sccache: ${SCCACHE}")
  set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE})
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
endif()

if(WIN32)
  # We are pretty confident that everyone would prefer to define NOMINMAX on
  # windows
  add_compile_definitions(NOMINMAX)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)

project("Ray_Tracing_in_a_Weekend")

file(GLOB HEADERS_CORE "core/*.h")
file(GLOB HEADERS_EXTRAS "extras/*.h")

# TODO: Properly link to stb_image, add to include libraries, avoid this
# hardcoding
file(GLOB HEADERS_EXTERNAL "external/*.h")

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS_CORE} ${HEADERS_EXTRAS}
                               ${HEADERS_EXTERNAL} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE core extras external)

add_subdirectory(examples)

# TODO: Add test for experimental stuffs

# Create PPM output image post build
set(BUILD_IMAGE_OUTPUT ON)
if(BUILD_IMAGE_OUTPUT)
  message(STATUS "Creating image output after build")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/images/earthmap.jpg earthmap.jpg
    COMMAND "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.exe" >
            "image.ppm"
    VERBATIM)
endif()
