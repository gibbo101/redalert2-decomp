// Mouse: the abstract mouse interface (RTTI vtable 0x007AFC38, 18 slots).
//
// Split out of shared/wwmouse.hpp (which includes it) so that units that only
// call through the game's mouse pointer (CD.CPP, MSEngine, the movie loop)
// need not include wwmouse.hpp, whose static unknown_empty_rect would give
// them a dynamic initializer the original objects do not have.
#ifndef RA2_SHARED_MOUSE_HPP
#define RA2_SHARED_MOUSE_HPP

#include "shared/rect.hpp"

class Surface;
struct ShapeFileStruct;

class Mouse {
public:
    Mouse() {}
    virtual ~Mouse() {}                                                         // slot 0  (+0x00)
    virtual void Set_Cursor(Point2D const &hotspot, ShapeFileStruct const *cursor, int frame) = 0;  // slot 1 (+0x04)
    virtual bool Is_Hidden() const = 0;                                         // slot 2  (+0x08)
    virtual void Hide_Mouse() = 0;                                              // slot 3  (+0x0C)
    virtual void Show_Mouse() = 0;                                              // slot 4  (+0x10)
    virtual void Release_Mouse() = 0;                                           // slot 5  (+0x14)
    virtual void Capture_Mouse() = 0;                                           // slot 6  (+0x18)
    virtual bool Is_Captured() const = 0;                                       // slot 7  (+0x1C)
    virtual void Conditional_Hide_Mouse(Rect region) = 0;                       // slot 8  (+0x20)
    virtual void Conditional_Show_Mouse() = 0;                                  // slot 9  (+0x24)
    virtual int Get_Mouse_State() const = 0;                                    // slot 10 (+0x28)
    virtual int Get_Mouse_X() const = 0;                                        // slot 11 (+0x2C)
    virtual int Get_Mouse_Y() const = 0;                                        // slot 12 (+0x30)
    virtual Point2D Get_Mouse_XY() const = 0;                                   // slot 13 (+0x34)
    virtual void Set_Mouse_XY(int x, int y) = 0;                                // slot 14 (+0x38)
    virtual void Draw_Mouse(Surface *surface, bool issidebar = false) = 0;      // slot 15 (+0x3C)
    virtual void Erase_Mouse(Surface *surface, bool issidebar = false) = 0;     // slot 16 (+0x40)
    virtual void Convert_Coordinate(int &x, int &y) const = 0;                  // slot 17 (+0x44)
};

// The game's mouse object; its Hide_Mouse/Show_Mouse bracket movie playback
// and its Draw_Mouse/Erase_Mouse bracket MSEngine blits.
extern Mouse *WWMouse;      // 0x00839C68

#endif
