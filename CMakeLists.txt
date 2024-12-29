# CMakeList.txt : Top-level CMake project file, do global configuration
#
cmake_minimum_required (VERSION 3.27)

# In order for the RelWithDebInfo configuration to work correctly,
# we need to tell cmake to prefer the Release configuration of packages
# instead of the Debug configuration when looking for RelWithDebInfo
# On some systems we observed that it would otherwise attempt to link
# the binary-incompatible Debug version of libraries
set(CMAKE_MAP_IMPORTED_CONFIG_MINSIZEREL "MinSizeRel;Release;")
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO "RelWithDebInfo;Release;")

# Some default settings, in case they're not set from command line.
#
# clangd (much better than intellisense) needs the compile_commands.json in the root folder or build folder.
# For IDE setup, see https://clangd.llvm.org/installation#project-setup
# If not explicitly set, we enable it:
if (NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)
	message(STATUS "CMAKE_EXPORT_COMPILE_COMMANDS not set explicitly")
endif()
message(STATUS "Using CMAKE_EXPORT_COMPILE_COMMANDS=${CMAKE_EXPORT_COMPILE_COMMANDS}")

# Use sccache if it is available on the system
find_program(SCCACHE sccache)
if(SCCACHE)
	message(STATUS "Using sccache: ${SCCACHE}")
	set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE})
	set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE})
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
endif()

if(WIN32)
	# In Windows, dependent shared libraries have to be in the same
	# folder as the depending executable to discover them easily
	# Alternativly, we could update the PATH environment variable like we do for third-parties but
	# i dont think that would scale well in some IDEs, like Visual Studio, that dont do it by default
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE STRING "Directory for built runtime binaries (EXE, DLL)")

	# We are pretty confident that everyone would prefer to define NOMINMAX on windows
	add_compile_definitions(NOMINMAX)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)

project("Ray_Tracing_in_a_Weekend")

set(HEADERS vec3.h color.h ray.h sphere.h hittable.h)
set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

## TODO: Add test for experimental stuffs
#option(BUILD_TESTS "Build Unit Tests" TRUE)
#
#if(BUILD_TESTS)
#	message(STATUS "Building Tests")
#	enable_testing()
#endif()

## Create PPM output image post build
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND "bin/${PROJECT_NAME}.exe" > "image.ppm"
  VERBATIM)