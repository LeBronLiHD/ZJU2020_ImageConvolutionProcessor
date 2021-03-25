#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox> // 弹窗
#include <QFileDialog> // 文件打开
#include <QPixmap>
#include <QImage>
#include <QWidget>
#include <QFont>
#include <QString>

#include "timer.h"
#include <QDebug>
#include <QElapsedTimer>

#include "randommatrix.h"

#include <QInputDialog>

#include "imageprocessing.h"

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

Timer_Convolution Obj; // 计时类的对象Obj

int startTimerCounting = 0; // 判断是否可以开始计时
int endTimerCounting = 1; // 判断是否可以停止计时
int editMatrix = 0; // 判断是否可以编辑卷积核
int alreadyConvolution = 0; // 判断是否可以开始卷积运算

int saveGrayImageName = 0; // 灰度处理的图像命名编号
int saveBinaryImageName = 0; // 二值化处理的图像命名便号
int saveLightImageName = 0; // 亮度提升图像处理的命名编号
int saveConvolutionImageName = 0; // 卷积处理的图像的命名编号

QString filename;
// 图片读取地址

long double matrixConvolution[3][3]; // 卷积核，声明为全局变量

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_exit->setStyleSheet("color : red"); // set button "Exit" red
    QString BackImageStringInit = "F:/QT Projects/Timer_One_Qt/null.png"; // 默认背景图片null的绝对路径
    QPixmap BackImageInit(BackImageStringInit);
    ui->label_img->setScaledContents(true); // 允许尺寸被修改
    ui->label_img->setPixmap(BackImageInit.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_img_2->setScaledContents(true); // 允许尺寸被修改
    ui->label_img_2->setPixmap(BackImageInit.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // 使图片适应label的尺寸
    QFont timeFont("Microsoft YaHei",10,75); // 字体：Microsoft YaHei  字号：10  加粗系数：75
    QFont matrixFont("Geogria",10,75); // 字体：Geogria  字号：10  加粗系数：75
    ui->label_time->setFont(timeFont); // 修改label内文本的字体格式
    ui->label_timerDocu->setFont(timeFont); // 修改字体
    ui->label_timerDocu->setText(" N U L L");
    ui->label_oriImage->setFont(timeFont); // 修改字体
    ui->label_finalImage->setFont(timeFont); // 修改字体
    ui->label_conMatrix->setFont(matrixFont); // 修改字体
    ui->label_conMatrix->setText("Convolution Core");

    ui->label_matTest->setFont(matrixFont); // 修改字体
    ui->label_matTest_2->setFont(matrixFont);
    ui->label_matTest_3->setFont(matrixFont);
    ui->label_matTest_4->setFont(matrixFont);
    ui->label_matTest_5->setFont(matrixFont);
    ui->label_matTest_6->setFont(matrixFont);
    ui->label_matTest_7->setFont(matrixFont);
    ui->label_matTest_8->setFont(matrixFont);
    ui->label_matTest_9->setFont(matrixFont);

    ui->label_matTest->setText("NULL"); // 默认字体为NULL
    ui->label_matTest_2->setText("NULL");
    ui->label_matTest_3->setText("NULL");
    ui->label_matTest_4->setText("NULL");
    ui->label_matTest_5->setText("NULL");
    ui->label_matTest_6->setText("NULL");
    ui->label_matTest_7->setText("NULL");
    ui->label_matTest_8->setText("NULL");
    ui->label_matTest_9->setText("NULL");

    ui->label_char->setFont(timeFont); // 修改字体

    ui->label_width->setFont(matrixFont); // 修改字体
    ui->label_length->setFont(matrixFont); // 修改字体
    ui->label_width->setText("NULL");
    ui->label_length->setText("NULL");

    // ui->pushButton_matrix->setFont(matrixFont);
    // ui->pushButton_userMatrix->setFont(matrixFont);
    // ui->pushButton_clearMatrix->setFont(matrixFont);
    ui->pushButton_matrix->setText(" Random\n3*3 Matrix");
    ui->pushButton_userMatrix->setText("Customize\n3*3 Matrix");
    ui->pushButton_clearMatrix->setText(" Clear  \n3*3 Matrix");

    QFont ConvolutionBold("SimSun",9,75);
    ui->pushButton_Convolution->setFont(ConvolutionBold); // 加粗

    ui->label_timeConvolution->setFont(timeFont);
    ui->label_timerDocuConvolution->setFont(timeFont);
    ui->label_timerDocuConvolution->setText(" N U L L");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    if (!(QMessageBox::information(this,tr("系统提示"),tr("\n确认离开？\n"),tr("Yes"),tr("No"))))
     {
        QMessageBox::about(this,tr("系统提示"),tr("\n欢迎再来哦 ^_^\n"));
        this->close();
     }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::about(this,
                       tr("人员信息"),
                       tr("\n姓名：李浩东\n\n"
                          "学号：3190104890\n\n"
                          "选题：第一题\n\n"
                          "基于：Qt Creator 5.9.0\n\n"
                          "计时：计时器类在timer.h文件\n\n"
                          "卷积：3*3卷积核，可随机可自定义\n\n"
                          "日期：2021年1月2日~2020年1月3日\n"));
}

void MainWindow::on_pushButton_read_Image_clicked()
{
    if(!(filename.isEmpty()))
    {
        QMessageBox::information(this,tr("系统提示"),tr("图片已存在，无法读取！"));
        return;
    }
    // QString filename; 全局变量
    filename = QFileDialog::getOpenFileName(this,
                                            tr("选择图像"),
                                            "",
                                            tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("系统提示"),tr("打开图像失败!"));
        return;
    }
    else
    {
        QPixmap MyImage(filename);
        if(MyImage.isNull()) // 加载图像失败
        {
            QMessageBox::information(this,tr("系统提示"),tr("打开图像失败!"));
            return;
        }
        else
        {
            // 拉伸图片
            ui->label_img->setScaledContents(true);
            ui->label_img->setPixmap(MyImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            // ui->label_img_2->setScaledContents(true);
            // ui->label_img_2->setPixmap(MyImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void MainWindow::on_label_img_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_clear_Image_clicked()
{
    QString BackImageString = "F:/QT Projects/Timer_One_Qt/null.png";
    QPixmap BackImage(BackImageString);
    ui->label_img->setScaledContents(true); // 允许拉伸图像
    ui->label_img->setPixmap(BackImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_img_2->setScaledContents(true);
    ui->label_img_2->setPixmap(BackImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    filename.clear();
    ui->label_width->setText("NULL");
    ui->label_length->setText("NULL");
}

void MainWindow::on_label_time_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_startTimer_clicked()
{
    if(!startTimerCounting)
    {
        startTimerCounting = 1;
        endTimerCounting = 0;
        ui->label_timerDocu->setText(" Timer working...");
        Obj.Refresh(); // 归零
    }
    else
        QMessageBox::information(this,tr("系统提示"),tr("计时器工作中，无法操作！"));
    return;
}

void MainWindow::on_pushButton_endTimer_clicked()
{
    if(!endTimerCounting)
    {
        endTimerCounting = 1;
        startTimerCounting = 0;
        long double durationCount = Obj.Duration(); // 经过的时间
        QString trDurationCount = QString::number(durationCount, 'f', 6);
        ui->label_timerDocu->setText(" " + trDurationCount + " ms");
        QString trMessage = "经过时间: " + trDurationCount + " ms";
        QMessageBox::information(this,tr("系统提示"),trMessage);
    }
    else
        QMessageBox::information(this,tr("系统提示"),tr("计时器不在工作，操作无效！"));
    ui->label_timerDocu->setText(" N U L L");
}

void MainWindow::on_pushButton_matrix_clicked()
{
    if(editMatrix)
    {
        QMessageBox::information(this,tr("系统提示"),tr("卷积核已存在，无法编辑！"));
        return;
    }
    editMatrix = 1;

    RandomMatrixConvolution Mat; // 卷积类的对象Mat

    long double test = Mat.generatorRandomDouble(); // 生成随机卷积核
    QString testString = QString::number(test,'f',4); // 单精度浮点型数据，保留四位小数
    ui->label_matTest->setText(testString);
    matrixConvolution[0][0] = test;

    long double test_2 = Mat.generatorRandomDouble();
    QString testString_2 = QString::number(test_2,'f',4);
    ui->label_matTest_2->setText(testString_2);
    matrixConvolution[0][1] = test_2;

    long double test_3 = Mat.generatorRandomDouble();
    QString testString_3 = QString::number(test_3,'f',4);
    ui->label_matTest_3->setText(testString_3);
    matrixConvolution[0][2] = test_3;

    long double test_4 = Mat.generatorRandomDouble();
    QString testString_4 = QString::number(test_4,'f',4);
    ui->label_matTest_4->setText(testString_4);
    matrixConvolution[1][0] = test_4;

    long double test_5 = Mat.generatorRandomDouble();
    QString testString_5 = QString::number(test_5,'f',4);
    ui->label_matTest_5->setText(testString_5);
    matrixConvolution[1][1] = test_5;

    long double test_6 = Mat.generatorRandomDouble();
    QString testString_6 = QString::number(test_6,'f',4);
    ui->label_matTest_6->setText(testString_6);
    matrixConvolution[1][2] = test_6;

    long double test_7 = Mat.generatorRandomDouble();
    QString testString_7 = QString::number(test_7,'f',4);
    ui->label_matTest_7->setText(testString_7);
    matrixConvolution[2][0] = test_7;

    long double test_8 = Mat.generatorRandomDouble();
    QString testString_8 = QString::number(test_8,'f',4);
    ui->label_matTest_8->setText(testString_8);
    matrixConvolution[2][1] = test_8;

    long double test_9 = Mat.generatorRandomDouble();
    QString testString_9 = QString::number(test_9,'f',4);
    ui->label_matTest_9->setText(testString_9);
    matrixConvolution[2][2] = test_9;

    alreadyConvolution = 1;
}

void MainWindow::on_pushButton_testTimer_clicked()
{
    if (QMessageBox::information(this,tr("系统提示"),tr("\n开始测试？\n"),tr("Yes"),tr("No")))
        return;
    if(!startTimerCounting)
    {
        startTimerCounting = 1;
        endTimerCounting = 0;
        ui->label_timerDocu->setText(" Timer working...");
        Obj.Refresh();
    }
    else
    {
        QMessageBox::information(this,tr("系统提示"),tr("计时器工作中，无法操作！"));
        return;
    }

    QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("系统提示"),tr("\n测试中...\n\n2秒钟后弹窗自动关闭...\n"));
    QTimer::singleShot(1990,box,SLOT(accept()));
    // 也可将accept改为close
    // 此方法精度较低，误差较大，故用1990代替2000
    box->exec();
    // or: box->show();

    // 2秒延时测试计时器功能
    // or: sleep_for(seconds(2));
    //     使用sleep_for函数测试计时器功能
    // or: QElapsedTimer Test;
    //     Test.start();
    //     while(Test.elapsed()<2000);
    // or: while (Obj.Duration() < 2000)
    //     {...}
    if(!endTimerCounting)
    {
        endTimerCounting = 1;
        startTimerCounting = 0;
        long double durationCount = Obj.Duration();
        QString trDurationCount = QString::number(durationCount, 'f', 6);
        ui->label_timerDocu->setText(" " + trDurationCount + " ms");
        QString trMessage = "经过时间: " + trDurationCount + " ms";
        QMessageBox::information(this,tr("系统提示"),trMessage);
    }
    else
        QMessageBox::information(this,tr("系统提示"),tr("计时器不在工作，操作无效！"));
    ui->label_timerDocu->setText(" N U L L");
    return;
}

void MainWindow::on_label_img_2_linkActivated(const QString &link)
{

}

void MainWindow::on_pushButton_userMatrix_clicked()
{
    if(editMatrix)
    {
        QMessageBox::information(this,tr("系统提示"),tr("卷积核已存在，无法编辑！"));
        return;
    }
    editMatrix = 1;

    long double res_1;
    // 生成自定义卷积核
    res_1 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [0][0]"),1.0000,0,2,4);
    // 初始值： 1.0000
    // 范围： 0~2
    // 小数位数： 4
    QString resString_1 = QString::number(res_1,'f',4);
    ui->label_matTest->setText(resString_1);
    matrixConvolution[0][0] = res_1;

    long double res_2;
    res_2 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [0][1]"),1.0000,0,2,4);
    QString resString_2 = QString::number(res_2,'f',4);
    ui->label_matTest_2->setText(resString_2);
    matrixConvolution[0][1] = res_2;

    long double res_3;
    res_3 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [0][2]"),1.0000,0,2,4);
    QString resString_3 = QString::number(res_3,'f',4);
    ui->label_matTest_3->setText(resString_3);
    matrixConvolution[0][2] = res_3;

    long double res_4;
    res_4 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [1][0]"),1.0000,0,2,4);
    QString resString_4 = QString::number(res_4,'f',4);
    ui->label_matTest_4->setText(resString_4);
    matrixConvolution[1][0] = res_4;

    long double res_5;
    res_5 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [1][1]"),1.0000,0,2,4);
    QString resString_5 = QString::number(res_5,'f',4);
    ui->label_matTest_5->setText(resString_5);
    matrixConvolution[1][1] = res_5;

    long double res_6;
    res_6 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [1][2]"),1.0000,0,2,4);
    QString resString_6 = QString::number(res_6,'f',4);
    ui->label_matTest_6->setText(resString_6);
    matrixConvolution[1][2] = res_6;

    long double res_7;
    res_7 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [2][0]"),1.0000,0,2,4);
    QString resString_7 = QString::number(res_7,'f',4);
    ui->label_matTest_7->setText(resString_7);
    matrixConvolution[2][0] = res_7;

    long double res_8;
    res_8 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [2][1]"),1.0000,0,2,4);
    QString resString_8 = QString::number(res_8,'f',4);
    ui->label_matTest_8->setText(resString_8);
    matrixConvolution[2][1] = res_8;

    long double res_9;
    res_9 = QInputDialog::getDouble(this, tr("自定义卷积核"),tr("元素位置： [2][2]"),1.0000,0,2,4);
    QString resString_9 = QString::number(res_9,'f',4);
    ui->label_matTest_9->setText(resString_9);
    matrixConvolution[2][2] = res_9;

    alreadyConvolution = 1;
}

void MainWindow::on_pushButton_clearMatrix_clicked()
{
    ui->label_matTest->setText("NULL");
    ui->label_matTest_2->setText("NULL");
    ui->label_matTest_3->setText("NULL");
    ui->label_matTest_4->setText("NULL");
    ui->label_matTest_5->setText("NULL");
    ui->label_matTest_6->setText("NULL");
    ui->label_matTest_7->setText("NULL");
    ui->label_matTest_8->setText("NULL");
    ui->label_matTest_9->setText("NULL");

    editMatrix = 0;
    alreadyConvolution = 0;
}

void MainWindow::on_pushButton_pixel_clicked()
{
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("系统提示"),tr("图片未载入，分析无效！"));
        return;
    }
    QPixmap AnalysisImage(filename);
    long double wid = AnalysisImage.size().rwidth();
    long double len = AnalysisImage.size().rheight();
    QString widStr = QString::number(wid,'f',0);
    QString lenStr = QString::number(len,'f',0);
    ui->label_width->setText(widStr);
    ui->label_length->setText(lenStr);
}

void MainWindow::on_pushButton_Grayscale_clicked()
{
    // 图像灰度处理
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("系统提示"),tr("图片未载入，操作无效！"));
        return;
    }
    QImage image;
    image.load(filename); // 加载图片
    imageProcessing imgObj; // 图像处理类的对象imgObj
    QImage * imgRes = imgObj.greyScale(&image); // 灰度处理

    saveGrayImageName++;
    QString pathSave = "F:/QT Projects/Timer_One_Qt/imgRes/Gray_" + QString::number(saveGrayImageName,'f',0) + ".jpg";
    imgRes->save(pathSave); // 保存图片
    QString reReadPath = pathSave;

    QPixmap reReadImage(reReadPath); // 重新加载图片并显示
    ui->label_img_2->setScaledContents(true);
    ui->label_img_2->setPixmap(reReadImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QMessageBox::information(this,tr("系统提示"),tr("图像灰度处理完毕！\n（已保存imgRes文件夹）"));
}

void MainWindow::on_pushButton_Binary_clicked()
{
    // 图像二值化处理
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("系统提示"),tr("图片未载入，操作无效！"));
        return;
    }
    long double threshold; // 二值化阈值
    threshold = QInputDialog::getDouble(this, tr("系统提示"),tr("请输入二值化阈值（0~255）"),125.50,0,255,2);
    QImage image;
    image.load(filename);
    imageProcessing imgObj_2;
    QImage * imgRes = imgObj_2.binaryScale(threshold,&image);

    saveBinaryImageName++;
    QString pathSave = "F:/QT Projects/Timer_One_Qt/imgRes/Binary_" + QString::number(saveBinaryImageName,'f',0) + ".jpg";
    imgRes->save(pathSave); // 保存图片
    QString reReadPath = pathSave;

    QPixmap reReadImage(reReadPath); // 显示图片
    ui->label_img_2->setScaledContents(true);
    ui->label_img_2->setPixmap(reReadImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QMessageBox::information(this,tr("系统提示"),tr("图像二值化处理完毕！\n（已保存imgRes文件夹）"));
}

void MainWindow::on_pushButton_Light_clicked()
{
    // 提高图像亮度
    if(filename.isEmpty())
    {
        QMessageBox::information(this,tr("系统提示"),tr("图片未载入，操作无效！"));
        return;
    }
    long double delta;
    delta = QInputDialog::getDouble(this, tr("系统提示"),tr("亮度提升系数（0~255）"),30.00,0,255,2);
    QImage image;
    image.load(filename);
    imageProcessing imgObj_3;
    QImage * imgRes = imgObj_3.light(delta,&image);

    saveLightImageName++;
    QString pathSave = "F:/QT Projects/Timer_One_Qt/imgRes/Light_" + QString::number(saveLightImageName,'f',0) + ".jpg";
    imgRes->save(pathSave);
    QString reReadPath = pathSave;

    QPixmap reReadImage(reReadPath);
    ui->label_img_2->setScaledContents(true);
    ui->label_img_2->setPixmap(reReadImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QMessageBox::information(this,tr("系统提示"),tr("提高图像亮度完毕！\n（已保存imgRes文件夹）"));
}

void MainWindow::on_pushButton_Convolution_clicked()
{
    // 卷积运算
    if(filename.isEmpty() || (!alreadyConvolution))
    {
        if(filename.isEmpty() && alreadyConvolution)
            QMessageBox::information(this,tr("系统提示"),tr("图片未载入，操作无效！"));
        else if ((!filename.isEmpty()) && (!alreadyConvolution))
        {
            QMessageBox::information(this,tr("系统提示"),tr("卷积核未编辑，操作无效！"));
        }
        else
            QMessageBox::information(this,tr("系统提示"),tr("\n图片未载入，卷积核未编辑，\n\n操作无效！\n"));
        return;
    }

    int step = 1; // 设置步长为1
    QMessageBox::information(this,tr("系统提示"),tr("\n卷积运算步长: step = 1\n\n按下“OK”按钮开始卷积运算并计时。\n"));

    ui->label_timerDocuConvolution->setText(" Timer working...");
    ui->label_timerDocuConvolution->repaint(); // 刷新，显示setText内容
    Timer_Convolution ObjCon;
    ObjCon.Refresh(); // 开始计时

    QImage image;
    image.load(filename);
    imageProcessing imgObj_4;
    QImage * imgRes = imgObj_4.convolutionProcessing(step, matrixConvolution, &image); // 卷积处理

    saveConvolutionImageName++;
    QString pathSave = "F:/QT Projects/Timer_One_Qt/imgRes/Convolution_" + QString::number(saveConvolutionImageName,'f',0) + ".jpg";
    imgRes->save(pathSave); // 保存图片
    QString reReadPath = pathSave;

    QPixmap reReadImage(reReadPath); // 显示处理后图片
    ui->label_img_2->setScaledContents(true);
    ui->label_img_2->setPixmap(reReadImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    long double durationCount = ObjCon.Duration(); // 记录经过的时间
    QString trDurationCount = QString::number(durationCount, 'f', 6);
    ui->label_timerDocuConvolution->setText(" " + trDurationCount + " ms");
    QString trMessage = "卷积运算完毕！\n（已保存imgRes文件夹）\n\n卷积运算用时: " + trDurationCount + " ms";
    QMessageBox::information(this,tr("系统提示"),trMessage);
    ui->label_timerDocuConvolution->setText(" N U L L");
}

/*
 * The inferior stopped because it received a signal from the operating system.
 * Signal name : SIGSEGV
 * Signal meaning : Segmentation fault
 * 野指针错误
 * 2021.1.3   21:01
 */
