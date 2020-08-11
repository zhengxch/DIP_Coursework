#ifndef MORPHOLOGICAL_H
#define MORPHOLOGICAL_H
#include <QImage>

QImage* erosiontionGary(QImage* image, int k);
QImage* erosiontionRGB(QImage* image);
QImage* dilationRGB(QImage* image);
QImage* dilationGary(QImage* image, int k);
QImage* closingMor(QImage* image);
QImage* openingMor(QImage* image);
QImage* sideInner(QImage* image);
QImage* sideOutter(QImage* image);
QImage* sideIO(QImage* image);

#endif // MORPHOLOGICAL_H

