#include "mathutils.h"
#include "xarrayqcp.h"
#include <xtensor/xmath.hpp>
#include <xtensor/xio.hpp>

XArrayQCPColorMap::XArrayQCPColorMap(
    QCustomPlot *plot,
    const char *xlabel,
    const char *ylabel,
    const char *zlabel,
    double xmin,
    double xmax,
    double ymin,
    double ymax,
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

    this->data()->setKeyRange(QCPRange(xmin, xmax));
    this->data()->setValueRange(QCPRange(ymin, ymax));
}

void XArrayQCPColorMap::plotData(std::function<double(double, double)> zfunc) {
    this->setData(zfunc);
    this->rescaleDataRange();
    this->parentPlot()->rescaleAxes();
}

void XArrayQCPColorMap::setData(std::function<double(double, double)> zfunc, bool copy) {
    QCPColorMapData *data = this->data();
    QCPColorMapData *newdata = new QCPColorMapData(
        data->keySize(),
        data->valueSize(),
        data->keyRange(),
        data->valueRange()
    );

    double x, y;
    for (int i=0; i<data->keySize(); i++) {
        for (int j=0; j<data->valueSize(); j++) {
            double z = zfunc(x, y);
            data->cellToCoord(i, j, &x, &y);
            newdata->setCell(i, j, z);
        }
    }
    QCPColorMap::setData(newdata, copy);
}

void XArrayQCPColorMap::plotData(
    const xt::xarray<double> &x,
    const xt::xarray<double> &y,
    const xt::xarray<double> &z
) {
    this->setData(x, y, z);
    this->parentPlot()->replot();
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
}
