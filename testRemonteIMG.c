#include "remonteIMG.h"

void testRemonteIMG(void) 
{
    char* imgData;
    int length = 921600;
    if((imgData = malloc(length*sizeof(char))) == NULL)
        printf("Erreur allocation memoire \n");
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        imgData[i] = 159;
        count++;
    }
    encodageBMP(&imgData[0], 640, 480);
    printf("%d\n", count);
}

int main() 
{
    testRemonteIMG();
    return 1;
}