#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QMouseEvent>
#include <QToolTip>

QT_CHARTS_USE_NAMESPACE

class CustomChartView : public QChartView
{
    Q_OBJECT
public:
    CustomChartView(QChart *chart, QWidget *parent = nullptr)
        : QChartView(chart, parent)
    {
        setMouseTracking(true);
    }

protected:
    void mouseMoveEvent(QMouseEvent  *event) override
    {
        auto pos = event->pos();
        auto series = chart()->series();
        for (auto s : series) {
            auto lineSeries = qobject_cast<QLineSeries*>(s);
            if (lineSeries) {
                auto points = lineSeries->pointsVector();
                for (auto point : points) {
                    QPoint screenPoint = chart()->mapToPosition(point).toPoint();
                    if (QRect(screenPoint.x() - 3, screenPoint.y() - 3, 6, 6).contains(pos)) {
                        QToolTip::showText(event->globalPos(), QString("y: %2").arg(point.y()));
                        return;
                    }
                }
            }
        }
        QToolTip::hideText();
    }
};

#endif // CUSTOMCHARTVIEW_H
