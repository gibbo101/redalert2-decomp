// CCINIClass::Save (0x00469A00).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

int CCINIClass::Save(Pipe &pipe, bool withdigest)
{
    if (!withdigest) {
        return INIClass::Save(pipe);
    }
    Clear("Digest");
    Calculate_Message_Digest();
    Put_UUBlock("Digest", Digest, sizeof(Digest));
    int result = INIClass::Save(pipe);
    Clear("Digest");
    return result;
}
