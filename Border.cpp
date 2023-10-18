#include "Border.h"

Border::Border(QWidget *parent)
    : QWidget(parent)
{
    displayLabel=new QLabel(this);
    displayLabel->setFixedSize(60,60);
    displayLabel->setScaledContents(true);

    setFixedSize(60,60);
}

Border::~Border()
{
    delete displayLabel;
}
void Border::setPosition(double X,double Y)
{
    move(X,Y);
}
void Border::setSize(int size)
{
    displayLabel->setFixedSize(size,size);
    this->setFixedSize(size,size);
}
void Border::setDisplay(char color)
{
    if(color=='c')
    {
        displayLabel->clear();
        return;
    }
    std::string displayPath="D:/SelFiles/School/Projects/QLink/QLink/Resource/border-";
    if(color=='r')displayPath+="red.png";
    if(color=='y')displayPath+="yellow.png";
    if(color=='b')displayPath+="blue.png";
    if(color=='g')displayPath+="green.png";
    if(color=='h')displayPath+="hint.png";
    displayLabel->setPixmap(QPixmap(displayPath.c_str()));
    displayLabel->setAlignment(Qt::AlignCenter);
    this->raise();
}
