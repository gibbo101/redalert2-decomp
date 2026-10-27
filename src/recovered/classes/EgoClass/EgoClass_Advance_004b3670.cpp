#include "shared/ego.hpp"
bool EgoClass::Advance(int amount) { Y -= amount; bool expired = Y < -20; return expired; }
