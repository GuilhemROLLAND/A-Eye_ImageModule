#include "preprocess.h"
#include <byteswap.h>

#ifndef _REMONTEIMG_H
#define _REMONTEIMG_H

    /**
     * @brief Create a bmp file corresponding to the data stocked att addr
     * 
     * @param addr starting of the img data
     * @param width of img 
     * @param height of img
     */
    void encodageBMP(unsigned char* addr, int width, int height);

#endif