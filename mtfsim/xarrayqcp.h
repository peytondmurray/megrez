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
        double xmin,
        double xmax,
        double ymin,
        double ymax,
        QCPColorGradient colorGradient = QCPColorGradient::gpGrayscale
    );

    void plotData(std::function<double(double, double)>, QCPRange xrange, QCPRange yrange);
    void setData(
        std::function<double(double, double)>,
        bool copy=false
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

    void setDataRescaled(
        std::function<double(double, double)> zfunc,
        QCPRange xrange,
        QCPRange yrange,
        bool copy=false
    );
};
