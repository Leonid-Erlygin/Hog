//
// Created by leonid on 08.07.2020.
//

#ifndef HOG_HOG_FEATURES_H
#define HOG_HOG_FEATURES_H
#include "opencv2/core/core.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cuda.hpp>

class hog_features {
public:

    std::vector<std::vector<float>> getDescriptors(const cv::Mat &image, bool oneDescriptor = true,cv::Size stride = cv::Size(32,32));
private:
    cv::HOGDescriptor hog;
    void draw_frame(cv::Point pt, const cv::Mat &image);
};


#endif //HOG_HOG_FEATURES_H
