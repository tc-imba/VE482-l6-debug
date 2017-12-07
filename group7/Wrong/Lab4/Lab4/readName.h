//
//  readName.h
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#ifndef readName_h
#define readName_h

typedef struct data
{
    int d;
    /*
     0 for int
     1 for double
     2 for char*
     */
}Data;

typedef struct type
{
    int t;
    /*
     0 for inc
     1 for dec
     2 for rand
     */
}Type;

void setData(Data D,int d);

void setType(Type T,int t);

void file(char *buf,char* d,char* t);//create filename

#endif /* readName_h */
