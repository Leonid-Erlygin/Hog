//
// Created by leonid on 08.07.2020.
//

#include "hog_features.h"
std::vector<std::vector<float>>hog_features:: getDescriptors(const cv::Mat &image, bool oneDescriptor,cv::Size stride) {
    std::vector<std::vector<float>> descriptors;
    if (oneDescriptor) {
        //change ratio and resize to match 64x128 size
        cv::Mat resIm;
        std::vector<float> v;
        resize(image, resIm, cv::Size(64, 128));
        hog.compute(resIm, v);
        descriptors.push_back(v);
    } else {


        //задание шага окошка детектора, с которым он будет скользить по изображению
        int widht = stride.width;
        int heihght = stride.height;
        std::vector<float> ders;
        std::vector<cv::Point> loc;
        //я вычисляю только дескрипторы, которые целиком лежат на картинке
        int i = 0;
        //здесь получаю локации точек, где нужно считать hog
        while (i + 128 <= image.rows) {
            int j = 0;
            while (j + 64 <= image.cols) {

                loc.emplace_back(j, i);
                //draw_frame(loc.back(),image); //Можно посмотреть откуда берутся hog'и
                j += widht;
            }
            i += heihght;
        }
        hog.compute(image, ders, cv::Size(0, 0), cv::Size(0, 0), loc);
        //метод выше дал все дескрипторы в одном массиве. Разобъем их на части.
        int hog_size = hog.getDescriptorSize();
        for (int k = 0; k < loc.size(); ++k) {
            descriptors.emplace_back(ders.begin() + k * hog_size, ders.begin() + (k + 1) * hog_size);
        }
    }
    return descriptors;
}

void hog_features::draw_frame(cv::Point pt, const cv::Mat &image) {
    line(image, pt, cv::Point(pt.x + 64, pt.y), cv::Scalar(0, 255, 0));
    line(image, pt, cv::Point(pt.x, pt.y + 128), cv::Scalar(0, 255, 0));
    line(image, cv::Point(pt.x + 64, pt.y), cv::Point(pt.x + 64, pt.y + 128), cv::Scalar(0, 255, 0));
    line(image, cv::Point(pt.x, pt.y + 128), cv::Point(pt.x + 64, pt.y + 128), cv::Scalar(0, 255, 0));
    namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", image);
    cv::waitKey(0);
}