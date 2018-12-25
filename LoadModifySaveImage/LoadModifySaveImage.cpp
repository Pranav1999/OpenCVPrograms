#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    String imageName("unnamed.jpg");
    if(argc > 1) {
        imageName = argv[1];
    }
    Mat image;
    image = imread(imageName, IMREAD_COLOR);
    if(!image.data) {
        cerr<<"No Image..";
        return -1;
    }
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    imwrite("Gray_Image.jpg", grayImage);
    namedWindow(imageName, WINDOW_AUTOSIZE);
    namedWindow("Gray", WINDOW_AUTOSIZE);
    imshow(imageName, image);
    imshow("Gray", grayImage);
    waitKey(0);
    return 0;
}
