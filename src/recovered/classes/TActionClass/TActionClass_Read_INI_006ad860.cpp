// void TActionClass::Read_INI() (0x006AD860)
// Reads "type,kind,value,a,b,c,d,last" from the current strtok position.
// The kind says what the value names: a number, a team type, a trigger type,
// a tag type, a text, an EVA voice, a sound or a theme (a short token is an
// index into the type list, a longer one a name); the last field is the
// waypoint, except for kinds 5 and 9.
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?Waypoint_From_String@@YIHPBD@Z=00724a70
#include "shared/object.hpp"
#include "shared/taction.hpp"
#include "shared/team_type.hpp"
#include "shared/trigger_type.hpp"
#include "shared/tag_type.hpp"
#include "shared/voc_class.hpp"
#include "shared/vox_class.hpp"
#include "shared/theme.hpp"
#include "shared/waypoint_path.hpp"

void TActionClass::Read_INI()
{
    Data.Value = 0;
    Type = atoi(strtok(0, ","));
    int kind = atoi(strtok(0, ","));
    char *token = strtok(0, ",");
    int value = atoi(token);
    switch (kind) {
        case 0:
        case 9:
            Data.Value = value;
            break;

        case 1:
        case 5:
            if (value == -1) {
                unknown_30 = 0;
            } else if (strlen(token) < 3) {
                unknown_30 = TeamTypes[value];
            } else {
                unknown_30 = TeamTypeClass::Find_Or_Make(token);
            }
            break;

        case 2:
            if (value == -1) {
                unknown_50 = 0;
            } else if (strlen(token) < 3) {
                unknown_50 = TriggerTypes[value];
            } else {
                unknown_50 = TriggerTypeClass::Find_Or_Make(token);
            }
            break;

        case 3:
            if (value == -1) {
                unknown_4c = 0;
            } else if (strlen(token) < 3) {
                unknown_4c = unknown_TagTypeClass_list_00abfea0[value];
            } else {
                unknown_4c = TagTypeClass::Find_Or_Make(token);
            }
            break;

        case 4:
            if (value == -1) {
                Text[0] = '\0';
            } else {
                Set_Text(token);
            }
            break;

        case 6:
            Data.Value = VoxClass::Find_Index(token);
            break;

        case 7:
            Data.Value = VocClass::From_Name(token);
            break;

        case 8:
            Data.Value = Theme.From_Name(token);
            break;
    }

    unknown_34 = atoi(strtok(0, ","));
    unknown_38 = atoi(strtok(0, ","));
    unknown_3c = atoi(strtok(0, ","));
    unknown_40 = atoi(strtok(0, ","));
    token = strtok(0, ",");
    if (token != 0) {
        if (kind == 5) {
            Data.Value = atoi(token);
        } else if (kind == 9) {
            unknown_48 = atoi(token);
        } else {
            unknown_44 = Waypoint_From_String(token);
        }
    }
}


