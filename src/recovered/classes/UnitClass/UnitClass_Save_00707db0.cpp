// HRESULT __stdcall UnitClass::Save(IStream *stream, BOOL clear_dirty) (0x00707DB0, slot 6)
// Releases the object at +0x5C4 first, then FootClass::Save.
#include "shared/unit.hpp"
// @ref ?unknown_4b25c0@UnknownUnit5C4@@QAEXXZ=004b25c0
// @ref ?Save@FootClass@@UAGJPAUIStream@@H@Z=004c9fe0

HRESULT __stdcall UnitClass::Save(IStream *stream, BOOL clear_dirty)
{
    if (unknown_5c4) {
        unknown_5c4->unknown_4b25c0();
        unknown_5c4 = 0;
    }
    return FootClass::Save(stream, clear_dirty);
}
