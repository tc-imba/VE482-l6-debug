#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

int main(int argc, char** argv) {
    printf("Hello,user!\n");
    printf("Sorting for you...\n");
    if(argc != 3){
        fprintf(stderr,"Usage: ./Hw3 filename output_sort_type");
        exit(1);
    }
    run_function(argv);
    printf("The file is sorted!\n");
    return 0;
}
