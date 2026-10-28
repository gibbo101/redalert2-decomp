// UnknownPathEstimator::UnknownPathEstimator() (0x00427FB0)
#ifndef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#include "shared/path_estimator.hpp"
// @ref ??0?$VectorClass@I@@QAE@IPBI@Z=0042b510
// @ref ??_7?$DynamicVectorClass@I@@6B@=0079c4dc

UnknownPathEstimator::UnknownPathEstimator()
    : unknown_00(false), unknown_01(false), unknown_02(false), unknown_03(true), unknown_04(1.0f), unknown_08(true),
      unknown_18(0), unknown_1c(0), unknown_20(0), unknown_24(0), unknown_28(-1), unknown_2c(-1), unknown_38(true),
      unknown_3c(0), unknown_6c(-1), unknown_70(0), unknown_72(0)
{
    unknown_14 = new UnknownPathEstimatorBlock(0x10000);
    unknown_68 = new UnknownPathEstimatorBlock(0x2710);
    unknown_10 = new UnknownPathTable16;
    unknown_0c = new UnknownPathTable24;
    unknown_0c->entries[0xFFFF].unknown_14 = 0;
    unknown_10->entries[0xFFFF].unknown_0c = 0;
    unknown_14->Clear();
    unknown_68->Clear();
    for (int index = 0; index < 3; index++) {
        unknown_40[index] = 0;
        unknown_4c[index] = 0;
        unknown_58[index] = 0;
        unknown_74[index].Clear();
        for (int slot = 0; slot < 250; slot++) {
            unknown_bc[index][slot] = 0;
        }
        unknown_c74[index] = 0;
    }
    unknown_64 = new char[0x27100];
}
