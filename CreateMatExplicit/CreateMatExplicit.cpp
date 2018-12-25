#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    //For multidimensional
    //int sz = {3,3,3};
    //Mat M(3,sz,CV_8UC3, Scalar(0,50,255));

    /*Mat M(20,20,CV_8UC(3), Scalar(0,50,255));                 //initialize with consructor
    Mat T;
    T.create(20,20,CV_8UC(3));                                  //initialize with create function
    cout<<"T="<<endl<<" "<<T;
    namedWindow("GG", WINDOW_AUTOSIZE);
    imshow("GG", T);
    waitKey(0);*/

    //Mat E = Mat::eye(5,5,CV_64F);
    //cout<<"E = "<<endl<<E<<endl;
    //Mat Z = Mat::zeros(5,5,CV_32F);
    //cout<<"Z = "<<endl<<Z<<endl;
    //Mat O = Mat::ones(5,5,CV_8UC1);
    //cout<<"O = "<<endl<<O<<endl;

    //Mat C = (Mat_<double>(3,3)<<0, -1, 0, -1, 5, -1, 0, -1, 0);
    //Mat D = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
    //Mat E = C.row(1).clone();
    //Mat F = Mat(10, 10, CV_8UC1);
    //randu(F, Scalar::all(0), Scalar::all(255));
    //cout<<"C = "<<endl<<C<<endl;
    //cout<<"D = "<<endl<<D<<endl;
    //cout<<"E = "<<endl<<E<<endl;
    //cout<<"F(default) = "<<endl<<F<<endl;
    //cout<<"F(python) = "<<endl<<format(F,Formatter::FMT_PYTHON)<<endl;
    //cout<<"F(csv) = "<<endl<<format(F,Formatter::FMT_CSV)<<endl;
    //cout<<"F(numpy) = "<<endl<<format(F,Formatter::FMT_NUMPY)<<endl;
    //cout<<"F(c) = "<<endl<<format(F,Formatter::FMT_C)<<endl;

    Point2f P2f(6,4);
    Point3f P3f(4,5,6);
    cout<<"Point 2D: "<<P2f<<endl;
    cout<<"Point 3D: "<<P3f<<endl;
    vector<float> v;
    v.push_back((float)CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    cout<<"Vector of floats via Mat: "<<endl<<Mat(v)<<endl;
    vector<Point2f> vPoints(20);
    for(size_t i=0; i<vPoints.size(); i++)
        vPoints[i] = Point2f((float)(i*5), (float)(i%7));
    cout<<"Vector of 2D points: "<<endl<<vPoints<<endl;
}
