#include "LoadOptions.h"
#include "ui_LoadOptions.h"
#include<QWidget>

LoadOptions::LoadOptions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoadOptions)
{
    ui->setupUi(this);
}

LoadOptions::~LoadOptions()
{
    delete ui;
}

