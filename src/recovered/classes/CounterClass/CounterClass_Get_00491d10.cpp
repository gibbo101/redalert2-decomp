int CounterClass::Get(int index) { if (Ensure_Index(index)) return Vector[index]; return 0; }
