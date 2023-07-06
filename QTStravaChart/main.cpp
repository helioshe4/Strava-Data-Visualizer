#include "stravachart.h"

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
#include "../include/api.h"
#include <ctime>
#include <iostream>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<WorkoutDataPoint> data = getWorkoutData();

    QLineSeries *series = new QLineSeries();
    //int count = 0;
    for (const WorkoutDataPoint& dataPoint : data) {
        // Convert the date to a QDateTime


        QString qstr = QString::fromStdString(dataPoint.start_date);
        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
        qint64 xValue = datetime.toMSecsSinceEpoch();
        series->append(xValue, (dataPoint.distance) / 1000);
        std::cout << xValue << std::endl;
//        QString qstr = QString::fromStdString(dataPoint.start_date);
//        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
//        qint64 xValue = datetime.toMSecsSinceEpoch();
//        series->append(xValue, (dataPoint.distance) / 1000);
//        std::cout << xValue << std::endl;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    //chart->createDefaultAxes();

    chart->setTitle("Workout Distance Over Time");

    // Create and set the x-axis
    QDateTimeAxis  *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Distance (km)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create and set the y-axis
//    QValueAxis *axisY = new QValueAxis();
//    axisY->setTitleText("Distance");
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    StravaChart window;
    window.setCentralWidget(chartView);
    window.resize(820, 600);
    window.show();

    return a.exec();
}
