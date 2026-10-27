// CCINIClass::Load (0x004697E0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

int CCINIClass::Load(Straw &file, bool withdigest, bool keep_comments)
{
    int result = INIClass::Load(file, keep_comments);
    Invalidate_Message_Digest();
    if (result && withdigest) {
        unsigned char digest[20];
        int length = Get_UUBlock("Digest", digest, sizeof(digest));
        if (length == 0) {
            return 2;
        }
        if (length > 0) {
            Clear("Digest");
            Calculate_Message_Digest();
            if (memcmp(digest, Digest, sizeof(digest)) != 0) {
                return 2;
            }
        }
    }
    return result;
}
