// int __stdcall unknown_table_lookup(UnknownOuter_00728b70 *object) -- 0x00728B70
// Purpose: an entry of the 4-column table at 0x007FBB78, indexed by the
// bytes at +0x12 (row) and +0x13 (column) of the record at object +0x04.
// Assumptions: owner, record and table meaning unknown.
// @ref ?unknown_table_7fbb78@@3PAY03HA=007fbb78

struct UnknownRecord_00728b70 {
    char unknown_00[0x12];
    unsigned char Row;                      // +0x12
    unsigned char Column;                   // +0x13
};
struct UnknownOuter_00728b70 {
    int unknown_00;
    UnknownRecord_00728b70 *Record;         // +0x04
};
extern int unknown_table_7fbb78[][4];

int __stdcall unknown_table_lookup(UnknownOuter_00728b70 *object)
{
    return unknown_table_7fbb78[object->Record->Row][object->Record->Column];
}
