#include <stdio.h>

int main()
{
    FILE *file = fopen("a.txt", "w");
    for (int i = 0; i < __INT_MAX__; i++)
    {
        fprintf(file, "Tom le Connard\n");
    }
    fclose(file);
    
    return 0;
}