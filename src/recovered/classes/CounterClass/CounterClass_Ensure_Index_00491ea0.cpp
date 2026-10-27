bool CounterClass::Ensure_Index(int index) {
 int old_size=VectorMax;
 if(index<old_size) return true;
 if(Resize(index+10)) {
  for(int i=old_size;i<VectorMax;++i) Vector[i]=0;
  return true;
 }
 return false;
}
