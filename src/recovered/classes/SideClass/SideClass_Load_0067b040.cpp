// HRESULT __stdcall SideClass::Load(IStream *stream) (0x0067B040)
// Restores the side in place and rebuilds its house index list from the
// saved count and entries.
#include "shared/side.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120

// Rebuilds a list in place from its saved count and elements.
template <class T>
static inline void Load_List(IStream *stream, TypeList<T> &list)
{
    new (&list) TypeList<T>;
    int count;
    stream->Read(&count, sizeof(count), 0);
    for (int index = 0; index < count; index++) {
        T value;
        stream->Read(&value, sizeof(value), 0);
        list.Add(value);
    }
}

HRESULT __stdcall SideClass::Load(IStream *stream)
{
    HRESULT result = AbstractTypeClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) SideClass(NoInitClass());
    Load_List(stream, Houses);
    return S_OK;
}
