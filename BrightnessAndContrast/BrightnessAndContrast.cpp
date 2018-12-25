#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv) {
    Mat src = imread("delhi.jpeg", IMREAD_COLOR);
    Mat newImage = Mat::zeros(src.size(), src.type());
    float alpha;
    int beta;
    cout<<"Enter alpha[1.0-3.0]"<<endl;
    cin>>alpha;
    cout<<"Enter beta[0-100]"<<endl;
    cin>>beta;
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            for(int k = 0; k < 3; k++) {
                newImage.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(alpha*(src.at<Vec3b>(i,j)[k]) + beta);
            }
        }
    }
    namedWindow("Output image",WINDOW_NORMAL);
    imshow("Output image", newImage);
    waitKey(0);
    return 0;
}
