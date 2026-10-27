#pragma once

// Observed component widths and minimum view layouts; original class names unknown.
struct SignedWordPair {
    short x;
    short y;
};
struct SignedIntPair {
    int x;
    int y;
};
typedef char SignedWordPair_size_check[(sizeof(SignedWordPair) == 4) ? 1 : -1];
typedef char SignedIntPair_size_check[(sizeof(SignedIntPair) == 8) ? 1 : -1];

class Div256PairSource_00413770 {
public:
    int x;
    int y;
    SignedWordPair* CopyDiv256PairAsSignedWords_00413770(SignedWordPair* output) const;
};
class Div256PairSource_004c2040 {
public:
    unsigned char unknown_0x00[0x34];
    int x;
    int y;
    SignedWordPair* CopyDiv256PairAsSignedWords_004c2040(SignedWordPair* output) const;
};
class ProjectedIntPair_006a2740 {
public:
    int x;
    int y;
    ProjectedIntPair_006a2740* ProjectWrappedIntegerPair_006a2740(int input_x, int input_y);
};
// The first two methods explicitly project ECX-source/stack-output/RET4.
// A hidden aggregate result in the developer API remains possible, not established.
// The projection member uses observed ECX-output/two scalar stack words/RET8.
// The second projection is a stack-only output/input-pointer function/RET8;
// caller ECX is unused by its original body. Original static/member API is unknown.
