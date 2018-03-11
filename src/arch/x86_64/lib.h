#ifndef __LIB_H
#define __LIB_H

#include "types.h"

extern void memcpy(void* dest, void* src, int numOfBytes);
extern char* itoa(uint64_t num, char* string, int base);

#endif
