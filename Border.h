#ifndef BORDER_H
#define BORDER_H
#include<QWidget>
#include<QLabel>

class Border : public QWidget
{
    Q_OBJECT

public:
    Border(QWidget *parent = nullptr);
    ~Border();
    void setPosition(double X,double Y);
    void setDisplay(char color);
    void setSize(int size);
private:
    QLabel *displayLabel;
};

#endif // BORDER_H
