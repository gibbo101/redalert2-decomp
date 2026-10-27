// void unknown_6c3a90(CoordStruct const &from, CoordStruct const &to, int color) (0x006C3A90)
// Draws the quarter of the line from `from` towards `to` that starts at `from`,
// in a color (0x006C3A90; TechnoClass slot 66; hypothesis).
void __fastcall unknown_6c3a90(CoordStruct const &from, CoordStruct const &to, int color)
{
    CoordStruct quarter = (from + from + from + to) / 4;
    if (from.Z > quarter.Z) {
        unknown_tactical_83996c->unknown_slot24(from, quarter, color, 0);
    } else {
        unknown_tactical_83996c->unknown_slot24(quarter, from, color, 0);
    }
}
