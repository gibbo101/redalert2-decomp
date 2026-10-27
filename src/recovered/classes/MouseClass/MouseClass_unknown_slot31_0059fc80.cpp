// HRESULT MouseClass::unknown_slot31(IStream *stream) (0x0059FC80, slot 31)
// Saves the whole screen object: the layers' own saves, the theater, the
// raw object image (0x4F3C bytes), the map buffers, the saved vectors and
// the count cells.
#include "shared/mouse_class.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Save@SidebarClass@@UAEJPAUIStream@@@Z=006822a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Has_Cell@MapClass@@QAE_NABVCell@@@Z=005480b0
// @ref __imp__OleSaveToStream@8=0079a5e8

HRESULT MouseClass::unknown_slot31(IStream *stream)
{
    HRESULT result = SidebarClass::unknown_slot31(stream);
    if (result < 0) {
        return result;
    }
    int value = unknown_id_source_a3d290->Theater;
    result = stream->Write(&value, 4, 0);
    if (result < 0) {
        return result;
    }
    result = stream->Write(this, 0x4F3C, 0);
    if (result < 0) {
        return result;
    }
    result = stream->Write(unknown_64, unknown_68 * 4, 0);
    if (result < 0) {
        return result;
    }
    for (int buffer = 0; buffer < 12; buffer++) {
        result = stream->Write(unknown_18[buffer], unknown_48 * 2, 0);
        if (result < 0) {
            return result;
        }
    }
    int zones = ZoneConnections.Count();
    result = stream->Write(&zones, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int zone = 0; zone < zones; zone++) {
        ZoneConnectionClass connection = ZoneConnections[zone];
        result = stream->Write(&connection, sizeof(connection), 0);
        if (result < 0) {
            return result;
        }
    }
    int count = 0;
    Unknown_0055A550();
    for (CellClass *cell = Unknown_0055A490(); cell != 0; cell = Unknown_0055A490()) {
        Cell where = cell->MapCoords;
        if (Has_Cell(where)) {
            count++;
        }
    }
    result = stream->Write(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    Unknown_0055A550();
    for (CellClass *cell2 = Unknown_0055A490(); cell2 != 0; cell2 = Unknown_0055A490()) {
        Cell where2 = cell2->MapCoords;
        if (Has_Cell(where2)) {
            OleSaveToStream((IPersistStream *)cell2, stream);
            count--;
        }
    }
    if (count != 0) {
        return result;
    }
    count = unknown_1158.Count();
    result = stream->Write(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int entry = 0; entry < count; entry++) {
        result = stream->Write(&unknown_1158[entry], 4, 0);
        if (result < 0) {
            return result;
        }
    }
    count = unknown_d0.Count();
    result = stream->Write(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int entry2 = 0; entry2 < count; entry2++) {
        result = stream->Write(&unknown_d0[entry2], 4, 0);
        if (result < 0) {
            return result;
        }
    }
    return 0;
}
