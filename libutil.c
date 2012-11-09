
#include "libutil.h"

/*
 * safe_malloc ()
 * 
 * Call calloc () and abort if the specified amount of memory cannot be
 * allocated.
 */
void*
safe_malloc(size_t size)
{
    void *memory = NULL;
 
    if ((memory = calloc(1, size)) == NULL) 
	{
		printf("Error in memory allocation\n");
        exit(0);
    }
    return memory;
}

/*
 * safe_realloc ()
 * 
 * Call realloc () and abort if the specified amount of memory cannot be
 * allocated.
 */
void*
safe_realloc(void *old_mem, size_t new_size)
{
    void * newAdd = realloc(old_mem, new_size);
	
    if(newAdd == NULL)
    {
        printf("Error in reallocating memory\n");
        exit(0);
    }
 
    return newAdd;
}

/*
 * safe_strdup ()
 * 
 * Safe version of strdup avoid buffer overflow, etc.
 * 
 */
char*
safe_strdup(const char *str)
{
    str = NULL;
    return 0;
}

/*
 * calc_stdev()
 *
 * Calculate time standard deviation
 *
 */
float calc_stdev(float *array, int runs)
{
    int i = 0;
	float runTimes = 0, sigma = 0, mean = 0, ans = 0, stdev = 0;
	
    for(i=0; i<runs; i++)
	{
	    runTimes += array[i];    
	}
	mean = runTimes/runs;	
	
	for(i=0; i<runs; i++)
	{
	    sigma+=(array[i] - mean)*(array[i] - mean);
	}
	
	ans = sigma/(runs-1);	
	stdev = sqrt(ans);
	
	return stdev;
}

/*
 * calc_avg()
 *
 * Calculate average time
 *
 */
float calc_avg(float *array, int runs)
{
    int i = 0;
	float runTimes = 0, avg = 0;
	
	for(i=0; i<runs; i++)
	{
	    runTimes += array[i];    
	}
	
	avg = runTimes/runs;
	
	return avg;
}
