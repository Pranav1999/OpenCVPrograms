#include "iostream"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

const char* window_name = "Pyramids";

int main(int argc, char** argv) {
    //i to zoomin, o to zoomout, esc to close

    Mat src = imread(argv[1]);

    while(true) {
        imshow(window_name, src);
        char c = (char)waitKey(0);

        if(c == 27) break;
        else if(c == 'o') {
            pyrDown(src, src, Size(src.cols/2, src.rows/2));
            std::cout<<"Zoom Out"<<std::endl;
        }
        else if(c == 'i') {
            pyrUp(src, src, Size(src.cols*2, src.rows*2));
            std::cout<<"Zoom In"<<std::endl;
        }
    }

    return 0;
}
