#include "fraunhofer.h"

Aperture::Aperture(int nx, int ny) {
    this->nx = nx;
    this->ny = ny;
}

Aperture::~Aperture() {}

Circle::Circle(double diameter, int nx, int ny) : Aperture(nx, ny) {
    this->l = diameter;
}

double Circle::transmittance(double x, double y) {
    if (xyToR(x, y) > this->l/2) {
        return 0;
    }
    return 1;
}

double Circle::intensity(double x, double y, double z, double lambda) {
    double r = xyToR(x, y);
    double A = std::numbers::pi*(this->l/2)*(this->l/2);
    double k = 2*std::numbers::pi/lambda;
    double klr_over_2z = k*this->l*r/(2*z);
    double I_sqrt = (2*A*std::cyl_bessel_j(1, klr_over_2z))/((lambda*z)*klr_over_2z);
    return pow(I_sqrt, 2);
}
