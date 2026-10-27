// int TaskForceClass::Max_Tech_Level() const (0x006B7140)
// The highest TechLevel of the entry types; a type with -1 counts as 11 in
// a game mode other than 0.
#include "shared/task_force.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

int TaskForceClass::Max_Tech_Level() const
{
    int level = 0;
    for (int index = 0; index < CountEntries; index++) {
        int techlevel = Entries[index].Type->TechLevel;
        if (techlevel > level) {
            level = techlevel;
        } else if (techlevel == -1 && unknown_game_mode_a3d298 != 0) {
            level = 11;
        }
    }
    return level;
}
