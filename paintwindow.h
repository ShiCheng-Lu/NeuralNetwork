#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QDebug>

const int loop = 25;
const int windowWidth = 400;
const int windowHeight = 300;

class PaintWindow : public QWidget {
    void paintEvent(QPaintEvent*) {
        for (int i = 0; i < ::loop; ++i) {
            QPainter painter(this);
            for (int x = 0; x < width(); ++x) {
                for (int y = 0; y < height(); ++y) {
                    const QColor color(static_cast<QRgb>(i+x+y));
                    painter.setPen(color);
                    painter.drawPoint(x, y);
                }
            }
        }
    }

    void draw(int x, int y, QColor color) {
        painter.
    }
};

#endif // PAINTWINDOW_H
