// The game's notice interfaces (AbstractClass bases at +8 and +0xC; TabClass
// also implements INoticeSink). Slot names are placeholders.
#ifndef RA2_SHARED_NOTICE_HPP
#define RA2_SHARED_NOTICE_HPP

class INoticeSink {
public:
    // thiscall with two arguments: InfantryClass's override 0x00509590 takes
    // `this` in ecx and the code at [esp+4] (ret 8); TabClass 0x006A2020 reads
    // the code at [esp+4] too. Argument names are hypotheses.
    virtual bool INoticeSink_Unknown(int code, int arg) = 0;
};

class INoticeSource {
public:
    virtual void __stdcall INoticeSource_Unknown() = 0;
};

#endif
