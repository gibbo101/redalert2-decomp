// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// Adapted for base RA2 0074E070 from ra2-decomp GAMEMD 007937B0,
// pinned 4453ab030c86d8586992bfa7425ef7f39e3fb8d4; shared names/ABI preserved.

// @ref ??_C@_09NGKE@?7?$CFd?5?$CG?5?$CFd?6?$AA@=007feefc
// @ref ??_C@_0BG@MIFH@Connection?5pairs?4?4?4?4?6?$AA@=007fef08
// @ref ??_C@_0CL@NDDD@Connection?5order?5?$DN?5?$CFd?0?5?$CFd?0?5?$CFd?0?5?$CF@=007fef20
// Prioritizes active player slots by firewall weight and writes every unordered pair (0074E070).
#include "shared/unknown_player_entry.hpp"
#include "shared/session_state.hpp"
#include "shared/firewall_settings.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"
namespace seed_005c9320 { unsigned int __fastcall FUN_005c9320(int entry); }

int __fastcall Unknown_0074e070(void *output)
{
	int (*pairs)[2] = (int (*)[2])output;
	int order[8];
	memset(order, 0, sizeof(order));
	int i = 0;
	int * out = order;
	for (; i < 8; i++) {
		if ((unsigned char)seed_005c9320::FUN_005c9320((int)unknown_player_slots_a3fa98[i])) {
			*out++ = i;
		}
	}
	for (int a = 0; a < unknown_players_a3fa7c.Count(); a++) {
		for (int b = 0; b < unknown_players_a3fa7c.Count() - 1; b++) {
			int cur_value = unknown_session_a3d298.unknown_299c.unknown[order[b]];
			int next_value = unknown_session_a3d298.unknown_299c.unknown[order[b + 1]];
			if (unknown_firewall_a71b18.Connection_Weight_005baee0(cur_value) < unknown_firewall_a71b18.Connection_Weight_005baee0(next_value)) {
				int temp = order[b];
				order[b] = order[b + 1];
				order[b + 1] = temp;
			}
		}
	}
	Debug_Printf("Connection order = %d, %d, %d, %d, %d, %d\n", order[0], order[1], order[2], order[3], order[4], order[5]);
	int n = 0;
	Debug_Printf("Connection pairs....\n");
	for (int x = 0; x < unknown_players_a3fa7c.Count(); x++) {
		for (int y = x + 1; y < unknown_players_a3fa7c.Count(); y++) {
			pairs[n][0] = order[x];
			pairs[n][1] = order[y];
			Debug_Printf("\t%d & %d\n", order[x], order[y]);
			n++;
		}
	}
	return n;
}
