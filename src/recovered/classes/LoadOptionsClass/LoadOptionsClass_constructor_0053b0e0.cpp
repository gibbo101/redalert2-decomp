// LoadOptionsClass default saved-game file list. Original0053B0E0,75body+5padding.
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/map_seed.hpp"
// @ref ??_7LoadOptionsClass@@6B@=007a581c
// @ref ??_7?$DynamicVectorClass@PAVFileEntryClass@@@@6B@=007a5844
// @ref ??_7?$VectorClass@PAVFileEntryClass@@@@6B@=007a5864
// @ref ??_E?$DynamicVectorClass@PAVFileEntryClass@@@@UAEPAXI@Z=0053cd80
// @ref ??_E?$VectorClass@PAVFileEntryClass@@@@UAEPAXI@Z=0053cd30
// @ref ??_G?$DynamicVectorClass@PAVFileEntryClass@@@@UAEPAXI@Z=0053cd80
// @ref ??_G?$VectorClass@PAVFileEntryClass@@@@UAEPAXI@Z=0053cd30
// @ref ??_GLoadOptionsClass@@UAEPAXI@Z=0053c9f0
// @ref ?Load@LoadOptionsClass@@UAE_NPBD@Z=0053c680
// @ref ?Save@LoadOptionsClass@@UAE_NPBDPBG@Z=0053c760
// @ref ?Delete_File@LoadOptionsClass@@UAE_NPBD@Z=0053c7d0
// @ref ?Load_Menu_Name@LoadOptionsClass@@UBEPBGXZ=0053c970
// @ref ?Save_Menu_Name@LoadOptionsClass@@UBEPBGXZ=0053c990
// @ref ?Delete_Menu_Name@LoadOptionsClass@@UBEPBGXZ=0053c9b0
// @ref ?Saved_Message@LoadOptionsClass@@UBEPBGXZ=0053c9d0
// @ref ??_C@_03BNDG@SAV?$AA@=007df9e8
// @ref ??1LoadOptionsClass@@UAE@XZ=0053b130

LoadOptionsClass::LoadOptionsClass()
{
    unknown_04 = 0;
    Description = 0;
    unknown_14 = 0;
    Extension = "SAV";
    unknown_10 = 0x800;
    Files.Clear();
}
