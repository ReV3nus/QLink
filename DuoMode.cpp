#include "DuoMode.h"
#include "ui_DuoMode.h"
#include<QWidget>

DuoMode::DuoMode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DuoMode)
{
    ui->setupUi(this);
    CellInit();

    timeLabel=ui->TimeLabel;
    scoreLabel[0]=ui->ScoreLabel_p1;
    scoreLabel[1]=ui->ScoreLabel_p2;
    playerLabel[0]=ui->ScoreWordLabel_p1;
    playerLabel[1]=ui->ScoreWordLabel_p2;
    gameLabel=ui->GAMELabel;
    defaultTitle[0]="PLAYER 1";
    defaultTitle[1]="PLAYER 2";

    linkLine[0] = new LinkLine(ui->displaywidget_p1);
    linkLine[1] = new LinkLine(ui->displaywidget_p2);
    linkLine[0]->move(0,0),linkLine[1]->move(0,0);
    linkLine[0]->setFixedSize(540,360),linkLine[1]->setFixedSize(540,360);
    linkLine[0]->raise(),linkLine[1]->raise();

    delayTimer[0] = new QTimer(this),delayTimer[1] = new QTimer(this);
    delayTimer[0]->setSingleShot(true),delayTimer[1]->setSingleShot(true);
    gameTimer = new QTimer(this);
    gameTimer->setInterval(1000);
    itemTimer = new QTimer(this);
    itemTimer->setInterval(10000);
    hintTimer = new QTimer(this);
    hintTimer->setInterval(5000);
    freezeTimer[0] = new QTimer(this),freezeTimer[1] = new QTimer(this);
    freezeTimer[0]->setInterval(5000),freezeTimer[1]->setInterval(5000);
    dizzleTimer[0] = new QTimer(this),dizzleTimer[1] = new QTimer(this);
    dizzleTimer[0]->setInterval(10000),dizzleTimer[1]->setInterval(10000);

    connect(gameTimer,&QTimer::timeout,this,&DuoMode::updateTime);
    connect(delayTimer[0], &QTimer::timeout, this, &DuoMode::DelayTimerAction_p1);
    connect(delayTimer[1], &QTimer::timeout, this, &DuoMode::DelayTimerAction_p2);
    connect(itemTimer,&QTimer::timeout,this,&DuoMode::ItemGenerate);
    connect(hintTimer,&QTimer::timeout,this,&DuoMode::HintTimeOut);
    connect(freezeTimer[0],&QTimer::timeout,this,&DuoMode::freezeTimeOut_p1);
    connect(freezeTimer[1],&QTimer::timeout,this,&DuoMode::freezeTimeOut_p2);
    connect(dizzleTimer[0],&QTimer::timeout,this,&DuoMode::dizzleTimeOut_p1);
    connect(dizzleTimer[1],&QTimer::timeout,this,&DuoMode::dizzleTimeOut_p2);
}

DuoMode::~DuoMode()
{
    delete ui;
}
void DuoMode::updateTime()
{
    if(!isRunning)return;
    timeLabel->setText(QString::number(gameTime));
    gameTime--;
    if(gameTime<0)
    {
        StopGame();
        if(gameScore[0]>gameScore[1])gameLabel->setText("PLAYER 1 WON!");
        else if(gameScore[0]<gameScore[1])gameLabel->setText("PLAYER 2 WON!");
        else gameLabel->setText("DRAW!");
        gameLabel->show();
    }
}
void DuoMode::updateScore(int playerid,double sco)
{
    if(!isRunning)return;
    gameScore[playerid]+=sco;
    scoreLabel[0]->setText(QString::number(qRound(gameScore[0])));
    scoreLabel[1]->setText(QString::number(qRound(gameScore[1])));
}
void DuoMode::CellInit()
{
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            cell[0][i][j] = new Cell(ui->displaywidget_p1);
            cell[1][i][j] = new Cell(ui->displaywidget_p2);
            cell[0][i][j]->setCellSize(CellSize),cell[1][i][j]->setCellSize(CellSize);
            cell[0][i][j]->setPosition(j*CellSize,i*CellSize);
            cell[1][i][j]->setPosition(j*CellSize,i*CellSize);
        }
    borderCell[0] = new Border(ui->displaywidget_p1);
    borderCell2[0] = new Border(ui->displaywidget_p1);
    borderCell[1] = new Border(ui->displaywidget_p2);
    borderCell2[1] = new Border(ui->displaywidget_p2);

    borderCell[0]->setSize(CellSize),borderCell[1]->setSize(CellSize);
    borderCell2[0]->setSize(CellSize),borderCell2[1]->setSize(CellSize);
    borderCell[0]->setDisplay('c'),borderCell[1]->setDisplay('c');
    borderCell2[0]->setDisplay('c'),borderCell2[1]->setDisplay('c');

    hintCell1[0] = new Border(ui->displaywidget_p1);
    hintCell2[0] = new Border(ui->displaywidget_p1);
    hintCell1[1] = new Border(ui->displaywidget_p2);
    hintCell2[1] = new Border(ui->displaywidget_p2);

    hintCell1[0]->setSize(CellSize),hintCell1[1]->setSize(CellSize);
    hintCell2[0]->setSize(CellSize),hintCell2[1]->setSize(CellSize);
    hintCell1[0]->setDisplay('c'),hintCell1[1]->setDisplay('c');
    hintCell2[0]->setDisplay('c'),hintCell2[1]->setDisplay('c');
}
void DuoMode::GameCleanInit()
{
    playerLabel[0]->setText(defaultTitle[0]);
    playerLabel[1]->setText(defaultTitle[1]);
    gameLabel->hide();
    gameTimer->start();
    itemTimer->start();

    isDelayTimerWorking[0]=isDelayTimerWorking[1]=false;
    isChosenActive[0]=isChosenActive[1]=false;
    hadRemoteChosen[0]=hadRemoteChosen[1]=false;
    hasSelected[0]=hasSelected[1]=false;
    isFrozen[0]=isFrozen[1]=false;
    isDizzle[0]=isDizzle[1]=false;

    borderCell[0]->setDisplay('c'),borderCell[1]->setDisplay('c');
    borderCell2[0]->setDisplay('c'),borderCell2[1]->setDisplay('c');
    hintCell1[0]->setDisplay('c'),hintCell1[1]->setDisplay('c');
    hintCell2[0]->setDisplay('c'),hintCell2[1]->setDisplay('c');;

    hasSelected[0]=false,hasSelected[1]=false;;
    borderCell[0]->setDisplay('c'),borderCell[1]->setDisplay('c');;
    borderCell2[0]->setDisplay('c'),borderCell2[1]->setDisplay('c');;
    hintCell1[0]->setDisplay('c'),hintCell1[1]->setDisplay('c');;
    hintCell2[0]->setDisplay('c'),hintCell2[1]->setDisplay('c');;

    if(hintTimer->isActive())hintTimer->stop();
    if(freezeTimer[0]->isActive())freezeTimer[0]->stop();
    if(freezeTimer[1]->isActive())freezeTimer[1]->stop();
    if(dizzleTimer[0]->isActive())dizzleTimer[0]->stop();
    if(dizzleTimer[1]->isActive())dizzleTimer[1]->stop();

    linkLine[0]->ClearPoints(),linkLine[1]->ClearPoints();
    linkLine[0]->hide(),linkLine[1]->hide();
}
void DuoMode::GenerateMap()
{
    for(int i=0;i<11;i++)cell[0][i][0]->setDisplay(empty,0),cell[0][i][17]->setDisplay(empty,0);
    for(int i=0;i<18;i++)cell[0][0][i]->setDisplay(empty,0),cell[0][10][i]->setDisplay(empty,0);
    for(int i=0;i<11;i++)cell[1][i][0]->setDisplay(empty,0),cell[1][i][17]->setDisplay(empty,0);
    for(int i=0;i<18;i++)cell[1][0][i]->setDisplay(empty,0),cell[1][10][i]->setDisplay(empty,0);
    mapGenerator.Generate_DuoMap(cell,blockUsed);
    playerPos[0]=Position(0,0),playerPos[1]=Position(0,0);
    cell[0][0][0]->setDisplay(chara,3),cell[1][0][0]->setDisplay(chara,3);

    hasSelected[0]=hasSelected[1]=false;
    borderCell[0]->setDisplay('c');
    borderCell[1]->setDisplay('c');
    borderCell2[0]->setDisplay('c');
    borderCell2[1]->setDisplay('c');
    hintCell1[0]->setDisplay('c');
    hintCell2[0]->setDisplay('c');
    hintCell1[1]->setDisplay('c');
    hintCell2[1]->setDisplay('c');
    if(hintTimer->isActive())hintTimer->stop();
    if(freezeTimer[0]->isActive())freezeTimer[0]->stop();
    if(freezeTimer[1]->isActive())freezeTimer[1]->stop();
    if(dizzleTimer[0]->isActive())dizzleTimer[0]->stop();
    if(dizzleTimer[1]->isActive())dizzleTimer[1]->stop();

    isFrozen[0]=isFrozen[1]=0;
    isDizzle[0]=isDizzle[1]=0;
    linkLine[0]->ClearPoints(),linkLine[1]->ClearPoints();
    linkLine[0]->hide(),linkLine[1]->hide();

    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
            CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][0]=CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][1]=Position(0,0);
    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
        {
            if(CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][0]==Position(0,0))
                CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][0]=Position(i,j);
            else CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][1]=Position(i,j);
        }
}
void DuoMode::StartGame()
{
    isRunning=true;
    gameTime=600;
    gameScore[0]=gameScore[1]=0;
    updateTime();
    updateScore(0,0);
    GameCleanInit();
    TypeList[0].clear(),TypeList[1].clear();
    NumList[0].clear(),NumList[1].clear();
    memset(blockUsed,0,sizeof(blockUsed));
    GenerateMap();
}
void DuoMode::StopGame()
{
    isRunning=false;
    gameTimer->stop();
    delayTimer[0]->stop(),delayTimer[1]->stop();
    itemTimer->stop();
    if(hintTimer->isActive())hintTimer->stop();
    if(freezeTimer[0]->isActive())freezeTimer[0]->stop();
    if(freezeTimer[1]->isActive())freezeTimer[1]->stop();
    if(dizzleTimer[0]->isActive())dizzleTimer[0]->stop();
    if(dizzleTimer[1]->isActive())dizzleTimer[1]->stop();

    isDelayTimerWorking[0]=isDelayTimerWorking[1]=false;
    isChosenActive[0]=isChosenActive[1]=false;
    hadRemoteChosen[0]=hadRemoteChosen[1]=false;
    hasSelected[0]=hasSelected[1]=false;
    isFrozen[0]=isFrozen[1]=false;
    isDizzle[0]=isDizzle[1]=false;

    borderCell[0]->setDisplay('c'),borderCell[1]->setDisplay('c');
    borderCell2[0]->setDisplay('c'),borderCell2[1]->setDisplay('c');
    hintCell1[0]->setDisplay('c'),hintCell1[1]->setDisplay('c');
    hintCell2[0]->setDisplay('c'),hintCell2[1]->setDisplay('c');;
}
void DuoMode::PauseAndContinue()
{
    isRunning^=1;
}
//number 0~71
static char NumberToChar(int num)
{
    if(num<10)return ('0'+num);
    num-=10;
    if(num<26)return 'a'+num;
    num-=26;
    if(num<26)return 'A'+num;
    num-=26;
    if(!num)return '!';num--;
    if(!num)return '@';num--;
    if(!num)return '#';num--;
    if(!num)return '$';num--;
    if(!num)return '%';num--;
    if(!num)return '^';num--;
    if(!num)return '&';num--;
    if(!num)return '*';num--;
    if(!num)return '|';num--;
    return '?';
}
static int CharToNumber(char c)
{
    int ret=0;
    if('0'<=c&&c<='9')return ret+c-'0';
    ret+=10;
    if('a'<=c&&c<='z')return ret+c-'a';
    ret+=26;
    if('A'<=c&&c<='Z')return ret+c-'A';
    ret+=26;
    if(c=='!')return ret;ret++;
    if(c=='@')return ret;ret++;
    if(c=='#')return ret;ret++;
    if(c=='$')return ret;ret++;
    if(c=='%')return ret;ret++;
    if(c=='^')return ret;ret++;
    if(c=='&')return ret;ret++;
    if(c=='*')return ret;ret++;
    if(c=='|')return ret;ret++;
    return ret;
}
void DuoMode::GenerateCode()
{
    gameCode="";
    gameCode+=NumberToChar(gameTime/72);
    gameCode+=NumberToChar(gameTime%72);

    int tmp=qRound(gameScore[0]);
    char tmpchar[5];
    for(int i=0;i<5;i++)tmpchar[i]=NumberToChar(tmp%72),tmp/=72;
    gameCode+=tmpchar[4];
    gameCode+=tmpchar[3];
    gameCode+=tmpchar[2];
    gameCode+=tmpchar[1];
    gameCode+=tmpchar[0];

    tmp=qRound(gameScore[1]);
    for(int i=0;i<5;i++)tmpchar[i]=NumberToChar(tmp%72),tmp/=72;
    gameCode+=tmpchar[4];
    gameCode+=tmpchar[3];
    gameCode+=tmpchar[2];
    gameCode+=tmpchar[1];
    gameCode+=tmpchar[0];

    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(cell[0][i][j]->blockType==empty||cell[0][i][j]->blockType==item)gameCode+='`';
            else if(cell[0][i][j]->blockType==chara)gameCode+='/';
            else gameCode+=NumberToChar((cell[0][i][j]->blockType-1)*14+cell[0][i][j]->num);
        }

    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(cell[1][i][j]->blockType==empty||cell[1][i][j]->blockType==item)gameCode+='`';
            else if(cell[1][i][j]->blockType==chara)gameCode+='/';
            else gameCode+=NumberToChar((cell[1][i][j]->blockType-1)*14+cell[1][i][j]->num);
        }

    gameCode+=NumberToChar(TypeList[0].size());
    for(int i=0;i<TypeList[0].size();i++)
        gameCode+=NumberToChar((TypeList[0][i]-1)*14+NumList[0][i]);

    gameCode+=NumberToChar(TypeList[1].size());
    for(int i=0;i<TypeList[1].size();i++)
        gameCode+=NumberToChar((TypeList[1][i]-1)*14+NumList[1][i]);
}
void DuoMode::LoadFromCode()
{
    isRunning=true;
    GameCleanInit();
    int tmpnum;
    int tmpid=0;
    std::string stringCode=gameCode.toStdString();
    gameTime=CharToNumber(stringCode[0])*72+CharToNumber(stringCode[1]);
    gameScore[0]=0,gameScore[1]=0;
    for(tmpid=2;tmpid<7;tmpid++)
        gameScore[0]*=72,gameScore[0]+=CharToNumber(stringCode[tmpid]);
    for(tmpid=7;tmpid<12;tmpid++)
        gameScore[1]*=72,gameScore[1]+=CharToNumber(stringCode[tmpid]);
    tmpid=12;
    updateTime();
    updateScore(0,0);
    TypeList[0].clear(),TypeList[1].clear();
    NumList[0].clear(),NumList[1].clear();

    for(int i=0;i<73;i++)blockUsed[0][i]=1;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
            CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][0]=CardPosition[cell[0][i][j]->blockType][cell[0][i][j]->num][1]=Position(0,0);
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(stringCode[tmpid]=='`')
            {
                cell[0][i][j]->setDisplay(empty,0);
                tmpid++;
                continue;
            }
            if(stringCode[tmpid]=='/')
            {
                cell[0][i][j]->setDisplay(chara,3);
                playerPos[0]=Position(i,j);
                tmpid++;
                continue;
            }
            tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
            int type=tmpnum/14+1;
            if(type==6)type--;
            int num=tmpnum-(type-1)*14;
            cell[0][i][j]->setDisplay((BlockType)type,num);
            blockUsed[0][tmpnum+1]=0;
            if(CardPosition[type][num][0]==Position(0,0))
                CardPosition[type][num][0]=Position(i,j);
            else CardPosition[type][num][1]=Position(i,j);
        }

    for(int i=0;i<73;i++)blockUsed[1][i]=1;
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(stringCode[tmpid]=='`')
            {
                cell[1][i][j]->setDisplay(empty,0);
                tmpid++;
                continue;
            }
            if(stringCode[tmpid]=='/')
            {
                cell[1][i][j]->setDisplay(chara,3);
                playerPos[1]=Position(i,j);
                tmpid++;
                continue;
            }
            tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
            int type=tmpnum/14+1;
            if(type==6)type--;
            int num=tmpnum-(type-1)*14;
            cell[1][i][j]->setDisplay((BlockType)type,num);
            blockUsed[1][tmpnum+1]=0;
        }

    tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
    for(int i=0;i<tmpnum;i++)
    {
        int tmpnum2=CharToNumber(stringCode[tmpid]);
        tmpid++;
        int type=tmpnum2/14+1;
        if(type==6)type--;
        int num=tmpnum-(type-1)*14;
        TypeList[0].push_back((BlockType)type);
        NumList[0].push_back(num);
    }

    tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
    for(int i=0;i<tmpnum;i++)
    {
        int tmpnum2=CharToNumber(stringCode[tmpid]);
        tmpid++;
        int type=tmpnum2/14+1;
        if(type==6)type--;
        int num=tmpnum-(type-1)*14;
        TypeList[1].push_back((BlockType)type);
        NumList[1].push_back(num);
    }
}
void DuoMode::SaveFile()
{
    if(!isRunning)
    {
        QMessageBox::warning(this, "保存提示", "保存失败：游戏未在进行状态！", QMessageBox::Close);
        return;
    }
    qDebug("saving to file.\n");
    GenerateCode();
    QFile file(SaveFilePath);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);
    qDebug("%s\n",gameCode.toStdString().c_str());
    out << gameCode;
    file.close();
    QMessageBox::information(this, "保存提示", "成功保存至双人游戏存档文件", QMessageBox::Close);
}
void DuoMode::LoadFile()
{
    StopGame();
    gameCode="";
    QFile file(SaveFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    gameCode=in.readLine();
    file.close();
    LoadFromCode();
}
void DuoMode::ItemGenerate()
{
    if(!isRunning)return;
    int genRan1=QRandomGenerator::global()->bounded(100)+1;
    int genRan2=QRandomGenerator::global()->bounded(100)+1;
    int itemId=QRandomGenerator::global()->bounded(5)+1;
    if(itemId==3)itemId=6;
    std::vector<Position>emptyPos;
    if(genRan1<=33)
    {
        emptyPos.clear();
        for(int i=0;i<11;i++)
            for(int j=0;j<18;j++)
                if(cell[0][i][j]->blockType==empty)emptyPos.push_back(Position(i,j));
        int posId=QRandomGenerator::global()->bounded(emptyPos.size());
        cell[0][emptyPos[posId].x][emptyPos[posId].y]->setDisplay(item,itemId);
    }
    if(genRan2<=33)
    {
        emptyPos.clear();
        for(int i=0;i<11;i++)
            for(int j=0;j<18;j++)
                if(cell[1][i][j]->blockType==empty)emptyPos.push_back(Position(i,j));
        int posId=QRandomGenerator::global()->bounded(emptyPos.size());
        cell[1][emptyPos[posId].x][emptyPos[posId].y]->setDisplay(item,itemId);
    }
}
void DuoMode::ItemFunction(int playerId,int itemId)
{
    if(!isRunning)return;
    if(itemId==1)ItemFunction_p1s();
    if(itemId==2)ItemFunction_shuffle();
    if(itemId==4)ItemFunction_hint();
    if(itemId==5)ItemFunction_freeze(playerId^1);
    if(itemId==6)ItemFunction_dizzle(playerId^1);

}
void DuoMode::ItemFunction_p1s()
{
    gameTime+=30;
    updateTime();
}
void DuoMode::ItemFunction_shuffle()
{
    isDelayTimerWorking[0]=isDelayTimerWorking[1]=false;
    isChosenActive[0]=isChosenActive[1]=false;
    hadRemoteChosen[0]=hadRemoteChosen[1]=false;

    GenerateMap();
}
void DuoMode::HintTimeOut()
{
    hintCell1[0]->setDisplay('c');
    hintCell2[0]->setDisplay('c');
    hintCell1[1]->setDisplay('c');
    hintCell2[1]->setDisplay('c');
    if(hintTimer->isActive())hintTimer->stop();
}
void DuoMode::ItemFunction_hint()
{
    std::vector<int>avaiList[2];
    avaiList[0].clear(),avaiList[1].clear();
    for(int i=1;i<=72;i++)if(!blockUsed[0][i])avaiList[0].push_back(i);
    for(int i=1;i<=72;i++)if(!blockUsed[1][i])avaiList[1].push_back(i);
    int ranId1=QRandomGenerator::global()->bounded(avaiList[0].size());
    int ranId2=QRandomGenerator::global()->bounded(avaiList[1].size());
    for(int fx=0;fx<72;fx++)
    {
        int i=ranId1+fx;
        if(i>72)i-=72;
        if(blockUsed[0][i])continue;
        int type=(i-1)/14+1;
        if(type==6)type--;
        int num=i-1-(type-1)*14;
        Position a=CardPosition[type][num][0],b=CardPosition[type][num][1];
        if(!CheckConnect(0,a,b))continue;
        hintCell1[0]->setPosition(a.y*CellSize,a.x*CellSize);
        hintCell2[0]->setPosition(b.y*CellSize,b.x*CellSize);
        hintCell1[0]->setDisplay('h');
        hintCell2[0]->setDisplay('h');
        break;
    }
    for(int fx=0;fx<72;fx++)
    {
        int i=ranId2+fx;
        if(i>72)i-=72;
        if(blockUsed[1][i])continue;
        int type=(i-1)/14+1;
        if(type==6)type--;
        int num=i-1-(type-1)*14;
        Position a=CardPosition[type][num][0],b=CardPosition[type][num][1];
        if(!CheckConnect(1,a,b))continue;
        hintCell1[1]->setPosition(a.y*CellSize,a.x*CellSize);
        hintCell2[1]->setPosition(b.y*CellSize,b.x*CellSize);
        hintCell1[1]->setDisplay('h');
        hintCell2[1]->setDisplay('h');
        break;
    }

    if(hintTimer->isActive())hintTimer->stop();
    hintTimer->start();
}
void DuoMode::freezeTimeOut_p1()
{
    isFrozen[0]=false;
    if(freezeTimer[0]->isActive())freezeTimer[0]->stop();
}
void DuoMode::freezeTimeOut_p2()
{
    isFrozen[1]=false;
    if(freezeTimer[1]->isActive())freezeTimer[1]->stop();
}
void DuoMode::ItemFunction_freeze(int playerid)
{
    if(freezeTimer[playerid]->isActive())freezeTimer[playerid]->stop();
    isFrozen[playerid]=true;
    freezeTimer[playerid]->start();
}
void DuoMode::dizzleTimeOut_p1()
{
    isDizzle[0]=false;
    if(dizzleTimer[0]->isActive())dizzleTimer[0]->stop();
}
void DuoMode::dizzleTimeOut_p2()
{
    isDizzle[1]=false;
    if(dizzleTimer[1]->isActive())dizzleTimer[1]->stop();
}
void DuoMode::ItemFunction_dizzle(int playerid)
{
    if(dizzleTimer[playerid]->isActive())dizzleTimer[playerid]->stop();
    isDizzle[playerid]=true;
    dizzleTimer[playerid]->start();
}
void DuoMode::PlayerMove(int playerid,int dirid)
{
    if(isFrozen[playerid])return;
    if(isDizzle[playerid])dirid^=2;
    Position nxtPos=playerPos[playerid]+moveDir[dirid];
    if(nxtPos.x<0||nxtPos.x>10||nxtPos.y<0||nxtPos.y>17)
    {
        cell[playerid][playerPos[playerid].x][playerPos[playerid].y]->setDisplay(chara,dirid);
        return;
    }
    if(cell[playerid][nxtPos.x][nxtPos.y]->blockType>empty&&cell[playerid][nxtPos.x][nxtPos.y]->blockType<=any)
    {
        //selectblock
        if(cell[playerid][playerPos[playerid].x][playerPos[playerid].y]->num==dirid)
            SelectBlock(playerid,nxtPos,false);
        else cell[playerid][playerPos[playerid].x][playerPos[playerid].y]->setDisplay(chara,dirid);
        return;
    }
    int itemNum=-1;
    if(cell[playerid][nxtPos.x][nxtPos.y]->blockType==item)
    {
        //accquire item
        itemNum=cell[playerid][nxtPos.x][nxtPos.y]->num;
    }
    cell[playerid][playerPos[playerid].x][playerPos[playerid].y]->setDisplay(empty,0);
    cell[playerid][nxtPos.x][nxtPos.y]->setDisplay(chara,dirid);
    playerPos[playerid]=nxtPos;
    if(itemNum!=-1)ItemFunction(playerid,itemNum);
}
void DuoMode::ChosenMove(int playerid,int dirid)
{
    Position nxtPos=chosenPos[playerid]+moveDir[dirid];
    if(nxtPos.x<0||nxtPos.x>10||nxtPos.y<0||nxtPos.y>17)
        return;
    chosenPos[playerid]=nxtPos;
    borderCell2[playerid]->setPosition(nxtPos.y*CellSize,nxtPos.x*CellSize);
    return;
}
bool DuoMode::CCdfs(int playerid,Position now,Position des,int dirid,int cnt)
{
    CCused[playerid][now.x][now.y]=1;
    CCpath[playerid].push_back(now);
    if(now==des)return 1;
    Position nxt=now+moveDir[dirid];
    if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[playerid][nxt.x][nxt.y])
    {
        if(cell[playerid][nxt.x][nxt.y]->blockType==empty||cell[playerid][nxt.x][nxt.y]->blockType>=chara)
        {
            if(CCdfs(playerid,nxt,des,dirid,cnt))return 1;
        }
        else if(nxt==des)return CCdfs(playerid,nxt,des,dirid,cnt);
    }
    if(cnt<=1)
    {
        int dir1=dirid^1,dir2=dir1^2;
        nxt=now+moveDir[dir1];
        if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[playerid][nxt.x][nxt.y])
        {
            if(cell[playerid][nxt.x][nxt.y]->blockType==empty||cell[playerid][nxt.x][nxt.y]->blockType>=chara)
            {
                if(CCdfs(playerid,nxt,des,dir1,cnt+1))return 1;
            }
            else if(nxt==des)return CCdfs(playerid,nxt,des,dir1,cnt+1);
        }

        nxt=now+moveDir[dir2];
        if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[playerid][nxt.x][nxt.y])
        {
            if(cell[playerid][nxt.x][nxt.y]->blockType==empty||cell[playerid][nxt.x][nxt.y]->blockType>=chara)
            {
                if(CCdfs(playerid,nxt,des,dir2,cnt+1))return 1;
            }
            else if(nxt==des)return CCdfs(playerid,nxt,des,dir2,cnt+1);
        }
    }
    CCused[playerid][now.x][now.y]=0;
    CCpath[playerid].pop_back();
    return 0;
}
bool DuoMode::CheckConnect(int playerid,Position a,Position b)
{
//    qDebug("now checking connection of block (%d,%d) and (%d,%d)\n",a.x,a.y,b.x,b.y);
    memset(CCused[playerid],0,sizeof(CCused[playerid]));
    CCpath[playerid].clear();
    CCpath[playerid].push_back(a);
    CCused[playerid][a.x][a.y]=1;
    for(int i=0;i<4;i++)
    {
        Position nxt=a+moveDir[i];
        if(cell[playerid][nxt.x][nxt.y]->blockType==empty||cell[playerid][nxt.x][nxt.y]->blockType>=chara)
        {
            if(CCdfs(playerid,nxt,b,i,0))break;
        }
        else if(nxt==b)
        {
            CCused[playerid][nxt.x][nxt.y]=1;
            CCpath[playerid].push_back(nxt);
        }
        if(CCused[playerid][b.x][b.y])break;
    }
    return CCused[playerid][b.x][b.y];
}
void DuoMode::DelayTimerAction_p1()
{
    isDelayTimerWorking[0]=false;
    if(secondPos[0].x==-1)
    {
        borderCell[0]->setDisplay('c');
        borderCell2[0]->setDisplay('c');
        hasSelected[0]=false;
        return;
    }
    borderCell[0]->setDisplay('c');
    borderCell2[0]->setDisplay('c');
    linkLine[0]->hide();
    linkLine[0]->ClearPoints();

    hasSelected[0]=false;

    BlockType type=cell[0][secondPos[0].x][secondPos[0].y]->blockType;
    int num=cell[0][secondPos[0].x][secondPos[0].y]->num;
    blockUsed[0][1+(int)(type-spade)*14+num]=1;
    cell[0][selectedBlockPos[0].x][selectedBlockPos[0].y]->setDisplay(empty,0);
    cell[0][secondPos[0].x][secondPos[0].y]->setDisplay(empty,0);
    bool tmpflag=1;
    for(int i=1;i<=72;i++)tmpflag&=blockUsed[0][i]&blockUsed[1][i];
    if(tmpflag)
    {
        StopGame();
        if(gameScore[0]>gameScore[1])gameLabel->setText("PLAYER 1 WON!");
        else if(gameScore[0]<gameScore[1])gameLabel->setText("PLAYER 2 WON!");
        else gameLabel->setText("DRAW!");
        gameLabel->show();
    }
    return;
}
void DuoMode::DelayTimerAction_p2()
{
    isDelayTimerWorking[1]=false;
    if(secondPos[1].x==-1)
    {
        borderCell[1]->setDisplay('c');
        borderCell2[1]->setDisplay('c');
        hasSelected[1]=false;
        return;
    }
    borderCell[1]->setDisplay('c');
    borderCell2[1]->setDisplay('c');
    linkLine[1]->hide();
    linkLine[1]->ClearPoints();

    hasSelected[1]=false;

    BlockType type=cell[1][secondPos[1].x][secondPos[1].y]->blockType;
    int num=cell[1][secondPos[1].x][secondPos[1].y]->num;
    blockUsed[1][1+(int)(type-spade)*14+num]=1;
    cell[1][selectedBlockPos[1].x][selectedBlockPos[1].y]->setDisplay(empty,0);
    cell[1][secondPos[1].x][secondPos[1].y]->setDisplay(empty,0);
    return;
}
void DuoMode::EliminateBlock(int playerid,BlockType type,int num)
{
    if(hadRemoteChosen[playerid])
    {
        updateScore(playerid,10);
        playerLabel[playerid]->setText("Remote Eliminated.(+10)");
        TypeList[playerid].push_back(empty);
        NumList[playerid].push_back(0);
        return;
    }
    TypeList[playerid].push_back(type);
    NumList[playerid].push_back(num);

    bool joker=0,JOKER=0;
    //pairs
    double score1=10;
    int sameCount=1;
    int i=TypeList[playerid].size()-2;
    for(;i>=0;i--)
    {
        if(!TypeList[playerid][i])break;
        if(NumList[playerid][i+1]>0&&NumList[playerid][i+1]<=13&&NumList[playerid][i]>0&&NumList[playerid][i+1]<=13&&NumList[playerid][i+1]!=NumList[playerid][i])break;
        sameCount++;
        if(NumList[playerid][i]==14)joker=1;
        if(NumList[playerid][i]==15)JOKER=1;
    }
    score1*=pow(4,sameCount-1);
    //staright
    double score2=10;
    int StraightCount=1;
    int TypeCount[5]={0,0,0,0,0};
    int maxTypeId;
    int maxCount=0;
    i=TypeList[playerid].size()-1;
    if(TypeList[playerid][i]<5)TypeCount[TypeList[playerid][i]]++;
    else TypeCount[1]=TypeCount[2]=TypeCount[3]=TypeCount[4]=1;
    i--;
    for(;i>=0;i--)
    {
        if(!TypeList[playerid][i])break;
        if(NumList[playerid][i+1]>0&&NumList[playerid][i+1]<=13&&NumList[playerid][i]>0&&NumList[playerid][i+1]<=13&&NumList[playerid][i+1]!=NumList[playerid][i]+1)break;
        if(TypeList[playerid][i]<5)TypeCount[TypeList[playerid][i]]++;
        else TypeCount[1]++,TypeCount[2]++,TypeCount[3]++,TypeCount[4]++;
        StraightCount++;
        if(NumList[playerid][i]==14)joker=1;
        if(NumList[playerid][i]==15)JOKER=1;
    }
    for(i=1;i<=4;i++)
        if(TypeCount[i]>maxCount)
            maxCount=TypeCount[i],maxTypeId=i;
    //*(1.45+0.05*a)^n
    score2*=pow(1.45+0.05*maxCount,StraightCount-1);

    QString displayString="";
    if(score1>=score2)
    {
        displayString+="Pairs of "+QString::number(sameCount)+"! ";
        if(joker)displayString+="(joker! x1.5) ";
        if(JOKER)displayString+="(JOKER! x2) ";
        displayString+="(+"+QString::number(score1*(joker?1.5:1)*(JOKER?2:1))+")";
        updateScore(playerid,score1*(joker?1.5:1)*(JOKER?2:1));
        playerLabel[playerid]->setText(displayString);
    }
    else
    {
        displayString+="Straight of "+QString::number(StraightCount)+" , within "+QString::number(maxCount);
        if(maxTypeId==1)displayString+=" Spades! ";
        if(maxTypeId==2)displayString+=" Hearts! ";
        if(maxTypeId==3)displayString+=" Clubs! ";
        if(maxTypeId==4)displayString+=" Diamonds! ";
        if(joker)displayString+="(joker! x1.5) ";
        if(JOKER)displayString+="(JOKER! x2) ";
        displayString+="(+"+QString::number(score2*(joker?1.5:1)*(JOKER?2:1))+")";
        updateScore(playerid,score2*(joker?1.5:1)*(JOKER?2:1));
        playerLabel[playerid]->setText(displayString);
    }
}
void DuoMode::SelectBlock(int playerid,Position pos,bool isRemote)
{
    if(!hasSelected[playerid])
    {
        hasSelected[playerid]=true;
        selectedBlockPos[playerid]=pos;
        borderCell[playerid]->setPosition(pos.y*CellSize,pos.x*CellSize);
        borderCell[playerid]->setDisplay('b');
        hadRemoteChosen[playerid]=isRemote;
        return;
    }
    else
    {
        if(pos==selectedBlockPos[playerid])
        {
            hasSelected[playerid]=false;
            borderCell[playerid]->setDisplay('c');
            hadRemoteChosen[playerid]=false;
            return;
        }
        hadRemoteChosen[playerid]|=isRemote;

        borderCell2[playerid]->setPosition(pos.y*CellSize,pos.x*CellSize);
        if(cell[playerid][selectedBlockPos[playerid].x][selectedBlockPos[playerid].y]->blockType!=cell[playerid][pos.x][pos.y]->blockType||
            cell[playerid][selectedBlockPos[playerid].x][selectedBlockPos[playerid].y]->num!=cell[playerid][pos.x][pos.y]->num||
            cell[playerid][pos.x][pos.y]->blockType<spade||cell[playerid][pos.x][pos.y]->blockType>any||
            !CheckConnect(playerid,selectedBlockPos[playerid],pos))
        {
            borderCell[playerid]->setDisplay('r');
            borderCell2[playerid]->setDisplay('r');

            isDelayTimerWorking[playerid]=true;
            secondPos[playerid]=Position(-1,-1);
            delayTimer[playerid]->start(500);
            return;
        }
        borderCell[playerid]->setDisplay('g');
        borderCell2[playerid]->setDisplay('g');

        linkLine[playerid]->ClearPoints();
        for(int i=0;i<CCpath[playerid].size();i++)
            linkLine[playerid]->AddPoint(CCpath[playerid][i].y*CellSize+(CellSize>>1),CCpath[playerid][i].x*CellSize+(CellSize>>1));
        linkLine[playerid]->show();
        linkLine[playerid]->raise();
        linkLine[playerid]->update();

        isDelayTimerWorking[playerid]=true;
        secondPos[playerid]=pos;

        EliminateBlock(playerid,cell[playerid][pos.x][pos.y]->blockType,cell[playerid][pos.x][pos.y]->num);

        delayTimer[playerid]->start(500);
        return;
    }
}
void DuoMode::HandleMove(int playerid,int dirid)
{
    if(isDelayTimerWorking[playerid])return;
    if(isChosenActive[playerid])ChosenMove(playerid,dirid);
    else PlayerMove(playerid,dirid);
}
void DuoMode::ChosenToggle(int playerid)
{
    if(isDelayTimerWorking[playerid])return;
    if(isChosenActive[playerid])
    {
        isChosenActive[playerid]=false;
        borderCell2[playerid]->setDisplay('c');
        return;
    }
    Position nxt=playerPos[playerid]+moveDir[cell[playerid][playerPos[playerid].x][playerPos[playerid].y]->num];
    if(cell[playerid][nxt.x][nxt.y]->blockType>=spade&&cell[playerid][nxt.x][nxt.y]->blockType<=any)
    {
        isChosenActive[playerid]=true;
        borderCell2[playerid]->setPosition(nxt.y*CellSize,nxt.x*CellSize);
        borderCell2[playerid]->setDisplay('y');
        chosenPos[playerid]=nxt;
    }
    return;
}
void DuoMode::ChosenConfirm(int playerid)
{
    if(isDelayTimerWorking[playerid])return;
    isChosenActive[playerid]=false;
    borderCell2[playerid]->setDisplay('c');
    if(cell[playerid][chosenPos[playerid].x][chosenPos[playerid].y]->blockType>=spade&&cell[playerid][chosenPos[playerid].x][chosenPos[playerid].y]->blockType<=any)
    {
        SelectBlock(playerid,chosenPos[playerid],true);
    }
    return;
}
void DuoMode::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)PauseAndContinue();
    if(!isRunning)return;
    if (event->key() == Qt::Key_W)HandleMove(0,1);
    else if (event->key() == Qt::Key_A)HandleMove(0,2);
    else if (event->key() == Qt::Key_S)HandleMove(0,3);
    else if (event->key() == Qt::Key_D)HandleMove(0,0);
    else if (event->key() == Qt::Key_Up)HandleMove(1,1);
    else if (event->key() == Qt::Key_Left)HandleMove(1,2);
    else if (event->key() == Qt::Key_Down)HandleMove(1,3);
    else if (event->key() == Qt::Key_Right)HandleMove(1,0);

    else if (event->key() == Qt::Key_Z)ChosenToggle(0);
    else if (event->key() == Qt::Key_X)ChosenConfirm(0);
    else if (event->key() == Qt::Key_Period)ChosenToggle(1);
    else if (event->key() == Qt::Key_Slash)ChosenConfirm(1);
    else if (event->key() == Qt::Key_P)ItemGenerate();
    else if (event->key() == Qt::Key_O)gameTime=3;

//    QWidget::keyPressEvent(event);
}
