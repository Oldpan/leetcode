/*
* 参考: http://www.cs.umd.edu/~djacobs/CMSC426/Convolution.pdf
* 本代码测试平台: VS2015 + OpenCV3.1
* 主要是利用OpenCV的copyMakeBorder函数以及Mat等数据结构, 适当的降低OpenCV库版本也可运行本代码
* 个人建议平台: OpenCV2.4.x以上 + VS2010以上
* 以可读性优先, 性能其次的要求来编写代码, 部分代码可以适当的优化. 如可以将Mat::clone()换成copyTo函数
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>
#include "opencv2/opencv.hpp"


/**************************************Correlation与Convolution算法实现函数*******************************************/
/** @brief 1D数据进行相关操作

*/
static void Correlation_1D(const cv::Mat& src, cv::Mat& kernel, cv::Mat& dst)
{
    CV_Assert(kernel.cols % 2 == 1);    // 列必须为奇数

    const int N = kernel.cols;          // kernel的长度
    const int n = N / 2;                // kernel的长度一半

    const int LEFT = n;
    const int RIGHT = n;
    // 数据左边和右边各个添加两个
    cv::Mat tmp;
    cv::copyMakeBorder(src, tmp, 0, 0, LEFT, RIGHT, cv::BORDER_REPLICATE);

    cv::Mat result = cv::Mat::zeros(tmp.rows, tmp.cols, CV_32FC1);
    for (int x = n; x < tmp.cols - n; ++x)
    {
        double sum = 0.0;
        for (int i = 0; i < kernel.cols; ++i)
        {
            float k = kernel.at<float>(0, i);
            float s = tmp.at<float>(0, i + x - n);
            sum = sum + (k*s);
        }
        result.at<float>(0, x) = sum;
    }
    // 扣出结果图
    cv::Rect r = cv::Rect(LEFT, 0, src.cols, src.rows);
    dst = result(r).clone();
}

/** @brief 1D数据进行卷积操作

*/
static void Convolution_1D(const cv::Mat& src, cv::Mat& kernel, cv::Mat& dst)
{
    CV_Assert(kernel.cols % 2 == 1);    // 列必须为奇数

    const int N = kernel.cols;          // kernel的长度
    const int n = N / 2;                // kernel的长度一半

    const int LEFT = n;
    const int RIGHT = n;
    // 数据左边和右边各个添加两个
    cv::Mat tmp;
    cv::copyMakeBorder(src, tmp, 0, 0, LEFT, RIGHT, cv::BORDER_REPLICATE);

    cv::Mat result = cv::Mat::zeros(tmp.rows, tmp.cols, CV_32FC1);
    for (int x = n; x < tmp.cols - n; ++x)
    {
        double sum = 0.0;
        for (int i = 0; i < kernel.cols; ++i)
        {
            float k = kernel.at<float>(0, i);
            float s = tmp.at<float>(0, x + n - i);
            sum = sum + (k * s);
        }
        result.at<float>(0, x) = sum;
    }

    // 扣出结果图
    cv::Rect r = cv::Rect(LEFT, 0, src.cols, src.rows);
    dst = result(r).clone();
}

/** @brief 二维相关

@param src 输入图像
@param kernel 相关核 核的长和宽必须是奇数, 即(2m+1)*(2*n+1)
@param dst 处理后的图
*/
static void Correlation_2D(const cv::Mat& src, cv::Mat& kernel, cv::Mat& dst)
{
    CV_Assert((kernel.cols % 2 == 1) && (kernel.rows % 2 == 1));

    const int X_N = kernel.cols;
    const int Y_N = kernel.rows;

    const int xn = X_N / 2;
    const int yn = Y_N / 2;

    const int LEFT = xn;
    const int RIGHT = xn;
    const int TOP = yn;
    const int BOTTOM = yn;

    cv::Mat tmp;
    cv::copyMakeBorder(src, tmp, TOP, BOTTOM, LEFT, RIGHT, cv::BORDER_REPLICATE);
    tmp.convertTo(tmp, CV_32F);

    cv::Mat result = cv::Mat::zeros(tmp.rows, tmp.cols, CV_32FC1);
    for (int x = xn; x < tmp.cols - xn; ++x)
    {
        for (int y = yn; y < tmp.rows - yn; ++y)
        {
            double sum = 0.0;

            for (int i = 0; i < kernel.rows; ++i)
            {
                for (int j = 0; j < kernel.cols; ++j)
                {
                    float k = kernel.at<float>(i, j);
                    float s = tmp.at<float>(i + y - yn, j + x - xn);
                    sum = sum + (k*s);
                }
            }
            result.at<float>(y, x) = sum;
        }
    }

    cv::Rect r = cv::Rect(LEFT, TOP, src.cols, src.rows);
    dst = result(r).clone();
}

/** @brief 二维卷积

@param src 输入图像
@param kernel 相关核 核的长和宽必须是奇数, 即(2m+1)*(2*n+1)
@param dst 处理后的图
*/
static void Convolution_2D(const cv::Mat& src, cv::Mat& kernel, cv::Mat& dst)
{
    CV_Assert((kernel.cols % 2 == 1) && (kernel.rows % 2 == 1));

    const int X_N = kernel.cols;
    const int Y_N = kernel.rows;

    const int xn = X_N / 2;
    const int yn = Y_N / 2;

    const int LEFT = xn;
    const int RIGHT = xn;
    const int TOP = yn;
    const int BOTTOM = yn;

    cv::Mat tmp;
    cv::copyMakeBorder(src, tmp, TOP, BOTTOM, LEFT, RIGHT, cv::BORDER_REPLICATE);
    tmp.convertTo(tmp, CV_32F);

    cv::Mat result = cv::Mat::zeros(tmp.rows, tmp.cols, CV_32FC1);
    for (int x = xn; x < tmp.cols - xn; ++x)
    {
        for (int y = yn; y < tmp.rows - yn; ++y)
        {
            double sum = 0.0;

            for (int i = 0; i < kernel.rows; ++i)
            {
                for (int j = 0; j < kernel.cols; ++j)
                {
                    float k = kernel.at<float>(i, j);
                    float s = tmp.at<float>(y + yn - i, x + xn - j);
                    sum = sum + (k * s);
                }
            }
            result.at<float>(y, x) = sum;
        }
    }

    cv::Rect r = cv::Rect(LEFT, TOP, src.cols, src.rows);
    dst = result(r).clone();
}


/**************************************算法验证所需要的工具函数*******************************************************/
/** @brief vector<int>类型数据转换成行向量

@param data vector<int>类型数据
@param dst 输出的Mat格式的行向量
*/
static void VecToMat(std::vector<float>& data, cv::Mat& dst)
{
    dst = cv::Mat(data, true);
    cv::transpose(dst, dst);
}

/** @brief 随机产生vector类型数据, 数据个数为num个

@param data 用来接收所产生的数据
@param num data数据的个数
*/
static void CreateVec(std::vector<float>& data, int num)
{
    data.clear();
    srand(unsigned(time(NULL)));
    for (int i = 0; i < num; ++i)
    {
        data.push_back(i);
    }
    std::random_shuffle(data.begin(), data.end());
}

/** @brief 输出矩阵的值
此矩阵必须是行矩阵, 即只有一行

@param m 要输出值的矩阵
*/
static void PrintResult(const cv::Mat& m)
{
    for (int x = 0; x < m.cols; ++x)
    {
        std::cout << m.at<float>(0, x) << " ";
    }
    std::cout << std::endl;
}

/** @brief 比较两个矩阵的差异

比较两个矩阵的差异, 因为两个矩阵均为浮点型, 所以如果两个像素值的差大于eps, 则认为是不同的;反之, 则相同
比较结果若为黑色, 则相同; 若为白色部分, 则不同.

@param m1 第一个矩阵
@param m2 第二个矩阵
@param dst 矩阵比较结果, 白色表示不同, 黑色表示相同
@param eps 两个像素值的差异比较精度
*/
static void CompareTwoMatrix(const cv::Mat& m1, const cv::Mat& m2, cv::Mat& dst, float eps)
{
    CV_Assert(m1.type() == CV_32FC1);
    CV_Assert(m2.type() == CV_32FC1);
    if ((m1.rows != m2.rows) || (m1.cols != m2.cols))
    {
        dst = cv::Mat(m1.rows, m1.cols, CV_8UC1, 255);
        return;
    }
    dst = cv::Mat::zeros(m1.rows, m1.cols, CV_8UC1);
    for (int y = 0; y < m1.rows; ++y)
    {
        for (int x = 0; x < m2.cols; ++x)
        {
            float v1 = m1.at<float>(y, x);
            float v2 = m2.at<float>(y, x);
            if (std::fabs(v1 - v2) > eps)
            {
                dst.at<uchar>(y, x) = 255;
            }
        }
    }

}

/** @brief 将矩阵旋转180

输入矩阵必须是单通道浮点类型, 即CV_32FC1
@param src 原始矩阵
@param dst 旋转后的局转
*/
static void RotateMatrix180(const cv::Mat& src, cv::Mat& dst)
{
    CV_Assert(src.type() == CV_32FC1);
    assert((src.rows == src.cols) && (src.rows % 2 == 1));

    dst = cv::Mat::zeros(src.rows, src.cols, src.type());

    for (int y = 0; y < dst.rows; ++y)
    {
        for (int x = 0; x < dst.cols; ++x)
        {
            //float value = src.at<float>(y, x);
            dst.at<float>(y, x) = src.at<float>(dst.rows - y - 1, dst.cols - x - 1);
        }
    }
}


/***************************************算法测试函数******************************************************************/
void test_CorrelationConvolution()
{
/************************************一维卷积相关验证部分****************************************/
    // 创建一维数据并转换成Mat类型
    std::vector<float> data;
    CreateVec(data, 16);
    cv::Mat m;
    VecToMat(data, m);
    std::cout << "一维原始数据:";
    PrintResult(m);

    // 创建一维核
    float kernelData[] = { 3, 7, 5 };
    cv::Mat kernel = cv::Mat(1, 3, CV_32FC1, kernelData);

    // 一维相关
    cv::Mat correlation_1D_dst;;
    Correlation_1D(m, kernel, correlation_1D_dst);
    std::cout << "一维相关的数据结果:";
    PrintResult(correlation_1D_dst);

    // 一维卷积
    cv::Mat convolution_1D_dst;
    Convolution_1D(m, kernel, convolution_1D_dst);
    std::cout << "一维卷积的数据结果:";
    PrintResult(convolution_1D_dst);
/*******************************二维卷积相关计算与Opencv验证部分*********************************/

    // 请在此添加自己的图片路径
    std::string path = "../Resources/wechat_20180409161327.bmp";
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (!img.data) return;
    cv::Mat kernel_2D = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    cv::Mat correlation_2d_dst;
    Correlation_2D(img, kernel_2D, correlation_2d_dst);

    cv::Mat cv_filter2D_dst;
    cv::filter2D(img, cv_filter2D_dst, CV_32F, kernel_2D, cv::Point(-1, -1), cv::BORDER_REPLICATE);

    cv::Mat convolution_2d_dst;
    Convolution_2D(img, kernel_2D, convolution_2d_dst);

    cv::Mat cmpCorrelationCvfilter2d;
    CompareTwoMatrix(cv_filter2D_dst, correlation_2d_dst, cmpCorrelationCvfilter2d, 1);
    cv::imshow("cv::filter2D与Correlation_2D比较", cmpCorrelationCvfilter2d);

/***********************************二维卷积与相关比较验证部分***********************************/
    kernel_2D = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    Correlation_2D(img, kernel_2D, correlation_2d_dst);
    cv::Mat rotKernel_2D;
    cv::Mat cmpRotResult;   RotateMatrix180(kernel_2D, rotKernel_2D);
    Convolution_2D(img, rotKernel_2D, convolution_2d_dst);
    CompareTwoMatrix(correlation_2d_dst, convolution_2d_dst, cmpRotResult, 2);
    cv::imshow("kernel的相关与kernel旋转后的卷积比较", cmpRotResult);

    cv::waitKey(0);
}
