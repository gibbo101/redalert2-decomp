// 0070FDF0: remove the surrounding vein overlay, buffers and tracking entries.
#include "shared/veinhole.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tactical.hpp"
#include "shared/object_index.hpp"
extern Rect unknown_rect_839630;
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_cell_index_428a90@@YIHABVCell@@@Z=00428a90
// @ref ?unknown_veinhole_buffer_ad07a0@@3PAEA=00ad07a0
// @ref ?Clear@UnknownVeinHeap@@QAEXXZ=00712a10
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ??1ObjectClass@@UAE@XZ=005d2530
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

inline RectPoint2D Rect::Top_Left() const { return RectPoint2D(X, Y); }
inline Rect Rect::operator-(RectPoint2D const &point) const { return Rect(Top_Left() - point, Width, Height); }

// Existing Clear_Growth member; the original expands this body in the dtor.
inline void VeinholeMonsterClass::unknown_func_711c90()
{
    if (unknown_9c != 0) {
        unknown_9c->Clear();
        delete unknown_9c;
        unknown_9c = 0;
    }
    if (unknown_a0 != 0) {
        delete[] unknown_a0;
        unknown_a0 = 0;
    }
    if (unknown_b0 != 0) {
        delete[] unknown_b0;
        unknown_b0 = 0;
    }
    unknown_98 = 0;
}

// Existing independently emitted lifecycle rows 00711C70 and 007114F0.
inline void __cdecl VeinholeMonsterClass::Clear_Global_Data()
{
    if (unknown_veinhole_buffer_ad07a0 != 0) {
        delete[] unknown_veinhole_buffer_ad07a0;
        unknown_veinhole_buffer_ad07a0 = 0;
    }
}
inline void __cdecl VeinholeMonsterClass::Deinit_Vein_Growth_System()
{
    for (int index = Array.Count() - 1; index >= 0; index--) {
        Array[index]->unknown_func_711c90();
    }
    Clear_Global_Data();
}

VeinholeMonsterClass::~VeinholeMonsterClass()
{
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            ::Cell cell(Cell + ::Cell(x, y));
            int cell_id = unknown_cell_index_428a90(cell);
            if (cell_id >= 0 && cell_id < unknown_cells_428ac0()) {
                unknown_veinhole_buffer_ad07a0[cell_id] = false;
                unknown_b0[cell_id] = false;
            }
            CellClass *map_cell = &Map[cell];
            if (map_cell->OverlayIndex == 0x7e || (map_cell->OverlayIndex != -1 && OverlayTypes[map_cell->OverlayIndex]->IsVeins)) {
                Map.Unknown_00631570(map_cell->MapCoords);
                RectPoint2D origin(unknown_rect_839630.Top_Left());
                unknown_tactical_83996c->Register_Dirty_Area(Union(map_cell->unknown_474eb0(), map_cell->unknown_475100()) - origin, false);
                map_cell->OverlayIndex = -1;
                map_cell->OverlayData = 0;
            }
        }
    }
    unknown_76 = true;
    unknown_74 = false;
    if (Strength > 0) Unknown_006ECB90(this, true);
    unknown_func_711c90();
    Array.Delete(this);
    unknown_object_index_abff58.Remove_Index(Fetch_ID());
}
