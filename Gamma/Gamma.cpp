#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include<cmath>

using namespace cv;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv) {

    for(int i = 1; i <= 21; i++) {
        String filename = std::to_string(i) + ".jpg";
        cout<<filename;
        Mat src = imread(filename, IMREAD_COLOR);
        Mat output, img, concatimg;
        float gamma;
        Mat lookuptable(1, 256, CV_8U);
        uchar* p = lookuptable.ptr();
        gamma = 2;
        for(int i = 0; i < 256; i++) {
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }
        img = src.clone();
        LUT(src, lookuptable, img);
        hconcat(img, src, concatimg);
        gamma = 1;
        for(int i = 0; i < 256; i++) {
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }
        img = src.clone();
        LUT(src, lookuptable, img);
        hconcat(concatimg, img, concatimg);
        gamma = 0.5;
        for(int i = 0; i < 256; i++) {
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }
        img = src.clone();
        LUT(src, lookuptable, img);
        hconcat(concatimg, img, concatimg);
        gamma = 0.33;
        for(int i = 0; i < 256; i++) {
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }
        img = src.clone();
        LUT(src, lookuptable, img);
        hconcat(concatimg, img, concatimg);
        gamma = 0.25;
        for(int i = 0; i < 256; i++) {
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        }
        img = src.clone();
        LUT(src, lookuptable, img);
        hconcat(concatimg, img, concatimg);
        imwrite(std::to_string(i) + "other.jpg", concatimg);
    }

    return 0;
    //Mat src = imread("delhi.jpeg", IMREAD_COLOR);
    //Mat concatimg, newImage = src.clone();
    //float gamma;
    //cout<<"Enter gamma"<<endl;
    //cin>>gamma;
    //Mat lookuptable(1, 256, CV_8U);
    //uchar* p = lookuptable.ptr();
    //for(int i = 0; i < 256; i++) {
    //    p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
    //}
    //LUT(src, lookuptable, newImage);
    //hconcat(src, newImage, concatimg);
    //namedWindow("Output image",WINDOW_NORMAL);
    //imshow("Output image", concatimg);
    //waitKey(0);
    //return 0;
}
