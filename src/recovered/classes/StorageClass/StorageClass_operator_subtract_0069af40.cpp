// StorageClass StorageClass::operator-(StorageClass const &that) const (0x0069AF40).
StorageClass StorageClass::operator-(StorageClass const &that) const
{
    StorageClass tmp;
    for (int i = 0; i < 4; i++) {
        tmp.Amounts[i] = Amounts[i] - that.Amounts[i];
    }
    return tmp;
}
