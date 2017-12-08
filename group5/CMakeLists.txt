cmake_minimum_required(VERSION 3.5)
project(group5)

include_directories(lab6/bug1)
add_executable(g5 lab6bug.debug.c)
add_executable(g5_bug1 lab6/main.c lab6/bug1/list.c lab6/bug1/dlist.c)
add_executable(g5_bug2 lab6/main.c lab6/bug2/list.c lab6/bug2/dlist.c)
