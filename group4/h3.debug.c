#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"
#include "read.h"
#include <time.h>

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    char *ordername = argv[2];
    enum dlistValueType_t vt;
    vt = gettype(filename);
    list *ol;
    list *rl;
    ol = createDlist(vt);
    rl = createDlist(vt);
    FILE *inputfile;
    inputfile = fopen(filename, "r");
    printf("reading %s\n", filename);
    enum dlistSortMethod_t st;
    st = getorder(ordername);
    char *filename2 = (char *) malloc(sizeof(char));
    if (vt == 1) {
        if (st == 1) { filename2 = "inc_char.txt"; }
        else if (st == 2) { filename2 = "dec_char.txt"; }
        else if (st == 3) { filename2 = "rand_char.txt"; }
        else {
            printf("unknown type");
            return -1;
        }
    } else if (vt == 2) {
        if (st == 1) { filename2 = "inc_int.txt"; }
        else if (st == 2) { filename2 = "dec_int.txt"; }
        else if (st == 3) { filename2 = "rand_int.txt"; }
        else {
            printf("unknown type");
            return -1;
        }
    } else if (vt == 3) {
        if (st == 2) { filename2 = "dec_double.txt"; }
        else if (st == 1) { filename2 = "inc_double.txt"; }
        else if (st == 3) { filename2 = "rand_double.txt"; }
        else {
            printf("unknown type");
            return -1;
        }
    } else {
        printf("unknown method");
        return -1;
    }
    FILE *fp;
    fp = fopen(filename2, "w+");
    getfile(ol, inputfile);
    printf("sorting elements\n");
    dlistSort(ol, rl, st);
    printf("writing %s\n", filename2);
    fileprint(rl, fp);
    fclose(inputfile);
    fclose(fp);
    dlistFree(ol);
    dlistFree(rl);
    return 0;
}
