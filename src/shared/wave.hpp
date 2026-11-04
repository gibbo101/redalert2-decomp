// WaveClass: a beam weapon effect (Wave.cpp, unit 0x007211B0-0x0072472F;
// RTTI vtables 0x007AECD0 primary, 0x007AECB4 IRTTITypeInfo at +4,
// 0x007AECAC INoticeSink, 0x007AECA4 INoticeSource).
//
// Layout (destructor 0x00721900, Detach 0x00722190, Load 0x007221D0; only
// the members these use; the rest stays unrecovered):
//   +0x98   ObjectClass *Target            (detached)
//   +0x19C  TechnoClass *Owner             (detached)
//   +0x1B8  DynamicVectorClass<CellClass *> Cells   (saved by Save 0x00722330)
//   size 0x208 (Size_Of)
// Every wave is added to Waves (0x00A40BE8).
#ifndef RA2_SHARED_WAVE_HPP
#define RA2_SHARED_WAVE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/object.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/map_view.hpp"
#include "shared/techno.hpp"

class WaveClass;
class CellClass;

extern "C" GUID const CLSID_WaveClass;            // 0x007A1C90
extern DynamicVectorClass<WaveClass *> Waves;     // 0x00A40BE8
class Surface;
extern bool Wave_Tables_Initialized_00b25554;
extern unsigned short Wave_Distance_Table_00af9620[300][300];
extern short Wave_Sine_Table_00af91e4[500];
extern int Wave_Intensity_Table_00af95d8[13];

// Two real embedded geometry states: 61BE40 receives ECX=input, EDX=scanlines.
// Names are behavioral hypotheses; no RTTI for these nonvirtual objects.
struct WavePolygonInput {
    WavePolygonInput() : Count(0), Points(0) {}
    WavePolygonInput(NoInitClass const &) : Points(0) {}
    int Count;
    Point2D *Points;
    // Six independently constructed geometry points; their observed contiguous layout is unchanged.
    Point2D InlinePoint0;
    Point2D InlinePoint1;
    Point2D InlinePoint2;
    Point2D InlinePoint3;
    Point2D InlinePoint4;
    Point2D InlinePoint5;
};
struct WaveScanlineBuffer {
    WaveScanlineBuffer() : Count(0), FirstY(0), Spans(0) {}
    WaveScanlineBuffer(NoInitClass const &) : Spans(0) {}
    int Count;
    int FirstY;
    Point2D *Spans;
};
typedef char WavePolygonInput_size[(sizeof(WavePolygonInput) == 0x38) ? 1 : -1];
typedef char WaveScanlineBuffer_size[(sizeof(WaveScanlineBuffer) == 0x0C) ? 1 : -1];

class WaveClass : public ObjectClass {
public:
    WaveClass(); // 0x007216D0
    WaveClass(CoordStruct const &start, CoordStruct const &end, TechnoClass *owner, int type, ObjectClass *target); // 0x007213A0
    WaveClass(NoInitClass const &noinit) : ObjectClass(noinit), Polygon_130(noinit), Scanlines_168(noinit) {}    // inline (Load)
    virtual ~WaveClass();                                           // 0x00721900

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x007223A0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                // 0x007221D0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00722330 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);    // 0x00722190 slot 10
    virtual int Kind_Of() const { return 0x2B; }                    // 0x007245F0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(WaveClass); }       // 0x007223E0 slot 12 (inline)
    virtual void AI();                                              // 0x00723220 slot 23
    virtual int unknown_slot29() const { return 3; }                // 0x007223F0 (inline)
    virtual ObjectTypeClass *Class_Of() const { return 0; }         // 0x00722400 slot 33 (inline)
    virtual bool unknown_slot52();                                  // 0x007224D0
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);              // 0x00722410
    void Brighten_Pixel_007219c0(int x, int offset, int row, unsigned short *pixel); // 0x007219C0
    void Set_Laser_Pixel_00721b00(unsigned short *pixel, int mult) const; // 0x00721B00 (TibSun Set_Laser_Pixel; inlined into 0x00722CB0)
    void unknown_func_722040(Cell const &cell);                         // 0x00722040 (adds a cell to Cells once)
    void unknown_func_721cc0();                                        // 0x00721CC0 (neighbour offsets from the surface stride)
    void Damage_Cell_00721eb0(CoordStruct const &coord);                // 0x00721EB0
    void unknown_func_7238b0(CoordStruct const &start, CoordStruct const &end); // 0x007238B0
    void Wave_Recalc_Affected_Cells();                                  // 0x00723360
    void Update_Wave_00724200();                                        // 0x00724200
    void unknown_func_7225b0(int arg1, int arg2);                      // 0x007225B0 (draws type 0)
    void unknown_func_722cb0(int arg1, int arg2);                      // 0x00722CB0 (draws types 1 and 2)
    void unknown_func_7232d0();                                        // 0x007232D0 (type 0 step)
    void unknown_func_723340();                                        // 0x00723340 (types 1 and 2 step)
    virtual void unknown_slot67(int arg1, int arg2);                // 0x00722530

    ObjectClass *Target;                        // +0x98 (constructorlastarg: firingtarget)
    int Type;                                   // +0x9C (0 sonic wave; 1 and 2 magnetron/beam waves; hypothesis)
    CoordStruct unknown_a0;                     // +0x0A0 start
    CoordStruct unknown_ac;                     // +0x0AC end
    Point2D unknown_b8; // +0x0B8 projectedpoint
    Point2D unknown_c0; // +0x0C0 projectedpoint
    Point2D unknown_c8; // +0x0C8 projectedpoint
    Point2D unknown_d0; // +0x0D0 projectedpoint
    Point2D unknown_d8; // +0xD8 projected outline corner
    Point2D unknown_e0; // +0xE0 projected outline corner
    CoordStruct WaveEndLeftCoord;               // +0x0E8 (TibSun names)
    CoordStruct WaveEndRightCoord;              // +0x0F4
    CoordStruct WaveStartLeftCoord;             // +0x100
    CoordStruct WaveStartRightCoord;            // +0x10C
    bool unknown_118; // +0x118 constructortrue
    bool unknown_119; // +0x119 constructorfalse
    char unknown_11a[2];
    int unknown_11c;                            // +0x11C frames left (100)
    double unknown_120; // +0x120 originalQWORD FPloads/stores
    double unknown_128; // +0x128 originalQWORD FPloads/stores
    WavePolygonInput Polygon_130; // +0x130 input points/buffer
    WaveScanlineBuffer Scanlines_168; // +0x168 rasterized spans
    int unknown_174[8];                         // +0x174 screen offsets of the 8 neighbours (Unknown_00721CC0)
    int unknown_194;                            // +0x194 direction (0..7)
    int unknown_198;                            // +0x198 fade (160, counts down by 6)
    TechnoClass *Owner;                         // +0x19C (constructorarg3: firingTechno)
    FacingClass Facing;                         // +0x1A0
    DynamicVectorClass<CellClass *> Cells;      // +0x1B8
    int PixelOffsets_1d0[13]; // +0x1D0 zero/neighbor/double/triple offsets, dynamicallyindexed7219C0
    char unknown_204[0x208 - 0x204];
};

// Builds the wave sine tables once (0x00721BF0; Westwood's WaveClass::Init_Statics;
// Fill_In_Data).
void __fastcall Initialize_Wave_Tables_00721bf0();


#endif
