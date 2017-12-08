cmake_minimum_required(VERSION 3.5)
project(group2)

include_directories(includes)
include_directories(lib/includes)

add_library(g2_lib lib/cmp.c lib/sort.debug.c)

add_executable(g2 src/main.c src/dlist.debug.c src/filehandler.debug.c)
target_link_libraries(g2 g2_lib)
