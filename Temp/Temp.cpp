#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(int argc, char** argv) {
    RNG rng(0xFFFFFFFF);
    for(int i = 0; i < 1000; i++) {
        std::cout<<rng.uniform(1,20)<<std::endl;
    }
}
