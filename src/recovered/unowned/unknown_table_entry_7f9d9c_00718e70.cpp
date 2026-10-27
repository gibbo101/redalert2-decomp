// int __fastcall unknown_table_entry_7f9d9c(int index) -- 0x00718E70
// Purpose: entry `index` of the word table at 0x007F9D9C.
// Assumptions: what the table holds is unknown.
// @ref ?unknown_table_7f9d9c@@3PAHA=007f9d9c

extern int unknown_table_7f9d9c[];

int __fastcall unknown_table_entry_7f9d9c(int index)
{
    return unknown_table_7f9d9c[index];
}
