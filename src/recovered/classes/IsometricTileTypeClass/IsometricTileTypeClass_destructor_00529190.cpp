// IsometricTileTypeClass::~IsometricTileTypeClass() (0x00529190)
// Detaches from everything, deletes the owned object, leaves IsoTileTypes and the object list, and frees the colour tables.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/isometric_tile.hpp"
#include "shared/object_lists.hpp"
#include "shared/crt_memory.hpp"
void __fastcall Detach_This_From_All(AbstractClass *object, bool all);
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60
// @ref ??_7?$VectorClass@PAG@@6B@=007a526c
// @ref ??_E?$VectorClass@PAG@@UAEPAXI@Z=0052ec50
// @ref ??_G?$VectorClass@PAG@@UAEPAXI@Z=0052ec50
// @ref ?Clear@?$VectorClass@PAG@@UAEXXZ=0052e880

IsometricTileTypeClass::~IsometricTileTypeClass()
{
    Detach_This_From_All(this, true);
    if (unknown_28c != 0) {
        AbstractClass *owned = unknown_28c;
        unknown_28c = 0;
        delete owned;
    }
    IsoTileTypes.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
    for (int i = unknown_274.Count() - 1; i >= 0; i--) {
        if (unknown_274[i] != 0) {
            delete unknown_274[i];
        }
        unknown_274.Delete(i);
    }
}
