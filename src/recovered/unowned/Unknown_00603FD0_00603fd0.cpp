// void Unknown_00603FD0() (0x00603FD0): makes the scheme table unless it exists.

void Unknown_00603FD0()
{
    if (unknown_scheme_table_a76414 == 0) {
        unknown_scheme_table_a76414 = new SchemeTable;
    }
}
