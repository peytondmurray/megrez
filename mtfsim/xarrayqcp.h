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
        const char *xlabel,
        const char *ylabel,
        const char *zlabel,
        QCPColorGradient colorGradient = QCPColorGradient::gpGrayscale
    );

    void plotData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z
    );
    void setData(
        const xt::xarray<double> &x,
        const xt::xarray<double> &y,
        const xt::xarray<double> &z,
        bool copy=false
    );
};
