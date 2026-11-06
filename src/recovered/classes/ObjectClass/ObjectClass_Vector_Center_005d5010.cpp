// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// CoordStruct __fastcall Vector_Center_005d5010(DynamicVectorClass<ObjectClass *> const &list) (0x005D5010)
// Adopted from ra2-decomp Vector_Center (YR 0x005F6790).
// The mean coordinate of the objects in the list. Nothing calls it directly.
#include "shared/object.hpp"
#include "shared/vector_class.hpp"

CoordStruct __fastcall Vector_Center_005d5010(DynamicVectorClass<ObjectClass *> const &list)
{
    CoordStruct center = CoordStruct(0, 0, 0);
    int count = list.Count();
    for (int i = count - 1; i >= 0; i--) {
        center += list[i]->Position_Coord_004f3f40();
    }
    center.X /= count;
    center.Y /= count;
    center.Z /= count;
    return center;
}
