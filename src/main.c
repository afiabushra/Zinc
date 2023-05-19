#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "zinc_internal.h"
#include "zinc_interface.h"

ZincImage image;



int main()
{
  ZincClearScreen();
  
  printf("%s", ZincGreetingText);
  char imagePath[256];

  printf(
    "\nGive the path to the image you want to process."
    "\nThis program only support files that ends with .jpg, .png, .bmp, .tga."
    "\nLastly, path cannot have spaces!"
    "\n\n-> "
  );

  scanf("%s", imagePath);

  char imageType[3] = {
    imagePath[strlen(imagePath) - 3],
    imagePath[strlen(imagePath) - 2],
    imagePath[strlen(imagePath) - 1]
  };


  if (imageType[0] == 'j' && imageType[1] == 'p' && imageType[2] == 'g')
    image = ZincLoadImage(imagePath, ZINC_JPG);
  else if (imageType[0] == 'p' && imageType[1] == 'n' && imageType[2] == 'g')
    image = ZincLoadImage(imagePath, ZINC_PNG);
  else if (imageType[0] == 'b' && imageType[1] == 'm' && imageType[2] == 'p')
    image = ZincLoadImage(imagePath, ZINC_BMP);
  else if (imageType[0] == 't' && imageType[1] == 'g' && imageType[2] == 'a')
    image = ZincLoadImage(imagePath, ZINC_TGA);
  else 
  {
    printf(
      "\nZINC_ERROR: Cannot load file." 
      "\nMaybe due to corrupted file or invalid path." 
      "\nMake sure the file ends with the types that are mentioned!\n"
    );
  
    exit(-1);
  }


  repeatTrue:;
    

  ZincClearScreen();
  printf("%s", ZincMenu);
  

  uint16_t  targetMenuOption;
  uint8_t   effectIntensity = 0;

  uint16_t  tintingRValue;
  uint16_t  tintingGValue;
  uint16_t  tintingBValue;

  ZincArr2  CroppingTopLeft;
  ZincArr2  CroppingBottomRight;

  uint8_t   UnCroppedBgColor;
  
  printf("Type: Integer | Range: (1 - %d) \n-> ", MAX_MENU_OPTIONS);
  scanf("%hu", &targetMenuOption);


  switch (targetMenuOption)
  {
    case 1:
      ZincClearScreen();
      ZincGray(&image);
      break;

    case 2:
      ZincClearScreen();
      ZincInvert(&image);
      break;

    case 3:
      ZincClearScreen();
      printf("Give the RGB value for tinting. \nType: Integer | Range: (0 - 100)%% \n\n");

      printf("R value -> ");
      scanf("%hu", &tintingRValue);
      printf("G value -> ");
      scanf("%hu", &tintingGValue);
      printf("B value -> ");
      scanf("%hu", &tintingBValue);

      ZincTint(&image, tintingRValue, tintingGValue, tintingBValue);
      break;

    case 4:
      ZincClearScreen();
      printf("Give the level of brightness your want. \nType: Integer | Range: (0 - 100)%% \n\n");

      printf("-> ");
      scanf("%hhu", &effectIntensity);

      ZincBrightness(&image, effectIntensity);
      break;

    case 5:
      ZincClearScreen();
      printf(
        "Give the positions of the section you want to crop. \n"
        "Type: Integer | Range X: (0 - %d), Range Y: (0 - %d). \n"
        "Give the coords between commas and spaces. eg. x, y \n\n", image.width, image.height
      );

      printf("Top Left -> ");
      scanf("%d, %d", &CroppingTopLeft.x, &CroppingTopLeft.y);
      printf("Bottom Right -> ");
      scanf("%d, %d", &CroppingBottomRight.x, &CroppingBottomRight.y);
      
      printf("Give the color for the uncropped places. \n-> ");
      scanf("%hhu", &UnCroppedBgColor);

      ZincCropWOCTR(&image, CroppingTopLeft, CroppingBottomRight, UnCroppedBgColor);
      break;

    case 6:
      ZincClearScreen();
      printf(
        "Give the positions of the section you want to crop. \n"
        "Type: Integer | Range X: (0 - %d), Range Y: (0 - %d). \n"
        "Give the coords between commas and spaces. eg. x, y \n\n", image.width, image.height
      );

      printf("Top Left -> ");
      scanf("%d, %d", &CroppingTopLeft.x, &CroppingTopLeft.y);
      printf("Bottom Right -> ");
      scanf("%d, %d", &CroppingBottomRight.x, &CroppingBottomRight.y);

      ZincCropCTR(&image, CroppingTopLeft, CroppingBottomRight);
      break;

    default:
      printf("ZINC_ERROR: Invalid input! \n \n");
      break;
  }

  #ifndef ZINC_DO_NOT_REPEAT_EFFECTS
    getchar();
    char willRepeat;
  
    ZincClearScreen();
    printf("Do you want to add more effects to your image? \n");
    printf("[Y/n] -> ");
    scanf("%c", &willRepeat);
  
    if (willRepeat == 'y' || willRepeat == 'Y')
      goto repeatTrue;
  #endif

  ZincWriteImage("ZincImage.jpg", &image, 200);
  ZincFreeImage(image.data);
  
  return 0;
}

