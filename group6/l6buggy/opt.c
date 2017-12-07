#include "opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(dlist lists, char *filename) {
	int i, j;
	for (i = 0; filename[i] != '_'; i++);
	i = i+1;
	FILE *fd;
	char line[1024];
	char *addchar;
	printf("reading %s\n", filename);
	fd = fopen(filename, "r");
	if (fd == NULL) {
		printf("Fail to open file %s\n", filename);
		return;
	}
	while (fgets(line, 1024, fd)) {
		for (j = 0; line[j] != '='; j++);
		addchar = (char*)malloc(sizeof(char)*1024);
		memset(addchar,'\0',sizeof(char)*1024);
		memcpy(addchar, line, j);
		j = j+1;
		if (strcmp(&filename[i], "int.txt") == 0) {
			dlistValue value1;
			value1.intValue = atoi(&line[j]);
			dlistAppend(lists, addchar, value1);
		}

		
		else if (strcmp(&filename[i], "double.txt") == 0) {
			dlistValue value1;
			value1.doubleValue = atof(&line[j]);
			dlistAppend(lists, addchar, value1);
		}
		
		else {
			dlistValue value1;
			value1.strValue = (char*)malloc(sizeof(char)*strlen(&line[j]));
			memset(value1.strValue,'\0',sizeof(char)*strlen(&line[j]));
			memcpy(value1.strValue, &line[j], strlen(&line[j])-1);
			dlistAppend(lists,addchar,value1);
		}
		
	}
	
	fclose(fd);
	return;
}

void sort(dlist list, dlist listDst, char *type){
	if (strcmp(type,"inc")) {
		dlistSort(list, listDst,0x03);
	}
	else if(strcmp(type,"dec")){
		dlistSort(list, listDst, 0x02);
	}
	else dlistSort(list, listDst, 0x01);
}



dlistValueType det_type(char *filename){
	int i;
	for (i = 0; filename[i] != '_'; i++);
	i = i+1;
	if (strcmp(&filename[i], "int.txt") == 0){
		return 0x01;
	}
	else if(strcmp(&filename[i], "double.txt") == 0){
		return 0x03;
	}
	else {
		return 0x02;
	}
}