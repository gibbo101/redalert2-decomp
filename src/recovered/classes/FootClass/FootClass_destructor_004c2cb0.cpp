// FootClass::~FootClass() (0x004C2CB0)
// Leaves its team (only while unknown_flag_a40958 is set) and both lists,
// deletes the owned object at +0x588 and stops the sound controller; the
// member destructors release the locomotor and the two vectors.
#include "shared/foot.hpp"
#include "shared/parasite.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?Delete@?$DynamicVectorClass@PAVFootClass@@@@QAE_NH@Z=004cebe0
// @ref ?Delete@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NH@Z=00454b20
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?Unknown_00405C10@UnknownAudioController@@QAEXXZ=00405c10
// @ref ??_7?$VectorClass@PAVAbstractClass@@@@6B@=007a179c
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??1TechnoClass@@UAE@XZ=006c20b0

FootClass::~FootClass()
{
    if (Team != 0 && unknown_flag_a40958) {
        Team->Unknown_006B8FB0(this, -1, 0);
    }
    unknown_FootClass_list_00865f38.Delete(this);
    unknown_list_ac0c18.Delete(this);
    if (unknown_588 != 0) {
        delete unknown_588;
        unknown_588 = 0;
    }
    unknown_43c.Unknown_00406070();
    unknown_43c.Unknown_00405C10();
}
