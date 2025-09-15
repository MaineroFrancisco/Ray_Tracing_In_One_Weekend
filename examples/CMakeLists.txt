cmake_minimum_required(VERSION 3.28)

# Loop through all .cpp files and create an executable for each
file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(EXAMPLE_FILE ${EXAMPLE_SOURCES})
  get_filename_component(EXE_NAME ${EXAMPLE_FILE} NAME_WE)
  add_executable(${EXE_NAME} ${EXAMPLE_FILE} ${HEADERS_CORE})
  target_compile_features(${EXE_NAME} PUBLIC cxx_std_20)
  target_include_directories(${EXE_NAME} PRIVATE ../core ../extras ../external)
endforeach()
