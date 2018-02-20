#include "cvimage.h"

//нициализируйте члены класса из аргументов конструктора, используя список инициализации членов.
//В этом методе применяется прямая инициализация, что более эффективно, чем использование операторов присваивания в теле конструктора.
CVImage::CVImage(int height, int width):height(height), width(width), image( make_unique<double[]>( height * width ))
{
}

//Загрузка с файла
shared_ptr<CVImage> CVImage::fromFile(const QString& fileName)
{
    QImage picture;
    bool isLoaded = picture.load(fileName);
    if(isLoaded)
    {
        qDebug() << "Load image from file: " << fileName;
        return fromQImage(picture);
    }
    else
    {
        qWarning() << "Failed to load image from file: " << fileName;
        return nullptr;
    }
}

//загрузка из qimage
shared_ptr<CVImage> CVImage::fromQImage(const QImage& qimg)
{
    int h =  qimg.height();
    int w = qimg.width();
    shared_ptr<CVImage> result = make_shared<CVImage>(h, w);
    QRgb original;
    double color;
    int gray;

    for(int i=0; i < h; i++)
    {
        for(int j=0; j < w; j++)
        {
            original = qimg.pixel(j,i);
            gray = qGray(original);
            color = intToDouble(gray);
            result->setPixel(i,j, color);
        }
    }

    return result;
}

QImage CVImage::toQImage(){

    QImage qimg = QImage(width, height, QImage::Format_RGB32);
    int color;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            color = doubleToInt(getPixel(i , j));
            if(color > 255)
                color = 255;
            qimg.setPixel(j, i, qRgb(color, color, color) );
        }
    }
    return qimg;
}

bool CVImage::toFile(const QString& fileName){
    QImage image = toQImage();
    return image.save(fileName, "JPEG");
}

double CVImage::setPixel(int i, int j, double value)
{
    if( i < height && j < width && i >= 0 && j >= 0 )
    {
        image[ i * width + j] = value;
        return value;
    }
    else
    {
        qFatal("Index out of the range");
        return -1;
    }
}

double CVImage::getPixel(int i, int j, EdgeMode _mode) const
{
    if(i<height && j<width && i>=0 && j>=0)
    {
        return image[i*width + j];
    }
    else
    {
        switch(_mode)
        {
        case EdgeMode::ZEROS: return 0;
        case EdgeMode::COPY:
            return image[min(max(i,0), height-1)*width + min(max(j,0), width-1)];
        case EdgeMode::MIRROR:
            if(i<0) i = i*(-1) - 1;
            if(j<0) j = j*(-1) - 1;
            if(i>=height) i = height - (i%height) - 1;
            if(j>=width) j = width - (j%width) - 1;
            return image[i*width + j];
        }
    }
    return 0;
}


double CVImage::intToDouble(int val)
{
    return (double)val/255;
}

int CVImage::doubleToInt(double val)
{
    return int(val*255);
}


