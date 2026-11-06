// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// int __fastcall Audio_Ring_Fill_Available(AudioStream *ring) -- 0x00408C60
// From ra2-decomp STM_StreamTotalBytesTillFull (YR 0x00408D40).
// Purpose: free bytes queued for filling that are not yet consumed.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Fill_Available(AudioStream *ring)
{
    return Audio_Queue_Available(&ring->Queues[0]);
}
