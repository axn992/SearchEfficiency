#include "libutil.h"
#include "libset.h"

int
main(int argc, char **argv)
{
    /* Program variables */
    int queries = 0;
    int runs = 0;
    uint64_t keys_found=0;
    float avg,stdev;
    int opt;
	FILE *fp, *fs;
	uint64_t inputData = 0;
	uint64_t searchData = 0;
	uint64_t i = 0;
	uint64_t b = 0;
	char *inputFile=NULL;
	char *searchFile=NULL;
	int algo=0;
	char *algoType;
	int a = 0;
	float *timeArray; 
	
	
	clock_t start, end;
	
	/* 1. Parse Arguments */
    if(argc == 1) {
        fprintf(stderr, "This program needs arguments....\n\n");
    }

    while((opt = getopt(argc, argv, "m:i:s:r:")) != -1) 
	{
        switch(opt) {
            case 'm':
            if(strcmp(optarg, "binary")==0)
            {
                algo=BINARY;
				algoType=optarg;
            }

            else if(strcmp(optarg, "linear")==0)
            {
                algo=LINEAR;
				algoType=optarg;
            }
			
			else if(strcmp(optarg, "interpolation")==0)
            {
                algo=INTERPOLATION;
				algoType=optarg;
            }
			else if(strcmp(optarg, "exponential")==0)
            {
                algo=EXPONENTIAL;
				algoType=optarg;
            }
			
			else if(strcmp(optarg, "block")==0)
            {
                algo=BLOCK;
				algoType=optarg;
            }

            else
            {
                printf("\nInvalid command line argument\n\n");
            }
            break;
		
            case 'i':
			inputFile = optarg;
            break;	

            case 's':
            searchFile = optarg;
            break;
		
            case 'r':
            runs = atoi(optarg);
            break;	
        }
    }
	
    /* 2. Create data empty set_t using function set_create */
    set_t *inputSet = set_create(DEFAULT_SET_SIZE);
	
    /* 3. Use fscanf and the function set_insert to read all data 
          values into new set_t */
    fp = fopen(inputFile, "r");
	
	if(fp==NULL)
	{
	   printf("\nInput file not found!\n");
	   return EXIT_FAILURE;
	}
	
    while(fscanf(fp, "%llu", &inputData) != EOF)
    {
        set_insert(inputSet, inputData);
    }
	
	/* 4. Call the function set_freeze to freeze set - reallocate so the 
          set uses one contiguous memory block of the exact size */
    set_freeze(inputSet);
	fclose(fp);
	
    /* 5. create empty  query set_t */
    set_t *querySet = set_create(DEFAULT_SET_SIZE);
	
    /* 6. read the query set and again use set_freeze*/
	fs = fopen(searchFile, "r");
	
	if(fs==NULL)
	{
	   printf("\nSearch file not found!\n");
	   return EXIT_FAILURE;
	}
	
    while(fscanf(fs, "%llu", &searchData) != EOF)
    {
        set_insert(querySet, searchData);
    }
	
	set_freeze(querySet);
	fclose(fs);
	
	/*
	 * 7. For each key in the query set, run the appropriate search 
              function and time it, based on the mode. Use fscanf to read 
             the key, and only time the search cost
	 */
	 
    /* Run linear search */
    if(algo==LINEAR)
	{
        timeArray = malloc(runs*sizeof(float));	
	    for(a=0; a<runs; a++)
		{
		    start = clock();
		    reset_cmp_cnt();
			i = 0;
			keys_found = 0;
	        while(i!=querySet->items)
            {
		        if((linear_search(inputSet->data, inputSet->items,
				querySet->data[i]))!=-1)
			    {
			        keys_found++;
			    }
			    i++;
            }
            end = clock();
            timeArray[a] = ((float)(end - start))/CLOCKS_PER_SEC;			
        } 		
        queries = querySet->items;		
	}
	
	/* Run binary search */
	else if(algo==BINARY)
	{
	    timeArray = malloc(runs*sizeof(float));	
	    for(a=0; a<runs; a++)
		{
		    start = clock();
		    reset_cmp_cnt();
			i = 0;
			keys_found = 0;
			while(i!=querySet->items)
            {
		        if((binary_search(inputSet->data, inputSet->items,
				querySet->data[i]))!=-1)
			    {
			        keys_found++;
			    }
			    i++;
            }
			end = clock();
            timeArray[a] = ((float)(end - start))/CLOCKS_PER_SEC;			
		}
        queries = querySet->items;
	}
	
	/* Run interpolation search */
	else if(algo==INTERPOLATION)
	{
	    timeArray = malloc(runs*sizeof(float));	
	    for(a=0; a<runs; a++)
		{
		    start = clock();
		    reset_cmp_cnt();
			i = 0;
			keys_found = 0;
			while(i!=querySet->items)
            {
		        if((interpolation_search(inputSet->data, inputSet->items,
				querySet->data[i]))!=-1)
			    {
			        keys_found++;
			    }
			    i++;
            }
			end = clock();
            timeArray[a] = ((float)(end - start))/CLOCKS_PER_SEC;			
		}
        queries = querySet->items;
	}
	
	/* Run exponential search */
	else if(algo==EXPONENTIAL)
	{
	    timeArray = malloc(runs*sizeof(float));	
	    for(a=0; a<runs; a++)
		{
		    start = clock();
		    reset_cmp_cnt();
			i = 0;
			keys_found = 0;
			while(i!=querySet->items)
            {
		        if((exponential_search(inputSet->data, inputSet->items,
				querySet->data[i]))!=-1)
			    {
			        keys_found++;
			    }
			    i++;
            }
			end = clock();
            timeArray[a] = ((float)(end - start))/CLOCKS_PER_SEC;			
		}
        queries = querySet->items;
	}
	
	/* Run block search */
	else if(algo==BLOCK)
	{
	    timeArray = malloc(runs*sizeof(float));
        b = sqrt(inputSet->items);		
	    for(a=0; a<runs; a++)
		{
		    start = clock();
		    reset_cmp_cnt();
			i = 0;
			keys_found = 0;
			while(i!=querySet->items)
            {
		        if((block_search(inputSet->data, inputSet->items,
				querySet->data[i], b))!=-1)
			    {
			        keys_found++;
			    }
			    i++;
            }
			end = clock();
            timeArray[a] = ((float)(end - start))/CLOCKS_PER_SEC;			
		}
        queries = querySet->items;
	}
	
	/* Exit failure if no method found */
	else
	{
	    printf("Wrong Option!\n");
		set_destroy(inputSet);
	    set_destroy(querySet);
		
		return EXIT_FAILURE;
	}

	
    /* 8. output number of items in the data set and the number of 
          search keys */
	printf("ALGORITHM : %s\n", algoType);		  
    fprintf(stdout,"KEYS SEARCHED : %d\n",queries);
    fprintf(stdout,"RUNS : %d\n",runs);
    
    /* 9. reset compare counter and allocate the runtimes array*/


    /* 10. output keys found and number of compares performed */
    fprintf(stdout,"KEYS MATCHED : %llu\n",keys_found);
    fprintf(stdout,"COMPARES : %llu\n",get_cmp_cnt());

    /* 11. calculate the average */
    /* calculate average and standard deviation */
	stdev = calc_stdev(timeArray, runs);
	avg = calc_avg(timeArray, runs);
	
    /*avg = (((float)(end - start))/CLOCKS_PER_SEC) / runs;*/
	
    /* 12. output timings */
    fprintf(stdout,"TIME : %.5f +/- %.5f s\n",avg,stdev);

	/* 13. Make sure you free all malloc'd resources and close open files */
    /* free all sets */

	/*Free the sets and allocated time*/
	set_destroy(inputSet);
	set_destroy(querySet);
	free(timeArray);
	return EXIT_SUCCESS;
}

