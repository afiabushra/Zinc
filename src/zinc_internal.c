#include "zinc_internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <math.h>


ZincImage ZincLoadImage(const char *imagePath, ZincImageType imageType) 
{
  ZincImage image = {
    .imageType = imageType
  };

  image.data = stbi_load(imagePath, &image.width, &image.height, &image.colorChannels, 0);   

  if (!image.data) 
  {
    printf("\nZINC_ERROR: Cannot load file. \nMaybe due to corrupted file or invalid path. \n");
    exit(-1);
  }

  return image;
}

void ZincGray(ZincImage *image)
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      *(result.data + 0 + p) = (*(image->data + 0 + p) + *(image->data + 1 + p) + *(image->data + 2 + p)) / 3;
      *(result.data + 1 + p) = (*(image->data + 0 + p) + *(image->data + 1 + p) + *(image->data + 2 + p)) / 3;
      *(result.data + 2 + p) = (*(image->data + 0 + p) + *(image->data + 1 + p) + *(image->data + 2 + p)) / 3;
  
      if (image->colorChannels == 4)
        *(result.data + 3 + p) = *(image->data + 3 + p); 

      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincInvert(ZincImage *image)
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      *(result.data + 0 + p) = 255 - *(image->data + 0 + p);
      *(result.data + 1 + p) = 255 - *(image->data + 1 + p);
      *(result.data + 2 + p) = 255 - *(image->data + 2 + p);

      if (image->colorChannels == 4)
        *(result.data + 3 + p) = *(image->data + 3 + p); 
      
      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincTint(ZincImage *image, uint8_t r, uint8_t g, uint8_t b) 
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      if ((uint16_t) (*(image->data + 0 + p) + ZincPercentageTo8Bit(r)) >= 255)
        *(result.data + 0 + p) = 255; 
      else
        *(result.data + 0 + p) = *(image->data + 0 + p) + ZincPercentageTo8Bit(r);

      if ((uint16_t) (*(image->data + 1 + p) + ZincPercentageTo8Bit(g)) >= 255)
        *(result.data + 1 + p) = 255;
      else
        *(result.data + 1 + p) = *(image->data + 1 + p) + ZincPercentageTo8Bit(g);

      if ((uint16_t) (*(image->data + 2 + p) + ZincPercentageTo8Bit(b)) >= 255)
        *(result.data + 2 + p) = 255; 
      else
        *(result.data + 2 + p) = *(image->data + 2 + p) + ZincPercentageTo8Bit(b);
      

      if (image->colorChannels == 4)
        *(result.data + 3 + p) = *(image->data + 3 + p); 
      
      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincGaussianBlur(ZincImage *image, uint8_t intensity)
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;
  int sum = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {

      // for (int kernelY = -ZINC_KERNEL_SIZE / 2; kernelY <= ZINC_KERNEL_SIZE / 2; kernelY++)
      // {
      //   for (int kernelX = -ZINC_KERNEL_SIZE / 2; kernelX <= ZINC_KERNEL_SIZE / 2; kernelX++)
      //   {
      //     if (p / 3 - ZINC_KERNEL_SIZE / 2) 
      //   }
      // }
      
      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincBrightness(ZincImage *image, uint8_t intensity) 
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;
  uint8_t intensity8bit = ZincPercentageTo8Bit(intensity);

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      if ((uint16_t) (*(image->data + 0 + p) + intensity8bit) >= 255)
        *(result.data + 0 + p) = 255; 
      else
        *(result.data + 0 + p) = *(image->data + 0 + p) + intensity8bit;

      if ((uint16_t) (*(image->data + 1 + p) + intensity8bit) >= 255)
        *(result.data + 1 + p) = 255;
      else
        *(result.data + 1 + p) = *(image->data + 1 + p) + intensity8bit;

      if ((uint16_t) (*(image->data + 2 + p) + intensity8bit) >= 255)
        *(result.data + 2 + p) = 255; 
      else
        *(result.data + 2 + p) = *(image->data + 2 + p) + intensity8bit;

      if (image->colorChannels == 4)
        *(result.data + 3 + p) = *(image->data + 3 + p); 
      
      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincCropWOCTR(ZincImage *image, ZincArr2 CroppingTopLeft, ZincArr2 CroppingBottomRight, uint8_t bgColor)
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      if (x >= CroppingTopLeft.x && x <= CroppingBottomRight.x && y >= CroppingTopLeft.y && y <= CroppingBottomRight.y)
      {
        *(result.data + 0 + p) = *(image->data + 0 + p);
        *(result.data + 1 + p) = *(image->data + 1 + p);
        *(result.data + 2 + p) = *(image->data + 2 + p);

        if (image->colorChannels == 4)
          *(result.data + 3 + p) = *(image->data + 3 + p); 
      }
      else
      {
        *(result.data + 0 + p) = bgColor;
        *(result.data + 1 + p) = bgColor;
        *(result.data + 2 + p) = bgColor;
      }

      p += image->colorChannels;
    }
  }

  image->data = result.data;
}


void ZincCropCTR(ZincImage *image, ZincArr2 CroppingTopLeft, ZincArr2 CroppingBottomRight)
{
  ZincImage result;

  result.data = (uint8_t *)malloc
  (
    (CroppingBottomRight.x - CroppingTopLeft.x) *
    (CroppingBottomRight.y - CroppingTopLeft.y) *
    image->colorChannels
  );

  int p = 0;
  int rp = 0;

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      if (x >= CroppingTopLeft.x && x <= CroppingBottomRight.x - 1 && y >= CroppingTopLeft.y && y <= CroppingBottomRight.y - 1)
      {
        *(result.data + 0 + rp) = *(image->data + 0 + p);
        *(result.data + 1 + rp) = *(image->data + 1 + p);
        *(result.data + 2 + rp) = *(image->data + 2 + p);

        if (image->colorChannels == 4)
          *(result.data + 3 + rp) = *(image->data + 3 + p);

        rp += image->colorChannels;
      }

      p += image->colorChannels;
    }
  }

  image->width = CroppingBottomRight.x - CroppingTopLeft.x;
  image->height = CroppingBottomRight.y - CroppingTopLeft.y; 
  image->data = result.data;
}

void ZincDithering(ZincImage *image, uint8_t colorLimit)
{
  ZincImage result;
  result.data = (uint8_t *)malloc(image->width * image->height * image->colorChannels);

  int p = 0;

  uint8_t r[256];
  uint8_t g[256];
  uint8_t b[256];

  uint8_t colorSum = 0;

  for (int i = 0; i <= colorLimit; i++)
  {
    r[i] = (uint16_t)floor(255.0f / colorLimit) * i;
    g[i] = (uint16_t)floor(255.0f / colorLimit) * i;
    b[i] = (uint16_t)floor(255.0f / colorLimit) * i;

    printf("%hhu \n", r[i]);
  }

  for (int y = 0; y < image->height; y++)
  {
    for (int x = 0; x < image->width; x++)
    {
      for (int i = 0; i < colorLimit; i++)
      {
        if (*(image->data + 0 + p) <= r[i])
          *(result.data + 0 + p) = r[i];
        if (*(image->data + 1 + p) <= g[i])
          *(result.data + 1 + p) = g[i];
        if (*(image->data + 2 + p) <= b[i])
          *(result.data + 2 + p) = b[i];
      }

      if (image->colorChannels == 4)
        *(result.data + 3 + p) = *(image->data + 3 + p); 
      
      p += image->colorChannels;
    }
  }

  image->data = result.data;
}

void ZincWriteImage(const char *imagePath, ZincImage *image, uint8_t jpgImageQuality)
{
  if (image->imageType == ZINC_JPG)
    stbi_write_jpg(imagePath, image->width, image->height, image->colorChannels, image->data, jpgImageQuality);
  if (image->imageType == ZINC_PNG)
    stbi_write_png(imagePath, image->width, image->height, image->colorChannels, image->data, image->width * image->colorChannels);
  if (image->imageType == ZINC_BMP)
    stbi_write_bmp(imagePath, image->width, image->height, image->colorChannels, image->data);
  if (image->imageType == ZINC_TGA)
    stbi_write_tga(imagePath, image->width, image->height, image->colorChannels, image->data);
}
