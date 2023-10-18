#include "HomeMenu.h"
#include "ui_HomeMenu.h"

HomeMenu::HomeMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeMenu)
{
    ui->setupUi(this);
}

HomeMenu::~HomeMenu()
{
    delete ui;
}

