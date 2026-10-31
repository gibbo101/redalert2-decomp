// Animation frame including disguise sequences and jumpjet target facing (0x00500350).
#include "shared/infantry.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Release_Held@UnknownPersistPtr@@QAEXXZ=004a4d00
// @ref _CLSID_JumpjetLocomotionClass=007a2000
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref ?Direction_To@ObjectClass@@QBE?AUUnknownFacingDir@@PBVAbstractClass@@@Z=005d2730
// @ref ?unknown_sequence_facings_7a33f4@@3QBHB=007a33f4
extern int const unknown_sequence_facings_7a33f4[32];
extern "C" GUID const CLSID_JumpjetLocomotionClass;

int InfantryClass::unknown_500350()
{
    int sequence = Sequence;
    if (sequence == -1) {
        if (Map_Cell_At(unknown_slot104())->unknown_ec == 2 && !unknown_79) {
            sequence = 16;
        } else {
            sequence = 0;
        }
    }
    InfantryTypeClass *type = Type;
    if (!unknown_slot245(unknown_player_a35db4)) {
        type = (InfantryTypeClass *)unknown_slot50(true);
    }
    int count = type->DoControls[sequence].Count;
    int frame = StageClass::Stage % (count > 1 ? count : 1);
    bool is_jumpjet = false;
    if (Type->JumpJet) {
        UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(Locomotor);
        GUID clsid;
        persist.Checked()->GetClassID(&clsid);
        is_jumpjet = clsid == CLSID_JumpjetLocomotionClass;
    }
    if (is_jumpjet && unknown_228 != 0) {
        if (type->DoControls[sequence].Jump > 0) {
            frame += unknown_sequence_facings_7a33f4[Dir_To_32(Direction_To(unknown_228))]
                * type->DoControls[sequence].Jump;
        }
    } else if (type->DoControls[sequence].Jump > 0) {
        frame += unknown_sequence_facings_7a33f4[Dir_To_32(unknown_2e0.Current())]
            * type->DoControls[sequence].Jump;
    }
    return type->DoControls[sequence].Frame + frame;
}
