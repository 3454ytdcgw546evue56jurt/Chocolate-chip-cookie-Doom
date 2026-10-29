#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

struct WAD_Directory
{
    void *LumpData;
    unsigned int size;
    char name[9];
};

struct WAD_Header
{
    char identification[5];
    unsigned int numlumps;
    WAD_Directory *Directories;

    WAD_Header(char *_identification,int _numlumps)
    {
        Directories = (WAD_Directory *) malloc(sizeof(WAD_Directory)*_numlumps);

        numlumps = _numlumps;
        identification[0] = identification[0];
        identification[1] = identification[1];
        identification[2] = identification[2];
        identification[3] = identification[3];
        identification[4] = 0x0;
    }
};

WAD_Header* Load_WAD(const char *FileName,WAD_Header* PatchWAD);
void WAD_Load_Directories(FILE* Wadfile,int Directories_Offset,WAD_Header *Header);