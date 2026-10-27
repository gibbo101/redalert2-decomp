// Disguise-when-still AI and nearby hostile-infantry suppression.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/terrain_type.hpp"
static inline TypeList<TerrainTypeClass *> &Unit_Default_Mirage_Disguises()
{
    return Rules->DefaultMirageDisguises;
}
static inline int Unit_Infantry_Blink_Disguise_Time()
{
    return Rules->InfantryBlinkDisguiseTime;
}
void UnitClass::Unknown_00709EC0()
{
    {
        bool can_disguise = false;
        if (!unknown_slot48() && !Locomotor.Checked()->Is_Moving() && Type->DisguiseWhenStill && !Contact(0))
            can_disguise = true;
        if (Locomotor.Checked()->Is_Moving()) goto clear_disguise;
        if (Frame % 8 != 0) {
            Cell position = unknown_slot104();
            bool bridge = ((CellClass *)unknown_slot105())->unknown_47b960();
            for (int facing = 0; facing < 8; facing++) {
                Cell adjacent = AdjacentCell[facing & 7] + position;
                CellClass &tile = Map[adjacent];
                TechnoClass *nearby = (TechnoClass *)tile.Cell_Infantry(bridge);
                if (nearby && !House->Is_Ally(nearby)) {
                    unknown_178 = CDTimerClass<FrameTimerClass>(Unit_Infantry_Blink_Disguise_Time());
                    goto clear_disguise;
                }
            }
        }
        if (!can_disguise || unknown_178.Value() != 0) return;
        int choice = unknown_id_source_a3d290->Random()(0, Unit_Default_Mirage_Disguises().Count() - 1);
        int last = Unit_Default_Mirage_Disguises().Count() - 1;
        if (choice >= last) choice = last;
        ObjectTypeClass *type = Unit_Default_Mirage_Disguises()[choice];
        if (type) {
            unknown_40c = type;
            unknown_410 = 0;
            unknown_170 = true;
            unknown_174 = Frame;
            unknown_slot266();
        }
        return;
    }
clear_disguise:
    unknown_slot256();
}
