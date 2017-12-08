//
//  readName.c
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#include "readName.h"
#include "list.h"

void setData(Data D,int d)
{
    D.d=d;
}

void setType(Type T,int t)
{
    T.t=t;
}

void file(char *buf,char* d,char* t)//create filename
{
    strcpy(buf,t);
    size_t len=strlen(buf);
    buf[len]='_';
    strcpy(buf+len,d);
}
