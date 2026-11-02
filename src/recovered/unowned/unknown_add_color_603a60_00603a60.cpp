// void __fastcall unknown_add_color_603a60(char const *name, HSVClass const &color) (0x00603A60; RulesClass::Colors
// 0x00647E60): adds an extra palette name (a 256-byte copy) and its colour (the table is made on first use).

void __fastcall unknown_add_color_603a60(char const *name, HSVClass const &color)
{
    Scheme_Table();
    char *copy = new char[0x100];
    strcpy(copy, name);
    unknown_scheme_table_a76414->Names->Add(copy);
    unknown_scheme_table_a76414->Colors->Add(color);
}
