#include "preprocess.h"

void encodageBMP(unsigned char* addr, int width, int height) {
    unsigned char *ptr_img = (unsigned char*) addr;
    if ((bmpImg = malloc(sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER) + (width*height*3) * sizeof(unsigned char))) == NULL)
        printf("erreur allocation mémoire\n");
    // initialisation du pointeur mémoire a l'adresse de démarrage
    BITMAPFILEHEADER* fileheader;
    if ((fileheader = malloc(sizeof(BITMAPFILEHEADER))) == NULL)
        printf("erreur allocation mémoire \n");
    BITMAPINFOHEADER* infoheader;
    if ((infoheader = malloc(sizeof(BITMAPINFOHEADER))) == NULL)
        printf("erreur allocation mémoire \n");
    
    // Création du FileHeader 
    int sizeOfFileHeader = 14;
    int sizeOfInfoHeader = 40;

    fileheader->fType = 0x424d;
    fileheader->fSize = ( width * height * 3 ) + sizeOfInfoHeader + sizeOfFileHeader; // bytes, to do: convert to hex and little endian
    fileheader->fReserved1 = 0x00;
    fileheader->fReserved2 = 0x00;
    fileheader->fOffBits = sizeOfFileHeader + sizeOfInfoHeader; //bytes,  TO DO : convert to hex and little endian

    // Création de l'InfoHeader 

    infoheader->size = 0x7c000000;
    infoheader->width = (unsigned int) width;
    infoheader->height = (unsigned int) height;
    infoheader->planes = 0x0100;
    infoheader->bitCount = 0x2000; 
    infoheader->compression = 0x00000000;
    infoheader->sizeImage = (unsigned int) width*height;
    infoheader->xPelsPerMeter = NULL;
    infoheader->yPelsPerMeter = NULL;
    infoheader->clrUsed = 0x01000000;
    infoheader->clrImportant = 0x00000000;

    //Ecriture des données header dans un fichier

    FILE* imageFile = fopen('ImageBMP.bmp', "wb");
    fwrite(fileheader, sizeof(BITMAPFILEHEADER), 1, imageFile);
    fwrite(infoheader, sizeof(BITMAPINFOHEADER), 1, imageFile);

    //Ecriture des données de l'image dans le fichier avec inversion des couleurs

    int n = 0;
    for (int i = 0; i < width*height; i++)
    { 
        for (n; n > ((i+1)*3)-2; n--)
        {
            fwrite(*(ptr_img+n), sizeof(unsigned char), 1, imageFile);
            n += 3;
        }
    }
    fclose(imageFile);
}
