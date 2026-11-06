// char *__fastcall Unknown_006F85E0(objects, name, limit, best) (0x006F85E0)
// Of the distinct object types in a list picks the dearest by total cost under limit other than name, or the
// costliest; a copy of its ID in a new 100-byte buffer, the total in *best. Caller 0x006F81B0.
// @ref ??0?$VectorClass@H@@=0046d020
// @ref ?Add@?$DynamicVectorClass@PBD@@QAE_NABQBD@Z=006f8b40
// @ref ??0?$DynamicVectorClass@PBD@@QAE@IPBQBD@Z=006f8ae0
#include "shared/uicmnds.hpp"
#include "shared/crt_string.hpp"
#include "shared/object_type.hpp"
#include "shared/techno_type.hpp"

int __fastcall unknown_find_name_index(DynamicVectorClass<char const *> const &names, char const *name);

char *__fastcall Unknown_006F85E0(DynamicVectorClass<TechnoClass *> const &objects, char const *name, int limit, int *best)
{
    DynamicVectorClass<char const *> *names = Unknown_Type_Names_006F84A0((DynamicVectorClass<ObjectClass *> const &)objects);
    DynamicVectorClass<int> *costs = new DynamicVectorClass<int>(0, 0);
    int count = names->Count();
    for (int index = 0; index < count; index++) {
        costs->Add(0);
    }
    int total = objects.Count();
    for (int item = 0; item < total; item++) {
        TechnoClass *object = objects[item];
        char const *id = object->Class_Of()->ID;
        int found = unknown_find_name_index(*names, id);
        int house = (int)object->House;
        int sum = (*costs)[found];
        int cost = ((TechnoTypeClass *)object->Class_Of())->unknown_slot33(house);
        (*costs)[found] = sum + cost;
    }
    *best = 0;
    int pick = -1;
    if (name != 0) {
        for (int entry = 0; entry < count; entry++) {
            if (strcmp(name, (*names)[entry]) != 0) {
                int cost = (*costs)[entry];
                if (cost < limit && cost > *best) {
                    *best = cost;
                    pick = entry;
                }
            }
        }
    }
    if (name == 0 || *best == 0) {
        int most = 0;
        int which = -1;
        for (int slot = 0; slot < count; slot++) {
            if ((*costs)[slot] > most) {
                most = (*costs)[slot];
                which = slot;
            }
        }
        *best = most;
        pick = which;
    }
    char const *selected = name;
    if (pick != -1) {
        selected = (*names)[pick];
    }
    char *result = new char[100];
    if (selected != 0) {
        strcpy(result, selected);
    }
    delete names;
    delete costs;
    return result;
}
