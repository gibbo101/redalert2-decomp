// MapSelect identity/base from MSVC RTTI at vtable007A608C.
// RA2 layout from0058F510 construction,0058FA20 initialization,0058FC60 cleanup.
#ifndef RA2_SHARED_MAP_SELECT_HPP
#define RA2_SHARED_MAP_SELECT_HPP
#include "shared/ms_engine.hpp"
#include "shared/ms_choice.hpp"
#include "shared/msfont.hpp"
#include "shared/cd_timer.hpp"
class UnknownIDSource;
class MapSelect : public MSEngine {
public:
    bool Advance_Progression_0058f720(UnknownIDSource *scenario,Wstring const &name);
    bool Presentation_0058f900(UnknownIDSource *scenario);
    bool Init_0058fa20(UnknownIDSource *scenario);
    void Deinit_0058fc60();
    void Play_Sound_0058fd00(Wstring const &name);
    void Queue_Voice_0058fd30(Wstring const &name,int delay);
    virtual void Unknown_Slot2(); //0058FCC0
    int XOffset, YOffset; //48,4c
    MapSelectData Choices; //50
    ConvertClass *AnimDrawer; //ac
    ConvertClass *OverlayDrawer; //b0
    MSFont *Font; //b4
    Rect TextRect; //b8
    Wstring VoiceName; //c8; RA2 differs from TS's char pointer
    CDTimerClass<SystemTimerClass> VoiceTimer; //cc
    int VoiceHandle; //d8
};
typedef char MapSelect_size[(sizeof(MapSelect)==0xdc)?1:-1];
#endif
