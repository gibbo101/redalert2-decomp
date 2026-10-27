// HRESULT __stdcall BulletClass::Save(IStream *stream, BOOL clear_dirty) (0x004638F0)
#include "shared/bullet.hpp"

HRESULT __stdcall BulletClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
