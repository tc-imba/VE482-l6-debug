#include "opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

	dlist list;
	dlist listDst;

	list = createDlist(det_type(argv[1]));
	listDst = createDlist(det_type(argv[1]));

	readfile(list,argv[1]);
	sort(list, listDst, argv[2]);
	dlistPrint(listDst);
	dlistFree(list);
	dlistFree(listDst);
	return 0;
}

