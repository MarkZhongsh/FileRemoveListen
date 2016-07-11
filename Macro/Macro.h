#ifndef MACRO_H_H_
#define MACRO_H_H_

#include <stdio.h>

#ifdef DSDEBUG
#define PRINT_LOG(...) printf(__VA_ARGS__)
#else
#define PRINT_LOG(...) 
#endif

#endif
