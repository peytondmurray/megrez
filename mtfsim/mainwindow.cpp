#include "mainwindow.h"
#include "./ui_mainwindow.h"

QCPColorMapData xarrayToQCPColorMapData(
    xt::xarray<double> x,
    xt::xarray<double> y,
    xt::xarray<double> z
) {
    QCPColorMapData data(
        z.shape(0),
        z.shape(1),
        QCPRange(x(0), x(x.size()-1)),
        QCPRange(y(0), y(y.size()-1))
    );

    for (int i=0; i<z.shape(0); i++) {
        for (int j=0; j<z.shape(1); j++) {
            data.setData(x(i), y(i), z(i, j));
        }
    }
    return data;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadPlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlots() {
    ui->leftPlot->addGraph();
    ui->leftPlot->axisRect()->setupFullAxesBox(true);

    ui->leftPlot->xAxis->setLabel("x");
    ui->leftPlot->yAxis->setLabel("y");
    QCPColorMap *colorMap = new QCPColorMap(
        ui->leftPlot->xAxis,
        ui->leftPlot->yAxis
    );

    // Number of data points along x and y
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny);
    colorMap->data()->setRange(QCPRange(-1, 1), QCPRange(-1, 1));


    xt::xarray<double>::shape_type shape = {200, 200};
    xt::xarray<double> z(shape);

    xt::xarray<double> x = xt::linspace(-1, 1, nx);
    xt::xarray<double> y = xt::linspace(-1, 1, ny);

    // double xv, yv, zv;

    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            // colorMap->data()->cellToCoord(i, j, &xv, &yv);
            // zv = std::sph_bessel(1, xyToR(xv, yv));
            // colorMap->data()->setCell(i, j, zv);

            z(i, j) = std::sph_bessel(1, xyToR(x(i), y(j)));
            // colorMap->data()->setCell(i, j, z(i, j));
        }
    }

    QCPColorMapData data = xarrayToQCPColorMapData(x, y, z);
    colorMap->setData(&data);

    QCPColorScale *colorScale = new QCPColorScale(ui->leftPlot);
    ui->leftPlot->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorScale->axis()->setLabel("Intensity");
    colorMap->setGradient(QCPColorGradient::gpGrayscale);

    colorMap->rescaleDataRange();

    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->leftPlot);
    ui->leftPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    ui->leftPlot->rescaleAxes();
}
