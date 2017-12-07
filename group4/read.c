#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "read.h"
#include "dlist.h"

enum dlistValueType_t gettype(char * filename)
{
	char *c="char";
	char *i="int";
	char *d="double";
	if (strstr(filename, c)) {return 1;}
	else if (strstr(filename, i)) {return 2;}
	else if (strstr(filename, d)) {return 3;}
	else {return 0;}
}
enum dlistSortMethod_t getorder(char* ordername)
{
	char *i="inc";
	char *d="dec";
	char *r="rand";
	if (strstr(ordername, i)) {return 1;}
	else if (strstr(ordername, d)) {return 2;}
	else if (strstr(ordername, r)) {return 3;}
	else {return 4;}
}
void getfile(list* dlist, FILE* file)
{
	int type;
	type=dlist->type;
	fseek(file, 0, SEEK_END);
	int size;
	size=ftell(file);
	fseek(file, 0, SEEK_SET);
	char *a=(char*)malloc((size)* sizeof(char));
	fread(a, size, sizeof(char),file);
	a[size-1]=0;
	char *t=strtok(a, "=\n");
	char *str;
	while (t!= NULL)
	{
		str=t;
		t=strtok(NULL, "=\n");
		if (type==1)
		{
		    char* a;
            dlistValue temp;
			a=(char*)malloc(strlen(t)*sizeof(char));
			//temp=(union dlistValue_t*)malloc(sizeof(union dlistValue_t));
			strcpy(a,t);
			temp.strValue=a;
			dlistAppend(dlist,str,temp);
		}
		else if (type==2)
		{
		    int a;
			dlistValue temp;
			a=atof(t);
			//temp=(union dlistValue_t*)malloc(sizeof(union dlistValue_t));
			temp.intValue=a;
			dlistAppend(dlist,str,temp);
		}
		else if (type==3)
		{
		    double a;
			dlistValue temp;
			a=atoi(t);
			//temp=(union dlistValue_t*)malloc(sizeof(union dlistValue_t));
			temp.doubleValue=a;
			dlistAppend(dlist,str,temp);
		}
		t=strtok(NULL, "=\n\0");
	}

}
void fileprint(list* dlist,FILE* fp)
{
    if (dlist->type==1)
    {
    node *cursor=dlist->first;
    while(cursor!=dlist->last)
    {
        fprintf(fp,"%s=%s\n", cursor->str, cursor->data.strValue);
        cursor=cursor->next;
    }
    fprintf(fp,"%s=%s\n", cursor->str, cursor->data.strValue);
    }
    else if (dlist->type==2)
    {
    node *cursor=dlist->first;
    while(cursor!=dlist->last)
    {
        fprintf(fp,"%s=%d\n", cursor->str, cursor->data.intValue);
        cursor=cursor->next;
    }
    fprintf(fp,"%s=%d\n", cursor->str, cursor->data.intValue);
    }
    else if (dlist->type==3)
    {
    node *cursor=dlist->first;
    while(cursor!=dlist->last)
    {
        fprintf(fp,"%s=%lf\n", cursor->str, cursor->data.doubleValue);
        cursor=cursor->next;
    }
    fprintf(fp,"%s=%lf\n", cursor->str, cursor->data.doubleValue);
    }
}
