// @ref ?Get_Object@FactoryClass@@QBEPAVTechnoClass@@XZ=004b9930
// int HouseClass::Can_Build(TechnoTypeClass const *type, bool forced, bool include_in_progress) -- 0x004E3660 (TibSun House.CPP)
// Whether the type can be built: 1 yes, 0 no, -1 at its build limit. The progress test is Factory_Producing_This expanded.
#include "shared/house.hpp"
#include "shared/techno.hpp"
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/rules.hpp"
#include "shared/super.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/house_type.hpp"
#include "shared/unknown_globals.hpp"

// The house type's bit in a house set (RequiredHouses, ForbiddenHouses).
static inline int House_Owner_Bit(HouseTypeClass const *type)
{
    return 1 << type->House;
}

int HouseClass::Can_Build(TechnoTypeClass const *type, bool forced, bool include_in_progress)
{
    if (!forced) {
        if (type->unknown_aa4) {
            return 0;
        }
        TypeList<int> over = type->PrerequisiteOverride;
        for (int i = 0; i < over.Count(); i++) {
            int id = over[i];
            if (unknown_5460.unknown_func_491d10(id) > 0) {
                goto skip;
            }
        }
        if (type->TechLevel == -1) {
            return 0;
        }
        TypeList<int> pre = type->Prerequisite;

        int level = unknown_11c;
        if (type->RequiresStolenAlliedTech && !unknown_205) {
            return 0;
        }
        if (type->RequiresStolenSovietTech && !unknown_204) {
            return 0;
        }
        if (type->RequiredHouses != -1 && (type->RequiredHouses & House_Owner_Bit(Type)) == 0) {
            if ((type->RequiredHouses & unknown_208) == 0 || type->Kind_Of() != 0x10) {
                if ((type->RequiredHouses & unknown_20c) == 0 || type->Kind_Of() != 0x28) {
                    if ((type->RequiredHouses & unknown_210) == 0 || type->Kind_Of() != 3) {
                        if ((type->RequiredHouses & unknown_214) == 0 || type->Kind_Of() != 7) {
                            return 0;
                        }
                    }
                }
            }
        }
        if (type->ForbiddenHouses != -1 && (type->ForbiddenHouses & House_Owner_Bit(Type)) != 0) {
            return 0;
        }
        if (unknown_session_a3d2c3 == 0 && type->Kind_Of() == 7) {
            BuildingTypeClass const *btype = (BuildingTypeClass const *)type;
            if (btype->SuperWeapon != -1 && Supers[btype->SuperWeapon]->Type->DisableableFromShell) {
                return 0;
            }
        }
        if (type->TechLevel > level) {
            return 0;
        }
        if (!Is_Human_Control()) {
            return 1;
        }
        for (int index = 0; index < pre.Count(); index++) {
            switch (pre[index]) {
            case -1: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisitePower.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisitePower[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            case -2: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisiteFactory.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisiteFactory[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            case -3: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisiteBarracks.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisiteBarracks[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            case -4: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisiteRadar.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisiteRadar[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            case -5: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisiteTech.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisiteTech[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            case -6: {
                bool found = false;
                for (int j = 0; j < Rules->PrerequisiteProc.Count(); j++) {
                    if (unknown_5460.unknown_func_491d10(Rules->PrerequisiteProc[j]) > 0) {
                        found = true;
                        break;
                    }
                }
                if (!found) return 0;
            } break;
            default: {
                BuildingTypeClass *btype = BuildingTypes[pre[index]];
                if (btype->PowersUpBuilding[0] != '\0') {
                    BuildingClass *bptr;
                    bool found = false;
                    for (int j = Buildings.Count() - 1; j >= 0; j--) {
                        bptr = Buildings[j];
                        if (!bptr->unknown_76 && bptr->unknown_530) {
                            if (bptr->unknown_slot91() != 0x13 && bptr->MissionQueue != 0x13) {
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found) {
                        int k = 0;
                        while (true) {
                            if (bptr->unknown_4c0[k] == btype) {
                                goto breakout;
                            }
                            k++;
                            if (k >= 3) break;
                        }
                    }
                    return 0;
                }
                if (unknown_5460.unknown_func_491d10(pre[index]) == 0) return 0;
                breakout:;
            } break;
            }
        }
    }
skip:
    switch (type->Kind_Of()) {
    case 0x28: {
        int limit = type->BuildLimit;
        if (type->BuildLimit <= 0) {
            if (unknown_54b0.unknown_func_491d10(type->unknown_slot16()) >= abs(limit)) return 0;
        }
        if (limit <= 0) return 1;
        if (unknown_5430.unknown_func_491d10(type->unknown_slot16()) < type->BuildLimit) {
            return 1;
        }
        if (include_in_progress) {
            if (Factory_Producing_This_004e4090(type) != 0) return 1;
        }
        return -1;
    }
    case 0x10: {
        if (type->BuildLimit <= 0) {
            if (unknown_54c0.unknown_func_491d10(type->unknown_slot16()) >= abs(type->BuildLimit)) return 0;
        }
        int count = unknown_5440.unknown_func_491d10(type->unknown_slot16());
        if (((InfantryTypeClass const *)type)->VehicleThief) {
            for (int i = 0; i < Units.Count(); i++) {
                UnitClass *unit = Units[i];
                if (unit->House == this && unit->unknown_290 == type->unknown_slot16()) {
                    count++;
                }
            }
        }
        if (type->BuildLimit <= 0) {
            return 1;
        }
        if (count < type->BuildLimit) {
            return 1;
        }
        if (include_in_progress && count == type->BuildLimit) {
            if (Factory_Producing_This_004e4090(type) != 0) return 1;
        }
        return -1;
    }
    case 7: {
        int limit = type->BuildLimit;
        if (type->BuildLimit <= 0) {
            if (unknown_54a0.unknown_func_491d10(type->unknown_slot16()) >= abs(limit)) return 0;
        }
        if (limit <= 0) return 1;
        if (unknown_5420.unknown_func_491d10(type->unknown_slot16()) < type->BuildLimit) {
            return 1;
        }
        if (include_in_progress) {
            if (Factory_Producing_This_004e4090(type) != 0) return 1;
        }
        return -1;
    }
    case 3: {
        int limit = type->BuildLimit;
        if (type->BuildLimit <= 0) {
            if (unknown_54d0.unknown_func_491d10(type->unknown_slot16()) >= abs(limit)) return 0;
        }
        if (limit <= 0) return 1;
        if (unknown_5450.unknown_func_491d10(type->unknown_slot16()) < type->BuildLimit) {
            return 1;
        }
        if (include_in_progress) {
            if (Factory_Producing_This_004e4090(type) != 0) return 1;
        }
        return -1;
    }
    }
    return 1;
}
