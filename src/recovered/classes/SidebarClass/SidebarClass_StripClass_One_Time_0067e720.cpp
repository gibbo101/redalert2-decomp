// void SidebarClass::StripClass::One_Time(int id) (0x0067E720)
// Loads the darkening overlay shape.
#include "shared/sidebar.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/cc_file_class.hpp"
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?unknown_shape_ab9480@SidebarClass@@2PBXB=00ab9480
// @ref ??_C@_0L@FJLO@DARKEN?4SHP?$AA@=007f3dbc

void SidebarClass::StripClass::One_Time(int id)
{
    SidebarClass::unknown_shape_ab9480 = MixFileClass::Retrieve("DARKEN.SHP");
}
