#ifndef FRAUNHOFER_H
#define FRAUNHOFER_H

#include <xtensor/xarray.hpp>
#include "mathutils.h"
#include <cmath>

class Aperture {
public:
    virtual double transmittance(double x, double y);
    virtual double intensity(double x, double y);
};

class Circle : Aperture {
public:
    Circle(double diameter);
    double transmittance(double x, double y);
    double intensity(double x, double y);

private:
    double diameter;
};

#endif // FRAUNHOFER_H
