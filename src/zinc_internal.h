#ifndef ZINC_INTERNAL_H
#define ZINC_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "zinc_types.h"

#define ZINC_MAX_ERRORS              32
#define ZINC_KERNEL_SIZE             7

#define ZincFreeImage(data)          free(data)
#define ZincPercentageTo8Bit(x)      (int)round(255 * ((float)x / 100))

ZincImage ZincLoadImage(const char *imagePath, ZincImageType imageType);

void ZincGray(ZincImage *image);
void ZincInvert(ZincImage *image);
void ZincTint(ZincImage *image, uint8_t r, uint8_t g, uint8_t b);
void ZincGaussianBlur(ZincImage *image, uint8_t intensity);
void ZincBrightness(ZincImage *image, uint8_t intensity);
void ZincCropWOCTR(ZincImage *image, ZincArr2 CroppingTopLeft, ZincArr2 CroppingBottomRight, uint8_t bgColor);
void ZincCropCTR(ZincImage *image, ZincArr2 CroppingTopLeft, ZincArr2 CroppingBottomRight);
void ZincDithering(ZincImage *image, uint8_t colorLimit);

void ZincWriteImage(const char *imagePath, ZincImage *image, uint8_t jpgImageQuality);

#endif
