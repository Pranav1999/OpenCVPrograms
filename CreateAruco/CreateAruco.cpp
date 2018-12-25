#include<iostream>
#include<sstream>
#include<fstream>

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/aruco.hpp>
#include<opencv2/calib3d.hpp>

using namespace cv;
using namespace std;

void createArucoMarkers() {
    Mat outputMarker;
    Ptr< aruco::Dictionary > markerDict = aruco::getPredefinedDictionary( aruco::DICT_4X4_50 );
    for(int i = 0; i < 50; i++) {
        aruco::drawMarker(markerDict, i, 500, outputMarker, 1);
        ostringstream convert;
        string imgname = "44Marker_";
        convert << imgname << i << ".jpg";
        imwrite(convert.str(), outputMarker);
    }
}

int main(int argc, char** argv) {
    createArucoMarkers();
}
