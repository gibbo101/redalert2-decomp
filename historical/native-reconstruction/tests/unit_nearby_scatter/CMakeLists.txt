cmake_minimum_required(VERSION 3.20)
project(unit_nearby_scatter_checks LANGUAGES CXX)
option(RA2_SANITIZE "Enable address and undefined behavior sanitizers" OFF)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)
add_executable(unit-nearby-scatter-vectors ../unit_nearby_scatter_vectors.cpp
 ../../src/sim/OriginalRandom.cpp ../../src/sim/UnitDiscovery.cpp ../../src/sim/Targeting.cpp
 ../../src/sim/FootCoordinates.cpp ../../src/sim/UnitAdmission.cpp ../../src/sim/MovingUnitAdmission.cpp
 ../../src/sim/MovementGate.cpp ../../src/assets/MapCellChildren.cpp ../../src/assets/MapFloorHeight.cpp
 ../../src/assets/MapCoordinateCell.cpp ../../src/render/Lighting.cpp ../../src/assets/RenderData.cpp ../../src/assets/MovementData.cpp ../../src/assets/PreparedData.cpp)
target_include_directories(unit-nearby-scatter-vectors PRIVATE ../../src)
target_link_libraries(unit-nearby-scatter-vectors PRIVATE OpenSSL::Crypto)
target_compile_features(unit-nearby-scatter-vectors PRIVATE cxx_std_20)
set_target_properties(unit-nearby-scatter-vectors PROPERTIES CXX_EXTENSIONS OFF)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
 target_compile_options(unit-nearby-scatter-vectors PRIVATE -Wall -Wextra -Wpedantic -ffp-contract=off -frounding-math)
 if(RA2_SANITIZE)
  target_compile_options(unit-nearby-scatter-vectors PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(unit-nearby-scatter-vectors PRIVATE -fsanitize=address,undefined)
 endif()
elseif(MSVC)
 target_compile_options(unit-nearby-scatter-vectors PRIVATE /W4 /fp:strict)
endif()

enable_testing()
add_test(NAME unit-nearby-guards COMMAND unit-nearby-scatter-vectors --guards)
