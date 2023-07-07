#include "stravachart.h"
#include "customchartview.h"

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

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    QScatterSeries *series4 = new QScatterSeries();

    for (const WorkoutDataPoint& dataPoint : data) {
        // Convert the date to a QDateTime
        QString qstr = QString::fromStdString(dataPoint.start_date);
        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
        qint64 xValue = datetime.toMSecsSinceEpoch();
        series1->append(xValue, (dataPoint.distance) / 1000);
        series2->append(xValue, dataPoint.average_heartrate);
        series3->append(xValue, (dataPoint.moving_time) / 60);
        series4->append(dataPoint.average_heartrate, (dataPoint.distance) / 1000);
        std::cout << xValue << std::endl;
    }

    QChart *chart1 = new QChart();
    //series
    series1->setName("Distance");
    series2->setName("Average Heart rate");
    series3->setName("Moving Time");

    chart1->addSeries(series1);
    chart1->addSeries(series2);
    chart1->addSeries(series3);

    //labels on series
    series1->setPointLabelsVisible(true);
    series1->setPointLabelsFormat("@yPoint");

    series2->setPointLabelsVisible(true);
    series2->setPointLabelsFormat("@yPoint");

    series3->setPointLabelsVisible(true);
    series3->setPointLabelsFormat("@yPoint");

    chart1->setAnimationOptions(QChart::AllAnimations);

    chart1->setTitle("Workout Distance Over Time");

    // Create and set the x-axis
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart1->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Distance (km)");
    chart1->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);

    QValueAxis *axisY2 = new QValueAxis;
    axisY2->setLabelFormat("%i");
    axisY2->setTitleText("Average HR (bpm)");
    chart1->addAxis(axisY2, Qt::AlignRight);
    series2->attachAxis(axisY2);

    //legend
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

\
    CustomChartView *chartView1 = new CustomChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);


    //chart 2
    QChart *chart2 = new QChart();
    //general setup
    chart2->setTitle("Correlation between average HR and distance");
    chart2->createDefaultAxes();

    series4->setName("HR and Distance");
    series4->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series4->setMarkerSize(15.0);

    chart2->addSeries(series4);

    //axes
    QValueAxis *scatterAxisX = new QValueAxis;
    scatterAxisX->setLabelFormat("%i");
    scatterAxisX->setTitleText("Average HR");
    chart2->addAxis(scatterAxisX, Qt::AlignBottom);
    series4->attachAxis(scatterAxisX);

    QValueAxis *scatterAxisY = new QValueAxis;
    scatterAxisY->setLabelFormat("%i");
    scatterAxisY->setTitleText("Distance (km)");
    chart2->addAxis(scatterAxisY, Qt::AlignLeft);
    series4->attachAxis(scatterAxisY);

    CustomChartView *chartView2 = new CustomChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    chart2->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);

    // Create a layout and add the chart views
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView1);
    layout->addWidget(chartView2);


    // Create a widget, set its layout, and show it
    QWidget window;
    window.setLayout(layout);
    window.resize(1280, 800);
    window.show();


    return a.exec();
}
