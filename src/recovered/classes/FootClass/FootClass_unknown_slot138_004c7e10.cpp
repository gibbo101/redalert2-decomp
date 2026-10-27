// int FootClass::unknown_slot138() (0x004C7E10)
// A mission handler (hypothesis: a move mission): with a radio contact (or
// the +0x1B0 target as a techno) the unit asks it for message 0xE; refused
// outside +0x370 it gives up (message 3, slot 261); otherwise an idle unit
// with queued destinations ends a finished piggyback, heads for the next
// queued destination and drops it, and a Teleporter type re-aims at its
// target. Without a contact it clears the target unless one is in hand,
// and commences (slot 117). Returns the mission's rate in frames plus 0..2.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?Unknown_0040DC20@@YIPAVTechnoClass@@PAVAbstractClass@@@Z=0040dc20
// @ref ?unknown_6d8080@TechnoClass@@QAE_NXZ=006d8080
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@8@4008e100000000000000=0079b608
// @ref __com_issue_error@4=00795940
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref _unknown_uuid_IPiggyback_7cfc30=007cfc30
// @ref ?Query@?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454c70

// IPiggyback's interface ID (a copy at 0x007CFC30).
extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;
// The object as a techno, or null (0x0040DC20; hypothesis).
TechnoClass *__fastcall Unknown_0040DC20(AbstractClass *object);

int FootClass::unknown_slot138()
{
    TechnoClass *contact = Contact(0);
    if (contact == 0) {
        contact = Unknown_0040DC20(unknown_1b0);
    }
    if (contact != 0) {
        if (unknown_slot150(0xE, contact) != 1 && !unknown_370) {
            unknown_slot149(3);
            unknown_slot261(0, true);
        } else if (unknown_494 == 0 && unknown_478.Count() > 0) {
            UnknownComPtr<IPiggyback, &unknown_uuid_IPiggyback_7cfc30> piggyback(Locomotor);
            if (piggyback != 0 && piggyback->Is_Ok_To_End()) {
                Locomotor.Attach(0);
                piggyback.Checked()->End_Piggyback(&Locomotor.Pointer);
            }
            if (unknown_478.Count() > 0) {
                unknown_slot260(unknown_478[0], 0);
                unknown_478.Delete(0);
            }
        } else if (unknown_slot32()->Teleporter) {
            AbstractClass *target = unknown_494;
            unknown_490 = 0;
            unknown_494 = 0;
            unknown_slot260(target, 1);
        }
    } else {
        if (!unknown_6d8080() && (unknown_494 == 0 || (unknown_494->Kind_Of() != 1 && unknown_494->Kind_Of() != 2))) {
            unknown_slot261(0, true);
        }
        unknown_slot117();
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
