#ifndef MODESELECT_H
#define MODESELECT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ModeSelect; }
QT_END_NAMESPACE

class ModeSelect : public QWidget
{
    Q_OBJECT

public:
    ModeSelect(QWidget *parent = nullptr);
    ~ModeSelect();

private:
    Ui::ModeSelect *ui;
};
#endif // MODESELECT_H
