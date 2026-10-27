// char const *UnknownVocRef_00714A70::unknown_name() const -- 0x00714A70
// Purpose: the name of the referenced sound (0x00405150), "Invalid Voc"
// when there is none.
// Assumptions: the referenced class (+0x00) is unidentified.
// @ref ?unknown_name_405150@UnknownVoc_00714a70@@QBEPBDXZ=00405150
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c

struct UnknownVoc_00714a70 {
    char const *unknown_name_405150() const;    // 0x00405150
};
struct UnknownVocRef_00714a70 {
    UnknownVoc_00714a70 *Voc;               // +0x00
    char const *unknown_name() const;
};

char const *UnknownVocRef_00714a70::unknown_name() const
{
    if (Voc != 0) {
        return Voc->unknown_name_405150();
    }
    return "Invalid Voc";
}
