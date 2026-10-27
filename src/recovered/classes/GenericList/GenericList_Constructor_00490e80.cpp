#define LIST_DECLARE_CONSTRUCTOR
#define GENERIC_LIST_IMPLEMENT_CONSTRUCTOR
#include "shared/ini_class.hpp"
// @ref ??_7GenericList@@6B@=0079aaf4
// @ref ??_7GenericNode@@6B@=0079aafc
GenericList::GenericList() { FirstNode.Link(&LastNode); }
