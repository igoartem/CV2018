#include <QCoreApplication>
#include "cvimage.h"

int main(int argc, char *argv[])
{
    QString fileNameSova = "D:\\!labs\\tests\\1\\sova.JPG";
    QString resultFileNameSova = "D:\\!labs\\tests\\result1\\sovaGray.JPG";

    shared_ptr<CVImage> test = CVImage::fromFile(fileNameSova);
    test->toFile(resultFileNameSova);

    return 0;
}
