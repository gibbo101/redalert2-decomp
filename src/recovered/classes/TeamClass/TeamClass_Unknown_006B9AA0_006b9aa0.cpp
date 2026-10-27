// void TeamClass::Unknown_006B9AA0(FootClass *member, int result, TechnoClass *source) (0x006B9AA0)
// A member was damaged by a source: a team that is not moving regroups; otherwise
// a team whose first member is not of the excluded kind may turn on the source.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20

void TeamClass::Unknown_006B9AA0(FootClass *member, int result, TechnoClass *source)
{
    if (source != 0 && result != 0 && !Class->Suicide) {
        if (!IsMoving) {
            unknown_34 = 0;
            NeedsReGrouping = true;
            IsReforming = true;
            return;
        }
        FootClass *first = Member;
        for (FootClass *current = Member; current != 0; current = (FootClass *)current->unknown_4c8) {
            if (current == (FootClass *)source) {
                return;
            }
        }
        if (first != 0 && first->Kind_Of() != 2 && Member->unknown_slot231(0)->WeaponType != 0 && unknown_40 != (AbstractClass *)source) {
            if (Class->Annoyance) {
                unknown_34 = 0;
                NeedsReGrouping = true;
                IsReforming = true;
            }
            if (unknown_40 != 0) {
                TechnoClass *techno = unknown_40->As_Techno();
                if (techno != 0 && techno->unknown_slot231(0)->WeaponType != 0) {
                    if (unknown_34 == 0) {
                        return;
                    }
                    if (techno->unknown_slot214(unknown_34->Center_Coord())) {
                        return;
                    }
                }
            }
            source->Kind_Of();
        }
    }
}

