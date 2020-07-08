#include <iostream>
#include "opencv2/core/core.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iomanip>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/cuda.hpp>

using namespace cv;
using namespace std;

class hog_features {

    HOGDescriptor hog;
public:
    vector<vector<float>> getDescriptors(const Mat &image, bool oneDescriptor = true,Size stride = Size(32,32)) {
        vector<vector<float>> descriptors;
        if (oneDescriptor) {
            //change ratio and resize to match 64x128 size
            Mat resIm;
            vector<float> v;
            resize(image, resIm, Size(64, 128));
            hog.compute(resIm, v);
            descriptors.push_back(v);
        } else {


            //задание шага окошка детектора, с которым он будет скользить по изображению
            int widht = stride.width;
            int heihght = stride.height;
            vector<float> ders;
            vector<Point> loc;
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
            hog.compute(image, ders, Size(0, 0), Size(0, 0), loc);
            //метод выше дал все дескрипторы в одном массиве. Разобъем их на части.
            int hog_size = hog.getDescriptorSize();
            for (int k = 0; k < loc.size(); ++k) {
                descriptors.emplace_back(ders.begin() + k * hog_size, ders.begin() + (k + 1) * hog_size);
            }
        }
        return descriptors;
    }

private:
    void draw_frame(Point pt, const Mat &image) {
        line(image, pt, Point(pt.x + 64, pt.y), Scalar(0, 255, 0));
        line(image, pt, Point(pt.x, pt.y + 128), Scalar(0, 255, 0));
        line(image, Point(pt.x + 64, pt.y), Point(pt.x + 64, pt.y + 128), Scalar(0, 255, 0));
        line(image, Point(pt.x, pt.y + 128), Point(pt.x + 64, pt.y + 128), Scalar(0, 255, 0));
        namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
        imshow("Display window", image);
        waitKey(0);
    }
};


int main(int argc, char **argv) {

    Mat image = imread("/home/leonid/jupyterProjects/york/images/P1020171.jpg");
    hog_features hog;
    vector<vector<float>> descriptors = hog.getDescriptors(image, false);
    return 0;
}
