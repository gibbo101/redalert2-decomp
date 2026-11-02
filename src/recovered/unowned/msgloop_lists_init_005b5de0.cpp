// msgloop.cpp's two lists (Westwood wwlib msgloop.cpp): the modeless dialogs (0x00A71900) and the accelerators
// (0x00A71928). Their dynamic initializers are 0x005B5DE0 / 0x005B5E60 and their atexit destructors
// 0x005B5E20 / 0x005B5EA0 (comment-only drafts follow). This first source of the unit sets the vector
// implementation switches the unit's members use.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/msgloop.hpp"
#include "shared/crt_string.hpp"
// @ref ??_7?$DynamicVectorClass@PAUHWND__@@@@6B@=007a70e4
// @ref ??_7?$VectorClass@PAUHWND__@@@@6B@=007a7104
// @ref ??_7?$DynamicVectorClass@UAcceleratorTracker@@@@6B@=007a7124
// @ref ??_7?$VectorClass@UAcceleratorTracker@@@@6B@=007a7144
// @ref ??8?$VectorClass@PAUHWND__@@@@UBE_NABV0@@Z=005b62e0
// @ref ??8?$VectorClass@UAcceleratorTracker@@@@UBE_NABV0@@Z=005b6540
// @ref ??_E?$DynamicVectorClass@PAUHWND__@@@@UAEPAXI@Z=005b68c0
// @ref ??_E?$DynamicVectorClass@UAcceleratorTracker@@@@UAEPAXI@Z=005b6960
// @ref ??_E?$VectorClass@PAUHWND__@@@@UAEPAXI@Z=005b6870
// @ref ??_E?$VectorClass@UAcceleratorTracker@@@@UAEPAXI@Z=005b6910
// @ref ?Clear@?$DynamicVectorClass@PAUHWND__@@@@UAEXXZ=005b6210
// @ref ?Clear@?$DynamicVectorClass@UAcceleratorTracker@@@@UAEXXZ=005b6270
// @ref ?Clear@?$VectorClass@PAUHWND__@@@@UAEXXZ=005b63d0
// @ref ?Clear@?$VectorClass@UAcceleratorTracker@@@@UAEXXZ=005b6690
// @ref ?Fetch@?$VectorClass@PAUHWND__@@@@UBEPAUHWND__@@H@Z=005b6260
// @ref ?Fetch@?$VectorClass@UAcceleratorTracker@@@@UBE?AUAcceleratorTracker@@H@Z=005b62c0
// @ref ?ID@?$DynamicVectorClass@PAUHWND__@@@@UAEHABQAUHWND__@@@Z=005b6510
// @ref ?ID@?$DynamicVectorClass@PAUHWND__@@@@UAEHPBQAUHWND__@@@Z=005b6240
// @ref ?ID@?$DynamicVectorClass@UAcceleratorTracker@@@@UAEHABUAcceleratorTracker@@@Z=005b6830
// @ref ?ID@?$DynamicVectorClass@UAcceleratorTracker@@@@UAEHPBUAcceleratorTracker@@@Z=005b62a0
// @ref ?ID@?$VectorClass@PAUHWND__@@@@UAEHABQAUHWND__@@@Z=005b6400
// @ref ?ID@?$VectorClass@PAUHWND__@@@@UAEHPBQAUHWND__@@@Z=005b6440
// @ref ?ID@?$VectorClass@UAcceleratorTracker@@@@UAEHABUAcceleratorTracker@@@Z=005b66c0
// @ref ?ID@?$VectorClass@UAcceleratorTracker@@@@UAEHPBUAcceleratorTracker@@@Z=005b6710
// @ref ?Resize@?$DynamicVectorClass@PAUHWND__@@@@UAE_NHPBQAUHWND__@@@Z=005b6460
// @ref ?Resize@?$DynamicVectorClass@UAcceleratorTracker@@@@UAE_NHPBUAcceleratorTracker@@@Z=005b6730
// @ref ?Resize@?$VectorClass@PAUHWND__@@@@UAE_NHPBQAUHWND__@@@Z=005b6320
// @ref ?Resize@?$VectorClass@UAcceleratorTracker@@@@UAE_NHPBUAcceleratorTracker@@@Z=005b65a0
// @ref _atexit=0078298a
// @ref ??3@YAXPAX@Z=00781d3b

DynamicVectorClass<HWND> _ModelessDialogs;
DynamicVectorClass<AcceleratorTracker> _Accelerators;
