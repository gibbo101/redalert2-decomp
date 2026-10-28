// HRESULT __stdcall BuildingClass::Load(IStream *stream) (0x0044EF90, slot 5)
// Leaves the techno index, loads the techno, rebuilds itself in place,
// rejoins the index, fixes up pointers and reads the two infantry lists
// (a count, then the pointers).
#include "shared/building.hpp"
// @ref ??0BuildingClass@@QAE@ABVNoInitClass@@@Z=00438c20
// @ref ?Load@TechnoClass@@UAGJPAUIStream@@@Z=006d6850
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58
// @ref ?Search_For_Node@?$UnknownIndexClass@JPAVObjectClass@@@@QAEPBUNodeElement@1@ABJ@Z=0041b990
// @ref ?Increase_Table_Size@?$UnknownIndexClass@JPAVObjectClass@@@@QAE_NH@Z=0041b900

HRESULT __stdcall BuildingClass::Load(IStream *stream)
{
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
    HRESULT result = TechnoClass::Load(stream);
    if (SUCCEEDED(result)) {
        int count;
        new (this) BuildingClass(NoInitClass());
        unknown_object_index_abff58.Add_Index(Fetch_ID(), this);
        Swizzle_Pointer(Type);
        Swizzle_Pointer(unknown_41c);
        Swizzle_Pointer(unknown_438);
        Swizzle_Pointer(unknown_440);
        Swizzle_Pointer(unknown_444);
        Swizzle_Pointer(unknown_4d4);
        unknown_570.Init();
        unknown_584.Init();

        HRESULT read = stream->Read(&count, sizeof(count), 0);
        if (FAILED(read)) {
            return read;
        }
        for (int index = 0; index < count; index++) {
            InfantryClass *infantry;
            read = stream->Read(&infantry, sizeof(infantry), 0);
            if (FAILED(read)) {
                return read;
            }
            unknown_53c.Add(infantry);
        }
        for (index = 0; index < count; index++) {
            Swizzle_Pointer(unknown_53c[index]);
        }
        read = stream->Read(&count, sizeof(count), 0);
        if (FAILED(read)) {
            return read;
        }
        for (index = 0; index < count; index++) {
            InfantryClass *infantry;
            read = stream->Read(&infantry, sizeof(infantry), 0);
            if (FAILED(read)) {
                return read;
            }
            unknown_554.Add(infantry);
        }
        for (index = 0; index < count; index++) {
            Swizzle_Pointer(unknown_554[index]);
        }
        for (index = 0; index < 18; index++) {
            Swizzle_Pointer(unknown_454[index]);
        }
        for (index = 0; index < 3; index++) {
            Swizzle_Pointer(unknown_4c0[index]);
        }
        for (index = 0; index < 8; index++) {
            Swizzle_Pointer(unknown_49c[index]);
        }
        unknown_4e8 = 0;
    }
    return result;
}
