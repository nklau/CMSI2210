#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char binary[32];

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("No argument provided. Please provide a base 10 number to convert. \n");
        return 0;
    }
    else if (argc > 2)
    {
        printf("Too many arguments provided! \n");
        return 0;
    }

    int decimal = atoi(argv[1]);
    int index = 31;

    while (index >= 0)
    {
        binary[index] = (decimal % 2) + '0';
        decimal /= 2;
        index--;
    }

    printf("%s", binary);

    return 0;
}