HashString &HashString::operator=(HashString const &other)
{
    strcpy(Text, other.Text);
    return *this;
}
