#include "padding.h"
#include "string.h"

// 根据不同的外插方法(borderType)，计算外插像素对应于原图中的坐标，p是扩充边缘的像素的坐标
int borderInterpolate( int p, int len, int borderType )
{
    if( (unsigned)p < (unsigned)len )
        ;
    else if( borderType == BORDER_REPLICATE )
        p = p < 0 ? 0 : len - 1;
    else if( borderType == BORDER_REFLECT || borderType == BORDER_REFLECT_101 )
    {
        int delta = borderType == BORDER_REFLECT_101;
        if( len == 1 )
            return 0;
        do
        {
            if( p < 0 )
                p = -p - 1 + delta;
            else
                p = len - 1 - (p - len) - delta;
        }
        while( (unsigned)p >= (unsigned)len );
    }
    else if( borderType == BORDER_WRAP )
    {
        if( p < 0 )
            p -= ((p-len+1)/len)*len;
        if( p >= len )
            p %= len;
    }
    else if( borderType == BORDER_CONSTANT )
        p = -1;

    return p;
}

// 填充边界像素，borderType: 边界类型，top，left为边界宽度，cn是尺度缩放因数
// borderType：扩充边缘的类型，就是外插的类型，有以下几种：
// * BORDER_REPLICATE             重复：  就是对边界像素进行复制
// * BORDER_REFLECT               反射：对感兴趣的图像中的像素在两边进行复制例如：fedcba|abcdefgh|hgfedcb    反射
// * BORDER_REFLECT_101           反射101： 例子：gfedcb|abcdefgh|gfedcba
// * BORDER_WRAP                  外包装：cdefgh|abcdefgh|abcdefg
// * BORDER_CONSTANT              常量复制：例子：iiiiii|abcdefgh|iiiiiii
void copyMakeBorder( const uchar* src, int w, int h,
                        uchar* dst, int nw, int nh,
                        int top, int left, int cn, int borderType )
{
    int i, j, k, elemSize = 1;

    int* tab = new int [(nw - w)*cn];
    int right = nw - w - left;
    int bottom = nh - h - top;

    for( i = 0; i < left; i++ )
    {
        // cn应该是scalar value吧
        j = borderInterpolate(i - left, w, borderType)*cn;
        for( k = 0; k < cn; k++ )
            tab[i*cn + k] = j + k;
    }

    for( i = 0; i < right; i++ )
    {
        j = borderInterpolate(w + i, w, borderType)*cn;
        for( k = 0; k < cn; k++ )
            tab[(i+left)*cn + k] = j + k;
    }

    w *= cn;
    nw *= cn;
    left *= cn;
    right *= cn;

    uchar* dstInner = dst + nw*top + left*elemSize;

    for( i = 0; i < h; i++, dstInner += nw, src += w )
    {
        if( dstInner != src )
            memcpy(dstInner, src, w*elemSize);
        for( j = 0; j < left; j++ )
            dstInner[j - left] = src[tab[j]];
        for( j = 0; j < right; j++ )
            dstInner[j + w] = src[tab[j + left]];
    }

    nw *= elemSize;
    dst += nw*top;

    for( i = 0; i < top; i++ )
    {
        j = borderInterpolate(i - top, h, borderType);
        memcpy(dst + (i - top)*nw, dst + j*nw, nw);
    }

    for( i = 0; i < bottom; i++ )
    {
        j = borderInterpolate(i + h, h, borderType);
        memcpy(dst + (i + h)*nw, dst + j*nw, nw);
    }
    delete [] tab;
}

// 这里把常值填充当作一个特殊情况进行处理，在重载函数copyMakeBorder中根据border_type类型进行分类型调用
// 填充边界像素，以常值数组value填充，top，left为边界宽度，cn为 scalar value
void copyMakeConstBorder( const uchar* src, int w, int h,
                             uchar* dst, int nw, int nh,
                             int top, int left, int cn, const uchar *value )
{
    int i, j;
    uchar* constBuf = new uchar[nw*cn]; //calloc, malloc -> free
    int right = nw - w - left;
    int bottom = nh - h - top;

    memset(dst, 0, nw*nh*cn);

    for( i = 0; i < nw; i++ )
    {
        for( j = 0; j < cn; j++ )
            constBuf[i*cn + j] = value[j];
    }

    w *= cn;
    nw *= cn;
    left *= cn;
    right *= cn;

    uchar* dstInner = dst + nw*top + left;
    for( i = 0; i < h; i++, dstInner += nw, src += w )
    {
        memcpy( dstInner, src, w );
        memcpy( dstInner - left, constBuf, left );
        memcpy( dstInner + w, constBuf, right );
    }

    //p += nw*top;
    dst += nw*top;
    for( i = 0; i < top; i++ )
        // 赋值
        memcpy(dst + (i - top)*nw, constBuf, nw);

    for( i = 0; i < bottom; i++ )
        memcpy(dst + (i + h)*nw, constBuf, nw);

    delete [] constBuf;
}

// 重载函数，主要是根据bordertype是否是常数边界分别用两个函数进行处理
void copyMakeBorder(uchar *src, int w, int h, int cn, int top, int bottom,
                    int left, int right, BorderType borderType, const uchar *value, uchar *dst)
{
    int nw = w+left+right;
    int nh = h+top+bottom;

    if(top == 0 && left == 0 && bottom == 0 && right == 0)
    {
        memcpy(dst, src, nw*nh*cn);
        return;
    }

    if( borderType != BORDER_CONSTANT )
        copyMakeBorder( src, w, h, dst, nw, nh,
                       top, left, cn, borderType );
    else
        copyMakeConstBorder( src, w, h, dst, nw, nh,
                            top, left, cn, value );
}

// 移除边界，直接通过坐标相减，right,left,top,buttom均为边界宽度
void copyRemoveBorder(const uchar *src, int w, int h, int cn, int top, int bottom,
                    int left, int right,  uchar *dst)
{
    int nw = w-left-right;
    int nh = h-top-bottom;

    w *= cn;
    nw *= cn;
    left *= cn;

    for (int i=0; i<nh; i++)
    {
        memcpy(dst+i*nw, src+(i+top)*w+left, nw);
    }
}
