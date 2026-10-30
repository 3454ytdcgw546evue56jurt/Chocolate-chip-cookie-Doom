#include "Level.h"
#include "../WAD/WAD.h"
#include "../Math/Vectors.h"

LEVEL *load_level(WAD_Header *Header,int level,int episode)
{
    int Level_map_len = snprintf(NULL, 0, "E%dM%D", level,episode);
    char *Map_str = (char *) malloc(Level_map_len + 1);
    snprintf(Map_str, Level_map_len + 1, "%d", level,episode);

    int level_lump_start_id = Lump_get_index((const char*) Map_str,Header,0);

    Lump_get_index("THINGS",Header,level_lump_start_id);
    Lump_get_index("LINEDEFS",Header,level_lump_start_id);
    Lump_get_index("SIDEDEFS",Header,level_lump_start_id);
    int vertices_id = Lump_get_index("VERTEXES",Header,level_lump_start_id);

    Lump_get_index("SEGS",Header,level_lump_start_id);
    Lump_get_index("SSECTORS",Header,level_lump_start_id);
    Lump_get_index("NODES",Header,level_lump_start_id);
    Lump_get_index("SECTORS",Header,level_lump_start_id);

    Lump_get_index("REJECT",Header,level_lump_start_id);
    Lump_get_index("BLOCKMAP",Header,level_lump_start_id);

    LEVEL *Curr_level = new LEVEL();

    //Loading maps vertices
    int vertices_ammout = Header->Directories[vertices_id].size/4;
    for(int i = 0;i<vertices_ammout;i++)
    {
        float x = (signed short) Header->Directories[vertices_id].LumpData;
        float y = (signed short) Header->Directories[vertices_id+2].LumpData;

        
    }
    

    int level_lump_end_id = Lump_get_index("BLOCKMAP",Header,level_lump_start_id);

    free(Map_str);
    return Curr_level;
}

void unload_level(LEVEL * Level)
{

}