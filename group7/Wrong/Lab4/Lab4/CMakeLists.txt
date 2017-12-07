cmake_minimum_required(VERSION 3.8)
project(Lab4)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c dlist.h dlist.c list.h list.c sort.h sort.c writeFile.h writeFile.c readName.h readName.c)
add_executable(Lab4 ${SOURCE_FILES})