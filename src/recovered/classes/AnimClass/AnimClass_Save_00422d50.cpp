// HRESULT __stdcall AnimClass::Save(IStream *stream, BOOL clear_dirty) (0x00422D50)
// Records unknown_bc as an index into the 0x00AB6EF8 list (-1 if absent),
// then saves through AbstractClass::Save.
#include "shared/anim.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0
// @ref ?unknown_list_ab6ef8@@3V?$DynamicVectorClass@PAUUnknownAB6EF8Entry@@@@A=00ab6ef8

HRESULT __stdcall AnimClass::Save(IStream *stream, BOOL clear_dirty)
{
    if (unknown_bc != 0) {
        for (int index = unknown_list_ab6ef8.Count() - 1; index >= 0; index--) {
            if (unknown_bc == unknown_list_ab6ef8[index]->unknown_30c) {
                unknown_c0 = index;
                goto save;
            }
        }
    }
    unknown_c0 = -1;
save:
    return AbstractClass::Save(stream, clear_dirty);
}
