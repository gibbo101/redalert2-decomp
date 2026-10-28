// void Tactical::Unknown_006AABC0(Rect const *rect, void (__fastcall *callback)(ObjectClass *))
// (0x006AABC0): every listed object (the table at 0x00ABE5F8) whose pixel lies
// in rect: its type ID to 0x006F71E0 while the 0x006F76B0 flag is set, else the
// callback, else the default selection test that clears 0x007D88D6 (as
// 0x0049C3F0 does). 0x007D88D6 is set before and after (hypothesis).
#include "shared/tactical.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno.hpp"
// @ref ?unknown_tactical_pixels_abe5f8@@3PAUTacticalObjectPixel@@A=00abe5f8
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6
// @ref ?Unknown_006F76B0@@YA_NXZ=006f76b0
// @ref ?Unknown_006F71E0@@YIXPBD@Z=006f71e0

void Tactical::Unknown_006AABC0(Rect const *rect, void (__fastcall *callback)(ObjectClass *object))
{
    unknown_sound_enabled_7d88d6 = true;
    if (rect->Is_Valid()) {
        for (int index = 0; index < unknown_db0; index++) {
            TacticalObjectPixel &entry = unknown_tactical_pixels_abe5f8[index];
            if (entry.Object != 0 && entry.Object->unknown_7d) {
                ObjectClass *object = entry.Object;
                Point2D view = unknown_b0;
                Point2D point(entry.Pixel.X - view.X, entry.Pixel.Y - view.Y);
                if (rect->Is_Point_Within(point)) {
                    if (Unknown_006F76B0()) {
                        Unknown_006F71E0(object->Class_Of()->ID);
                    } else if (callback == 0) {
                        bool undeploys = false;
                        if (object->Kind_Of() == 6) {
                            BuildingTypeClass *type = ((BuildingClass *)object)->Type;
                            if (type->UndeploysInto != 0 && !type->ConstructionYard) {
                                undeploys = true;
                            }
                        }
                        HouseClass *house = object->Owning_House();
                        if (house != 0 && house->Unknown_004F52B0() && object->unknown_slot76()
                            && (object->Kind_Of() != 6 || undeploys) && object->unknown_slot80()) {
                            unknown_sound_enabled_7d88d6 = false;
                        }
                    } else {
                        callback(object);
                    }
                }
            }
        }
    }
    unknown_sound_enabled_7d88d6 = true;
}
