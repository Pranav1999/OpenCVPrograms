#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;

int main(int argc, char** argv) {
    //initialize
    Mat src = imread("delhi.jpg", IMREAD_COLOR);
    Mat dst;
    int ab, ba, bb, bc, cb;
    int cont;
    //loop
        //ask user for mask
        //apply filter

    while(true) {
        std::cout<<"Enter mask"<<std::endl;
        std::cin>>ab;
        std::cin>>ba;
        std::cin>>bb;
        std::cin>>bc;
        std::cin>>cb;
        std::cout<<std::endl;
        Mat kernel = (Mat_<char>(3,3)<<0,ab,0,ba,bb,bc,0,cb,0);
        filter2D(src, dst, src.depth(), kernel);
        namedWindow("Output", WINDOW_NORMAL);
        imshow("Output", dst);
        waitKey(5000);
        std::cout<<"Continue??"<<std::endl;
        std::cin>>cont;
        if(!cont)
            break;
    }
}
