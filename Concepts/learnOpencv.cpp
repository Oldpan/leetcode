#include "learnOpencv.h"

using namespace cv;

int image_read()
{
    cv::Mat img = cv::imread("../dataset/image/88.jpg", -1);
    if( img.empty() )
        return -1;
    cv::namedWindow( "Example1", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Example1", img);
    cv::waitKey(0);
    cv::destroyWindow("Example1");
    return 0;
}

void NearestInsert(cv::Mat& input, cv::Mat& result, int Width)
{
    //判断输入有效性
    CV_Assert(input.data != NULL);
    int rows = input.rows, cols = input.cols;
    //构建目标图像
    result = cv::Mat(cv::Size(Width, Width), input.type(), cv::Scalar::all(0));
    int resultrows = result.rows, resultcols = result.cols;
    //坐标转换，求取缩放倍数
    float cx = (float)cols / resultcols;
    float cy = (float)rows / resultrows;
    //遍历图像，完成缩放操作
    for (int i = 0; i < resultrows; i++)
    {
        //取整，获取目标图像在源图像对应坐标
        int yy = cvFloor(cy*i);
        for (int j = 0; j < resultcols; j++)
        {
            int xx = cvFloor(j*cx);
            //边界处理，防止指针越界
            if (xx >= cols) xx  = rows - 1;
            if (yy >= rows) yy = cols - 1;
            //映射矩阵
            result.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(yy, xx);
        }
    }

    cv::imshow("origin", input);
    cv::imshow("result", result);
    cv::waitKey(0);
}

void BilinearInterpolation(cv::Mat& src, cv::Mat& dst)
{
    CV_Assert(src.data!=NULL);
    int srcRows = src.rows;
    int srcCols = src.cols;
    //定义目标函数
    dst = cv::Mat::zeros(150,150,src.type());
    int dstRows = dst.rows;
    int dstCols = dst.cols;
    //缩放因子
    double sx = src.cols / dst.cols;
    double sy = src.rows / dst.rows;
    for (int i = 0; i < dst.rows; i++)
    {
        //求目标图像的像素对应原图像的坐标，为了使得目标图像中心与原图像中心对齐，使用下面的公式
        double index_i = (i + 0.5)*sy - 0.5;
        //判断是否越界
        if (index_i < 0)
            index_i = 0;
        if (index_i > src.rows - 1)
            index_i = src.rows - 1;
        int i1 = cvFloor(index_i);//向下取整
        int i2 = cvCeil(index_i);
        double v = index_i - i1;
        for (int j = 0; j < dst.cols; j++)
        {
            double index_j = (j + 0.5)*sx - 0.5;
            if (index_j < 0)
                index_j = 0;
            if (index_j > src.cols - 1)
                index_j = src.cols - 1;
            int j1 = cvFloor(index_j);
            int j2 = cvCeil(index_j);
            double u = index_j - j1;
            if (src.channels() == 1)
                dst.at<uchar>(i, j) = cvFloor((1 - u)*(1 - v)*src.at<uchar>(i1, j1) + (1 - u)*v*src.at<uchar>(i2, j1) + u*(1 - v)*src.at<uchar>(i1, j2) + u*v*src.at<uchar>(i2, j2));
            else
            {
                dst.at<Vec3b>(i, j)[0] = cvFloor((1 - u)*(1 - v)*src.at<Vec3b>(i1, j1)[0] + (1 - u)*v*src.at<Vec3b>(i2, j1)[0] + u*(1 - v)*src.at<Vec3b>(i1, j2)[0] + u*v*src.at<Vec3b>(i2, j2)[0]);
                dst.at<Vec3b>(i, j)[1] = cvFloor((1 - u)*(1 - v)*src.at<Vec3b>(i1, j1)[1] + (1 - u)*v*src.at<Vec3b>(i2, j1)[1] + u*(1 - v)*src.at<Vec3b>(i1, j2)[1] + u*v*src.at<Vec3b>(i2, j2)[1]);
                dst.at<Vec3b>(i, j)[2] = cvFloor((1 - u)*(1 - v)*src.at<Vec3b>(i1, j1)[2] + (1 - u)*v*src.at<Vec3b>(i2, j1)[2] + u*(1 - v)*src.at<Vec3b>(i1, j2)[2] + u*v*src.at<Vec3b>(i2, j2)[2]);
            }
        }

    }
    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
}
