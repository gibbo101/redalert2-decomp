#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/object.hpp"
// Existing shared/display.hpp receiver type, incomplete here: no new owner class.
class Unknown84E8D0;
extern Unknown84E8D0 unknown_object_84e8d0;
// Observed one-DWORD ECX argument, no stack arguments; original source form unknown.
void __fastcall Unknown_006f6780(unsigned int value);
// Observed one-pointer ECX receiver, no stack arguments; member/free source form unknown.
void __fastcall Unknown_0042e830(Unknown84E8D0 *receiver);
// @ref ?unknown_objects_a40c60@@=00a40c60
// @ref ?unknown_object_84e8d0@@=0084e8d0
// @ref ?Unknown_006f6780@@=006f6780
// @ref ?Unknown_0042e830@@=0042e830
void __cdecl Clear_Selected_Objects_00482bc0()
{
    while (unknown_objects_a40c60.Count()!=0)
        unknown_objects_a40c60[0]->unknown_slot81();
    Unknown_006f6780(0);
    Unknown_0042e830(&unknown_object_84e8d0);
}
