cmake_minimum_required(VERSION 3.20)
project(ra2_original_target LANGUAGES NONE)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(RA2_LOCAL_CONFIG "${CMAKE_SOURCE_DIR}/private/original-target.local.json" CACHE FILEPATH "Private input/toolchain configuration")
add_custom_target(original-target
  COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_SOURCE_DIR}/tools/original_target/build.py" --config "${RA2_LOCAL_CONFIG}"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" USES_TERMINAL)
add_custom_target(check-inputs
  COMMAND "${Python3_EXECUTABLE}" -B "${CMAKE_SOURCE_DIR}/tools/original_target/build.py" --config "${RA2_LOCAL_CONFIG}" --verify-inputs
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" USES_TERMINAL)
