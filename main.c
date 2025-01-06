#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY1_SIZE 1024*1024*256
#define ARRAY2_SIZE 256*256

#define VALUE_RANGE 40

typedef struct
{
    int value;
    int index;  //random data to showcase usecase
} randomStruct;

#define BOUNDARY_CHECK

void main()
{
    randomStruct * array1 = malloc(sizeof(randomStruct)*ARRAY1_SIZE);
    randomStruct * array2 = malloc(sizeof(randomStruct)*ARRAY2_SIZE);

    srand(time(NULL));

    //fill with data
    for(int i = 0; i < ARRAY1_SIZE; i++)
    {
        array1[i].value = rand() % VALUE_RANGE;
        array1[i].index = i;
    }

    //start method


    int * valueCounter = calloc(sizeof(int), VALUE_RANGE);

    clock_t start = clock();

    //get amount of instances of each value
    for(int i = 0; i < ARRAY1_SIZE; i++)
    {
        #ifdef BOUNDARY_CHECK
            if(array1[i].value < 0 && array1[i].value >= VALUE_RANGE)
                continue;
        #endif

        valueCounter[array1[i].value]++;
    }

    //count available slots per possible value
    int availableSpots = ARRAY2_SIZE;
    for(int i = VALUE_RANGE; i >= 0; i--)
    {
        if(availableSpots == 0)
        {
            valueCounter[i] = 0;
            continue;
        }

        if(availableSpots < valueCounter[i])
        {
            valueCounter[i] = availableSpots;
            availableSpots = 0;
            continue;
        }

        if(availableSpots >= valueCounter[i])
        {
            availableSpots -= valueCounter[i];
        }
    }

    //include element when its value has slots left
    int array2_index = 0;
    int counter = 0;
    for(int i = 0; i < ARRAY1_SIZE; i++)
    {
        #ifdef BOUNDARY_CHECK
            if(array1[i].value < 0 && array1[i].value >= VALUE_RANGE)
                continue;
        #endif

        if(valueCounter[array1[i].value] == 0)
            continue;
        
        valueCounter[array1[i].value]--;

        array2[array2_index] = array1[i];
        array2_index++;
        counter++;

        if(counter == ARRAY2_SIZE)
            break;
    }

    //finished
    printf("took %.2fms with %i top elements taken from %i total\n", (clock()-start)/(CLOCKS_PER_SEC/1000.0f), ARRAY2_SIZE, ARRAY1_SIZE);
    printf("array2 index to anti optimize %i\n", array2[rand()%ARRAY2_SIZE].index);
}