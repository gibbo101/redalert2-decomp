#include "shared/object.hpp"
#include "shared/techno.hpp"

void BombListClass::Unknown_004361F0()
{
    for(int index=Bombs.Count()-1;index>=0;--index) {
        BombClass *bomb=Bombs[index];
        if(bomb==0) Bombs.Delete(index);
        else if(bomb->Target==0) {
            delete bomb;
            Bombs.Delete(index);
        }
    }
    for(index=Bombs.Count()-1;index>=0;--index) {
        BombClass *bomb=Bombs[index];
        if(bomb->unknown_50!=-1) {
            if(bomb->Target->unknown_76) {
                bomb->unknown_3c.Unknown_00405D50();
                bomb->unknown_54=0;
            } else if(bomb->unknown_54==0) {
                Voc_Play_At(bomb->unknown_50,bomb->Target->Position_Coord_004f3f40(),&bomb->unknown_3c);
                bomb->unknown_54=1;
            } else {
                Voc_Update_At(bomb->Target->Position_Coord_004f3f40(),&bomb->unknown_3c);
            }
        }
    }
    if(unknown_30>0) {
        --unknown_30;
        return;
    }
    unknown_30=45;
    for(index=Bombs.Count()-1;index>=0;--index) {
        BombClass *bomb=Bombs[index];
        bool visible=false;
        bool previous=bomb->Target->unknown_68;
        if(bomb->unknown_28->Unknown_004F52B0()) visible=true;
        else {
            int scan=0;
            if(unknown_18.Count()>0) {
                do {
                    TechnoClass *detector=unknown_18[scan];
                    if(detector->Owning_House()->Unknown_004F52B0()) {
                        CoordStruct delta=detector->Center_Coord()-bomb->Target->Center_Coord();
                        double z=delta.Z;
                        double y=delta.Y;
                        double x=delta.X;
                        int distance=(int)unknown_sqrt_4ba410(x*x+y*y+z*z);
                        if(distance<detector->unknown_slot32()->BombSight*256) {
                            visible=true;
                            break;
                        }
                    }
                } while(++scan<unknown_18.Count());
            }
        }
        bomb->Target->unknown_68=visible;
        if(visible!=previous) bomb->Target->unknown_75=true;
    }
}

// External references checked against complete original body operands.
// @ref ?Unknown_00405D50@UnknownAudioController@@QAEXXZ=00405d50
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ?Voc_Update_At@@YIPAUAudioEvent@@ABUCoordStruct@@PAUAudioEventHandle@@@Z=007141b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __ftol=0077f110
