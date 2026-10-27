// Whether an object is alive and may be dealt with: it counts, has strength, and either the editor flag is set or it is not 0x76.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_a40774@@3HA=00a40774

bool __fastcall TeamClass::unknown_func_6bdd80(ObjectClass *object)
{
    if (object != 0 && object->unknown_7d && object->Strength != 0 && (unknown_a40774 != 0 || !object->unknown_76)) {
        return true;
    }
    return false;
}
