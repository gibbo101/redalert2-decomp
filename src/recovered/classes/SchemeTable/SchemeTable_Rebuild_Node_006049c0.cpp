// void SchemeTable::Rebuild_Node(char const *name) (0x006049C0): replaces the named node's list with a fresh
// one (the node must exist).

void SchemeTable::Rebuild_Node(char const *name)
{
    SchemeNode *node = *Table->Find(name);
    DynamicVectorClass<ColorScheme *> *schemes = Build_Schemes(name);
    node->unknown_603320();
    node->Schemes = schemes;
}
