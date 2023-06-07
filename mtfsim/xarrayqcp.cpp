#include "xarrayqcp.h"
#include <xtensor/xmath.hpp>

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    const char *xlabel,
    const char *ylabel
) {
    return this->plotData(x, y, z, QString(xlabel), QString(ylabel));
}

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    const QString xlabel,
    const QString ylabel
) {

    this->keyAxis()->setLabel(xlabel);
    this->valueAxis()->setLabel(ylabel);

    int nx = x.shape(0);
    int ny = y.shape(0);

    double xmin = x(xt::amin(x));
    double xmax = x(xt::amax(x));
    double ymin = y(xt::amin(y));
    double ymax = y(xt::amax(y));

    this->data()->setSize(nx, ny);
    this->data()->setRange(
        QCPRange(xmin, xmax),
        QCPRange(ymin, ymax)
    );

    if (this->scale != nullptr) {
        delete this->scale;
    }
    this->scale = new QCPColorScale(this);
}

void XArrayQCPColorMap::setData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    bool copy
) {
    QCPColorMapData *data = new QCPColorMapData(
        z.shape(0),
        z.shape(1),
        QCPRange(x(0), x(x.size()-1)),
        QCPRange(y(0), y(y.size()-1))
    );

    for (int i=0; i<static_cast<int>(z.shape(0)); i++) {
        for (int j=0; j<static_cast<int>(z.shape(1)); j++) {
            data->setData(x(i), y(i), z(i, j));
        }
    }
    QCPColorMap::setData(data, copy);
}
