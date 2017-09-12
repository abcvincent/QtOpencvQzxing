#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "QZXing.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

//添加Qzxing.h头文件前确定pro文件中已经添加路径

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    //初始化timer
    //    cam = NULL;//opencv2方法
    //    // 初始化cam

    cap=NULL;

    connect(timer, SIGNAL(timeout()), this, SLOT(cameraopen()));
    // 时间到，读取当前摄像头信息,这个必须加，因为timer需要配合timeout()信号用
    //没有的话会出现错误；
    //另外注意自己有没有野指针，有的话常常会
    //出现Program Files (x86)\SogouInput\7.2.0.2124\程序异常终止,这样的错误

}

MainWindow::~MainWindow()
{
    delete ui;
    //    cvReleaseCapture(&cam);
    //释放内存；
    cap.release();

}

void MainWindow::on_pushButton_clicked()
{

    //    cam = cvCreateCameraCapture(0);//opencv2方法
    //    //打开摄像头，从摄像头中获取视频

    cap.open(0);
//    capture=cv::VideoCapture(0);

    timer->start(33);
    // 开始计时，超时则发出timeout()信号

}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
    // 停止读取数据。
    //    cvReleaseCapture(&cam);//opencv2方法
    //    //释放内存；
    ui->label_video->clear();
    ui->lineEdit->clear();
    cap.release();
}

void MainWindow::cameraopen()
{
    //    pFrame = cvQueryFrame(cam);//opencv2方法
    //    // 从摄像头中抓取并返回每一帧
    cap>>frame;//opencv3方法
    //    QImage image((const uchar*)pFrame->imageData, pFrame->width, pFrame->height,QImage::Format_RGB888);//opencv2方法
    //    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    //    cv::cvtColor(frame,frame,CV_BGR2RGB);
    //    QImage image((const uchar*)frame.data,frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_RGB888);
    QImage image=MatToQImage(frame);
    QZXing *pDecoder = new QZXing(QZXing::DecoderFormat_MAXICODE);
      //Qzxing对象
    QString qrmsg=pDecoder->decodeImage(image);
    //decodeImage是Qzxing解码函数，解码出来的是QString字符体
    if (!qrmsg.isEmpty())
    {
        ui->lineEdit->setText(qrmsg);

        //        //将解码出的文本显示在lineEdit上
        //        QGraphicsScene *scene = new QGraphicsScene;
        //        //创建图片显示方式的容器
        //        scene->addPixmap(QPixmap::fromImage(image));
        //        //装载图片
        //        ui->graphicsView->setScene(scene);
        //        //显示图片，自动添加滚动条
        //        ui->graphicsView->show();
        //        //显示图片

        ui->label_video->setPixmap(QPixmap::fromImage(image));
        timer->stop();
        // 停止读取数据。
        //        cvReleaseCapture(&cam);//opencv2方法
        //        //释放内存；

        cap.release();
    }
    else
    {
        ui->lineEdit->setText("未检测到");
        //显示解码失败
        //        QGraphicsScene *scene = new QGraphicsScene;
        //        //创建图片显示方式的容器
        //        scene->addPixmap(QPixmap::fromImage(image));
        //        //装载图片
        //        ui->graphicsView->setScene(scene);
        //        //显示图片，自动添加滚动条
        //        ui->graphicsView->show();
        //        //显示图片
        ui->label_video->setPixmap(QPixmap::fromImage(image));
        //        ui->label_video->repaint();
    }

//    ui->label_video->setPixmap(QPixmap::fromImage(image));
////    ui->lineEdit->setText(qrmsg);
}


QImage MainWindow::MatToQImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if (mat.type() == CV_8UC4)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        return QImage();
    }
}
