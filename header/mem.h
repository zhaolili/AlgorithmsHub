#ifndef _MEM_H_
#define _MEM_H_

#include "common_def.h"

CELL** mem_alloc_2D(CELL ***table, int len1, int len2);
void mem_free_2D(CELL **table, int len);

#endif