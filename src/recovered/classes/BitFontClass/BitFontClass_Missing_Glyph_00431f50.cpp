// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void *BitFontClass::Missing_Glyph(unsigned short *color) (0x00431F50): the fallback glyph (unknown_08),
// flipping the colour with 0x5555 when one is given. From ra2-decomp BitFont::FUN_00434790 (YR 0x00434790).
#include "shared/text_print.hpp"

void *BitFontClass::Missing_Glyph(unsigned short *color)
{
    if (color) *color ^= 0x5555;
    return unknown_08;
}
