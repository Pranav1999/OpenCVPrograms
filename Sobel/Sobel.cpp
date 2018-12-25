#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/core/utility.hpp>
#include<opencv2/imgproc.hpp>
#include<sstream>

using namespace cv;

int main(int argc, char** argv) {
    Mat img = imread("delhi.jpg", IMREAD_COLOR);
    Mat sobelx, sobely, result;
    Sobel(img, sobelx, CV_8U, 0, 1);
    Sobel(img, sobely, CV_8U, 1, 0);
	addWeighted(sobelx, 0.5, sobely, 0.5, 0, result);
	namedWindow("result", WINDOW_NORMAL);
	imshow("result", result);
	waitKey();
    imwrite("sobelx.jpg", sobelx);
    imwrite("sobely.jpg", sobely);
}
