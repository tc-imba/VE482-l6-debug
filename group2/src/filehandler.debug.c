#include "dlist.h"

void file_write(char *outfile, dlist this)
{
    printf("Writing to %s\n", outfile);
    int fout = open(outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    dup2(fout, STDOUT_FILENO);
    close(fout);
    dlistPrint(this);
}

void file_read(char *argv[], char *token, dlist this)
{
    char line[100], tmp_line[100];
    int read;
    printf("Reading %s\n", argv[1]);
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
        perror("File open error\n");
    char *key, *strval;
    dlistValue value;

    if (dlistIsEmpty(this))
        while (1)
        {
            read = fscanf(fin, "%s", line);
            if (read < 0)
                break;
            key = strtok(line, "= \t\a\r\n");
            strval = strtok(NULL, "= \t\a\r\n");
            //printf("data type: %d\n", CAST(this, vector *)->type);
            switch (CAST(this, vector *)->type)
            {
            case DLIST_STR:
                value.strValue = malloc(sizeof(char) * (strlen(strval) + 1));
                strcpy(value.strValue, strval);
                break;
            case DLIST_INT:
                value.intValue = atoi(strval);
                break;
            case DLIST_DOUBLE:
                value.doubleValue = atoi(strval);
                break;
            default:
                value.strValue = NULL;
            }
            dlistAppend(this, key, value);
        }
    fclose(fin);
}
