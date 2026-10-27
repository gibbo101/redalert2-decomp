#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/factory_class.hpp"
extern DynamicVectorClass<AbstractClass *> unknown_AbstractClass_list_00ac0d60;
extern bool unknown_flag_a40958;
// @ref ?unknown_AbstractClass_list_00ac0d60@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d60
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?Abandon_Production_004B97C0@FactoryClass@@QAE_NXZ=004b97c0
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ??_7FactoryClass@@6BIPersistStream@@@=007a0ee0
// @ref ??_7FactoryClass@@6BIRTTITypeInfo@@@=007a0ec4
// @ref ??_7FactoryClass@@6BINoticeSink@@@=007a0ebc
// @ref ??_7FactoryClass@@6BINoticeSource@@@=007a0eb4
// @ref ??_7?$VectorClass@PAVTechnoTypeClass@@@@6B@=007a0f64
FactoryClass::~FactoryClass()
{
    Unknown_006ECB90(this, true);
    Factories.Delete(this);
    if (unknown_flag_a40958) Abandon_Production_004B97C0();
    unknown_AbstractClass_list_00ac0d60.Delete(this);
}
