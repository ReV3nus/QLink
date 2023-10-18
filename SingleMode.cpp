#include "SingleMode.h"
#include "ui_SingleMode.h"
#include<QWidget>

SingleMode::SingleMode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SingleMode)
{
    ui->setupUi(this);
    CellInit();

    timeLabel=ui->TimeLabel;
    scoreLabel=ui->ScoreLabel;
    titleLabel=ui->TitileLabel;
    gameLabel=ui->GAMELabel;
    defaultTitle="QLink Game(Single Mode)";

    linkLine = new LinkLine(ui->centralwidgetdisplay);
    linkLine->move(0,0);
    linkLine->setFixedSize(1080,690);
    linkLine->raise();

    delayTimer = new QTimer(this);
    delayTimer->setSingleShot(true);
    gameTimer = new QTimer(this);
    gameTimer->setInterval(1000);
    itemTimer = new QTimer(this);
    itemTimer->setInterval(10000);
    hintTimer = new QTimer(this);
    hintTimer->setInterval(5000);
    flashTimer = new QTimer(this);
    flashTimer->setInterval(10000);

    connect(gameTimer,&QTimer::timeout,this,&SingleMode::updateTime);
    connect(delayTimer, &QTimer::timeout, this, &SingleMode::DelayTimerAction);
    connect(itemTimer,&QTimer::timeout,this,&SingleMode::ItemGenerate);
    connect(hintTimer,&QTimer::timeout,this,&SingleMode::HintTimeOut);
    connect(flashTimer,&QTimer::timeout,this,&SingleMode::FlashTimeOut);
}

SingleMode::~SingleMode()
{
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
            delete cell[i][j];
    delete borderCell;
    delete borderCell2;
    delete linkLine;
    delete ui;
}
void SingleMode::updateTime()
{
    if(!isRunning)return;
    timeLabel->setText(QString::number(gameTime));
    gameTime--;
    if(gameTime<0)
    {
        StopGame();
        gameLabel->setText("SCORE:"+QString::number(qRound(gameScore)));
        gameLabel->show();
    }
}
void SingleMode::updateScore(double sco)
{
    if(!isRunning)return;
    gameScore+=sco;
    scoreLabel->setText(QString::number(qRound(gameScore)));
}
void SingleMode::CellInit()
{
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            cell[i][j] = new Cell(ui->centralwidgetdisplay);
            cell[i][j]->setCellSize(CellSize);
            cell[i][j]->setPosition(j*CellSize,i*CellSize);
        }
    borderCell = new Border(ui->centralwidgetdisplay);
    borderCell2 = new Border(ui->centralwidgetdisplay);
    borderCell->setSize(CellSize);
    borderCell2->setSize(CellSize);
    borderCell2->setDisplay('c');

    hintCell1 = new Border(ui->centralwidgetdisplay);
    hintCell2 = new Border(ui->centralwidgetdisplay);
    hintCell1->setSize(CellSize);
    hintCell2->setSize(CellSize);
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');
}
void SingleMode::GameCleanInit()
{
    titleLabel->setText(defaultTitle);
    gameLabel->hide();
    gameTimer->start();
    itemTimer->start();

    isDelayTimerWorking=false;
    isChosenActive=false;
    hadRemoteChosen=false;
    hasSelected=false;
    isFlashActive=false;

    borderCell->setDisplay('c');
    borderCell2->setDisplay('c');
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');

    hasSelected=false;
    borderCell->setDisplay('c');
    borderCell2->setDisplay('c');
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');

    if(hintTimer->isActive())hintTimer->stop();
    if(flashTimer->isActive())flashTimer->stop();

    linkLine->ClearPoints();
    linkLine->hide();
}
void SingleMode::GenerateMap()
{
    for(int i=0;i<11;i++)cell[i][0]->setDisplay(empty,0),cell[i][17]->setDisplay(empty,0);
    for(int i=0;i<18;i++)cell[0][i]->setDisplay(empty,0),cell[10][i]->setDisplay(empty,0);
    mapGenerator.Generate_Map(cell,blockUsed);
    playerPos=Position(0,0);
    cell[0][0]->setDisplay(chara,3);

    hasSelected=false;
    borderCell->setDisplay('c');
    borderCell2->setDisplay('c');
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');
    if(hintTimer->isActive())hintTimer->stop();
    if(flashTimer->isActive())flashTimer->stop();

    linkLine->ClearPoints();
    linkLine->hide();

    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
            CardPosition[cell[i][j]->blockType][cell[i][j]->num][0]=CardPosition[cell[i][j]->blockType][cell[i][j]->num][1]=Position(0,0);
    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
        {
            if(CardPosition[cell[i][j]->blockType][cell[i][j]->num][0]==Position(0,0))
                CardPosition[cell[i][j]->blockType][cell[i][j]->num][0]=Position(i,j);
            else CardPosition[cell[i][j]->blockType][cell[i][j]->num][1]=Position(i,j);
        }
}
void SingleMode::StartGame()
{
    isRunning=true;
    gameTime=600;
    gameScore=0;
    updateTime();
    updateScore(0);
    GameCleanInit();
    TypeList.clear();
    NumList.clear();
    memset(blockUsed,0,sizeof(blockUsed));
    GenerateMap();
}
void SingleMode::StopGame()
{
    isRunning=false;
    gameTimer->stop();
    delayTimer->stop();
    itemTimer->stop();
    if(hintTimer->isActive())hintTimer->stop();
    if(flashTimer->isActive())flashTimer->stop();

    isDelayTimerWorking=false;
    isChosenActive=false;
    hadRemoteChosen=false;
    hasSelected=false;
    isFlashActive=false;

    borderCell->setDisplay('c');
    borderCell2->setDisplay('c');
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');
}
void SingleMode::PauseAndContinue()
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
void SingleMode::GenerateCode()
{
    gameCode="";
    gameCode+=NumberToChar(gameTime/72);
    gameCode+=NumberToChar(gameTime%72);
    int tmp=qRound(gameScore);
    char tmpchar[5];
    for(int i=0;i<5;i++)tmpchar[i]=NumberToChar(tmp%72),tmp/=72;
    gameCode+=tmpchar[4];
    gameCode+=tmpchar[3];
    gameCode+=tmpchar[2];
    gameCode+=tmpchar[1];
    gameCode+=tmpchar[0];
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(cell[i][j]->blockType==empty||cell[i][j]->blockType==item)gameCode+='`';
            else if(cell[i][j]->blockType==chara)gameCode+='/';
            else gameCode+=NumberToChar((cell[i][j]->blockType-1)*14+cell[i][j]->num);
        }
    for(int i=0;i<TypeList.size();i++)
        gameCode+=NumberToChar((TypeList[i]-1)*14+NumList[i]);
}
void SingleMode::LoadFromCode()
{
    isRunning=true;
    GameCleanInit();
    int tmpnum;
    int tmpid=0;
    std::string stringCode=gameCode.toStdString();
    gameTime=CharToNumber(stringCode[0])*72+CharToNumber(stringCode[1]);
    gameScore=0;
    for(tmpid=2;tmpid<7;tmpid++)
        gameScore*=72,gameScore+=CharToNumber(stringCode[tmpid]);
    tmpid=7;
    updateTime();
    updateScore(0);
    TypeList.clear();
    NumList.clear();
    for(int i=0;i<73;i++)blockUsed[i]=1;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=16;j++)
            CardPosition[cell[i][j]->blockType][cell[i][j]->num][0]=CardPosition[cell[i][j]->blockType][cell[i][j]->num][1]=Position(0,0);
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
        {
            if(stringCode[tmpid]=='`')
            {
                cell[i][j]->setDisplay(empty,0);
                tmpid++;
                continue;
            }
            if(stringCode[tmpid]=='/')
            {
                cell[i][j]->setDisplay(chara,3);
                playerPos=Position(i,j);
                tmpid++;
                continue;
            }
            tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
            int type=tmpnum/14+1;
            if(type==6)type--;
            int num=tmpnum-(type-1)*14;
            cell[i][j]->setDisplay((BlockType)type,num);
            blockUsed[tmpnum+1]=0;
            if(CardPosition[type][num][0]==Position(0,0))
                CardPosition[type][num][0]=Position(i,j);
            else CardPosition[type][num][1]=Position(i,j);
        }
    while(tmpid<stringCode.length())
    {
        tmpnum=CharToNumber(stringCode[tmpid]),tmpid++;
        int type=tmpnum/14+1;
        if(type==6)type--;
        int num=tmpnum-(type-1)*14;
        TypeList.push_back((BlockType)type);
        NumList.push_back(num);
    }
}
void SingleMode::SaveFile()
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
    QMessageBox::information(this, "保存提示", "成功保存至单人游戏存档文件", QMessageBox::Close);
}
void SingleMode::LoadFile()
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
void SingleMode::ItemGenerate()
{
    if(!isRunning)return;
    int genRan=QRandomGenerator::global()->bounded(100)+1;
    if(genRan<=33)return;
    int itemId=QRandomGenerator::global()->bounded(4)+1;
    std::vector<Position>emptyPos;
    emptyPos.clear();
    for(int i=0;i<11;i++)
        for(int j=0;j<18;j++)
            if(cell[i][j]->blockType==empty)emptyPos.push_back(Position(i,j));
    int posId=QRandomGenerator::global()->bounded(emptyPos.size());
    cell[emptyPos[posId].x][emptyPos[posId].y]->setDisplay(item,itemId);
}
void SingleMode::ItemFunction(int itemId)
{
    if(!isRunning)return;
    if(itemId==1)ItemFunction_p1s();
    if(itemId==2)ItemFunction_shuffle();
    if(itemId==3)ItemFunction_flash();
    if(itemId==4)ItemFunction_hint();

}
void SingleMode::ItemFunction_p1s()
{
    gameTime+=30;
    updateTime();
}
void SingleMode::ItemFunction_shuffle()
{
    isDelayTimerWorking=false;
    isChosenActive=false;
    hadRemoteChosen=false;

    GenerateMap();
}
void SingleMode::HintTimeOut()
{
    hintCell1->setDisplay('c');
    hintCell2->setDisplay('c');
    if(hintTimer->isActive())hintTimer->stop();
}
void SingleMode::ItemFunction_hint()
{
    std::vector<int>avaiList;
    avaiList.clear();
    for(int i=1;i<=72;i++)if(!blockUsed[i])avaiList.push_back(i);
    int ranId=QRandomGenerator::global()->bounded(avaiList.size());
    for(int fx=0;fx<72;fx++)
    {
        int i=ranId+fx;
        if(i>72)i-=72;
        if(blockUsed[i])continue;
        int type=(i-1)/14+1;
        if(type==6)type--;
        int num=i-1-(type-1)*14;
        Position a=CardPosition[type][num][0],b=CardPosition[type][num][1];
        if(!CheckConnect(a,b))continue;
//        qDebug("hint (%d,%d) and (%d,%d)\n",a.x,a.y,b.x,b.y);
        hintCell1->setPosition(a.y*CellSize,a.x*CellSize);
        hintCell2->setPosition(b.y*CellSize,b.x*CellSize);
        hintCell1->setDisplay('h');
        hintCell2->setDisplay('h');
        break;
    }

    if(hintTimer->isActive())hintTimer->stop();
    hintTimer->start();
}
void SingleMode::FlashTimeOut()
{
    isFlashActive=false;
    if(flashTimer->isActive())flashTimer->stop();
}
void SingleMode::ItemFunction_flash()
{
    if(flashTimer->isActive())flashTimer->stop();
    flashTimer->start();
    isFlashActive=true;
}
void SingleMode::Fdfs(Position now)
{
    Fused[now.x][now.y]=1;
    for(int i=0;i<4;i++)
    {
        Position nxt=now+moveDir[i];
        if(nxt.x<0||nxt.x>10||nxt.y<0||nxt.y>17)continue;
        if(!Fused[nxt.x][nxt.y]&&(cell[nxt.x][nxt.y]->blockType==empty||cell[nxt.x][nxt.y]->blockType==item))Fdfs(nxt);
    }
}
void SingleMode::Flash(double X,double Y)
{
    X-=90,Y-=60;
    qDebug("Flash %lf %lf\n",X,Y);
    int y=(X-0.1)/60,x=(Y-0.1)/60;
    if(x<0||x>11||y<0||y>17)return;
    memset(Fused,0,sizeof(Fused));
    Fdfs(Position(0,0));
    Position now=Position(x,y);
    Position movePos=Position(-1,-1);
    if(Fused[now.x][now.y])
        movePos=now;
    else
    {
        for(int i=0;i<4;i++)
        {
            Position nxt=now+moveDir[i];
            if(nxt.x<0||nxt.x>10||nxt.y<0||nxt.y>17)continue;
            if(!Fused[nxt.x][nxt.y])continue;
            movePos=nxt;
            break;
        }
    }
    if(movePos.x==-1)
        return;
    int itemNum=-1;
    if(cell[movePos.x][movePos.y]->blockType==item)
    {
        //accquire item
        itemNum=cell[movePos.x][movePos.y]->num;
    }
    cell[playerPos.x][playerPos.y]->setDisplay(empty,0);
    cell[movePos.x][movePos.y]->setDisplay(chara,3);
    playerPos=movePos;
    if(cell[now.x][now.y]->blockType>empty&&cell[now.x][now.y]->blockType<=any)
        SelectBlock(now,0);
    if(flashTimer->isActive())flashTimer->stop();
    isFlashActive=false;

    ItemFunction(itemNum);
}
void SingleMode::PlayerMove(int dirid)
{
    Position nxtPos=playerPos+moveDir[dirid];
    if(nxtPos.x<0||nxtPos.x>10||nxtPos.y<0||nxtPos.y>17)
    {
        cell[playerPos.x][playerPos.y]->setDisplay(chara,dirid);
        return;
    }
    if(cell[nxtPos.x][nxtPos.y]->blockType>empty&&cell[nxtPos.x][nxtPos.y]->blockType<=any)
    {
        //selectblock
        if(cell[playerPos.x][playerPos.y]->num==dirid)
            SelectBlock(nxtPos,false);
        else cell[playerPos.x][playerPos.y]->setDisplay(chara,dirid);
        return;
    }
    int itemNum=-1;
    if(cell[nxtPos.x][nxtPos.y]->blockType==item)
    {
        //accquire item
        itemNum=cell[nxtPos.x][nxtPos.y]->num;
    }
    cell[playerPos.x][playerPos.y]->setDisplay(empty,0);
    cell[nxtPos.x][nxtPos.y]->setDisplay(chara,dirid);
    playerPos=nxtPos;
    ItemFunction(itemNum);
}
void SingleMode::ChosenMove(int dirid)
{
    Position nxtPos=chosenPos+moveDir[dirid];
    if(nxtPos.x<0||nxtPos.x>10||nxtPos.y<0||nxtPos.y>17)
        return;
    chosenPos=nxtPos;
    borderCell2->setPosition(nxtPos.y*CellSize,nxtPos.x*CellSize);
    return;
}
bool SingleMode::CCdfs(Position now,Position des,int dirid,int cnt)
{
    CCused[now.x][now.y]=1;
    CCpath.push_back(now);
    if(now==des)return 1;
    Position nxt=now+moveDir[dirid];
    if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[nxt.x][nxt.y])
    {
        if(cell[nxt.x][nxt.y]->blockType==empty||cell[nxt.x][nxt.y]->blockType>=chara)
        {
            if(CCdfs(nxt,des,dirid,cnt))return 1;
        }
        else if(nxt==des)return CCdfs(nxt,des,dirid,cnt);
    }
    if(cnt<=1)
    {
        int dir1=dirid^1,dir2=dir1^2;
        nxt=now+moveDir[dir1];
        if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[nxt.x][nxt.y])
        {
            if(cell[nxt.x][nxt.y]->blockType==empty||cell[nxt.x][nxt.y]->blockType>=chara)
            {
                if(CCdfs(nxt,des,dir1,cnt+1))return 1;
            }
            else if(nxt==des)return CCdfs(nxt,des,dir1,cnt+1);
        }

        nxt=now+moveDir[dir2];
        if((nxt.x>=0&&nxt.x<=10&&nxt.y>=0&&nxt.y<=17)&&!CCused[nxt.x][nxt.y])
        {
            if(cell[nxt.x][nxt.y]->blockType==empty||cell[nxt.x][nxt.y]->blockType>=chara)
            {
                if(CCdfs(nxt,des,dir2,cnt+1))return 1;
            }
            else if(nxt==des)return CCdfs(nxt,des,dir2,cnt+1);
        }
    }
    CCused[now.x][now.y]=0;
    CCpath.pop_back();
    return 0;
}
bool SingleMode::CheckConnect(Position a,Position b)
{
//    qDebug("now checking connection of block (%d,%d) and (%d,%d)\n",a.x,a.y,b.x,b.y);
    memset(CCused,0,sizeof(CCused));
    CCpath.clear();
    CCpath.push_back(a);
    CCused[a.x][a.y]=1;
    for(int i=0;i<4;i++)
    {
        Position nxt=a+moveDir[i];
        if(cell[nxt.x][nxt.y]->blockType==empty||cell[nxt.x][nxt.y]->blockType>=chara)
        {
            if(CCdfs(nxt,b,i,0))break;
        }
        else if(nxt==b)
        {
            CCused[nxt.x][nxt.y]=1;
            CCpath.push_back(nxt);
        }
        if(CCused[b.x][b.y])break;
    }
    return CCused[b.x][b.y];
}
void SingleMode::DelayTimerAction()
{
    isDelayTimerWorking=false;
    if(secondPos.x==-1)
    {
        borderCell->setDisplay('c');
        borderCell2->setDisplay('c');
        hasSelected=false;
        return;
    }
    borderCell->setDisplay('c');
    borderCell2->setDisplay('c');
    linkLine->hide();
    linkLine->ClearPoints();

    hasSelected=false;

    BlockType type=cell[secondPos.x][secondPos.y]->blockType;
    int num=cell[secondPos.x][secondPos.y]->num;
    blockUsed[1+(int)(type-spade)*14+num]=1;
    cell[selectedBlockPos.x][selectedBlockPos.y]->setDisplay(empty,0);
    cell[secondPos.x][secondPos.y]->setDisplay(empty,0);
    bool tmpflag=1;
    for(int i=1;i<=72;i++)tmpflag&=blockUsed[i];


    if(tmpflag)
    {
        StopGame();
        gameLabel->setText("SCORE:"+QString::number(qRound(gameScore)));
        gameLabel->show();
    }
    return;
}
void SingleMode::EliminateBlock(BlockType type,int num)
{
    if(hadRemoteChosen)
    {
        updateScore(10);
        titleLabel->setText("Remote Eliminated.(+10)");
        TypeList.push_back(empty);
        NumList.push_back(0);
        return;
    }
    TypeList.push_back(type);
    NumList.push_back(num);

    bool joker=0,JOKER=0;
    //same number
    double score1=10;
    int sameCount=1;
    int i=TypeList.size()-2;
    for(;i>=0;i--)
    {
        if(!TypeList[i])break;
        if(NumList[i+1]>0&&NumList[i+1]<=13&&NumList[i]>0&&NumList[i+1]<=13&&NumList[i+1]!=NumList[i])break;
        sameCount++;
        if(NumList[i]==14)joker=1;
        if(NumList[i]==15)JOKER=1;
    }
    score1*=pow(4,sameCount-1);
    //staright
    double score2=10;
    int StraightCount=1;
    int TypeCount[5]={0,0,0,0,0};
    int maxTypeId;
    int maxCount=0;
    i=TypeList.size()-1;
    if(TypeList[i]<5)TypeCount[TypeList[i]]++;
    else TypeCount[1]=TypeCount[2]=TypeCount[3]=TypeCount[4]=1;
    i--;
    for(;i>=0;i--)
    {
        if(!TypeList[i])break;
        if(NumList[i+1]>0&&NumList[i+1]<=13&&NumList[i]>0&&NumList[i+1]<=13&&NumList[i+1]!=NumList[i]+1)break;
        if(TypeList[i]<5)TypeCount[TypeList[i]]++;
        else TypeCount[1]++,TypeCount[2]++,TypeCount[3]++,TypeCount[4]++;
        StraightCount++;
        if(NumList[i]==14)joker=1;
        if(NumList[i]==15)JOKER=1;
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
        updateScore(score1*(joker?1.5:1)*(JOKER?2:1));
        titleLabel->setText(displayString);
    }
    else
    {
        displayString+="Straight of "+QString::number(StraightCount)+", within "+QString::number(maxCount);
        if(maxTypeId==1)displayString+="Spades! ";
        if(maxTypeId==2)displayString+="Hearts! ";
        if(maxTypeId==3)displayString+="Clubs! ";
        if(maxTypeId==4)displayString+="Diamonds! ";
        if(joker)displayString+="(joker! x1.5) ";
        if(JOKER)displayString+="(JOKER! x2) ";
        displayString+="(+"+QString::number(score2*(joker?1.5:1)*(JOKER?2:1))+")";
        updateScore(score2*(joker?1.5:1)*(JOKER?2:1));
        titleLabel->setText(displayString);
    }
}
void SingleMode::SelectBlock(Position pos,bool isRemote)
{
    if(!hasSelected)
    {
        hasSelected=true;
        selectedBlockPos=pos;
        borderCell->setPosition(pos.y*CellSize,pos.x*CellSize);
        borderCell->setDisplay('b');
        hadRemoteChosen=isRemote;
        return;
    }
    else
    {
        if(pos==selectedBlockPos)
        {
            hasSelected=false;
            borderCell->setDisplay('c');
            hadRemoteChosen=false;
            return;
        }
        hadRemoteChosen|=isRemote;

        borderCell2->setPosition(pos.y*CellSize,pos.x*CellSize);
        if(cell[selectedBlockPos.x][selectedBlockPos.y]->blockType!=cell[pos.x][pos.y]->blockType||
            cell[selectedBlockPos.x][selectedBlockPos.y]->num!=cell[pos.x][pos.y]->num||
            cell[pos.x][pos.y]->blockType<spade||cell[pos.x][pos.y]->blockType>any||
            !CheckConnect(selectedBlockPos,pos))
        {
            borderCell->setDisplay('r');
            borderCell2->setDisplay('r');

            isDelayTimerWorking=true;
            secondPos=Position(-1,-1);
            delayTimer->start(500);
            return;
        }
        borderCell->setDisplay('g');
        borderCell2->setDisplay('g');

        linkLine->ClearPoints();
        for(int i=0;i<CCpath.size();i++)
            linkLine->AddPoint(CCpath[i].y*CellSize+(CellSize>>1),CCpath[i].x*CellSize+(CellSize>>1));
        linkLine->show();
        linkLine->raise();
        linkLine->update();

        isDelayTimerWorking=true;
        secondPos=pos;

        EliminateBlock(cell[pos.x][pos.y]->blockType,cell[pos.x][pos.y]->num);

        delayTimer->start(500);
        return;
    }
}
void SingleMode::HandleMove(int dirid)
{
    if(isChosenActive)ChosenMove(dirid);
    else PlayerMove(dirid);
}
void SingleMode::ChosenToggle()
{
    if(isChosenActive)
    {
        isChosenActive=false;
        borderCell2->setDisplay('c');
        return;
    }
    Position nxt=playerPos+moveDir[cell[playerPos.x][playerPos.y]->num];
    if(cell[nxt.x][nxt.y]->blockType>=spade&&cell[nxt.x][nxt.y]->blockType<=any)
    {
        isChosenActive=true;
        borderCell2->setPosition(nxt.y*CellSize,nxt.x*CellSize);
        borderCell2->setDisplay('y');
        chosenPos=nxt;
    }
    return;
}
void SingleMode::ChosenConfirm()
{
    isChosenActive=false;
    borderCell2->setDisplay('c');
    if(cell[chosenPos.x][chosenPos.y]->blockType>=spade&&cell[chosenPos.x][chosenPos.y]->blockType<=any)
    {
        SelectBlock(chosenPos,true);
    }
    return;
}
void SingleMode::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)PauseAndContinue();
    if(isDelayTimerWorking)return;
    if(!isRunning)return;
    if (event->key() == Qt::Key_W)HandleMove(1);
    else if (event->key() == Qt::Key_A)HandleMove(2);
    else if (event->key() == Qt::Key_S)HandleMove(3);
    else if (event->key() == Qt::Key_D)HandleMove(0);
    else if (event->key() == Qt::Key_Z)ChosenToggle();
    else if (event->key() == Qt::Key_X)ChosenConfirm();
    else if (event->key() == Qt::Key_P)ItemGenerate();
    else if (event->key() == Qt::Key_O)gameTime=3;

    QWidget::keyPressEvent(event);
}
void SingleMode::mousePressEvent(QMouseEvent *event)
{
    if(isDelayTimerWorking)return;
    if(!isRunning)return;
    if(isFlashActive)
    {
        QPoint pos = event->pos();
        Flash(pos.x(),pos.y());
    }

    QWidget::mousePressEvent(event);
}
