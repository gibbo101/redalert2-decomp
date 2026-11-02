// int RadioClass::unknown_slot95(RadioClass *radio, int message, long &param) (0x00636900, slot 95)
// Receives a radio message: remembers the last three message kinds in
// Old; message 3 hangs up a contact and message 2 accepts one (0xA
// when the other house is no ally or no link is free); anything else is
// ObjectClass's.
#include "shared/radio.hpp"
#include "shared/techno.hpp"
// @ref ?unknown_slot95@ObjectClass@@UAEHPAVRadioClass@@HAAJ@Z=005d3cb0
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580

int RadioClass::unknown_slot95(RadioClass *radio, int message, long &param)
{
    if (message != Old[0]) {
        Old[2] = Old[1];
        Old[1] = Old[0];
        Old[0] = message;
    }
    if (message == 3) {
        for (int index = 0; index < RadioLinks.Length(); index++) {
            if (radio == RadioLinks[index]) {
                MissionClass::unknown_slot95(radio, 3, param);
                RadioLinks[index] = 0;
                return 1;
            }
        }
    } else if (message == 2 && Strength != 0) {
        if (!((TechnoClass *)radio)->House->Is_Ally((TechnoClass *)this)) {
            return 0xA;
        }
        if (this != 0 && AbstractFlags.IsTechno && !((TechnoClass *)this)->House->Is_Ally((TechnoClass *)radio)) {
            return 0xA;
        }
        if (radio != 0 && Unknown_00636E70((TechnoClass *)radio) != -1) {
            return 1;
        }
        for (int index = 0; index < RadioLinks.Length(); index++) {
            if (RadioLinks[index] == 0) {
                RadioLinks[index] = (TechnoClass *)radio;
                return 1;
            }
        }
        return 0xA;
    }
    return MissionClass::unknown_slot95(radio, message, param);
}
