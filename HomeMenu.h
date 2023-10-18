#ifndef HOMEMENU_H
#define HOMEMENU_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class HomeMenu; }
QT_END_NAMESPACE

class HomeMenu : public QWidget
{
    Q_OBJECT

public:
    HomeMenu(QWidget *parent = nullptr);
    ~HomeMenu();

private:
    Ui::HomeMenu *ui;
};
#endif  //HOMEMENU_H
