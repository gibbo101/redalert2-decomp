// bool UnknownSessionState::Unknown_006728D0(int color) (0x006728D0)
// True when a player's colour (0x66E2A0's +0x57/+0x53 sentinel, -2 for random) or one of the eight computer colours equals color; -2 is never taken.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"

bool UnknownSessionState::Unknown_006728D0(int color)
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
