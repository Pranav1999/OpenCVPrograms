#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/core/utility.hpp>
#include<sstream>

using namespace cv;

int main(int argc, char** argv) {
    Mat I = imread("save.jpg", IMREAD_COLOR);
    int channels = I.channels();

    switch(channels) {
        case 1: {
               for(int i = 0; i < I.cols; i++) {
                for(int j = 0; j < I.rows; j++) {
                    //accessing pixel intensity values for single gray channel
                    I.at<uchar>(Point(i, j)) = 255 - I.at<uchar>(Point(i, j));
                }
            }
            break;
        }
        case 3: {
            for(int i = 0; i < I.cols; i++) {
                for(int j = 0; j < I.rows; j++) {
                    //accessing pixel intensity values for 3 channel
                    I.at<Vec3b>(Point(i, j)).val[0] = 255 - I.at<Vec3b>(Point(i, j)).val[0];    //blue
                    I.at<Vec3b>(Point(i, j)).val[1] = 255 - I.at<Vec3b>(Point(i, j)).val[1];    //green
                    I.at<Vec3b>(Point(i, j)).val[2] = 255 - I.at<Vec3b>(Point(i, j)).val[2];    //red
                }
            }
            break;
        }
    }
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow("Output", I);
	imwrite("Output.jpg", I);
    waitKey(0);
}
