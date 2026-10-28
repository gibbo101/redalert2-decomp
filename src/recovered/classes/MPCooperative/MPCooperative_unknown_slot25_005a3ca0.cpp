// void MPCooperative::unknown_slot25(int kind, char *text) -- 0x005A3CA0
// Kind 1 carries the campaign AI settings: a round count, then per round one comma-separated
// value per player for each of the two per-player lists (-1 where a value is missing).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
// @ref _strtok=00782ec2
// @ref _atoi=00782d72
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/crt_tokens.hpp"

void MPCooperative::unknown_slot25(int kind, char *text)
{
    if (kind == 1) {
        int rounds = atoi(strtok(text, ","));
        int i;
        for (i = 0; i < 8; i++) {
            int capacity = unknown_1a8[i].Length();
            unknown_1a8[i].Clear();
            unknown_1a8[i].Resize(capacity);
            capacity = unknown_268[i].Length();
            unknown_268[i].Clear();
            unknown_268[i].Resize(capacity);
        }
        for (int round = 0; round < rounds; round++) {
            for (i = 0; i < 8; i++) {
                char *token = strtok(0, ",");
                if (token != 0) {
                    unknown_1a8[i].Add(atoi(token));
                } else {
                    unknown_1a8[i].Add(-1);
                }
                token = strtok(0, ",");
                if (token != 0) {
                    unknown_268[i].Add(atoi(token));
                } else {
                    unknown_268[i].Add(-1);
                }
            }
        }
    }
}
