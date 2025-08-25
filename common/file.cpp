#include <string.h>

#include "file.h"

const CncLogger Find_File_Data::Logger = CncLogger("Find_File_Data");

#ifndef _WIN32
static void Resolve_File_Single(char* fname)
{
    Find_File_Data* ffblk;

    ffblk = Find_File_Data::CreateFindData();

    if (ffblk == nullptr) {
        return;
    }

    size_t name_len = strlen(fname);

    if (ffblk->FindFirst(fname) && name_len == strlen(ffblk->GetFullName())) {
        strncpy(fname, ffblk->GetFullName(), name_len + 1);
    }

    delete ffblk;
}
#endif

void Resolve_File(char* fname)
{
#ifndef _WIN32
    // step through each sub-directory before going for the win
    char* next = fname;
    while (next = strchr(next, '/')) {
        *next = '\0';
        Resolve_File_Single(fname);
        *next++ = '/';
    }

    Resolve_File_Single(fname);
#endif
}

bool Find_First(const char* fname, unsigned int mode, Find_File_Data** ffblk)
{
    if (ffblk == nullptr) {
        return false;
    }
    *ffblk = nullptr;

    *ffblk = Find_File_Data::CreateFindData();
    if ((*ffblk)->FindFirst(fname)) {
        return true;
    }

    delete *ffblk;
    *ffblk = nullptr;

    return false;
}

bool Find_Next(Find_File_Data* ffblk)
{
    if (ffblk == nullptr) {
        return false;
    }

    return ffblk->FindNext();
}

void Find_Close(Find_File_Data* ffblk)
{
    if (ffblk != nullptr) {
        delete ffblk;
    }
}
