// Techno defaults and membership registration; unknown field names retain offsets.
#include "shared/techno.hpp"
// @ref ??0RadioClass@@QAE@XZ=00636830
// @ref ??0UnknownTechnoPair@@QAE@XZ=00713340
TechnoClass::TechnoClass(HouseClass *house) :
    RadioClass(), FlasherClass(), StageClass(), Cargo(),
    unknown_100(-1), unknown_104(-1), unknown_108(0), unknown_10c(0),
    unknown_110(-1), unknown_114(-1), unknown_118(),
    unknown_120(1.0), unknown_128(1.0),
    unknown_130(0), unknown_13c(0), unknown_148(45), unknown_154(0), unknown_160(0),
    unknown_170(false), unknown_174(0), unknown_178(0),
    unknown_184(0), unknown_190(false), unknown_194(0), unknown_1a0(0,0),
    unknown_1a8(0), unknown_1ac(-1), unknown_1b0(0), House(house), unknown_1b8(0),
    unknown_1bc(), unknown_1d4(0), unknown_1e0(0), unknown_1e4(false),
    unknown_1e8(unknown_geometry_l), unknown_1f4(0), unknown_1f8(0),
    unknown_1fc(false), unknown_1fd(false), unknown_200(0),
    unknown_204(false), unknown_205(false), unknown_206(false),
    unknown_208(0), unknown_20c(0), unknown_210(false), unknown_214(0), unknown_218(0),
    unknown_21c(unknown_geometry_l), unknown_228(0), unknown_22c(0), unknown_230(0),
    unknown_234(0), SpawnManager(0), unknown_23c(0), unknown_240(0), unknown_244(0),
    unknown_250(0), unknown_254(-1), unknown_258(0),
    unknown_27c(0), unknown_280(0), unknown_284(0), unknown_288(0), unknown_28c(0), unknown_290(-1),
    unknown_294(), unknown_2a8(), unknown_2c8(3), unknown_2e0(), unknown_2f8(),
    unknown_310(0), unknown_314(0), unknown_322(0),
    unknown_324(false), unknown_325(false), unknown_326(false), unknown_327(false),
    unknown_328(false), unknown_329(false), unknown_32a(false), unknown_32b(false),
    unknown_32c(false), unknown_32d(false), unknown_330(), unknown_350(),
    unknown_370(false), unknown_371(false), unknown_372(false), unknown_373(false),
    unknown_374(false), unknown_375(false), unknown_376(false), unknown_377(false), unknown_378(0),
    unknown_379(true), unknown_37a(true), unknown_37b(false), unknown_37c(false),
    unknown_37d(false), unknown_37e(false), unknown_37f(false), unknown_380(false), unknown_381(false),
    unknown_384(0), unknown_388(false), unknown_38c(0),
    unknown_390(), unknown_3a8(), unknown_3c0(),
    unknown_3ec(1), unknown_3f0(0), unknown_3f4(Frame), unknown_3f8(0), unknown_3fc(0),
    unknown_408(0), unknown_40c(0), unknown_410(0)
{
    if (house) unknown_114=house->unknown_130;
    unknown_3d8.Init();
    Technos.Add(this);
    unknown_abstracts_ac0d08.Add(this);
    unknown_14_bit0=true;
    for (int i=0;i<8;++i) unknown_25c[i]=0;
    unknown_320=short(unknown_id_source_a3d290->Random()());
}
