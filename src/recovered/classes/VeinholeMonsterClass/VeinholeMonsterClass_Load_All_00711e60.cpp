#include "shared/veinhole.hpp"
#include "shared/techno_index.hpp"
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_veinhole_buffer_ad07a0@@3PAEA=00ad07a0
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?Here_I_Am@SwizzleManagerClass@@QAGJJPAX@Z=0069fba0
// @ref ?unknown_object_index_abff58@@3V?$UnknownIndexClass@JPAVObjectClass@@@@A=00abff58

bool __fastcall VeinholeMonsterClass::Load_All(IStream *stream)
{
    Clear_All();

    int cell_count = unknown_cells_428ac0();

    int monster_count;
    if (FAILED(stream->Read(&monster_count, sizeof(monster_count), 0))) {
        return false;
    }

    unknown_veinhole_buffer_ad07a0 = new unsigned char[cell_count];
    if (FAILED(stream->Read(unknown_veinhole_buffer_ad07a0, cell_count, 0))) {
        return false;
    }

    for (int i = 0; i < monster_count; i++) {
        VeinholeMonsterClass *monster = (VeinholeMonsterClass *)new char[sizeof(VeinholeMonsterClass)];

        LONG id;
        if (FAILED(stream->Read(&id, sizeof(id), 0))) {
            return false;
        }

        SwizzleManager.Here_I_Am(id, monster);
        if (FAILED(stream->Read(monster, sizeof(VeinholeMonsterClass), 0))) {
            return false;
        }

        if (monster != 0) {
            new (monster) VeinholeMonsterClass(NoInitClass());
        }

        unsigned char *state = monster->unknown_b0;
        UnknownVeinHeap *queue = monster->unknown_9c;
        UnknownVeinNode *nodes = monster->unknown_a0;

        if (FAILED(stream->Read(state, cell_count, 0))) {
            return false;
        }
        monster->unknown_b0 = state;

        if (FAILED(stream->Read(nodes, sizeof(UnknownVeinNode) * Rules->unknown_d4, 0))) {
            return false;
        }
        monster->unknown_a0 = nodes;

        if (!queue->Load(stream, nodes)) {
            return false;
        }
        monster->unknown_9c = queue;

        unknown_object_index_abff58.Add_Index(monster->Fetch_ID(), monster);
    }

    return true;
}
