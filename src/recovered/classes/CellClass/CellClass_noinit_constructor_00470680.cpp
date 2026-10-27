// CellClass::CellClass(NoInitClass const &noinit) (0x00470680): installs the
// vtables and clears +0x34 and +0x4C (Load builds the cell in place).
#include "shared/cell.hpp"
// @ref ??_7CellClass@@6BIPersistStream@@@=0079db04
// @ref ??_7CellClass@@6BIRTTITypeInfo@@@=0079dae8
// @ref ??_7CellClass@@6BINoticeSink@@@=0079dae0
// @ref ??_7CellClass@@6BINoticeSource@@@=0079dad8
// @ref ?What_Am_I@CellClass@@UAGHXZ=0047cf70
// @ref ?Kind_Of@CellClass@@UBEHXZ=0047cf80
// @ref ?Size_Of@CellClass@@UBEHXZ=0047cf90
// @ref ??_GCellClass@@UAEPAXI@Z=0047cfa0
// @ref ??_ECellClass@@UAEPAXI@Z=0047cfa0

CellClass::CellClass(NoInitClass const &noinit) :
    AbstractClass(noinit),
    unknown_68(noinit)
{
    unknown_34 = 0;
    unknown_4c = 0;
}
