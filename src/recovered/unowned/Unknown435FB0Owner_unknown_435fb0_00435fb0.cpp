// Unknown435FB0Owner::unknown_435fb0() (0x00435FB0)
// Detaches the target at +0x2C (clearing two of its fields), then resets the owner and its +0x3C sub-object.
// @ref ?unknown_405fe0@Unknown435FB0Sub@@QAEXXZ=00405fe0
struct Unknown435FB0Target {
    char unknown_pad[0x38];
    int unknown_38;
    char unknown_pad2[0x2c];
    char unknown_68;
};
struct Unknown435FB0Sub { void unknown_405fe0(); };
struct Unknown435FB0Owner {
    void unknown_435fb0();
    char unknown_pad0[0x24];
    int unknown_24;
    int unknown_28;
    Unknown435FB0Target *unknown_2c;
    char unknown_pad1[0xc];
    Unknown435FB0Sub unknown_3c;
    char unknown_pad2[0x14];
    int unknown_54;
    char unknown_58;
};
void Unknown435FB0Owner::unknown_435fb0()
{
    if (unknown_2c != 0) {
        unknown_2c->unknown_38 = 0;
        unknown_2c->unknown_68 = 0;
    }
    unknown_58 = 1;
    unknown_24 = 0;
    unknown_2c = 0;
    unknown_28 = 0;
    unknown_3c.unknown_405fe0();
    unknown_54 = 0;
}
