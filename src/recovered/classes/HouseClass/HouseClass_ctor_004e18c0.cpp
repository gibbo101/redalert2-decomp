// @ref ??0?$VectorClass@PAUIConnectionPoint@@@@QAE@IPBQAUIConnectionPoint@@@Z=004f89f0
// @ref ??0StorageClass@@QAE@XZ=0069ada0
// @ref ??0UnknownHouseTracker@@QAE@XZ=0070c440
// @ref ?unknown_func_70c4d0@UnknownHouseTracker@@QAEXH@Z=0070c4d0
// HouseClass normal constructor004E18C0; complete3860-byte body plus12 frozen NOP bytes.
// Layout names remain hypotheses where current shared headers do not identify them.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/building_type_list.hpp"
extern DynamicVectorClass<AircraftTypeClass *> AircraftTypes;
extern DynamicVectorClass<InfantryTypeClass *> InfantryTypes;
extern DynamicVectorClass<UnitTypeClass *> UnitTypes;
extern "C" wchar_t *__cdecl wcscpy(wchar_t *, wchar_t const *);

HouseClass::HouseClass(HouseTypeClass *type)
    : AbstractClass(),
      ArrayIndex(-1),
      Type(type),
      unknown_c8(unknown_id_source_a3d290->unknown_610),
      unknown_d0(1.0),
      unknown_d8(1.0),
      unknown_e0(1.0),
      unknown_e8(1.0),
      unknown_f0(1.0),
      unknown_f8(1.0),
      unknown_100(1.0),
      unknown_108(0.0),
      unknown_110(0.0),
      unknown_118(0),
      unknown_11c(1),
      unknown_120(0),
      unknown_124(0),
      unknown_128(0),
      unknown_12c(0),
      unknown_134(0),
      unknown_135(0),
      unknown_136(0),
      unknown_137(0),
      unknown_138(1),
      unknown_139(0),
      unknown_13a(0),
      unknown_13b(0),
      unknown_13c(0),
      unknown_13d(0),
      unknown_13e(0),
      unknown_13f(0),
      unknown_140(0),
      unknown_141(0),
      unknown_142(0),
      unknown_143(0),
      unknown_144(1),
      unknown_148(0),
      unknown_14c(0),
      unknown_150(0),
      unknown_154(-1),
      unknown_188(0),
      unknown_189(0),
      unknown_18a(0),
      unknown_18b(0),
      unknown_18c(0),
      unknown_18d(0),
      unknown_18e(0),
      unknown_18f(0),
      unknown_190(0),
      unknown_191(0),
      unknown_192(1),
      unknown_194(unknown_118),
      unknown_198(0),
      unknown_1b4(-1),
      unknown_1b8(-1),
      unknown_1bc(-1),
      unknown_1c0(-1),
      unknown_1c4(0),
      unknown_204(0),
      unknown_205(0),
      unknown_206(0),
      unknown_207(0),
      unknown_208(0),
      unknown_20c(0),
      unknown_210(0),
      unknown_214(0),
      unknown_218(0),
      unknown_21c(0),
      unknown_220(0),
      unknown_224(0),
      unknown_228(0),
      unknown_22c(0),
      CurBuildings(0),
      unknown_234(0),
      unknown_238(0),
      Balance(0),
      Capacity(0),
      unknown_52b8(0),
      unknown_52bc(0),
      unknown_52c0(0),
      unknown_52c4(0),
      unknown_52c8(0),
      unknown_52cc(0),
      Power(0),
      Drain(0),
      unknown_52d8(0),
      unknown_52dc(0),
      unknown_52e0(0),
      unknown_52e4(0),
      unknown_52e8(0),
      unknown_52ec(0),
      unknown_52f0(0),
      unknown_52f4(0),
      unknown_52f8(0),
      unknown_52fc(0),
      unknown_52fd(0),
      unknown_52fe(0),
      unknown_52ff(0),
      unknown_5300(0),
      unknown_5301(0),
      unknown_5302(0),
      unknown_5303(0),
      unknown_5304(0),
      unknown_5308(0),
      unknown_530c(0, 0),
      unknown_5360(0),
      unknown_53b4(0),
      unknown_53b8(-1),
      BaseCenter(0, 0, 0),
      unknown_53c8(0),
      unknown_5408(0),
      unknown_540c(-1),
      unknown_5410(0),
      unknown_5414(0),
      unknown_5418(0),
      unknown_541c(1),
      unknown_54ec(0),
      unknown_54f0(-1),
      unknown_553c(-1),
      unknown_5540(-1),
      unknown_5544(-1),
      unknown_5548(-1),
      unknown_554c(100),
      unknown_5550(75),
      unknown_5554(75),
      unknown_5558(75),
      unknown_555c(0),
      unknown_55e4(0),
      unknown_55e8(0),
      unknown_55e9(0, 0, 0),
      unknown_55ec(255, 255, 255),
      unknown_5668(1),
      unknown_5669(1),
      unknown_566a(0),
      unknown_566c(0),
      unknown_566e(0),
      unknown_5670(0),
      unknown_5672(0),
      Allies(0),
      unknown_5678(int(900 * Rules->DamageDelay)),
      unknown_5684(1),
      unknown_5690(0),
      unknown_569c(1),
      unknown_56a8(1),
      unknown_56b4(1),
      unknown_56c0(1),
      unknown_56cc(0),
      ColorSchemeIndex(0),
      unknown_15f44(0),
      unknown_15f60(0),
      unknown_15f64(0),
      unknown_15f68(1.0),
      unknown_15f70(1.0),
      unknown_15f7c(0.33f),
      unknown_15f80(0.33f),
      unknown_15f84(0.34f),
      unknown_15f88(0)
{
    unknown_15ef5 = FixedString<32>(unknown_string_83c55c);
    UIName[0] = 0;
    Create_ID();
    if (Type != 0) {
        ColorSchemeIndex = Type->Color;
    }
    unknown_objects_ac0cb0.Add(this);
    unknown_abstracts_ac0c80.Add(this);
    unknown_objects_ac0c30.Add(this);
    unknown_objects_ac0c58.Add(this);
    unknown_AbstractClass_list_00ac0d60.Add(this);
    ArrayIndex = Houses.Count();
    if (type != 0) {
        for (int index = 0; index < Houses.Count(); index++) {
            Houses[index]->AngerNodes.Add(AngerStruct(this, 0));
            AngerNodes.Add(AngerStruct(Houses[index], 0));
            Houses[index]->ScoutNodes.Add(ScoutStruct(this, false));
            ScoutNodes.Add(ScoutStruct(Houses[index], false));
        }
    }
    Houses.Add(this);
    memset(unknown_56d0, 0, sizeof(unknown_56d0));
    for (int index = 0; index < SuperWeaponTypes.Count(); index++) {
        Supers.Add(new SuperClass(SuperWeaponTypes[index], this));
    }
    memset(unknown_5310, 0, sizeof(unknown_5310));
    memset(unknown_5364, 0, sizeof(unknown_5364));
    if (type != 0) {
        IniName = (char const *)type->ID;
        wcscpy(UIName, type->UIName);
    }
    memset(unknown_56d0, 0, sizeof(unknown_56d0));
    unknown_120 |= 1 << ArrayIndex;
    int attack = Random_Pick(450, 1800);
    attack = int(attack * Rules->AttackDelay);
    unknown_54e0 = attack;
    unknown_54ec = attack;
    unknown_268.unknown_func_70c4d0(AircraftTypes.Count());
    unknown_a70.unknown_func_70c4d0(InfantryTypes.Count());
    unknown_1278.unknown_func_70c4d0(UnitTypes.Count());
    unknown_1a80.unknown_func_70c4d0(BuildingTypes.Count());
    unknown_2288.unknown_func_70c4d0(AircraftTypes.Count());
    unknown_2a90.unknown_func_70c4d0(InfantryTypes.Count());
    unknown_3298.unknown_func_70c4d0(UnitTypes.Count());
    unknown_3aa0.unknown_func_70c4d0(BuildingTypes.Count());
    unknown_42a8.unknown_func_70c4d0(BuildingTypes.Count());
    unknown_4ab0.unknown_func_70c4d0(19);
    for (index = 0; index < 12; index++) {
        WaypointPaths[index] = 0;
    }
    if (type != 0) {
        unknown_143 = true;
    }
    unknown_130 = -1;
    if (Type != 0) {
        if (Type->Side == 0) {
            unknown_130 = 0;
        } else if (Type->Side == 1) {
            unknown_130 = 1;
        }
    }
    IUnknown *unknown = 0;
    QueryInterface(IID_IUnknown_7afce0, (void **)&unknown);
    unknown_15f60 = new ConnectionPointClass(unknown_iid_7a1ac0, unknown);
    IConnectionPoint *connection;
    unknown_15f60->QueryInterface(IID_IConnectionPoint, (void **)&connection);
    ConnectionPoints.Add(connection);
    unknown->Release();
}
