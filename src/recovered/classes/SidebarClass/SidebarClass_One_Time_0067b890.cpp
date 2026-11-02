// void SidebarClass::One_Time() (0x0067B890, slot 5)
// After the power bar's, retrieves "DARKEN.SHP" once per strip.
#include "shared/sidebar.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?One_Time@PowerClass@@UAEXXZ=0061c550
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?unknown_shape_ab9480@SidebarClass@@2PBXB=00ab9480

void SidebarClass::One_Time()
{
    PowerClass::One_Time();
    for (int index = 0; index < 4; index++) {
        unknown_shape_ab9480 = MixFileClass::Retrieve("DARKEN.SHP");
    }
}
// @ref ??_C@_0L@FJLO@DARKEN?4SHP?$AA@=007f3dbc
