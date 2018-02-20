#pragma once
#include <memory>
#include <limits>
#include <QImage>
#include <QtDebug>
using namespace std;

enum class EdgeMode
{
    ZEROS = 1,
    MIRROR = 2,
    COPY = 3
};


class CVImage
{

public:
    CVImage(int height, int width);
    static shared_ptr<CVImage> fromFile(const QString &fileName);
    static shared_ptr<CVImage> fromQImage(const QImage &qimg);
    static double intToDouble(int val);
    static int doubleToInt(double val);
    double setPixel(int i, int j, double value);
    double getPixel(int i, int j, EdgeMode _mode=EdgeMode::COPY) const;
    QImage toQImage();
    bool toFile(const QString& fileName);


private:
    const int height;
    const int width;
    const unique_ptr<double[]> image;
};


