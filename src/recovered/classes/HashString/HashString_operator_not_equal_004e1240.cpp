bool HashString::operator!=(HashString const &other) const
{
    return strcmp(Text, other.Text) != 0;
}
