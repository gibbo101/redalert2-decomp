// UnknownListEntry_6017c0::UnknownListEntry_6017c0(UnknownListEntry_6017c0 const &) (0x00601780): the 24-byte
// ownrdraw.cpp list element's member-wise copy (the two WideStrings through their copy constructor); the struct is
// defined beside 0x00601490. Called by the list's add (0x006025A0).
UnknownListEntry_6017c0::UnknownListEntry_6017c0(UnknownListEntry_6017c0 const &other)
    : unknown_00(other.unknown_00), unknown_04(other.unknown_04), unknown_08(other.unknown_08),
      unknown_0c(other.unknown_0c), unknown_10(other.unknown_10), unknown_14(other.unknown_14)
{
}
