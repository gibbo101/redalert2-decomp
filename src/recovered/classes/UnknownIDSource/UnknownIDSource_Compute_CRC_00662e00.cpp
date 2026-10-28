// void UnknownIDSource::Compute_CRC(WWCRCEngine &crc) const (0x00662E00)
// Adds the scenario's name, movies, timers and lighting settings to a CRC.
// @ref ??RWWCRCEngine@@QAEXPBD@Z=00493f90
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
#include "shared/id_source.hpp"
#include "shared/wwcrc_engine.hpp"

void UnknownIDSource::Compute_CRC(WWCRCEngine &crc) const
{
    crc(UIName);
    crc((long)IntroMovie);
    crc((long)BriefMovie);
    crc((long)WinMovie);
    crc((long)LoseMovie);
    crc((long)ActionMovie);
    crc((long)PostScoreMovie);
    crc((long)PreMapSelectMovie);
    crc((long)unknown_11fc);
    crc((long)Percent);
    crc((long)Theme);
    crc(CarryOverMoney);
    crc(MultiplayerOnly);
    crc(unknown_2231);
    crc((long)(unknown_1208 / 100));
    crc((long)unknown_2224);
    crc(EndOfGame);
    crc((long)unknown_224c);
    crc(SkipScore);
    crc(OneTimeOnly);
    crc(SkipMapSelect);
    crc(FillSilos);
    crc(unknown_2238);
    crc(TruckCrate);
    crc((long)Percent);
    crc((long)StartingDropships);
    crc((long)MissionTimer.Value());
    crc((long)unknown_7f8.Value());
    crc((long)unknown_804.Value());
    crc((long)unknown_810.Value());
    crc((long)unknown_81c.Value());
    crc((long)ElapsedTime.Time());
    crc((long)Difficulty);
    crc((long)unknown_610);
    crc((long)Theater);
    crc((long)AmbientGround);
    crc((long)AmbientLevel);
    crc(FreeRadar);
    crc((long)IonAmbient);
    crc((long)IonRed);
    crc((long)IonGreen);
    crc((long)IonBlue);
    crc((long)IonGround);
    crc((long)IonLevel);
    crc((long)unknown_22a8);
    crc((long)unknown_22ac);
    crc((long)unknown_22b0);
}
