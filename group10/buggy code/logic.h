#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "list.h"

void parse_input(char* filename, char* output_sort_type);

void fill_dll(dll *list, char* filename);

void run_function(char** argv);

#endif // LOGIC_H_INCLUDED
