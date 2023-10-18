#ifndef SINGLEMODE_H
#define SINGLEMODE_H

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
namespace Ui { class SingleMode; }
QT_END_NAMESPACE

class SingleMode : public QWidget
{
    Q_OBJECT
#ifdef UNIT_TEST
    friend class SelectFunctionTest;
#endif

public:
    SingleMode(QWidget *parent = nullptr);
    ~SingleMode();
    void StartGame();
    void StopGame();

    void SaveFile();
    void LoadFile();

    void PauseAndContinue();

private:
    Ui::SingleMode *ui;
    QLabel *background;
    Position moveDir[4]={Position(0,1),Position(-1,0),Position(0,-1),Position(1,0)};

    bool isRunning=false;

    bool blockUsed[73];
    MapGenerator mapGenerator;
    Position CardPosition[10][20][2];
    void GenerateMap();

    int CellSize=60;
    Cell *cell[11][18];

    Position playerPos,chosenPos;
    bool isChosenActive;
    bool hadRemoteChosen;
    void HandleMove(int dirid);
    void PlayerMove(int dirid);
    void ChosenMove(int dirid);
    void ChosenToggle();
    void ChosenConfirm();

    Position selectedBlockPos;
    bool hasSelected;
    Border *borderCell,*borderCell2;
    void SelectBlock(Position pos,bool isRemote);
    bool CheckConnect(Position a,Position b);
    bool CCused[11][18];
    std::vector<Position>CCpath;
    bool CCdfs(Position now,Position des,int dirid,int cnt);
    LinkLine *linkLine;

    QTimer *delayTimer;
    Position secondPos;
    bool isDelayTimerWorking;
    void DelayTimerAction();

    void CellInit();
    void GameCleanInit();

    QTimer *gameTimer;
    QLabel *timeLabel,*scoreLabel;
    int gameTime;
    void updateTime();
    double gameScore;
    void updateScore(double sco);

    void EliminateBlock(BlockType type,int num);
    std::vector<BlockType>TypeList;
    std::vector<int>NumList;

    QString defaultTitle;
    QLabel *titleLabel;
    QLabel *gameLabel;

    QTimer *itemTimer;
    void ItemGenerate();
    void ItemFunction(int itemId);
    void ItemFunction_p1s();
    void ItemFunction_shuffle();
    void ItemFunction_hint();
    void ItemFunction_flash();

    QTimer *hintTimer;
    Border *hintCell1,*hintCell2;
    void HintTimeOut();

    QTimer *flashTimer;
    void FlashTimeOut();
    bool isFlashActive;
    void Flash(double x,double y);
    bool Fused[11][18];
    void Fdfs(Position now);

    QString SaveFilePath="D:/SelFiles/School/Projects/QLink/QLink/save/single.sav";
    QString gameCode;
    void GenerateCode();
    void LoadFromCode();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // SINGLEMODE_H
