#include "shared/compressed_file.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Unknown_Uncompress_Data_0053aeb0=0053aeb0
int __fastcall Load_Compressed_Data_004953b0(FileClass &file, Buffer const &scratch,
    Buffer const &output, void *extra)
{
    void *destination = output.Get_Buffer();
    char *data = (char *)scratch.Get_Buffer();
    int close_file = 0;
    if (!file.Is_Open()) {
        if (!file.Open(FILE_RIGHTS_READ)) return 0;
        close_file = 1;
    }
    unsigned short bytes;
    file.Read(&bytes, 2);
    CompressedFileHeader header;
    file.Read(&header, sizeof(header));
    bytes -= sizeof(header);
    if (header.ExtraBytes) {
        bytes -= header.ExtraBytes;
        if (extra) file.Read(extra, header.ExtraBytes);
        else file.Seek(header.ExtraBytes, FILE_SEEK_CURRENT);
        header.ExtraBytes = 0;
    }
    if (scratch.Get_Buffer() == output.Get_Buffer())
        data += scratch.Get_Size() - bytes - sizeof(header);
    memmove(data, &header, sizeof(header));
    file.Read(data + sizeof(header), bytes);
    bytes = (unsigned short)Unknown_Uncompress_Data_0053aeb0(data, destination);
    if (close_file) file.Close();
    return bytes;
}
