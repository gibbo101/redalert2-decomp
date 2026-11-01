// StorageClass StorageClass::operator+=(StorageClass const &that) (0x0069AF00).
StorageClass StorageClass::operator+=(StorageClass const &that)
{
    for (int i = 0; i < 4; i++) {
        Amounts[i] += that.Amounts[i];
    }
    return *this;
}
