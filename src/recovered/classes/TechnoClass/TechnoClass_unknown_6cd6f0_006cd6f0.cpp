
// int TechnoClass::unknown_6cd6f0() (0x006CD6F0)
// The distance bonus of this object's height above the map's lowest level
// (0x0056A8A0), measured like 0x006C48F0: the levels divided by the rules'
// +0x1480, scaled by +0x1488 and limited to +0x1490, in leptons, combined
// with the levels times the geometry constant; 0 when slot 21 holds or the
// increment is 0. Never called (inlined everywhere).
// @ref ?Unknown_0056A8A0@MapClass@@QAEHXZ=0056a8a0
int TechnoClass::unknown_6cd6f0()
{
    if (unknown_slot21()) {
        return 0;
    }
    int increment = Rules->unknown_1480;
    if (increment == 0) {
        return 0;
    }
    double bonus = Rules->unknown_1488;
    Cell here = Coord_Cell(Center_Coord());
    UnknownCellClass *cell = (UnknownCellClass *)&Map[here];
    int lowest = Map.Unknown_0056A8A0();
    char level = cell->unknown_11b;
    double scaled = (level - lowest) / increment * bonus;
    double limit = Rules->unknown_1490;
    if (scaled >= limit) {
        scaled = Rules->unknown_1490;
    }
    int vertical = level * unknown_geometry_g;
    int horizontal = (int)scaled << 8;
    return (int)unknown_sqrt_4ba410((double)(horizontal * horizontal + vertical * vertical));
}
