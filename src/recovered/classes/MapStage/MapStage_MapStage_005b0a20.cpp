// MapStage::MapStage(INIClass &ini, Wstring const &section) (0x005B0A20)
// Loads one stage from its MAPSEL.INI section: the scenario, description
// (a string-table label), voice-over, map movie, up to two overlays, the
// click map, the "Text1".."Text7" lines, the "Targets" points and the
// selections keyed "0".."255".
// Assumptions: `unused` is a local the original constructs and destroys but
// never reads; the Description line number 0x1E2 is the original __LINE__.
#include "shared/ms_choice.hpp"
// @ref ??_7?$DynamicVectorClass@UPoint2D@@@@6B@=007a6fa8
// @ref ??_7?$DynamicVectorClass@PAVMSTextEntry@@@@6B@=007a6f88
// @ref ??_7?$DynamicVectorClass@PAVMapSelection@@@@6B@=007a6f68
// @ref ??_C@_08DFKC@Scenario?$AA@=007d145c
// @ref ??_C@_0M@DKEL@Description?$AA@=007d1444
// @ref ??_C@_0BE@FMFF@D?3?2Ra2?2MSChoice?4cpp?$AA@=007e5c50
// @ref ??_C@_09FIPE@VoiceOver?$AA@=007e5c44
// @ref ??_C@_05EJK@MapVQ?$AA@=007e5c3c
// @ref ??_C@_08FIBA@Overlays?$AA@=007e5c30
// @ref ??_C@_08OADD@ClickMap?$AA@=007e5c24
// @ref ??_C@_04BNNJ@Text?$AA@=007e5c1c
// @ref ??_C@_07MHHP@Targets?$AA@=007e5c14
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??4WideString@@QAEAAV0@PBG@Z=0076fb70
// @ref ??H@YI?AVWstring@@PBDABV0@@Z=0076f6b0
// @ref ?Wstring_To_Wide@@YI?AVWideString@@ABVWstring@@@Z=007711c0
// @ref ?Int_To_Wstring@@YI?AVWstring@@H@Z=0076f580
// @ref ?Get_String@INIClass@@QBEHABVWstring@@00AAV2@@Z=0050eb40
// @ref ??0MSTextEntry@@QAE@ABVWideString@@@Z=005b13d0

MapStage::MapStage(INIClass &ini, Wstring const &section)
{
    Wstring value;
    WideString text;
    Wstring unused;

    Name = section;

    Scenario = (char const *)0;
    if (ini.Get_String(section, "Scenario", (char const *)0, value) > 0) {
        Scenario = value;
    }

    Description = (unsigned short const *)0;
    if (ini.Get_String(section, "Description", (char const *)0, value) > 0) {
        Description = StringTable::Load_String(value.Get(), 0, "D:\\Ra2\\MSChoice.cpp", 0x1E2);
    }

    VoiceOver = (char const *)0;
    if (ini.Get_String(section, "VoiceOver", (char const *)0, value) > 0) {
        VoiceOver = value;
    }

    MapVQ = (char const *)0;
    if (ini.Get_String(section, "MapVQ", (char const *)0, value) > 0) {
        MapVQ = value;
    }

    OverlayCount = 0;
    int index;
    for (index = 0; index < 2; index++) {
        Overlays[index] = (char const *)0;
    }
    if (ini.Get_String(section, "Overlays", (char const *)0, value) > 0) {
        index = 0;
        Wstring token;
        int position = value.Get_Token(0, ",", token);
        while (token.Length() > 0 && index < 2) {
            Overlays[index] = token;
            position = value.Get_Token(position, ",", token);
            index++;
        }
        OverlayCount = index;
    }

    ClickMap = (char const *)0;
    if (ini.Get_String(section, "ClickMap", (char const *)0, value) > 0) {
        ClickMap = value;
    }

    for (index = 1; index < 8; index++) {
        if (ini.Get_String(section, "Text" + Int_To_Wstring(index), (char const *)0, value) > 0) {
            text = Wstring_To_Wide(value);
            MSTextEntry *entry = new MSTextEntry(text);
            if (entry != 0) {
                Texts.Add(entry);
            }
        }
    }

    if (ini.Get_String(section, "Targets", (char const *)0, value) > 0) {
        int count = 0;
        Wstring token;
        int position = value.Get_Token(0, ",", token);
        if (token.Length() > 0) {
            count = token.As_Integer();
        }
        for (index = 0; index < count; index++) {
            Point2D point(-1, -1);
            int next = value.Get_Token(position, ",", token);
            if (token.Length() > 0) {
                point.X = token.As_Integer();
            }
            position = value.Get_Token(next, ",", token);
            if (token.Length() > 0) {
                point.Y = token.As_Integer();
            }
            Targets.Add(point);
        }
    }

    for (index = 0; index < 256; index++) {
        if (ini.Get_String(section, Int_To_Wstring(index), (char const *)0, value) > 0) {
            MapSelection *selection = new MapSelection(value, (char)index);
            if (selection != 0) {
                Selections.Add(selection);
            }
        }
    }
}
