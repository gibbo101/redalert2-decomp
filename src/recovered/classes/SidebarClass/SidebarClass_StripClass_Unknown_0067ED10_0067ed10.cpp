// void SidebarClass::StripClass::Unknown_0067ED10(int type, int id) (0x0067ED10)
// Inserts a buildable into the strip in sort order (0x0067EA20): the later
// entries move down one place, the new entry gets its type and id (and the
// kind of a type 7 buildable) and has its factory, build progress and
// stage cleared.
#include "shared/sidebar.hpp"
// @ref ?Unknown_0067EA20@StripClass@SidebarClass@@QAE_NHHHH@Z=0067ea20
// @ref ?Unknown_004EB550@@YIHHH@Z=004eb550

void SidebarClass::StripClass::Unknown_0067ED10(int type, int id)
{
    BuildableCount++;
    for (int index = 0; index < BuildableCount; index++) {
        int other_type = Buildables[index].unknown_04;
        int other_id = Buildables[index].unknown_00;
        if (Unknown_0067EA20(type, id, other_type, other_id)) {
            for (int move = BuildableCount - 1; move > index; move--) {
                Buildables[move] = Buildables[move - 1];
            }
            Buildables[index].unknown_04 = type;
            Buildables[index].unknown_00 = id;
            if (type == 7) {
                Buildables[index].unknown_08 = Unknown_004EB550(type, id);
            }
            Buildables[index].Factory = 0;
            Buildables[index].unknown_10 = 0;
            Buildables[index].Stage.Value = 0;
            Buildables[index].Stage.Set_Rate(0);
            Buildables[index].unknown_2c = 0;
            return;
        }
    }
}
