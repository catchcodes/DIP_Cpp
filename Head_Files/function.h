#ifndef Function_H
#define Function_H

#include<opencv2/opencv.hpp>

using cv::Mat;

// 直方图均衡化函数的声明
void HistEqual(Mat& gray, Mat& result);
// 拉普拉斯算子
void Laplacian(Mat& gray, Mat& result, int padding=0);
// 频移
void fftshift(Mat plane0, Mat plane1);
// 理想低/高通滤波器
void ILPF(Mat& gray, Mat& result, int fc, bool highpass=false);
// n阶巴特沃斯低通滤波器
void BLPF(Mat& gray, Mat& result, int fc, int level=2);
// 高斯低通滤波器
void GLPF(Mat& gray, Mat& result, int fc);

#endif
