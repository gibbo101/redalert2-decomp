// bool HouseTypeClass::Read_INI(CCINIClass &ini) (0x004F9550)
// The abstract type's keys, then the country keys: suffix, parent country
// and colour, prefix letter, the multipliers, multiplayer flags, the
// veteran infantry/unit/aircraft lists, and the side (moving this country
// from its old side's list to the new one's).
// The float multipliers unknown_0x100..unknown_0x148 are, in order,
// ArmorInfantryMult, ArmorUnitsMult, ArmorAircraftMult, ArmorBuildingsMult,
// ArmorDefensesMult, CostInfantryMult, CostUnitsMult, CostAircraftMult,
// CostBuildingsMult, CostDefensesMult, SpeedInfantryMult, SpeedUnitsMult,
// SpeedAircraftMult, BuildTimeInfantryMult, BuildTimeUnitsMult,
// BuildTimeAircraftMult, BuildTimeBuildingsMult, BuildTimeDefensesMult and
// IncomeMult.
#include "shared/house_type.hpp"
#include "shared/ccini_class.hpp"
#include "shared/side.hpp"
#include "shared/infantry_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/crt_string.hpp"
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ?Get_ColorScheme@CCINIClass@@QBEHPBD0H@Z=00469f50
// @ref ?Get_Side@CCINIClass@@QBEHPBD0H@Z=0046ab30
// @ref ?Sides@@3V?$DynamicVectorClass@PAVSideClass@@@@A=008661b0
// @ref _strtok=00782ec2
// @ref _strncpy=007823d0
// @ref ??0?$DynamicVectorClass@PAVInfantryTypeClass@@@@QAE@IPBQAVInfantryTypeClass@@@Z=004faa90
// @ref ?Add@?$DynamicVectorClass@PAVInfantryTypeClass@@@@QAE_NABQAVInfantryTypeClass@@@Z=004fabf0
// @ref ??0?$DynamicVectorClass@PAVUnitTypeClass@@@@QAE@IPBQAVUnitTypeClass@@@Z=004fae60
// @ref ?Add@?$DynamicVectorClass@PAVUnitTypeClass@@@@QAE_NABQAVUnitTypeClass@@@Z=004fafc0
// @ref ??0?$DynamicVectorClass@PAVAircraftTypeClass@@@@QAE@IPBQAVAircraftTypeClass@@@Z=004fb230
// @ref ??0?$DynamicVectorClass@PAVInfantryTypeClass@@@@QAE@ABV0@@Z=004fb4a0
// @ref ??0?$DynamicVectorClass@PAVUnitTypeClass@@@@QAE@ABV0@@Z=004fb530
// @ref ??0?$TypeList@PAVAircraftTypeClass@@@@QAE@ABV0@@Z=004fb410
// @ref ?Clear@?$VectorClass@PAVInfantryTypeClass@@@@UAEXXZ=004faa00
// @ref ?Clear@?$VectorClass@PAVUnitTypeClass@@@@UAEXXZ=004fadd0
// @ref ?Clear@?$VectorClass@PAVAircraftTypeClass@@@@UAEXXZ=004fb1a0
// @ref ??4?$VectorClass@PAVInfantryTypeClass@@@@QAEAAV0@ABV0@@Z=004fa8a0
// @ref ??4?$VectorClass@PAVUnitTypeClass@@@@QAEAAV0@ABV0@@Z=004fac70
// @ref ??4?$VectorClass@PAVAircraftTypeClass@@@@QAEAAV0@ABV0@@Z=004fb040
// @ref ??_7?$DynamicVectorClass@PAVInfantryTypeClass@@@@6B@=007a3178
// @ref ??_G?$DynamicVectorClass@PAVInfantryTypeClass@@@@UAEPAXI@Z=004faaf0
// @ref ??_7?$DynamicVectorClass@PAVUnitTypeClass@@@@6B@=007a3198
// @ref ??_7?$DynamicVectorClass@PAVAircraftTypeClass@@@@6B@=007a31b8
// @ref ??_G?$DynamicVectorClass@PAVAircraftTypeClass@@@@UAEPAXI@Z=004fb290
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_03CEPL@ROF?$AA@=007dae30
// @ref ??_C@_04IHF@Cost?$AA@=007dae28
// @ref ??_C@_04LJDI@Side?$AA@=007cdd8c
// @ref ??_C@_05KFDN@Armor?$AA@=007d3824
// @ref ??_C@_06HPDC@Suffix?$AA@=007dae64
// @ref ??_C@_06MONO@Prefix?$AA@=007dae4c
// @ref ??_C@_07IIJG@SmartAI?$AA@=007dade8
// @ref ??_C@_08DELK@Airspeed?$AA@=007dae34
// @ref ??_C@_09BHCF@Multiplay?$AA@=007dae10
// @ref ??_C@_09IFKJ@Firepower?$AA@=007d3810
// @ref ??_C@_09JFOK@BuildTime?$AA@=007dae1c
// @ref ??_C@_09JLGL@WallOwner?$AA@=007dadf0
// @ref ??_C@_0BA@JBMG@VeteranInfantry?$AA@=007dac60
// @ref ??_C@_0BA@OADN@VeteranAircraft?$AA@=007dac40
// @ref ??_C@_0BB@HGHI@CostInfantryMult?$AA@=007dad74
// @ref ??_C@_0BB@HIJI@CostAircraftMult?$AA@=007dad50
// @ref ??_C@_0BB@IKHO@MultiplayPassive?$AA@=007dadfc
// @ref ??_C@_0BB@JLEI@CostDefensesMult?$AA@=007dad28
// @ref ??_C@_0BC@CECC@SpeedInfantryMult?$AA@=007dad14
// @ref ??_C@_0BC@CKMC@SpeedAircraftMult?$AA@=007dacf0
// @ref ??_C@_0BC@DPBP@CostBuildingsMult?$AA@=007dad3c
// @ref ??_C@_0BC@GFIB@ArmorAircraftMult?$AA@=007dadb0
// @ref ??_C@_0BC@GLGB@ArmorInfantryMult?$AA@=007dadd4
// @ref ??_C@_0BC@IGFB@ArmorDefensesMult?$AA@=007dad88
// @ref ??_C@_0BD@NCAC@ArmorBuildingsMult?$AA@=007dad9c
// @ref ??_C@_0BD@PCOH@BuildTimeUnitsMult?$AA@=007dacc4
// @ref ??_C@_0BG@GCGE@BuildTimeAircraftMult?$AA@=007dacac
// @ref ??_C@_0BG@GMIE@BuildTimeInfantryMult?$AA@=007dacd8
// @ref ??_C@_0BG@IBLE@BuildTimeDefensesMult?$AA@=007dac7c
// @ref ??_C@_0BH@LLAF@BuildTimeBuildingsMult?$AA@=007dac94
// @ref ??_C@_0L@JABB@IncomeMult?$AA@=007dac70
// @ref ??_C@_0M@CGIC@Groundspeed?$AA@=007dae40
// @ref ??_C@_0N@CDNB@VeteranUnits?$AA@=007dac50
// @ref ??_C@_0O@GFLN@ParentCountry?$AA@=007dae54
// @ref ??_C@_0O@GJJE@CostUnitsMult?$AA@=007dad64
// @ref ??_C@_0P@BKHF@ArmorUnitsMult?$AA@=007dadc4
// @ref ??_C@_0P@MPIG@SpeedUnitsMult?$AA@=007dad04

extern "C" char *__cdecl strtok(char *string, char const *delimiters);

#define TYPE_LIST_READER(NAME, TYPE, FIND) \
static inline TypeList<TYPE *> NAME(CCINIClass &ini, char const *section, char const *entry, TypeList<TYPE *> const &defvalue) \
{ \
    char buffer[128]; \
    if (ini.Get_String(section, entry, unknown_string_83c55c, buffer, sizeof(buffer))) { \
        TypeList<TYPE *> list; \
        for (char *name = strtok(buffer, ","); name != 0 && *name != 0; name = strtok(0, ",")) { \
            TYPE *object = FIND(name); \
            if (object != 0) { \
                list.Add(object); \
            } \
        } \
        return list; \
    } \
    return defvalue; \
}

TYPE_LIST_READER(Get_Infantry_List, InfantryTypeClass, InfantryTypeClass::Find_Or_Make)
TYPE_LIST_READER(Get_Unit_List, UnitTypeClass, UnitTypeClass::Find_Or_Make)
TYPE_LIST_READER(Get_Aircraft_List, AircraftTypeClass, AircraftTypeClass::Find_Or_Make)

bool HouseTypeClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
        char buffer[32];
        ini.Get_String(ID, "Suffix", unknown_string_83c55c, buffer, sizeof(Suffix));
        if (strlen(buffer) != 0) {
            strcpy(Suffix, buffer);
        }
        ini.Get_String(ID, "ParentCountry", ID, buffer, sizeof(ParentCountry));
        ParentCountry = FixedString<25>(buffer);
        Color = ini.Get_ColorScheme(ID, "Color", Color);
        char prefix[2];
        buffer[0] = Prefix;
        buffer[1] = '\0';
        ini.Get_String(ID, "Prefix", buffer, prefix, sizeof(prefix));
        Prefix = prefix[0];
        FirepowerMult = ini.Get_Double(ID, "Firepower", FirepowerMult);
        GroundspeedMult = ini.Get_Double(ID, "Groundspeed", GroundspeedMult);
        AirspeedMult = ini.Get_Double(ID, "Airspeed", AirspeedMult);
        ArmorMult = ini.Get_Double(ID, "Armor", ArmorMult);
        ROFMult = ini.Get_Double(ID, "ROF", ROFMult);
        CostMult = ini.Get_Double(ID, "Cost", CostMult);
        BuildtimeMult = ini.Get_Double(ID, "BuildTime", BuildtimeMult);
        Multiplay = ini.Get_Bool(ID, "Multiplay", Multiplay);
        MultiplayPassive = ini.Get_Bool(ID, "MultiplayPassive", MultiplayPassive);
        WallOwner = ini.Get_Bool(ID, "WallOwner", WallOwner);
        SmartAI = ini.Get_Bool(ID, "SmartAI", SmartAI);
        unknown_0x100 = ini.Get_Double(ID, "ArmorInfantryMult", unknown_0x100);
        unknown_0x104 = ini.Get_Double(ID, "ArmorUnitsMult", unknown_0x104);
        unknown_0x108 = ini.Get_Double(ID, "ArmorAircraftMult", unknown_0x108);
        unknown_0x10C = ini.Get_Double(ID, "ArmorBuildingsMult", unknown_0x10C);
        unknown_0x110 = ini.Get_Double(ID, "ArmorDefensesMult", unknown_0x110);
        unknown_0x114 = ini.Get_Double(ID, "CostInfantryMult", unknown_0x114);
        unknown_0x118 = ini.Get_Double(ID, "CostUnitsMult", unknown_0x118);
        unknown_0x11C = ini.Get_Double(ID, "CostAircraftMult", unknown_0x11C);
        unknown_0x120 = ini.Get_Double(ID, "CostBuildingsMult", unknown_0x120);
        unknown_0x124 = ini.Get_Double(ID, "CostDefensesMult", unknown_0x124);
        unknown_0x128 = ini.Get_Double(ID, "SpeedInfantryMult", unknown_0x128);
        unknown_0x12C = ini.Get_Double(ID, "SpeedUnitsMult", unknown_0x12C);
        unknown_0x130 = ini.Get_Double(ID, "SpeedAircraftMult", unknown_0x130);
        unknown_0x134 = ini.Get_Double(ID, "BuildTimeInfantryMult", unknown_0x134);
        unknown_0x138 = ini.Get_Double(ID, "BuildTimeUnitsMult", unknown_0x138);
        unknown_0x13C = ini.Get_Double(ID, "BuildTimeAircraftMult", unknown_0x13C);
        unknown_0x140 = ini.Get_Double(ID, "BuildTimeBuildingsMult", unknown_0x140);
        unknown_0x144 = ini.Get_Double(ID, "BuildTimeDefensesMult", unknown_0x144);
        unknown_0x148 = ini.Get_Double(ID, "IncomeMult", unknown_0x148);
        VeteranInfantry = Get_Infantry_List(ini, ID, "VeteranInfantry", VeteranInfantry);
        VeteranUnits = Get_Unit_List(ini, ID, "VeteranUnits", VeteranUnits);
        VeteranAircraft = Get_Aircraft_List(ini, ID, "VeteranAircraft", VeteranAircraft);
        int side = Side;
        Side = ini.Get_Side(ID, "Side", side);
        if (Side != side) {
            if (side != -1) {
                Sides[side]->Houses.Delete(House);
            }
            if (Side != -1) {
                Sides[Side]->Houses.Add(House);
            }
        }
        return true;
    }
    return false;
}
