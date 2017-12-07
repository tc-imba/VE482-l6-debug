//
//  sort.c
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#include "sort.h"

int INT_INC( void *a, void *b)
{
    int a_v=*(int *)(((Node *) a)->v);
    int b_v=*(int *)(((Node *) b)->v);
    if(a_v>=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int INT_DEC(void *a,void *b)
{
    int a_v=*(int *)(((Node *) a)->v);
    int b_v=*(int *)(((Node *) b)->v);
    if(a_v<=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DOUBLE_INC(void *a,void *b)
{
    double a_v=*(double *)(((Node *) a)->v);
    double b_v=*(double *)(((Node *) b)->v);
    if(a_v>=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DOUBLE_DEC(void *a,void *b)
{
    double a_v=*(double *)(((Node *) a)->v);
    double b_v=*(double *)(((Node *) b)->v);
    if(a_v<=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int STRING_INC(void *a,void *b)
{
    char *a_v=(char *)(((Node *) a)->v);
    char *b_v=(char *)(((Node *) b)->v);
    if(a_v>=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int STRING_DEC(void *a,void *b)
{
    char *a_v=(char *)(((Node *) a)->v);
    char *b_v=(char *)(((Node *) b)->v);
    if(a_v<=b_v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Random(void *a,void *b)
{
    srand(time(0));
    return rand()%2;
}
