#include "libset.h"
#include <assert.h>

/** Basic Set Operations **/

/* use unsigned int. will overflow for linear search for big files otherwise */
static uint64_t cmp_cnt;

/* reset the comparison counter */
void
reset_cmp_cnt()
{
	cmp_cnt = 0;
}

/* return the value of the comparison counter */
uint64_t
get_cmp_cnt()
{
	return cmp_cnt;
}

/* increase the comparison counter */
static void
inc_cmp_cnt()
{
	cmp_cnt++;
}

/*
 * insert a new item into the set and adjust the size of the underlying
 * dynamic memory block if needed
 */
int
set_insert(set_t * set, uint64_t item)
{
    if(set->lock==LOCKED)
	{
	   printf("Set is locked! Cannot insert items\n");
	   return (TRUE);
	}
	
	if(set->items >= set->n_max)
	{
	    set->size = set->size*2;
	    set->data = safe_realloc(set->data, set->size * sizeof(uint64_t));
	    set->n_max = set->size; /* Change this */
	}
	
    set->data[set->items] = item;
    set->items++;	

	return TRUE;
}

/*
 * create and initialize a set_t data structure of size 'size'
 */
set_t*
set_create(uint64_t size)
{
    set_t *setPtr;
	setPtr = safe_malloc(sizeof(set_t));
	setPtr->data = safe_malloc(size * sizeof(uint64_t));
	setPtr->items = 0;
	setPtr->n_max = size;
	setPtr->size = size;
	setPtr->lock = UNLOCKED;

	return setPtr;
}

/* free all memory used by the set */
void
set_destroy(set_t * set)
{
    free(set->data);
    free(set);
}

/*
 * freeze the set - reallocate the dynamic memory block in the set to a
 * contiguous memory block of the exact size of the array and 'lock' the data
 * structure
 */
int
set_freeze(set_t * set)
{
    set->data = safe_realloc(set->data, set->items * sizeof(uint64_t));
	set->lock = LOCKED;
	
	return 0;
}

/*
 * perform Algorithm 'LinearSearch' on the set and if 'key' is found in the
 * set return it's index otherwise return -1
 */
int64_t
linear_search(uint64_t *set, uint64_t len, uint64_t key)
{
    uint64_t i=0;
    for(i=0; i<len; i++)
	{
	    if(set[i] == key)
		{
		    inc_cmp_cnt();
		    return i;
		}
		
        else if(set[i] > key)
        {
            return -1;
        }
		inc_cmp_cnt();
	}
	
	return -1;
}

/*
 * perform Algorithm 'BinarySearch' on the set and if 'key' is found in the
 * set return it's index otherwise return -1
 */
int64_t
binary_search(uint64_t *set, uint64_t len, uint64_t key)
{
    int l = 0, r = len - 1, m;
	
	while(l<=r)
	{
	    m = (l+(r-l)/2);
		if(key == set[m])
		{
            inc_cmp_cnt();
		    return m;
		}
		
		else if(key < set[m])
		{
		    r = m - 1;
		}
		
		else
		{
		   l = m + 1;
		}
		inc_cmp_cnt();
	}
	
	return -1;	
}

/*
 * perform Algortihm 'InterPolationSearch' on the set and if 'key' is found
 * in the set return it's index otherwise return -1
 */
int64_t
interpolation_search(uint64_t *set, uint64_t len, uint64_t key)
{
    int l = 0, r = len - 1, m;
	
	while(set[l]<key && set[r]>=key)
	{
	    m = l + (((key - set[l])*(r - l)) / (set[r] - set[l]));
		
		if(set[m] < key)
		{
		    l = m + 1;
		}
		
		else if(set[m] > key)
		{
		    r = m - 1;
		}
		
		else
		{
            inc_cmp_cnt();
		    return m;
		}
		
		inc_cmp_cnt();
	}
	
	if(set[l] == key)
	{
	    inc_cmp_cnt();
	    return l;
	}
	
	else
	{ 
	    return -1;
	}
}

/*
 * perform Algorithm 'ExponentialSearch' on the set and if 'key' is found in
 * the set return it's index otherwise return -1
 */
int64_t
exponential_search(uint64_t *set, uint64_t len, uint64_t key)
{
    int pos = 2, prev = 0, n = len - 1, newLen = 0, result = 0;
	while(pos < n && set[pos] <= key)
	{
	    prev = pos;
	    pos = pos * 2;
        inc_cmp_cnt();
	}
	
	if(pos > (n - 1))
	{
	    pos = n - 1;
	}
	
	newLen = pos - prev;

	result = binary_search(set+prev, newLen+2, key);
	
	if(result == -1)
	{
	    return -1;
	}
	
	else
	{
	    return result + prev;
	}
	
}

/*
 * perform Algorithm 'BlockSearch' on the set and if 'key' is found in the
 * set return it's index otherwise return -1
 * 
 * parameter 'b' referes to a fixed block size of probe positions
 */
int64_t
block_search(uint64_t *set, uint64_t len, uint64_t key, uint64_t b)
{
    int pos = b, prev = 0, n = len - 1, newLen = 0, result = 0;
	
	while(pos < n && set[pos] < key)
	{
	    prev = pos;
		pos = pos + b;
		inc_cmp_cnt();
	}
	
	if(pos > (n - 1))
	{
	    pos = n - 1;
	}
	
	newLen = pos - prev;
	
	result = binary_search(set+prev, newLen+2, key);
	
	if(result == -1)
	{
	    return -1;
	}
	
	else
	{
	    return (result + prev);
	}
	
}

