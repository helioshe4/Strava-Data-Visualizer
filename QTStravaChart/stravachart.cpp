#include "stravachart.h"
#include "ui_stravachart.h"
#include "customchartview.h"
#include "credentialsdialog.h"

void StravaChart::updateChart(int index) {

    // Hide existing Y-axis and series from the chart
    if (index != 3) {
        axisY->hide();
        axisY2->hide();
        axisY3->hide();

        series_distance->hide();
        series_avg_hr->hide();
        series_moving_time->hide();
    }

    QLineSeries *newSeries = nullptr;
    QValueAxis *newAxisY = nullptr;
    QString metric;

    switch (index) {
        case 0:
            newSeries = series_distance;  // assumed to be already populated
            newAxisY = axisY;
            metric = "Distance (km)";
            break;
        case 1:
            newSeries = series_avg_hr;  // assumed to be already populated
            newAxisY = axisY2;
            metric = "Average HR (bpm)";
            break;
        case 2:
            newSeries = series_moving_time;  // assumed to be already populated
            newAxisY = axisY3;
            metric = "Moving Time (min)";
            break;
        case 3:
            axisY->show();
            axisY2->show();
            axisY3->show();

            series_distance->show();
            series_avg_hr->show();
            series_moving_time->show();
            return;
    }

    if (newSeries != nullptr && newAxisY != nullptr) {
        newAxisY->setLabelFormat("%i");
        newAxisY->setTitleText(metric);
        //chart1->addAxis(newAxisY, Qt::AlignRight);

        newSeries->show();
        newAxisY->show();
        //newSeries->attachAxis(axisX);  // assumed to be the existing X-axis
        //newSeries->attachAxis(newAxisY);
    }
}

void StravaChart::updateMaxValue(std::map<qint64, qreal>& maxValues, qint64 xValue, qreal yValue) {
    auto it = maxValues.find(xValue);
    if (it != maxValues.end()) {
        if (yValue > it->second) {
            it->second = yValue;
        }
    } else {
        maxValues[xValue] = yValue;
    }
}

void StravaChart::appendPointsToSeries(QtCharts::QLineSeries* series, const std::map<qint64, qreal>& maxValues) {
    QVector<QPointF> points;
    for (const auto& pair : maxValues) {
        points.append(QPointF(pair.first, pair.second));
    }
    series->clear();
    series->replace(points);
}

qint64 StravaChart::roundToNearestInterval(qint64 timestamp, qint64 interval) {
    return (timestamp / interval) * interval;
}


StravaChart::StravaChart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StravaChart)
{
    ui->setupUi(this);

    QString client_id;
    QString client_secret;
    QString refresh_token;
    CredentialsDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        client_id = dialog.getClientId();
        client_secret = dialog.getClientSecret();
        refresh_token = dialog.getRefreshToken();



        // If the user didn't enter any values, use the defaults
        if (client_id.isEmpty() && client_secret.isEmpty() && refresh_token.isEmpty()) {
            loadEnvFromFile("../src/.env");
            client_id = QString::fromStdString(std::getenv("CLIENT_ID"));
            client_secret = QString::fromStdString(std::getenv("STRAVA_CLIENT_SECRET"));
            refresh_token = QString::fromStdString(std::getenv("STRAVA_REFRESH_TOKEN"));
        }
    }
    //api call to get workoutdata
    std::vector<WorkoutDataPoint> data = getWorkoutData(client_id.toStdString(), client_secret.toStdString(), refresh_token.toStdString());

    series_distance = new QLineSeries();
    series_avg_hr = new QLineSeries();
    series_moving_time = new QLineSeries();
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

    chart1 = new QChart();
    //series
    chart1->addSeries(series_distance);
    chart1->addSeries(series_avg_hr);
    chart1->addSeries(series_moving_time);
    series_distance->setName("Distance (km)");
    series_avg_hr->setName("Average Heart Rate (bpm)");
    series_moving_time->setName("Moving Time (min)");
    series_avg_hr->hide();
    series_moving_time->hide();

    chart1->setAnimationOptions(QChart::AllAnimations);
    chart1->setTitle("Workout Metrics Over Time");

    // Create and set the x-axis
    axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart1->addAxis(axisX, Qt::AlignBottom);

    axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Distance (km)");
    chart1->addAxis(axisY, Qt::AlignRight);

    axisY2 = new QValueAxis;
    axisY2->setLabelFormat("%i");
    axisY2->setTitleText("Average HR (bpm)");
    chart1->addAxis(axisY2, Qt::AlignRight);

    axisY3 = new QValueAxis;
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
    axisY2->hide();
    axisY3->hide();


    //legend
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    //customchartview for tooltip
    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);


    /*------------------------CHART 2-------------------------------*/
    QChart *chart2 = new QChart();
    //general setup
    chart2->setTitle("Relationship between average HR and distance");
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

    //QVBoxLayout *layout = new QVBoxLayout(ui->chartContainer);
    QVBoxLayout *layout = new QVBoxLayout();

    QComboBox *comboBox1 = new QComboBox();
    comboBox1->addItem("Distance (km)");
    comboBox1->addItem("Average HR (bpm)");
    comboBox1->addItem("Moving Time (min)");
    comboBox1->addItem("All");
    layout->addWidget(comboBox1);
    layout->addWidget(chartView1);

    // connects combobox selection to rendered y axis
    connect(comboBox1, SIGNAL(currentIndexChanged(int)), this, SLOT(updateChart(int)));

//    QComboBox *comboBox2 = new QComboBox();
//    comboBox2->addItem("Distance (km)");
//    comboBox2->addItem("Average HR (bpm)");
//    comboBox2->addItem("Moving Time (min)");
//    comboBox2->addItem("All");
//    layout->addWidget(comboBox2);
    layout->addWidget(chartView2);

    ui->centralwidget->setLayout(layout);
}


StravaChart::~StravaChart()
{
    delete ui;
}

