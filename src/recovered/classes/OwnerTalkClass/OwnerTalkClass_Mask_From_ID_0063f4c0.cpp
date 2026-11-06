// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// unsigned char OwnerTalkClass::Unknown_0063F4C0(int id) (0x0063F4C0)
// Adopted from ra2-decomp OwnerTalkClass::Mask_From_ID (YR 0x00663D60).
// The mask of the connection with this ID; all bits (0xFF) for -1 or no match.
#include "shared/owner_talk.hpp"

unsigned char OwnerTalkClass::Unknown_0063F4C0(int id)
{
    unsigned char mask = 0;

    if (id == -1) {
        return 0xFF;
    }
    for (int i = 0; i < Connections.Count(); i++) {
        if (id == Connections[i]->ID) {
            mask = Connections[i]->Mask;
            break;
        }
    }
    if (mask == 0) {
        mask = 0xFF;
    }
    return mask;
}
