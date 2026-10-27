// void HouseClass::Read_INI(CCINIClass &ini) (0x004EBBB0)
// Reads the house's own section (named by its IniName): tech level, credits
// (the campaign money delta for a player-controlled house outside
// multiplayer), UIName (a string-table label, else the type's name), the
// team ratios, IQ, edge, colour (and the laser colour derived from it),
// allies, the first team delay and the base plan.
// @ref ??_C@_02KPHM@IQ?$AA@=007da854
// @ref ??_C@_04ICPD@Edge?$AA@=007da84c
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_06BMKI@UIName?$AA@=007ce29c
// @ref ??_C@_06KHDF@Allies?$AA@=007da844
// @ref ??_C@_07NGJJ@Credits?$AA@=007da8b4
// @ref ??_C@_09FKED@TechLevel?$AA@=007da8bc
// @ref ??_C@_0BB@GHMK@D?3?2Ra2?2House?4CPP?$AA@=007da270
// @ref ??_C@_0BC@BDMM@RatioTeamInfantry?$AA@=007da868
// @ref ??_C@_0BC@GCDH@RatioTeamAircraft?$AA@=007da87c
// @ref ??_C@_0BD@FMDC@RatioAITriggerTeam?$AA@=007da890
// @ref ??_C@_0O@BOLA@PlayerControl?$AA@=007da8a4
// @ref ??_C@_0P@LECO@RatioTeamUnits?$AA@=007da858
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Normalize_Color@@YIXAAN00@Z=004f5490
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Read_INI@BaseClass@@QAEXAAVCCINIClass@@PBD@Z=0042c460
// @ref ?Set@RGBClass@@QAEXEEE@Z=004f6bc0
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@4005c000000000000000=007a2f48
// @ref __real@8@4006f000000000000000=007a2f58
// @ref __real@8@4006ff00000000000000=007a2f50
// @ref _strncpy=007823d0
// @ref _wcscpy=00783689
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/rules.hpp"
#include "shared/string_table.hpp"
#include "shared/color_scheme.hpp"
#include "shared/convert.hpp"
#include "shared/hicolor.hpp"
#include "shared/options.hpp"

void HouseClass::Read_INI(CCINIClass &ini)
{
    char section[20];
    strcpy(section, IniName);

    unknown_11c = ini.Get_Int(section, "TechLevel", unknown_id_source_a3d290->TechLevel);
    unknown_124 = ini.Get_Int(section, "Credits", 0) * 100;
    unknown_135 = ini.Get_Bool(section, "PlayerControl", false);
    if (unknown_135 && !unknown_game_mode_a3d298) {
        if (Options.Difficulty == 0) {
            Balance = Rules->CampaignMoneyDeltaEasy + unknown_124;
        } else if (Options.Difficulty == 2) {
            Balance = Rules->CampaignMoneyDeltaHard + unknown_124;
        } else {
            Balance = unknown_124;
        }
        Balance = Balance > 0 ? Balance : 0;
    } else {
        Balance = unknown_124;
    }

    char buffer[100];
    ini.Get_String(section, "UIName", unknown_15ef5, buffer, 32);
    unknown_15ef5 = buffer;
    if (unknown_15ef5[0] != 0) {
        wcsncpy(UIName, StringTable::Load_String(unknown_15ef5, 0, "D:\\Ra2\\House.CPP", 7898), 32);
        UIName[20] = 0;
    } else {
        wcscpy(UIName, Type->UIName);
    }

    unknown_554c = ini.Get_Int(section, "RatioAITriggerTeam", unknown_554c);
    unknown_5550 = ini.Get_Int(section, "RatioTeamAircraft", 75);
    unknown_5554 = ini.Get_Int(section, "RatioTeamInfantry", 75);
    unknown_5558 = ini.Get_Int(section, "RatioTeamUnits", 75);

    unknown_130 = Type->Side;
    if (unknown_130 == -1) {
        unknown_130 = 0;
    }

    int iq = ini.Get_Int(section, "IQ", 0);
    if (iq > Rules->MaxIQ) {
        iq = 1;
    }
    unknown_118 = iq;
    unknown_194 = iq;

    unknown_128 = ini.Get_SourceType(section, "Edge", (SourceType)0);
    ColorSchemeIndex = ini.Get_ColorScheme(section, "Color", ColorSchemeIndex);
    Update_Color();
    Update_Laser_Color();

    unknown_56cc = 0;
    Make_Ally(Houses[ArrayIndex], false);
    int allies = ini.Get_Houses(section, "Allies", 0);
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        if (allies & (1 << house->ArrayIndex)) {
            Make_Ally(house, false);
        }
    }

    unknown_5684 = CDTimerClass<FrameTimerClass>(Rules->TeamDelays[unknown_c8] + ArrayIndex * 175);
    unknown_55f0.Read_INI(ini, section);
    unknown_55f0.House = this;
}
