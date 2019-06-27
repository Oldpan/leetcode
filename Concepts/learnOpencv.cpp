#include "learnOpencv.h"

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


