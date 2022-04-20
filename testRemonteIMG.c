#include "remonteIMG.h"

void testRemonteIMG(void) 
{
    char* imgData;
    int length;
    if((imgData = malloc(length*sizeof(char))) == NULL)
        printf("Erreur allocation memoire \n");
    for (int i = 0; i < length; i++)
    {
        imgData[i] = 255;
    }
    encodageBMP(&imgData[0], 640, 480);
}

int main() 
{
    testRemonteIMG();
    return 1;
}