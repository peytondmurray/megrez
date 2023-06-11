#include "fraunhofer.h"
#include <numbers>

Circle::Circle(double diameter) {
    this->diameter = diameter;
}

double Circle::transmittance(double x, double y) {
    if (xyToR(x, y) > this->diameter/2) {
        return 0;
    }
    return 1;
}

double Circle::intensity(double x, double y) {
    double r = xyToR(x, y);
    double A = std::numbers::pi*(this->diameter/2)*(this->diameter/2);

    double lambda = 1;



    return 0;
}
