#include "Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library font_lib;

void font_init(int _numFonts, ...)
{
    va_list args;
    va_start(args, _numFonts);
    for (int i = 0; i < _numFonts; i++)
    {
        printf("Font %d: %s\n",i, va_arg(args, char*));
    }
    va_end(args);
    FT_Error err = FT_Init_FreeType(&font_lib);
    if (err)
    {
        printf("Error while initializing freetype: %d\n", err);
        return;
    }
    printf("Freetype initialized!\n");
}