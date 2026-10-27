// int __fastcall Unknown_006525F0() (0x006525F0): the sum of the unique IDs of the
// INI at 0x008396D0, of every session INI (0x005B6F80 count, 0x005B6FE0 lookup,
// UnknownSessionA3D29C 0x005B7840) and of CoopCamp.ini (Coop_Camp_Unique_ID,
// expanded inline). Used for multiplayer synchronisation (hypothesis).
// __fastcall as Coop_Camp_Unique_ID: the inlined CCFileClass/Load setup is
// scheduled register-first only in a fastcall caller.
// @ref ?Unknown_005B6F80@@YAHXZ=005b6f80
// @ref ?Unknown_005B6FE0@@YIPAVUnknownSessionA3D29C@@H@Z=005b6fe0
// @ref ?unknown_ini_005b7840@UnknownSessionA3D29C@@QAEPAVCCINIClass@@XZ=005b7840
// @ref ?unknown_ini_8396d0@@3PAVCCINIClass@@A=008396d0
#include "shared/ccini_class.hpp"
#include "shared/radar.hpp"

extern CCINIClass *unknown_ini_8396d0;     // 0x008396D0
int Unknown_005B6F80();
UnknownSessionA3D29C *__fastcall Unknown_005B6FE0(int index);
int __fastcall Coop_Camp_Unique_ID();

int __fastcall Unknown_006525F0()
{
    int id = unknown_ini_8396d0->Get_Unique_ID();
    int count = Unknown_005B6F80();
    for (int index = 1; index <= count; index++) {
        UnknownSessionA3D29C *session = Unknown_005B6FE0(index);
        if (session != 0) {
            id += session->unknown_ini_005b7840()->Get_Unique_ID();
        }
    }
    return id + Coop_Camp_Unique_ID();
}
