// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// void Planning_Unknown_617af0() (0x00617AF0)
// Adopted from ra2-decomp FUN_0063AD50 (YR 0x0063AD50).
// Connects the remembered node to the selection: with objects selected,
// every selected techno without a path, and every member of the last node
// of each selected path, gets a connect event (0x2A) to the node's target
// object, then help message 3; with none, the node is kept in
// unknown_node_a766b0 and help message 4 shown.
#include "shared/planning.hpp"
// @ref ?Planning_Unknown_617af0@@YAXXZ=00617af0
// @ref ??0EventClass@@QAE@HHVTargetClass@@0@Z=004b6090
// @ref ?Unknown_0062E670@@YG_NVEventClass@@@Z=0062e670
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

// AbstractClass::Is_Techno as ra2-decomp writes it (not in this unit's
// ObjectClass declaration).
static inline bool Is_Techno(ObjectClass const *object)
{
    if (object == 0) return false;
    unsigned char flag = object->AbstractFlags.IsTechno;
    return flag != 0;
}

static inline void Connect_Node_Target(PlanningNodeClass *node, TechnoClass *techno)
{
    EventClass packet = node->Member_Event(0);
    AbstractClass *target = ((PlanningEventTargets *)&packet)->First_Target_Object();
    if (target) {
        EventClass event(unknown_player_a35db4->ArrayIndex, 0x2A, TargetClass(techno), TargetClass(target));
        Unknown_0062E670(event);
    }
}

void Planning_Unknown_617af0()
{
    PlanningNodeClass *selected = Planning_Get_a766f8();
    Planning_Set_a766f8(0);
    int count = unknown_objects_a40c60.Count();
    if (count > 0) {
        DynamicVectorClass<TechnoClass *> units;
        for (int i = 0; i < count; ++i) {
            ObjectClass *object = unknown_objects_a40c60[i];
            if (Is_Techno(object)) {
                TechnoClass *techno = (TechnoClass *)object;
                PlanningTokenClass *token = Planning_Token(techno);
                if (token) {
                    PlanningNodeClass *last = token->Last_Node();
                    if (!last) {
                        units.Add(techno);
                    } else {
                        int members = last->Get_Member_Count();
                        for (int j = 0; j < members; ++j) {
                            TechnoClass *owner = last->Member_Owner(j);
                            if (units.ID(owner) == -1) units.Add(owner);
                        }
                    }
                } else {
                    units.Add(techno);
                }
            }
        }
        int total = units.Count();
        for (int j = 0; j < total; ++j) {
            TechnoClass *techno = units[j];
            Connect_Node_Target(selected, techno);
        }
        if (total > 0) Planning_Help(3);
    } else {
        unknown_node_a766b0 = selected;
        Planning_Help(4);
    }
}
