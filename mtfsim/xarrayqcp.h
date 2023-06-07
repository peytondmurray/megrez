#include <QString>
#include <xtensor/xarray.hpp>
#include "qcustomplot.h"

class XArrayQCPColorMap: public QCPColorMap {
    using QCPColorMap::QCPColorMap;

private:
    QCPColorScale *scale;

public:
    void plotData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        const char *xlabel = "x",
        const char *ylabel = "y"
    );
    void plotData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        const QString xlabel,
        const QString ylabel
    );
    void setData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        bool copy=false
    );
};
