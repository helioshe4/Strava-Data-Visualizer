#include "stravachart.h"
#include "chartwidget.h"

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
#include <QToolTip>
#include <QVBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QLegendMarker>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<WorkoutDataPoint> data = getWorkoutData();

    QLineSeries *series = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    for (const WorkoutDataPoint& dataPoint : data) {
        // Convert the date to a QDateTime
        QString qstr = QString::fromStdString(dataPoint.start_date);
        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
        qint64 xValue = datetime.toMSecsSinceEpoch();
        series->append(xValue, (dataPoint.distance) / 1000);
        series2->append(xValue, dataPoint.average_heartrate);
        series3->append(xValue, (dataPoint.moving_time) / 60);
        std::cout << xValue << std::endl;
    }

    QChart *chart = new QChart();
    //series
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->addSeries(series3);

    //legend
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //labels on series
    series->setPointLabelsVisible(true);
    series->setPointLabelsFormat("@yPoint");

    chart->setAnimationOptions(QChart::AllAnimations);

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

    QValueAxis *axisY2 = new QValueAxis;
    axisY2->setLabelFormat("%i");
    axisY2->setTitleText("Average HR (bpm)");
    chart->addAxis(axisY2, Qt::AlignRight);
    series2->attachAxis(axisY2);

    QChartView *chartView1 = new QChartView(chart);
    chartView1->setRenderHint(QPainter::Antialiasing);


     //chart 2
//    QLineSeries *series2 = new QLineSeries();
//    //int count = 0;
//    for (const WorkoutDataPoint& dataPoint : data) {
//        // Convert the date to a QDateTime

//        QString qstr = QString::fromStdString(dataPoint.start_date);
//        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
//        qint64 xValue = datetime.toMSecsSinceEpoch();
//        series2->append(xValue, (dataPoint.distance) / 1000);
//        std::cout << xValue << std::endl;
//    }


    // Create a layout and add the chart views
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView1);
    //layout->addWidget(chartView2);


    // Create a widget, set its layout, and show it
    QWidget window;
    window.setLayout(layout);
    window.resize(820, 600);
    window.show();


    return a.exec();
}
