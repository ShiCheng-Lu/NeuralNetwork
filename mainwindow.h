#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Network;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *);

    void learnThread();

private slots:
  void learn();

private:
    Ui::MainWindow *ui;
    Network *network;
    std::vector<std::vector<QColor>> colors;
    bool learning = false;
    std::thread learningThread;
};
#endif // MAINWINDOW_H
