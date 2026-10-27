// WaveClass::~WaveClass() (0x00721900)
// Releases references and removes the wave from Waves (the cell list is
// destroyed with it).
#include "shared/wave.hpp"
// @ref ??1ObjectClass@@UAE@XZ=005d2530
// @ref ?Unknown_006ECB90@@YIXPAVObjectClass@@_N@Z=006ecb90
// @ref ?Waves@@3V?$DynamicVectorClass@PAVWaveClass@@@@A=00a40be8
// @ref ??_7WaveClass@@6BIPersistStream@@@=007aecd0
// @ref ??_7WaveClass@@6BIRTTITypeInfo@@@=007aecb4
// @ref ??_7WaveClass@@6BINoticeSink@@@=007aecac
// @ref ??_7WaveClass@@6BINoticeSource@@@=007aeca4
// @ref ?Load@WaveClass@@UAGJPAUIStream@@@Z=007221d0
// @ref ?Save@WaveClass@@UAGJPAUIStream@@H@Z=00722330
// @ref ?AI@WaveClass@@UAEXXZ=00723220
// @ref ?unknown_slot53@WaveClass@@UAE_NPBUCoordStruct@@H@Z=00722410
// @ref ?unknown_slot67@WaveClass@@UAEXHH@Z=00722530
// @ref ??_7?$VectorClass@PAVCellClass@@@@6B@=007a59b8

WaveClass::~WaveClass()
{
    Unknown_006ECB90(this, true);
    Waves.Delete(this);
    Cells.Clear();
}
