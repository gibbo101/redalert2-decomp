#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/techno_type.hpp"
class UnitTypeClass;
class AircraftTypeClass;
class BuildingTypeClass;
class InfantryTypeClass;
extern DynamicVectorClass<UnitTypeClass *> UnitTypes;
extern DynamicVectorClass<AircraftTypeClass *> AircraftTypes;
extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;
extern DynamicVectorClass<InfantryTypeClass *> InfantryTypes;
// Every listed concrete type has its ObjectTypeClass base at offset zero,
// as established by the actual shared class layouts; no concrete members are read.
// Lookup accepts either an object's kind or the corresponding type's kind.
ObjectTypeClass *__fastcall Unknown_00482C00(int kind,int index)
{
    switch (kind) {
    case 1: case 40: return (ObjectTypeClass *)UnitTypes[index];
    case 6: case 7: return (ObjectTypeClass *)BuildingTypes[index];
    case 15: case 16: return (ObjectTypeClass *)InfantryTypes[index];
    case 2: case 3: return (ObjectTypeClass *)AircraftTypes[index];
    }
    return 0;
}
