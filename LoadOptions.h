#ifndef LOADOPTIONS_H
#define LOADOPTIONS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoadOptions; }
QT_END_NAMESPACE

class LoadOptions : public QWidget
{
    Q_OBJECT

public:
    LoadOptions(QWidget *parent = nullptr);
    ~LoadOptions();

private:
    Ui::LoadOptions *ui;
};
#endif // LOADOPTIONS_H
