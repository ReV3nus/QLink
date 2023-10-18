#ifndef DUOMODE_H
#define DUOMODE_H

#include <QWidget>
#include "Cell.h"
#include "Border.h"
#include "MapGenerator.h"
#include "LinkLine.h"
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QTimer>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class DuoMode; }
QT_END_NAMESPACE

class DuoMode : public QWidget
{
    Q_OBJECT

public:
    DuoMode(QWidget *parent = nullptr);
    ~DuoMode();
    void StartGame();
    void StopGame();

    void SaveFile();
    void LoadFile();

    void PauseAndContinue();
private:
    Ui::DuoMode *ui;
    Position moveDir[4]={Position(0,1),Position(-1,0),Position(0,-1),Position(1,0)};

    bool isRunning=false;

    bool blockUsed[2][73];
    MapGenerator mapGenerator;
    Position CardPosition[10][20][2];
    void GenerateMap();

    int CellSize=30;
    Cell *cell[2][11][18];

    Position playerPos[2],chosenPos[2];
    bool isChosenActive[2];
    bool hadRemoteChosen[2];
    void HandleMove(int playerid,int dirid);
    void PlayerMove(int playerid,int dirid);
    void ChosenMove(int playerid,int dirid);
    void ChosenToggle(int playerid);
    void ChosenConfirm(int playerid);

    Position selectedBlockPos[2];
    bool hasSelected[2];
    Border *borderCell[2],*borderCell2[2];
    void SelectBlock(int playerid,Position pos,bool isRemote);
    bool CheckConnect(int playerid,Position a,Position b);
    bool CCused[2][11][18];
    std::vector<Position>CCpath[2];
    bool CCdfs(int playerid,Position now,Position des,int dirid,int cnt);
    LinkLine *linkLine[2];

    QTimer *delayTimer[2];
    Position secondPos[2];
    bool isDelayTimerWorking[2];
    void DelayTimerAction_p1();
    void DelayTimerAction_p2();

    void CellInit();
    void GameCleanInit();

    QTimer *gameTimer;
    QLabel *timeLabel,*scoreLabel[2];
    int gameTime;
    void updateTime();
    double gameScore[2];
    void updateScore(int playerid,double sco);

    void EliminateBlock(int playerid,BlockType type,int num);
    std::vector<BlockType>TypeList[2];
    std::vector<int>NumList[2];

    QString defaultTitle[2];
    QLabel *playerLabel[2];
    QLabel *gameLabel;

    QTimer *itemTimer;
    void ItemGenerate();
    void ItemFunction(int playerid,int itemId);
    void ItemFunction_p1s();
    void ItemFunction_shuffle();
    void ItemFunction_hint();
    void ItemFunction_freeze(int playerid);
    void ItemFunction_dizzle(int playerid);

    QTimer *hintTimer;
    Border *hintCell1[2],*hintCell2[2];
    void HintTimeOut();

    QTimer *freezeTimer[2];
    bool isFrozen[2];
    void freezeTimeOut_p1();
    void freezeTimeOut_p2();

    QTimer *dizzleTimer[2];
    bool isDizzle[2];
    void dizzleTimeOut_p1();
    void dizzleTimeOut_p2();

    QString SaveFilePath="D:/SelFiles/School/Projects/QLink/QLink/save/duo.sav";
    QString gameCode;
    void GenerateCode();
    void LoadFromCode();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // DUOMODE_H
