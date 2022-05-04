#include "preprocess.h"

void encodageBMP(unsigned char* addr, int width, int length) {
    unsigned char *ptr_img = (unsigned char*) addr;
    if ((bmpImg = malloc(sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER) + size * sizeof(unsigned char))) == NULL)
        printf("erreur allocation mémoire");
    // initialisation du pointeur mémoire a l'adresse de démarrage
    BITMAPFILEHEADER* fileheader;
    if ((fileheader = malloc(sizeof(BITMAPFILEHEADER))) == NULL)
        printf("erreur allocation mémoire \n");
    BITMAPINFOHEADER* infoheader;
    if ((infoheader = malloc(sizeof(BITMAPINFOHEADER))) == NULL)
        printf("erreur allocation mémoire \n");
    
    // Création du FileHeader 

    fileheader->fType = 0x424d;
    fileheader->fSize = NULL; // TO DO : calculer la taille d'une image standard 640*480
    fileheader->fReserved1 = 0x00;
    fileheader->fReserved2 = 0x00;
    fileheader->fOffBits = NULL; // TO DO : specifier offset pour image standard

    // Création de l'InfoHeader 

    infoheader->size = 0x7c000000;
    infoheader->width = 0x80020000;
    infoheader->height = 0xe0010000;
    infoheader->planes = 0x0100;
    infoheader->bitCount = 0x2000; 
    infoheader->compression = 0x00000000;
    infoheader->sizeImage = 0x000E1000;
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
    for (int i = 0; i < 640*480; i++)
    { 
        for (n; n > ((i+1)*3)-2; n--)
        {
            fwrite(*(ptr_img+n), sizeof(unsigned char), 1, imageFile);
            n += 3;
        }
    }

    fclose(imageFile);
}