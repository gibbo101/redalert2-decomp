// HRESULT __stdcall BuildingTypeClass::Load(IStream *stream) (0x0045DD90)
// Frees the loaded images, loads the techno part, rebuilds the object in
// place, reads the docking offsets, then restores the foundation lists,
// pointers and images for the scenario's theater.
#include "shared/building_type.hpp"
// @ref ??0BuildingTypeClass@@QAE@ABVNoInitClass@@@Z=00458160
// @ref ?unknown_foundation_cells_84ede8@@3QAY0BO@$$CBVCell@@A=0084ede8
// @ref ?unknown_foundation_outside_84f848@@3QAY0BO@$$CBVCell@@A=0084f848
// @ref ?unknown_func_458ea0@BuildingTypeClass@@QAEXH@Z=00458ea0
// @ref ?unknown_func_459640@BuildingTypeClass@@QAEXXZ=00459640

HRESULT __stdcall BuildingTypeClass::Load(IStream *stream)
{
    Free_Buildup();
    Free_unknown_11cc();
    Free_unknown_11a0();
    Free_unknown_11a8();
    Free_unknown_11b0();
    Free_unknown_11b8();
    HRESULT result = TechnoTypeClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) BuildingTypeClass(NoInitClass());
        int count;
        result = stream->Read(&count, sizeof(count), 0);
        if (FAILED(result)) {
            return result;
        }
        new (&DockingOffsets) VectorClass<TPoint3D<int> >();
        DockingOffsets.Resize(count);
        for (int index = 0; index < count; index++) {
            TPoint3D<int> point(0, 0, 0);
            result = stream->Read(&point, sizeof(point), 0);
            if (FAILED(result)) {
                return result;
            }
            DockingOffsets[index] = point;
        }
        unknown_func_459640();
        unknown_func_5d7630();
        unknown_bf0 = 0;
        FoundationData = unknown_foundation_cells_84ede8[Foundation];
        FoundationOutside = unknown_foundation_outside_84f848[Foundation];
        SwizzleManager.Swizzle((void **)&ToOverlay);
        SwizzleManager.Swizzle((void **)&FreeUnit);
        unknown_func_459640();
        BuildupData = 0;
        BuildupDataAllocated = false;
        unknown_11cc = 0;
        unknown_11d0 = false;
        unknown_11a0 = 0;
        unknown_11a4 = false;
        unknown_11a8 = 0;
        unknown_11ac = false;
        unknown_11b0 = 0;
        unknown_11b4 = false;
        unknown_11b8 = 0;
        unknown_11bc = false;
        unknown_func_458ea0(unknown_id_source_a3d290->Theater);
        return S_OK;
    }
    return result;
}
