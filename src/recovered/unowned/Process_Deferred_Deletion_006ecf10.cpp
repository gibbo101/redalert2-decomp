// void Process_Deferred_Deletion() (0x006ECF10)
// TibSun tracker.cpp: releases the objects waiting on the deferred deletion list
// (0x00AC0CD8) once they are inactive (slot 17); a released building, unit, infantry or
// aircraft is marked +0x7D first. Active objects stay for a later pass.
#include "shared/object.hpp"
// @ref ??_7type_info@@6B@=007b15e4
// @ref ??_R0?AVBuildingClass@@@8=007cf6a8
// @ref ??_R0?AVUnitClass@@@8=007f6d68
// @ref ??_R0?AVInfantryClass@@@8=007daec0
// @ref ??_R0?AVAircraftClass@@@8=007ce5e0
// @ref ___RTtypeid=00783c05
// @ref ??8type_info@@QBEHABV0@@Z=00781cd1

class type_info {
public:
    virtual ~type_info();
    int operator==(type_info const &rhs) const;
    int operator!=(type_info const &rhs) const;
private:
    void *_m_data;
    char _m_d_name[1];
};

class BuildingClass;
class UnitClass;
class InfantryClass;
class AircraftClass;

void Process_Deferred_Deletion()
{
    int index = 0;
    while (index < unknown_objects_ac0cd8.Count()) {
        AbstractClass *obj = unknown_objects_ac0cd8[index];
        if (obj->unknown_slot17()) {
            while (true) {
                if (!unknown_objects_ac0cd8.Delete(obj)) {
                    break;
                }
            }
            if (obj->Release()) {
                if (typeid(BuildingClass) == typeid(*obj)
                 || typeid(UnitClass) == typeid(*obj)
                 || typeid(InfantryClass) == typeid(*obj)
                 || typeid(AircraftClass) == typeid(*obj)) {
                    ((ObjectClass *)obj)->unknown_7d = true;
                }
                delete obj;
            }
        } else {
            ++index;
        }
    }
}
