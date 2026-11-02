// SchemeTable::~SchemeTable() (0x00604250; Unknown_00603FA0): frees the extra palettes and both lists, every
// node and its schemes, then the table.

SchemeTable::~SchemeTable()
{
    if (Table != 0) {
        Unknown_00603950();
        delete Names;
        delete Colors;
        UnknownSchemeListIterator it;
        HashString *key = Table->Next(it);
        while (key != 0) {
            SchemeNode **node = Table->Find(*key);
            delete *node;
            key = Table->Next(it);
        }
        Table->Clear();
        delete Table;
    }
}
