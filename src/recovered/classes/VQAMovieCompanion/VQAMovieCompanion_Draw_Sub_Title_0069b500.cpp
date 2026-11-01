// void VQAMovieCompanion::Draw_Sub_Title(SubTitle const *subtitle) (0x0069B500): clears the last caption
// and prints this one on its line of the surface.
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?BitText@@3PAVBitTextClass@@A=0084e9d0
// @ref ?Get_Text_Area@BitFontClass@@QAE_NPBGPAH1H@Z=004314b0
// @ref ?Print_Box@BitTextClass@@QAE_NPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?Set_Clip_Box@BitFontClass@@QAEXPBUtagRECT@@@Z=00431460
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
void VQAMovieCompanion::Draw_Sub_Title(SubTitle const *subtitle)
{
    if (unknown_10 != 0) {
        unknown_10->Fill_Rect(unknown_14, 0);
        BitFontClass *font = BitFont;
        unsigned long rgb = subtitle->Get_RGB_Color();
        font->Set_Color(Build_Hicolor_Pixel((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF));
        int width = unknown_10->Get_Width();
        int height = unknown_10->Get_Height();
        tagRECT clip = {0, 0, width, height};
        font->Set_Clip_Box(&clip);
        unsigned short *text = subtitle->Get_Text();
        int textwidth;
        int textheight;
        font->Get_Text_Area(text, &textwidth, &textheight, width);
        int x = 0;
        int y = (subtitle->Get_Line_Position() - 1) * font->Height;
        int alignment = subtitle->Get_Alignment();
        if (alignment == 2) {
            x = (width - textwidth) / 2;
        } else if (alignment == 1) {
            x = width - textwidth;
        }
        BitText->Print_Box(font, unknown_10, text, x, y, width, height, 0, 0, 0);
        unknown_24 = unknown_14;
        unknown_14.Set(x, y, textwidth, textheight);
    }
}
