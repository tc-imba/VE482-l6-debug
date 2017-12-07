cmake_minimum_required(VERSION 2.8)
project(lab4)

add_library(lab4_list_static STATIC list.c)
add_library(lab4_logic_static STATIC logic.c)

add_executable(lab4_interface_static interface.c)
target_link_libraries(lab4_interface_static lab4_logic_static lab4_list_static)

add_library(lab4_list_dynamic SHARED list.c)
add_library(lab4_logic_dynamic SHARED logic.c)
target_link_libraries(lab4_logic_dynamic lab4_list_dynamic)

add_executable(lab4_interface interface.c logic.c list.c)
