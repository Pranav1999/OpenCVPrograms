#include<iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/core.hpp>
#include<opencv2/core/utility.hpp>
#include<sstream>

using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table);

int main(int argc, char** argv) {
    if(argc < 3) {
        std::cout<<"Not enough param";
        return -1;
    }

    Mat I, J;
    if(argc == 4 && !strcmp(argv[3], "G"))
        I = imread(argv[1], IMREAD_GRAYSCALE);
    else
        I = imread(argv[1], IMREAD_COLOR);

    if(I.empty()) {
        std::cout<<"Image couldn't be loaded";
        return -1;
    }

    int divideWith = 0;
    std::stringstream s;
    s << argv[2];
    s >> divideWith;
    if(!s || !divideWith) {
        std::cout<<"Invalid number entered for dividing";
        return -1;
    }

    uchar table[256];
    for(int i = 0; i < 256; i++)
        table[i] = (uchar)(divideWith * (i / divideWith));

    double t;

    Mat clone = I.clone();
    t = (double)getTickCount();
    J = ScanImageAndReduceC(clone, table);
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    std::cout<<"Time taken by ScanImageAndReduceC()"<<t<<std::endl;
    imwrite("1.jpg",J);

    clone = I.clone();
    t = (double)getTickCount();
    J = ScanImageAndReduceRandomAccess(clone, table);
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    std::cout<<"Time taken by ScanImageAndReduceRandomAccess()"<<t<<std::endl;
    imwrite("2.jpg",J);

    clone = I.clone();
    t = (double)getTickCount();
    J = ScanImageAndReduceIterator(clone, table);
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    std::cout<<"Time taken by ScanImageAndReduceIterator()"<<t<<std::endl;
    imwrite("3.jpg",J);

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for(int i = 0; i < 256; i++)
        p[i] = table[i];
    clone = I.clone();
    t = (double)getTickCount();
    LUT(I, lookUpTable, J);
    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    std::cout<<"Time taken by LUI()"<<t<<std::endl;
    imwrite("4.jpg",J);

}

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table) {
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;

    if(I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for(i=0; i<nRows; i++) {
        p=I.ptr<uchar>(i);
        for(j=0; j<nCols; j++)
            p[j] = table[p[j]];
    }

    return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table) {
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();

    switch(channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for(it=I.begin<uchar>(), end=I.end<uchar>(); it!=end; it++)
                *it = table[*it];
            break;
            }
        case 3:{
            MatIterator_<Vec3b> it, end;
            for(it=I.begin<Vec3b>(), end=I.end<Vec3b>(); it!=end; it++) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
            }
    }

    return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table) {
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels) {
        case 1: {
            for(int i = 0; i < I.rows; i++) {
                for(int j = 0; j < I.cols; i++)
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
            }
            break;
            }
        case 3: {
            Mat_<Vec3b> _I = I;
            for(int i = 0; i < I.rows; i++) {
                for(int j = 0; j < I.cols; j++) {
                    _I(i,j)[0] = table[_I(i,j)[0]];
                    _I(i,j)[1] = table[_I(i,j)[1]];
                    _I(i,j)[2] = table[_I(i,j)[2]];
                }
            }
            I=_I;
            }
    }

    return I;
}
