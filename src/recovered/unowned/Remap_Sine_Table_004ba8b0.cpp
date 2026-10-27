#include "shared/fast_math.hpp"
float __fastcall Fast_Sin_Float_004ba920(float angle);
float __fastcall Fast_Acos_Float_004baa30(float value);
extern double const unknown_sine_step_007a0f98;
extern double const unknown_acos_step_007a0fa0;
// @ref ?unknown_sine_step_007a0f98@@=007a0f98
// @ref ?unknown_acos_step_007a0fa0@@=007a0fa0
void __cdecl Remap_Sine_Table_004ba8b0()
{
 for(int i=0;i!=10241;++i) unknown_sin_table_801dc4[i]=Fast_Sin_Float_004ba920((float)(i*unknown_sine_step_007a0f98));
}
