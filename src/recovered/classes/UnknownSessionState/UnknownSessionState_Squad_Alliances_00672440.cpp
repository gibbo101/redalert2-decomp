#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/session_state.hpp"
#include "shared/house.hpp"
#include "shared/special.hpp"
#include "shared/id_source.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/debug_printf.hpp"

// The squad lists' constructors expand over the out-of-line VectorClass constructor (0x00674BA0).
template <>
VectorClass<HouseClass *>::VectorClass(unsigned size, HouseClass *const *array);
template <>
inline DynamicVectorClass<HouseClass *>::DynamicVectorClass(unsigned size, HouseClass *const *array)
    : VectorClass<HouseClass *>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

// Makes each squad's members allies of one another (game mode 4, after the load wait of 0x0065C7D0).
void UnknownSessionState::Unknown_00672440()
{
    unknown_638 = false;
    if (Type != 4) {
        return;
    }
    unknown_id_source_a3d290->Special().FixedAlliance = false;
    Debug_Printf("Squad 1 = %s\n", unknown_squad_1_b2a820);
    Debug_Printf("Squad 2 = %s\n", unknown_squad_2_b293d8);
    if (strlen(unknown_squad_1_b2a820) == 0 || strlen(unknown_squad_2_b293d8) == 0) {
        return;
    }
    int i;
    int j;
    char *name;
    DynamicVectorClass<HouseClass *> squad_1;
    DynamicVectorClass<HouseClass *> squad_2;
    char *names = new char[(strlen(unknown_squad_1_b2a820) > strlen(unknown_squad_2_b293d8) ? strlen(unknown_squad_1_b2a820) : strlen(unknown_squad_2_b293d8)) + 0x20];
    strcpy(names, unknown_squad_1_b2a820);
    for (name = strtok(names, ","); name && *name; name = strtok(0, ",")) {
        for (i = 0; i < Houses.Count(); i++) {
            HouseClass *house = Houses[i];
            if (house->unknown_134 && _stricmp(house->IniName, name) == 0) {
                squad_1.Add(house);
            }
        }
    }
    strcpy(names, unknown_squad_2_b293d8);
    for (name = strtok(names, ","); name && *name; name = strtok(0, ",")) {
        for (i = 0; i < Houses.Count(); i++) {
            HouseClass *house = Houses[i];
            if (house->unknown_134 && _stricmp(house->IniName, name) == 0) {
                squad_2.Add(house);
            }
        }
    }
    if (squad_1.Count() > 1) {
        for (i = 0; i < squad_1.Count(); i++) {
            for (j = 0; j < squad_1.Count(); j++) {
                if (squad_1[i]->ArrayIndex != squad_1[j]->ArrayIndex) {
                    squad_1[i]->Make_Ally(squad_1[j], false);
                }
            }
        }
    }
    if (squad_2.Count() > 1) {
        for (i = 0; i < squad_2.Count(); i++) {
            for (j = 0; j < squad_2.Count(); j++) {
                if (squad_2[i]->ArrayIndex != squad_2[j]->ArrayIndex) {
                    squad_2[i]->Make_Ally(squad_2[j], false);
                }
            }
        }
    }
    delete names;
    unknown_638 = true;
    unknown_id_source_a3d290->Special().FixedAlliance = true;
}
// @ref ??0?$VectorClass@PAVHouseClass@@@@QAE@IPBQAVHouseClass@@@Z=00674ba0
// @ref ?unknown_squad_1_b2a820@@3PADA=00b2a820
// @ref ?unknown_squad_2_b293d8@@3PADA=00b293d8
// @ref ??_C@_0O@NLPF@Squad?51?5?$DN?5?$CFs?6?$AA@=007f3bc0
// @ref ??_C@_0O@KIEL@Squad?52?5?$DN?5?$CFs?6?$AA@=007f3bb0
