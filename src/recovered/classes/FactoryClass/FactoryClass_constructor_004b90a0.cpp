#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/factory_class.hpp"
#include "shared/object_lists.hpp"
// @ref ?unknown_AbstractClass_list_00ac0d60@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d60
// @ref ??_7?$DynamicVectorClass@PAVTechnoTypeClass@@@@6B@=007a0f44
// @ref ??_7FactoryClass@@6BIPersistStream@@@=007a0ee0
// @ref ??_7FactoryClass@@6BIRTTITypeInfo@@@=007a0ec4
// @ref ??_7FactoryClass@@6BINoticeSink@@@=007a0ebc
// @ref ??_7FactoryClass@@6BINoticeSource@@@=007a0eb4
FactoryClass::FactoryClass() :
 Object(0),unknown_58(false),unknown_59(false),UnspentCost(0),unknown_60(0),unknown_64(-1),Owner(0),unknown_6c(false),unknown_6d(true)
{
    Create_ID();
    Factories.Add(this);
    Set_Rate(0);
    Stage = 0;
    unknown_AbstractClass_list_00ac0d60.Add(this);
}
