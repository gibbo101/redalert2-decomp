// Create and replace one attached building animation, preserving its stage.
#include "shared/building.hpp"
#include "shared/anim.hpp"
#include "shared/tactical.hpp"
// @ref ?From_Name@AnimTypeClass@@=00425640
// @ref ?Unknown_006A2BF0@Tactical@@=006a2bf0
// @ref ??0AnimClass@@=00420110
// @ref ?unknown_func_422c10@AnimClass@@=00422c10
// @ref ?unknown_6d86f0@TechnoClass@@=006d86f0
inline int Fetch_Building_Animation_Stage_0044ca60(AnimClass const &animation)
{
    return animation.Stage;
}
inline void Set_Building_Animation_Stage_0044ca60(AnimClass &animation, int stage)
{
    animation.Stage=stage;
}
inline void Hide_Building_Animation_0044ca60(AnimClass &animation)
{
    animation.unknown_17d=true;
}
void BuildingClass::unknown_44ca60(char const *name, int index, bool damaged, bool garrisoned, int delay)
{
    unknown_44d070(damaged);
    int type = AnimTypeClass::From_Name(name);
    if (type != -1) {
        CoordStruct coord(unknown_slot42() + unknown_tactical_83996c->Unknown_006A2BF0(Type->Anims[index].Offset));
        AnimClass *animation = new AnimClass(AnimTypes[type], coord, delay, 1, 0x1600, 0);
        animation->ZAdjust = Type->Anims[index].ZAdjust;
        animation->YSortAdjust = Type->Anims[index].YSort;
        animation->unknown_100 = true;
        if (unknown_5b7) animation->unknown_179 = true;
        unknown_44d2d0(unknown_5bd);
        if (unknown_454[index]) {
            Set_Building_Animation_Stage_0044ca60(*animation,Fetch_Building_Animation_Stage_0044ca60(*static_cast<AnimClass *>(unknown_454[index])));
            AbstractClass *previous = unknown_454[index];
            unknown_454[index] = 0;
            delete previous;
        }
        unknown_454[index] = animation;
        if (!unknown_5ba && Type->Anims[index].Powered) animation->unknown_func_422c10();
        if (animation->Class->ShouldUseCellDrawer) {
            animation->unknown_bc = unknown_slot115();
            int height = reinterpret_cast<UnknownBuildingSlot105 *>(unknown_slot105())->unknown_10a;
            int brightness = unknown_slot254(height);
            if (unknown_slot203()) brightness = unknown_6d86f0(brightness);
            animation->unknown_e4 = brightness;
        }
        if (index == 9 && Type->BarrelAnimIsVoxel) Hide_Building_Animation_0044ca60(*animation);
        if (unknown_slot111()) animation->unknown_102 = true;
    }
}
