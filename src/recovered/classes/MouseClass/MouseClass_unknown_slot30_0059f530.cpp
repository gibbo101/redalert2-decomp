// HRESULT MouseClass::unknown_slot30(IStream *stream) (0x0059F530, slot 30)
// Loads the whole screen object: the layers' own loads, then the raw object
// image (0x4F3C bytes), rebuilt in place with the load constructor, its
// pointers swizzled and the map buffers and hash tables rebuilt, followed
// by the saved vectors; the theater types are reinitialized last.
#include "shared/mouse_class.hpp"
#include "shared/map_cell.hpp"
#include "shared/anim_type.hpp"
#include "shared/building_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/terrain_type.hpp"
#include "shared/map_view.hpp"
// @ref ??0?$VectorClass@U?$HashObject@II@@@@QAE@IPBU?$HashObject@II@@@Z=0056cdd0
// @ref ??0?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@QAE@IPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056ce50
// @ref ??8?$VectorClass@U?$HashObject@II@@@@UBE_NABV0@@Z=0056bef0
// @ref ??8?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UBE_NABV0@@Z=0056c040
// @ref ??_7?$DynamicVectorClass@U?$HashObject@II@@@@6B@=007a5a78
// @ref ??_7?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@6B@=007a5a58
// @ref ??_7?$VectorClass@U?$HashObject@II@@@@6B@=007a5af8
// @ref ??_7?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@6B@=007a5b18
// @ref ??_E?$DynamicVectorClass@U?$HashObject@II@@@@UAEPAXI@Z=0056c410
// @ref ??_E?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEPAXI@Z=0056c620
// @ref ??_E?$VectorClass@U?$HashObject@II@@@@UAEPAXI@Z=0056c910
// @ref ??_E?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEPAXI@Z=0056c960
// @ref ??_G?$VectorClass@U?$HashObject@II@@@@UAEPAXI@Z=0056c910
// @ref ??_G?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEPAXI@Z=0056c960
// @ref ?Clear@?$DynamicVectorClass@U?$HashObject@II@@@@UAEXXZ=0056ad40
// @ref ?Clear@?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEXXZ=0056adb0
// @ref ?Clear@?$VectorClass@U?$HashObject@II@@@@UAEXXZ=0056c590
// @ref ?Clear@?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEXXZ=0056c7d0
// @ref ?Fetch@?$VectorClass@U?$HashObject@II@@@@UBE?AU?$HashObject@II@@H@Z=0056ad90
// @ref ?Fetch@?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UBE?AU?$HashObject@IUSubzoneConnectionStruct@@@@H@Z=0056ae10
// @ref ?ID@?$DynamicVectorClass@U?$HashObject@II@@@@UAEHABU?$HashObject@II@@@Z=0056c010
// @ref ?ID@?$DynamicVectorClass@U?$HashObject@II@@@@UAEHPBU?$HashObject@II@@@Z=0056ad70
// @ref ?ID@?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEHABU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056c180
// @ref ?ID@?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEHPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056ade0
// @ref ?ID@?$VectorClass@U?$HashObject@II@@@@UAEHABU?$HashObject@II@@@Z=0056c5c0
// @ref ?ID@?$VectorClass@U?$HashObject@II@@@@UAEHPBU?$HashObject@II@@@Z=0056c600
// @ref ?ID@?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEHABU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056c800
// @ref ?ID@?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAEHPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056c840
// @ref ?Resize@?$DynamicVectorClass@U?$HashObject@II@@@@UAE_NHPBU?$HashObject@II@@@Z=0056bf30
// @ref ?Resize@?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAE_NHPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056c080
// @ref ?Resize@?$VectorClass@U?$HashObject@II@@@@UAE_NHPBU?$HashObject@II@@@Z=0056c4c0
// @ref ?Resize@?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@UAE_NHPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056c6d0
// @ref ?Unknown_0052B2E0@@YIX_N0@Z=0052b2e0
// @ref ?Load@SidebarClass@@UAEJPAUIStream@@@Z=00682290
// @ref ?unknown_loaded_theater_7d88dc@@3HA=007d88dc
// @ref ??0TabClass@@QAE@ABVNoInitClass@@@Z=0059ff60
// @ref ?Swizzle@SwizzleManagerClass@@QAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Unknown_Hash_0054F240@@YIIABI@Z=0054f240
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __imp__OleLoadFromStream@12=0079a5ec
// @ref _IID_IUnknown_7afce0=007afce0
// @ref ?Init@TerrainTypeClass@@SIXH@Z=006e5460
// @ref ?Unknown_00529870@@YIXH_N@Z=00529870
// @ref ?Unknown_0052B650@@YAXXZ=0052b650
// @ref ?Unknown_0052B2E0@@YI_N_N@Z=0052b2e0
// @ref ?Init@OverlayTypeClass@@SIXH@Z=005dc960
// @ref ?Init@BuildingTypeClass@@SIXH@Z=00458600
// @ref ?Init@AnimTypeClass@@SIXH@Z=00425230
// @ref ?Init@SmudgeTypeClass@@SIXH@Z=00687fb0
// @ref ??0?$DynamicVectorClass@U?$HashObject@II@@@@QAE@IPBU?$HashObject@II@@@Z=0059ffe0

// The zone cell table: 256 buckets, growth step 20 (as MapClass::One_Time builds it).
static HashTableClass<unsigned int, unsigned int> *New_Cell_Table()
{
    return new HashTableClass<unsigned int, unsigned int>(Unknown_Hash_0054F240, 256, 20);
}

HRESULT MouseClass::unknown_slot30(IStream *stream)
{
    unknown_1158.Clear();
    unknown_d0.Clear();
    HRESULT result = SidebarClass::unknown_slot30(stream);
    if (result < 0) {
        return result;
    }
    int unused;
    result = stream->Read(&unused, 4, 0);
    if (result < 0) {
        return result;
    }
    unknown_loaded_theater_7d88dc = -1;
    unknown_slot23();
    delete unknown_6c;
    unknown_6c = 0;
    delete unknown_64;
    unknown_64 = 0;
    delete unknown_14;
    unknown_14 = 0;
    for (int clear = 0; clear < 3; clear++) {
        SubzoneTracking[clear].Clear();
    }
    for (int free_buffer = 0; free_buffer < 12; free_buffer++) {
        delete unknown_18[free_buffer];
        unknown_18[free_buffer] = 0;
    }
    for (int free_table = 0; free_table < 3; free_table++) {
        if (unknown_7c[free_table] != 0) {
            delete unknown_7c[free_table];
            unknown_7c[free_table] = 0;
        }
    }
    Cells.Clear();
    result = stream->Read(this, 0x4F3C, 0);
    if (result < 0) {
        return result;
    }
    new (this) MouseClass(NoInitClass());
    for (int strip = 0; strip < 4; strip++) {
        UnknownBuildable30 *buildable = Column[strip].Buildables;
        for (int item = 0; item < 75; item++) {
            Swizzle_Pointer(buildable[item].Factory);
        }
    }
    Swizzle_Pointer(unknown_11a0);
    Swizzle_Pointer(unknown_11a4);
    Swizzle_Pointer(unknown_119c);
    unknown_slot22();
    unknown_slot24();
    unknown_6c = 0;
    unknown_64 = 0;
    unknown_slot28(&MapSize, true, false, false);
    if (unknown_6c != 0) {
        delete unknown_6c;
        unknown_6c = 0;
    }
    if (unknown_64 != 0) {
        delete unknown_64;
        unknown_64 = 0;
    }
    unknown_6c = new char[unknown_68 * 10];
    unknown_64 = new UnknownMapElem4[unknown_68];
    unknown_14 = New_Cell_Table();
    for (int tier = 0; tier < 3; tier++) {
        int factor = 1 << (tier + 1);
        SubzoneTracking[tier].Clear();
        int cells = MapSize.Height * MapSize.Width * 4;
        SubzoneTracking[tier].Set_Growth_Step(cells / (factor * factor));
        unknown_7c[tier] = new HashTableClass<unsigned int, SubzoneConnectionStruct>(Unknown_Hash_0054F240, 256, 20);
    }
    result = stream->Read(unknown_64, unknown_68 * 4, 0);
    if (result < 0) {
        return result;
    }
    for (int buffer = 0; buffer < 12; buffer++) {
        unknown_18[buffer] = new char[unknown_48 * 2];
        result = stream->Read(unknown_18[buffer], unknown_48 * 2, 0);
        if (result < 0) {
            return result;
        }
    }
    int zones = 0;
    result = stream->Read(&zones, 4, 0);
    if (result < 0) {
        return result;
    }
    ZoneConnections.Clear();
    for (int zone = 0; zone < zones; zone++) {
        ZoneConnectionClass connection;
        result = stream->Read(&connection, sizeof(connection), 0);
        if (result < 0) {
            return result;
        }
        ZoneConnections.Add(connection);
    }
    for (int cell = 0; cell < Cells.Length(); cell++) {
        if (Cells[cell] != 0) {
            delete Cells[cell];
            Cells[cell] = 0;
        }
    }
    int count;
    result = stream->Read(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int object = 0; object < count; object++) {
        void *loaded;
        OleLoadFromStream(stream, IID_IUnknown_7afce0, &loaded);
    }
    result = stream->Read(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int entry = 0; entry < count; entry++) {
        Cell cell;
        result = stream->Read(&cell, 4, 0);
        if (result < 0) {
            return result;
        }
        unknown_1158.Add(cell);
    }
    result = stream->Read(&count, 4, 0);
    if (result < 0) {
        return result;
    }
    for (int entry2 = 0; entry2 < count; entry2++) {
        Cell cell;
        result = stream->Read(&cell, 4, 0);
        if (result < 0) {
            return result;
        }
        unknown_d0.Add(cell);
    }
    TerrainTypeClass::Init(unknown_id_source_a3d290->Theater);
    if (unknown_id_source_a3d290->Theater != unknown_loaded_theater_7d88dc) {
        Unknown_00529870(unknown_id_source_a3d290->Theater, true);
    } else {
        Unknown_0052B650();
    }
    Unknown_0052B2E0(false, false);
    OverlayTypeClass::Init(unknown_id_source_a3d290->Theater);
    BuildingTypeClass::Init(unknown_id_source_a3d290->Theater);
    AnimTypeClass::Init(unknown_id_source_a3d290->Theater);
    SmudgeTypeClass::Init(unknown_id_source_a3d290->Theater);
    unknown_11b8 = 0;
    unknown_loaded_theater_7d88dc = unknown_id_source_a3d290->Theater;
    return 0;
}
