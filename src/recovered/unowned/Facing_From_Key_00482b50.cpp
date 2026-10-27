// Converts navigation keys to eight-way facing indices, ignoring modifier bits.
int __fastcall Facing_From_Key_00482b50(unsigned int key)
{
    switch (key & 0xfffff8ff) {
    case 0x25: return 6; // left: west
    case 0x27: return 2; // right: east
    case 0x26: return 0; // up: north
    case 0x28: return 4; // down: south
    case 0x24: return 7; // home: northwest
    case 0x21: return 1; // page up: northeast
    case 0x23: return 5; // end: southwest
    case 0x22: return 3; // page down: southeast
    }
    return -1;
}
