// VectorCursor<MSSfxEntry*,DynamicVectorClass<MSSfxEntry*> >00730340.
// Concrete cursor identity comes from vptr007AF37C and the accepted Selection sound walks.
#include "shared/wdt_selection.hpp"
template<>
VectorCursor<MSSfxEntry *, DynamicVectorClass<MSSfxEntry *> >::VectorCursor(
    DynamicVectorClass<MSSfxEntry *> &vector, unsigned index)
    : Vector(&vector), Index(index)
{
}
