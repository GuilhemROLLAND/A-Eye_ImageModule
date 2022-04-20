#include "remonteIMG.h"

void encodageBMP(unsigned char* addr, int width, int height) {
    unsigned char *ptr_img = (unsigned char*) addr;
    BITMAPFILEHEADER* fileheader;
    if ((fileheader = malloc(sizeof(BITMAPFILEHEADER))) == NULL)
        printf("erreur allocation mémoire \n");

    BITMAPINFOHEADER* infoheader;
    if ((infoheader = malloc(sizeof(BITMAPINFOHEADER))) == NULL)
        printf("erreur allocation mémoire \n");

    
    // Création du FileHeader 
    int sizeOfFileHeader = 14;
    int sizeOfInfoHeader = 40;

    fileheader->fType = (0x4d42);
    fileheader->fSize = (( width * height * 3 ) + sizeOfInfoHeader + sizeOfFileHeader)-1;
    fileheader->fReserved1 = 0;
    fileheader->fReserved2 = 0;
    fileheader->fOffBits = (unsigned int) sizeOfFileHeader + sizeOfInfoHeader; 

    // Création de l'InfoHeader 

    infoheader->size = 0x0000028;
    infoheader->width = (unsigned int) width;
    infoheader->height = (unsigned int) height;
    infoheader->planes = 0x0001;
    infoheader->bitCount = 0x0018; 
    infoheader->compression = 0;
    infoheader->sizeImage = 0;//(unsigned int) width*height*3
    infoheader->xPelsPerMeter = 0x00000EC3;
    infoheader->yPelsPerMeter = 0x00000EC3;
    infoheader->clrUsed = 0;
    infoheader->clrImportant = 0;

    //Ecriture des données header dans un fichier

    FILE* imageFile = fopen("ImageBMP.bmp", "wb");
    fwrite(fileheader, sizeof(BITMAPFILEHEADER), 1, imageFile);
    fwrite(infoheader, sizeof(BITMAPINFOHEADER), 1, imageFile);

    //Ecriture des données de l'image dans le fichier avec inversion des couleurs
    int n = 2;
    for (int i = 0; i < width*height; i++)
    {   
        for (n; n >= ((i+1)*3)-2; n--)
        {
            fwrite((ptr_img+n), sizeof(unsigned char), 1, imageFile);
        }
        n += 6;
    }
    char *completion;
    char a = 0;
    completion = &a;
    fwrite(completion, sizeof(char), 1, imageFile);
    fwrite(completion, sizeof(char), 1, imageFile);
    fwrite(completion, sizeof(char), 1, imageFile);

    fclose(imageFile);
}
