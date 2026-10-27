// void Draw_Box(Rect const &rect, int style, bool fill) (0x004973D0)
// Draws a GUI box in the current box colour scheme on the GUI surface:
// optionally filled, then by style a sunken or raised bevel (styles 0-3:
// shadow lines right and bottom, highlight lines top and left, corner
// pixels), an outline (4) or an outline inset by one pixel (5). Styles
// follow Westwood's BOXSTYLE_DOWN, RAISED, DIS_DOWN, DIS_RAISED, BOX,
// BORDER (hypothesis); 2 and 3 use fixed palette indices.
#include "shared/text_print.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0

struct BoxStyleType {
    int Filler;
    int Shadow;
    int Highlight;
    int Corner;
};

void __fastcall Draw_Box(Rect const &rect, int style, bool fill)
{
    ColorScheme *scheme = ColorSchemes[unknown_scheme_index_4cefc0()];
    BoxStyleType const styles[6] = {
        {scheme->unknown_color_0x320, scheme->unknown_color_0x328, scheme->unknown_color_0x31c, scheme->unknown_color_0x324},
        {scheme->unknown_color_0x320, scheme->unknown_color_0x31c, scheme->unknown_color_0x328, scheme->unknown_color_0x324},
        {13, 15, 12, 13},
        {13, 12, 14, 13},
        {scheme->unknown_color_0x320, scheme->unknown_color_0x32c, scheme->unknown_color_0x32c, scheme->unknown_color_0x320},
        {scheme->unknown_color_0x320, scheme->unknown_color_0x32c, scheme->unknown_color_0x32c, scheme->unknown_color_0x320},
    };
    BoxStyleType const &colors = styles[style];

    if (fill) {
        unknown_surface_83995c->Fill_Rect(rect, scheme->Converter->Convert(colors.Filler));
    }

    switch (style) {
    case 4:
        unknown_surface_83995c->Draw_Rect(rect, scheme->Converter->Convert(colors.Highlight));
        break;

    case 5:
        unknown_surface_83995c->Draw_Rect(Rect(rect.X + 1, rect.Y + 1, rect.Width - 1, rect.Height - 1),
                                          scheme->Converter->Convert(colors.Highlight));
        break;

    default:
        unknown_surface_83995c->Draw_Line(Point2D(rect.X, rect.Y + rect.Height),
                                          Point2D(rect.X + rect.Width, rect.Y + rect.Height),
                                          scheme->Converter->Convert(colors.Shadow));
        unknown_surface_83995c->Draw_Line(Point2D(rect.X + rect.Width, rect.Y),
                                          Point2D(rect.X + rect.Width, rect.Y + rect.Height),
                                          scheme->Converter->Convert(colors.Shadow));
        unknown_surface_83995c->Draw_Line(Point2D(rect.X, rect.Y),
                                          Point2D(rect.X + rect.Width, rect.Y),
                                          scheme->Converter->Convert(colors.Highlight));
        unknown_surface_83995c->Draw_Line(Point2D(rect.X, rect.Y),
                                          Point2D(rect.X, rect.Y + rect.Height),
                                          scheme->Converter->Convert(colors.Highlight));
        unknown_surface_83995c->Put_Pixel(Point2D(rect.X, rect.Y + rect.Height),
                                          scheme->Converter->Convert(colors.Corner));
        unknown_surface_83995c->Put_Pixel(Point2D(rect.X + rect.Width, rect.Y),
                                          scheme->Converter->Convert(colors.Corner));
        break;
    }
}
