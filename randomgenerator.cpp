#include "randomgenerator.h"
#include<QRandomGenerator64>
#include<vector>
#include<cstring>
#include<QDebug>

std::vector<int>dolist;
bool filled[11][18];
std::vector<std::vector<Position>>Conn;
int used[11][18];
void random_init()
{
    memset(used,0,sizeof(used));
    memset(filled,0,sizeof(filled));
    dolist.clear();
    Conn.clear();
    for(int i=1;i<=72;i++)
        dolist.push_back(i);
    for(int i=0;i<18;i++)
        filled[0][i]=filled[10][i]=1;
    for(int i=0;i<11;i++)
        filled[i][0]=filled[i][17]=1;
    std::vector<Position>tmp;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
            tmp.push_back(Position(i,j));
    Conn.push_back(tmp);

}
void _dfs(Position u,int dirx,int diry,int times)
{
    used[u.x][u.y]=1;
    if(!filled[u.x+dirx][u.y+diry])_dfs(Position(u.x+dirx,u.y+diry),dirx,diry,times);
    if(times==2)return;
    if(dirx)
    {
        if(!filled[u.x][u.y+1])_dfs(Position(u.x,u.y+1),0,1,times+1);
        if(!filled[u.x][u.y-1])_dfs(Position(u.x,u.y-1),0,-1,times+1);
    }
    else
    {
        if(!filled[u.x+1][u.y])_dfs(Position(u.x+1,u.y),1,0,times+1);
        if(!filled[u.x-1][u.y])_dfs(Position(u.x-1,u.y),-1,0,times+1);
    }
}
bool check_conn(Position a,Position b)
{
    memset(used,0,sizeof(used));
    used[a.x][a.y]=1;
    if(!filled[a.x+1][a.y])_dfs(Position(a.x+1,a.y),1,0,1);
    if(!filled[a.x-1][a.y])_dfs(Position(a.x-1,a.y),-1,0,1);
    if(!filled[a.x][a.y+1])_dfs(Position(a.x,a.y+1),0,1,1);
    if(!filled[a.x][a.y-1])_dfs(Position(a.x,a.y-1),0,-1,1);
    if(used[b.x][b.y])return 1;
    Position c=b;
    while(1)
    {
        c.x++;
        if(filled[c.x][c.y])break;
        if(used[c.x][c.y])return 1;
    }
    c=b;
    while(1)
    {
        c.x--;
        if(filled[c.x][c.y])break;
        if(used[c.x][c.y])return 1;
    }
    c=b;
    while(1)
    {
        c.y++;
        if(filled[c.x][c.y])break;
        if(used[c.x][c.y])return 1;
    }
    c=b;
    while(1)
    {
        c.y--;
        if(filled[c.x][c.y])break;
        if(used[c.x][c.y])return 1;
    }
    return 0;
}
void _checkdfs(int x,int y,int *cnt,int usedid)
{
    used[x][y]=usedid;
    (*cnt)++;
    if(!filled[x+1][y]&&!used[x+1][y])_checkdfs(x+1,y,cnt,usedid);
    if(!filled[x-1][y]&&!used[x-1][y])_checkdfs(x-1,y,cnt,usedid);
    if(!filled[x][y+1]&&!used[x][y+1])_checkdfs(x,y+1,cnt,usedid);
    if(!filled[x][y-1]&&!used[x][y-1])_checkdfs(x,y-1,cnt,usedid);
}
bool check_avai(int tmpi)
{
    memset(used,0,sizeof(used));
    std::vector<Position>conn=Conn[tmpi];
    int cnt=0,goal=conn.size();
    int startx,starty;
    int usedid=1;
    int i1=-1,i2=-1;
    for(int i=0;i<goal;i++)
    {
        int nowx=conn[i].x,nowy=conn[i].y;
        if(filled[nowx][nowy])
        {
            if(i1==-1)i1=i;
            else i2=i;
            continue;
        }
    }
    for(int i=0;i<goal;i++)
    {
        int nowx=conn[i].x,nowy=conn[i].y;
        if(!filled[nowx][nowy]&&!used[nowx][nowy])
        {
            _checkdfs(nowx,nowy,&cnt,usedid);
            break;
        }
    }
//    qDebug("step 1: get i1=%d i2=%d cnt=%d goal=%d\n",i1,i2,cnt,goal);
    if(cnt==goal-2)
    {
        if(i1>i2)std::swap(i1,i2);
        Conn[tmpi].erase(Conn[tmpi].begin()+i2);
        Conn[tmpi].erase(Conn[tmpi].begin()+i1);
        if(Conn[tmpi].size()==0)Conn.erase(Conn.begin()+tmpi);
        return 1;
    }
    if(cnt&1)return 0;
    while(cnt<goal-2)
    {
        int nowcnt=0;
        usedid++;
        for(int i=0;i<goal;i++)
        {
            int nowx=conn[i].x,nowy=conn[i].y;
            if(filled[nowx][nowy]||used[nowx][nowy])continue;
            _checkdfs(nowx,nowy,&nowcnt,usedid);
            break;
        }
        if(nowcnt&1)return 0;
        cnt+=nowcnt;
    }
    std::vector<Position>tmpv[usedid+1];
    for(int i=0;i<goal;i++)
    {
        int nowx=conn[i].x,nowy=conn[i].y;
        if(filled[nowx][nowy])continue;
        tmpv[used[nowx][nowy]].push_back(Position(nowx,nowy));
    }
    Conn.erase(Conn.begin()+tmpi);
    for(int i=1;i<=usedid;i++)
    {
        if(tmpv[i].size()>0)
            Conn.push_back(tmpv[i]);
    }
    return 1;
}
void Random_Generator::random_generate()
{
//    qDebug("StartGenerating\n");
    random_init();
    while(dolist.size())
    {
//        qDebug("now remaining %d\n",(int)dolist.size());
        int tmp1 = QRandomGenerator::global()->bounded(Conn.size());
//        qDebug("chosed Conn %d of %d with %d cells\n",tmp1,(int)Conn.size(),Conn[tmp1].size());
        std::vector<Position>conn=Conn[tmp1];
        while(1)
        {
            int pi1 = QRandomGenerator::global()->bounded(conn.size());
            int pi2 = QRandomGenerator::global()->bounded(conn.size());
            while(pi2==pi1)pi2 = QRandomGenerator::global()->bounded(conn.size());
            Position a=conn[pi1],b=conn[pi2];
//            qDebug("Chosed point %d(%d,%d) and %d(%d,%d) of %d\n",pi1,a.x,a.y,pi2,b.x,b.y,(int)conn.size());
            if(!check_conn(conn[pi1],conn[pi2]))continue;
//            qDebug("connection check passed.\n");
            filled[a.x][a.y]=filled[b.x][b.y]=1;
//            qDebug("checking availablity.\n");
            if(!check_avai(tmp1))
            {
                filled[a.x][a.y]=filled[b.x][b.y]=0;
                continue;
            }
//            qDebug("availablity check passed.\n");
            int pick = QRandomGenerator::global()->bounded(dolist.size());
            _pos1[dolist[pick]]=Position(a.x,a.y);
            _pos2[dolist[pick]]=Position(b.x,b.y);
            dolist.erase(dolist.begin()+pick);
//            qDebug("erased.\n");
            break;
        }
    }
}
