#include "plot.h"

double  Plot::m_plotData1 = 0.0;
double  Plot::m_plotData2 = 0.0;
double  Plot::m_plotData3 = 0.0;

Plotter Plot::m_plotter;

const int Plot::POINTS_IN_TIME = 1000;

Plot::Plot()
{

}

void Plot::init()
{
    m_plotter.Begin(); // start plotter
    m_plotter.AddTimeGraph( "Testing graph", POINTS_IN_TIME,
                            "Data1", m_plotData1, "Data2", m_plotData2, "Data3", m_plotData3);
}

void Plot::draw(double data1, double data2, double data3)
{
    m_plotData1 = data1;
    m_plotData2 = data2;
    m_plotData3 = data3;

    m_plotter.Plot();
}

