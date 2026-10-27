// void TeamTypeClass::unknown_func_6c0110(int value) const (0x006C0110)
// Passes value to TeamClass::unknown_func_6bd990 of every team of this type.
#include "shared/team_type.hpp"
#include "shared/team.hpp"
// @ref ?unknown_func_6bd990@TeamClass@@QAEXH@Z=006bd990

void TeamTypeClass::unknown_func_6c0110(int value) const
{
    for (int index = 0; index < Teams.Count(); index++) {
        if (Teams[index]->Class == this) {
            Teams[index]->unknown_func_6bd990(value);
        }
    }
}
