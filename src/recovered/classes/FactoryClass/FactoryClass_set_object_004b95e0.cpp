#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/factory_class.hpp"
#include "shared/debug_printf.hpp"
// Original production-cancel operation; names of the factory flags and
// house construction indices remain unknown.
// @ref ?unknown_abandon_message_7d7f44@@3QBDB=007d7f44
extern char const unknown_abandon_message_7d7f44[];

void FactoryClass::Set_Object_004B95E0(TechnoClass *object)
{
    Abandon_Production_004B97C0();
    Object = object;
    Owner = object->House;
    UnspentCost = 0;
    Set_Rate(0);
    Stage = 54;
    unknown_59 = true;
    unknown_6c = true;
}
