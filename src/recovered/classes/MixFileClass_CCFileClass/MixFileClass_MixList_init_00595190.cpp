// MixFileClass::MixList (0x00A70CC0), the list every constructed archive joins. Its definition
// (last in the unit) emits the dynamic initializer 0x00595190, the atexit destructor 0x005951E0
// (guarded by bit 0 of 0x00A70CF0, as VC6 guards static data members) and, through the emitted
// List vtable, List's scalar deleting destructor 0x00595D60.
#include "shared/mix_file_class.hpp"
// @ref ??_7?$List@PAVMixFileClass@@@@6B@=007a6458
// @ref ??_G?$List@PAVMixFileClass@@@@UAEPAXI@Z=00595d60
// @ref _$S17=00a70cf0
// @ref ?MixList@MixFileClass@@2V?$List@PAVMixFileClass@@@@A=00a70cc0

List<MixFileClass *> MixFileClass::MixList;
