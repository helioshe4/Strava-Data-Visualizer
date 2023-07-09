#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QLegendMarker>

QT_CHARTS_USE_NAMESPACE

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    ChartWidget(QWidget *parent = nullptr);

private slots:
    void handleMarkerClicked();

private:
    QChart *m_chart;
};

#endif // CHARTWIDGET_H
