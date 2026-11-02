// ObjectTypeClass existing constructor API/layout; real Particle-type base dependency.
#include "shared/object_type.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ?unknown_string_83c55c@@3PADA=0083c55c
// @ref ?ObjectTypes@ObjectTypeClass@@2V?$DynamicVectorClass@PAVObjectTypeClass@@@@A=00a72f90
// Per-unit form of the real container append: observed growth operand order.
// No new layout or alias; same existing template member and protected fields.
template <> inline bool DynamicVectorClass<ObjectTypeClass *>::Add(ObjectTypeClass *const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(GrowthStep + VectorMax)) return false;
        } else return false;
    }
    int index = ActiveCount++;
    Vector[index] = object;
    return true;
}
ObjectTypeClass::ObjectTypeClass(char const *ini_name)
    : AbstractTypeClass(ini_name),
      unknown_9c(0), MaxStrength(0), unknown_a4(0), unknown_a8(false), unknown_ac(0),
      unknown_1b8(false), unknown_1bc(0), unknown_1c0(-1), unknown_1c4(-1),
      unknown_1e1(false), unknown_1e2(false),
      unknown_1fc(false), unknown_1fd(false), unknown_1fe(true), unknown_1ff(false),
      unknown_200(true), unknown_201(true), unknown_202(false), unknown_203(false),
      unknown_204(false), unknown_205(true), unknown_206(false), unknown_207(false),
      unknown_208(false), unknown_209(false), unknown_20a(false),
      LineTrailColor(128,128,128), unknown_210(16)
{
    unknown_1c8 = ID;
    unknown_1e3 = unknown_string_83c55c;
    ObjectTypes.Add(this);
}
