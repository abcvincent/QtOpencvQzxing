#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QTime>

//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>

#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp> // for camera
#include <QMessageBox>
#pragma execution_character_set("utf-8")
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void cameraopen();
    //声明函数
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    //QTimer 计时用；
//    IplImage* pFrame;//opencv2方法
//    //申请IplImage类型指针，就是申请内存空间来存放每一帧图像
//    CvCapture *cam;//opencv2方法
//    // 视频获取结构， 用来作为视频获取函数的一个参数


    Mat frame;
    VideoCapture  cap;
};

#endif // MAINWINDOW_H
