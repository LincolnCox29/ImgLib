#include "ImgLib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "errors.h"
#include "operations/grayscale.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

ImgLibErrorInfo writeImg(const char* path, Img img)
{
    const char* ext = strrchr(path, '.');

    if (ext != NULL)
    {
        if (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0)
        {
            stbi_write_png(path, img.width, img.height, img.channels, img.data, img.width * img.channels);
            return (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL };
        }
        else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".JPG") == 0 || strcmp(ext, ".JPEG") == 0)
        {
            stbi_write_jpg(path, img.width, img.height, img.channels, img.data, 100);
            return (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL };
        }
        else if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".BMP") == 0)
        {
            stbi_write_bmp(path, img.width, img.height, img.channels, img.data);
            return (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL };
        }
        else if (strcmp(ext, ".tga") == 0 || strcmp(ext, ".TGA") == 0)
        {
            stbi_write_tga(path, img.width, img.height, img.channels, img.data);
            return (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL };
        }
        else
            return (ImgLibErrorInfo) { IMG_LIB_ERROR_UNSUPPORTED_IMAGE_FORMAT, "Unsupported image format." };
    }
    else
        return (ImgLibErrorInfo) { IMG_LIB_ERROR_FILE_PATH_DOES_NOT_EXIST, "File path does not have an extension!" };
}

Img* loadImg(const char* path)
{
    Img* img = malloc(sizeof(Img));
    img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    return img;
}