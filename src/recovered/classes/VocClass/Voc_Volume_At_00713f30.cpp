// float Voc_Volume_At(CoordStruct const &coord, int *pan, AudioEventType *type)
// (0x00713F30): the volume (0..1) of a sound of a type at a coordinate and its
// pan (0..0x4000), from the coordinate's pixel against the middle of the
// tactical area and the type's range (60 pixels a cell); 0 for a cell the
// type's 0x800 flag refuses and below 0.05 (hypothesis).
#include "shared/voc_class.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/tool_tip.hpp"
#include "shared/crt_memory.hpp"
// The cell 0x00713F30 never plays a 0x800-flagged sound in (0x00AD07C0; hypothesis).
extern Cell unknown_voc_cell_ad07c0;
// @ref ?unknown_voc_cell_ad07c0@@3VCell@@A=00ad07c0
// @ref ?Audio_Event_Type_Range@@YIHPAUAudioEventType@@@Z=00405110
// @ref ?Audio_Event_Type_Min_Volume@@YIMPAUAudioEventType@@@Z=00405120
// @ref ?Audio_Event_Type_Flags@@YIIPAUAudioEventType@@@Z=00405140
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref __real@8@3ffaccccccccccccd000=007a10f8
// @ref __real@4@400c8000000000000000=007ae9c8

float __fastcall Voc_Volume_At(CoordStruct const &coord, int *pan, AudioEventType *type)
{
    *pan = 0;
    float half_width = unknown_rect_839630.Width * 0.5f;
    float half_height = unknown_rect_839630.Height * 0.5f;
    float volume = 0;
    float width = half_width + half_width;
    float range = Audio_Event_Type_Range(type) * 60;
    unsigned int flags = Audio_Event_Type_Flags(type);
    if (flags & 0x800) {
        Cell cell = Cell(coord.X / 256, coord.Y / 256);
        if (cell == unknown_voc_cell_ad07c0) {
            return 0;
        }
        if ((Map[cell].unknown_12c & 0x18) == 0) {
            return 0;
        }
    }
    Point2D pixel;
    unknown_tactical_83996c->Unknown_006A29D0(coord, pixel);
    float dx = pixel.X - half_width;
    float x = abs((int)dx);
    float y = abs((int)(pixel.Y - half_height));
    if (!(flags & 0x40)) {
        x -= half_width;
        y -= half_height;
        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
    }
    y = y + y;
    if (x < range && y < range && range > 0) {
        float distance = x > y ? x : y;
        volume = (range - distance) / range;
    }
    if (flags & 0x10) {
        if (Audio_Event_Type_Min_Volume(type) > volume) {
            volume = Audio_Event_Type_Min_Volume(type);
        }
    }
    if (volume < 0.05) {
        return 0;
    }
    if (dx < -width) {
        dx = -width;
    } else if (dx > width) {
        dx = width;
    }
    *pan = (int)(dx * 8192.0f / width + 8192.0f);
    return volume;
}
