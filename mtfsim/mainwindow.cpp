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

    QObject::connect(ui->zSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::loadPlots);
    QObject::connect(ui->apertureSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::loadPlots);
    QObject::connect(ui->zSpinBox, &QDoubleSpinBox::valueChanged, this, &MainWindow::loadPlots);

    this->initPlots();
    this->loadPlots();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initPlots() {
    this->diffractionPlot = new XArrayQCPColorMap(
        ui->leftPlot,
        "x",
        "y",
        "Intensity"
    );
}

void MainWindow::loadPlots() {
    // Number of data points along x and y
    unsigned long nx = 100;
    unsigned long ny = 100;
    xt::xarray<double>::shape_type shape({nx, ny});
    xt::xarray<double> x = xt::linspace<double>(-1, 1, nx);
    xt::xarray<double> y = xt::linspace<double>(-1, 1, ny);
    xt::xarray<double> z(shape);

    Circle c = Circle(ui->apertureSpinBox->value(), nx, ny);    // Aperture in mm
    double lambda = ui->wavelengthSpinBox->value()*1e-6;            // Wavelength in mm

    for (size_t i=0; i<nx; i++) {
        for (size_t j=0; j<ny; j++) {
            z(i, j) = c.intensity(x(i), y(j), ui->zSpinBox->value(), lambda);
        }
    }

    this->diffractionPlot->plotData(x, y, z);
}
