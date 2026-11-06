// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void MonoClass::Print(char const *text) (0x0059E6D0)
// Adopted from ra2-decomp DebugPage::Print_Raw (YR 0x005BD0D0).
// Writes text at the cursor inside the window (clipped to the window width)
// in the current attribute, moving the cursor (a newline returns it to the
// window's left edge one row down), then redraws the written span.
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?Map_Character@MonoClass@@QBEDD@Z=0059e960
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

void MonoClass::Print(char const *text)
{
    if (unknown_mono_enabled_a70f0a) {
        int cx = X;
        int start = WindowX + cx;
        int row = WindowY + Y;
        int limit = WindowWidth + WindowX;
        Changed = false;
        int end = (int)strlen(text) + start;
        if (end > limit) {
            end = limit;
        }
        for (int col = start, i = 0; col < end; col++, i++) {
            char c = text[i];
            Characters[col][row] = Map_Character(c);
            Attributes[col][row] = Attribute;
            if (c == '\n') {
                X = 0;
                Y++;
            } else {
                X++;
            }
        }
        Refresh(start, row, end - start, 1);
    }
}
