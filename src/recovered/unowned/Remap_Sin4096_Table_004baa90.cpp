#include "shared/fast_math.hpp"
extern double unknown_sin4096_scale_007a0f80;
extern double const unknown_sin4096_step_007a0fa8;
// @ref ?unknown_sin4096_scale_007a0f80@@=007a0f80
// @ref ?unknown_sin4096_step_007a0fa8@@=007a0fa8
// @ref ?unknown_sin_table_80fde4@@=0080fde4
float __fastcall Fast_Sin4096_Float_004baaf0(float angle);
void __cdecl Remap_Sin4096_Table_004baa90()
{
 for(int i=0;i!=4097;++i) unknown_sin_table_80fde4[i]=Fast_Sin4096_Float_004baaf0((float)(i*unknown_sin4096_step_007a0fa8));
}
