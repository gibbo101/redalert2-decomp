// The 12 x 8 table at 0x007E00C4 and the row of it that best matches two
// rows: no 2 of either row where it has a 1, the most shared 1s; -1 when no
// row qualifies (0x0056A900, MapClass unit; TeamTypeClass 0x006C0180 passes
// two movement zones). Kept apart from shared/map.hpp so callers outside
// the map units do not instantiate the map's vector classes.
#ifndef RA2_SHARED_ZONE_TABLE_HPP
#define RA2_SHARED_ZONE_TABLE_HPP

extern int unknown_table_7e00c4[12][8];
int __fastcall Unknown_0056A900(int row1, int row2);

#endif
