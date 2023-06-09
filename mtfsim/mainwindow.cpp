#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <xtensor/xutils.hpp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->loadPlots();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadPlots() {
    ui->leftPlot->addGraph();
    ui->leftPlot->axisRect()->setupFullAxesBox(true);

    XArrayQCPColorMap *colorMap = new XArrayQCPColorMap(ui->leftPlot);

    // Number of data points along x and y
    unsigned long nx = 100;
    unsigned long ny = 100;
    xt::xarray<double>::shape_type shape({nx, ny});
    xt::xarray<double> x = xt::linspace<double>(-1, 1, nx);
    xt::xarray<double> y = xt::linspace<double>(-1, 1, ny);
    xt::xarray<double> z(shape);

    for (size_t i=0; i<nx; i++) {
        for (size_t j=0; j<ny; j++) {
            z(i, j) = std::sph_bessel(1, xyToR(x(i), y(j)));
        }
    }

    colorMap->plotData(x, y, z);
}
