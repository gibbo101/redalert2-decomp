// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// int __fastcall Audio_Queue_Available(AudioQueue *queue) -- 0x00409240
// From ra2-decomp STM_AccessTotalBytes (YR 0x00409320).
// Purpose: the bytes queued to this queue that it has not committed yet
// (Queued minus Consumed, written with the twin's unsigned wrap test, which folds).
#include "shared/audio.hpp"

int __fastcall Audio_Queue_Available(AudioQueue *queue)
{
    unsigned int queued = queue->Queued;
    unsigned int consumed = queue->Consumed;
    if (queued < consumed) {
        return (0xFFFFFFFFu - consumed) + 1 + queued;
    }
    return queued - consumed;
}
