#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/session_state.hpp"
#include "shared/vector_class.hpp"
#include "shared/multi_mission.hpp"
extern "C" void __cdecl free(void *block);

UnknownSessionState::~UnknownSessionState()
{
    while (InitStrings.Count()) {
        delete InitStrings[0];
        InitStrings.Delete(0);
    }
    while (CallWaitStrings.Count()) {
        free((void *)CallWaitStrings[0]);
        CallWaitStrings.Delete(0);
    }
}
// @ref ??_7?$VectorClass@PAVPhoneEntryClass@@@@6B@=007a9604
// @ref ??_7?$VectorClass@PAUUnknownGlobalPacket@@@@6B@=007a95e4
// @ref ??_7?$VectorClass@PAVMultiMission@@@@6B@=007a95c4
// @ref _free=007825e8
// @ref ??8?$VectorClass@PAVMultiMission@@@@UBE_NABV0@@Z=00674070
// @ref ?Resize@?$VectorClass@PAVMultiMission@@@@UAE_NHPBQAVMultiMission@@@Z=006740b0
// @ref ?Clear@?$VectorClass@PAVMultiMission@@@@UAEXXZ=00674160
// @ref ?ID@?$VectorClass@PAVMultiMission@@@@UAEHABQAVMultiMission@@@Z=00674190
// @ref ?ID@?$VectorClass@PAVMultiMission@@@@UAEHPBQAVMultiMission@@@Z=006741d0
// @ref ?Fetch@?$VectorClass@PAVMultiMission@@@@UBEPAVMultiMission@@H@Z=00673920
// @ref ??_G?$VectorClass@PAUUnknownGlobalPacket@@@@UAEPAXI@Z=00674960
// @ref ??8?$VectorClass@PAUUnknownGlobalPacket@@@@UBE_NABV0@@Z=006742d0
// @ref ?Resize@?$VectorClass@PAUUnknownGlobalPacket@@@@UAE_NHPBQAUUnknownGlobalPacket@@@Z=00674310
// @ref ?Clear@?$VectorClass@PAUUnknownGlobalPacket@@@@UAEXXZ=006743c0
// @ref ?ID@?$VectorClass@PAUUnknownGlobalPacket@@@@UAEHABQAUUnknownGlobalPacket@@@Z=006743f0
// @ref ?ID@?$VectorClass@PAUUnknownGlobalPacket@@@@UAEHPBQAUUnknownGlobalPacket@@@Z=00674430
// @ref ?Fetch@?$VectorClass@PAUUnknownGlobalPacket@@@@UBEPAUUnknownGlobalPacket@@H@Z=00673980
// @ref ??_G?$VectorClass@PAVPhoneEntryClass@@@@UAEPAXI@Z=00674a00
// @ref ??8?$VectorClass@PAVPhoneEntryClass@@@@UBE_NABV0@@Z=00674530
// @ref ?Resize@?$VectorClass@PAVPhoneEntryClass@@@@UAE_NHPBQAVPhoneEntryClass@@@Z=00674570
// @ref ?Clear@?$VectorClass@PAVPhoneEntryClass@@@@UAEXXZ=00674620
// @ref ?ID@?$VectorClass@PAVPhoneEntryClass@@@@UAEHABQAVPhoneEntryClass@@@Z=00674650
// @ref ?ID@?$VectorClass@PAVPhoneEntryClass@@@@UAEHPBQAVPhoneEntryClass@@@Z=00674690
// @ref ?Fetch@?$VectorClass@PAVPhoneEntryClass@@@@UBEPAVPhoneEntryClass@@H@Z=006739e0
// @ref ??_7?$VectorClass@PBG@@6B@=007a5734
// @ref ??_E?$VectorClass@PBG@@UAEPAXI@Z=0053ae60
// @ref ??8?$VectorClass@PBG@@UBE_NABV0@@Z=0053ac00
// @ref ?Clear@?$VectorClass@PBG@@UAEXXZ=0053acf0
// @ref ?ID@?$VectorClass@PBG@@UAEHABQPBG@Z=0053ad20
// @ref ?Fetch@?$VectorClass@PBG@@UBEPBGH@Z=0053abf0
// @ref ??_E?$VectorClass@PAD@@UAEPAXI@Z=00491340
// @ref ??8?$VectorClass@PAD@@UBE_NABV0@@Z=004910e0
// @ref ?Clear@?$VectorClass@PAD@@UAEXXZ=004911d0
// @ref ?ID@?$VectorClass@PAD@@UAEHABQPAD@Z=00491200
// @ref ?Fetch@?$VectorClass@PAD@@UBEPADH@Z=004910b0
// @ref ??_7?$VectorClass@PAD@@6B@=0079e57c
// @ref ??_G?$VectorClass@PAUNodeNameType@@@@UAEPAXI@Z=005a6c40
// @ref ??8?$VectorClass@PAUNodeNameType@@@@UBE_NABV0@@Z=005a6730
// @ref ?Clear@?$VectorClass@PAUNodeNameType@@@@UAEXXZ=005a6820
// @ref ?ID@?$VectorClass@PAUNodeNameType@@@@UAEHABQPAUNodeNameType@@@Z=005a6850
// @ref ?Fetch@?$VectorClass@PAUNodeNameType@@@@UBEPAUNodeNameType@@H@Z=005a6460
// @ref ??_7?$VectorClass@PAUNodeNameType@@@@6B@=007a6884
// @ref ?Resize@?$VectorClass@PBG@@UAE_NHPBQBG@Z=0053ac40
// @ref ?ID@?$VectorClass@PBG@@UAEHABQBG@Z=0053ad20
// @ref ?ID@?$VectorClass@PBG@@UAEHPBQBG@Z=0053ad60
// @ref ?Resize@?$VectorClass@PAD@@UAE_NHPBQAD@Z=00491120
// @ref ?ID@?$VectorClass@PAD@@UAEHABQAD@Z=00491200
// @ref ?ID@?$VectorClass@PAD@@UAEHPBQAD@Z=00491240
// @ref ?Resize@?$VectorClass@PAUNodeNameType@@@@UAE_NHPBQAUNodeNameType@@@Z=005a6770
// @ref ?ID@?$VectorClass@PAUNodeNameType@@@@UAEHABQAUNodeNameType@@@Z=005a6850
// @ref ?ID@?$VectorClass@PAUNodeNameType@@@@UAEHPBQAUNodeNameType@@@Z=005a6890
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ?Reset@MessageListClass@@QAEXXZ=005b4c40
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??3@YAXPAX@Z=00781d3b
