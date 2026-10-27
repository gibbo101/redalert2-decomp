// Dial8Class, RTTI vtable0079E794. Layout recovered from constructor00496D30.
#ifndef RA2_SHARED_DIAL8_HPP
#define RA2_SHARED_DIAL8_HPP
#include "shared/gadget.hpp"
#include "shared/rect.hpp"
class Dial8Class : public ControlClass {
public:
    Dial8Class(unsigned id, int x, int y, int width, int height, unsigned direction);
    virtual int Action(unsigned flags, unsigned &key);
    virtual int Draw_Me(int forced = false);
    void Update_Direction(unsigned direction);
    void Set_Direction(unsigned direction);
    int Get_Direction() const;
    Point2D Center;             // +2C
    Point2D OuterPoints[8];     // +34
    Point2D InnerPoints[8];     // +74
    int Direction;        // +B4 direction256
    int Selected;         // +B8 direction8
    int Previous;         // +BC
};
#endif
