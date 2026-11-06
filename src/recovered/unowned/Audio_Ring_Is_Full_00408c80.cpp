// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// int __fastcall Audio_Ring_Is_Full(AudioStream *ring) -- 0x00408C80
// From ra2-decomp STM_StreamFull (YR 0x00408D60).
// Purpose: whether the fill queue has no free bytes left.
#include "shared/audio.hpp"

int __fastcall Audio_Ring_Is_Full(AudioStream *ring)
{
    return Audio_Ring_Fill_Available(ring) == 0;
}
