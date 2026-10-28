// static TerrainTypeClass *__fastcall TerrainTypeClass::Find_Or_Make(char const *name) (0x006E5A20)
// The type with this ID, else a new one; null for "<none>" and "none".
#include "shared/terrain_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0TerrainTypeClass@@QAE@PBD@Z=006e5260

TerrainTypeClass *__fastcall TerrainTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < TerrainTypes.Count(); index++) {
        if (_stricmp(TerrainTypes[index]->ID, name) == 0) {
            return TerrainTypes[index];
        }
    }
    return new TerrainTypeClass(name);
}
