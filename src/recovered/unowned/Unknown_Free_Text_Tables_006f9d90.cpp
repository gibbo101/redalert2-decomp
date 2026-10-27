// void Unknown_006F9D90() (0x006F9D90)
// Frees the string manager's data (hypothesis: the text manager of 0x006F9EC0): the chunk
// list at 0x00AD0458, the two pointer tables (0x00AD0444, 0x00AD0448) of
// 0x00AD043C entries with their entries, the table 0x00AD0440 and the chunk
// list at 0x00AD0454; the counter 0x00AD044C resets.
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_chunks_ad0458@@3PAUUnknownTextChunk@@A=00ad0458
// @ref ?unknown_table_ad0444@@3PAPAXA=00ad0444
// @ref ?unknown_table_ad0448@@3PAPAXA=00ad0448
// @ref ?unknown_index_ad0440@@3PAXA=00ad0440
// @ref ?unknown_chunks_ad0454@@3PAUUnknownTextChunk@@A=00ad0454
// @ref ?unknown_count_ad043c@@3HA=00ad043c
// @ref ?unknown_total_ad044c@@3HA=00ad044c

struct UnknownTextChunk {
    UnknownTextChunk *Next;
};
extern UnknownTextChunk *unknown_chunks_ad0458;
extern void **unknown_table_ad0444;
extern void **unknown_table_ad0448;
extern void *unknown_index_ad0440;
extern UnknownTextChunk *unknown_chunks_ad0454;
extern int unknown_count_ad043c;
extern int unknown_total_ad044c;

void Unknown_006F9D90()
{
    while (unknown_chunks_ad0458) {
        UnknownTextChunk *chunk = unknown_chunks_ad0458;
        unknown_chunks_ad0458 = chunk->Next;
        delete chunk;
    }
    unknown_chunks_ad0458 = 0;
    if (unknown_table_ad0444) {
        for (int index = 0; index < unknown_count_ad043c; index++) {
            if (unknown_table_ad0444[index]) {
                delete unknown_table_ad0444[index];
            }
        }
        delete unknown_table_ad0444;
        unknown_table_ad0444 = 0;
    }
    if (unknown_table_ad0448) {
        for (int index = 0; index < unknown_count_ad043c; index++) {
            if (unknown_table_ad0448[index]) {
                delete unknown_table_ad0448[index];
            }
        }
        delete unknown_table_ad0448;
        unknown_table_ad0448 = 0;
    }
    if (unknown_index_ad0440) {
        delete unknown_index_ad0440;
        unknown_index_ad0440 = 0;
    }
    UnknownTextChunk *chunk = unknown_chunks_ad0454;
    while (chunk) {
        UnknownTextChunk *next = chunk->Next;
        delete chunk;
        chunk = next;
    }
    unknown_chunks_ad0454 = 0;
    unknown_total_ad044c = 0;
}
