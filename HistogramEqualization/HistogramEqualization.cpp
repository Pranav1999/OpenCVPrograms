#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    Mat src, dst;
    src = imread(argv[1], IMREAD_COLOR);
    cvtColor(src, src, COLOR_BGR2GRAY);
    equalizeHist(src, dst);
    namedWindow("Src", WINDOW_NORMAL);
    namedWindow("Dst", WINDOW_NORMAL);
    imshow("Src", src);
    imshow("Dst", dst);
    waitKey(0);
    return 0;
}
