// void unknown_write_wdtmap_ini_72a880(Wstring const &prefix, Wstring const &filename) (0x0072A880, __fastcall):
// scans a PCX territory map, collects each colour's bounding rectangle and centroid
// (colours 0-29), and writes the centroids as Target_<width> points of the sections
// <prefix><NN> into WDTMap.ini (next to the game and as ..\code\wdtmap.ini).
// A development tool; no caller is recovered.
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ??0CDFileClass@@QAE@ABVWstring@@@Z=0046fd60
// @ref ??_C@_0BD@JCPH@?4?4?2code?2wdtmap?4ini?$AA@=007fc110
// @ref ?Clear@?$VectorClass@V?$TRect@H@@@@UAEXXZ=0058e690
// @ref ??_C@_0L@HMJF@WDTMap?4ini?$AA@=007fc12c
// @ref ??_C@_07GLHL@Target_?$AA@=007fc124
// @ref ??_7?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@6B@=007af284
// @ref ??0?$TRect@H@@QAE@XZ=0072af70
// @ref ??_7?$VectorClass@V?$TRect@H@@@@6B@=007a5eb0
// @ref ??_7?$VectorClass@UCentroid@WorldDominationTour@@@@6B@=007af298
// @ref ??B?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UBE_NXZ=0072b0b0
// @ref ??E?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEAAV0@XZ=0072b8d0
// @ref ??F?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEAAV0@XZ=0072b8e0
// @ref ??_G?$VectorCursor@V?$TRect@H@@V?$VectorClass@V?$TRect@H@@@@@@UAEPAXI@Z=0072b0f0
// @ref ??_E?$VectorClass@V?$TRect@H@@@@UAEPAXI@Z=0058ed40
// @ref ??8?$VectorClass@V?$TRect@H@@@@UBE_NABV0@@Z=0058e530
// @ref ?Resize@?$VectorClass@V?$TRect@H@@@@UAE_NHPBV?$TRect@H@@@Z=0058e5a0
// @ref ?ID@?$VectorClass@V?$TRect@H@@@@UAEHABV?$TRect@H@@@Z=0058e6c0
// @ref ?ID@?$VectorClass@V?$TRect@H@@@@UAEHPBV?$TRect@H@@@Z=0058e720
// @ref ?Fetch@?$VectorClass@V?$TRect@H@@@@UBE?AV?$TRect@H@@H@Z=0058dde0
// @ref ??_E?$VectorClass@UCentroid@WorldDominationTour@@@@UAEPAXI@Z=0072baa0
// @ref ??8?$VectorClass@UCentroid@WorldDominationTour@@@@UBE_NABV0@@Z=0072b6c0
// @ref ?Resize@?$VectorClass@UCentroid@WorldDominationTour@@@@UAE_NHPBUCentroid@WorldDominationTour@@@Z=0072b720
// @ref ?Clear@?$VectorClass@UCentroid@WorldDominationTour@@@@UAEXXZ=0072b820
// @ref ?ID@?$VectorClass@UCentroid@WorldDominationTour@@@@UAEHABUCentroid@WorldDominationTour@@@Z=0072b850
// @ref ?ID@?$VectorClass@UCentroid@WorldDominationTour@@@@UAEHPBUCentroid@WorldDominationTour@@@Z=0072b8a0
// @ref ?Fetch@?$VectorClass@UCentroid@WorldDominationTour@@@@UBE?AUCentroid@WorldDominationTour@@H@Z=0072b060
// @ref ??_E?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_7?$List@PAUINISection@INIClass@@@@6B@=0079aaec
// @ref ?Load@INIClass@@QAEHAAVFileClass@@_N@Z=0050bbe0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0GenericNode@@QAE@XZ=0040e160
// @ref ?Link@GenericNode@@QAEXPAV1@@Z=0040e180
// @ref ??_7INIClass@@6B@=007a2b34
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_GINIClass@@UAEPAXI@Z=004deef0
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_7GenericNode@@6B@=0079aafc
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
#include "shared/wdt_map.hpp"
#include "shared/cd_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/ms_anim.hpp"
#include "shared/surface.hpp"
#include "shared/rect.hpp"
#include "shared/trect.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/vector_class.hpp"
#include "shared/vector_cursor.hpp"
#include "shared/vector_elements.hpp"
#include "shared/wstring.hpp"

using WorldDominationTour::Centroid;

// The INI point of a screen point (taken by value; the copy is the original's temporary).
static inline INIPoint2D To_Point(Point2D point)
{
    return INIPoint2D(point.X, point.Y);
}

void __fastcall unknown_write_wdtmap_ini_72a880(Wstring const &prefix, Wstring const &filename)
{
    CDFileClass file;
    file.Open("WDTMap.ini", FILE_RIGHTS_READ);
    INIClass ini;
    ini.Load(file, false);
    file.Close();

    CDFileClass pcx(filename);
    Surface *surface = unknown_load_pcx_60d110(&pcx, 0, 0, 0);
    int height = surface->Get_Height();
    int width = surface->Get_Width();

    VectorClass<TRect<int> > rects(30);
    VectorClass<Centroid> centroids(30);

    VectorCursor<TRect<int>, VectorClass<TRect<int> > > cursor(rects);
    for (; cursor; ++cursor) {
        (*cursor).Set(0, 0, 0, 0);
    }

    Point2D point;
    for (point.Y = 0; point.Y < height; point.Y++) {
        for (point.X = 0; point.X < width; point.X++) {
            unsigned index = surface->Get_Pixel(point);
            if (index <= 29 && index < 255) {
                if (centroids.Length() < index + 1) {
                    centroids.Resize(index + 1);
                }
                centroids[index] += point;
                if (rects.Length() < index + 1) {
                    int count = rects.Length();
                    rects.Resize(index + 1);
                    VectorCursor<TRect<int>, VectorClass<TRect<int> > > fresh(rects, count);
                    for (; fresh; ++fresh) {
                        (*fresh).Set(0, 0, 0, 0);
                    }
                }
                TRect<int> &rect = rects[index];
                if (rect.Width == 0) {
                    rect.Height = 0;
                }
                if (!rect.Is_Point_Within(point)) {
                    rect = Union(rect, TRect<int>(point, 1, 1));
                }
            }
        }
    }

    {
        VectorCursor<TRect<int>, VectorClass<TRect<int> > > reset(rects, 0);
        cursor = reset;
    }
    int i = 0;
    while (cursor) {
        Wstring section = Wstring_Join(prefix, Wstring_From_Integer(i, 2));
        Wstring number = Wstring_From_Integer(unknown_8523e0);
        ini.Put_Point(section, Wstring("Target_") + number, To_Point(centroids[i].Average()));
        ++cursor;
        i++;
    }

    file.Open("WDTMap.ini", FILE_RIGHTS_WRITE);
    ini.Save(file);
    file.Open("..\\code\\wdtmap.ini", FILE_RIGHTS_WRITE);
    ini.Save(file);
}
