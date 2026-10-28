// Sets one of the 50 local variables at +0x1A12 (TagClass 0x006B4250 is told
// of a change) and returns its old value; false for an index out of range.
bool UnknownIDSource::unknown_661560(unsigned index, bool value)
{
    if (index < 50) {
        bool old = LocalVariables[index].Value;
        if (old != value) {
            LocalVariables[index].Value = value;
            unknown_222e = true;
            TagClass::unknown_func_6b4250(index);
        }
        return old;
    }
    return false;
}
