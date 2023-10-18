#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVBoxLayout>
#include <QStackedLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setStyleSheet("background-color: white;");
    Init_setObjects();
    showHomeMenu();

    Init_connectBuild();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete widgetContainer;
    delete stackedLayout;

    delete modeSelect;
    delete homeMenu;
    delete loadOptions;
    delete singleMode;
    delete duoMode;
}
void MainWindow::setMenuSize() {setFixedSize(640,370);}
void MainWindow::setGameSizeSingle() {setFixedSize(1275,747);}
void MainWindow::setGameSizeDuo() {setFixedSize(1275,747);}
void MainWindow::quitGame() {this->close();}

void MainWindow::showHomeMenu() {setMenuSize(),stackedLayout->setCurrentWidget(homeMenu);singleMode->StopGame();}
void MainWindow::showModeSelect() {setMenuSize(),stackedLayout->setCurrentWidget(modeSelect);singleMode->StopGame();}
void MainWindow::showLoadOptions() {setMenuSize(),stackedLayout->setCurrentWidget(loadOptions);singleMode->StopGame();}

void MainWindow::startSingleMode() {setGameSizeSingle(),stackedLayout->setCurrentWidget(singleMode);singleMode->StartGame();}
void MainWindow::startDuoMode() {setGameSizeDuo(),stackedLayout->setCurrentWidget(duoMode);duoMode->StartGame();}

void MainWindow::Init_setObjects(){

    widgetContainer = new QWidget(this);
    setCentralWidget(widgetContainer);

    stackedLayout = new QStackedLayout(widgetContainer);
    widgetContainer->setLayout(stackedLayout);

    modeSelect = new ModeSelect(this);
    homeMenu = new HomeMenu(this);
    loadOptions = new LoadOptions(this);
    singleMode = new SingleMode(this);
    duoMode = new DuoMode(this);

    stackedLayout->addWidget(modeSelect);
    stackedLayout->addWidget(homeMenu);
    stackedLayout->addWidget(loadOptions);
    stackedLayout->addWidget(singleMode);
    stackedLayout->addWidget(duoMode);
}
void MainWindow::Init_connectBuild(){
    //MainWindow
    QAction *actionQuit=findChild<QAction*>("actionQuit");
    QAction *actionReturn=findChild<QAction*>("actionReturn");
    QAction *actionLoadSingle=findChild<QAction*>("actionLoadSingle");
    QAction *actionLoadDuo=findChild<QAction*>("actionLoadDuo");
    QAction *actionSaveFile=findChild<QAction*>("actionSaveFile");
    QAction *actionPause=findChild<QAction*>("actionPause");
    connect(actionQuit,&QAction::triggered,this,&MainWindow::quitGame);
    connect(actionReturn,&QAction::triggered,this,&MainWindow::showHomeMenu);
    connect(actionLoadSingle,&QAction::triggered,this,&MainWindow::LoadSingle);
    connect(actionLoadDuo,&QAction::triggered,this,&MainWindow::LoadDuo);
    connect(actionSaveFile,&QAction::triggered,this,&MainWindow::SaveFile);
    connect(actionPause,&QAction::triggered,this,&MainWindow::Pause);


    //HomeMenu Page
    QPushButton *startButton=homeMenu->findChild<QPushButton*>("startButton");
    QPushButton *loadButton=homeMenu->findChild<QPushButton*>("loadButton");
    QPushButton *quitButton=homeMenu->findChild<QPushButton*>("quitButton");
    connect(startButton,&QPushButton::clicked,this,&MainWindow::showModeSelect);
    connect(loadButton,&QPushButton::clicked,this,&MainWindow::showLoadOptions);
    connect(quitButton,&QPushButton::clicked,this,&MainWindow::quitGame);

    //ModeSelect Page
    QPushButton *singleButton=modeSelect->findChild<QPushButton*>("singleButton");
    QPushButton *duoButton=modeSelect->findChild<QPushButton*>("duoButton");
    QPushButton *returnButton_mode=modeSelect->findChild<QPushButton*>("returnButton");
    connect(returnButton_mode,&QPushButton::clicked,this,&MainWindow::showHomeMenu);
    connect(singleButton,&QPushButton::clicked,this,&MainWindow::startSingleMode);
    connect(duoButton,&QPushButton::clicked,this,&MainWindow::startDuoMode);

    //LoadOptions Page
    QPushButton *loadSingleButton=loadOptions->findChild<QPushButton*>("loadSingleButton");
    QPushButton *loadDuoButton=loadOptions->findChild<QPushButton*>("loadDuoButton");
    QPushButton *returnButton_load=loadOptions->findChild<QPushButton*>("returnButton");
    connect(returnButton_load,&QPushButton::clicked,this,&MainWindow::showHomeMenu);
    connect(loadSingleButton,&QPushButton::clicked,this,&MainWindow::LoadSingle);
    connect(loadDuoButton,&QPushButton::clicked,this,&MainWindow::LoadDuo);
}
void MainWindow::SaveFile()
{
    if(stackedLayout->currentWidget()==singleMode)
        singleMode->SaveFile();
    else if(stackedLayout->currentWidget()==duoMode)
        duoMode->SaveFile();
}
void MainWindow::LoadSingle()
{
    if(stackedLayout->currentWidget()==singleMode)
    {
        singleMode->StopGame();
        singleMode->LoadFile();
    }
    else if(stackedLayout->currentWidget()==duoMode)
    {
        duoMode->StopGame();
        setGameSizeSingle(),stackedLayout->setCurrentWidget(singleMode);
        singleMode->LoadFile();
    }
    else
    {
        setGameSizeSingle(),stackedLayout->setCurrentWidget(singleMode);
        singleMode->LoadFile();
    }
}
void MainWindow::LoadDuo()
{
    if(stackedLayout->currentWidget()==duoMode)
    {
        duoMode->StopGame();
        duoMode->LoadFile();
    }
    else if(stackedLayout->currentWidget()==singleMode)
    {
        singleMode->StopGame();
        setGameSizeSingle(),stackedLayout->setCurrentWidget(duoMode);
        duoMode->LoadFile();
    }
    else
    {
        setGameSizeSingle(),stackedLayout->setCurrentWidget(duoMode);
        duoMode->LoadFile();
    }
}
void MainWindow::Pause()
{
    if(stackedLayout->currentWidget()==duoMode)
    {
        duoMode->PauseAndContinue();
    }
    else if(stackedLayout->currentWidget()==singleMode)
    {
        singleMode->PauseAndContinue();
    }
}
