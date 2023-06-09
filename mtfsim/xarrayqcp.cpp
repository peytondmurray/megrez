#include "mathutils.h"
#include "xarrayqcp.h"
#include <xtensor/xmath.hpp>

XArrayQCPColorMap::XArrayQCPColorMap(
    QCustomPlot *plot,
    QCPColorGradient colorGradient
) : QCPColorMap(plot->xAxis, plot->yAxis) {
    this->scale = nullptr;
    this->marginGroup = nullptr;
    this->colorGradient = colorGradient;
}

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    const char *xlabel,
    const char *ylabel,
    const char *zlabel
) {
    return this->plotData(x, y, z, QString(xlabel), QString(ylabel), QString(zlabel));
}

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z,
    const QString xlabel,
    const QString ylabel,
    const QString zlabel
) {

    this->keyAxis()->setLabel(xlabel);
    this->valueAxis()->setLabel(ylabel);

    int nx = x.shape(0);
    int ny = y.shape(0);

    double xmin = -1;
    double xmax = 1;
    double ymin = -1;
    double ymax = 1;

    this->data()->setSize(nx, ny);
    this->data()->setRange(
        QCPRange(xmin, xmax),
        QCPRange(ymin, ymax)
    );

    // If plotData is called twice, clean out existing
    // scale and marginGroup first.
    if (this->scale != nullptr) {
        delete this->scale;
    }
    if (this->marginGroup != nullptr) {
        delete this->marginGroup;
    }

    this->setData(x, y, z);

    // Set a new color scale up
    this->scale = new QCPColorScale(this->parentPlot());
    this->parentPlot()->plotLayout()->addElement(0, 1, this->scale);
    this->scale->setType(QCPAxis::atRight);
    this->setColorScale(this->scale);
    this->scale->axis()->setLabel("Intensity");
    this->scale->setGradient(this->colorGradient);
    this->rescaleDataRange();

    // Set a margin
    this->marginGroup = new QCPMarginGroup(this->parentPlot());
    this->parentPlot()->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    this->scale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
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
        QCPRange(x(0), x(x.size()-1)),
        QCPRange(y(0), y(y.size()-1))
    );
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            data->setCell(i, j, z(i, j));
        }
    }
    QCPColorMap::setData(data, copy);
    this->parentPlot()->replot();
}
