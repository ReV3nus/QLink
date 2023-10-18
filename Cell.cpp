#include "Cell.h"
#include<QWidget>

Cell::Cell(QWidget *parent)
    : QWidget(parent)
{
    displayLabel=new QLabel(this);
    displayLabel->setFixedSize(60,60);
    displayLabel->setScaledContents(true);

    blockType=empty;
    num=0;
    x=y=0.0;

    setFixedSize(60,60);
}

Cell::~Cell()
{
    delete displayLabel;
}
void Cell::setPosition(double X,double Y)
{
    x=X,y=Y;
    move(X,Y);
}
void Cell::setCellSize(int size)
{
    displayLabel->setFixedSize(size,size);
    this->setFixedSize(size,size);
}
void Cell::setDisplay(BlockType type,int n)
{
    blockType=type;
    num=n;
    if(type==empty)
    {
        displayLabel->clear();
    }
    else if(type==chara)
    {
        std::string displayPath="D:/SelFiles/School/Projects/QLink/QLink/Resource/chara-";
        if(n==0)displayPath+="right.png";
        if(n==1)displayPath+="up.png";
        if(n==2)displayPath+="left.png";
        if(n==3)displayPath+="down.png";
        displayLabel->setPixmap(QPixmap(displayPath.c_str()));
        displayLabel->setAlignment(Qt::AlignCenter);
    }
    else
    {
        std::string displayPath="D:/SelFiles/School/Projects/QLink/QLink/Resource/"+std::to_string(((int)type))+"-"+std::to_string(n)+".png";
        displayLabel->setPixmap(QPixmap(displayPath.c_str()));
        displayLabel->setAlignment(Qt::AlignCenter);
    }
}

