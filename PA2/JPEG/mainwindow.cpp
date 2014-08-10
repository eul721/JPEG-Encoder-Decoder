/*This is the implementation of GUI, connecting buttons actions to the encoder/decoder functions
 *It also resizes all images FOR DISPLAY to 640x480
 */


#include "mainwindow.h"
#include "GeneratedFiles\ui_mainwindow.h"
#include "EncoderDecoder.h"
#include <QtWidgets\qfiledialog.h>
#include <QtWidgets\qmessagebox.h>


#include <iostream>
#include <math.h>

QString fileName = NULL;
String imgpath;
//QString lastfileName;

EncoderDecoder encoder;
QSize newsize(640,480);









MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);




}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Browsefor_released()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (fileName != NULL){
       imgpath = fileName.toUtf8();

   Mat img_temp = imread(imgpath);
   cvtColor(img_temp,img_original,CV_BGR2RGB);




   QImage *qimgoriginal= new QImage((uchar*)img_original.data,img_original.cols,img_original.rows,img_original.step,QImage::Format_RGB888);
   QImage smalloriginal = qimgoriginal->scaled(newsize,Qt::KeepAspectRatio);


   ui->img_original->setPixmap(QPixmap::fromImage(smalloriginal));

   delete qimgoriginal;}

}



void MainWindow::on_verYCha_clicked()
{
    if(fileName==NULL){
        QMessageBox::information(this,"Error","No image loaded!!");
    }
    else{
    Mat img2_temp = encoder.Encode(imgpath,0);
    cvtColor(img2_temp,img_encoded,CV_BGR2RGB);
    QImage *qimgencoded = new QImage((uchar*)img_encoded.data,img_original.cols,img_original.rows,img_original.step,QImage::Format_RGB888);
    QImage smallencoded = qimgencoded->scaled(newsize,Qt::KeepAspectRatio);
    ui->img_processed->setPixmap(QPixmap::fromImage(smallencoded));

    delete qimgencoded;}
}

void MainWindow::on_verQA_clicked()
{
    if(fileName==NULL){
        QMessageBox::information(this,"Error","No image loaded!!");
    }
    else{
    Mat img2_temp = encoder.Encode(imgpath,1);
    cvtColor(img2_temp,img_encoded,CV_BGR2RGB);
    QImage *qimgencoded = new QImage((uchar*)img_encoded.data,img_original.cols,img_original.rows,img_original.step,QImage::Format_RGB888);
    QImage smallencoded = qimgencoded->scaled(newsize,Qt::KeepAspectRatio);
    ui->img_processed->setPixmap(QPixmap::fromImage(smallencoded));

    delete qimgencoded;}
}

void MainWindow::on_verQB_clicked()
{
    if(fileName==NULL){
        QMessageBox::information(this,"Error","No image loaded!!");
    }
    else{
    Mat img2_temp = encoder.Encode(imgpath,2);
    cvtColor(img2_temp,img_encoded,CV_BGR2RGB);
    QImage *qimgencoded = new QImage((uchar*)img_encoded.data,img_original.cols,img_original.rows,img_original.step,QImage::Format_RGB888);
    QImage smallencoded = qimgencoded->scaled(newsize,Qt::KeepAspectRatio);
    ui->img_processed->setPixmap(QPixmap::fromImage(smallencoded));

    delete qimgencoded;}
}
