#ifndef FRAUNHOFER_H
#define FRAUNHOFER_H

#include <qcustomplot.h>
#include <xtensor/xarray.hpp>
#include "mathutils.h"
#include <cmath>
#include <numbers>

class Aperture {
protected:
    int nx;         // Number of data points in the x-direction
    int ny;         // Number of data points in the y-direction
public:
    Aperture(int nx = 1000, int ny = 1000);
    ~Aperture();
    virtual double transmittance(double x, double y) = 0;
    virtual double intensity(double x, double y, double z, double lambda) = 0;
};

class Circle : Aperture {
public:
    Circle(double diameter, int nx = 1000, int ny = 1000);
    double transmittance(double x, double y);
    double intensity(double x, double y, double z, double lambda);
    QCPRange xrange;
    QCPRange yrange;

private:
    double l;       // Diameter
};

#endif // FRAUNHOFER_H
