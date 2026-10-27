// void UnknownSelectable_006f9fb0::unknown_make_current() -- 0x006F9FB0
// Purpose: when this object is not the current one (0x00AD0450), runs
// 0x006F9D90 on it, makes it current and has the object at 0x00AD0434
// run 0x006F8E30.
// Assumptions: the class (string-table / language area, 0x006F9xxx) and
// both helpers are unidentified.
// @ref ?unknown_current_ad0450@@3PAUUnknownSelectable_006f9fb0@@A=00ad0450
// @ref ?unknown_6f9d90@UnknownSelectable_006f9fb0@@QAEXXZ=006f9d90
// @ref ?unknown_6f8e30@UnknownObserver_006f9fb0@@QAEXXZ=006f8e30
// @ref ?unknown_observer_ad0434@@3PAUUnknownObserver_006f9fb0@@A=00ad0434

struct UnknownObserver_006f9fb0 {
    void unknown_6f8e30();                  // 0x006F8E30
};
extern UnknownObserver_006f9fb0 *unknown_observer_ad0434;

struct UnknownSelectable_006f9fb0 {
    void unknown_make_current();
    void unknown_6f9d90();                  // 0x006F9D90
};
extern UnknownSelectable_006f9fb0 *unknown_current_ad0450;

void UnknownSelectable_006f9fb0::unknown_make_current()
{
    if (unknown_current_ad0450 != this) {
        unknown_6f9d90();
        unknown_current_ad0450 = this;
        unknown_observer_ad0434->unknown_6f8e30();
    }
}
