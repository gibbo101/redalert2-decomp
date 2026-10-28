// HRESULT __stdcall FoggedObjectClass::Load(IStream *stream) (0x004C1C80)
// Loads the base object, rebuilds the object in place, then reads the draw record
// count and records and lists the object in Index under its cell.
#include "shared/fogged_object.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??0?$VectorClass@UDrawRecord@FoggedObjectClass@@@@QAE@IPBUDrawRecord@FoggedObjectClass@@@Z=004c2520
// @ref ??_7FoggedObjectClass@@6BIPersistStream@@@=007a1148
// @ref ??_7FoggedObjectClass@@6BIRTTITypeInfo@@@=007a112c
// @ref ??_7FoggedObjectClass@@6BINoticeSink@@@=007a1124
// @ref ??_7FoggedObjectClass@@6BINoticeSource@@@=007a111c
// @ref ??_7?$DynamicVectorClass@UDrawRecord@FoggedObjectClass@@@@6B@=007a11b0
// @ref ?Index@FoggedObjectClass@@=00865e40
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868

HRESULT __stdcall FoggedObjectClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (result >= 0) {
        new (this) FoggedObjectClass(NoInitClass());
        Swizzle_Pointer(unknown_28);
        int count = 0;
        result = stream->Read(&count, sizeof(count), 0);
        if (result < 0) {
            return result;
        }
        for (int index = 0; index < count; index++) {
            DrawRecord record;
            result = stream->Read(&record, sizeof(record), 0);
            if (result < 0) {
                return result;
            }
            DrawRecords.Add(record);
            Swizzle_Pointer(DrawRecords[DrawRecords.Count() - 1].Type);
        }
        Cell cell = unknown_slot24();
        Index.Add_Index(unknown_index_key(cell, unknown_30), this);
    }
    return result;
}
