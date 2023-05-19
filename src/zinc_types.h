#ifndef ZINC_TYPES_H
#define ZINC_TYPES_H

#include <stdint.h>

typedef struct ZincArr2
{
  int x;
  int y;

} ZincArr2;

typedef struct ZincArr3
{
  int x;
  int y;
  int z;

} ZincArr3;

typedef enum ZincImageType 
{
  ZINC_JPG,
  ZINC_PNG,
  ZINC_BMP,
  ZINC_TGA
  
} ZincImageType;

typedef struct ZincImage 
{
  int width;
  int height;
  uint8_t *data;
  
  int colorChannels;
  ZincImageType imageType;
  
} ZincImage;

#endif
