#ifndef STRAVACHART_H
#define STRAVACHART_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StravaChart; }
QT_END_NAMESPACE

class StravaChart : public QMainWindow
{
    Q_OBJECT

public:
    StravaChart(QWidget *parent = nullptr);
    ~StravaChart();

private:
    Ui::StravaChart *ui;
};


#endif // STRAVACHART_H
