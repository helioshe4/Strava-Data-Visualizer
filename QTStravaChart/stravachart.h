#ifndef STRAVACHART_H
#define STRAVACHART_H

#include "../include/api.h"
#include <QMainWindow>
#include <ctime>
#include <iostream>
#include <QApplication>
#include <QDateTime>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QScatterSeries>
#include <QToolTip>
#include <QVBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>

QT_BEGIN_NAMESPACE
namespace Ui { class StravaChart; }
QT_END_NAMESPACE

class StravaChart : public QMainWindow
{
    Q_OBJECT

public:
    StravaChart(QWidget *parent = nullptr);
    ~StravaChart();

    void updateMaxValue(std::map<qint64, qreal>& maxValues, qint64 xValue, qreal yValue);
    void appendPointsToSeries(QtCharts::QLineSeries* series, const std::map<qint64, qreal>& maxValues);
    qint64 roundToNearestInterval(qint64 timestamp, qint64 interval);

private:
    Ui::StravaChart *ui;
};


#endif // STRAVACHART_H
