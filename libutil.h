#ifndef _LIBUTIL_H_
#define _LIBUTIL_H_

#ifdef __cplusplus
extern          "C" {
#endif				/** cplusplus **/

#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <getopt.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : + (x) )
#endif

#define LINEAR 1
#define BINARY 2
#define INTERPOLATION 3
#define EXPONENTIAL 4
#define BLOCK 5

void           *safe_malloc(size_t size);
void           *safe_realloc(void *old_mem, size_t new_size);
char           *safe_strdup(const char *str);
float          calc_stdev(float *array, int runs);
float          calc_avg(float *array, int runs);

#ifdef __cplusplus
}
#endif				/** cplusplus **/

#endif				/** _LIBUTIL_H_ **/
