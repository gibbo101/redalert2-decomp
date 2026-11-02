// void SchemeTable::Add_Node(char const *name) (0x00604870): files a node with a freshly built list under the name.
// @ref ?Build_Schemes@SchemeTable@@QAEPAV?$DynamicVectorClass@PAVColorScheme@@@@PBD@Z=00604540

void SchemeTable::Add_Node(char const *name)
{
    DynamicVectorClass<ColorScheme *> *schemes = Build_Schemes(name);
    SchemeNode *node = new SchemeNode(name, schemes);
    Table->Add(name, node);
}
