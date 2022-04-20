#include "remonteIMG.h"

void encodageBMP(unsigned char* addr, int width, int height) {
    unsigned char *ptr_img = (unsigned char*) addr;
    unsigned char *bmpImg;
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

    fileheader->fType = (0x424d);
    fileheader->fSize = bswap_32(( width * height * 3 ) + sizeOfInfoHeader + sizeOfFileHeader);
    fileheader->fReserved1 = 0x00;
    fileheader->fReserved2 = 0x00;
    fileheader->fOffBits = bswap_32(sizeOfFileHeader + sizeOfInfoHeader); //bytes,  TO DO : convert to hex and little endian

    // Création de l'InfoHeader 

    infoheader->size = bswap_32(0x7c000000);
    infoheader->width = bswap_32((unsigned int) width);
    infoheader->height = bswap_32((unsigned int) height);
    infoheader->planes = bswap_16(0x0100);
    infoheader->bitCount = bswap_16(0x2000); 
    infoheader->compression = 0x00000000;
    infoheader->sizeImage = bswap_32((unsigned int) width*height);
    infoheader->xPelsPerMeter = 0;
    infoheader->yPelsPerMeter = 0;
    infoheader->clrUsed = bswap_32(0x01000000);
    infoheader->clrImportant = 0x00000000;

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
        n += 5;
    }
    fclose(imageFile);
}
