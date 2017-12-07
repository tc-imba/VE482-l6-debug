#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

int type;
int output_sorting_type;

void parse_input(char* filename, char* output_sort_type){

    char* start = strchr(filename,'_');
    start++;
    char* end = strchr(filename,'.');
    char temp[7];
    strncpy(temp,start,end-start);
    temp[end-start] = '\0';
    if(strcmp(temp,"string") == 0){
        type = 0;
    }
    else if(strcmp(temp,"int") == 0){
        type = 1;
    }
    else if(strcmp(temp,"double") == 0){
        type = 2;
    }


    if(strcmp(output_sort_type,"rand") == 0){
        output_sorting_type = 0;
    }
    else if(strcmp(output_sort_type,"inc") == 0){
        output_sorting_type = 1;
    }
    else if(strcmp(output_sort_type,"dec") == 0){
        output_sorting_type = 2;
    }
}

void fill_dll(dll *list, char* filename){
    FILE *fp=fopen(filename, "r");
    char *line;
    char *buffer;


    line = (char*)malloc(sizeof(char));
    while(fgets(line, 1025, fp) != NULL){
        buffer = strtok(line,"=");
        char* temp = (char *)malloc(sizeof(char));
        strcpy(temp,buffer);
        switch(type) {
            case (0):{
               char* temp2 = (char*)malloc(sizeof(char));
                strcpy(temp2,buffer);
                push_back(list,temp,temp2);
                break;
            }
            case(1):{
                int* temp2 = (int*)malloc(sizeof(int));
                sscanf(buffer,"%d",temp2);
                push_back(list,temp,temp2);
                break;
            }
            case(2):{
                double* temp2 = (double*)malloc(sizeof(double));
                sscanf(buffer,"%lf",temp2);
                push_back(list,temp,temp2);
                break;
            }
            default:{
                fprintf(stderr,"Wtf type invalid");
                exit(1);
            }
        }
    }
    free(line);
    fclose(fp);
}


void run_function(char** argv){
    dll list;
    dll_ctor(&list);
    parse_input(argv[1], argv[2]);
    fill_dll(&list,argv[1]);
    sort(&list,type,output_sorting_type);

    char buffer[15];
    strcpy(buffer, argv[2]);
    switch(type) {
        case (0): {
            strcat(buffer,"_string.txt");
            break;
        }
        case(1):{
            strcat(buffer,"_int.txt");
            break;
        }
        case(2):{
            strcat(buffer,"_double.txt");
            break;
        }
        default:{
            fprintf(stderr,"Wtf invalid type");
            exit(1);
        }
    }
    FILE *ofp;
    ofp = fopen(buffer, "w");
    node *temp = list.head;
    while(temp){
        switch(type) {
            case (0): {
                fprintf(ofp,"%s=%s\n",temp->charptr,((char*)temp->voidptr));
                break;
            }
            case(1):{
                fprintf(ofp,"%s=%d\n",temp->charptr,*((int*)temp->voidptr));
                break;
            }
            case(2):{
                fprintf(ofp,"%s=%lf\n",temp->charptr,*((double*)temp->voidptr));
                break;
            }
            default:{
                fprintf(stderr,"Wtf invalid type");
                exit(1);
            }
        }
        temp = temp->next;
    }
    fclose(ofp);
    dll_dtor(&list);
}
