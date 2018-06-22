#ifndef PLOT_H
#define PLOT_H

#include <Plotter.h>

class Plot
{
public:
     Plot();
    ~Plot();

    static void init();
    static void draw(double data1, double data2, double data3);


private:

    static double m_plotData1;
    static double m_plotData2;
    static double m_plotData3;

    static Plotter m_plotter;

    static const int POINTS_IN_TIME;
};

#endif // PLOT_H
