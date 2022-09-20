#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "data.h"
#include "network.h"
#include <QPainter>

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    network = new Network(vector<int>{2, 3, 2});

    connect(ui->learn, &QPushButton::released, this, &MainWindow::learn);
    connect(ui->draw, &QPushButton::released, this, &MainWindow::mydraw);

    learningThread = std::thread{&MainWindow::learnThread, this};
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (int x = 0; x < colors.size(); ++x) {
        for (int y = 0; y < colors[0].size(); ++y) {
            painter.setPen(colors[x][y]);
            painter.drawPoint(x + 20, y + 120);
        }
    }

    for (auto& point : dataset) {
        painter.setPen(qRgb((1 - point.expected) * 255, point.expected * 255, 0));
        int x = int(point.inputs[0] * 500) + 20;
        int y = int(point.inputs[1] * 500) + 120;
        painter.drawPoint(x - 1, y);
        painter.drawPoint(x + 1, y);
        painter.drawPoint(x, y - 1);
        painter.drawPoint(x, y + 1);
        painter.drawPoint(x, y);
    }

    painter.end();
}

void MainWindow::learnThread() {
    int counter = 100;
    while (true) {
        while (learning) {
            network->learn();
            if (counter == 100) {
                mydraw();
                counter = 0;
            }
            counter++;
        }
        this_thread::yield();
    }
}

void MainWindow::learn() {
    learning = !learning;
}

void MainWindow::mydraw() {
    // threading, prevent fuzzy output
    bool originalLearningStatus = learning;
    learning = false;

    colors = network->visualize();
    update();
    network->print();

    // restart learning if enabled before
    learning = originalLearningStatus;
}

MainWindow::~MainWindow() {
    delete ui;
    delete network;
}
