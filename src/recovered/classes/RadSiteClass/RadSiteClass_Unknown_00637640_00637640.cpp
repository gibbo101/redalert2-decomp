// void RadSiteClass::Unknown_00637640() (0x00637640)
// Starts the site's timers, derives its decay steps and light from the rules
// (RadColor, RadLightFactor, RadTintFactor), then creates or retints the
// light and fills the cells (0x00637A80).
#include "shared/radsite.hpp"
#include "shared/id_source.hpp"
#include "shared/rgb_class.hpp"
extern double const unknown_double_7a6020;  // 0x007A6020 (2000.0)
// @ref ?unknown_double_7a6020@@3NB=007a6020
// @ref ?Unknown_00637A80@RadSiteClass@@QAEXXZ=00637a80
// @ref ?Activate@LightSourceClass@@QAEXH@Z=00537540
// @ref ?Change@LightSourceClass@@QAEXHHHHH@Z=00537580
// @ref ??0LightSourceClass@@QAE@UCoordStruct@@HHHHH@Z=00537240

void RadSiteClass::Unknown_00637640()
{
    int level_delay = Rules->RadLevelDelay;
    int light_delay = Rules->RadLightDelay;
    unknown_28 = CDTimerClass<FrameTimerClass>(level_delay);
    unknown_34 = CDTimerClass<FrameTimerClass>(light_delay);
    int red = Rules->RadColor.Red;
    int green = Rules->RadColor.Green;
    int blue = Rules->RadColor.Blue;
    if (unknown_id_source_a3d290->Theater == 1) {
        red = blue = -128;
    }
    red = red * 1000 / 255;
    green = green * 1000 / 255;
    blue = blue * 1000 / 255;
    int visibility = SpreadInLeptons;
    double v = RadLevel;
    v = v * Rules->RadLightFactor;
    int intensity = (int)(unknown_double_7a6020 < v ? unknown_double_7a6020 : v);
    v = red * Rules->RadTintFactor;
    int r = (int)(unknown_double_7a6020 < v ? unknown_double_7a6020 : v);
    v = green * Rules->RadTintFactor;
    int g = (int)(unknown_double_7a6020 < v ? unknown_double_7a6020 : v);
    v = blue * Rules->RadTintFactor;
    int b = (int)(unknown_double_7a6020 < v ? unknown_double_7a6020 : v);
    unknown_58 = r;
    unknown_5c = g;
    unknown_60 = b;
    unknown_54 = intensity;
    unknown_50 = RadDuration / level_delay;
    unknown_64 = RadDuration / light_delay;
    unknown_68 = intensity / unknown_64;
    RadSiteCell &cell = (RadSiteCell &)Map[BaseCell];
    CoordStruct coord = cell.Center_Coord();
    if (LightSource == 0) {
        LightSource = new LightSourceClass(coord, visibility, intensity, r, g, b);
        LightSource->DetailLevel = 0;
        LightSource->Activate(0);
    } else {
        LightSource->Change(intensity, r, g, b, 0);
    }
    Unknown_00637A80();
}
