// Ten-byte per-cell subzone record, from native Reset_Subzone00563D80.
// The record name follows the reference; the original nonpolymorphic type name is unknown.
#ifndef RA2_SHARED_CELL_SUBZONE_HPP
#define RA2_SHARED_CELL_SUBZONE_HPP
struct CellSubzoneStruct {
    short SubzoneID[3];
    short ZoneID;
    unsigned char Height;
};
typedef char CellSubzoneStruct_size_10[(sizeof(CellSubzoneStruct) == 10) ? 1 : -1];
#endif
