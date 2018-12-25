#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    Mat image1 = imread("unnamed.jpg", IMREAD_COLOR);
    //namedWindow("Original", WINDOW_AUTOSIZE);
    //imshow("Original", image1);
    Mat image2(image1, Rect(10,10,100,100));
    //namedWindow("Rect", WINDOW_AUTOSIZE);
    //imshow("Rect", image2);
    Mat image3 = image1(Range::all(), Range(200,300));
    namedWindow("Range", WINDOW_AUTOSIZE);
    imshow("Range", image3);
    waitKey(0);
}
