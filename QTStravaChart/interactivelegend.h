#ifndef INTERACTIVELEGEND_H
#define INTERACTIVELEGEND_H

QT_BEGIN_NAMESPACE
namespace Ui { class InteractiveLegend; }
QT_END_NAMESPACE

class InteractiveLegend : public QLegend
{
    Q_OBJECT

public:
    InteractiveLegend(QChart *chart) : QLegend(chart) {
        connect(this, &QLegend::markerClicked, this, &InteractiveLegend::handleMarkerClicked);
    }

private slots:
    void handleMarkerClicked(QLegendMarker *marker) {
        marker->series()->setVisible(!marker->series()->isVisible());
        marker->setVisible(true);
        qreal alpha = marker->series()->isVisible() ? 1.0 : 0.5;
        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);
        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);
        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);
    }
};


#endif // INTERACTIVELEGEND_H
