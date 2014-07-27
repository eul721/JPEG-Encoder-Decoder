#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define PI 3.14159265
#define SQRT2 1.41421356237


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:


private slots:
    void on_Browsefor_released();


    void on_verYCha_clicked();

    void on_verQA_clicked();

    void on_verQB_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat img_original;
    cv::Mat img_encoded;

    QImage qimgoriginal;
    QImage qimgencoded;

    //QString* testString;

    //QPushButton *YChannel;




};

#endif // MAINWINDOW_H
