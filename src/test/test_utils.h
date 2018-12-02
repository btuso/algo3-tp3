#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define TEST printf("%s... ", __func__);
#define END_TEST printf("PASSED\n");
#define IGNORE if(0) 
#define given(x)
#define when(x)
#define then(x)
#define And(x)
#define Case(x)
#define cleanup

#endif
