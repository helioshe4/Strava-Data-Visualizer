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
#include <QComboBox>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QScatterSeries>
#include <QToolTip>
#include <QVBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>
#include <QtMath>

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
    QtCharts::QChart *chart1;
    QtCharts::QChart *chart2;
    QtCharts::QLineSeries *series_distance;
    QtCharts::QLineSeries *series_avg_hr;
    QtCharts::QLineSeries *series_moving_time;
    QtCharts::QDateTimeAxis *axisX;
    QtCharts::QValueAxis *axisY;
    QtCharts::QValueAxis *axisY2;
    QtCharts::QValueAxis *axisY3;

    QtCharts::QScatterSeries *series_scatter;
    //Scatter plot vectors
    QVector<qreal> distanceData;
    QVector<qreal> avgHRData;
    QVector<qreal> movingTimeData;

    QtCharts::QValueAxis *scatterAxisX;
    QtCharts::QValueAxis *scatterAxisY;



private slots:
    void updateChart1(int index);
    void updateChart2X(int index);
    void updateChart2Y(int index);
};


#endif // STRAVACHART_H
