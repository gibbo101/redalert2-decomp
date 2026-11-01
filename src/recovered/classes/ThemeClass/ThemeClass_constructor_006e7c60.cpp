// ThemeClass::ThemeClass() (0x006E7C60)
// Nothing playing or queued, full volume, no themes and no stream.
#define THEME_CONTROL_RECORD
#ifndef VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#include "shared/vector_class.hpp"
#include "shared/theme.hpp"
// @ref ??_7?$DynamicVectorClass@PAUThemeControl@@@@6B@=007ad814
// @ref ??_7?$VectorClass@PAUThemeControl@@@@6B@=007a2ac4
// @ref ??_G?$VectorClass@PAUThemeControl@@@@UAEPAXI@Z=004dc050
// @ref ?Resize@?$VectorClass@PAUThemeControl@@@@UAE_NHPBQAUThemeControl@@@Z=004d69f0
// @ref ?Clear@?$VectorClass@PAUThemeControl@@@@UAEXXZ=004d6aa0
// @ref ?ID@?$VectorClass@PAUThemeControl@@@@UAEHABQAUThemeControl@@@Z=004d6ad0
// @ref ?ID@?$VectorClass@PAUThemeControl@@@@UAEHPBQAUThemeControl@@@Z=004d6b10
// @ref ??_G?$DynamicVectorClass@PAUThemeControl@@@@UAEPAXI@Z=006e86e0
// @ref ??8?$VectorClass@PAUThemeControl@@@@UBE_NABV0@@Z=004d69b0
// @ref ?Resize@?$DynamicVectorClass@PAUThemeControl@@@@UAE_NHPBQAUThemeControl@@@Z=006e8600
// @ref ?Clear@?$DynamicVectorClass@PAUThemeControl@@@@UAEXXZ=006e85b0
// @ref ?ID@?$DynamicVectorClass@PAUThemeControl@@@@UAEHABQAUThemeControl@@@Z=006e86b0
// @ref ?ID@?$DynamicVectorClass@PAUThemeControl@@@@UAEHPBQAUThemeControl@@@Z=006e85e0
// @ref ?Fetch@?$VectorClass@PAUThemeControl@@@@UBEPAUThemeControl@@H@Z=004d4c40

ThemeClass::ThemeClass() :
    Current(-1),
    Score(THEME_NONE),
    Pending(THEME_NONE),
    Volume(255),
    IsRepeat(false),
    unknown_11(false),
    IsShuffle(false),
    Sample(0)
{
}
