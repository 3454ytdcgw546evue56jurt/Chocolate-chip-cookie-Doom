#include "WAD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <errno.h>

#define wad_identification_size 4
#define wad_numlumps_size 4
#define wad_infotableofs_size 4

#define wad_dir_filepos 4
#define wad_dir_size 4
#define wad_dir_name 8

WAD_Header* Load_WAD(const char *FileName, WAD_Header* PatchWAD)
{
    FILE* Wadfile;

    Wadfile = fopen(FileName, "rb");

    // Opening the file in read mode

    if(Wadfile == NULL) 
    {
        printf("Error opening the file %s. \n",FileName);
        printf("Error %s\n", strerror(errno));
        return nullptr;
    }

    int file_size = 0;
    
    char identification[4];
    fread(&identification, wad_identification_size, 1, Wadfile);

    bool Patch_file = false;
    if(strcmp((const char*) &identification,"IWAD") == 0)
    {

    }
    else if(strcmp((const char*) &identification,"PWAD") == 0)
    {
        //TODO
        printf("Error opening the file. Unimplented Patch wads\n");
        return nullptr;

        if(PatchWAD == nullptr)
        {
            printf("Error opening the file. Patch wads need to load the Internal WAD first\n");
            return nullptr;
        }
        Patch_file = true;
    }
    else
    {
        printf("Error opening the file %s. Unimplented WAD format or not a WAD\n",&identification);
        return nullptr;
    }

    int numlumps = 0;
    fread(&numlumps, wad_numlumps_size, 1, Wadfile);
    int DirOffset = 0;
    fread(&DirOffset, wad_infotableofs_size, 1, Wadfile);

    printf("WAD dir offset: %d,Number of lumps: %d,WAD ID: %s\n",DirOffset,numlumps,&identification);
    
    WAD_Header *Header = new WAD_Header(identification,numlumps);
    WAD_Load_Directories(Wadfile,DirOffset,Header);

    fclose(Wadfile);
    return Header;
}

void WAD_Load_Directories(FILE* Wadfile,int Directories_Offset,WAD_Header *Header)
{
    fseek(Wadfile,Directories_Offset,SEEK_SET);

    int WAD_Lumps_ammout = Header->numlumps;

    int LumpPos = 0;
    int LumpSize = 0;
    char LumpName[9];

    int FilePos;
    for(int i = 0;i<WAD_Lumps_ammout;i++)
    {
        fread(&LumpPos, wad_dir_filepos, 1, Wadfile);
        fread(&LumpSize, wad_dir_size, 1, Wadfile);
        fread(&LumpName, wad_dir_name, 1, Wadfile);
        LumpName[9] = 0x0;
        printf("Lump %s size:%d\n",&LumpName,LumpSize);
        
        //Preseving the file position before copying the lump data
        FilePos = ftell(Wadfile);

        void *LumpData = malloc(LumpSize);
        fseek(Wadfile,LumpPos,SEEK_SET);
        fread(LumpData, LumpSize, 1, Wadfile);
        fseek(Wadfile,FilePos,SEEK_SET);

        Header->Directories[i].LumpData = LumpData;
        strcpy((char*) &Header->Directories[i].name,(const char*) &LumpName);
        Header->Directories[i].size = LumpSize;
    }
}

int Lump_get_index(const char *Lump_name,WAD_Header *Header,int starting_id)
{
    int Lump_ammount = Header->numlumps;
    WAD_Directory *Directories = Header->Directories;
    WAD_Directory *Directory = nullptr;

    for(int i = starting_id;i<Lump_ammount;i++)
    {
        Directory = &Directories[i];

        if(strcmp(Directory->name,Lump_name) == 0)
        {
            return 0;
        }
    }

    return -1;
}