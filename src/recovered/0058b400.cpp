// 0x0058b400: function not yet identified
//
// Body: 17 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: void FUN_0058b400(void)
// Callees with accepted source:
//   FUN_0078298a -> src/recovered/0078298a.cpp
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//

namespace seed_0058b400 {

extern void  FUN_0058b420(void);
extern void __cdecl FUN_0058d970(void);
extern unsigned int  FUN_0078298a(unsigned int param_1);

void  FUN_0058b400(void)
{
    FUN_0058b420();
    FUN_0078298a((unsigned int)(FUN_0058d970));
    return;
}

}  // namespace seed_0058b400
