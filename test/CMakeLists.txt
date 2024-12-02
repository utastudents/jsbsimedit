# this is the subproject for Unit Testing

cmake_minimum_required(VERSION 3.25.1)

project(JSBSimEdit_Testing)



# get the files recursively so that programmers don't have to touch this file
# file(GLOB_RECURSE SIMEDIT_SOURCES ${CMAKE_SOURCE_DIR}/src/XML/*.cpp)
# file(GLOB_RECURSE SIMEDIT_SOURCES ${CMAKE_SOURCE_DIR}/src/Metrics/*.cpp)
file(GLOB_RECURSE SIMEDIT_SOURCES ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

# filter out main.cpp
list(FILTER SIMEDIT_SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/src/Application/main.cpp")

#file(GLOB GENERAL_INFO_TESTS GeneralInformation/*.cpp )
#file(GLOB AERO_TESTS Aerodynamics/*.cpp )
#file(GLOB BOUYANT_TESTS BouyantForces/*.cpp )
#file(GLOB ENGINE_TESTS Engines/*.cpp )
#file(GLOB EXTERNAL_RE_TESTS External-Reactions/*.cpp )
#file(GLOB FLIGHT_CONTROL_TESTS Flight-Control-Systems/*.cpp )
#file(GLOB GROUND_TESTS Ground-Reactions/*.cpp )
#file(GLOB INPUT_OUTPUT_TESTS Input-Output/*.cpp )
#file(GLOB MASS_BALANCE_TESTS Mass-Balance/*.cpp )
file(GLOB METRICS_TESTS Metrics/*.cpp )
#file(GLOB PLOT_EDITING_TESTS Plot-Editing/*.cpp )
#file(GLOB PROPULSION_TESTS Propulsion/*.cpp )
#file(GLOB SYSTEM_TESTS System/*.cpp )
file(GLOB XML_TESTS XML/*.cpp )

add_executable(${PROJECT_NAME}  ${GENERAL_INFO_TESTS} ${AERO_TESTS} ${BOUYANT_TESTS}
 ${ENGINE_TESTS} ${EXTERNAL_RE_TESTS} ${FLIGHT_CONTROL_TESTS} ${GROUND_TESTS}
 ${INPUT_OUTPUT_TESTS} ${MASS_BALANCE_TESTS} ${METRICS_TESTS} ${PLOT_EDITING_TESTS}
 ${PROPULSION_TESTS} ${SYSTEM_TESTS} ${XML_TESTS} ${SIMEDIT_SOURCES}
 ${CMAKE_BINARY_DIR}/resources.c ${CMAKE_BINARY_DIR}/gschemas.compiled
 )

#include(Catch)
#catch_discover_tests(JSBSimEdit_Testing)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 17 C_STANDARD_REQUIRED ON)

# handle the different compilers
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CLANG_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CLANG_COMPILE_RELEASE_OPTIONS}>")

elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")

elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${MSVC_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${MSVC_COMPILE_RELEASE_OPTIONS}>")
endif()

find_package(PkgConfig REQUIRED)
if(PKG_CONFIG_FOUND)
	message("pkgconfig path: ${PKG_CONFIG_EXECUTABLE}")
endif()
	
pkg_check_modules(GTKMM4 REQUIRED IMPORTED_TARGET gtkmm-4.0)
	
# we use pkgconfig, we must link manually here
target_link_libraries(${PROJECT_NAME} ${GTKMM4_LIBRARIES} pugixml::pugixml Catch2::Catch2WithMain)
target_link_directories(${PROJECT_NAME} PUBLIC ${GTKMM4_LIBRARY_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${GTKMM4_INCLUDE_DIRS} PUBLIC "../src" PUBLIC pugixml::pugixml Catch2::Catch2WithMain)
target_compile_options(${PROJECT_NAME} PUBLIC ${GTKMM4_CFLAGS_OTHER})
