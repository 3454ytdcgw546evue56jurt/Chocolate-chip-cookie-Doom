#pragma once
#include "../Math/Vectors.h"

struct Sector
{
    Vector2D *Point;
    int *Lines;
    int *Sides;
};

struct LEVEL
{
    Sector *Sector;
};

LEVEL *load_level(WAD_Header *Header,int Level,int episode);

void unload_level(LEVEL * Level);