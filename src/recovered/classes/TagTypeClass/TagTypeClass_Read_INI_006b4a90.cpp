// bool TagTypeClass::Read_INI(CCINIClass &ini) (0x006B4A90)
// The [Tags] entry "persistence,name,trigger": the persistence, the
// display name and the first trigger type (made when missing).
#include "shared/object.hpp"
#include "shared/trigger_type.hpp"
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?Find_Or_Make@TriggerTypeClass@@SIPAV1@PBD@Z=006eecc0
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd

extern "C" char *__cdecl strtok(char *string, char const *delimiters);

bool TagTypeClass::Read_INI(CCINIClass &ini)
{
    char buffer[128];
    if (ini.Get_String(unknown_tags_section_7ac770, ID, unknown_string_83c55c, buffer, sizeof(buffer))) {
        strtok(buffer, ",");
        Persistence = atoi(buffer);
        Name = FixedString<49>(strtok(0, ","));
        Triggers = TriggerTypeClass::Find_Or_Make(strtok(0, ","));
        return true;
    }
    return false;
}
