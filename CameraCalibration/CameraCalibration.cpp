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

const float calibrationSquareDim = 0.0245f; //metre
const Size chessboardDim = Size(6, 9);
const float arucoSquareDim = 0.11f; //metre

void createKnownBoardPosition(Size boardSize, float squareEdgeLength, vector<Point3f>& corners) {
    for(int i = 0; i < boardSize.height; i++) {
        for(int j = 0; j < boardSize.width; j++) {
            corners.push_back(Point3f(j * squareEdgeLength, i * squareEdgeLength, 0.0f));
        }
    }
}

void getChessBoardCorners(vector<Mat> images, vector< vector<Point2f> >& allFoundCorners, bool showResults = false) {
    for(vector<Mat>::iterator iter = images.begin(); iter!= images.end(); iter++) {
        vector<Point2f> pointBuf;
        bool found = findChessboardCorners(*iter, chessboardDim, pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        if(found)
            allFoundCorners.push_back(pointBuf);

        if(showResults)
            drawChessboardCorners(*iter, chessboardDim, pointBuf, found);
            imshow("Looking for Corners", *iter);
            waitKey(0);
    }
}

void cameraCalib( vector<Mat> calibImages, Size boardSize, float squareEdgeLength, Mat& cameraMatrix, Mat& distCoeff) {
    vector< vector<Point2f> > checkerBoardImageSpacePoints;
    getChessBoardCorners(calibImages, checkerBoardImageSpacePoints, false);

    vector< vector< Point3f > > worldSpaceCornerPoints(1);
    createKnownBoardPosition(boardSize, squareEdgeLength, worldSpaceCornerPoints[0]);
    worldSpaceCornerPoints.resize(checkerBoardImageSpacePoints.size(), worldSpaceCornerPoints[0]);

    vector<Mat> rVectors, tVectors;
    distCoeff = Mat::zeros(8, 1, CV_64F);

    calibrateCamera(worldSpaceCornerPoints, checkerBoardImageSpacePoints, boardSize, cameraMatrix, distCoeff, rVectors, tVectors);

}

bool saveCameraCalib(string name, Mat cameraMatrix, Mat distCoeff) {
    ofstream outStream(name.c_str());
    if(outStream) {
        uint16_t rows = cameraMatrix.rows;
        uint16_t columns = cameraMatrix.cols;

        outStream << rows <<endl;
        outStream << columns <<endl;

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                double value = cameraMatrix.at<double>(i, j);
                outStream << value << endl;
            }
        }

        rows = distCoeff.rows;
        columns = distCoeff.cols;

        outStream << rows;
        outStream << columns;

        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                double value = distCoeff.at<double>(i, j);
                outStream << value << endl;
            }
        }

        outStream.close();
        return true;

    }
    return false;
}
/*
int startWebcamMonitor(Mat& cameraMartix, Mat& distCoeff) {
    Mat frame;
    vector<int> markerIDs;
    vector< vector< Point2f > > markerCorners, rejectedCandidates;
    aruco::DetectorParameters parameters;
    Ptr< aruco::Dictionary > markerDict; = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);
    VideoCapture vid(1);
    if(!vid.isOpened())
        return -1;
    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);
    vector< Vec3d > rotationVectors, translationVectors;
    while(true) {
        if(!vid.read(frame))
            break;

        aruco::detectMarkers(frame, markerDict, markerCorners, markerIDs);
        aruco::estimatePoseSingleMarkers(markerCorners, arucoSquareDim, cameraMartix, distCoeff, rotationVectors, translationVectors);

        for(int i = 0; i < markerIDs.size(); i++) {
            aruco::drawAxis(frame, cameraMartix, distCoeff, rotationVectors, translationVectors, arucoSquareDim);
        }
        imshow("Webcam", frame);
        if(waitKey(30 >= 0)) break;
    }
    return 1;
}
*/
bool loadCameraCalib(string name, Mat& cameraMatrix, Mat& distCoeff) {
    ifstream instream(name.c_str());
    if(instream) {
        uint16_t rows;
        uint16_t cols;

        instream >> rows;
        instream >> cols;

        cameraMatrix = Mat(Size(cols, rows), CV_64F);

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                double read = 0.0f;
                instream >> read;
                cameraMatrix.at<double>(r, c) = read;
                cout << cameraMatrix.at<double>(r, c) << endl;
            }
        }

        instream >> rows;
        instream >> cols;

        distCoeff = Mat(Size(cols, rows), CV_64F);

        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                double read = 0.0f;
                instream >> read;
                distCoeff.at<double>(r, c) = read;
                cout << distCoeff.at<double>(r, c) << endl;
            }
        }

        instream.close();
    }

    return false;
}

int startWebcamMonitoring(Mat& cameraMatrix, Mat& distCoeff) {
    Mat frame;
    vector<int> markerIDs;
    vector< vector< Point2f > > markerCorners, rejectedCandidates;
    aruco::DetectorParameters parameters;
    Ptr< aruco::Dictionary > markerDict = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);
    VideoCapture vid(1);
    if(!vid.isOpened())
        return -1;
    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);
    vector< Vec3d > rotationVectors, translationVectors;
    while(true) {
        if(!vid.read(frame))
            break;

        aruco::detectMarkers(frame, markerDict, markerCorners, markerIDs);
        aruco::estimatePoseSingleMarkers(markerCorners, arucoSquareDim, cameraMatrix, distCoeff, rotationVectors, translationVectors);

        for(int i = 0; i < markerIDs.size(); i++) {
            aruco::drawAxis(frame, cameraMatrix, distCoeff, rotationVectors[i], translationVectors[i], arucoSquareDim);
        }
        imshow("Webcam", frame);
        if(waitKey(30) >= 0) break;
    }
    return 1;
}

void cameraCalibProcess(Mat& cameraMatrix, Mat& distCoeff) {
    Mat frame;
    Mat drawToFrame;
    vector<Mat> savedImages;
    vector< vector< Point2f > > markerCorners, rejectedCandidates;
    VideoCapture vid(1);
    if(!vid.isOpened())
        return;

    int fps = 20;
    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);
    while(true) {
        if(!vid.read(frame))
            break;

        vector<Vec2f> foundPoints;
        bool found = false;

        found = findChessboardCorners(frame, chessboardDim, foundPoints, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        frame.copyTo(drawToFrame);
        drawChessboardCorners(drawToFrame, chessboardDim, foundPoints, found);
        if(found)
            imshow("Webcam", drawToFrame);
        else
            imshow("Webcam", frame);
        char ch = waitKey(1);
        switch(ch) {
            case ' ' :
                if( found ) {
                    Mat temp;
                    frame.copyTo(temp);
                    savedImages.push_back(temp);
                }
                break;
            case 13 :
                if(savedImages.size() > 15) {
                    cameraCalib(savedImages, chessboardDim, calibrationSquareDim, cameraMatrix, distCoeff);
                    saveCameraCalib("I love camera calib", cameraMatrix, distCoeff);
                }
                break;
            case 27 :
                return;
                break;
        }
    }
}

int main(int argc, char** argv) {
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distCoeff;

    //cameraCalibProcess(cameraMatrix, distCoeff);
    loadCameraCalib("I love camera calib", cameraMatrix, distCoeff);
    startWebcamMonitoring(cameraMatrix, distCoeff);

    return 0;
}
