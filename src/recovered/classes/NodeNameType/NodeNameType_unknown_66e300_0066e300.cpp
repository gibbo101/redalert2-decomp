// Sets the colour; -2 (random) stores colour -1 and marks +0x57.
void NodeNameType::unknown_66e300(int value)
{
    if (value == -2) {
        unknown_53 = -1;
        unknown_57 = -2;
    } else {
        unknown_53 = value;
        unknown_57 = -1;
    }
}
