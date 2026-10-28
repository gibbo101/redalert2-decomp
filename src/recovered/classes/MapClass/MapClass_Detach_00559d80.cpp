// void MapClass::Detach(AbstractClass *target, bool all) (0x00559D80, slot 25)
// Forgets a target: for a tag (kind 0x2C) every cell of the tagged-cell list
// (+0x1158) carrying it loses its tag and leaves the list, the dummy cell
// forgets it (0x0047A340), and the tag leaves the tag list 0x00866238.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/abstract_class.hpp"
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8
// @ref ?unknown_tags_866238@@3V?$DynamicVectorClass@PAVTagClass@@@@A=00866238
// @ref ?unknown_47a340@CellClass@@QAEXPAVAbstractClass@@@Z=0047a340
// @ref ?Set_unknown_3c@CellClass@@QAEXPAVTagClass@@@Z=0047a460

// The tag list (0x00866238; as TagClass's destructor 0x006B39F0 declares it).
extern DynamicVectorClass<TagClass *> unknown_tags_866238;

void MapClass::Detach(AbstractClass *target, bool all)
{
    if (target->Kind_Of() == 0x2C) {
        for (int index = 0; index < unknown_1158.Count(); index++) {
            CellClass *cell = &(*this)[unknown_1158[index]];
            if (cell != 0 && cell->unknown_3c == (TagClass *)target) {
                cell->Set_unknown_3c(0);
                unknown_1158.Delete(cell->MapCoords);
                index--;
            }
        }
        unknown_dummy_cell_a6f9f8.unknown_47a340(target);
    }
    if (target->Kind_Of() == 0x2C) {
        unknown_tags_866238.Delete((TagClass *)target);
    }
}
