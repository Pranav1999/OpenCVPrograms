#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    cv::CommandLineParser parser(argc, argv,
                                "{@input   |lena.jpg|input image}"
                                "{ksize   k|1|ksize (hit 'K' to increase its value)}"
                                "{scale   s|1|scale (hit 'S' to increase its value)}"
                                "{delta   d|0|delta (hit 'D' to increase its value)}"
                                "{help    h|false|show help message}");
    cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
    parser.printMessage();
    cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";
    Mat image, src, src_gray;
    Mat grad;
    const String window_name = "Sobel demo";
    int ksize = parser.get<int>("ksize");
    int scale = parser.get<int>("scale");
    int delta = parser.get<int>("delta");
    int ddepth = CV_16S;
    image = imread(parser.get<String>("@input"), IMREAD_COLOR);
    namedWindow(window_name, WINDOW_NORMAL);
    while(true) {
        GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
        cvtColor(src, src_gray, COLOR_BGR2GRAY);
        /*Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
        Sobel(src_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
        Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
        //OR
        //Scharr(src_gray, grad, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);    // converting back to CV_8U
        convertScaleAbs(grad_y, abs_grad_y);
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0 , grad);*/
        Mat abs_grad, dst;
        Laplacian(src_gray,  dst, ddepth, ksize, scale, delta, BORDER_DEFAULT);
        convertScaleAbs(dst, abs_grad);
        imshow(window_name, abs_grad);
        char key = (char)waitKey(0);
        if(key == 27) return 0;
        if(key == 'k' || key == 'K')
            ksize = ksize < 30 ? ksize + 2   : -1;
        if(key == 's' || key == 'S')
            scale++;
        if(key == 'd' || key == 'D')
            delta++;
        if(key == 'a' || key == 'A')
            imwrite("save.jpg", abs_grad);
        if(key == 'r' || key == 'R') {
            scale = 1;
            //ksize = -1; for Sobel
            ksize = 1; // for Laplacian
            delta = 0;
        }
    }
    return 0;
}
