#include "sobelFilter.h"
#include "../errors.h"
#include "../tools.h"

ImgLibErrorInfo imgSobelFilter(Img* img, float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    unsigned char* edgeData = imgDataAlloc(img);
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(edgeData)).code != IMG_LIB_SUCCESS)
    {
        free(edgeData);
        return err;
    }

    const int sobelX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int sobelY[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    int pIndex = 0;
    int gx = 0, gy = 0;
    int xOffset, yOffset;
    int newValue = 0;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;

            for (int c = 0; c < img->channels; c++)
            {
                gx = 0;
                gy = 0;

                for (int ky = -1; ky <= 1; ky++)
                {
                    yOffset = y + ky;
                    if (yOffset < 0 || yOffset >= img->height)
                        continue;

                    for (int kx = -1; kx <= 1; kx++)
                    {
                        xOffset = x + kx;
                        if (xOffset < 0 || xOffset >= img->width)
                            continue;

                        int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                        gx += img->data[neighborIndex + c] * sobelX[ky + 1][kx + 1];
                        gy += img->data[neighborIndex + c] * sobelY[ky + 1][kx + 1];
                    }
                }

                newValue = (int)((float)(sqrt(gx * gx + gy * gy)) * factor);
                clampColorValue(&newValue);
                edgeData[pIndex + c] = (unsigned char)newValue;
            }
        }
    }

    memcpy(img->data, edgeData, img->width * img->height * img->channels * sizeof(unsigned char));
    free(edgeData);

    return err;
}