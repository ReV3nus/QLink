#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "Cell.h"
#include "randomgenerator.h"
class MapGenerator
{
public:
    MapGenerator();
    void Generate_Map(Cell* cell[11][18],bool blockUsed[73]);
    void Generate_DuoMap(Cell* cell[2][11][18],bool blockUsed[2][73]);
private:
    Random_Generator random_generator;
};

#endif // MAPGENERATOR_H
