#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "fraunhofer.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set up plots
    ui->leftPlot->addGraph();
    ui->leftPlot->axisRect()->setupFullAxesBox(true);
    ui->rightPlot->addGraph();
    ui->rightPlot->axisRect()->setupFullAxesBox(true);

    QObject::connect(this->zSpinBox, &QDoubleSpinBox::textChanged, this, this->loadPlots);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadPlots(double zval) {
    XArrayQCPColorMap *colorMap = new XArrayQCPColorMap(ui->leftPlot);

    // Number of data points along x and y
    unsigned long nx = 1000;
    unsigned long ny = 1000;
    xt::xarray<double>::shape_type shape({nx, ny});
    xt::xarray<double> x = xt::linspace<double>(-10, 10, nx);
    xt::xarray<double> y = xt::linspace<double>(-10, 10, ny);
    xt::xarray<double> z(shape);

    Circle c = Circle(152.0, 1000, 1000); // Aperture in mm
    double lambda = 532e-6; // Wavelength in mm

    for (size_t i=0; i<nx; i++) {
        for (size_t j=0; j<ny; j++) {
            z(i, j) = c.intensity(x(i), y(j), zval, lambda);
        }
    }

    colorMap->plotData(x, y, z);
}
