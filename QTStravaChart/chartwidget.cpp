#include "chartwidget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include "../include/api.h"
#include <QVBoxLayout>

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent), m_chart(new QChart)
{
    // Connect all markers to handler
    const auto markers = m_chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked, this, &ChartWidget::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &ChartWidget::handleMarkerClicked);
    }


}

void ChartWidget::handleMarkerClicked()
{
    // Your marker click handling code here...
}
