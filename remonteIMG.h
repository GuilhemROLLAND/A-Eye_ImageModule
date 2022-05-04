#include "preprocess.h"

#ifndef _REMONTEIMG_H
#define _REMONTEIMG_H

    /**
     * @brief Create a bmp file corresponding to the data stocked att addr
     * 
     * @param addr starting of the img data
     * @param size of img (HEIGHT*WIDTH*3)
     */
    void encodageBMP(unsigned char* addr, int size);

#endif