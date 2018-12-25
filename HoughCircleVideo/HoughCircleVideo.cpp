#include "iostream"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

using namespace std;

int main(int argc, char** argv) {
    VideoCapture cap(1);
    Mat frame;
    Mat gray;
    namedWindow("video", WINDOW_NORMAL);
    char c;
    while(true) {
        cap>>frame;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        medianBlur(gray, gray, 7);
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows/16, 100, 80, 1, 300);
        for(size_t i = 0; i < circles.size(); i++) {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            circle(frame, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
            circle(frame, center, c[2], Scalar(255, 0, 255), 3, LINE_AA);
        }
        imshow("video", frame);
        c = (char)waitKey(10);
        if( c == 27 ) break;
    }
    return 0;
}
