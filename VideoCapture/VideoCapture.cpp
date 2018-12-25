#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;

const int fps = 60;

int main(int argc, char** argv) {
    Mat frame;
    VideoCapture vid("rtsp://184.72.239.149/vod/mp4:BigBuckBunny_175k.mov");
    if(!vid.isOpened())
        return -1;
    //while(ture) {vid >> frame;}
    while(vid.read(frame)) {
        imshow("webcam", frame);
        if(waitKey(1000 / fps) >= 0)
            break;
    }

    return 0;
}
