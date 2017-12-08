//
//  writeFile.h
//  lab4_1
//
//  Created by 季星佑 on 2017/10/25.
//  Copyright © 2017年 季星佑. All rights reserved.
//

#ifndef writeFile_h
#define writeFile_h

#include "list.h"

void INT_print(FILE *f,void *a);

void DOUBLE_print(FILE *f,void *a);

void STRING_print(FILE *f,void *a);

void lprint(List *l,FILE *f,void(*print_mode)(FILE* f, void *));

#endif /* writeFile_h */
