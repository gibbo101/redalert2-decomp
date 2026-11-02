// The per-palette colour scheme lists of the palette-name loader (unit 0x00602FD0 continued; RA2 only): a named
// list of the colour schemes built for one palette file (0x104 bytes; the value type of the scheme hash table,
// HashObject<HashString, SchemeNode *>). Names are hypotheses.
// @ref ??1ColorScheme@@QAE@XZ=00663bb0
// @ref ??_7?$DynamicVectorClass@VHSVClass@@@@6B@=007a7b58
// @ref ??_7?$VectorClass@VHSVClass@@@@6B@=007a7bf8
// @ref ??_7?$DynamicVectorClass@PAD@@6B@=0079e55c
// @ref ??_7?$VectorClass@PAD@@6B@=0079e57c
// @ref ??0?$VectorClass@VHSVClass@@@@QAE@IPBVHSVClass@@@Z=00605da0
// @ref ??3@YAXPAX@Z=00781d3b
#define VECTOR_IMPLEMENT_ALL
#define RGB_DECLARE_DEFAULT_CONSTRUCTOR
#include "shared/color_scheme.hpp"
#include "shared/crt_string.hpp"

class SchemeNode {
public:
    // A node for the palette file name and its scheme list (0x00603200).
    SchemeNode(char const *name, DynamicVectorClass<ColorScheme *> *schemes);
    // Frees the schemes and the list (0x00603240: the destructor, Free expanded inline).
    ~SchemeNode();
    // Deletes every scheme and the list (0x00603320, out of line where a caller's budget runs out).
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
