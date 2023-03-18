#include <iostream>
#include <string>
#include "opencv2/imgproc/types_c.h"
#include "function.h"

using namespace std;
using namespace cv;


int main()
{
    Mat scrImage = imread(".\\Resource_Files\\moon.bmp");
    // 通道数，灰度图或彩色图
    int channels = scrImage.channels();
    // 克隆原始图像用于显示
    Mat image = scrImage.clone();
    Mat imageRGB[3];
    // 分离scrImage的三个Channels到imageRGB
    split(scrImage, imageRGB);

    // 分别进行直方图均衡化/拉普拉斯锐化
    for (int i = 0; i < channels; i++)
        //HistEqual(imageRGB[i], imageRGB[i]);
        //Laplacian(imageRGB[i], imageRGB[i], 0);
        //ILPF(imageRGB[i], imageRGB[i], 30);
        //BLPF(imageRGB[i], imageRGB[i], 30);
        GLPF(imageRGB[i], imageRGB[i], 30);

    // 合并通道
    merge(imageRGB, 3, scrImage);

    namedWindow("原始", 0); resizeWindow("原始", 500, 700); moveWindow("原始", 0, 0); imshow("原始", image);
    //namedWindow("均衡后", 0); resizeWindow("均衡后", 500, 700); moveWindow("均衡后", 500, 0); imshow("均衡后", scrImage);
    //namedWindow("拉普拉斯", 0); resizeWindow("拉普拉斯", 500, 700); moveWindow("拉普拉斯", 500, 0); imshow("拉普拉斯", scrImage);
    namedWindow("低通", 0); resizeWindow("低通", 500, 700); moveWindow("低通", 500, 0); imshow("低通", scrImage);

    waitKey(0);

    return 0;
}