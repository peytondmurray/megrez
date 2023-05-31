#ifndef FRAUNHOFER_H
#define FRAUNHOFER_H

#include <xtensor/xarray.hpp>
#include <cmath>

class Aperture {
public:
    virtual double transmittance();
    virtual double intensity();
};

class Circle : Aperture {
public:
    double transmittance();

private:
    // Aperture
    double l;
};

#endif // FRAUNHOFER_H
