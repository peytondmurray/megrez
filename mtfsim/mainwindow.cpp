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
        "Transmittance",
        -1,
        1,
        -1,
        1
    );
    this->diffractionPlot = new XArrayQCPColorMap(
        ui->rightPlot,
        "x",
        "y",
        "Intensity",
        -1,
        1,
        -1,
        1
    );
}

void MainWindow::loadPlots() {
    unsigned long nx = 100;
    unsigned long ny = 100;

    Circle c = Circle(ui->apertureSpinBox->value(), nx, ny);    // Aperture in mm
    double lambda = ui->wavelengthSpinBox->value()*1e-6;            // Wavelength in mm
    double zVal = ui->zSpinBox->value();

    this->diffractionPlot->plotData(
        [lambda, &c, zVal](double x, double y) -> double {
            return c.intensity(x, y, zVal, lambda);
        }
    );
    this->transmittancePlot->plotData(
        [&c](double x, double y) -> double {
            return c.transmittance(x, y);
        }
    );
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
        QString("x: %1 y: %2 z: %3").arg(x, 6, 'g', 3).arg(y, 6, 'g', 3).arg(z, 6, 'g', 3)
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
        QString("x: %1 y: %2 z: %3").arg(x, 6, 'g', 3).arg(y, 6, 'g', 3).arg(z, 6, 'g', 3)
    );
}
