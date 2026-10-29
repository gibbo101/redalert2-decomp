// void VeterancyNavCommandClass::Execute(int key) const -- 0x0051BC90
// Runs the UICmnds.cpp handler with whether the 0x100 key bit is clear.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
// @ref ?Unknown_006F7EC0@@YIX_N@Z=006f7ec0

void __fastcall Unknown_006F7EC0(bool arg);

void VeterancyNavCommandClass::Execute(int key) const
{
    Unknown_006F7EC0(!(key & 0x100));
}
