// void CombatantSelectCommandClass::Execute(int key) const -- 0x0051BA90
// Runs the UICmnds.cpp handler with whether the 0x100 key bit is clear.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/command.hpp"
#include "shared/mouse_class.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
// @ref ?Unknown_006F6D00@@YIX_N@Z=006f6d00

void __fastcall Unknown_006F6D00(bool arg);

void CombatantSelectCommandClass::Execute(int key) const
{
    Unknown_006F6D00(!(key & 0x100));
}
