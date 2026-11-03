#include "shared/fly_locomotion.hpp"
#include "shared/aircraft.hpp"
// All native Fly.cpp held-release calls stay out of line; Attach releases its pointer directly.
#pragma auto_inline(off)
template<>
void UnknownComPtr<IFlyControl, &unknown_uuid_7d80a8>::Release_Held()
{
    if (Pointer) Pointer->Release();
}

#pragma auto_inline(on)
