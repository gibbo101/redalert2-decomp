// Unknown42C350Table::Find(Cell const &) (0x0042C350)
// Finds the 16-byte record whose cell (+0x04) equals the given cell; null when absent.
#include "shared/coord.hpp"
struct Unknown42C350Record {
    int unknown_00;
    ::Cell Cell;
    int unknown_08;
    int unknown_0c;
};
struct Unknown42C350Table {
    Unknown42C350Record *Find(Cell const &cell) const;
    char unknown_pad0[8];
    Unknown42C350Record *Data;   // +0x08
    char unknown_pad1[8];
    int Count;                      // +0x14
};
Unknown42C350Record *Unknown42C350Table::Find(Cell const &cell) const
{
    int index = 0;
    if (0 < Count) {
        short x = cell.X;
        Cell const *entry = &Data->Cell;
        do {
            if (x == entry->X && cell.Y == entry->Y) {
                return &Data[index];
            }
            index++;
            entry = (Cell const *)((char const *)entry + 16);
        } while (index < Count);
    }
    return 0;
}
