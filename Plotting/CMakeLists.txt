# Use the code in this section for standalone projects
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(gas_visualization)
if(NOT TARGET Garfield::Garfield)
  find_package(Garfield REQUIRED)
endif()

# ---Build executable------------------------------------------------------------
add_executable(gas_visualization gas_visualization.C)
target_link_libraries(gas_visualization Garfield::Garfield)

# ---Copy all files locally to the build directory-------------------------------
foreach(_file xe_500v.gas)
  configure_file(${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_file} COPYONLY)
endforeach()
