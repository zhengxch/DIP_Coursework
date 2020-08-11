#include "imageprocess.h"

// 填充0
void paddingZeros(const float *r, const float *g, const float *b,
                   const int width, const int height,
                   const int half_pad_width, const int half_pad_height,
                   float *nr, float *ng, float *nb)
{
    int nw = width + 2*half_pad_width;
    int nh = height + 2*half_pad_height;
    //先全部赋为0
    memset(nr, 0, nh*nw*sizeof(float));
    memset(ng, 0, nh*nw*sizeof(float));
    memset(nb, 0, nh*nw*sizeof(float));

    for (int j=half_pad_height; j<nh-half_pad_height; j++) {
        // 把原图片分通道按行赋值给新图片，完成0边的填充
        memcpy(nr+j*nw+half_pad_width, r+(j-half_pad_height)*width, width*sizeof(float));
        memcpy(ng+j*nw+half_pad_width, g+(j-half_pad_height)*width, width*sizeof(float));
        memcpy(nb+j*nw+half_pad_width, b+(j-half_pad_height)*width, width*sizeof(float));
    }
}

// 重载函数，分离图像颜色通道，存放到多个一维float数组中
void splitImageChannel(QImage &image, float *r, float *g, float *b)
{
    int width = image.width();
    int height = image.height();
    int count = 0;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = image.pixel(i, j);
            r[count] = qRed(pixel);
            g[count] = qGreen(pixel);
            b[count] = qBlue(pixel);
            count++;
        }
    }
}

// 重载函数，分离图像颜色通道，存放到多维float数组
void splitImageChannel(QImage &image, float *rgb)
{
    int width = image.width();
    int height = image.height();
    int count = 0;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = image.pixel(i, j);
            rgb[j*3*width+3*i] = (float)qRed(pixel);
            rgb[j*3*width+3*i+1] = (float)qGreen(pixel);
            rgb[j*3*width+3*i+2] = (float)qBlue(pixel);
            count++;
        }
    }
}

// 重载函数，分离图像颜色通道，存放到多个一维unsigned_char数组
void splitImageChannel(QImage &image, uchar *r, uchar *g, uchar *b)
{
    int width = image.width();
    int height = image.height();
    int count = 0;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = image.pixel(i, j);
            r[count] = qRed(pixel);
            g[count] = qGreen(pixel);
            b[count] = qBlue(pixel);
            count++;
        }
    }
}

// 重载函数，分离图像颜色通道，存放到多维unsigned_char数组
void splitImageChannel(QImage &image, uchar *rgb)
{
    int width = image.width();
    int height = image.height();
    int count = 0;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = image.pixel(i, j);
            rgb[j*3*width+3*i] = (uchar)qRed(pixel);
            rgb[j*3*width+3*i+1] = (uchar)qGreen(pixel);
            rgb[j*3*width+3*i+2] = (uchar)qBlue(pixel);
            count++;
        }
    }
}

// 重载函数，完成颜色通道拼接(concatenate)，组合成qRgb的一个实例，再设置为image的一个像素，输入为多个一维float数组
void concatenateImageChannel(float *r, float *g, float *b, int w, int h, QImage &image)
{
    image = QImage(w, h, QImage::Format_RGB888);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            QRgb pixel = qRgb((int)(*r), (int)(*g), (int)(*b));
            image.setPixel(i, j, pixel);
        }
    }
}

// 重载函数，完成颜色通道拼接(concatenate)，组合成qRgb的一个实例，再设置为image的一个像素，输入为多维float数组
void concatenateImageChannel(float *rgb, int w, int h, QImage &image)
{
    image = QImage(w, h, QImage::Format_RGB888);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            int r = (int)rgb[j*3*w+3*i];
            int g = (int)rgb[j*3*w+3*i+1];
            int b = (int)rgb[j*3*w+3*i+2];
            QRgb pixel = qRgb(r, g, b);
            image.setPixel(i, j, pixel);
        }
    }
}

// 重载函数，完成颜色通道拼接(concatenate)，组合成qRgb的一个实例，再设置为image的一个像素，输入为多个一维unsigned_char数组
void concatenateImageChannel(uchar *r, uchar *g, uchar *b, int w, int h, QImage &image)
{
    image = QImage(w, h, QImage::Format_RGB888);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            QRgb pixel = qRgb((int)(*r), (int)(*g), (int)(*b));
            image.setPixel(i, j, pixel);
        }
    }
}

// 重载函数，完成颜色通道拼接(concatenate)，组合成qRgb的一个实例，再设置为image的一个像素，输入为多维unsigned_char数组
void concatenateImageChannel(uchar *rgb, int w, int h, QImage &image)
{
    image = QImage(w, h, QImage::Format_RGB888);
    for (int j=0; j<h; j++) {
        for (int i=0; i<w; i++) {
            int r = (int)rgb[j*3*w+3*i];
            int g = (int)rgb[j*3*w+3*i+1];
            int b = (int)rgb[j*3*w+3*i+2];
            QRgb pixel = qRgb(r, g, b);
            image.setPixel(i, j, pixel);
        }
    }
}

// 颜色空间转换,RGB转换到YUV
void rgb2ycrcb(uchar *r, uchar *g, uchar *b, int size, float *y, float *cr, float *cb)
{
    for (int i=0; i<size; i++)
    {
        y[i] = 0.256789 * r[i] + 0.504129 * g[i] + 0.097906 * b[i] + 16;
        cb[i] = -0.148223 * r[i] - 0.290992 * g[i] + 0.439215 * b[i] + 128;
        cr[i] = 0.439215 * r[i] - 0.367789 * g[i] - 0.071426 * b[i] + 128;
    }
}

// 颜色空间转换，YUV转换到RGB
void ycrcb2rgb(float *y, float *cr, float *cb, int size, uchar *r, uchar *g, uchar *b)
{
    for (int i=0; i<size; i++)
    {
        r[i] = 1.164383 * (y[i]-16) + 1.596027 * (cr[i]-128);
        g[i] = 1.164383 * (y[i]-16) - 0.391762 * (cb[i]-128)- 0.812969 * (cr[i]-128);
        b[i] = 1.164383 * (y[i]-16) + 2.017230 * (cb[i]-128);
    }
}

// 整图变换，完成通道分割，颜色空间转换，由qimage生成y,cr,cb三个数组
void qimage2ycrcb(QImage image, float *y, float *cr, float *cb)
{
    int pixel_num = image.width()*image.height();
    // obtain image channels
    uchar *channels = new uchar[pixel_num*3];
    uchar *r = channels;
    uchar *g = channels+pixel_num;
    uchar *b = channels+2*pixel_num;
    splitImageChannel(image, r, g, b);

    // rgb to ycrcb
    rgb2ycrcb(r, g, b, pixel_num, y, cr, cb);

    delete [] channels;
}

// 生成新图，由y，cb，cr三个数组进行颜色空间转换，合成像素实例并拼接成图
void ycrcb2qimage(float *y, float *cr, float *cb, int width, int height, QImage &image)
{
    int pixel_num = width*height;

    uchar *channels = new uchar[pixel_num*3];
    uchar *r = channels;
    uchar *g = channels+pixel_num;
    uchar *b = channels+2*pixel_num;

    // ycrcb to rgb
    ycrcb2rgb(y, cr, cb, pixel_num, r, g, b);

    // update image
    int count = 0;
    image = QImage(width, height, QImage::Format_RGB888);
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            int nr = r[count];
            int ng = g[count];
            int nb = b[count];
            count++;
            image.setPixel(i, j, qRgb(nr,ng,nb));
        }
    }
    delete [] channels;
}

// 计算直方图
QImage calculateHistogram(QImage &image, ImageChannel channel)
{
    // 获取灰度图
    QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);
    int width = grayImage.width();
    int height = grayImage.height();
    uchar *r = new uchar[width*height];
    uchar *g = new uchar[width*height];
    uchar *b = new uchar[width*height];

    // 通道分离
    splitImageChannel(image, r, g, b);

    QRgb hist_ior;
    // 根据不同的选项选择不同通道组合
    uchar *bits = nullptr;
    switch (channel) {
        case ImageChannel::Y:
            hist_ior = qRgba(128, 128, 128, 255);
            bits = grayImage.bits();
            break;
        case ImageChannel::R:
            hist_ior = qRgba(255, 0, 0, 255);
            bits = r;
            break;
        case ImageChannel::G:
            hist_ior = qRgba(0, 255, 0, 255);
            bits = g;
            break;
        case ImageChannel::B:
            hist_ior = qRgba(0, 0, 255, 255);
            bits = b;
            break;
    }

    const int gray_level = 256;
    int hist[gray_level] = {0};

    // 计算直方图
    for (int i=0; i<width*height; i++)
    {
       int val = bits[i];
       hist[val]++;
    }

    // 压缩直方图使其与图像同高
    int max_hist_val = hist[0];
    for (int i=1; i<gray_level; i++)
    {
        max_hist_val = hist[i] > max_hist_val ? hist[i] : max_hist_val;
    }

    int s_w = 2;
    int w = s_w*gray_level;
    int h = w;//width*height;
    float s_h = 0.8;

    for (int i=0; i<gray_level; i++)
    {
        int v = hist[i];
        // 看不太懂，为什么乘了一堆东西
        hist[i] = int(h*1.0/max_hist_val * s_h * v);
    }

    QImage hist_image(w, h, QImage::Format_RGBA8888);
    QRgb value;
    for (int j=0; j<h; j++)
    {
        for (int i=0; i<w; i++)
        {
            // 判断数值范围
            if ( (hist[i/s_w] > 0) && (j >= h-hist[i/s_w]) )
                value = hist_ior;
            else
                value = qRgba(255, 255, 255, 255);
            hist_image.setPixel(i, j, value);
        }
    }
    QImage scaled_hish_image = hist_image.scaled(width, height,Qt::KeepAspectRatio);
    delete [] r;
    delete [] g;
    delete [] b;

    return scaled_hish_image;
}

// 计算负片
QImage calculateNegative(QImage &image, ImageChannel channel)
{
    // obtain gray image
    int width = image.width();
    int height = image.height();

    QImage newImage = image;
    int r, g, b;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = image.pixel(i, j);
            r = qRed(pixel);
            g = qGreen(pixel);
            b = qBlue(pixel);
            QRgb newPixel;
            // 按不同颜色通道分别处理，在对应通道计算对255的补
            switch (channel) {
                case ImageChannel::Y:
                    newPixel = qRgb(255-r, 255-g, 255-b);
                    break;
                case ImageChannel::R:
                    newPixel = qRgb(255-r, g, b);
                    break;
                case ImageChannel::G:
                    newPixel = qRgb(r, 255-g, b);
                    break;
                case ImageChannel::B:
                    newPixel = qRgb(r, g, 255-b);
                    break;
            }
            newImage.setPixel(i, j, newPixel);
          }
    }

    return newImage;
}

// 生成伪彩色图像
QImage convertToPseudoColor(QImage &image, ColorMap map)
{
    int width = image.width();
    int height = image.height();
    // 获得灰色图像
    QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);

    // 分离3个通道
    QImage newImage(width, height, QImage::Format_RGB888);
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            QRgb pixel = grayImage.pixel(i, j);
            QRgb newPixel;
            int index, r, g, b;
            index = qRed(pixel); // 为什么是qRed？
            r = qRed(pixel);
            g = qGreen(pixel);
            b = qBlue(pixel);
            // 颜色映射关系保存在map中，以index变量为索引取值
            switch (map) {
                case ColorMap::Jet:
                    r = jet_table[index*3];
                    g = jet_table[index*3+1];
                    b = jet_table[index*3+2];
                    break;
                case ColorMap::Parula:
                    r = parula_table[index*3];
                    g = parula_table[index*3+1];
                    b = parula_table[index*3+2];
                    break;
                case ColorMap::Hot:
                    r = hot_table[index*3];
                    g = hot_table[index*3+1];
                    b = hot_table[index*3+2];
                    break;
            }
            newPixel = qRgb(r, g, b);
            newImage.setPixel(i, j, newPixel);
          }
    }
    return newImage;
}

// 直方图均衡化
QImage equalizeHistogramProc1(QImage &image)
{
    int width = image.width();
    int height = image.height();
    int pixel_num = width*height;

    // 分离颜色通道
    uchar *channels = new uchar[pixel_num*3];
    uchar *r = channels;
    uchar *g = channels+pixel_num;
    uchar *b = channels+2*pixel_num;
    splitImageChannel(image, r, g, b);

    // RGB转换为YUV颜色空间
    float *ycrcb = new float[pixel_num*3];
    float *y = ycrcb;
    float *cr = ycrcb+pixel_num;
    float *cb = ycrcb+2*pixel_num;
    rgb2ycrcb(r, g, b, pixel_num, y, cr, cb);

    // 计算直方图
    int *hist = new int[pixel_num]; // hist/pdf
    const int gray_level = 256;
    float *gray_distribution = new float[gray_level];// cdf

    uchar *gray_equal = new uchar[gray_level]; // equalized gray

        // 计算概率密度
        memset(hist, 0, pixel_num*sizeof(int));
        for (int i=0; i<pixel_num; i++)
        {
            int index = (int)y[i]; // gray scale
            hist[index]++;
        }

        // 累计概率密度
        memset(gray_distribution, 0, gray_level*sizeof(float));
        gray_distribution[0] = hist[0]*1.0f/pixel_num;
        for (int i = 1; i < gray_level; i++)
        {
            gray_distribution[i] = gray_distribution[i-1] + hist[i]*1.0f/pixel_num;
        }

        // 均衡后的灰度值计算
        memset(gray_equal, 0, gray_level*sizeof(uchar));
        for (int i = 0; i < gray_level; i++)
        {
            gray_equal[i] = (uchar)(255 * gray_distribution[i] + 0.5);
        }

        // 新的灰色通道
        for (int i=0; i<pixel_num; i++)
        {
            int index = (int)y[i]; // gray scale
            y[i] = gray_equal[index];
        }

        // 颜色空间变换
    ycrcb2rgb(y, cr, cb, pixel_num, r, g, b);

    // 生成处理后的图片
    int count = 0;
    QImage newImage = image;//grayImage;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            int nr = r[count];
            int ng = g[count];
            int nb = b[count];
            count++;
            newImage.setPixel(i, j, qRgb(nr,ng,nb));
        }
    }
    delete [] gray_equal;
    delete [] gray_distribution;
    delete [] channels;
    delete [] ycrcb;

    return newImage;
}

// 直方图均衡化
QImage equalizeHistogramProc(QImage &image)
{
    int width = image.width();
    int height = image.height();
    int pixel_num = width*height;

    // 获得灰度图像
    uchar *channels = new uchar[width*height*3];
    uchar *r = channels;
    uchar *g = channels+width*height;
    uchar *b = channels+2*width*height;
    splitImageChannel(image, r, g, b);

    uchar *c[4] = {r, g, b, 0};

    // 计算概率密度函数
    int *hist = new int[pixel_num]; // hist/pdf
    const int gray_level = 256;
    float *gray_distribution = new float[gray_level];// cdf

    uchar *gray_equal = new uchar[gray_level]; // equalized gray
    for (uchar **p=c; (*p) != 0; p++)
    {
        // 计算概率密度函数
        memset(hist, 0, pixel_num*sizeof(int));
        for (int i=0; i<pixel_num; i++)
        {
            int index = (*p)[i]; // gray scale
            hist[index]++;
        }

        // 计算累计概率密度
        memset(gray_distribution, 0, gray_level*sizeof(float));
        gray_distribution[0] = hist[0]*1.0f/pixel_num;
        for (int i = 1; i < gray_level; i++)
        {
            gray_distribution[i] = gray_distribution[i-1] + hist[i]*1.0f/pixel_num;
        }

        // 重新计算均衡化后的灰度值
        memset(gray_equal, 0, gray_level*sizeof(uchar));
        for (int i = 0; i < gray_level; i++)
        {
            gray_equal[i] = (uchar)(255 * gray_distribution[i] + 0.5);
        }

        // 新的灰度图
        for (int i=0; i<pixel_num; i++)
        {
            int index = (*p)[i]; // gray scale
            (*p)[i] = gray_equal[index];
        }
    }

    // 更新图片
    int count = 0;
    QImage newImage = image;//grayImage;
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            int nr = r[count];
            int ng = g[count];
            int nb = b[count];
            count++;
            newImage.setPixel(i, j, qRgb(nr,ng,nb));
        }
    }
    delete [] gray_equal;
    delete [] gray_distribution;
    delete [] channels;

    return newImage;
}


// 核心功能是实现卷积运算
void filter(uchar *src, int image_width, int image_height,
            float *kernel, int kernel_width, int kernel_height, uchar *dst)
{
    int i, j, m, n;
    float val;

    memset(dst, 0, image_width*image_height);

    for (j=kernel_height/2; j<image_height-kernel_height/2; j++)
    {
        for (i = kernel_width/2; i<image_width-kernel_width/2; i++)
        {
            val = 0;
            for (n=-kernel_height/2; n<=kernel_height/2; n++)
            {
                for (m=-kernel_width/2; m<=kernel_width/2; m++)
                {
                    // 按元素相乘再相加，四层for循环，方向绕的有点晕
                    val += src[(j-n)*image_width+(i-m)] *
                            kernel[(n+kernel_height/2)*kernel_width+m+kernel_width/2];
                }
            }
            // 截断
            val = val>255 ? 255 : val;
            dst[j*image_width+i] = (uchar)(val<0 ? 0 : val);
        }
    }
}

// 自适应对比度增强
void adaptiveContrastEnhancement(QImage &src_image, float *rgb, float *rgb_ii, float *rgb_ii_power, int max_window_size,
                                 int half_window_size, float alpha, float max_cg, QImage &dst_image)
{
    dst_image = src_image;
    int image_width = src_image.width();
    int image_height = src_image.height();
    int pixel_num = image_width*image_height;

    int max_image_width = src_image.width() + 2*max_window_size;
    int max_image_height = src_image.height() + 2*max_window_size;
    int max_pixel_num = max_image_width*max_image_height;
    int max_kernel_height = 2*max_window_size+1;
    int max_kernel_width = 2*max_window_size+1;

    int i=0, j=0;
    int kernel_height = 2*half_window_size+1;
    int kernel_width = 2*half_window_size+1;
    int kernel_size = kernel_height*kernel_width;
    float image_mean=0, image_std=0;
    for (int c=0; c<3; c++)
    {
        // 图像均值
        image_mean = box_integral(rgb_ii+c*max_pixel_num, max_image_width, max_image_height,
                               max_window_size, max_window_size + image_width-1,
                               max_window_size, max_window_size + image_height-1);
        image_mean /= pixel_num;

        // 图像标准差
        image_std = box_integral(rgb_ii_power+c*max_pixel_num, max_image_width, max_image_height,
                               max_window_size, max_window_size + image_width-1,
                               max_window_size, max_window_size + image_height-1);
        image_std /= pixel_num;
        image_std -= image_mean*image_mean;

        image_std = sqrtf(image_std);

        // 局部均值与标准差
        for (j=max_kernel_height/2; j<max_image_height-max_kernel_height/2; j++)
        {
            for (i=max_kernel_width/2; i<max_image_width-max_kernel_width/2; i++)
            {
                // mean
                float mean = box_integral(rgb_ii+c*max_pixel_num, max_image_width, max_image_height,
                                       i-kernel_width/2, i+kernel_width/2,
                                       j-kernel_height/2, j+kernel_height/2);
                mean /= kernel_size;

                // std
                float std= box_integral(rgb_ii_power+c*max_pixel_num, max_image_width, max_image_height,
                                       i-kernel_width/2, i+kernel_width/2,
                                       j-kernel_height/2, j+kernel_height/2);
                std = std/kernel_size - mean*mean;
                std = sqrtf(std);

                // 对比度的增益，还看不太明白
                float cg = alpha*image_std/std;
                if (cg>max_cg) cg = max_cg;

                float dst_val = mean + cg * (rgb[c*max_pixel_num + j*max_image_width+i] - mean);
                if (dst_val > 255) dst_val = 255;
                if (dst_val < 0) dst_val = 0;
                QRgb temp = dst_image.pixel(i-max_kernel_width/2, j-max_kernel_height/2);
                int temp_r = qRed(temp);
                int temp_g = qGreen(temp);
                int temp_b = qBlue(temp);
                if (c==0) temp_r = dst_val;
                if (c==1) temp_g = dst_val;
                if (c==2) temp_b = dst_val;
                dst_image.setPixel(i-max_kernel_width/2, j-max_kernel_height/2, qRgb(temp_r, temp_g, temp_b));
            }
        }
    }
}

// 积分图计算（直接相加）
void calculate_integral_image(float *image, int width, int height, float *integral_image)
{
    int i, j;

    // 只计算第一行，因为第二行以后都会用到前一行的数据
    float rs = 0;
    for(j=0; j<width; j++)
    {
        rs += image[j];
        integral_image[j] = rs;
    }
    for(i=1; i<height; ++i)
    {
        rs = 0;
        for(j=0; j<width; ++j)
        {
            rs += image[i*width+j];
            integral_image[i*width+j] = rs + integral_image[(i-1)*width+j];
        }
    }
}

// 积分图计算（平方处理)
void calculate_integral_image_power(float *image, int width, int height, float *integral_image)
{
    int i, j;

    // 计算第一行
    float rs = 0;
    for(j=0; j<width; j++)
    {
        rs += image[j]*image[j];
        integral_image[j] = rs;
    }

    // 从第二行进行累加，利用了前一行的数据，因此第一行需要单独处理
    for(i=1; i<height; ++i)
    {
        rs = 0;
        for(j=0; j<width; ++j)
        {
            // 一直累加，水平累加完，再加上上一行对应位置的rs值
            rs += image[i*width+j]*image[i*width+j];
            integral_image[i*width+j] = rs + integral_image[(i-1)*width+j];
        }
    }
}

// 取积分图上由((c1,c2),(r1,r2))确定的盒状区域的四个顶点的值
__inline float box_integral(float *integral_image, int width, int height, int c1, int c2, int r1, int r2)
{
    float a, b, c, d;

    a = (c1-1<0 || r1-1<0)	? 0 : integral_image[(r1-1) * width + (c1-1)];
    b = r1-1<0				? 0 : integral_image[(r1-1) * width + c2];
    c = c1-1<0				? 0 : integral_image[r2 * width + (c1-1)];
    d = integral_image[r2 * width + c2];
    // ？？？
    return a - b - c + d;
}
