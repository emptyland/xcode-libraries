#include <string>
#include <stdio.h>
#include <wchar.h>

#include "freetype/ft2build.h"
#include FT_FREETYPE_H

static void render(FT_Face face) {
    for (size_t row = 0; row < face->glyph->bitmap.rows; ++row) {
        for (size_t pixel = 0; pixel < face->glyph->bitmap_left; ++pixel)
            printf("_");
        for (size_t pixel = 0; pixel < face->glyph->bitmap.width; ++pixel){
            if (face->glyph->bitmap.buffer
                [row * face->glyph->bitmap.pitch +
                 pixel / 8] & (0xC0 >> (pixel % 8)))
                //printf("\033[44;37m" " " "\033[m");
                printf("X");
            else
                printf("_");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    FT_Library  library;

    FT_Error err = FT_Init_FreeType(&library);
    if (err) {
        printf("init error %d\n", err);
        return 1;
    }


    FT_Face face;
    err = FT_New_Face(library, "fonts/SourceHanSansSC-Regular.otf", 0, &face);
    if (err == FT_Err_Unknown_File_Format) {
        printf("err: font file not support.\n");
        return 1;
    } else if (err) {
        printf("FT_New_Face error %d\n", err);
        return 1;
    }

    err = FT_Set_Char_Size(face, 0, 16 * 64, 800, 600);
    if (err) {
        printf("FT_Set_Char_Size error %d\n", err);
        return 1;
    }

    err = FT_Set_Pixel_Sizes(face, 64, 0);
    if (err) {
        printf("FT_Set_Pixel_Sizes error %d\n", err);
        return 1;
    }

    std::u16string s = u"汉字-zh";
    for (size_t i = 0; i < s.length(); i++) {
        FT_UInt index = FT_Get_Char_Index(face, s[i]);
        err = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);
        err = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
        render(face);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
}