// TechnoClass::~TechnoClass() (0x006C20B0)
// Releases the +0x408 object, deletes the owned helpers (+0x230 capture
// manager, +0x238 spawn manager, +0x208 temporal), stops the audio at +0x3D8,
// forgets the owner, leaves Technos and the 0x00AC0D08 list, releases the
// +0x108 object (slot 60) and leaves the 0x00AC0BF8 list; then the members
// and RadioClass/MissionClass/ObjectClass are destroyed.
#include "shared/techno.hpp"
// @ref ??_7TechnoClass@@6BIPersistStream@@@=007acb80
// @ref ??_7TechnoClass@@6BIRTTITypeInfo@@@=007acb64
// @ref ??_7TechnoClass@@6BINoticeSink@@@=007acb5c
// @ref ??_7TechnoClass@@6BINoticeSource@@@=007acb54
// @ref ??1UnknownTechnoPair@@QAE@XZ=00713350
// @ref ?Delete@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NH@Z=0061bdc0
// @ref ?unknown_6130b0@UnknownTechno408@@QAEXXZ=006130b0
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?unknown_abstracts_ac0d08@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d08
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8

TechnoClass::~TechnoClass()
{
    if (unknown_408 != 0) {
        unknown_408->unknown_6130b0();
        unknown_408 = 0;
    }
    if (unknown_230 != 0) {
        delete unknown_230;
        unknown_230 = 0;
    }
    if (unknown_238 != 0) {
        delete unknown_238;
        unknown_238 = 0;
    }
    if (unknown_208 != 0) {
        delete unknown_208;
        unknown_208 = 0;
    }
    unknown_3d8.Unknown_00405FE0();
    unknown_3d8.Unknown_00405C10();
    House = 0;
    unknown_372 = false;
    Technos.Delete(this);
    unknown_abstracts_ac0d08.Delete(this);
    if (unknown_108 != 0) {
        unknown_108->unknown_slot60();
        unknown_108 = 0;
    }
    unknown_abstracts_ac0bf8.Delete(this);
}
