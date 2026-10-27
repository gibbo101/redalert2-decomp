// int MapClass::Unknown_0054FA60(Cell const &cell) (0x0054FA60)
// The +0x02 value of the +0x64 element of a cell (index clamped by
// 0x0054FAB0, expanded inline).
#include "shared/map.hpp"

int MapClass::Unknown_0054FA60(Cell const &cell)
{
    return unknown_64[Unknown_0054FAB0(cell)].unknown_02;
}
