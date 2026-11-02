#define RA2_COORD_EQUAL_MEMBER
// void Unknown_00613E40() (0x00613E40)
// A Prog_End shutdown step of the planning mode: forwards to 0x00613E50 (a tail jump).
// @ref ?Unknown_00613E50@@YAXXZ=00613e50
#include "shared/planning.hpp"

void Unknown_00613E50();

void Unknown_00613E40()
{
    Unknown_00613E50();
}
