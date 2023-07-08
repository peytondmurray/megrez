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

    QObject::connect(ui->leftPlot, &QCustomPlot::mouseMove, this, &MainWindow::leftMouseMoved);
    QObject::connect(ui->rightPlot, &QCustomPlot::mouseMove, this, &MainWindow::rightMouseMoved);
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
    this->transmittancePlot = new XArrayQCPColorMap(
        ui->leftPlot,
        "x",
        "y",
        "Intensity"
    );
    this->diffractionPlot = new XArrayQCPColorMap(
        ui->rightPlot,
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
    xt::xarray<double> intensity(shape);
    xt::xarray<double> transmittance(shape);

    Circle c = Circle(ui->apertureSpinBox->value(), nx, ny);    // Aperture in mm
    double lambda = ui->wavelengthSpinBox->value()*1e-6;            // Wavelength in mm

    for (size_t i=0; i<nx; i++) {
        for (size_t j=0; j<ny; j++) {
            intensity(i, j) = c.intensity(x(i), y(j), ui->zSpinBox->value(), lambda);
            transmittance(i, j) = c.transmittance(x(i), y(j));
        }
    }

    this->diffractionPlot->plotData(x, y, intensity);
    this->transmittancePlot->plotData(x, y, transmittance);
}

void MainWindow::leftMouseMoved(QMouseEvent *event) {
    double x, y, z;


    this->transmittancePlot->pixelsToCoords(
        event->pos().x(),
        event->pos().y(),
        x,
        y
    );
    z = this->transmittancePlot->data()->data(x, y);

    ui->leftPlotMouseCoordsLabel->setText(
        QString("x: %1 y: %2 z: %3").arg(x).arg(y).arg(z)
    );
}

void MainWindow::rightMouseMoved(QMouseEvent *event) {
    double x, y, z;
    this->diffractionPlot->pixelsToCoords(
        event->pos().x(),
        event->pos().y(),
        x,
        y
    );
    z = this->diffractionPlot->data()->data(x, y);

    ui->rightPlotMouseCoordsLabel->setText(
        QString("x: %1 y: %2 z: %3").arg(x).arg(y).arg(z)
    );
}
