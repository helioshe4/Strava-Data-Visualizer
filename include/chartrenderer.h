#ifndef CHARTRENDERER_H
#define CHARTRENDERER_H

#include <QtCharts>
#include <vector>
#include "workoutdatapoint.h"

class ChartRenderer {
public:
    ChartRenderer();
    void renderChart(const std::vector<WorkoutDataPoint>& data);
};

#endif // CHARTRENDERER_H

