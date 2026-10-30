// SPDX-License-Identifier: GPL-3.0-or-later
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QtMath>
#include <cstdio>

#include "qcustomplot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    const QString versions = QString("Qt compile-time: %1 | Qt runtime: %2 | QCustomPlot: %3")
                                 .arg(QT_VERSION_STR, qVersion(), QCUSTOMPLOT_VERSION_STR);

    QCustomPlot *plot = new QCustomPlot;
    plot->addGraph();
    plot->addGraph();
    plot->graph(0)->setName("sin(x)");
    plot->graph(1)->setName("cos(x)");
    plot->graph(1)->setPen(QPen(Qt::red));

    QVector<double> x(501), s(501), c(501);
    for (int i = 0; i < x.size(); ++i) {
        x[i] = i * 0.02;
        s[i] = qSin(x[i]);
        c[i] = qCos(x[i]);
    }
    plot->graph(0)->setData(x, s);
    plot->graph(1)->setData(x, c);
    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->rescaleAxes();
    plot->legend->setVisible(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    if (app.arguments().contains("--smoke")) {
        plot->resize(640, 480);
        const bool ok = plot->savePng("smoke.png", 640, 480);
        std::printf("%s\nsavePng: %s\n", qPrintable(versions), ok ? "ok" : "FAILED");
        delete plot;
        return ok ? 0 : 1;
    }

    QWidget window;
    window.setWindowTitle("QCustomPlot test - " + QString(qVersion()));
    QVBoxLayout *layout = new QVBoxLayout(&window);
    layout->addWidget(new QLabel(versions));
    layout->addWidget(plot);
    window.resize(800, 600);
    window.show();
    return app.exec();
}
