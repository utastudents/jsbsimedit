cmake_minimum_required(VERSION 3.25.1)

project(JSBSimEdit)

if(TRUE)
    #include(Ctest)
    add_subdirectory(thirdparty/catch2)
    add_subdirectory(test)
endif()

add_subdirectory(thirdparty/pugixml)



# get the files recursively so that programmers don't have to touch this file
file(GLOB_RECURSE SIMEDIT_SOURCES src/*.cpp src/*.c)
if(WIN32)

    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.c
      COMMAND ${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/x64-windows/tools/glib//glib-compile-resources.exe --target=${CMAKE_CURRENT_BINARY_DIR}/resources.c --generate-source exampleapp.gresource.xml
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/Application/
      DEPENDS ${CMAKE_SOURCE_DIR}/src/Application/exampleapp.gresource.xml
    )
   
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/x64-windows/tools/glib/glib-compile-schemas.exe --targetdir=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/Application
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${CMAKE_SOURCE_DIR}/src/Application/org.gtkmm.exampleapp.gschema.xml
    )

else()

    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.c
      COMMAND glib-compile-resources --target=${CMAKE_CURRENT_BINARY_DIR}/resources.c --generate-source exampleapp.gresource.xml
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src/Application/
      DEPENDS ${CMAKE_SOURCE_DIR}/src/Application/exampleapp.gresource.xml
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled
        COMMAND glib-compile-schemas --targetdir=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/Application
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS ${CMAKE_SOURCE_DIR}/src/Application/org.gtkmm.exampleapp.gschema.xml
    )
endif()

# /usr/bin/glib-compile-resources --target=resources.c --sourcedir=. --generate-source exampleapp.gresource.xml
# cc -MT resources.o -MD -MP -MF .deps/resources.Tpo -c -o resources.o `pkg-config --cflags gtk4` resources.c
# g++ -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o `pkg-config --cflags gtkmm-4.0` -std=c++17 -Wall -g main.cc
# g++ -MT exampleappwindow.o -MD -MP -MF .deps/exampleappwindow.Tpo -c -o exampleappwindow.o `pkg-config --cflags gtkmm-4.0` -std=c++17 -Wall -g exampleappwindow.cc
# g++ -MT exampleapplication.o -MD -MP -MF .deps/exampleapplication.Tpo -c -o exampleapplication.o `pkg-config --cflags gtkmm-4.0` -std=c++17 -Wall -g exampleapplication.cc
# g++ -MT exampleappprefs.o -MD -MP -MF .deps/exampleappprefs.Tpo -c -o exampleappprefs.o `pkg-config --cflags gtkmm-4.0` -std=c++17 -Wall -g exampleappprefs.cc
# g++ -o exampleapp resources.o main.o exampleappwindow.o exampleapplication.o exampleappprefs.o `pkg-config --libs gtkmm-4.0`
# /usr/bin/glib-compile-schemas --strict --dry-run --schema-file=org.gtkmm.exampleapp.gschema.xml
# /usr/bin/glib-compile-schemas .

add_executable(${PROJECT_NAME} ${SIMEDIT_SOURCES} ${CMAKE_BINARY_DIR}/resources.c ${CMAKE_CURRENT_BINARY_DIR}/gschemas.compiled )

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 17 C_STANDARD_REQUIRED ON)

# handle the different compilers
if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
	set(CLANG_COMPILE_OPTIONS "-m64;-fno-strict-aliasing;-Wall;-Wextra;-Wpedantic;-Wno-multichar;-Wno-comment;-Wno-sign-compare;-Wno-deprecated;-Wno-reorder;-Winline")
    set(CLANG_COMPILE_DEBUG_OPTIONS "${CLANG_COMPILE_OPTIONS};-g")
    set(CLANG_COMPILE_RELEASE_OPTIONS "${CLANG_COMPILE_OPTIONS};-O3")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CLANG_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CLANG_COMPILE_RELEASE_OPTIONS}>")

elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(GCC_COMPILE_OPTIONS "-m64;-fPIC;-fno-strict-aliasing;-Wall;-Wextra;-Wpedantic;-Wno-multichar;-Wno-comment;-Wno-sign-compare;-funsigned-char;-pthread;-Wno-deprecated;-Wno-reorder;-ftemplate-depth-64;-fno-gnu-keywords;-Winline")
    set(GCC_COMPILE_DEBUG_OPTIONS "${GCC_COMPILE_OPTIONS};-g;-O0")
    set(GCC_COMPILE_RELEASE_OPTIONS "${GCC_COMPILE_OPTIONS};-O3")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${GCC_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${GCC_COMPILE_RELEASE_OPTIONS}>")

elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	set(MSVC_COMPILE_OPTIONS "/MP;/W4;/w34710;/Gy;/Zc:wchar_t;/nologo;/EHsc")
    set(MSVC_COMPILE_DEBUG_OPTIONS "${MSVC_COMPILE_OPTIONS} /ZI /Od")
    set(MSVC_COMPILE_RELEASE_OPTIONS "${MSVC_COMPILE_OPTIONS} /O2")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${MSVC_COMPILE_DEBUG_OPTIONS}>")
    target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${MSVC_COMPILE_RELEASE_OPTIONS}>")
endif()

find_package(PkgConfig REQUIRED)
if(PKG_CONFIG_FOUND)
	message("pkgconfig path: ${PKG_CONFIG_EXECUTABLE}")
endif()
	
pkg_check_modules(GTKMM4 REQUIRED IMPORTED_TARGET gtkmm-4.0)
	
# we use pkgconfig, we must link manually here
target_link_libraries(${PROJECT_NAME} ${GTKMM4_LIBRARIES} pugixml::pugixml)
target_link_directories(${PROJECT_NAME} PUBLIC ${GTKMM4_LIBRARY_DIRS} PUBLIC pugixml::pugixml)
target_include_directories(${PROJECT_NAME} PUBLIC ${GTKMM4_INCLUDE_DIRS} PUBLIC "src" PUBLIC pugixml::pugixml)
target_compile_options(${PROJECT_NAME} PUBLIC ${GTKMM4_CFLAGS_OTHER})

if(WIN32)
    message("Compiling Schemas for Windows")
    message(STATUS ${CMD_EXEC})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND cmd /c ${CMAKE_SOURCE_DIR}/compile_schemas.bat ${CMAKE_BINARY_DIR})
endif()
