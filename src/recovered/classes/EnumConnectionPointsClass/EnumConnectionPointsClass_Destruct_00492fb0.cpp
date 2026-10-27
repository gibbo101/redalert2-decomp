EnumConnectionPointsClass::~EnumConnectionPointsClass() { for(int i=0;i<Points.Count();++i) Points[i]->Release(); Points.Clear(); }
