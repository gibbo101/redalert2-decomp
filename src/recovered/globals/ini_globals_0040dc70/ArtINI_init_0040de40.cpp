// The INI globals unit (0x0040DC70): after its header statics, the five
// CCINIClass objects it defines. Each gets a dynamic initializer (the inline
// CCINIClass constructor, then atexit) and an atexit destructor that calls
// ~INIClass (0x0050B8D0); the other drafts of this plan at 0x0040DED0-
// 0x0040E150 are emitted by these definitions, as are the GenericNode and
// INI list helpers at 0x0040E160-0x0040E300 (kept as their own regions).
// @ref ?ArtINI@@3VCCINIClass@@A=008397f0
// @ref ?unknown_ini_839860@@3VCCINIClass@@A=00839860
// @ref ?unknown_ini_8397a0@@3VCCINIClass@@A=008397a0
// @ref ?unknown_ini_8396e0@@3VCCINIClass@@A=008396e0
// @ref ?unknown_ini_839740@@3VCCINIClass@@A=00839740
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??0GenericNode@@QAE@XZ=0040e160
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??1INIClass@@UAE@XZ=0050b8d0
#include "shared/ccini_class.hpp"

CCINIClass ArtINI;              // 0x008397F0
CCINIClass unknown_ini_839860;  // 0x00839860
CCINIClass unknown_ini_8397a0;  // 0x008397A0
CCINIClass unknown_ini_8396e0;  // 0x008396E0
CCINIClass unknown_ini_839740;  // 0x00839740
