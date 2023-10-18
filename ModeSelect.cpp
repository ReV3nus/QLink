#include "ModeSelect.h"
#include "ui_ModeSelect.h"
#include<QWidget>

ModeSelect::ModeSelect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModeSelect)
{
    ui->setupUi(this);

}

ModeSelect::~ModeSelect()
{
    delete ui;
}

