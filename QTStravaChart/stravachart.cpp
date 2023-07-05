#include "stravachart.h"
#include "ui_stravachart.h"

StravaChart::StravaChart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StravaChart)
{
    ui->setupUi(this);
}

StravaChart::~StravaChart()
{
    delete ui;
}

