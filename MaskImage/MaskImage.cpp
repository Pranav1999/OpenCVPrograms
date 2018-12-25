#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;

void Sharpen(const Mat& myImg, Mat& Result);

int main(int argc, char** argv) {
    const char* filename = argc >= 2 ? argv[1] : "blur.jpg";
    Mat src, dst0, dst1;
    if(argc>=3 && !strcmp("G", argv[2]))
        src = imread(filename, IMREAD_GRAYSCALE);
    else
        src = imread(filename, IMREAD_COLOR);

    if(src.empty()) {
        std::cout<<"Can't open image";
        return -1;
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    //Sharpen(src, dst0);
    //or we can use build-in function
    Mat kernel = (Mat_<char>(3,3) << 0,1,0,1,5,1,0,1,0);
    filter2D(src, dst1, src.depth(), kernel);

    imshow("Input", src);
    waitKey();
    //imshow("Output", dst0);
    imshow("Output", dst1);
    waitKey();
}

void Sharpen(const Mat& myImg, Mat& Result) {
    CV_Assert(myImg.depth() == CV_8U);

    const int nChannels = myImg.channels();
    Result.create(myImg.size(), myImg.type());

    for(int i = 1; i < myImg.rows - 1; i++) {
        const uchar* previous = myImg.ptr<uchar>(i - 1);
        const uchar* current = myImg.ptr<uchar>(i);
        const uchar* next = myImg.ptr<uchar>(i + 1);

        uchar* output = Result.ptr<uchar>(i);

        for(int j = nChannels; j < nChannels*(myImg.cols - 1); j++) {
            *output++ = saturate_cast<uchar>(5*current[j] - current[j - nChannels] - current[j + nChannels] - previous[j] - next[j]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));

}
