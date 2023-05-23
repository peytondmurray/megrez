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

    int ndata = 100;
    xt::xarray<double> x = xt::linspace(-1, 1, ndata);
    xt::xarray<double> y = xt::linspace(-1, 1, ndata);

    xt::xarray<double>::shape_type shape(ndata, ndata);
    xt::xarray<double> z(shape);

    for (auto i: x) {
        for (auto j: y) {
            z(i, j) = std::sph_bessel(1,)
        }
    }

}
