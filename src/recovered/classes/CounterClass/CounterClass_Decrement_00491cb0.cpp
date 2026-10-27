int CounterClass::Decrement(int index) { if (Ensure_Index(index)) { --Vector[index]; return Vector[index]; } return 0; }
