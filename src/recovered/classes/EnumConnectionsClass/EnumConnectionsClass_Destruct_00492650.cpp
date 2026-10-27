EnumConnectionsClass::~EnumConnectionsClass() { for (int i=0;i<Connections.Count();++i) Connections[i].pUnk->Release(); Connections.Clear(); }
