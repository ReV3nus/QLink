#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QLabel>

enum BlockType{empty,spade,heart,club,diamond,any,chara,item};
class Cell : public QWidget
{
    Q_OBJECT

public:
    BlockType blockType;
    int num;
    double x=0,y=0;

    Cell(QWidget *parent = nullptr);
    ~Cell();
    void setPosition(double X,double Y);
    void setDisplay(BlockType type,int n);
    void setCellSize(int size);
private:
    QLabel *displayLabel;
};
#endif // CELL_H
