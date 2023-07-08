#include "mathutils.h"
#include "xarrayqcp.h"
#include <xtensor/xmath.hpp>
#include <xtensor/xio.hpp>

XArrayQCPColorMap::XArrayQCPColorMap(
    QCustomPlot *plot,
    const char *xlabel,
    const char *ylabel,
    const char *zlabel,
    QCPColorGradient colorGradient
) : QCPColorMap(plot->xAxis, plot->yAxis) {
    this->scale = nullptr;
    this->marginGroup = nullptr;
    this->setInterpolate(false);

    this->colorGradient = colorGradient;
    this->keyAxis()->setLabel(QString(xlabel));
    this->valueAxis()->setLabel(QString(ylabel));

    // Set a new color scale up
    this->scale = new QCPColorScale(this->parentPlot());
    this->parentPlot()->plotLayout()->addElement(0, 1, this->scale);
    this->scale->setType(QCPAxis::atRight);
    this->setColorScale(this->scale);
    this->scale->axis()->setLabel(zlabel);
    this->scale->setGradient(this->colorGradient);

    // Set a margin
    this->marginGroup = new QCPMarginGroup(this->parentPlot());
    this->parentPlot()->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    this->scale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
}

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z
) {
    this->setData(x, y, z);
    this->rescaleDataRange();
    this->parentPlot()->rescaleAxes();
}

void XArrayQCPColorMap::setData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    bool copy
) {
    int nx = x.shape(0);
    int ny = y.shape(0);
    QCPColorMapData *data = new QCPColorMapData(
        z.shape(0),
        z.shape(1),
        QCPRange(xt::amin(x)(0), xt::amax(x)(0)),
        QCPRange(xt::amin(y)(0), xt::amax(y)(0))
    );

    double zmax = xt::amax(z)(0);

    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            data->setCell(i, j, z(i, j)/zmax);
        }
    }
    QCPColorMap::setData(data, copy);
    this->parentPlot()->replot();
}
