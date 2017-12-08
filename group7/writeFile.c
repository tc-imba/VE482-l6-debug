//
//  writeFile.c
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#include "writeFile.h"

void INT_print(FILE *f,void *a)
{
    fprintf(f,"%d",*(int *)(a));
}

void DOUBLE_print(FILE *f,void *a)
{
    fprintf(f,"%f",*(double *)(a));
}

void STRING_print(FILE *f,void *a)
{
    fprintf(f,"%s",(char *)(a));
}
