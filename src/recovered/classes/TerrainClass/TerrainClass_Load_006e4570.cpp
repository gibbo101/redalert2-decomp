// HRESULT __stdcall TerrainClass::Load(IStream *stream) (0x006E4570)
// Leaves the object index under the old ID, restores the object in place,
// rejoins the index under the loaded ID and swizzles the type.
#include "shared/terrain.hpp"
#include "shared/terrain_object_index.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Increase_Table_Size@?$IndexClass@JPAVObjectClass@@@@QAE_NH@Z=0041b900

HRESULT __stdcall TerrainClass::Load(IStream *stream)
{
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    HRESULT result = ObjectClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) TerrainClass(NoInitClass());
    Add_Object_Index(Fetch_ID(), this);
    Swizzle_Pointer(Class);
    return result;
}
