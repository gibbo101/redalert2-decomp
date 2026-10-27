// void TActionClass::Build_INI_Entry(char *buffer) const (0x006AD640)
// @ref ??_C@_02HNAB@?91?$AA@=007f6bcc
// @ref ??_C@_0BI@FJEA@?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?$AA@=007f6bb4
// @ref ??_C@_0BI@FMLC@?$CFd?0?$CFd?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFs?$AA@=007f6b84
// @ref ??_C@_0BI@KACH@?$CFd?0?$CFd?0?$CFs?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?$AA@=007f6b9c
// @ref ??_C@_0BI@KFNF@?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFs?$AA@=007f6b6c
// @ref ?Name@ThemeClass@@QBEPBDH@Z=006e8570
// @ref ?Name_From@VoxClass@@SIPBDH@Z=007158a0
// @ref ?Value_Kind@TActionClass@@SIHH@Z=006b2ab0
// Appends "type,kind,value,a,b,c,d,last": the value is the number, or the
// name of the team/trigger/tag type, text, voice, sound or theme its type
// takes; the last field is the waypoint (kinds 5 and 9 write a number there).
// @ref ?Voc_Name@@YIPBDH@Z=00714a00
// @ref ?Waypoint_As_String@@YIPBDH@Z=007249f0
// @ref ??_EWaypointClass@@QAEPAXI@Z=0041b890
#include "shared/object.hpp"
#include "shared/taction.hpp"
#include "shared/team_type.hpp"
#include "shared/trigger_type.hpp"
#include "shared/tag_type.hpp"
#include "shared/voc_class.hpp"
#include "shared/vox_class.hpp"
#include "shared/theme.hpp"
#include "shared/waypoint_path.hpp"

void TActionClass::Build_INI_Entry(char *buffer) const
{
    int value_kind = Value_Kind(Type);
    int value = Data;
    int number = 0;
    int last = 0;
    int kind = 0;
    char const *name = 0;
    if (value_kind == 0x2B) {
        kind = 9;
        number = value;
        last = unknown_48;
    }
    if (unknown_30 != 0 && value_kind == 0x28) {
        kind = 5;
        value = ((TeamTypeClass *)unknown_30)->ArrayIndex;
        name = unknown_30->ID;
    }
    if (unknown_30 != 0 && (value_kind == 0x0C || value_kind == 0x22)) {
        value = ((TeamTypeClass *)unknown_30)->ArrayIndex;
        kind = 1;
        name = unknown_30->ID;
    } else if (unknown_50 != 0 && value_kind == 0x0B) {
        value = ((TriggerTypeClass *)unknown_50)->ArrayIndex;
        kind = 2;
        name = ((TriggerTypeClass *)unknown_50)->ID;
    } else if (unknown_4c != 0 && value_kind == 0x1A) {
        value = ((TagTypeClass *)unknown_4c)->ArrayIndex;
        kind = 3;
        name = ((TagTypeClass *)unknown_4c)->ID;
    } else if (value_kind == 0x27) {
        kind = 4;
        name = Get_Text();
        if (name == 0) {
            name = "-1";
        }
    } else if (value_kind == 4) {
        kind = 6;
        name = VoxClass::Name_From(Data);
    } else if (value_kind == 3 || value_kind == 0x26) {
        kind = 7;
        name = Voc_Name(Data);
    } else if (value_kind == 1) {
        kind = 8;
        name = Theme.Name(Data);
    }

    buffer += strlen(buffer);
    if (kind == 9) {
        sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%d", Type, kind, number, unknown_34, unknown_38, unknown_3c, unknown_40, last);
    } else if (kind == 5) {
        sprintf(buffer, "%d,%d,%s,%d,%d,%d,%d,%d", Type, kind, name, unknown_34, unknown_38, unknown_3c, unknown_40, Data);
    } else if (kind != 0) {
        sprintf(buffer, "%d,%d,%s,%d,%d,%d,%d,%s", Type, kind, name, unknown_34, unknown_38, unknown_3c, unknown_40,
                Waypoint_As_String(unknown_44));
    } else {
        sprintf(buffer, "%d,%d,%d,%d,%d,%d,%d,%s", Type, 0, value, unknown_34, unknown_38, unknown_3c, unknown_40,
                Waypoint_As_String(unknown_44));
    }
}
