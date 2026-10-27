// Dynamic initializers of Tab.cpp's static buttons (0x006A0460 Buttons[25],
// 0x006A04C0, 0x006A0500, _$E) and their guarded atexit destructors
// (0x006A0490, 0x006A04E0, 0x006A0520; guard byte 0x00ABD904), emitted by
// these definitions.
#include "shared/tab.hpp"
// @ref ??0ShapeButtonClass@@QAE@XZ=00675020
// @ref ??1ShapeButtonClass@@UAE@XZ=006750f0
// @ref _atexit=0078298a
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918
// @ref ?unknown_button_abe400@TabClass@@2VShapeButtonClass@@A=00abe400
// @ref ?unknown_button_abe390@TabClass@@2VShapeButtonClass@@A=00abe390

ShapeButtonClass TabClass::Buttons[25];
ShapeButtonClass TabClass::unknown_button_abe400;
ShapeButtonClass TabClass::unknown_button_abe390;
// @ref _$E78=006a0490
// @ref _$E84=006a04e0
// @ref _$E89=006a0520
// @ref _$S79=00abd904
