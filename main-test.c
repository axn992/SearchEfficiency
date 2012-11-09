#include "libutil.h"
#include "libset.h"
#define len 10
#define bsize 10

int
main(int argc, char **argv)
{
    argc = 0;
	argv = NULL;

	int i = 0;
	int found = 0;
    /* test set funtionality */
    uint64_t array1[len] = {3,4,7,8,10,13,15,23,27,30};
	uint64_t array2[len] = {1,2,3,6,13,30,41,55,66,70};
	
    /* test linear search */
    while(i!=len)
    {
        if((linear_search(array1, len, array2[i]))==9)
        {
            printf("[LINEAR SEARCH] - Search last entry  - OK\n");
        }

	    if((linear_search(array1, len, array2[i]))==0)
		{
		    printf("[LINEAR SEARCH] - Search first entry - OK\n");
		}
		
		if((linear_search(array1, len, array2[i]))==5)
		{
		    printf("[LINEAR SEARCH] - Search middle entry - OK\n");
		}
		
		if((linear_search(array1, len, 31))!=-1)
		{
		    found = 1;
		}
		
        i++;
    }
	
	if(found == 0)
	{
	    printf("[LINEAR SEARCH] - Search larger entry - OK\n\n");
	}
	
    /* test binary search */
	/* Refresh counters */
	i = 0;
	found = 0;
    while(i!=len)
    {
        if((binary_search(array1, len, array2[i]))==9)
        {
            printf("[BINARY SEARCH] - Search last entry  - OK\n");
        }

	    if((binary_search(array1, len, array2[i]))==0)
		{
		    printf("[BINARY SEARCH] - Search first entry - OK\n");
		}
		
		if((binary_search(array1, len, array2[i]))==5)
		{
		    printf("[BINARY SEARCH] - Search middle entry - OK\n");
		}
		
		if((binary_search(array1, len, 31))!=-1)
		{
		    found = 1;
		}
		
        i++;
    }
	
	if(found == 0)
	{
	    printf("[BINARY SEARCH] - Search larger entry - OK\n\n");
	}
	
    /* test interpolation search */
    /* Refresh counters */
	i = 0;
	found = 0;
    while(i!=len)
    {
        if((interpolation_search(array1, len, array2[i]))==9)
        {
            printf("[INTERPOLATION SEARCH] - Search last entry  - OK\n");
        }

	    if((interpolation_search(array1, len, array2[i]))==0)
		{
		    printf("[INTERPOLATION SEARCH] - Search first entry - OK\n");
		}
		
		if((interpolation_search(array1, len, array2[i]))==5)
		{
		    printf("[INTERPOLATION SEARCH] - Search middle entry - OK\n");
		}
		
		if((interpolation_search(array1, len, 31))!=-1)
		{
		    found = 1;
		}
		
        i++;
    }
	
	if(found == 0)
	{
	    printf("[INTERPOLATION SEARCH] - Search larger entry - OK\n\n");
	}
	
    /* test exponential search */
    /* Refresh counters */
	i = 0;
	found = 0;
    while(i!=len)
    {
        if((exponential_search(array1, len, array2[i]))==9)
        {
            printf("[EXPONENTIAL SEARCH] - Search last entry  - OK\n");
        }

	    if((exponential_search(array1, len, array2[i]))==0)
		{
		    printf("[EXPONENTIAL SEARCH] - Search first entry - OK\n");
		}
		
		if((exponential_search(array1, len, array2[i]))==5)
		{
		    printf("[EXPONENTIAL SEARCH] - Search middle entry - OK\n");
		}
		
		if((exponential_search(array1, len, 31))!=-1)
		{
		    found = 1;
		}
		
        i++;
    }
	
	if(found == 0)
	{
	    printf("[EXPONENTIAL SEARCH] - Search larger entry - OK\n\n");
	}
	
    /* test block search */
    /* Refresh counters */
	i = 0;
	found = 0;
    while(i!=len)
    {
        if((block_search(array1, len, array2[i], bsize))==9)
        {
            printf("[BLOCK SEARCH] - Search last entry  - OK\n");
        }

	    if((block_search(array1, len, array2[i], bsize))==0)
		{
		    printf("[BLOCK SEARCH] - Search first entry - OK\n");
		}
		
		if((block_search(array1, len, array2[i], bsize))==5)
		{
		    printf("[BLOCK SEARCH] - Search middle entry - OK\n");
		}
		
		if((block_search(array1, len, 31, bsize))!=-1)
		{
		    found = 1;
		}
		
        i++;
    }
	
	if(found == 0)
	{
	    printf("[BLOCK SEARCH] - Search larger entry - OK\n\n");
	}
	
	return EXIT_SUCCESS;
}

