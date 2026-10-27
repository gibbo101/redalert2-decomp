cmake_minimum_required(VERSION 3.20)
project(process_terminal_scatter_checks LANGUAGES CXX)
option(RA2_SANITIZE "Enable address and undefined behavior sanitizers" OFF)
find_package(OpenSSL REQUIRED COMPONENTS Crypto)
add_executable(process-terminal-scatter-vectors ../process_terminal_scatter_vectors.cpp
 ../../src/render/RampGeometry.cpp ../../src/assets/RampGeometryData.cpp ../../src/assets/RasterData.cpp
 ../../src/assets/RenderData.cpp ../../src/render/Lighting.cpp ../../src/sim/OriginalRandom.cpp ../../src/sim/UnitDiscovery.cpp ../../src/sim/Targeting.cpp
 ../../src/sim/Drive.cpp ../../src/sim/ActorGroundState.cpp ../../src/sim/GroundMovementPlacement.cpp ../../src/sim/GroundDriveAdvance.cpp ../../src/sim/GroundDriveProcess.cpp ../../src/sim/FootCoordinates.cpp ../../src/sim/UnitNextCell.cpp ../../src/sim/UnitAdmission.cpp ../../src/sim/MovingUnitAdmission.cpp
 ../../src/sim/MovementGate.cpp ../../src/assets/MapCellChildren.cpp ../../src/assets/MapFloorHeight.cpp
 ../../src/assets/MapCoordinateCell.cpp ../../src/assets/MovementData.cpp ../../src/assets/PreparedData.cpp)
target_include_directories(process-terminal-scatter-vectors PRIVATE ../../src)
target_link_libraries(process-terminal-scatter-vectors PRIVATE OpenSSL::Crypto)
target_compile_features(process-terminal-scatter-vectors PRIVATE cxx_std_20)
set_target_properties(process-terminal-scatter-vectors PROPERTIES CXX_EXTENSIONS OFF)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
 target_compile_options(process-terminal-scatter-vectors PRIVATE -Wall -Wextra -Wpedantic -ffp-contract=off -frounding-math)
 if(RA2_SANITIZE)
  target_compile_options(process-terminal-scatter-vectors PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(process-terminal-scatter-vectors PRIVATE -fsanitize=address,undefined)
 endif()
elseif(MSVC)
 target_compile_options(process-terminal-scatter-vectors PRIVATE /W4 /fp:strict)
endif()

enable_testing()
add_test(NAME process-terminal-scatter-guards COMMAND process-terminal-scatter-vectors --guards)
