#ifndef RA2_SHARED_WOL_LADDER_LIST_CELL_HPP
#define RA2_SHARED_WOL_LADDER_LIST_CELL_HPP
#include "shared/wide_string.hpp"
// Non-polymorphic list-cell value used by CNetUtilEventSink::OnLadderList.
// Name is a purpose-based hypothesis; no original class name/RTTI is known.
// Constructor 0x005DE940 calls WideString's default constructor at +4/+8,
// then writes all four scalar fields. Uses in 0x0075D330 confirm Flags/Text.
struct WolLadderListCell {
    WolLadderListCell();
    int Flags;                  // +0x00
    WideString Text;            // +0x04
    WideString Secondary;       // +0x08
    int unknown_0c;
    int unknown_10;
    int unknown_14;
};
#endif
