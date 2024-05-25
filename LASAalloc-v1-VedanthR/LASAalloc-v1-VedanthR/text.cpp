#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "LASAalloc.h"

// Uncomment the following line to switch to SIMPLETEST2
//#define SIMPLETEST2

#ifdef SIMPLETEST1
int main(int argc, char *argv[])
{
    LASAalloc lasa;

    char *array;
    int i;

    array = (char *)lasa.lalloc(10);
    if(array == NULL)
    {
        fprintf(stderr,"call to lasa.lalloc() failed\n");
        fflush(stderr);
        exit(1);
    }

    for(i=0; i < 9; i++)
    {
        array[i] = 'a' + i;
    }
    array[9] = 0;

    printf("here is my nifty new string: %s\n",array);

    lasa.lfree(array);

    return 0;
}
#endif // SIMPLETEST1

#ifdef SIMPLETEST2
int main(int argc, char *argv[])
{
    LASAalloc lasa;

    char *a1;
    char *a2;
    char *a3;
    char *a4;

    a1 = (char *)lasa.lalloc(128);
    if(a1 == NULL)
    {
        fprintf(stderr,"call to lasa.lalloc(128) failed\n");
        fflush(stderr);
        exit(1);
    }

    printf("FREE LIST after lalloc(128)\n");
    lasa.display(lasa.freeList);

    a2 = (char *)lasa.lalloc(32);
    if(a2 == NULL)
    {
        fprintf(stderr,"first call to lasa.lalloc(32) failed\n");
        fflush(stderr);
        exit(1);
    }

    printf("FREE LIST after lalloc(32)\n");
    lasa.display(lasa.freeList);

    lasa.lfree(a1);

    printf("FREE LIST after free of first 128 lalloc()\n");
    lasa.display(lasa.freeList);

    a3 = (char *)lasa.lalloc(104);
    if(a3 == NULL)
    {
        fprintf(stderr,"call to lasa.lalloc(104) failed\n");
        fflush(stderr);
        exit(1);
    }

    printf("FREE LIST after lalloc(104)\n");
    lasa.display(lasa.freeList);

    a4 = (char *)lasa.lalloc(8);
    if(a4 == NULL)
    {
        fprintf(stderr,"call to lasa.lalloc(8) failed\n");
        fflush(stderr);
        exit(1);
    }
    printf("FREE LIST after lalloc(8)\n");
    lasa.display(lasa.freeList);

    /*
     * free it all -- notice that a1 is already free
     */
    lasa.lfree(a2);
    lasa.lfree(a3);
    lasa.lfree(a4);
    printf("FREE LIST after all free\n");
    lasa.display(lasa.freeList);

    return 0;
}
#endif // SIMPLETEST2
