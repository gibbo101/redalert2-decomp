// void __stdcall AbstractClass::Create_ID() (0x0040FFD0)
// IRTTITypeInfo: takes a new unique ID from the ID source (0 without one).
#include "shared/abstract.hpp"
// @ref ?Next_ID@UnknownIDSource@@QAEJXZ=00663170
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

void __stdcall AbstractClass::Create_ID()
{
    UniqueID = unknown_id_source_a3d290 == 0 ? 0 : unknown_id_source_a3d290->Next_ID();
}
