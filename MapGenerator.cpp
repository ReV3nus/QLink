#include "MapGenerator.h"

MapGenerator::MapGenerator()
{

}
void MapGenerator::Generate_Map(Cell* cell[11][18],bool blockUsed[73])
{
    random_generator.random_generate();
    for(int i=0;i<=13;i++)
    {
        int t=i+1;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        if(blockUsed[t])
        {
            cell[x1][y1]->setDisplay(empty,0);
            cell[x2][y2]->setDisplay(empty,0);
        }
        else
        {
            cell[x1][y1]->setDisplay(spade,i);
            cell[x2][y2]->setDisplay(spade,i);
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+15;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        if(blockUsed[t])
        {
            cell[x1][y1]->setDisplay(empty,0);
            cell[x2][y2]->setDisplay(empty,0);
        }
        else
        {
            cell[x1][y1]->setDisplay(heart,i);
            cell[x2][y2]->setDisplay(heart,i);
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+29;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        if(blockUsed[t])
        {
            cell[x1][y1]->setDisplay(empty,0);
            cell[x2][y2]->setDisplay(empty,0);
        }
        else
        {
            cell[x1][y1]->setDisplay(club,i);
            cell[x2][y2]->setDisplay(club,i);
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+43;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        if(blockUsed[t])
        {
            cell[x1][y1]->setDisplay(empty,0);
            cell[x2][y2]->setDisplay(empty,0);
        }
        else
        {
            cell[x1][y1]->setDisplay(diamond,i);
            cell[x2][y2]->setDisplay(diamond,i);
        }
    }
    for(int i=0;i<=15;i++)
    {
        int t=i+57;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        if(blockUsed[t])
        {
            cell[x1][y1]->setDisplay(empty,0);
            cell[x2][y2]->setDisplay(empty,0);
        }
        else
        {
            cell[x1][y1]->setDisplay(any,i);
            cell[x2][y2]->setDisplay(any,i);
        }
    }
}
void MapGenerator::Generate_DuoMap(Cell* cell[2][11][18],bool blockUsed[2][73])
{
    random_generator.random_generate();
    for(int i=0;i<=13;i++)
    {
        int t=i+1;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        for(int j=0;j<2;j++)
        {
            if(blockUsed[j][t])
            {
                cell[j][x1][y1]->setDisplay(empty,0);
                cell[j][x2][y2]->setDisplay(empty,0);
            }
            else
            {
                cell[j][x1][y1]->setDisplay(spade,i);
                cell[j][x2][y2]->setDisplay(spade,i);
            }
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+15;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        for(int j=0;j<2;j++)
        {
            if(blockUsed[j][t])
            {
                cell[j][x1][y1]->setDisplay(empty,0);
                cell[j][x2][y2]->setDisplay(empty,0);
            }
            else
            {
                cell[j][x1][y1]->setDisplay(heart,i);
                cell[j][x2][y2]->setDisplay(heart,i);
            }
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+29;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        for(int j=0;j<2;j++)
        {
            if(blockUsed[j][t])
            {
                cell[j][x1][y1]->setDisplay(empty,0);
                cell[j][x2][y2]->setDisplay(empty,0);
            }
            else
            {
                cell[j][x1][y1]->setDisplay(club,i);
                cell[j][x2][y2]->setDisplay(club,i);
            }
        }
    }
    for(int i=0;i<=13;i++)
    {
        int t=i+43;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        for(int j=0;j<2;j++)
        {
            if(blockUsed[j][t])
            {
                cell[j][x1][y1]->setDisplay(empty,0);
                cell[j][x2][y2]->setDisplay(empty,0);
            }
            else
            {
                cell[j][x1][y1]->setDisplay(diamond,i);
                cell[j][x2][y2]->setDisplay(diamond,i);
            }
        }
    }
    for(int i=0;i<=15;i++)
    {
        int t=i+57;
        int x1=random_generator._pos1[t].x;
        int x2=random_generator._pos2[t].x;
        int y1=random_generator._pos1[t].y;
        int y2=random_generator._pos2[t].y;
        for(int j=0;j<2;j++)
        {
            if(blockUsed[j][t])
            {
                cell[j][x1][y1]->setDisplay(empty,0);
                cell[j][x2][y2]->setDisplay(empty,0);
            }
            else
            {
                cell[j][x1][y1]->setDisplay(any,i);
                cell[j][x2][y2]->setDisplay(any,i);
            }
        }
    }
}
