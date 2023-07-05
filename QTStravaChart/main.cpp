#include "stravachart.h"

#include <QApplication>
#include <QtWidgets/QMainWindow>
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

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QBarSet *set0 = new QBarSet("Altuve");
    QBarSet *set1 = new QBarSet("Martinez");
    QBarSet *set2 = new QBarSet("Segura");
    QBarSet *set3 = new QBarSet("Simmons");
    QBarSet *set4 = new QBarSet("Trout");

    *set0 << 283 << 341 << 313 << 338 <<346 << 335;
    *set1 << 283 << 341 << 313 << 300 <<346 << 335;
    *set2 << 283 << 215 << 313 << 338 <<346 << 335;
    *set3 << 283 << 341 << 313 << 214 <<346 << 413;
    *set4 << 283 << 341 << 313 << 338 <<213 << 335;

    //vertical bar
    //QBarSeries *series = new QBarSeries();
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Batting avg by Year");
    //NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories;
    categories << "2013" << "2014" << "2015" << "2016" << "2017" << "2018";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    //vertical bar
    //chart->setAxisX(axis, series);
    //horizontal bar
    chart->setAxisY(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xfffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));

    StravaChart w;
    w.show();
    return a.exec();
}
