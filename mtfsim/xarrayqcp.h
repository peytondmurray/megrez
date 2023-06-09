#include <QString>
#include <xtensor/xarray.hpp>
#include "qcustomplot.h"

class XArrayQCPColorMap: public QCPColorMap {
    using QCPColorMap::QCPColorMap;

private:
    QCPColorScale *scale;
    QCPMarginGroup *marginGroup;
    QCPColorGradient colorGradient;

public:

    XArrayQCPColorMap(
        QCustomPlot *plot,
        QCPColorGradient colorGradient = QCPColorGradient::gpGrayscale
    );

    void plotData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        const char *xlabel = "x",
        const char *ylabel = "y",
        const char *zlabel = "z"
    );
    void plotData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        const QString xlabel,
        const QString ylabel,
        const QString zlabel
    );
    void setData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        bool copy=false
    );
};
