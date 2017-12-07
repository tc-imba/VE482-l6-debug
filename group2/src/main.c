#include "dlist.h"

int main(int argc, char *argv[])
{
    dlistSortMethod method;
    srand(time(NULL));
    char *token;
    char infile[100], outfile[100];
    //printf("before format file\n");
    //file_format(argv, outfile, infile);

    strcpy(infile, argv[1]);
    token = strtok(infile, "._ \t\a\r\n");
    token = strtok(NULL, "._ \t\a\r\n");
    strcpy(outfile, argv[2]);
    strcat(outfile, "_");
    strcat(outfile, token);
    strcat(outfile, ".txt");

    dlist dlist_sample, dlist_dst;
    dlistValueType type;
    //printf("token: %s\n", token);
    if (strcmp(token, "int") == 0)
        type = DLIST_INT;
    else if (strcmp(token, "double") == 0)
        type = DLIST_DOUBLE;
    else if (strcmp(token, "str") == 0)
        type = DLIST_STR;
    else
        type = DLIST_UNKOWN;
    //printf("data type: %d\n", type);
    dlist_sample = createDlist(type);
    dlist_dst = createDlist(type);
    //printf("list created\n");
    file_read(argv, token, dlist_sample);
    //printf("read to list\n");
    if (strcmp(argv[2], "inc") == 0)
        method = DLIST_SORT_INC;
    else if (strcmp(argv[2], "dec") == 0)
        method = DLIST_SORT_DEC;
    else if (strcmp(argv[2], "rand") == 0)
        method = DLIST_SORT_RAND;
    else
        method = DLIST_SORT_UNKOWN;
    //printf("sort type: %d\n", method);
    //dlistPrint(dlist_sample);
    dlistSort(dlist_sample, dlist_dst, method);
    //printf("sorted\n");
    file_write(outfile, dlist_dst);
    //printf("write to file\n");
    dlistFree(dlist_sample);
    dlistFree(dlist_dst);
    return 0;
}
