#include "zinc_interface.h"

const char *ZincGreetingText = 
"\t  -----------------------------------------------  \n" 
"\t |    |----|     |-----|     |   |     |----|    | \n"
"\t |        |         |        ||  |    |          | \n"
"\t |       |          |        | | |    |          | \n"
"\t |      |           |        |  ||    |          | \n"
"\t |     |----|    |-----|     |   |     |----|    | \n"
"\t  -----------------------------------------------  \n"
"\t      An Image Processing Program Written In C     \n";

const char *ZincMenu = 
"\n\n"
"Effects: \n"
"\t 1. Gray Scale    \n"
"\t 2. Invert Color  \n"
"\t 3. Tint Color    \n"
"\t 4. Brightness    \n"
"\t 5. Cropping - Not Changing Resolution \n"
"\t 6. Cropping - Changing Resolution \n\n";

void ZincClearScreen()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}
