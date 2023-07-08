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

void updateMaxValue(std::map<qint64, qreal>& maxValues, qint64 xValue, qreal yValue) {
    auto it = maxValues.find(xValue);
    if (it != maxValues.end()) {
        if (yValue > it->second) {
            it->second = yValue;
        }
    } else {
        maxValues[xValue] = yValue;
    }
}

void appendPointsToSeries(QLineSeries* series, const std::map<qint64, qreal>& maxValues) {
    QVector<QPointF> points;
    for (const auto& pair : maxValues) {
        points.append(QPointF(pair.first, pair.second));
    }
    series->clear();
    series->replace(points);
}

qint64 roundToNearestInterval(qint64 timestamp, qint64 interval) {
    return (timestamp / interval) * interval;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //api call to get workoutdata
    std::vector<WorkoutDataPoint> data = getWorkoutData();

    /*
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
    */

    QLineSeries *series_distance = new QLineSeries();
    QLineSeries *series_avg_hr = new QLineSeries();
    QLineSeries *series_moving_time = new QLineSeries();
    QScatterSeries *series_scatter = new QScatterSeries();

    std::map<qint64, qreal> maxValues1;
    std::map<qint64, qreal> maxValues2;
    std::map<qint64, qreal> maxValues3;

    qint64 interval = 6 * 60 * 60 * 1000;  // 6 hours in milliseconds

    for (const WorkoutDataPoint& dataPoint : data) {
        // Convert the date to a QDateTime
        QString qstr = QString::fromStdString(dataPoint.start_date);
        QDateTime datetime = QDateTime::fromString(qstr, Qt::ISODate);
        qint64 xValue = datetime.toMSecsSinceEpoch();
        xValue = roundToNearestInterval(xValue, interval);

        qreal yValue1 = (dataPoint.distance) / 1000;
        qreal yValue2 = dataPoint.average_heartrate;
        qreal yValue3 = (dataPoint.moving_time) / 60;

        // Check if we've already added a point with this x value for each series
        // and update the y value if the new one is greater
        updateMaxValue(maxValues1, xValue, yValue1);
        updateMaxValue(maxValues2, xValue, yValue2);
        updateMaxValue(maxValues3, xValue, yValue3);
    }

    // Now add the points to the series
    appendPointsToSeries(series_distance, maxValues1);
    appendPointsToSeries(series_avg_hr, maxValues2);
    appendPointsToSeries(series_moving_time, maxValues3);

    // For the scatter series, just append the points directly
    for (const WorkoutDataPoint& dataPoint : data) {
        series_scatter->append(dataPoint.average_heartrate, (dataPoint.distance) / 1000);
    }

    QChart *chart1 = new QChart();
    //series
    chart1->addSeries(series_distance);
    chart1->addSeries(series_avg_hr);
    chart1->addSeries(series_moving_time);
    series_distance->setName("Distance (km)");
    series_avg_hr->setName("Average Heart Rate (bpm)");
    series_moving_time->setName("Moving Time (min)");



    //labels on series
    /*
    series1->setPointLabelsVisible(true);
    series1->setPointLabelsFormat("@yPoint");

    series2->setPointLabelsVisible(true);
    series2->setPointLabelsFormat("@yPoint");

    series3->setPointLabelsVisible(true);
    series3->setPointLabelsFormat("@yPoint");
    */

    chart1->setAnimationOptions(QChart::AllAnimations);
    chart1->setTitle("Workout Metrics Over Time");

    // Create and set the x-axis
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart1->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Distance (km)");
    chart1->addAxis(axisY, Qt::AlignRight);

    QValueAxis *axisY2 = new QValueAxis;
    axisY2->setLabelFormat("%i");
    axisY2->setTitleText("Average HR (bpm)");
    chart1->addAxis(axisY2, Qt::AlignRight);

    QValueAxis *axisY3 = new QValueAxis;
    axisY3->setLabelFormat("%i");
    axisY3->setTitleText("Moving Time (min)");
    chart1->addAxis(axisY3, Qt::AlignRight);

    //attaching axes
    series_distance->attachAxis(axisX);
    series_avg_hr->attachAxis(axisX);
    series_moving_time->attachAxis(axisX);

    series_distance->attachAxis(axisY);
    series_avg_hr->attachAxis(axisY2);
    series_moving_time->attachAxis(axisY3);


    //legend
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    //customchartview for tooltip
    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    //chart 2
    QChart *chart2 = new QChart();
    //general setup
    chart2->setTitle("Correlation between average HR and distance");
    chart2->createDefaultAxes();

    series_scatter->setName("HR and Distance");
    series_scatter->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series_scatter->setMarkerSize(15.0);

    chart2->addSeries(series_scatter);

    //axes
    QValueAxis *scatterAxisX = new QValueAxis;
    scatterAxisX->setLabelFormat("%i");
    scatterAxisX->setTitleText("Average HR");
    chart2->addAxis(scatterAxisX, Qt::AlignBottom);
    series_scatter->attachAxis(scatterAxisX);

    QValueAxis *scatterAxisY = new QValueAxis;
    scatterAxisY->setLabelFormat("%i");
    scatterAxisY->setTitleText("Distance (km)");
    chart2->addAxis(scatterAxisY, Qt::AlignLeft);
    series_scatter->attachAxis(scatterAxisY);

    CustomChartView *chartView2 = new CustomChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    //legend
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
