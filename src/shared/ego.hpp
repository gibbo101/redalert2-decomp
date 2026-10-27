// EgoClass: 16-byte scrolling text record; name evidenced by its pointer vector.
#ifndef RA2_SHARED_EGO_HPP
#define RA2_SHARED_EGO_HPP
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
class Surface;
class EgoClass {
public:
    EgoClass(int unknown04, int y, wchar_t const *text, unsigned int flags);
    ~EgoClass();
    bool Advance(int amount);
    void Draw(bool force);
    void Copy_Background(Surface *source);
    wchar_t *Text;          // +0x00 owned heap string
    int unknown_04;
    int Y;                 // +0x08
    unsigned int TextFlags;// +0x0C
};
#endif
