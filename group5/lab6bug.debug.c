#include<stdio.h>
#include<malloc.h>  
#include<stdlib.h>  
#include<string.h>


/*node definition*/
typedef struct node
{
	struct node	*next;
	struct node	*prev;
	void		*op;//somedata
	char		*string; //somestring
}node;

/*Dlist*/
typedef struct Dlist
{
	node *first;
	node *last;
	int size;
}Dlist;

/*Initialization*/
void InitDlist(Dlist *Dlist) {
	Dlist->first = NULL;
	Dlist->last = NULL;
	Dlist->size = 0;
}

/*Insert Front*/
void insertFront(Dlist *Dlist, void *op, char* string) {
	node *np = (node*)malloc(128 * sizeof(node));
	np->next = Dlist->first;
	np->prev = NULL;
	np->op = op;
	np->string = string;
	if (Dlist->first) Dlist->first->prev = np;
	else Dlist->last = np;
	Dlist->first = np;
}

void insertBack(Dlist *Dlist, void *op, char* string) {
	node *np = (node*)malloc(sizeof(node));
	np->next = NULL;
	np->prev = Dlist->last;
	np->op = op;
	np->string = string;
	if (Dlist->last)Dlist->last->next = np;
	else Dlist->first = np;
	Dlist->last = np;
}

/*remove*/
void* removeFront(Dlist *Dlist) {
	node *victim = Dlist->first;
	void* result = victim->op;
	Dlist->first = victim->next;
	if (Dlist->first != NULL) Dlist->first->prev = NULL;
	else Dlist->last = NULL;
	free(victim);
	return result;
}
int isEmpty(Dlist* Dlist) {
	if (Dlist->first == NULL) return 1;
	return 0;
}
void removeAll(Dlist* Dlist) {
	while (isEmpty(Dlist) == 0) {
		void *op = removeFront(Dlist);
		free(op);
	}
}


void insert(node* cp, void *op, char* string) {
	node *np = (node*)malloc(sizeof(node));
	np->next = cp->next;
	np->prev = cp;
	cp->next = np;
	cp->next->prev = np;
	np->op = op;
	np->string = string;
}
/*****************************/
void swap(Dlist *Dlist, node *p, node *t)
{
	node *temp;
	if (t->next == NULL)
	{
		if (p->next == t)
		{
			t->next = p;
			t->prev = p->prev;
			p->next = NULL;
			if (p->prev == NULL) {
				p->prev = t;
			}
			else {
				p->prev->next = t;
				p->prev = t;
			}
		}
		else
		{
			t->next = p->next;
			t->prev->next = p;
			temp = t->prev;
			t->prev = p->prev;
			p->next->prev = t;
			p->next = NULL;
			p->prev->next = t;
			p->prev = temp;
		}
	}
	else
	{
		if (p->next == t)
		{
			t->next->prev = p;
			temp = t->next;
			t->next = p;
			t->prev = p->prev;
			p->next = temp;
			p->prev->next = t;
			p->prev = t;
		}
		else
		{
			t->next->prev = p;
			temp = t->next;
			t->next = p->next;
			p->next->prev = t;
			p->next = temp;
			t->prev->next = p;
			temp = t->prev;
			t->prev = p->prev;
			p->prev->next = t;
			p->prev = temp;
		}
	}
}

void Sort(Dlist* Dlist, char* type)
{
	node *i, *j, *k;
	if (!Dlist->first)
		return;
	for (i = Dlist->first->next; i->next != NULL; i = k->next)
	{
		for (j = i->next, k = i; j != NULL; j = j->next) {

			if (strcmp(type, "int") == 0) {
				int temp1, temp2;
				temp1 = k->op;
				temp2 = j->op;
				if (temp1 > temp2)	k = j;
			}
			else if (strcmp(type, "double") == 0) {
				double *temp1, *temp2;
				temp1 = k->op;
				temp2 = j->op;
				if (*temp1 > *temp2) k = j;
			}
			else if (strcmp(type, "char") == 0) {
				char* temp1, *temp2;
				temp1 = k->op;
				temp2 = j->op;
				if (strcmp(temp1, temp2) > 0)k = j;
			}
		}
		if (k != i)
			swap(Dlist, i, k);
	}
}
/*****************************/




int main(int argc, char *argv[]) {
	if (strcmp(argv[2], "rand") != 0) {
		FILE * in_file;
		char line[1024];
		Dlist *list;
		list = (Dlist*)malloc(sizeof(Dlist));
		InitDlist(list);
		char *string;
		char* data_s;
		void* data;
		char* type;
		char* end;
		double *data_d;
		printf("reading %s\n", argv[1]);
		//read
		in_file = fopen(argv[1], "rt");
		if (in_file == NULL) {
			printf("can't open file");
			return -1;
		}
		type = end = argv[1];
		//assign type
		int len = strlen(argv[1]);
		while (type[0] != '_')type = ++end;
		type++;
		while (end[0] != '.')end++;
		*end = '\0';

		int i = 0, j;
		while (fgets(line, 1024, in_file)) {
			int len = strlen(line);
			for (j = 0; j < len; ++j) {
				if (line[j] == '=') break;
			}

			//assign somestring
			string = (char*)malloc(128 * sizeof(char));
			strncpy(string, line, j);
				//assign somedata
				data_s = end = line;
			for (; j >= 0; --j) {
				end = ++data_s;
			}
			while (end[0] != '\n'&&strlen(end) != 0)end++;
			*end = '\0';
			if (strcmp(type, "int") == 0) {
				int *data_i = (int*)malloc(1024 * sizeof(int));
				*data_i = atoi(data_s);
				insertFront(list, data_i, string);
			}
			else if (strcmp(type, "double") == 0) {
				data_d = (double*)malloc(1024 * sizeof(double));
				*data_d = atof(data_s);
				insertFront(list, data_d, string);
			}
			else if (strcmp(type, "char") == 0) {
				data = (char*)malloc(1024 * sizeof(char));
				strcpy(data, data_s);
				insertFront(list, data, string);
			}
			i++;
		}
		if (strcmp(argv[2], "inc") == 0) {
			printf("sorting elements\n");
			//sort
			insertFront(list, data_d, string);
			Sort(list, type);
			//write
			FILE* file_out;
			char* output;
			//char*t;
			output = (char*)malloc(sizeof(char));
			strcpy(output, argv[2]);
			strcat(output, "_");
			strcat(output, type);
			strcat(output, ".txt");
			file_out = fopen(output, "w");
			printf("writing %s\n", output);
			node* current; current = list->first->next;
			if (strcmp(argv[2], "inc") == 0) {
				current = list->first->next;
				while (current->next != NULL) {
					if (strcmp(type, "int") == 0) fprintf(file_out, "%s=%d\n", current->string, current->op);
					else if (strcmp(type, "char") == 0)fprintf(file_out, "%s=%s\n", current->string, current->op);
					else if (strcmp(type, "double") == 0) {
						double *temp = current->op;
						fprintf(file_out, "%s=%f\n", current->string, *temp);
					}
					current = current->next;
				}
				if (strcmp(type, "int") == 0) fprintf(file_out, "%s=%d\n", current->string, current->op);
				else if (strcmp(type, "char") == 0)fprintf(file_out, "%s=%s\n", current->string, current->op);
				else if (strcmp(type, "double") == 0) {
					double * temp = current->op;
					fprintf(file_out, "%s=%f\n", current->string, *temp);
				}
			}
			else if (strcmp(argv[2], "dec") == 0) {
				current = list->first;
				while (current->next != NULL)current = current->next;
				while (current->prev != NULL) {
					if (strcmp(type, "int") == 0) fprintf(file_out, "%s=%d\n", current->string, current->op);
					else if (strcmp(type, "char") == 0)fprintf(file_out, "%s=%s\n", current->string, current->op);
					else if (strcmp(type, "double") == 0) {
						double *temp = current->op;
						fprintf(file_out, "%s=%f\n", current->string, *temp);
					}
					current = current->prev;
				}
			}
			fclose(file_out);
		}
		else {
			int flag = 0;
			char* key = argv[2];
			node* current = list->first;
			while (current->next != NULL) {
				if (strcmp(current->string, key) == 0) {
					flag = 1;
					if (strcmp(type, "int") == 0) printf("key:%s,data:%d\n", key, current->op);
					else if (strcmp(type, "char") == 0)printf("key:%s,data:%s\n", key, current->op);
					else if (strcmp(type, "double") == 0) {
						double *temp = current->op;
						printf("key:%s,data:%s\n", key, *temp);
					}
					break;
				}
				current = current->next;
			}
			if (flag == 0) {
				if (strcmp(current->string, key) == 0) {
					flag == 1;
					if (strcmp(type, "int") == 0) printf("key:%s,data:%d\n", key, current->op);
					else if (strcmp(type, "char") == 0)printf("key:%s,data:%s\n", key, current->op);
					else if (strcmp(type, "double") == 0) {
						double *temp = current->op;
						printf("key:%s,data:%s\n", key, *temp);
					}
				}
				else printf("No key: %s\n", key);
			}

		}
		//free
		fclose(in_file);
		//free(string);
		//free(output);
		//free(list);
	}
	else {
		printf("reading %s\n", argv[1]);
		printf("sorting elements\n");
		printf("writing %s\n", argv[1]);
	}
	return 0;
}