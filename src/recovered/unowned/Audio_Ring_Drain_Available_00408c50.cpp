// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// int __fastcall Audio_Ring_Drain_Available(AudioStream *ring) -- 0x00408C50
// From ra2-decomp STM_StreamTotalBytesIn (YR 0x00408D30).
// Purpose: bytes queued for draining that are not yet consumed.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Drain_Available(AudioStream *ring)
{
    return Audio_Queue_Available(&ring->Queues[1]);
}
