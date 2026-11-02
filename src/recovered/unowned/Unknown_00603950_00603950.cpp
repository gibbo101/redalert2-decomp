// void Unknown_00603950() (0x00603950; RulesClass::Process 0x006433A0): frees the extra palette names and empties
// the name and colour lists (the table is made on first use).

void Unknown_00603950()
{
    int count = Scheme_Table()->Names->Count();
    for (int index = 0; index < count; index++) {
        delete (*unknown_scheme_table_a76414->Names)[index];
    }
    unknown_scheme_table_a76414->Names->Clear();
    unknown_scheme_table_a76414->Colors->Clear();
}
