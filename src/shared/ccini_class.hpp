// CCINIClass list readers (CCINI unit, 0x0046B1B0-0x0046C87B): comma
// separated INI values parsed into a TypeList returned by value.
//
// Each reader is a member (`this` is the INI, used for Get_String
// 0x0050E9A0), returns the list through a hidden pointer and takes the
// default list by value (0x1C bytes, destroyed by the callee): `ret 0x28`.
// Shape (0x0046B1B0): read the entry into a 512-byte buffer with an empty
// default; when it is present, strtok(",") the tokens into a local list
// (stopping at an empty token) and return a copy of it, otherwise return a
// copy of the default. Reader names are hypotheses.
#ifndef SHARED_CCINI_CLASS_HPP
#define SHARED_CCINI_CLASS_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/ini_class.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/type_list.hpp"
#include "shared/rgb_class.hpp"
#include "shared/voc_class.hpp"

class TechnoTypeClass;
class FileClass;
class Straw;
class Pipe;
class ObjectTypeClass;
class TargetClass;
class Cell;
class HSVClass;
struct AbilitiesStruct;
enum SpeedType;
enum LayerType;
enum LevelType;
enum ArmorType;
enum CrateType;
enum SourceType;
enum TheaterType;
enum LandType;
enum CategoryType;
enum RTTIType;
enum BuildCat;

// The value CCINIClass 0x00469F10 / 0x00469F30 read and write with Get_Hex /
// Put_Hex. A class (it is returned through a hidden pointer) holding one int;
// both functions are unreferenced and the type is unidentified.
struct UnknownHexValue {
    UnknownHexValue(int value) : Value(value) {}
    int Value;
};

class CCINIClass : public INIClass {
public:
    CCINIClass() : IsDigestValid(false) {}
    // 0x0046C1C0: CRC of the message digest (computed on first use).
    int Get_Unique_ID() const;
    // 0x0046C260: SHA-1 of the saved INI text into Digest.
    void Calculate_Message_Digest();
    void Invalidate_Message_Digest() { IsDigestValid = false; }

    // 0x0046B1B0: integers (atoi of each token).
    TypeList<int> Get_Integer_List(char const *section, char const *entry, TypeList<int> defvalue);
    // 0x0046B370: writes the integers comma separated ("%d" each).
    bool Put_Integer_List(char const *section, char const *entry, TypeList<int> const &list);
    // 0x0046B460: infantry or vehicle type names (InfantryTypeClass::
    // From_Name first, then UnitTypeClass::From_Name) as packed object
    // references (TargetClass, kind in the top byte); names of neither kind
    // and references of kind 0 are skipped. (The member name predates
    // identifying the two lists.)
    TypeList<int> Get_Anim_Target_List(char const *section, char const *entry, TypeList<int> defvalue);
    // 0x0046B680: writes the targets' type IDs comma separated.
    bool Put_Anim_Target_List(char const *section, char const *entry, TypeList<int> const &list);
    // 0x0046B780 / 0x0046B860: three comma separated floats (atof) or
    // integers (atoi); the default when the entry is absent.
    INIVector3 Get_Float_Triple(char const *section, char const *entry, INIVector3 const &defvalue);
    INIPoint3D Get_Integer_Triple(char const *section, char const *entry, INIPoint3D const &defvalue);
    // 0x0046B930: techno types named by ID (case-insensitive scan of
    // TechnoTypes, first match; unknown names are skipped).
    TypeList<TechnoTypeClass *> Get_Techno_List(char const *section, char const *entry,
                                                TypeList<TechnoTypeClass *> defvalue);
    // 0x0046BB30: writes the techno types' IDs comma separated.
    bool Put_Techno_List(char const *section, char const *entry, TypeList<TechnoTypeClass *> const &list);
    // 0x0046BC00: house type indices, 128-byte buffer: a house name adds
    // its index, a side name adds every house of the side (SideClass's
    // TypeList<int> at +0x98).
    TypeList<int> Get_House_List(char const *section, char const *entry, TypeList<int> defvalue);
    // 0x0046C2F0: an infantry, unit, aircraft or building type by name
    // (128-byte buffer, default "<none>"), searched in that order; null
    // when none matches.
    ObjectTypeClass *Get_Object_Type(char const *section, char const *entry);
    // 0x0046C3B0: the target's type ID, or "<none>".
    bool Put_Target_Type(char const *section, char const *entry, TargetClass const &target);
    // 0x0046C400 / 0x0046C490: a movement type or layer by name (128-byte
    // buffer, the default's name as the string default).
    SpeedType Get_SpeedType(char const *section, char const *entry, SpeedType defvalue);
    LayerType Get_LayerType(char const *section, char const *entry, LayerType defvalue);
    // 0x0046C880 / 0x0046C950: three comma separated integers into
    // separate variables (each kept when its token is missing) / "%d,%d,%d".
    void Get_Integers(char const *section, char const *entry, int &first, int &second, int &third);
    bool Put_Integers(char const *section, char const *entry, int first, int second, int third);
    // 0x0046C9D0: a LevelType by name (first token), else the default.
    LevelType Get_Level(char const *section, char const *entry, LevelType defvalue);
    // 0x0046CA80: the abilities named in the entry (128-byte buffer;
    // unknown names are skipped), else the default.
    AbilitiesStruct Get_Abilities(char const *section, char const *entry, AbilitiesStruct const &defvalue);
    // 0x0046BF60: colours written "(r,g,b)" as three tokens: the first
    // skips its leading character, the last loses its final one.
    TypeList<RGBClass> Get_Color_List(char const *section, char const *entry, TypeList<RGBClass> defvalue);

    // BEGIN unit-3 members
    // 0x00469AE0
    int Get_Lepton(char const *section, char const *entry, int defvalue) const;
    // 0x00469B20
    bool Put_Lepton(char const *section, char const *entry, int lepton);
    // 0x00469B50
    bool Put_Facing(char const *section, char const *entry, int facing);
    // 0x00469BA0
    int Get_Facing(char const *section, char const *entry, int defvalue) const;
    // 0x00469C80
    bool Put_Cell(char const *section, char const *entry, Cell const &cell);
    // 0x00469CD0
    int Get_Percent(char const *section, char const *entry, int defvalue) const;
    // 0x00469D30
    bool Put_Percent(char const *section, char const *entry, int value);
    // 0x00469D60
    int Get_PipType(char const *section, char const *entry, int defvalue) const;
    // 0x00469DD0
    bool Put_PipType(char const *section, char const *entry, int pip);
    // 0x00469E00
    int Get_PipScale(char const *section, char const *entry, int defvalue) const;
    // 0x00469EA0
    CategoryType Get_CategoryType(char const *section, char const *entry, CategoryType defvalue) const;
    // 0x00469EE0
    bool Put_CategoryType(char const *section, char const *entry, CategoryType category);
    // 0x0046A260
    int Get_Foundation(char const *section, char const *entry, int defvalue) const;
    // 0x0046A2D0
    bool Put_Foundation(char const *section, char const *entry, int foundation);
    // 0x0046A300
    int Get_MovementZone(char const *section, char const *entry, int defvalue) const;
    // 0x0046A370
    bool Put_MovementZone(char const *section, char const *entry, int zone);
    // 0x0046A3A0
    int Get_ActionType(char const *section, char const *entry, int defvalue) const;
    // 0x0046A8B0
    ArmorType Get_ArmorType(char const *section, char const *entry, ArmorType defvalue) const;
    // 0x0046A900
    bool Put_ArmorType(char const *section, char const *entry, ArmorType armor);
    // 0x0046A970
    LandType Get_LandType(char const *section, char const *entry, LandType defvalue) const;
    // 0x0046ABE0
    bool Put_Side(char const *section, char const *entry, int side);
    // 0x0046ACB0
    TheaterType Get_TheaterType(char const *section, char const *entry, TheaterType defvalue) const;
    // 0x0046ADC0
    SourceType Get_SourceType(char const *section, char const *entry, SourceType defvalue) const;
    // 0x0046AE30
    CrateType Get_CrateType(char const *section, char const *entry, CrateType defvalue) const;
    // 0x0046AE80
    bool Put_CrateType(char const *section, char const *entry, CrateType crate);
    // 0x00469C00
    Cell Get_Cell(char const *section, char const *entry, Cell const &defvalue) const;
    // 0x0046A010
    RGBClass Get_RGB(char const *section, char const *entry, RGBClass const &defvalue) const;
    // 0x0046A0E0
    bool Put_RGB(char const *section, char const *entry, RGBClass const &rgb);
    // 0x0046A130
    HSVClass Get_HSV(char const *section, char const *entry, HSVClass const &defvalue) const;
    // 0x0046A210
    bool Put_HSV(char const *section, char const *entry, HSVClass const &hsv);
    // 0x0046A4B0
    RTTIType Get_RTTIType(char const *section, char const *entry, RTTIType defvalue) const;
    // 0x0046A520
    BuildCat Get_BuildCat(char const *section, char const *entry, BuildCat defvalue) const;
    // 0x0046AA00
    int Get_HousesType(char const *section, char const *entry, int defvalue) const;
    // 0x0046AAB0
    bool Put_HousesType(char const *section, char const *entry, int house);
    // 0x0046AB30
    int Get_Side(char const *section, char const *entry, int defvalue) const;
    // 0x0046A410
    int Get_SuperWeaponType(char const *section, char const *entry, int defvalue) const;
    // 0x0046A460
    int Get_VoxType(char const *section, char const *entry, int defvalue) const;
    // 0x0046A590
    int Get_Owners(char const *section, char const *entry, int defvalue) const;
    // 0x0046A610
    bool Put_Owners(char const *section, char const *entry, int owners);
    // 0x0046A720
    int Get_Houses(char const *section, char const *entry, int defvalue) const;
    // 0x0046A7A0
    bool Put_Houses(char const *section, char const *entry, int houses);
    // 0x0046AC10
    int Get_Listed_Name(char const *section, char const *entry, int defvalue) const;
    // 0x0046AC60
    bool Put_Listed_Name(char const *section, char const *entry, unsigned index);
    // 0x0046AD30
    int Get_ThemeType(char const *section, char const *entry, int defvalue) const;
    // 0x00469F10 (unreferenced): a hex value returned through a hidden pointer
    UnknownHexValue Get_UnknownHex_469f10(char const *section, char const *entry, int defvalue) const;
    // 0x00469F30 (unreferenced)
    bool Put_UnknownHex_469f30(char const *section, char const *entry, int value);
    // 0x00469F50
    int Get_ColorScheme(char const *section, char const *entry, int defvalue) const;
    // 0x00469FE0
    bool Put_ColorScheme(char const *section, char const *entry, int scheme);
    // 0x0046A4F0
    bool Put_RTTIType(char const *section, char const *entry, RTTIType rtti);
    // 0x0046A560
    bool Put_BuildCat(char const *section, char const *entry, BuildCat category);
    // 0x0046A9D0
    bool Put_LandType(char const *section, char const *entry, LandType land);
    // 0x0046AD00
    bool Put_TheaterType(char const *section, char const *entry, TheaterType theater);
    // 0x0046AD90
    bool Put_ThemeType(char const *section, char const *entry, int theme);
    // 0x0046AE10
    bool Put_SourceType(char const *section, char const *entry, SourceType source);
    // 0x0046AFB0
    bool Put_Buildings(char const *section, char const *entry, int buildings);
    // 0x0046B0B0
    bool Put_Voc_List(char const *section, char const *entry, TypeList<int> list);
    // 0x004696B0
    int Load(FileClass &file, bool withdigest, bool keep_comments);
    // Without comments (an inline split: RulesClass::Process 0x006433A0 spends inline budget
    // on it inside the LANGRULE.INI scope, which keeps INIClass's second list constructor
    // 0x0040E160 out of line as in the original).
    int Load(FileClass &file, bool withdigest) { return Load(file, withdigest, false); }
    // 0x004697E0
    int Load(Straw &file, bool withdigest, bool keep_comments);
    // 0x004698F0
    int Save(FileClass &file, bool withdigest);
    // 0x00469A00
    int Save(Pipe &pipe, bool withdigest);
    // 0x0046A920
    bool Put_VocType(char const *section, char const *entry, int voc);
    // END unit-3 members

    bool IsDigestValid;             // +0x38 Digest is current
    unsigned char Digest[20];       // +0x39 SHA-1 of the saved text
};

// The art INI (hypothesis: art.ini; 0x008397F0): object images and their
// settings are read from it.
extern CCINIClass ArtINI;
// The game settings INI (RA2.INI; 0x00839740): OptionsClass and the
// firewall settings read and write it.
extern CCINIClass unknown_ini_839740;   // 0x00839740
// The rules INI (pointer 0x008396D0), the AI INI (0x008397A0; its teams,
// scripts, task forces and AI triggers are the global ones) and the INI
// Read_Scenario_INI hands to RulesClass::Advanced_Command_Bar (0x00839860).
extern CCINIClass *unknown_ini_8396d0;  // 0x008396D0
extern CCINIClass unknown_ini_8397a0;   // 0x008397A0
extern CCINIClass unknown_ini_839860;   // 0x00839860
// A fifth INI object of the INI globals unit (0x008396E0; use unknown).
extern CCINIClass unknown_ini_8396e0;   // 0x008396E0

// 0x0046C520 (not a member: __fastcall, result pointer in ECX, the INI in
// EDX): building prerequisites, 128-byte buffer. The group names POWER,
// FACTORY, BARRACKS, RADAR, TECH and PROC add -1 ... -6 (each name is tested,
// in that order); any other token adds its BuildingTypes index when found.
TypeList<int> __fastcall Get_Prerequisite_List(CCINIClass &ini, char const *section, char const *entry,
                                               TypeList<int> defvalue);

// 0x0050B610 (same convention): the sound names of an entry (WeaponType "Report"); each
// token is looked up by name and its index added.
TypeList<int> __fastcall Get_Voc_List(CCINIClass &ini, char const *section, char const *entry,
                                      TypeList<int> defvalue);

// The type named by an entry (a 128-byte buffer; T::Find_Or_Make makes unknown types), else
// the default. WeaponType expands it inline for "AssaultAnim", "Warhead" and "Projectile".
template <class T>
inline T *__fastcall Get_Type(CCINIClass &ini, char const *section, char const *entry, T *defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        return T::Find_Or_Make(buffer);
    }
    return defvalue;
}

// The sound effect named by an entry (a 128-byte buffer; VocClass::From_Name), else the
// default (also for an unknown name). TechnoTypeClass::Read_INI expands it inline.
inline int Get_Sound(CCINIClass &ini, char const *section, char const *entry, int defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        int voc = VocClass::From_Name(buffer);
        if (voc != -1) {
            return voc;
        }
    }
    return defvalue;
}

// Rules.ini lists of one object type, named by ID (0x00653BD0 BuildingTypeClass, 0x00653E90
// InfantryTypeClass, 0x00654150 TerrainTypeClass: one template, instantiated per type). The
// reader is __fastcall like Get_Prerequisite_List: result pointer in ECX, the INI in EDX, the
// default list by reference. Each token names a type (T::Find_Or_Make makes unknown ones and
// gives 0 for "none", which is not added); the default list is returned when the entry is missing.
template <class T>
class TypeListReader {
public:
    static TypeList<T *> __fastcall Get(CCINIClass &ini, char const *section, char const *entry,
                                        TypeList<T *> const &defvalue);
};

template <class T>
TypeList<T *> __fastcall TypeListReader<T>::Get(CCINIClass &ini, char const *section, char const *entry,
                                                TypeList<T *> const &defvalue)
{
    char buffer[128];
    if (ini.Get_String(section, entry, "", buffer, sizeof(buffer))) {
        TypeList<T *> list;
        for (char *token = strtok(buffer, ","); token != 0 && *token != '\0'; token = strtok(0, ",")) {
            T *type = T::Find_Or_Make(token);
            if (type != 0) {
                list.Add(type);
            }
        }
        return list;
    }
    return defvalue;
}

#endif
