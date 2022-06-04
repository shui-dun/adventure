cmake_minimum_required(VERSION 3.16)
project(adventure)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_RPATH_USE_ORIGIN on)
set(CMAKE_VERBOSE_MAKEFILE on)
include_directories(include)

if (USE_UNICODE)
    add_compile_options(-DUSE_UNICODE_CHARACTER)
    set(CURSES_NEED_WIDE TRUE)
endif ()

find_package(Curses REQUIRED)

if (UNIX)
    include_directories(${CURSES_INCLUDE_DIR})
else ()
    set(CMAKE_EXE_LINKER_FLAGS -static)
    include_directories("${CURSES_INCLUDE_DIR}/ncurses")
endif ()

find_package(Threads REQUIRED)

aux_source_directory(src src_list)
add_executable(main ${src_list})
target_link_libraries(main ${CURSES_LIBRARIES})
target_link_libraries(main Threads::Threads)
