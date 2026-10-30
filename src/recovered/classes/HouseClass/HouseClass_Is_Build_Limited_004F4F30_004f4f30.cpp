// Build-limit exhaustion, original004F4F30; reference names are hypotheses.
#include "shared/unit.hpp"
#include "shared/infantry_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/rules.hpp"
#include "shared/crt_memory.hpp"
bool HouseClass::Is_Build_Limited_004F4F30(TechnoTypeClass *type)
{
    if (!type) return true;
    int queued=0;
    bool naval=type->Naval;
    FactoryClass *factory=unknown_func_4eb580(type->Kind_Of(),naval,0);
    if (factory) queued=factory->Count_Type_004B9E40(type);
    switch (type->Kind_Of()) {
    case 40:
        if (type->BuildLimit<=0) {
            if (queued+unknown_54b0.unknown_func_491d10(type->unknown_slot16())>=abs(type->BuildLimit)) return true;
        }
        if (type->BuildLimit>0) {
            if (queued+unknown_5430.unknown_func_491d10(type->unknown_slot16())>=type->BuildLimit) return true;
        }
        break;
    case 16: {
        if (type->BuildLimit<=0) {
            if (queued+unknown_54c0.unknown_func_491d10(type->unknown_slot16())>=abs(type->BuildLimit)) return true;
        }
        int owned=unknown_5440.unknown_func_491d10(type->unknown_slot16());
        if (((InfantryTypeClass *)type)->VehicleThief) {
            for (int i=0;i<Units.Count();++i) {
                UnitClass *unit=Units[i];
                if (unit->House==this && unit->unknown_290==type->unknown_slot16()) ++owned;
            }
        }
        if (type->BuildLimit>0) {
            if (queued+owned>=type->BuildLimit) return true;
        }
        break;
    }
    case 7:
        if (type->BuildLimit<=0) {
            if (queued+unknown_54a0.unknown_func_491d10(type->unknown_slot16())>=abs(type->BuildLimit)) return true;
        }
        if (type->BuildLimit>0) {
            if (queued+unknown_5420.unknown_func_491d10(type->unknown_slot16())>=type->BuildLimit) return true;
        }
        break;
    case 3:
        if (((AircraftTypeClass *)type)->AirportBound) {
            int owned=0,queued_aircraft=0;
            for (int i=0;i<Rules->PadAircraft.Count();++i) {
                owned+=unknown_5490.unknown_func_491d10(Rules->PadAircraft[i]->unknown_slot16());
                if (factory) queued_aircraft+=factory->Count_Type_004B9E40(Rules->PadAircraft[i]);
            }
            if (queued_aircraft+owned>=unknown_218) return true;
            break;
        }
        if (type->BuildLimit<=0) {
            if (queued+unknown_54d0.unknown_func_491d10(type->unknown_slot16())>=abs(type->BuildLimit)) return true;
        }
        if (type->BuildLimit>0) {
            if (queued+unknown_5450.unknown_func_491d10(type->unknown_slot16())>=type->BuildLimit) return true;
        }
        break;
    }
    return false;
}
