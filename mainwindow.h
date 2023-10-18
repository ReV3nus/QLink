#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include "HomeMenu.h"
#include "ModeSelect.h"
#include "LoadOptions.h"
#include "SingleMode.h"
#include "DuoMode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *widgetContainer;
    QStackedLayout *stackedLayout;

    ModeSelect *modeSelect;
    HomeMenu *homeMenu;
    LoadOptions *loadOptions;
    SingleMode *singleMode;
    DuoMode *duoMode;

    void SaveFile();
    void LoadSingle();
    void LoadDuo();

    void setMenuSize();
    void setGameSizeSingle();
    void setGameSizeDuo();

    void showHomeMenu();
    void showModeSelect();
    void showLoadOptions();
    void startSingleMode();
    void startDuoMode();
    void Pause();

    void Init_setObjects();
    void Init_connectBuild();

    void quitGame();
};
#endif // MAINWINDOW_H
