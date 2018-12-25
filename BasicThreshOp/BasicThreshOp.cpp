#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;

Mat src, dst, gray;
const char* window_name = "Threshold";
const char* trackbar_type = "0 Binary\n1 Binary inverted\n2 Truncate\n3 To zero\n4 To zero inverted";
const char* trackbar_value = "Value";

void Threshold_Demo(int, void*) {
    threshold(gray, dst, threshold_value, max_binary_value, threshold_type);
    imshow(window_name, dst);
}

int main(int argc, char** argv) {
    String imageName("chappal.jpg");
    if (argc > 1)
    {
        imageName = argv[1];
    }
    src = imread( imageName, IMREAD_COLOR );
    if( src.empty() )
        return -1;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    namedWindow("Threshold", WINDOW_NORMAL);
    createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
    createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);

    Threshold_Demo(0,0);

    while(true) {
        char c = (char)waitKey(20);
        if( c == 27)
            break;
    }

    return 0;
}
