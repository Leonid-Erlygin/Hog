#include <iostream>
#include "opencv2/core/core.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cuda.hpp>
#include "hog_features.h"
using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    Mat image = imread("/home/leonid/jupyterProjects/york/images/P1020171.jpg");
    hog_features hog;
    vector<vector<float>> descriptors = hog.getDescriptors(image, false);
    return 0;
}
