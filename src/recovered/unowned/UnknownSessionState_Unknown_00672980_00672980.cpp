// void UnknownSessionState::Unknown_00672980() (0x00672980)
// Draws random colours (0-7) from the scenario's generator until one is not in use. Unknown_006728D0 is inlined here
// (its own copy, 0x006728D0, is a separate unit), so this unit defines it inline.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

inline bool UnknownSessionState::Unknown_006728D0(int color)
{
    if (color != -2) {
        int i;
        for (i = 0; i < Players.Count(); i++) {
            UnknownPlayerEntry *entry = Players[i];
            int value;
            if (entry->unknown_57 == -2 && entry->unknown_53 == -1) {
                value = -2;
            } else {
                value = entry->unknown_53;
            }
            if (value == color) {
                return true;
            }
        }
        for (i = 0; i < 8; i++) {
            if (AIColor[i] == color) {
                return true;
            }
        }
    }
    return false;
}

void UnknownSessionState::Unknown_00672980()
{
    int color;
    do {
        color = unknown_id_source_a3d290->Random()(0, 7);
    } while (Unknown_006728D0(color));
}
