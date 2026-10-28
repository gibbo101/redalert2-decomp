// The command unit's globals: the hotkey index (initializer 0x0040BC80 zeroes
// unknown_hotkeys_832380 (0x00832380) and registers its atexit destructor
// 0x0040BCB0) and the registered commands (initializer 0x0040BCE0, atexit
// 0x0040BD20; vtables 0x0079A81C/0x0079A83C, RTTI DynamicVectorClass<CommandClass const *>).
// The list's template members are this unit's copies at 0x0040BD60-0x0040BFF0 (accepted
// as standalone members); its deleting destructors 0x0040C020/0x0040C070 are claimed here.
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/command.hpp"
// @ref ?unknown_hotkeys_832380@@3V?$IndexClass@HPAVCommandClass@@@@A=00832380
// @ref _atexit=0078298a
// @ref _$E2=0040bcb0
// @ref ??8?$VectorClass@PBVCommandClass@@@@UBE_NABV0@@Z=0040bdc0
// @ref ??_7?$DynamicVectorClass@PBVCommandClass@@@@6B@=0079a81c
// @ref ??_7?$VectorClass@PBVCommandClass@@@@6B@=0079a83c
// @ref ?Clear@?$DynamicVectorClass@PBVCommandClass@@@@UAEXXZ=0040bd60
// @ref ?Clear@?$VectorClass@PBVCommandClass@@@@UAEXXZ=0040beb0
// @ref ?Fetch@?$VectorClass@PBVCommandClass@@@@UBEPBVCommandClass@@H@Z=0040bdb0
// @ref ?ID@?$DynamicVectorClass@PBVCommandClass@@@@UAEHABQBVCommandClass@@@Z=0040bff0
// @ref ?ID@?$DynamicVectorClass@PBVCommandClass@@@@UAEHPBQBVCommandClass@@@Z=0040bd90
// @ref ?ID@?$VectorClass@PBVCommandClass@@@@UAEHABQBVCommandClass@@@Z=0040bee0
// @ref ?ID@?$VectorClass@PBVCommandClass@@@@UAEHPBQBVCommandClass@@@Z=0040bf20
// @ref ?Resize@?$DynamicVectorClass@PBVCommandClass@@@@UAE_NHPBQBVCommandClass@@@Z=0040bf40
// @ref ?Resize@?$VectorClass@PBVCommandClass@@@@UAE_NHPBQBVCommandClass@@@Z=0040be00
// @ref ?unknown_commands_832358@@3V?$DynamicVectorClass@PBVCommandClass@@@@A=00832358
// @ref _$E7=0040bd20

IndexClass<int, CommandClass *> unknown_hotkeys_832380;
DynamicVectorClass<CommandClass const *> unknown_commands_832358;
