#pragma once

// Observed 12-byte intrusive-link prefix shared by the inspected dispatch tables.
// This view does not claim the full concrete class identity or allocation size.
// Insertion has accepted source; endpoint bodies remain unrecovered.
class LinkPrefix_00539040 {
public:
    unsigned char* dispatch_table;
    LinkPrefix_00539040* next;
    LinkPrefix_00539040* previous;
    LinkPrefix_00539040* FindPreviousEndpoint_00539040();
    LinkPrefix_00539040* FindNextEndpoint_00539070();
    LinkPrefix_00539040* InsertAfterAndFindFirst_005390a0(LinkPrefix_00539040* preceding);
};
typedef char LinkPrefix_size_check[(sizeof(LinkPrefix_00539040)==12)?1:-1];
