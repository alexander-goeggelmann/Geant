cmake_minimum_required(VERSION 2.6)
project(muonsimulation)

include_directories(
    "/home/alexander/Geant/geant4.10.06.p03-install/include/Geant4/")
link_directories(
    "/home/alexander/Geant/geant4.10.06.p03-install/lib/")


list(APPEND CMAKE_PREFIX_PATH $ENV{GEANT4SYS})
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB sources
    ${PROJECT_SOURCE_DIR}/ActionInitialization/src/*.cpp
    ${PROJECT_SOURCE_DIR}/DetectorConstruction/src/*.cpp
    ${PROJECT_SOURCE_DIR}/EventAction/src/*.cpp
    ${PROJECT_SOURCE_DIR}/PrimaryGenerator/src/*.cpp
    ${PROJECT_SOURCE_DIR}/RunAction/src/*.cpp
    ${PROJECT_SOURCE_DIR}/SteppingAction/src/*.cpp
    ${PROJECT_SOURCE_DIR}/PhysicsList/src/*.cpp)
file(GLOB headers
    ${PROJECT_SOURCE_DIR}/ActionInitialization/include/*.hh
    ${PROJECT_SOURCE_DIR}/DetectorConstruction/include/*.hh
    ${PROJECT_SOURCE_DIR}/EventAction/include/*.hh
    ${PROJECT_SOURCE_DIR}/PrimaryGenerator/include/*.hh
    ${PROJECT_SOURCE_DIR}/RunAction/include/*.hh
    ${PROJECT_SOURCE_DIR}/SteppingAction/include/*.hh
    ${PROJECT_SOURCE_DIR}/PhysicsList/include/*.hh
    ${PROJECT_SOURCE_DIR}/safe_delete.hh
    ${PROJECT_SOURCE_DIR}/output.hh)

add_executable(muonsimulation main.cpp ${sources} ${headers})
target_link_libraries(muonsimulation
    ${Geant4_LIBRARIES}
    ${Boost_LIBRARIES})

set(MAC_FILES
    run_init.mac
    set_primary.mac
    seed_10.mac
    seed_20.mac
    seed_30.mac
    seed_40.mac
    viewer.mac
    setup.init)

foreach(_script ${MAC_FILES})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY)
endforeach()

add_library(SimulationLib ${sources} ${headers})
target_include_directories(SimulationLib PUBLIC .)
