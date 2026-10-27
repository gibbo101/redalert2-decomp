// @ref ?Unknown_004E5E30@HouseClass@@=004e5e30
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/factory_class.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

// Private typed experiment. Owner authorized fresh House call-interface copy;
// return and fourth-argument meanings remain explicit hypotheses.
// Full original body 114 bytes, then14 NOPs to independently used004B9DF0.
void FactoryClass::Start_Next_Queued_004B9D70()
{
    if (Queue.Count() && !Object && (!Rate || unknown_6c)) {
        TechnoTypeClass *type = Queue[0];
        Queue.Delete(0);
        int index = type->unknown_slot16();
        if (index >= 0) {
            Owner->Unknown_004E5E30(type->Kind_Of(), index, type->Naval, 1);
        }
    }
}
