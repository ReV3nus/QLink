#include "selectfunctiontest.h"
#include "SingleMode.h"

SelectFunctionTest::SelectFunctionTest()
{

}
void SelectFunctionTest::FirstSelection()
{
    SingleMode singleMode;
    singleMode.StartGame();
    singleMode.SelectBlock(Position(1,1),0);
    QVERIFY(1+1==2);
    QVERIFY(singleMode.hasSelected==1);
}
void SelectFunctionTest::DuplicateSelection()
{
    SingleMode singleMode;
    singleMode.StartGame();
    singleMode.SelectBlock(Position(1,1),0);
    singleMode.SelectBlock(Position(1,1),0);
    QVERIFY(singleMode.hasSelected==0);
    QVERIFY(singleMode.gameScore==0);
}
void SelectFunctionTest::InvalidSecondSelection_WrongType()
{
    SingleMode singleMode;
    singleMode.StartGame();
    Position a=singleMode.CardPosition[1][1][0],b=singleMode.CardPosition[2][1][0];
    singleMode.SelectBlock(a,0);
    singleMode.SelectBlock(b,0);
    QVERIFY(singleMode.gameScore==0);
}
void SelectFunctionTest::InvalidSecondSelection_WrongNum()
{
    SingleMode singleMode;
    singleMode.StartGame();
    Position a=singleMode.CardPosition[1][1][0],b=singleMode.CardPosition[1][2][0];
    singleMode.SelectBlock(a,0);
    singleMode.SelectBlock(b,0);
    QVERIFY(singleMode.gameScore==0);
}
void SelectFunctionTest::InvalidSecondSelection_DisConnect()
{
    SingleMode singleMode;
    singleMode.StartGame();
    Position a,b;
    for(int i=1;i<=72;i++)
    {
        int type=(i-1)/14+1;
        if(type==6)type--;
        int num=i-1-(type-1)*14;
        a=singleMode.CardPosition[type][num][0],b=singleMode.CardPosition[type][num][1];
        if(!singleMode.CheckConnect(a,b))break;
    }
    singleMode.SelectBlock(a,0);
    singleMode.SelectBlock(b,0);
    QVERIFY(singleMode.gameScore==0);
}
void SelectFunctionTest::ValidSecondSelection()
{
    SingleMode singleMode;
    singleMode.StartGame();
    Position a,b;
    for(int i=1;i<=72;i++)
    {
        int type=(i-1)/14+1;
        if(type==6)type--;
        int num=i-1-(type-1)*14;
        a=singleMode.CardPosition[type][num][0],b=singleMode.CardPosition[type][num][1];
        if(singleMode.CheckConnect(a,b))break;
    }
//    qDebug("Found position (%d,%d) and (%d,%d)\n",a.x,a.y,b.x,b.y);
//    qDebug("which type and num is (%d,%d) and (%d,%d)\n"
//           ,singleMode.cell[a.x][a.y]->blockType,singleMode.cell[a.x][a.y]->num
//           ,singleMode.cell[b.x][b.y]->blockType,singleMode.cell[b.x][b.y]->num);
    singleMode.SelectBlock(a,0);
    singleMode.SelectBlock(b,0);

    QVERIFY(singleMode.delayTimer->isActive()==true);
    QVERIFY(singleMode.gameScore>0);
}

QTEST_MAIN(SelectFunctionTest)
