// The per-palette colour scheme lists of the palette-name loader (unit 0x00602FD0 continued; RA2 only): a named
// list of the colour schemes built for one palette file (0x104 bytes; the value type of the scheme hash table,
// HashObject<HashString, SchemeNode *>). Names are hypotheses.
// @ref ??1ColorScheme@@QAE@XZ=00663bb0
// @ref ??3@YAXPAX@Z=00781d3b
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/color_scheme.hpp"
#include "shared/crt_string.hpp"

class SchemeNode {
public:
    // A node for the palette file name and its scheme list (0x00603200).
    SchemeNode(char const *name, DynamicVectorClass<ColorScheme *> *schemes);
    // Two identical out-of-line copies that delete every scheme and the list (0x00603240, 0x00603320; only the
    // second has callers).
    void unknown_603240();
    void unknown_603320();
    // Frees the current list and takes another (0x006032A0; the free expands inline).
    void unknown_6032a0(DynamicVectorClass<ColorScheme *> *schemes);

    char Name[0x100];                               // +0x000
    DynamicVectorClass<ColorScheme *> *Schemes;     // +0x100
};

SchemeNode::SchemeNode(char const *name, DynamicVectorClass<ColorScheme *> *schemes)
{
    strcpy(Name, name);
    Schemes = schemes;
}
