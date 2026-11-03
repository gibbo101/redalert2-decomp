// Full Building 0x00446820: 246-byte body, 10-byte original padding.
// Complete private compiler candidate; current canonical constructor and timer.
// Lead-approved private field proposal: original DWORD store at laser+0x18.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/rgb_class.hpp"
#include "shared/laser_draw.hpp" // canonical constructor declaration

// @ref ??0LaserDrawClass@@QAE@UCoordStruct@@0H_NVRGBClass@@22H11MM@Z=00533110
typedef char LaserDraw_size_must_be_0x58[(sizeof(LaserDrawClass)==0x58)?1:-1];
typedef char LaserDraw_field18_offset[((unsigned int)&((LaserDrawClass*)0)->unknown_18==0x18)?1:-1];
typedef char LaserDraw_housecolor_offset[((unsigned int)&((LaserDrawClass*)0)->IsHouseColor==0x1C)?1:-1];
void BuildingClass::unknown_446820(CoordStruct destination)
{
    RGBClass black;
    LaserDrawClass *laser = new LaserDrawClass(
        unknown_slot43(0), destination, 0, true,
        House->unknown_55ec, black, black,
        Rules->PrismSupportDuration, false, true, 1.0f, 0.0f);
    if (laser) {
        laser->IsHouseColor = true;
        laser->unknown_18 = 3;
    }
    int delay = Rules->PrismSupportDelay;
    unknown_244 = CDTimerClass<FrameTimerClass>(delay);
    unknown_534 = 0;
}
