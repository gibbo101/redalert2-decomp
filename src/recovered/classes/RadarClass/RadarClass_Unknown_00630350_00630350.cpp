// void RadarClass::Unknown_00630350() (0x00630350)
// The multiplayer player list in the radar area (Draw_It, mode 2): the frame,
// the "Name:" and "Kills:" headings in grey, a rule, then one line per
// multiplayer house with its name (cut to 18 characters) and the sum of its
// unit and building kills.
#include "shared/radar.hpp"
#include "shared/house_screen.hpp"
#include "shared/house_type.hpp"
#include "shared/text_print.hpp"
#include "shared/palette.hpp"
#include "shared/convert.hpp"
#include "shared/color_scheme.hpp"
// @ref ??_C@_04HPIL@Grey?$AA@=007d83b8
// @ref ??_C@_0BA@HLEP@TXT_KILLS_COLON?$AA@=007ee1d8
// @ref ??_C@_0BB@PACI@D?3?2Ra2?2Radar?4CPP?$AA@=007ee1f8
// @ref ??_C@_0P@FFAO@TXT_NAME_COLON?$AA@=007ee1e8
// @ref ??_C@_15DEDE@?$AA?$CF?$AAs?$AA?$AA@=007d9c94
// @ref ??_C@_17IPOH@?$AA?$CF?$AA2?$AAd?$AA?$AA@=007ee1bc
// @ref ??_C@_1BC@LNGA@?$AA_?$AA_?$AA_?$AA_?$AA_?$AA_?$AA_?$AA_?$AA?$AA@=007ee1c4
// @ref ?unknown_shape_ab64a0@@3PAXA=00ab64a0
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8

ColorScheme *__fastcall unknown_color_scheme_663d30(char const *name, int kind);

void RadarClass::Unknown_00630350()
{
    if (unknown_flag_8373c1) {
        CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, (ShapeFileStruct const *)unknown_shape_ab64a0, 32,
                      Point2D(unknown_11e0, unknown_11e8), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0,
                      Point2D(0, 0));
        int y = unknown_11f0 + 2;
        Fancy_Text_Printf(StringTable::Load_String("TXT_NAME_COLON", 0, "D:\\Ra2\\Radar.CPP", 1217), unknown_surface_839948,
                          &unknown_surface_839948->Get_Rect(), &Point2D(unknown_11ec, y), unknown_color_scheme_663d30("Grey", 1), 0, 0x19);
        Fancy_Text_Printf(StringTable::Load_String("TXT_KILLS_COLON", 0, "D:\\Ra2\\Radar.CPP", 1219), unknown_surface_839948,
                          &unknown_surface_839948->Get_Rect(), &Point2D(unknown_11ec + unknown_11f4 - 2, y),
                          unknown_color_scheme_663d30("Grey", 1), 0, 0x219);
        y += 7;
        unknown_surface_839948->Draw_Line(Point2D(unknown_11ec, y), Point2D(unknown_11ec + unknown_11f4 - 1, y),
                                          unknown_drawer_8323cc->Convert(14));
        y += 4;
        for (int index = 0; index < Houses.Count(); index++) {
            HouseClass *house = Houses[index];
            if (house != 0 && house->Type->Multiplay) {
                ColorScheme *scheme;
                unsigned flags;
                int color = house->ColorSchemeIndex;
                if (house->unknown_13d) {
                    scheme = unknown_color_scheme_663d30("Grey", 1);
                    flags = 0x19;
                } else {
                    scheme = ColorSchemes[color];
                    flags = 0x4019;
                }
                wchar_t text[40];
                text[0] = 0;
                swprintf(text, L"%s", house->UIName);
                if (wcslen(text) == 0) {
                    wcscpy(text, L"________");
                }
                if (wcslen(text) > 18) {
                    text[18] = '.';
                    text[19] = 0;
                }
                Fancy_Text_Printf(text, unknown_surface_839948, &unknown_surface_839948->Get_Rect(), &Point2D(unknown_11ec, y),
                                  scheme, 0, flags);
                int kills = 0;
                for (int other = 0; other < 20; other++) {
                    kills += house->unknown_5310[other] + house->unknown_5364[other];
                }
                swprintf(text, L"%2d", kills);
                Fancy_Text_Printf(text, unknown_surface_839948, &unknown_surface_839948->Get_Rect(),
                                  &Point2D(unknown_11ec + unknown_11f4 - 2, y), scheme, 0, flags | 0x200);
                y += 9;
            }
        }
    }
}
