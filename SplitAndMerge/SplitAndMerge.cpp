#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat img, splitChannels[3], bgr[3], output;
int redValue=0, blueValue=0, greenValue=0;

void init(char* name) {
    img = imread(name, IMREAD_COLOR);
    split(img, splitChannels);
}

void changeOutput(int, void*) {
        bgr[0] = (blueValue)?(splitChannels[0].clone()):(Mat::zeros(splitChannels[0].size(), CV_8UC1));
        bgr[1] = (greenValue)?(splitChannels[1].clone()):(Mat::zeros(splitChannels[1].size(), CV_8UC1));
        bgr[2] = (redValue)?(splitChannels[2].clone()):(Mat::zeros(splitChannels[2].size(), CV_8UC1));
        merge(bgr, 3, output);
        imshow("SplitAndMerge", output);
}

int main(int argc, char** argv) {
    namedWindow("SplitAndMerge", WINDOW_NORMAL);
    init(argv[1]);
    createTrackbar("red", "SplitAndMerge", &redValue, 1, changeOutput);
    createTrackbar("blue", "SplitAndMerge", &blueValue, 1, changeOutput);
    createTrackbar("green", "SplitAndMerge", &greenValue, 1, changeOutput);
    changeOutput(0,0);
    waitKey(0);
}
/*
int main(int argc, char** argv) {
    Mat image = imread(argv[1], IMREAD_COLOR);
    Mat splitChannels[3];
    split(image, splitChannels);
    namedWindow("redintensity", WINDOW_NORMAL);
    namedWindow("blueintensity", WINDOW_NORMAL);
    namedWindow("greenintensity", WINDOW_NORMAL);
    imshow("blueintensity", splitChannels[0]);
    imshow("greenintensity", splitChannels[1]);
    imshow("redintensity", splitChannels[2]);
    imwrite("blueintensity.jpg", splitChannels[0]);
    imwrite("greenintensity.jpg", splitChannels[1]);
    imwrite("redintensity.jpg", splitChannels[2]);
    Mat bgr[3], red, blue, green;
    bgr[0] = splitChannels[0].clone();
    bgr[1] = Mat::zeros(splitChannels[1].size(), CV_8UC1);
    bgr[2] = Mat::zeros(splitChannels[2].size(), CV_8UC1);
    merge(bgr, 3, blue);
    bgr[1] = splitChannels[1].clone();
    bgr[0] = Mat::zeros(splitChannels[0].size(), CV_8UC1);
    merge(bgr, 3, green);
    bgr[2] = splitChannels[2].clone();
    bgr[1] = Mat::zeros(splitChannels[1].size(), CV_8UC1);
    merge(bgr, 3, red);
    namedWindow("red", WINDOW_NORMAL);
    namedWindow("blue", WINDOW_NORMAL);
    namedWindow("green", WINDOW_NORMAL);
    imshow("blue", blue);
    imshow("green", green);
    imshow("red", red);
    imwrite("blue.jpg", blue);
    imwrite("green.jpg", green);
    imwrite("red.jpg", red);
    waitKey(0);
}
*/
