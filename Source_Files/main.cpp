#include <iostream>
#include <string>
#include "opencv2/imgproc/types_c.h"
#include "function.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qlabel.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
    vector<int> location_x;
    vector<int> location_y;
    // 设置python.exe的路径
    Py_SetPythonHome(L"C:\\Users\\19941\\AppData\\Local\\Programs\\Python\\Python310");
    Py_Initialize(); //调用Py_Initialize()进行初始化
    if (!Py_IsInitialized())
    {
        cout << "初始化失败!" << endl;
    }
    else 
    {
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('.\\Py_Files')"); //指定face.py所在的目录

        PyObject* pModule = nullptr;  //声明变量
        // PyObject* pFunc = nullptr; // 声明变量
        PyObject* pFuncl = nullptr;

        pModule = PyImport_ImportModule("face");//这里是要调用的文件名face.py
        if (pModule == NULL)
        {
            cout << "没找到该Python文件" << endl;
        }
        else
        {
            // pFunc = PyObject_GetAttrString(pModule, "find_face");//这里是要调用的函数名
            pFuncl = PyObject_GetAttrString(pModule, "find_face_landmarks");

            PyObject* args = Py_BuildValue("(s)", ".\\Resource_Files\\1.jpg");//给python函数参数赋值
            // PyObject* face = PyObject_CallObject(pFunc, args);  // 面部矩形框
            PyObject* mark = PyObject_CallObject(pFuncl, args);//调用函数
            PyObject* x = nullptr;
            PyObject* y = nullptr;

            for (int n = 0; n < int(PyList_GET_SIZE(mark)); n++)
            {
                PyObject* location = PyList_GetItem(mark, n);
                x = PyTuple_GetItem(location, 0);
                y = PyTuple_GetItem(location, 1);
                int int_x = 1;
                int int_y = 1;

                PyArg_Parse(x, "i", &int_x);
                PyArg_Parse(y, "i", &int_y);
                location_x.push_back(int_x);  // 特征点的x坐标
                location_y.push_back(int_y);  // 特征点的y坐标
            }
        }
        Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。
    }
    QApplication a(argc, argv);
    QLabel label(QLabel::tr("Hello Qt"));
    label.show();

    //Mat scrImage = imread( ".\\Resource_Files\\1.jpg");
    //// 通道数，灰度图或彩色图
    //int channels = scrImage.channels();
    //// 克隆原始图像用于显示
    //Mat image = scrImage.clone();
    //Mat imageRGB[3];
    //// 分离scrImage的三个Channels到imageRGB
    //split(scrImage, imageRGB);

    //// 分别进行直方图均衡化/拉普拉斯锐化
    //for (int i = 0; i < channels; i++)
    //    //HistEqual(imageRGB[i], imageRGB[i]);
    //    //Laplacian(imageRGB[i], imageRGB[i], 0);
    //    ILPF(imageRGB[i], imageRGB[i], 30);
    //    //BLPF(imageRGB[i], imageRGB[i], 30);
    //    //GLPF(imageRGB[i], imageRGB[i], 30);

    //// 合并通道
    //merge(imageRGB, 3, scrImage);

    //namedWindow("原始", 0); resizeWindow("原始", 500, 700); moveWindow("原始", 0, 0); imshow("原始", image);
    ////namedWindow("均衡后", 0); resizeWindow("均衡后", 500, 700); moveWindow("均衡后", 500, 0); imshow("均衡后", scrImage);
    ////namedWindow("拉普拉斯", 0); resizeWindow("拉普拉斯", 500, 700); moveWindow("拉普拉斯", 500, 0); imshow("拉普拉斯", scrImage);
    //namedWindow("低通", 0); resizeWindow("低通", 500, 700); moveWindow("低通", 500, 0); imshow("低通", scrImage);

    //waitKey(0);
    ////system("pause");
    return a.exec();
}