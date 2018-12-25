#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    const char* filename = argc >=2 ? argv[1] : "circles.jpg";
    Mat src = imread(filename, IMREAD_COLOR);
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows/16, 100, 35, 1, 300);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);
    }
    namedWindow("detected circles", WINDOW_NORMAL);
    imshow("detected circles", src);
    waitKey();
    return 0;
}
