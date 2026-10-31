// WOL API Ladder record: original linked-list stride 0x6C, next +0x3C, login +0x40.
#ifndef RA2_SHARED_WOL_LADDER_HPP
#define RA2_SHARED_WOL_LADDER_HPP
namespace WOL {
struct Ladder {
    unsigned int game_type;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1c;
    int unknown_20;
    char unknown_24[0x3c - 0x24];
    Ladder *next;
    char name[0x6c - 0x40];
};
}
#endif
