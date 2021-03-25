#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QPixelFormat>

class imageProcessing
{
public:
    imageProcessing() {}

    ~imageProcessing() {}

    QImage * greyScale(QImage * origin) // 灰度处理
    {
        QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
        for(int y = 0; y < newImage->height(); y++)
        {
            QRgb * line = (QRgb *)origin->scanLine(y);
            for(int x = 0; x < newImage->width(); x++)
            {
                int average = (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]))/3; // 每像素点的颜色值为RGB颜色值的均值
                newImage->setPixel(x,y, qRgb(average, average, average));
            }
        }
        return newImage;
    }

    QImage * light(int delta, QImage * origin) // 图像亮度提升
    {
        QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
        QColor oldColor;
        int r,g,b;
        for(int x=0; x < newImage->width(); x++)
        {
            for(int y=0; y < newImage->height(); y++)
            {
                oldColor = QColor(origin->pixel(x,y)); // 亮度提升等价于RGB三个颜色值提高相同的值
                r = oldColor.red() + delta;
                g = oldColor.green() + delta;
                b = oldColor.blue() + delta;
                //we check if the new values are between 0 and 255
                r = qBound(0, r, 255);
                g = qBound(0, g, 255);
                b = qBound(0, b, 255);
                newImage->setPixel(x,y, qRgb(r,g,b));
            }
        }
        return newImage;
    }

    QImage * binaryScale(int threshold, QImage * origin) // 图像二值化处理
    {
        QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
        for(int y = 0; y < newImage->height(); y++)
        {
            QRgb * line = (QRgb *)origin->scanLine(y);
            for(int x = 0; x < newImage->width(); x++)
            {
                int average = (qRed(line[x]) + qGreen(line[x]) + qBlue(line[x]))/3;
                if(average >= threshold) // 若RGB三个颜色值的均值大于阈值，则为黑色，否则为白色
                    newImage->setPixel(x,y, qRgb(255,255,255));
                else
                    newImage->setPixel(x,y, qRgb(0,0,0));
            }
        }
        return newImage;
    }

    QImage * convolutionProcessing(int step, long double coreDouble[3][3], QImage * origin) // 图像卷积化处理
    {
        int core[3][3];
        int element;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
            {
                element = coreDouble[i][j] * 10000;
                core[i][j] = element;
            }

        QImage * newImage = new QImage(origin->width() - 2, origin->height() - 2, QImage::Format_ARGB32);
        for(int y = 0; y < newImage->height(); y++)
        {
            QRgb * lineOne = (QRgb *)origin->scanLine(y);
            QRgb * lineTwo = (QRgb *)origin->scanLine(y + 1);
            QRgb * lineThr = (QRgb *)origin->scanLine(y + 2);
            for(int x = 0; x < newImage->width(); x++) // 3*3卷积核，矩阵对应位置相乘再相加
            {
                int tempR = 0; // 初始化为0
                int tempG = 0;
                int tempB = 0;

                int index;
                index = 0;
                tempR += qRed(lineOne[x])     * core[index][0];
                tempR += qRed(lineOne[x + 1]) * core[index][0 + 1];
                tempR += qRed(lineOne[x + 2]) * core[index][0 + 2];
                tempR += qRed(lineTwo[x])     * core[index][0];
                tempR += qRed(lineTwo[x + 1]) * core[index][0 + 1];
                tempR += qRed(lineTwo[x + 2]) * core[index][0 + 2];
                tempR += qRed(lineThr[x])     * core[index][0];
                tempR += qRed(lineThr[x + 1]) * core[index][0 + 1];
                tempR += qRed(lineThr[x + 2]) * core[index][0 + 2];

                index = 1;
                tempG += qGreen(lineOne[x])     * core[index][0];
                tempG += qGreen(lineOne[x + 1]) * core[index][0 + 1];
                tempG += qGreen(lineOne[x + 2]) * core[index][0 + 2];
                tempG += qGreen(lineTwo[x])     * core[index][0];
                tempG += qGreen(lineTwo[x + 1]) * core[index][0 + 1];
                tempG += qGreen(lineTwo[x + 2]) * core[index][0 + 2];
                tempG += qGreen(lineThr[x])     * core[index][0];
                tempG += qGreen(lineThr[x + 1]) * core[index][0 + 1];
                tempG += qGreen(lineThr[x + 2]) * core[index][0 + 2];

                index = 2;
                tempB += qBlue(lineOne[x])     * core[index][0];
                tempB += qBlue(lineOne[x + 1]) * core[index][0 + 1];
                tempB += qBlue(lineOne[x + 2]) * core[index][0 + 2];
                tempB += qBlue(lineTwo[x])     * core[index][0];
                tempB += qBlue(lineTwo[x + 1]) * core[index][0 + 1];
                tempB += qBlue(lineTwo[x + 2]) * core[index][0 + 2];
                tempB += qBlue(lineThr[x])     * core[index][0];
                tempB += qBlue(lineThr[x + 1]) * core[index][0 + 1];
                tempB += qBlue(lineThr[x + 2]) * core[index][0 + 2];

                int intTempR = tempR / 90000;
                int intTempG = tempG / 90000;
                int intTempB = tempB / 90000;

                int rRgb = qBound(0, intTempR, 255);
                int gRgb = qBound(0, intTempG, 255);
                int bRgb = qBound(0, intTempB, 255);

                newImage->setPixel(x,y, qRgb(rRgb, gRgb, bRgb));
                // newImage->setPixel(x,y, qRgb(0,0,0));
            }
        }
        return newImage;
        // return origin;
    }
};

#endif // IMAGEPROCESSING_H
