// Building repair mission: construction-yard, hospital, armory and unit service states.
// Original 00447260: 4503-byte complete body and 9 bytes of frozen padding.
// Repair states: 0 initializes service, 1 waits for the client, 2 performs service.
#include "shared/unit.hpp"
#include "shared/building.hpp"
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/locomotion.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
#include "shared/radar_event.hpp"
#include "shared/vox_class.hpp"
#include "shared/sound_play.hpp"
extern "C" GUID const CLSID_HoverLocomotionClass;
extern "C" GUID const CLSID_ShipLocomotionClass;
// Existing 0051FC80 owner-condition ABI; its nominal receiver type remains unknown.
class Leaf_51fc80 { public: bool get(); };
// @ref ?get@Leaf_51fc80@@QAE_NXZ=0051fc80
// @ref ??_C@_0BB@LLKG@EVA_UnitRepaired?$AA@=007cfa00
// @ref ??_C@_0BG@DIHB@EVA_InsufficientFunds?$AA@=007cf9e8
// @ref _CLSID_HoverLocomotionClass=007a1f80
// @ref _CLSID_ShipLocomotionClass=007a1ff0
// @ref ?unknown_84ed10@@3HA=0084ed10
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref __real@8@4008e100000000000000=0079b608
// The repeated archive-position query and signed conversion to cell units.
inline Cell Building_Repair_Archive_Cell_00447260(AbstractClass const &target)
{
    return Cell(target.Center_Coord());
}

int BuildingClass::unknown_slot141()
{
    if (Type->ConstructionYard) {
        switch (unknown_a8) {
        case 0: {
                unknown_443d60(2);
                unknown_44c920(7, Health_Ratio() <= Rules->unknown_1368, false, 0);
                unknown_a8 = 2;

                break;
            }
        case 2: {
                if (!In_Radio_Contact()) {
                    unknown_slot116(5, false);
                    unknown_44cfd0(7);

                }

                break;
            }
        }
        return 1;
    }
    if (Type->Hospital) {
        switch (unknown_a8) {
        case 0: {
                unknown_a8 = 2;
                unknown_5ad = false;
                unknown_4f4.Set_Stage(0);
                unknown_4f4.Set_Rate(1);
                if (Type->Ammo != -1) {
                    --unknown_254;
                    unknown_254 = unknown_254 > 0 ? unknown_254 : 0;
                }

                break;
            }
        case 2: {
                unknown_4f4.Graphic_Logic();
                if (unknown_4f4.Fetch_Stage() >= Rules->IRepairRate * 900.0) {
                    unknown_5ad = false;
                    unknown_4f4.Set_Stage(0);
                    switch (unknown_slot149(28)) {
                    case 33:
                        if (House->Unknown_004F52B0()) {
                            if (Unknown_0063B5B0(8, unknown_slot104())) Speech_Play_Name("EVA_UnitRepaired", -1, -1);
                            Voc_Play_At(Rules->HealCrateSound, CoordStruct(Coord), 0);
                        }
                        // Both completed treatment and an empty reply release the patient.
                    case 10:
                        unknown_slot62((TechnoClass *)Cargo.unknown_4689f0());
                        unknown_slot116(5, false);
                        break;
                    case 32:
                        unknown_slot62((TechnoClass *)Cargo.unknown_4689f0());
                        break;
                    }
                }
                return 1;

            }
        }
        return (int)(Control()->unknown_10 * 900.0);
    }
    if (Type->Armory) {
        switch (unknown_a8) {
        case 0: {
                unknown_a8 = 2;
                unknown_5ad = false;
                unknown_4f4.Set_Stage(0);
                unknown_4f4.Set_Rate(1);
                --unknown_254;
                unknown_254 = unknown_254 > 0 ? unknown_254 : 0;

                break;
            }
        case 2: {
                unknown_4f4.Graphic_Logic();
                if (unknown_4f4.Fetch_Stage() >= Rules->IRepairRate * 900.0) {
                    TechnoClass *contact = Contact(0);
                    if (contact->unknown_118.unknown_713400()) contact->unknown_118.unknown_713520(true);
                    else contact->unknown_118.Unknown_00713550(true);
                    unknown_slot62((TechnoClass *)Cargo.unknown_4689f0());
                    unknown_slot116(5, false);
                }

                break;
            }
        }
        return (int)(Control()->unknown_10 * 900.0);
    }
    if (Type->UnitRepair) {

        switch (unknown_a8) {
        case 0: {
                if (!In_Radio_Contact()) {
                    unknown_44cfd0(8);
                    unknown_44cfd0(11);
                    unknown_44c920(12, Health_Ratio() <= Rules->unknown_1368, false, 0);
                    unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                    unknown_slot116(5, true);
                    return 1;
                }
                unknown_5ad = false;
                int distance = 100;
                FootClass *contact = (FootClass *)Contact(0);
                UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(contact->Locomotor);
                GUID clsid;
                persist.Checked()->GetClassID(&clsid);
                if (clsid == CLSID_HoverLocomotionClass) distance = 200;
                if (clsid == CLSID_ShipLocomotionClass) distance = 200;
                if (unknown_slot149(19) == 1 && unknown_slot281(Contact(0)) < distance) {
                    unknown_a8 = 1;
                    return 3;
                }
                if (!reinterpret_cast<Leaf_51fc80 *>(House)->get()) contact->Locomotor.Checked()->Power_On();

                break;
            }
        case 2: {
                if (!In_Radio_Contact()) {
                    unknown_44cfd0(8);
                    unknown_44cfd0(11);
                    unknown_44c920(12, Health_Ratio() <= Rules->unknown_1368, false, 0);
                    unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                    unknown_a8 = 1;
                    return 1;
                }
                if (unknown_4f4.unknown_10 == 0) unknown_4f4.unknown_10 = 1;
                unknown_4f4.Graphic_Logic();
                if (unknown_4f4.Fetch_Stage() >= Rules->URepairRate * 900.0 && unknown_slot149(19) == 1) {
                    unknown_5ad = false;
                    unknown_4f4.Set_Stage(0);
                    switch (unknown_slot149(28)) {
                    case 1:
                        break;
                    case 32: {
                            if (unknown_372 && House->Available_Money() == 0) Speech_Play_Name("EVA_InsufficientFunds", -1, -1);
                            unknown_44cfd0(8);
                            unknown_44cfd0(11);
                            unknown_44c920(12, Health_Ratio() <= Rules->unknown_1368, false, 0);
                            unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                            unknown_a8 = 1;

                            break;
                        }
                    default: {
                            if (unknown_372 && Unknown_0063B5B0(8, unknown_slot104())) Speech_Play_Name("EVA_UnitRepaired", -1, -1);
                            unknown_44cfd0(8);
                            unknown_44cfd0(11);
                            unknown_44c920(12, Health_Ratio() <= Rules->unknown_1368, false, 0);
                            unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                            unknown_a8 = 1;
                            FootClass *mover = Building_Radio_Foot_004397f0(Contact(0));
                            if (mover->unknown_1b0 && !mover->House->unknown_func_4f52f0()) {
                                mover->unknown_slot116(2, false);
                                mover->unknown_slot260(mover->unknown_1b0, 1);
                                mover->unknown_6d6e50(0);
                                unknown_slot149(3);
                                mover->unknown_3f8 = 0;
                                return 1;
                            }
                            Cell exit = *(Cell *)unknown_slot280((int)&Cell(), (int)Contact(0));
                            if (unknown_1b0) exit = Building_Repair_Archive_Cell_00447260(*unknown_1b0);
                            if (exit != *(Cell const *)&unknown_84ed10) {
                                mover->unknown_slot116(2, false);
                                mover->unknown_slot260(&Map[exit], 1);
                                unknown_slot149(3);
                                mover->unknown_3f8 = 0;
                                return 1;
                            }

                            break;
                        }
                    }
                }
                return 1;

            }
        case 1: {
                if (!In_Radio_Contact()) {
                    if (unknown_454[8] || unknown_454[11]) {
                        unknown_44c920(12, Health_Ratio() <= Rules->unknown_1368, false, 0);
                        unknown_44c920(3, Health_Ratio() <= Rules->unknown_1368, false, 0);
                        unknown_44cfd0(8);
                        unknown_44cfd0(11);
                    }
                    if (!unknown_454[12]) {
                        unknown_5ad = true;
                        unknown_slot116(5, true);
                    }
                    return 1;
                }
                if (unknown_454[8]) return 1;
                FootClass *contact = (FootClass *)Contact(0);
                if (unknown_slot281(Contact(0)) < 200) {
                    if (contact->Locomotor.Checked()->Is_Powered()) {
                        if (!contact->Locomotor.Checked()->Is_Moving()) contact->Locomotor.Checked()->Power_Off();
                        return 1;
                    }
                    if (!contact->Locomotor.Checked()->Is_Powered() && ((FootClass *)Contact(0))->unknown_494) {
                        ((FootClass *)Contact(0))->unknown_4cd9b0();
                    }
                }
                if (unknown_slot149(19) == 1) {
                    TechnoClass *client = Contact(0);
                    bool damaged = client->Health_Ratio() < Rules->unknown_1360;
                    bool manual_reload = client->unknown_slot32()->ManualReload;
                    int reply = unknown_slot149(28);
                    bool roger = reply == 1;
                    bool all_done = reply == 33;
                    if ((!damaged && !manual_reload) || (!roger && !all_done)) {
                        if (client->Health_Ratio() == Rules->unknown_1360 && !((FootClass *)client)->Locomotor.Checked()->Is_Powered()) {
                            FootClass *mover = Building_Radio_Foot_004397f0(Contact(0));
                            mover->Locomotor.Checked()->Power_On();
                            if (mover->unknown_1b0 && !mover->House->unknown_func_4f52f0()) {
                                mover->unknown_slot116(2, false);
                                mover->unknown_slot260(mover->unknown_1b0, 1);
                                mover->unknown_6d6e50(0);
                                mover->unknown_3f8 = 0;
                                unknown_slot149(3);
                            } else {
                                Cell exit = *(Cell *)unknown_slot280((int)&Cell(), (int)Contact(0));
                                if (unknown_1b0) exit = Building_Repair_Archive_Cell_00447260(*unknown_1b0);
                                if (exit != *(Cell const *)&unknown_84ed10) {
                                    mover->unknown_slot116(2, false);
                                    mover->unknown_slot260(&Map[exit], 1);
                                    mover->unknown_6d6e50(0);
                                    unknown_slot149(3);
                                    mover->unknown_3f8 = 0;
                                }
                            }
                        }
                    } else if (!client->unknown_328 || client->House->unknown_func_4f52f0()) {
                        if (unknown_372) Speech_Play_Name("EVA_Repairing", -1, -1);
                        unknown_a8 = 2;
                        unknown_44c920(10, Health_Ratio() <= Rules->unknown_1368, false, 0);
                        unknown_44cfd0(3);
                        unknown_44cfd0(17);
                        unknown_5ad = false;
                        unknown_4f4.Set_Stage(0);
                        unknown_4f4.Set_Rate(1);
                    } else {
                        client->unknown_slot98(1);
                        unknown_a8 = 0;
                        unknown_5ad = true;
                    }
                } else if (!reinterpret_cast<Leaf_51fc80 *>(House)->get()) {
                    if (!((FootClass *)Contact(0))->Locomotor.Checked()->Is_Powered()) ((FootClass *)Contact(0))->Locomotor.Checked()->Power_On();
                }

                break;
            }
        }
    } else if (Type->UnitReload) {
        bool servicing = false;
        for (int index=0; index<RadioLinks.Length(); ++index) {
            TechnoClass *contact = Contact(index);
            if (contact) {
                if (unknown_slot150(29, contact) == 1 && contact->Strength == contact->unknown_slot32()->MaxStrength) goto release_contact;
                if (contact->unknown_slot91() != 7 && unknown_slot150(19, contact) == 1) {
                    servicing = true;
                    if (contact->unknown_slot91() != 0) {
                        contact->unknown_slot116(0, false);
                    } else {
                        if (unknown_slot150(31, contact) != 1 && unknown_slot150(28, contact) != 1) {
                        release_contact:
                            contact->unknown_slot261(false, true);
                            contact->unknown_slot118(5);
                            contact->unknown_slot194();
                        }
                    }
                }
            }
        }
        if (servicing) return (int)(Rules->ReloadRate * 900.0);
        unknown_slot116(5, false);
        return 3;
    } else return 15;
    return (int)(Control()->unknown_10 * 900.0);
}
