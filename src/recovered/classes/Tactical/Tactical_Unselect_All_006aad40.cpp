// void Tactical::Unknown_006AAD40() (0x006AAD40): unselects every selected object
// (slot 81 of the first until none is left), then clears the pending command
// (0x006F6780 with 0; hypothesis).
#include "shared/tactical.hpp"
#include "shared/vector_class.hpp"
#include "shared/object.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Unknown_006f6780@@YIXI@Z=006f6780

void __fastcall Unknown_006f6780(unsigned int value);

void Tactical::Unknown_006AAD40()
{
    while (unknown_objects_a40c60.Count()) {
        unknown_objects_a40c60[0]->unknown_slot81();
    }
    Unknown_006f6780(0);
}
