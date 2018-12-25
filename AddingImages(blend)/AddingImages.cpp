#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/core/utility.hpp>
#include<sstream>

using namespace cv;

int main(int argc, char** argv) {
    Mat img1, img2, dst;
    img1 = imread("panda.jpg", IMREAD_COLOR);
    img2 = imread("black.jpg", IMREAD_COLOR);
    int alpha = 1.0, beta = 1.0, gamma = 0.0;
    addWeighted(img1, alpha, img2, beta, gamma, dst);
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow("Output", dst);
    waitKey(0);
}
