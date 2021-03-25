#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_exit_clicked();

    void on_pushButton_clicked();

    void on_pushButton_read_Image_clicked();

    void on_label_img_linkActivated(const QString &link);

    void on_pushButton_clear_Image_clicked();

    void on_label_time_linkActivated(const QString &link);

    void on_pushButton_endTimer_clicked();

    void on_pushButton_startTimer_clicked();

    void on_pushButton_matrix_clicked();

    void on_pushButton_testTimer_clicked();

    void on_label_img_2_linkActivated(const QString &link);

    void on_pushButton_userMatrix_clicked();

    void on_pushButton_clearMatrix_clicked();

    void on_pushButton_pixel_clicked();

    void on_pushButton_Grayscale_clicked();

    void on_pushButton_Binary_clicked();

    void on_pushButton_Light_clicked();

    void on_pushButton_Convolution_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
