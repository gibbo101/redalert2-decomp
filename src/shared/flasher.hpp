// Non-polymorphic Techno base: original RTTI places it at +0xD8.
#ifndef RA2_SHARED_FLASHER_HPP
#define RA2_SHARED_FLASHER_HPP
class NoInitClass;
class FlasherClass {
public:
    FlasherClass() { FlashCount=0; IsBlushing=false; }
    FlasherClass(NoInitClass const &) {}
    ~FlasherClass() {}
    unsigned FlashCount;
    bool IsBlushing;
};
#endif
