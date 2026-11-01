// StorageClass::StorageClass() (0x0069ADA0): every slot empty. Storage.cpp (0x0069ABD0-0x0069B00F; TibSun storage.cpp
// with float amounts).
#define STORAGE_CLASS_UNIT
#include "shared/storage_class.hpp"
#include "shared/tiberium.hpp"

StorageClass::StorageClass()
{
    for (int i = 0; i < 4; i++) {
        Amounts[i] = 0;
    }
}
