// @ref ??_C@_0BC@EKNB@IsSuspended?7?$DN?5?$CFd?6?$AA@=007d7fd8
// @ref ??_C@_0BG@EDND@Object?9?$DOHeapID?5?$DN?$DN?5?$CFd?6?$AA@=007d7fec
// @ref ??_C@_0BE@EMPD@Object?9?$DORTTI?5?$DN?$DN?5?$CFd?6?$AA@=007d8004
// @ref ??_C@_0CD@JIFF@fptr?9?$DOQueuedObjects?4Count?$CI?$CJ?5?$DN?$DN?5?$CF@=007da358
// @ref ??_C@_0N@NJAM@Frame?5?$DN?$DN?5?$CFd?6?$AA@=007d8038
// @ref ??_C@_08NKGA@type?$DN?$CFd?6?$AA@=007da37c
// @ref ??_C@_0GF@CJND@Request?5to?5Begin_Production?5of?5?8@=007da388
// @ref ??_C@_0EL@FFCC@Request?5to?5Begin_Production?5of?5?8@=007da3f0
// @ref ??_C@_0EM@PKHD@Request?5to?5Begin_Production?5of?5?8@=007da43c
// @ref ??_C@_0EF@NGDE@Request?5to?5Begin_Production?5of?5?8@=007da488
// HouseClass::Begin_Production, original004E5E30. Real source reconstruction.
#include "shared/building_class.hpp"
#include "shared/house_views.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/debug_printf.hpp"
#include "shared/map_view.hpp"
extern int unknown_max_ahead_a3d560;
extern int unknown_a3d568;
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_4b9440@FactoryClass@@QAE_NPAVTechnoTypeClass@@PAVHouseClass@@E@Z=004b9440
int HouseClass::Begin_Production(int kind,int index,bool naval,bool resume)
{
    int result=true;
    FactoryClass *factory;
    int buildcat=unknown_func_4eb550(kind,index);
    bool was_suspended=unknown_func_4eb770(kind,naval,buildcat);
    unknown_func_4eb810(kind,naval,buildcat,false);
    TechnoTypeClass *type=Unknown_00482C00(kind,index);
    BuildingClass *builder=type->Who_Can_Build_Me(false,true,true,this);
    bool onhold=false;
    if (!builder) {
        if (resume) builder=type->Who_Can_Build_Me(true,false,true,this);
        if (builder) onhold=true;
        else {
            Debug_Printf("Request to Begin_Production of '%s' was rejected. No-one can build.\n",(char const *)type->Name);
            return 3;
        }
    }
    factory=unknown_func_4eb580(kind,naval,buildcat);
    if (!factory) {
        factory=new FactoryClass;
        if (!factory) {
            Debug_Printf("Request to Begin_Production of '%s' was rejected. Unable to create factory\n",(char const *)type->Name);
            return 3;
        }
    }
    if (factory->Rate!=0 && !factory->unknown_6c && kind==7) {
        Debug_Printf("Request to Begin_Production of '%s' was rejected. Cannot queue buildings.\n",(char const *)type->Name);
        return 3;
    }
    Set_Factory(factory,kind,naval,buildcat);
    bool has_suspended=false;
    if (factory->unknown_6c) {
        TechnoClass *object=factory->Object;
        if (object && object->unknown_slot32()==type) has_suspended=true;
    }
    if (!has_suspended) result=factory->unknown_4b9440(type,this,resume);
    if (result) {
        if (factory->Queue.Count() && !resume && !has_suspended) {
            Map.Unknown_0067C2D0(Unknown_006818D0(kind,index,0));
        } else {
            bool suspended=factory->unknown_6c;
            factory->Start_Production_004B9670(onhold);
            if (!suspended && unknown_game_mode_a3d298 && unknown_134) {
                int duration=factory->Object->unknown_slot32()->unknown_slot34();
                int stage=(int)(((unsigned)unknown_a3d568*(unsigned)unknown_max_ahead_a3d560/60)*54)/duration;
                if (stage>=53) stage=53;
                if (was_suspended) factory->Stage=stage;
            }
            if (unknown_player_a35db4==this) Map.Unknown_0067C370((int)factory,kind,index);
        }
        return 0;
    }
    Debug_Printf("Request to Begin_Production of '%s' was rejected. Factory was unable to create the requested object\n",(char const *)type->Name);
    if (!factory->Queue.Count() && !factory->Object) {
        Debug_Printf("type=%d\n",kind);
        Debug_Printf("Frame == %d\n",Frame);
        Debug_Printf("fptr->QueuedObjects.Count() == %d\n",factory->Queue.Count());
        Debug_Printf("Object->RTTI == %d\n",factory->Object ? factory->Object->Kind_Of() : -1);
        Debug_Printf("Object->HeapID == %d\n",factory->Object ? factory->Object->unknown_slot16() : -1);
        Debug_Printf("IsSuspended\t= %d\n",factory->unknown_6c);
        delete factory;
        Set_Factory(0,kind,naval,buildcat);
    }
    return 3;
}
