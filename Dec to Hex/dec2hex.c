#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decimal;
int bits = 32;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Input number to convert to hex: ");
        scanf("%d", &decimal);
    }
    else if (argc == 2)
    {
        decimal = atoi(argv[1]);
    }
    else if (argc == 3)
    {
        decimal = atoi(argv[1]);
        bits = atoi(argv[2]);
    }
    else if (argc > 3)
    {
        printf("Too many arguments provided! \n");
        return 0;
    }

    printf("\nConverting %d to %d-bit hex...", decimal, bits);

    if (bits == 32)
    {
        printf("\n0x%08X\n", decimal);
    }
    else
    {
        printf("\n0x%016X\n", decimal);
    }

    return 0;
}