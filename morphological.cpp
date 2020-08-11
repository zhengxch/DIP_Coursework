#include "morphological.h"

// 采用二值图算法，定义阈值K，对于灰度大于k的像素认为存在，否则认为不存在， 二值图腐蚀处理

QImage* erosiontionGary(QImage* image, int k)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            int hr = 1;
            int hg = 1;
            int hb = 1;
            Rcolor = QColor(image->pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() < k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hr == 1)
                    {
                        hr = 0;
                    }
                    while (color.green() < k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hg == 1)
                    {
                        hg = 0;
                    }
                    while (color.blue() < k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hb == 1)
                    {
                        hb = 0;
                    }
                }
            }
            if (hr == 0)
            {
                r = 0;
            }
            else
            {
                r = color.red();
            }
            if (hg == 0)
            {
                g = 0;
            }
            else
            {
                g = color.green();
            }
            if (hb == 0)
            {
                b = 0;
            }
            else
            {
                b = color.blue();
            }

            newImage->setPixel(x, y, qRgb(r, g, b));
        }
    }
    return newImage;
}


// 采用最小描述算法，腐蚀处理

QImage* erosiontionRGB(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;

    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            Rcolor = QColor(image->pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    return newImage;
}


// 采用二值图算法，定义阈值K，对于灰度大于k的像素认为存在，否则认为不存在， 二值图膨胀处理

QImage* dilationGary(QImage* image, int k)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            int hr = 1;
            int hg = 1;
            int hb = 1;
            Rcolor = QColor(image->pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() >= k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hr == 1)
                    {
                        hr = 0;
                    }
                    while (color.green() >= k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hg == 1)
                    {
                        hg = 0;
                    }
                    while (color.blue() >= k && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j] && hb == 1)
                    {
                        hb = 0;
                    }
                }
            }
            if (hr == 0)
            {
                r = color.red();
            }
            else
            {
                r = 0;
            }
            if (hg == 0)
            {
                g = color.green();
            }
            else
            {
                g = 0;
            }
            if (hb == 0)
            {
                b = color.blue();
            }
            else
            {
                b = 0;
            }

            newImage->setPixel(x, y, qRgb(r, r, r));
        }
    }
    return newImage;
}

// 采用最大描述算法，膨胀处理

QImage* dilationRGB(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 0,0,0,1,0,0,0 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 1,1,1,1,1,1,1 },
        { 0,1,1,1,1,1,0 },
        { 0,1,1,1,1,1,0 },
        { 0,0,0,1,0,0,0 } };
    int sizeKernel = 7;
    QColor color;
    QColor Rcolor;

    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            Rcolor = QColor(image->pixel(x, y));
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    return newImage;
}

// 二值化的开运算

QImage* openingMor(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    QImage* newImage1 = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 } };
    int sizeKernel = 7;
    QColor color;
    // 腐蚀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    // 膨胀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    delete newImage;
    return newImage1;
}

// 二值化的闭运算

QImage* closingMor(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    QImage* newImage1 = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[7][7] = {
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 },
        { 1,1,1,1,1,1,1 } };
    int sizeKernel = 7;
    QColor color;

    // 膨胀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    // 腐蚀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }


    delete newImage;
    return newImage1;
}



// 提取二值图的内边界
QImage* sideInner(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[3][3] = {
        { 1,1,1 },
        { 1,1,1 },
        { 1,1,1 }
    };
    int sizeKernel = 3;
    QColor color;
    QColor newcolor;
    int r = 0;
    int g = 0;
    int b = 0;
    // 腐蚀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    // end
    for (int y = 0; y<image->height(); y++)
    {
        for (int x = 0; x<image->width(); x++)
        {
            color = QColor(image->pixel(x, y));
            newcolor = QColor(newImage->pixel(x, y));
            if (color.red() != newcolor.red())
            {
                r = 255;
            }
            else
            {
                r = 0;
            }
            if (color.green() != newcolor.green())
            {
                g = 255;
            }
            else
            {
                g = 0;
            }
            if (color.blue() != newcolor.blue())
            {
                b = 255;
            }
            else
            {
                b = 0;
            }
            newImage->setPixel(x, y, qRgb(r, g, b));
        }
    }
    return newImage;
}

// 提取二值图的外边界
QImage* sideOutter(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[3][3] = {
        { 1,1,1 },
        { 1,1,1 },
        { 1,1,1 }
    };
    int sizeKernel = 3;
    QColor color;
    QColor newcolor;
    int r = 0;
    int g = 0;
    int b = 0;
    // 膨胀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    // end
    for (int y = 0; y<image->height(); y++)
    {
        for (int x = 0; x<image->width(); x++)
        {
            color = QColor(image->pixel(x, y));
            newcolor = QColor(newImage->pixel(x, y));
            if (color.red() != newcolor.red())
            {
                r = 255;
            }
            else
            {
                r = 0;
            }
            if (color.green() != newcolor.green())
            {
                g = 255;
            }
            else
            {
                g = 0;
            }
            if (color.blue() != newcolor.blue())
            {
                b = 255;
            }
            else
            {
                b = 0;
            }
            newImage->setPixel(x, y, qRgb(r, g, b));
        }
    }
    return newImage;
}

// 提取双线空心文字
QImage* sideIO(QImage* image)
{
    QImage* newImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    QImage* newImage1 = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    QImage* newImage2 = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    int kernel[3][3] = {
        { 1,1,1 },
        { 1,1,1 },
        { 1,1,1 }
    };
    int sizeKernel = 3;
    QColor color;
    QColor newcolor;
    int r = 0;
    int g = 0;
    int b = 0;
    // 第一次腐蚀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    // 第二次腐蚀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 255;
            int kg = 255;
            int kb = 255;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage->pixel(x + i, y + j));
                    while (color.red() < kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() < kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() < kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }

    // 二次腐蚀相减
    for (int y = 0; y<image->height(); y++)
    {
        for (int x = 0; x<image->width(); x++)
        {
            color = QColor(newImage->pixel(x, y));
            newcolor = QColor(newImage1->pixel(x, y));
            if (color.red() != newcolor.red())
            {
                r = 255;
            }
            else
            {
                r = 0;
            }
            if (color.green() != newcolor.green())
            {
                g = 255;
            }
            else
            {
                g = 0;
            }
            if (color.blue() != newcolor.blue())
            {
                b = 255;
            }
            else
            {
                b = 0;
            }
            newImage->setPixel(x, y, qRgb(r, g, b));
        }
    }

    // 第一次膨胀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(image->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage1->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    /*end*/
    // 第二次膨胀操作
    for (int y = sizeKernel / 2; y < image->height() - sizeKernel / 2; y++)
    {
        for (int x = sizeKernel / 2; x < image->width() - sizeKernel / 2; x++)
        {
            int kr = 0;
            int kg = 0;
            int kb = 0;
            for (int j = -sizeKernel / 2; j <= sizeKernel / 2; j++)
            {
                for (int i = -sizeKernel / 2; i <= sizeKernel / 2; i++)
                {
                    color = QColor(newImage1->pixel(x + i, y + j));
                    while (color.red() > kr && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kr = color.red();
                    }
                    while (color.green() > kg && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kg = color.green();
                    }
                    while (color.blue() > kb && kernel[sizeKernel / 2 + i][sizeKernel / 2 + j])
                    {
                        kb = color.blue();
                    }
                }
            }
            newImage2->setPixel(x, y, qRgb(kr, kg, kb));
        }
    }
    /*end*/
    // 二次膨胀相减
    for (int y = 0; y<image->height(); y++)
    {
        for (int x = 0; x<image->width(); x++)
        {
            color = QColor(newImage1->pixel(x, y));
            newcolor = QColor(newImage2->pixel(x, y));
            if (color.red() != newcolor.red())
            {
                r = 255;
            }
            else
            {
                r = 0;
            }
            if (color.green() != newcolor.green())
            {
                g = 255;
            }
            else
            {
                g = 0;
            }
            if (color.blue() != newcolor.blue())
            {
                b = 255;
            }
            else
            {
                b = 0;
            }
            newImage1->setPixel(x, y, qRgb(r, g, b));
        }
    }

    // 复合提取内外边界
    for (int y = 0; y<image->height(); y++)
    {
        for (int x = 0; x<image->width(); x++)
        {
            color = QColor(newImage1->pixel(x, y));
            newcolor = QColor(newImage->pixel(x, y));
            if (color.red() > newcolor.red())
            {
                r = color.red();
            }
            else
            {
                r = newcolor.red();
            }
            if (color.green() > newcolor.green())
            {
                g = color.green();
            }
            else
            {
                g = newcolor.green();
            }
            if (color.blue() > newcolor.blue())
            {
                b = color.blue();
            }
            else
            {
                b = newcolor.blue();
            }
            newImage->setPixel(x, y, qRgb(r, g, b));
        }
    }
    delete newImage1;
    delete newImage2;
    return newImage;
}
