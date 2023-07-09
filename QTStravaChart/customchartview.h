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
    /*
    void mouseMoveEvent(QMouseEvent  *event) override
    {
        auto pos = event->pos();
        auto series = chart()->series();
        bool matchFound = false;
        QPointF matchingPoint;

        for (auto s : series) {
            auto lineSeries = qobject_cast<QLineSeries*>(s);
            if (lineSeries) {
                auto points = lineSeries->pointsVector();
                for (auto point : points) {
                    QPoint screenPoint = chart()->mapToPosition(point).toPoint();
                    if (QRect(screenPoint.x() - 3, screenPoint.y() - 3, 6, 6).contains(pos)) {
                        matchFound = true;
                        matchingPoint = point;
                        break;
                    }
                }
                if (matchFound) {
                    break;
                }
            }
        }

        if (matchFound) {
            QToolTip::showText(event->globalPos(), QString("y: %1").arg(matchingPoint.y()));
        } else {
            QToolTip::hideText();
        }
    }
    */
    void mouseMoveEvent(QMouseEvent  *event) override
    {
        auto pos = event->pos();
        auto series = chart()->series();
        bool matchFound = false;
        QPointF matchingPoint;
        qreal minDistance = std::numeric_limits<qreal>::max();
        qreal activationDistance = 10.0;  // Adjust this value to change the activation distance

        for (auto s : series) {
            auto lineSeries = qobject_cast<QLineSeries*>(s);
            if (lineSeries) {
                auto points = lineSeries->pointsVector();
                for (auto point : points) {
                    QPoint screenPoint = chart()->mapToPosition(point).toPoint();
                    qreal distance = QLineF(pos, screenPoint).length();
                    if (distance < minDistance && distance <= activationDistance) {
                        matchFound = true;
                        matchingPoint = point;
                        minDistance = distance;
                    }
                }
            }
        }

        if (matchFound) {
            QToolTip::showText(event->globalPos(), QString("y: %1").arg(matchingPoint.y()));
        } else {
            QToolTip::hideText();
        }
    }
};

#endif // CUSTOMCHARTVIEW_H
