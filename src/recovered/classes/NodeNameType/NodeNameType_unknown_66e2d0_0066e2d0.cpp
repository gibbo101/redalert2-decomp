// Sets the country; -2 (random) stores country 0 and marks +0x4F.
void NodeNameType::unknown_66e2d0(int value)
{
    if (value == -2) {
        unknown_4b = 0;
        unknown_4f = -2;
    } else {
        unknown_4b = value;
        unknown_4f = -1;
    }
}
