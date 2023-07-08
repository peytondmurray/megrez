#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xadapt.hpp>
#include "xarrayqcp.h"
#include "qcustomplot.h"
#include "mathutils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initPlots();

public slots:
    void loadPlots();
    void leftMouseMoved(QMouseEvent*);
    void rightMouseMoved(QMouseEvent*);

private:
    Ui::MainWindow *ui;
    XArrayQCPColorMap *transmittancePlot;
    XArrayQCPColorMap *diffractionPlot;
};
#endif // MAINWINDOW_H
