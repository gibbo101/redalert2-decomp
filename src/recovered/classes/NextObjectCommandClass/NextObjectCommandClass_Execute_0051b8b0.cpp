// void NextObjectCommandClass::Execute(int key) const -- 0x0051B8B0
// Leaves the screen modes, then selects the object after the first selected
// one (DisplayClass::Next_Object; the first selectable when none is selected)
// and centres the view on it.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049E3B0@DisplayClass@@QAEXXZ=0049e3b0
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60

void __cdecl Clear_Selected_Objects_00482bc0();

void NextObjectCommandClass::Execute(int key) const
{
    Map.Unknown_0049C980(0);
    Map.Unknown_0049C860(0, false);
    Map.Unknown_0049CA20(0);
    Map.Unknown_0049C7C0(0);
    ObjectClass *object = Map.Next_Object(unknown_objects_a40c60.Count() ? unknown_objects_a40c60[0] : 0);
    if (object != 0) {
        Clear_Selected_Objects_00482bc0();
        object->unknown_slot80();
        Map.Unknown_0049E3B0();
        Map.Flag_To_Redraw(true);
    }
}
