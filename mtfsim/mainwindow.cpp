#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    XArrayQCPColorMap *colorMap = new XArrayQCPColorMap(
        ui->leftPlot->xAxis,
        ui->leftPlot->yAxis
    );

    // Number of data points along x and y
    int nx = 200;
    int ny = 200;
    xt::xarray<double> x = xt::linspace(-1, 1, nx);
    xt::xarray<double> y = xt::linspace(-1, 1, ny);
    xt::xarray<double>::shape_type shape = {200, 200};
    xt::xarray<double> z(shape);


    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            z(i, j) = std::sph_bessel(1, xyToR(x(i), y(j)));
        }
    }

    colorMap->plotData(x, y, z);

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
