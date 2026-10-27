// BuildingClass 0x00452F50: releases the building's occupants (codex2 R2485).
// Names and pointer constness are hypotheses.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/infantry.hpp"
#include "shared/team.hpp"
#include "shared/crt_memory.hpp"

extern int unknown_84ed10; // original packed default Cell at 0x0084ED10
// @ref ?unknown_84ed10@@3HA=0084ed10
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@HH@Z=006b8fb0
// @ref ?Unknown_006D9610@TechnoClass@@=006d9610

void BuildingClass::unknown_452f50(int control)
{
    if (unknown_554.Count() == 0) return;

    CoordStruct destination = unknown_geometry_l;
    Cell selected;
    memcpy(&selected, &unknown_84ed10, sizeof(selected));
    int width = Type->Width();
    int height = Type->Foundation_Height(false);
    bool found = false;
    Cell probe = unknown_slot104();
    probe.X = (short)((unsigned int)(int)probe.X + (unsigned int)width);
    probe.Y = (short)((unsigned int)(int)probe.Y + (unsigned int)height);
    InfantryClass *occupant = unknown_554[0];

    int entry_result = occupant->unknown_slot101(&Map[probe], -1, -1, 0, 1);
    while (entry_result != 0) {
        if ((int)probe.Y <= (int)unknown_slot104().Y - 1) goto after_first_edge;
        probe.Y = (short)(probe.Y - 1);
        entry_result = occupant->unknown_slot101(&Map[probe], -1, -1, 0, 1);
    }
    found = true;
    selected = probe;
after_first_edge:
    probe = unknown_slot104();
    probe.X = (short)((unsigned int)(int)probe.X + (unsigned int)width);
    probe.Y = (short)((unsigned int)(int)probe.Y + (unsigned int)height);
    while (!found && (int)probe.X > (int)unknown_slot104().X - 1) {
        probe.X = (short)(probe.X - 1);
        if (occupant->unknown_slot101(&Map[probe], -1, -1, 0, 1) == 0) {
            found = true;
            selected = probe;
        }
    }

    probe = unknown_slot104();
    probe.X = (short)(probe.X - 1);
    probe.Y = (short)(probe.Y - 1);
    while (!found && (int)probe.X < (int)((unsigned int)(int)unknown_slot104().X + (unsigned int)width)) {
        probe.X = (short)(probe.X + 1);
        if (occupant->unknown_slot101(&Map[probe], -1, -1, 0, 1) == 0) {
            found = true;
            selected = probe;
        }
    }

    probe = unknown_slot104();
    probe.X = (short)(probe.X - 1);
    probe.Y = (short)(probe.Y - 1);
    while (!found && (int)probe.Y < (int)((unsigned int)(int)unknown_slot104().Y + (unsigned int)height)) {
        probe.Y = (short)(probe.Y + 1);
        if (occupant->unknown_slot101(&Map[probe], -1, -1, 0, 1) == 0) {
            selected = probe;
            found = true;
        }
    }
    if (!found) {
        Unknown_004536D0(0);
        return;
    }

    destination = Map[selected].Center_Coord();
    unknown_a40774 = (int)((unsigned int)unknown_a40774 + 1u);
    for (int index = (int)((unsigned int)unknown_554.Count() - 1u); index >= 0; --index) {
        InfantryClass *member = unknown_554[index];
        if (member->unknown_slot53(&destination, 0)) {
            member->unknown_slot220(0);
            member->unknown_slot87(Center_Coord(), true, true);
            if ((unsigned char)control != 0) {
                TeamClass *team = member->Team;
                if (team) team->Unknown_006B8FB0(member, -1, 0);
                member->unknown_slot116(15, false);
            }
        } else {
            member->unknown_slot60();
        }
    }
    unknown_a40774 = (int)((unsigned int)unknown_a40774 - 1u);
    DynamicVectorClass<InfantryClass *> &occupants = unknown_554;
    int capacity = occupants.Length();
    occupants.Clear();
    occupants.Resize(capacity, 0);
    Unknown_006D9610(unknown_slot105());
}
