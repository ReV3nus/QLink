#ifndef POSITION_H
#define POSITION_H

struct Position
{
    int x,y;
    Position(int xx,int yy)
    {
        x=xx,y=yy;
    }
    Position()
    {
        x=0,y=0;
    }
    Position operator +(const Position &b)
    {
        return Position(x+b.x,y+b.y);
    }
    bool operator ==(const Position &b)
    {
        return (x==b.x)&&(y==b.y);
    }
};
#endif // POSITION_H
