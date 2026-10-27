#include "shared/crt_memory.hpp"
#include "shared/fast_math.hpp"
float __fastcall Fast_Atan_Float_004bac50(float value);
extern float const unknown_atan_sample_00810dc8;
// @ref ?unknown_atan_sample_00810dc8@@=00810dc8
// @ref __real@4@3ff38000000000000000=007a0fb0
// @ref __real@4@3fffc90fdb0000000000=007a0f8c
// @ref __real@4@bfffc90fdb0000000000=007a0f90
// @ref __real@8@4000c90fdaa22168c000=0079d158
// @ref ?unknown_atan_step_817df8@@3MA=00817df8
// @ref ?unknown_atan_table_813df4@@3PAMA=00813df4
float __cdecl Remap_Atan_Table_004bab30()
{
 float limit=unknown_atan_sample_00810dc8;
 unknown_atan_step_817df8=limit*0.000244140625f;
 float value=0.0f;
 for(int i=0;i!=4097;++i) {
  unknown_atan_table_813df4[i]=Fast_Atan_Float_004bac50(value);
  value+=unknown_atan_step_817df8;
 }
 return limit;
}
