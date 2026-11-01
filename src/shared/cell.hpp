// CellClass: one map cell (Cell.cpp, 0x00470490 unit: members 0x00470680-
// 0x0047D08F; RTTI vtables 0x0079DB04 primary (24 slots, AbstractClass's
// plus overrides), 0x0079DAE8 IRTTITypeInfo at +4, 0x0079DAE0 INoticeSink,
// 0x0079DAD8 INoticeSource). Moved out of shared/map.hpp, where a stand-in
// with placeholder slots stood for it.
//
// Layout (from the constructor 0x00470F10, the NoInitClass constructor
// 0x00470680, the destructor 0x00470E80, Load 0x00478CB0 and Save
// 0x00478ED0; names are hypotheses unless stated):
//   +0x000  AbstractClass (0x24)
//   +0x024  Cell MapCoords      the zero cell when constructed
//   +0x028  DynamicVectorClass<FoggedObjectClass *> *FoggedObjects (owned;
//           saved as a count and pointers, swizzled)
//   +0x02C  CellClass *unknown_2c     (swizzled; bridge owner cell)
//   +0x030  void *unknown_30          (swizzled)
//   +0x034  LightConvertClass *unknown_34  the tile drawer (Westwood's Drawer;
//           counted at its +0x194, Init_Drawer 0x004790F0)
//   +0x038  int IsoTileIndex          0xFFFF when constructed
//   +0x03C  TagClass *unknown_3c (swizzled; the cell tag: counted at +0x2C,
//           cells with one are listed in the map at 0x00833638)
//   +0x040  void * (swizzled)
//   +0x044  int OverlayIndex, +0x048 int SmudgeIndex (-1)
//   +0x04C  int unknown_4c            (cleared by the NoInit constructor)
//   +0x050..+0x064  int unknown_50[6] (-1)
//   +0x068  Rect unknown_68           (0)
//   +0x078  unsigned int unknown_78   per-house bit mask
//   +0x07C  short unknown_7c[24]      per-house counters (zero-filled)
//   +0x0AC  int unknown_ac[12]        (zero-filled)
//   +0x0DC  int, +0x0E0 void * (swizzled; Set_unknown_e0)
//   +0x0E4  ObjectClass *OccupierPtr, +0x0E8 ObjectClass *AltOccupierPtr
//           (swizzled; chained through ObjectClass +0x30)
//   +0x0EC  int unknown_ec            the land type (index into Ground,
//           0x00850EA0)
//   +0x0F0  double unknown_f0         (Reduce_f0 0x0047CEC0)
//   +0x0F8  void * (swizzled), +0x0FC owned object (deleted by the destructor)
//   +0x100  int, +0x104 int (0x10000)
//   +0x108  short, +0x10A..+0x114 short (1000), +0x116 short (-1)
//   +0x118..+0x122  chars (+0x118 -1, +0x120/+0x121 -2; +0x11C blocks
//           smudges, +0x11E OverlayData, +0x11F SmudgeData, +0x122 adjacent
//           terrain count)
//   +0x124, +0x128  unsigned char
//   +0x12C  flag bits (bits 0..4 cleared when constructed)
//   +0x130  int (1), +0x134 int, +0x138 bool, +0x13C int
//   +0x140  flag bits (bits 0..22 cleared when constructed)
//   size 0x148
#ifndef RA2_SHARED_CELL_HPP
#define RA2_SHARED_CELL_HPP

// Preserve the original provider dependencies for all existing cell.hpp users.
#include "shared/abstract_type.hpp"
#include "shared/cell_class.hpp"

#endif
